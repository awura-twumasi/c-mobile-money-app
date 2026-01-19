#include <stdio.h>   
#include <string.h>  

void displayMenu();
void saveToFile(const char* filename, const char* message);
int validatePassword();
int getOption();
float getAmount();

int main() {
    //declare variable
    int option, network;
    char receiverName[50], receiverNumber[20], confirm;
    float amount;
    char message[200];

    //welcome messages
    printf("Welcome to Awura's Mobile Money Platform\n");
    printf("Dial *171#\n");

    //check if PIN is correct
    if (!validatePassword()) {
        printf("Too many failed attempts. Exiting...\n");
        return 1; //exit program if authentication fails
    }

    //display menu options and get user's choice
    displayMenu();
    option = getOption();

    //handle user selection
    switch(option) {
        case 1:
        case 2:
            printf("\nTransfer Money\n");
            printf("1. MTN\n2. Vodafone\n3. AirtelTigo\n");
            printf("Choose: ");
            scanf("%d", &network);

            //logical OR operator (||) is required here
            if (network == 1 || network == 2 || network == 3) {
                printf("\nReceiver Name: ");
                scanf(" %[^\n]", receiverName); //read full name including spaces

                printf("Receiver Mobile Number: ");
                scanf("%s", receiverNumber);

                //get transfer amount
                amount = getAmount();

                //confirm transaction
                printf("\nTransfer GHS %.2f to %s (%s)?\n", amount, receiverName, receiverNumber);
                printf("Enter PIN to confirm or 0 to cancel: ");
                scanf(" %c", &confirm);

                if (confirm == '0') {
                    printf("\nTransaction cancelled.\n");
                } else {
                    printf("\nTransfer of GHS %.2f to %s (%s) successful.\n",
                           amount, receiverName, receiverNumber);

                    //write transaction message
                    sprintf(message,
                            "Transfer of GHS %.2f to %s (%s) successful.\n",
                            amount, receiverName, receiverNumber);

                    //save transaction to file
                    saveToFile("send_money.txt", message);
                }
            } else {
                printf("Invalid network selected.\n");
            }
            break;

        case 3:
            printf("\nBuy Airtime\n");

            //get airtime amount
            amount = getAmount();

            printf("Enter PIN to confirm or 0 to cancel: ");
            scanf(" %c", &confirm);

            if (confirm == '0') {
                printf("\nAirtime purchase cancelled.\n");
            } else {
                printf("\nYou have successfully purchased GHS %.2f airtime.\n", amount);

                //save airtime transaction
                sprintf(message, "Airtime of GHS %.2f purchased.\n", amount);
                saveToFile("airtime.txt", message);
            }
            break;

        case 4:
            //feature placeholder
            printf("\nCheck Balance\nFeature not yet implemented.\n");
            break;

        default:
            printf("Invalid option.\n");
    }

    return 0; //program ended successfully
}

//validates user PIN with a maximum of 3 attempts
int validatePassword() {
    char password[20];
    char correctPassword[] = "1234";
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter your code (attempt %d of 3): ", attempts + 1);
        scanf("%s", password);

        //compare entered password with correct password
        if (strcmp(password, correctPassword) == 0) {
            printf("Access granted.\n");
            return 1; //successful authentication
        } else {
            printf("Incorrect password.\n");
            attempts++;
        }
    }
    return 0; //authentication failed
}

//displays the main menu
void displayMenu() {
    printf("\n1. Send Money\n2. Transfer Money\n3. Buy Airtime\n4. Check Balance\n");
}

//gets menu option from user
int getOption() {
    int opt;
    printf("Choose: ");
    scanf("%d", &opt);
    return opt;
}

//gets transaction amount from user
float getAmount() {
    float amt;
    printf("Enter amount: ");
    scanf("%f", &amt);
    return amt;
}

//appends transaction details to a file
void saveToFile(const char* filename, const char* message) {
    FILE *file = fopen(filename, "a"); //open file in append mode
    if (file != NULL) {
        fprintf(file, "%s", message);
        fclose(file);
    } else {
        printf("Error writing to %s\n", filename);
    }
}
   }
}
