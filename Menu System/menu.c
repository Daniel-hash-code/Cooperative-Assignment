#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define SIZE 6
#define NUM_CATEGORIES 5

int main()
{
    sqlite3 *db;

    // Open the SQLite database //
    if (sqlite3_open("ProduceDeliveries.db", &db) != SQLITE_OK)
    {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Database connected successfully.\n");

    int choice;

    do
    {
        printf("\n");
        printf("=====================================================\n");
        printf("      NYERI GREEN FARMERS COOPERATIVE SYSTEM\n");
        printf("=====================================================\n");
        printf("1. Display All Farmer Deliveries\n");
        printf("2. Search for a Farmer\n");
        printf("3. Calculate Farmer Payments\n");
        printf("4. Display Pending Payments\n");
        printf("5. Update Payment Status\n");
        printf("6. Display Large Deliveries\n");
        printf("7. Generate Daily Report\n");
        printf("8. Save Updated Records\n");
        printf("9. Exit\n");
        printf("=====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nDisplay All Farmer Deliveries selected.\n");
                break;

            case 2:
                printf("\nSearch Farmer selected.\n");
                break;

            case 3:
                printf("\nCalculate Payments selected.\n");
                break;

            case 4:
                printf("\nDisplay Pending Payments selected.\n");
                break;

            case 5:
                printf("\nUpdate Payment Status selected.\n");
                break;

            case 6:
                printf("\nDisplay Large Deliveries selected.\n");
                break;

            case 7:
                printf("\nGenerate Daily Report selected.\n");
                break;

            case 8:
                printf("\nSave Updated Records selected.\n");
                break;

            case 9:
                printf("\nClosing the system...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 9);

    sqlite3_close(db);

    printf("Database connection closed.\n");

    return 0;
}