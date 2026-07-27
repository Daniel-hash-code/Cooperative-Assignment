#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int main(void)
{
    sqlite3 *db;

    // Open the shared database //
    if (sqlite3_open("../ProduceDeliveries.db", &db) != SQLITE_OK)
    {
        printf("Failed to open database.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Database connected successfully!\n");
    printf("========================================\n");

    int choice;

    do
    {
        printf("\n");
        printf("=============================================\n");
        printf(" NYERI GREEN FARMERS COOPERATIVE SYSTEM\n");
        printf("=============================================\n");
        printf("1. Display All Farmer Deliveries\n");
        printf("2. Search for a Farmer\n");
        printf("3. Calculate Farmer Payments\n");
        printf("4. Display Pending Payments\n");
        printf("5. Update Payment Status\n");
        printf("6. Display Large Deliveries\n");
        printf("7. Generate Daily Report\n");
        printf("8. Save Updated Records\n");
        printf("9. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:{
    printf("\n========== ALL FARMER DELIVERIES ==========\n\n");

    sqlite3_stmt *stmt;

    const char *sql = "SELECT FarmerNumber, FarmerName, ProduceType, QuantityDelivered, PricePerUnit, PaymentStatus FROM ProduceDeliveries;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("----------------------------------------\n");
        printf("Farmer Number : %d\n", sqlite3_column_int(stmt, 0));
        printf("Farmer Name   : %s\n", sqlite3_column_text(stmt, 1));
        printf("Produce Type  : %s\n", sqlite3_column_text(stmt, 2));
        printf("Quantity      : %d\n", sqlite3_column_int(stmt, 3));
        printf("Price Per Unit: %.2f\n", sqlite3_column_double(stmt, 4));
        printf("Payment Status: %s\n", sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left by previous input
    getchar(); // Wait for user to press Enter

    break;
}

          case 2:{
    int farmerNumber;

    printf("\n========== SEARCH FARMER ==========\n");
    printf("Enter Farmer Number: ");
    scanf("%d", &farmerNumber);

    sqlite3_stmt *stmt;

    const char *sql = "SELECT FarmerNumber, FarmerName, ProduceType, QuantityDelivered, PricePerUnit, PaymentStatus "
    "FROM ProduceDeliveries WHERE FarmerNumber = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    // Bind the farmer number to the placeholder //
    sqlite3_bind_int(stmt, 1, farmerNumber);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("\n========== FARMER RECORD ==========\n");

        printf("Farmer Number : %d\n", sqlite3_column_int(stmt, 0));

        printf("Farmer Name   : %s\n", sqlite3_column_text(stmt, 1));

        printf("Produce Type  : %s\n", sqlite3_column_text(stmt, 2));

        printf("Quantity      : %d\n", sqlite3_column_int(stmt, 3));

        printf("Price Per Unit: %.2f\n", sqlite3_column_double(stmt, 4));

        printf("Payment Status: %s\n", sqlite3_column_text(stmt, 5));
    }
    else
    {
        printf("\nFarmer record not found.\n");
    }

    sqlite3_finalize(stmt);

    printf("\nPress Enter to return to the main menu...");
    getchar();   // Consume newline from scanf
    getchar();   // Wait for Enter

    break;
}

            case 3:
{
    printf("\n========== FARMER PAYMENTS ==========\n\n");

    sqlite3_stmt *stmt;

    const char *sql = "SELECT FarmerName, QuantityDelivered, PricePerUnit "
            "FROM ProduceDeliveries;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    double payment;
    double totalPayment = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *farmerName = sqlite3_column_text(stmt, 0);

        int quantity = sqlite3_column_int(stmt, 1);
        double price = sqlite3_column_double(stmt, 2);

        payment = quantity * price;
        totalPayment += payment;

        printf("%-20s : KES %.2f\n", farmerName, payment);
    }

    sqlite3_finalize(stmt);

    printf("-----------------------------------------\n");
    printf("Total Amount Payable : KES %.2f\n", totalPayment);

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}

           case 4:
{
    printf("\n========== PENDING PAYMENTS ==========\n\n");

    sqlite3_stmt *stmt;

    const char *sql = "SELECT FarmerNumber, FarmerName, ProduceType, QuantityDelivered, PricePerUnit, PaymentStatus "
            "FROM ProduceDeliveries WHERE PaymentStatus = 'Pending';";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    int found = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        found = 1;

        int quantity = sqlite3_column_int(stmt, 3);
        double price = sqlite3_column_double(stmt, 4);
        double payment = quantity * price;

        printf("----------------------------------------\n");
        printf("Farmer Number : %d\n", sqlite3_column_int(stmt, 0));

        printf("Farmer Name   : %s\n", sqlite3_column_text(stmt, 1));

        printf("Produce Type  : %s\n", sqlite3_column_text(stmt, 2));

        printf("Quantity      : %d\n", quantity);

        printf("Price Per Unit: %.2f\n", price);

        printf("Amount Payable: KES %.2f\n", payment);

        printf("Payment Status: %s\n", sqlite3_column_text(stmt, 5));
    }

    if (found == 0)
    {
        printf("There are no pending payments.\n");
    }

    sqlite3_finalize(stmt);

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}

            case 5:
{
    printf("\n========== UPDATE PAYMENT STATUS ==========\n\n");

    char confirm;

    printf("Update all pending payments below KES 10,000? (Y/N): ");
    scanf(" %c", &confirm);

    if(confirm != 'Y' && confirm != 'y')
    {
        printf("\nUpdate cancelled.\n");

        printf("\nPress Enter to return to the main menu...");
        getchar();
        getchar();
        break;
    }

    sqlite3_stmt *selectStmt;
    sqlite3_stmt *updateStmt;

    const char *selectSQL = "SELECT FarmerNumber, FarmerName, QuantityDelivered, PricePerUnit "
            "FROM ProduceDeliveries WHERE PaymentStatus='Pending';";

    const char *updateSQL = "UPDATE ProduceDeliveries "
            "SET PaymentStatus='Paid' WHERE FarmerNumber=?;";

    if(sqlite3_prepare_v2(db, selectSQL, -1, &selectStmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SELECT statement.\n");
        break;
    }

    if(sqlite3_prepare_v2(db, updateSQL, -1, &updateStmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare UPDATE statement.\n");
        sqlite3_finalize(selectStmt);
        break;
    }

    int updated = 0;

    while(sqlite3_step(selectStmt) == SQLITE_ROW)
    {
        int farmerNumber = sqlite3_column_int(selectStmt, 0);
        const unsigned char *farmerName = sqlite3_column_text(selectStmt, 1);
        int quantity = sqlite3_column_int(selectStmt, 2);
        double price = sqlite3_column_double(selectStmt, 3);

        double payment = quantity * price;

        if(payment < 10000)
        {
            sqlite3_bind_int(updateStmt, 1, farmerNumber);

            if(sqlite3_step(updateStmt) == SQLITE_DONE)
            {
                printf("Farmer %d (%s) updated to Paid.\n", farmerNumber, farmerName);
                updated++;
            }

            sqlite3_reset(updateStmt);
            sqlite3_clear_bindings(updateStmt);
        }
    }

    sqlite3_finalize(selectStmt);
    sqlite3_finalize(updateStmt);

    printf("\n%d record(s) updated successfully.\n", updated);

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}

            case 6:
{
    printf("\n========== LARGE DELIVERIES ==========\n\n");

    sqlite3_stmt *stmt;

    const char *sql = "SELECT FarmerNumber, FarmerName, ProduceType, QuantityDelivered, PricePerUnit "
            "FROM ProduceDeliveries WHERE QuantityDelivered > 200;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    int found = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        found = 1;

        int quantity = sqlite3_column_int(stmt, 3);
        double price = sqlite3_column_double(stmt, 4);
        double payment = quantity * price;

        printf("----------------------------------------\n");
        printf("Farmer Number : %d\n", sqlite3_column_int(stmt, 0));

        printf("Farmer Name   : %s\n", sqlite3_column_text(stmt, 1));

        printf("Produce Type  : %s\n", sqlite3_column_text(stmt, 2));

        printf("Quantity      : %d\n", quantity);

        printf("Payment Due   : KES %.2f\n", payment);
    }

    if (!found)
    {
        printf("No large deliveries found.\n");
    }

    sqlite3_finalize(stmt);

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}

            case 7:
{
    printf("\n========== DAILY COOPERATIVE REPORT ==========\n\n");

    sqlite3_stmt *stmt;

    const char *sql =
    "SELECT FarmerName, QuantityDelivered, PricePerUnit, PaymentStatus "
    "FROM ProduceDeliveries;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare SQL statement.\n");
        printf("SQLite Error: %s\n", sqlite3_errmsg(db));
        break;
    }

    int totalFarmers = 0;
    int totalQuantity = 0;
    int paidFarmers = 0;
    int pendingFarmers = 0;

    double totalGrossPayment = 0;
    double totalLevy = 0;
    double totalNetPayment = 0;

    int highestQuantity = 0;
    char highestDeliveryFarmer[100] = "";

    double highestPayment = 0;
    char highestPaymentFarmer[100] = "";

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *farmerName = (const char *)sqlite3_column_text(stmt, 0);

        int quantity = sqlite3_column_int(stmt, 1);
        double price = sqlite3_column_double(stmt, 2);

        const char *status = (const char *)sqlite3_column_text(stmt, 3);

        double grossPayment = quantity * price;
        double levy = grossPayment * 0.02;
        double netPayment = grossPayment - levy;

        totalFarmers++;
        totalQuantity += quantity;

        totalGrossPayment += grossPayment;
        totalLevy += levy;
        totalNetPayment += netPayment;

        if(strcmp(status, "Paid") == 0)
            paidFarmers++;
        else
            pendingFarmers++;

        if(quantity > highestQuantity)
        {
            highestQuantity = quantity;
            strcpy(highestDeliveryFarmer, farmerName);
        }

        if(grossPayment > highestPayment)
        {
            highestPayment = grossPayment;
            strcpy(highestPaymentFarmer, farmerName);
        }
    }

    sqlite3_finalize(stmt);

    printf("------------------------------------------\n");
    printf("Total Farmers           : %d\n", totalFarmers);
    printf("Total Quantity          : %d Units\n", totalQuantity);
    printf("Total Gross Payment     : KES %.2f\n", totalGrossPayment);
    printf("Total Cooperative Levy  : KES %.2f\n", totalLevy);
    printf("Total Net Payment       : KES %.2f\n", totalNetPayment);
    printf("Paid Farmers            : %d\n", paidFarmers);
    printf("Pending Farmers         : %d\n", pendingFarmers);
    printf("Highest Delivery        : %s (%d Units)\n", highestDeliveryFarmer, highestQuantity);
    printf("Highest Payment         : %s (KES %.2f)\n", highestPaymentFarmer, highestPayment);
    printf("------------------------------------------\n");

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}

            case 8:
{
    printf("\n========== SAVE UPDATED RECORDS ==========\n\n");

    printf("All changes have already been saved to the database.\n");
    printf("SQLite automatically writes successful updates to the database.\n");

    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();

    break;
}
    
            case 9:
                printf("\nExiting the system...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 9);


    
    
    
    
    
    
    
    sqlite3_close(db);

    printf("Database connection closed.\n");

    return 0;
}