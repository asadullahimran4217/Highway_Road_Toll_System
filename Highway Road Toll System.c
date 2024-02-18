#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char username[50];
    char password[50];
    float account_balance;
} User;

typedef struct {
    char vehicle_type[20];
    float toll_rate;
} TollRate;

typedef struct {
    char timestamp[50];
    char username[50];
    char vehicle_type[20];
    float distance;
    float toll_amount;
} Transaction;

void registerUser(User *users, int *userCount);
void calculateToll(User *users, int userCount, TollRate *tollRates, int tollRateCount, Transaction *transactions, int *transactionCount);
void displayTransactions(Transaction *transactions, int transactionCount);
void rechargeAccount(User *users, int userCount);
void displayUserList(User *users, int userCount);

int main() {
    User users[100];
    int userCount = 0;
    TollRate tollRates[5];
    tollRates[0].toll_rate = 0.1;
    strcpy(tollRates[0].vehicle_type, "Car");
    tollRates[1].toll_rate = 0.25;
    strcpy(tollRates[1].vehicle_type, "Truck");
    tollRates[2].toll_rate = 0.2;
    strcpy(tollRates[2].vehicle_type, "Bus");
    tollRates[3].toll_rate = 0.05;
    strcpy(tollRates[3].vehicle_type, "Motor-Cycle");
    tollRates[4].toll_rate = 0.05;
    strcpy(tollRates[4].vehicle_type, "Auto");
    tollRates[4].toll_rate = 0.3;
    strcpy(tollRates[4].vehicle_type, "Covered Van");
    tollRates[4].toll_rate = 0.6;
    strcpy(tollRates[4].vehicle_type, "Container Truck");
    tollRates[4].toll_rate = 0.2;
    strcpy(tollRates[4].vehicle_type, "Mini Truck");
    tollRates[4].toll_rate = 0.15;
    strcpy(tollRates[4].vehicle_type, "Micro Bus");

    int tollRateCount = 5;
    Transaction transactions[100];
    int transactionCount = 0;
    int choice;

    printf("\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\t\t::::::::::::                          ::::::::::::\n");
    printf("\t\t::::::::::::      Highway Road        ::::::::::::\n");
    printf("\t\t::::::::::::      Toll System         ::::::::::::\n");
    printf("\t\t::::::::::::                          ::::::::::::\n");
    printf("\t\t::::::::::::::::::::::::::::::::::::::::::::::::::\n");

    do {
        printf("\n\tList       Topic\n");
        printf("\n");
        printf("\t 1.       Register User\n");
        printf("\t 2.       Calculate Toll\n");
        printf("\t 3.       Recharge Account\n");
        printf("\t 4.       Display User List\n");
        printf("\t 5.       Display Transactions\n");
        printf("\t 6.       Exit\n");
        printf("\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser(users, &userCount);
                break;
            case 2:
                calculateToll(users, userCount, tollRates, tollRateCount, transactions, &transactionCount);
                break;
            case 3:
                rechargeAccount(users, userCount);
                break;
            case 4:
                displayUserList(users, userCount);
                break;
            case 5:
                displayTransactions(transactions, transactionCount);
                break;
            case 6:
                printf("\n\tExiting the program. Goodbye!\n");
                break;
            default:
                printf("\n\tInvalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
void registerUser(User *users, int *userCount) {
    if (*userCount >= 100) {
        printf("\n\tCannot register more users. Maximum limit reached.\n");
        return;
    }
    printf("\n\tEnter username: ");
    scanf("%s", users[*userCount].username);
    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, users[*userCount].username) == 0) {
            printf("\tUsername already exists. Please choose a different one.\n");
            return;
        }
    }
    printf("\tEnter password: ");
    scanf("%s", users[*userCount].password);
    users[*userCount].account_balance = 0.0;
    printf("\tUser '%s' registered successfully!\n", users[*userCount].username);
    (*userCount)++;
}
void calculateToll(User *users, int userCount, TollRate *tollRates, int tollRateCount, Transaction *transactions, int *transactionCount) {
    char username[50];
    char vehicle_type[20];
    float distance;
    printf("\n\tEnter username: ");
    scanf("%s", username);
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) {
        printf("\n\tUser not found. Please register first.\n");
        return;
    }
    printf("\tEnter vehicle type (e.g., Car, Truck): ");
    scanf("%s", vehicle_type);
    int tollRateIndex = -1;
    for (int i = 0; i < tollRateCount; i++) {
        if (strcmp(tollRates[i].vehicle_type, vehicle_type) == 0) {
            tollRateIndex = i;
            break;
        }
    }
    if (tollRateIndex == -1) {
        printf("\tToll rate not found for the specified vehicle type.\n");
        return;
    }
    printf("\tEnter distance traveled (in miles): ");
    scanf("%f", &distance);
    float toll_amount = distance * tollRates[tollRateIndex].toll_rate;
    if (users[userIndex].account_balance < toll_amount) {
        printf("\tInsufficient account balance. Please recharge your account.\n");
        return;
    }
    users[userIndex].account_balance -= toll_amount;
    strcpy(transactions[*transactionCount].timestamp, "current_time");
    strcpy(transactions[*transactionCount].username, username);
    strcpy(transactions[*transactionCount].vehicle_type, vehicle_type);
    transactions[*transactionCount].distance = distance;
    transactions[*transactionCount].toll_amount = toll_amount;
    printf("\tToll calculated successfully. Transaction recorded.\n");
    (*transactionCount)++;
}

void rechargeAccount(User *users, int userCount) {
    char username[50];
    float amount;
    printf("\tEnter username: ");
    scanf("%s", username);
    int userIndex = -1;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) {
        printf("\tUser not found. Please register first.\n");
        return;
    }
    printf("\tEnter recharge amount: ");
    scanf("%f", &amount);
    users[userIndex].account_balance += amount;
    printf("\tAccount recharge successful. New balance: %.2f\n", users[userIndex].account_balance);
}
void displayUserList(User *users, int userCount) {
    printf("\n\tUser List:\n");
    for (int i = 0; i < userCount; i++) {
        printf("\n\t\t%d. Username: %s, Account Balance: %.2f\n", i + 1, users[i].username, users[i].account_balance);
    }
}
void displayTransactions(Transaction *transactions, int transactionCount) {
    if (transactionCount == 0) {
        printf("\n\t\tNo transactions to display.\n");
        return;
    }
    printf("\n\t\tTransaction History:\n");
    printf("\t\t---------------------------------------------------------------------------------------------------\n");
    printf("\t\t| %-20s | %-20s | %-10s | %-15s | %-15s |\n", "Timestamp", "Username", "Vehicle Type", "Distance (miles)", "Toll Amount");
    printf("\t\t---------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        printf("\t\t| %-20s | %-20s | %-10s   | %-15.2f  | $%-14.2f |\n",
               transactions[i].timestamp, transactions[i].username, transactions[i].vehicle_type,
               transactions[i].distance, transactions[i].toll_amount);
    }
    printf("\t\t---------------------------------------------------------------------------------------------------\n");
}

