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
                printf("\nOption 5 selected.\n");
                break;

            case 6:
                printf("\nOption 6 selected.\n");
                break;

            case 7:
                printf("\nOption 7 selected.\n");
                break;

            case 8:
                printf("\nOption 8 selected.\n");
                break;

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