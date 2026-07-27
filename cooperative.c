#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

#define SIZE 6

/*Callback Function
  SQLite automatically calls this function for each row returned by the SELECT statement 
  
  argc: Number of columns in the current row
  argv: Value in each column
  azCol: Column names
  */

  int displayPending(void *NotUsed, int argc, char **argv, char **azCol)
{
    int i;

    printf("\n------------------------------\n");

    /* Print every column in the current row */
    for(i = 0; i < argc; i++)
    {
        printf("%s : %s\n", azCol[i], argv[i]? argv[i] : "NULL");
    }

    return 0;
}
int main(void) {
  sqlite3 *db;
  if(sqlite3_open("ProduceDeliveries.db", &db) != SQLITE_OK) 
  {
    printf("Error opening database: %s\n", sqlite3_errmsg(db));
    return 1;
  }
  printf("Database connected successfully.\n");

  char *sql =
"CREATE TABLE IF NOT EXISTS ProduceDeliveries ("
"FarmerNumber INTEGER PRIMARY KEY,"
"FarmerName TEXT,"
"ProduceType TEXT,"
"QuantityDelivered INTEGER,"
"PricePerUnit REAL,"
"PaymentStatus TEXT"
");";

char *errMsg = NULL;

if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK)
{
    printf("SQL Error: %s\n", errMsg);
    sqlite3_free(errMsg);
    errMsg = NULL;
}
else
{
    printf("Table created successfully (or already exists).\n");
}

/*Insert the sample farmer records into the database.
  INSERT OR IGNORE prevents duplicate records if the
  program is run multiple times.*/

char *insertSQL =
"INSERT OR IGNORE INTO ProduceDeliveries VALUES "
"(101,'Mwangi Kamau','Milk',120,55,'Pending'),"
"(102,'Wanjiku Njeri','Coffee',85,120,'Paid'),"
"(103,'Peter Maina','Potatoes',300,40,'Pending'),"
"(104,'Akinyi Otieno','Maize',250,65,'Pending'),"
"(105,'Mutiso Musyoka','Milk',150,55,'Paid'),"
"(106,'Chebet Kiptoo','Vegetables',95,80,'Pending');";

if (sqlite3_exec(db, insertSQL, 0, 0, &errMsg) != SQLITE_OK)
{
    printf("Error inserting records: %s\n", errMsg);
    sqlite3_free(errMsg);
    errMsg = NULL;
}
else
{
    printf("Sample farmer records inserted successfully.\n");
}

  int farmerNumbers[SIZE] = {101, 102, 103, 104, 105, 106};

  char farmerNames[SIZE][50] = {"Mwangi Kamau",   "Wanjiku Njeri",
                                "Peter Maina",    "Akinyi Otieno",
                                "Mutiso Musyoka", "Chebet Kiptoo"};

  char produceTypes[SIZE][20] = {"Milk",  "Coffee", "Potatoes",
                                 "Maize", "Milk",   "Vegetables"};

  int quantities[SIZE] = {120, 85, 300, 250, 150, 95};

  double pricesPerUnit[SIZE] = {55, 120, 40, 65, 55, 80};

  char paymentStatus[SIZE][10] = {"Pending", "Paid", "Pending",
                                  "Pending", "Paid", "Pending"};

  // Question 1: Display Farmer Records //

  int i;

  for (i = 0; i < SIZE; i++) {
    printf("Farmer Number : %d\n", farmerNumbers[i]);
    printf("Farmer Name   : %s\n", farmerNames[i]);
    printf("Produce Type  : %s\n", produceTypes[i]);
    printf("Quantity      : %d\n", quantities[i]);
    printf("Price Per Unit: %.2f\n", pricesPerUnit[i]);
    printf("Payment Status: %s\n", paymentStatus[i]);
    printf("\n");
  }

  // Question 2: Calculate Farmer Payments //

  double payments[SIZE];

  printf("\n Farmer Payments \n");

  for (i = 0; i < SIZE; i++) {
    payments[i] = quantities[i] * pricesPerUnit[i];
    printf("%s: KES %.2f\n", farmerNames[i], payments[i]);
  }

  // Question 3: Calculate total pay //

  double totalPayment = 0;

  for (i = 0; i < SIZE; i++) {
    totalPayment = totalPayment + payments[i];
  }

  printf("\nTotal amount payable: KES %.2f\n", totalPayment);

  // Question 4: Identify Pending Payments //

  printf("\n--- Pending Payments ---\n");

  /*for (i = 0; i < SIZE; i++) {
    if (strcmp(paymentStatus[i], "Pending") == 0) {
      printf("Farmer Number : %d\n", farmerNumbers[i]);
      printf("Farmer Name   : %s\n", farmerNames[i]);
      printf("Amount Payable: KES %.2f\n", payments[i]);
      printf("Payment Status: %s\n", paymentStatus[i]);
      printf("\n");
    }
  }*/

  /*Display all farmers with Pending payments
  using the SQLite database.*/

printf("\n========== QUESTION 4 ==========\n");
printf("Farmers with Pending Payments:\n");

char *pendingSQL =
"SELECT * FROM ProduceDeliveries "
"WHERE PaymentStatus='Pending';";

/* Execute the SQL statement */
if (sqlite3_exec(db, pendingSQL, displayPending, NULL, &errMsg) != SQLITE_OK)
{
    printf("SQL Error : %s\n", errMsg);
    sqlite3_free(errMsg);
}

// Question 5: Update Payment Status for Payments Below KES 10,000 //

printf("\n========== QUESTION 5 ==========\n");
printf("Updating payment status for payments below KES 10,000...\n");

/* Parameterized SQL UPDATE statement.
   The '?' placeholder will be replaced with the FarmerNumber
   using sqlite3_bind_int(). */

const char *updateSQL =
    "UPDATE ProduceDeliveries "
    "SET PaymentStatus = 'Paid' "
    "WHERE FarmerNumber = ?;";

sqlite3_stmt *stmt;

// Prepare the SQL statement once. //
if (sqlite3_prepare_v2(db, updateSQL, -1, &stmt, NULL) != SQLITE_OK)
{
    printf("Failed to prepare UPDATE statement: %s\n",
           sqlite3_errmsg(db));
}
else
{
    for(i = 0; i < SIZE; i++)
    {
        // Check whether the payment is below KES 10,000 and the payment is still pending. //
        if(payments[i] < 10000 &&
           strcmp(paymentStatus[i], "Pending") == 0)
        {
            // Update the local array //
            strcpy(paymentStatus[i], "Paid");

            // Remove any previous parameter values //
            sqlite3_clear_bindings(stmt);

            // Bind the farmer number into the '?' placeholder //
            sqlite3_bind_int(stmt, 1, farmerNumbers[i]);

            // Execute the UPDATE statement / /
            if(sqlite3_step(stmt) != SQLITE_DONE)
            {
                printf("Update failed for Farmer %d: %s\n", farmerNumbers[i], sqlite3_errmsg(db));
            }
            else
            {
                printf("---------------------------------\n");
                printf("Farmer Number : %d\n", farmerNumbers[i]);
                printf("Farmer Name   : %s\n", farmerNames[i]);
                printf("Payment       : KES %.2f\n", payments[i]);
                printf("New Status    : %s\n", paymentStatus[i]);
                printf("---------------------------------\n");
            }

            // Reset the prepared statement so it can be reused //
            sqlite3_reset(stmt);
        }
    }

    // Release resources used by the prepared statement //
    sqlite3_finalize(stmt);
}

// Verify the updates by displaying the remaining farmers whose payment status is still Pending.//

printf("\n Remaining Pending Payments:\n");

if(sqlite3_exec(db, pendingSQL, displayPending, NULL, &errMsg) != SQLITE_OK)
{
    printf("SQL Error: %s\n", errMsg);
    sqlite3_free(errMsg);
    errMsg = NULL;
}

  // Question 6: Farmer with the Highest Delivery Quantity //
 
  printf("\n========== QUESTION 6 ==========\n");
  printf("Farmer with the Highest Delivery Quantity:\n\n");
 
  /* Assume the first farmer has the highest quantity, then compare
     every other farmer against the current highest found so far. */
  int highestDeliveryIndex = 0;
 
  for (i = 1; i < SIZE; i++) {
    if (quantities[i] > quantities[highestDeliveryIndex]) {
      highestDeliveryIndex = i;
    }
  }

  // Display the farmer with the highest delivery //

printf("---------------------------------\n");
printf("Farmer Name       : %s\n", farmerNames[highestDeliveryIndex]);
printf("Produce Type      : %s\n", produceTypes[highestDeliveryIndex]);
printf("Quantity Delivered: %d\n", quantities[highestDeliveryIndex]);
printf("Payment Due       : KES %.2f\n", payments[highestDeliveryIndex]);
printf("---------------------------------\n");


// Question 7: Farmer with the Lowest Payment //
 
  printf("========== QUESTION 7 ==========\n");
  printf("Farmer with the Lowest Payment:\n\n");
 
  // Assume the first farmer has the lowest payment, then compare every other farmer against the current lowest found so far. //
  int lowestIndex = 0;
 
  for (i = 1; i < SIZE; i++) {
    if (payments[i] < payments[lowestIndex]) {
      lowestIndex = i;
    }
  }
 
  printf("---------------------------------\n");
  printf("Farmer Name   : %s\n", farmerNames[lowestIndex]);
  printf("Amount Payable: KES %.2f\n", payments[lowestIndex]);
  printf("---------------------------------\n");

  /*The loop begins by assuming that the first payment in the payments array is the lowest. 
  It then compares each subsequent payment with the current lowest payment. 
  Whenever a smaller payment is found, the index of that payment is stored as the new lowest. 
  After the loop finishes, the stored index identifies the farmer with the lowest payment.*/



  // Question 8: Search for a Farmer by Number //
 
  printf("========== QUESTION 8 ==========\n");
 
  int searchNumber;
  int found = 0;
 
  printf("Enter the Farmer Number to search for: ");
  scanf("%d", &searchNumber);
 
  printf("\nSearching for Farmer Number %d in the array:\n\n", searchNumber);
 
  for (i = 0; i < SIZE; i++) {
    if (farmerNumbers[i] == searchNumber) {
      found = 1;
      printf("Farmer Number : %d\n", farmerNumbers[i]);
      printf("Farmer Name   : %s\n", farmerNames[i]);
      printf("Produce Type  : %s\n", produceTypes[i]);
      printf("Quantity      : %d\n", quantities[i]);
      printf("Amount Payable: KES %.2f\n", payments[i]);
      printf("Payment Status: %s\n", paymentStatus[i]);
      break;  
    }
  }
 
  if (found == 0) {
    printf("Farmer record not found.\n");
  }

// Same search performed on the database, using a parameterized SELECT. //

  printf("\nSearch performed on database...\n");

const char *searchSQL =
    "SELECT * FROM ProduceDeliveries "
    "WHERE FarmerNumber = ?;";

sqlite3_stmt *searchStmt;

if(sqlite3_prepare_v2(db, searchSQL, -1, &searchStmt, NULL) != SQLITE_OK)
{
    printf("Failed to prepare search statement: %s\n", sqlite3_errmsg(db));
}
else
{
    sqlite3_bind_int(searchStmt, 1, searchNumber);

    int dbFound = 0;

    while(sqlite3_step(searchStmt) == SQLITE_ROW)
    {
        dbFound = 1;

        printf("\nRecord Retrieved from Database\n");
        printf("---------------------------------\n");
        printf("Farmer Number     : %d\n", sqlite3_column_int(searchStmt, 0));
        printf("Farmer Name       : %s\n", (const char *)sqlite3_column_text(searchStmt, 1));
        printf("Produce Type      : %s\n", (const char *)sqlite3_column_text(searchStmt, 2));
        printf("Quantity Delivered: %d\n", sqlite3_column_int(searchStmt, 3));
        printf("Price Per Unit    : KES %.2f\n", sqlite3_column_double(searchStmt, 4));
        printf("Payment Status    : %s\n",  (const char *)sqlite3_column_text(searchStmt, 5));
        printf("---------------------------------\n");
    }

    if(dbFound == 0)
    {
        printf("Farmer record not found in the database.\n");
    }

    sqlite3_finalize(searchStmt);
}



// Question 9: Counting Produce Categories //


#define NUM_CATEGORIES 5

printf("\n========== QUESTION 9 ==========\n");
printf("Number of Farmers per Produce Category\n");
printf("---------------------------------\n");

// List of produce categories //
const char *categories[NUM_CATEGORIES] =
{ "Milk", "Coffee", "Potatoes", "Maize", "Vegetables" };

// Array to store the number of farmers for each category //
int produceCounts[NUM_CATEGORIES] = {0};

int c;
for(c = 0; c < NUM_CATEGORIES; c++)         //  Count the number of farmers delivering each produce type //
{
    for(i = 0; i < SIZE; i++)
    {
        if(strcmp(produceTypes[i], categories[c]) == 0)
        {
            produceCounts[c]++;
        }
    }
}

// Display the results //
for(c = 0; c < NUM_CATEGORIES; c++)
{
    printf("%-12s : %d farmer(s)\n",
           categories[c],
           produceCounts[c]);
}

printf("---------------------------------\n");

// Question 10: Calculating Payments by Produce Type //
 
  printf("========== QUESTION 10 ==========\n");
  printf("Total Payments by Produce Type\n");
  printf("---------------------------------\n");
 
  // Array to store total payment for each produce category //
  double producePayments[NUM_CATEGORIES] = {0};
 
  // Calculate total payment for each produce category //
  for (c = 0; c < NUM_CATEGORIES; c++) {
    for (i = 0; i < SIZE; i++) {
      if (strcmp(produceTypes[i], categories[c]) == 0) {
        producePayments[c] += payments[i];
      }
    }
  }
 
  // Display the results //
  for (c = 0; c < NUM_CATEGORIES; c++) {
    printf("%-12s : KES %.2f\n", categories[c], producePayments[c]);
  }
  printf("---------------------------------\n\n");
 


  // Question 11: Identify Large Deliveries (over 200 units) //
 
  printf("========== QUESTION 11 ==========\n");
  printf("Farmers with Deliveries Exceeding 200 Units\n");
  printf("---------------------------------\n");
 
  int largeDeliveryFarmers[SIZE];   
  int largeCount = 0;            
 
  for (i = 0; i < SIZE; i++) {
    if (quantities[i] > 200) {
      largeDeliveryFarmers[largeCount] = farmerNumbers[i];
      largeCount++;
 
      printf("Farmer Number : %d\n", farmerNumbers[i]);
      printf("Farmer Name   : %s\n", farmerNames[i]);
      printf("Quantity      : %d\n", quantities[i]);
      printf("\n");
    }
  }
 
  if (largeCount == 0) {
    printf("No farmers exceeded 200 units.\n\n");
  } else {
    printf("Farmer numbers stored in largeDeliveryFarmers[]: ");
    for (i = 0; i < largeCount; i++) {
      printf("%d ", largeDeliveryFarmers[i]);
    }
    printf("\n\n");
  }
 
  printf("\nLarge Deliveries Retrieved from Database\n");
 
  const char *largeDeliverySQL =
      "SELECT FarmerNumber, FarmerName, QuantityDelivered "
      "FROM ProduceDeliveries WHERE QuantityDelivered > 200;";
 
  if (sqlite3_exec(db, largeDeliverySQL, displayPending, NULL, &errMsg) != SQLITE_OK)
  {
      printf("SQL Error : %s\n", errMsg);
      sqlite3_free(errMsg);
      errMsg = NULL;
  }
  printf("---------------------------------\n\n");


// Question 12: Applying a Cooperative Levy //

printf("\n========== QUESTION 12 ==========\n");
printf("Gross Payment, Levy, and Net Payment\n");
printf("---------------------------------------\n");

// Arrays to store levy and net payment //
double levies[SIZE];
double netPayments[SIZE];

// Calculate levy and net payment for each farmer //
for(i = 0; i < SIZE; i++)
{
    levies[i] = payments[i] * 0.02;
    netPayments[i] = payments[i] - levies[i];

    printf("Farmer Name  : %s\n", farmerNames[i]);
    printf("Gross Payment: KES %.2f\n", payments[i]);
    printf("Levy (2%%)    : KES %.2f\n", levies[i]);
    printf("Net Payment  : KES %.2f\n", netPayments[i]);
    printf("-------------------------------------\n");
}


printf("========== QUESTION 13 ==========\n");
  printf("Pseudocode: Update NetPayment in the Database\n");
  printf("---------------------------------\n");
  printf(
    "BEGIN\n"
    " OPEN connection TO database\n"
    "\n"
    "    FOR each farmer i FROM 1 TO NUMBER_OF_FARMERS\n"
    "        SET sql = \"UPDATE ProduceDeliveries\n"
    "                    SET NetPayment = ?\n"
    "                    WHERE FarmerNumber = ?\"\n"
    "\n"
    "        PREPARE statement USING sql\n"
    "        BIND netPayments[i] TO placeholder 1\n"
    "        BIND farmerNumbers[i] TO placeholder 2\n"
    "\n"
    "        EXECUTE statement\n"
    "        CLEAR bindings\n"
    "    END FOR\n"
    "\n"
    "    CLOSE connection\n"
    "END\n"
  );
  printf("---------------------------------\n\n");
 

  // Question 14: Identify and (with confirmation) Delete Invalid Records //

printf("\n========== QUESTION 14 ==========\n");
printf("Checking for Invalid Records\n");
printf("---------------------------------\n");

int invalidFound = 0;

// Parameterized SQL DELETE statement //
const char *deleteSQL =
    "DELETE FROM ProduceDeliveries "
    "WHERE FarmerNumber = ?;";

sqlite3_stmt *deleteStmt;

// Prepare the DELETE statement once //
if (sqlite3_prepare_v2(db, deleteSQL, -1, &deleteStmt, NULL) != SQLITE_OK)
{
    printf("Failed to prepare DELETE statement: %s\n",
           sqlite3_errmsg(db));
}
else
{
    // Check every farmer record  
    for(i = 0; i < SIZE; i++)
    {
        if(quantities[i] <= 0 ||
           pricesPerUnit[i] <= 0 ||
           farmerNumbers[i] <= 0)
        {
            invalidFound = 1;

            printf("---------------------------------\n");
            printf("Invalid Record Found\n");
            printf("---------------------------------\n");
            printf("Farmer Number     : %d\n", farmerNumbers[i]);
            printf("Farmer Name       : %s\n", farmerNames[i]);
            printf("Produce Type      : %s\n", produceTypes[i]);
            printf("Quantity Delivered: %d\n", quantities[i]);
            printf("Price Per Unit    : KES %.2f\n", pricesPerUnit[i]);
            printf("Payment Status    : %s\n", paymentStatus[i]);
            printf("---------------------------------\n");

            char confirm;

            printf("Delete this record from the database? (Y/N): ");
            scanf(" %c", &confirm);

            if(confirm == 'Y' || confirm == 'y')
            {
                // Remove previous parameter values //
                sqlite3_clear_bindings(deleteStmt);

                // Bind the farmer number //
                sqlite3_bind_int(deleteStmt, 1, farmerNumbers[i]);

                // Execute the DELETE statement //
                if(sqlite3_step(deleteStmt) != SQLITE_DONE)
                {
                    printf("Delete failed: %s\n",
                           sqlite3_errmsg(db));
                }
                else
                {
                    printf("Farmer %d deleted successfully.\n",
                           farmerNumbers[i]);
                }

                // Reset the prepared statement for reuse //
                sqlite3_reset(deleteStmt);
            }
            else
            {
                printf("Deletion cancelled by user.\n");
            }

            printf("\n");
        }
    }

    // Release resources used by the prepared statement //
    sqlite3_finalize(deleteStmt);
}

// No invalid records found //
if(invalidFound == 0)
{
    printf("No invalid records found in the current dataset.\n");
}

printf("---------------------------------\n");



// Question 15: Generating a Daily Summary //

printf("\n========== QUESTION 15 ==========\n");
printf("Daily Cooperative Summary Report\n");
printf("===================================\n");

// Summary variables //
int totalFarmers = SIZE;
int totalQuantity = 0;
double totalGrossPayment = 0.0;
double totalLevy = 0.0;
double totalNetPayment = 0.0;

int paidFarmers = 0;
int pendingFarmers = 0;

// Assume the first farmer has the highest payment //
int highestPaymentIndex = 0;
for(i = 0; i < SIZE; i++)
{
    totalQuantity += quantities[i];
    totalGrossPayment += payments[i];
    totalLevy += levies[i];
    totalNetPayment += netPayments[i];

    if(strcmp(paymentStatus[i], "Paid") == 0)
    {
        paidFarmers++;
    }
    else
    {
        pendingFarmers++;
    }

    if(payments[i] > payments[highestPaymentIndex])
    {
        highestPaymentIndex = i;
    }
}

// Display the report //

printf("Total Farmers              : %d\n", totalFarmers);
printf("Total Quantity Delivered   : %d Units\n", totalQuantity);
printf("Total Gross Payment        : KES %.2f\n", totalGrossPayment);
printf("Total Cooperative Levy     : KES %.2f\n", totalLevy);
printf("Total Net Payment          : KES %.2f\n", totalNetPayment);
printf("Paid Farmers               : %d\n", paidFarmers);
printf("Awaiting Payment           : %d\n", pendingFarmers);

printf("\nHighest Delivery\n");
printf("---------------------------------\n");
printf("Farmer Name : %s\n", farmerNames[highestDeliveryIndex]);
printf("Quantity    : %d Units\n", quantities[highestDeliveryIndex]);

printf("\nHighest Payment\n");
printf("---------------------------------\n");
printf("Farmer Name : %s\n", farmerNames[highestPaymentIndex]);
printf("Payment     : KES %.2f\n", payments[highestPaymentIndex]);

printf("=========================================\n");




sqlite3_close(db);
  return 0;
}
