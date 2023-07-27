#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_MENU_ITEMS = 5;

class RECEIPT {
private:
    string username;
    string paymentMethod;
    string orderOption;
    double total; // Track the total

public:
    RECEIPT(string username, string paymentMethod, string orderOption, double total) {
        this->username = username;
        this->paymentMethod = paymentMethod;
        this->orderOption = orderOption;
        this->total = total;
    }

    void writeToDataFile(string menuItems[], double menuPrices[], int order[]) {
        ofstream outputFile("data.dat");
        if (outputFile.is_open()) {
            outputFile << "Item\t\tQuantity\tPrice" << endl;
            for (int i = 0; i < MAX_MENU_ITEMS - 1; i++) {
                if (order[i] > 0) {
                    outputFile << menuItems[i] << "\t\t" << order[i] << "\t\t" << menuPrices[i] * order[i] << endl;
                }
            }
            outputFile << "Total:\t\t\tRM" << total << endl;
            outputFile << "Username: " << username << endl;
            outputFile << "Payment Method: " << paymentMethod << endl;
            outputFile << "Order Type: " << orderOption << endl;
            outputFile.close();
            cout << "Data successfully written to data.dat file." << endl;
        } else {
            cout << "Unable to open data.dat file." << endl;
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "========== MENU ==========" << endl;
    cout << "1. BBQ Chicken - RM10" << endl;
    cout << "2. Hawaiian - RM10" << endl;
    cout << "3. Pepperoni - RM10" << endl;
    cout << "4. Mushroom Soup - RM4" << endl;
    cout << "5. Next" << endl;
    cout << "==========================" << endl;
}

// Function to validate the user's login credentials
bool validateCredentials(string username, string password) {
    // Here, you would typically validate the credentials against a database
    // For simplicity, this example uses hard-coded credentials
    if (username == "am" && password == "am00") {
        return true;
    } else {
        return false;
    }
}

// Function to handle Bank Card payment
void processBankCardPayment(int& cardNumber, double& creditLimit, double& total) {
    double amount;
    cout << "Welcome to the Pixza Hot Cafe!" << endl;

    while (true) {
        cout << "\nEnter your card number: ";
        cin >> cardNumber;

        cout << "Enter the payment amount: RM";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid payment amount. Please enter a positive value." << endl;
        } else if (amount > creditLimit) {
            cout << "Payment amount exceeds credit limit. Payment failed." << endl;
        } else {
            // Process payment logic
            // Assuming successful payment, deduct the amount from credit limit
            creditLimit -= amount;
            total = amount; // Set total for receipt
            cout << "Payment successful. Your updated credit limit is: RM" << creditLimit << endl;
            break;
        }
    }
}

// Function to handle QR code payment
void processQRCodePayment(double& total) {
    string qrCode;
    cout << "=== Payment Using QR Code ===" << endl;

    // Logic to decode the QR code and extract relevant information
    // (e.g., recipient's account number, payment amount, etc.)

    // Stimulating Scanning of a QR code
    cout << "Scan the QR code: ";
    cin >> qrCode;

    cout << "Enter the amount: ";
    cin >> total;

    // Display a success message
    cout << "Payment successful!" << endl;
}

void processCardPayment(double& total, const string& recipientName) {
    cout << "Enter your card PIN: ";
    int cardPIN;
    cin >> cardPIN;

    // Here you can add code to validate the card PIN with the bank's records
    // For simplicity, let's assume any PIN is accepted for payment.

    cout << "Enter the payment amount: RM";
    cin >> total;

    cout << "Card payment to " << recipientName << " successful." << endl;
}

void processPayWavePayment(double& total) {
    cout << "Enter the payment amount: RM";
    cin >> total;
    cout << "PayWave payment successful." << endl;
}

int main() {
    string menuItems[MAX_MENU_ITEMS] = { "BBQ Chicken", "Hawaiian", "Pepperoni", "Mushroom Soup", "Exit" };
    double menuPrices[MAX_MENU_ITEMS] = { 10.0, 10.0, 10.0, 4.0, 0.0 };

    int order[MAX_MENU_ITEMS] = { 0 };
    int choice;
    int quantity;
    double total = 0.0;

    string username, password;
    double bankAmount = 1000.0; // Set initial bank amount to RM1000

    cout << "Welcome to the Pixza HOT!" << endl;
    cout << "====================================" << endl;

    // Login process
    while (true) {
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        if (validateCredentials(username, password)) {
            cout << "Login successful!" << endl;
            break;
        } else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }

    do {
        cout << "Welcome to the Pixza HOT!" << endl;
        cout << "====================================" << endl;

        displayMenu();

        while (true) {
            cout << "Enter your choice (1-" << MAX_MENU_ITEMS << "): ";
            cin >> choice;

            if (choice < 1 || choice > MAX_MENU_ITEMS) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            if (choice == MAX_MENU_ITEMS) {
                break;
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            order[choice - 1] += quantity;
            total += menuPrices[choice - 1] * quantity;

            cout << "Added " << quantity << " " << menuItems[choice - 1] << "(s) to your order." << endl;

            displayMenu();
        }

        cout << "Total: RM" << total << endl;

        int paymentOption;
        cout << "Choose your payment option:" << endl;
        cout << "1. Scan QR Code" << endl;
        cout << "2. Pay with Card (using PIN)" << endl;
        cout << "3. Pay with Card (using PayWave)" << endl;
        cout << "Enter option: ";
        cin >> paymentOption;

        string paymentMethod;
        int cardNumber = 0;

        switch (paymentOption) {
            case 1:
                paymentMethod = "Scan QR Code";
                processQRCodePayment(total);
                break;
            case 2:
                paymentMethod = "Card (using PIN)";
                processCardPayment(total, "Pixza HOT");
                break;
            case 3:
                paymentMethod = "Card (using PayWave)";
                processPayWavePayment(total);
                break;
            default:
                cout << "Invalid payment option. Payment failed." << endl;
                return 0;
        }

        // Deduct the payment from the bank amount
        bankAmount -= total;

        int orderOption;
        cout << "Choose your option:" << endl;
        cout << "1. Serve at table" << endl;
        cout << "2. Self-pickup" << endl;
        cout << "Enter option: ";
        cin >> orderOption;

        int tableNo;
        int orderNo;
        string orderType;

        switch (orderOption) {
            case 1:
                cout << "Enter your table number: ";
                cin >> tableNo;
                orderType = "Serve at Table";
                break;
            case 2:
                orderNo = 34568;
                orderType = "Self-pickup";
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                return 0;
        }

        RECEIPT receipt(username, paymentMethod, orderType, total);
        receipt.writeToDataFile(menuItems, menuPrices, order);

        cout << "\n\n============ RECEIPT ============" << endl;
        cout << "Username: " << username << endl;
        cout << "Payment Method: " << paymentMethod << endl;
        cout << "Order Type: " << orderType << endl;

        if (orderOption == 1) {
            cout << "Table Number: " << tableNo << endl;
        } else {
            cout << "Order Number: " << orderNo << endl;
        }

        cout << "---------------------------------" << endl;
        cout << "Item\t\tQuantity\tPrice" << endl;
        cout << "---------------------------------" << endl;

        for (int i = 0; i < MAX_MENU_ITEMS - 1; i++) {
            if (order[i] > 0) {
                cout << menuItems[i] << "\t\t" << order[i] << "\t\t" << menuPrices[i] * order[i] << endl;
            }
        }

        cout << "---------------------------------" << endl;
        cout << "Total:\t\t\tRM" << total << endl;
        cout << "=================================" << endl;

        // Display the updated bank balance
        cout << "\nYour bank balance after this payment: RM" << bankAmount << endl;
        cout << "Your order is now prepared. Please wait 5 minutes" << endl;

        // Reset for the next order
        total = 0.0;
        for (int i = 0; i < MAX_MENU_ITEMS; i++) {
            order[i] = 0;
        }

        // Ask if the customer wants to make another order
        char anotherOrder;
        cout << "Do you want to make another order? (y/n): ";
        cin >> anotherOrder;

        if (anotherOrder == 'n' || anotherOrder == 'N') {
            cout << "\nThank you for your purchase! Have a great day!" << endl;
            break;
        }

    } while (true);

    return 0;
}
