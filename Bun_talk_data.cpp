#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Structure to store user accounts
struct User {
    string username;
    string password;
};

// Structure to store menu items
struct MenuItem {
    string name;
    double price;
};

// Function prototypes
void displayMenu();
double calculateBill();
void registerUser();
void login();
void displayHelp();

// Global variables
vector<User> users;
vector<MenuItem> menu;
vector<int> selectedItems;
bool loggedIn = false;

// Function to display the menu
void displayMenu() {
	
	cout << "\n";
    cout << "+---------------------------------+\n";
    cout << "|      Welcome to Bun Talk       |\n";
    cout << "+---------------------------------+\n";
    cout << "\n";
    cout << "Bakery Menu:\n";
    cout << "\n";

    for (int i = 0; i < menu.size(); i++) {
        cout << i + 1 << ". " << menu[i].name << " - $" << fixed << setprecision(2) << menu[i].price << endl;
    }
}


// Function to calculate the bill
double calculateBill() {
    double total = 0.0;
    for (int itemIndex : selectedItems) {
        total += menu[itemIndex].price;
    }
    return total;
}

// Function to perform user registration and save to a file
void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    // Check if the username already exists
    for (const User& user : users) {
        if (user.username == username) {
        	cout << "\n";
            cout << "Username already exists. Please choose a different one.\n";
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;
    
    users.push_back({username, password});

    // Save the new user data to an output file
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << endl;
        userFile.close();
        cout << "\n";
        cout << "Registration successful. You can now log in.\n";
    } else {
    	cout << "\n";
        cout << "Error: Unable to save user data.\n";
    }
}

// Function to perform user login
void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if the provided username and password match any user in the vector
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            loggedIn = true;
            cout << "\n";
            cout << "Login successful. Welcome, " << username << "!\n";
            return;
        }
    }
    cout << "Invalid username or password. Please try again.\n";
}

void displayHelp() {
    cout << "Bun Talk Bakery Billing System - Help\n";
    cout << "=====================================\n";
    cout << "This program allows you to:\n";
    cout << "1. Register as a new user.\n";
    cout << "2. Log in with an existing account.\n";
    cout << "3. View the bakery menu and select items.\n";
    cout << "4. Calculate and print your bill.\n";
    cout << "5. Log out.\n";
    cout << "6. Exit the program.\n";
    cout << "-------------------------------------\n";
    cout << "Usage:\n";
    cout << "- To register, choose option 1 and follow the prompts.\n";
    cout << "- To log in, choose option 2 and enter your username and password.\n";
    cout << "- Once logged in, you can:\n";
    cout << "  - View the menu (option 1).\n";
    cout << "  - Select items from the menu (option 2).\n";
    cout << "  - Calculate and print your bill (option 3).\n";
    cout << "  - Log out (option 4).\n";
    cout << "- To exit the program, choose option 5.\n";
    cout << "-------------------------------------\n";
    cout << "Note: Make sure to load the menu and user data from the respective files.\n";
    cout << "=====================================\n";
}

// Function to print the bill and save it to a file
void printAndSaveBill(double total) {
    cout << "Printing Bill..." << endl;
    
    // Print the bill to the console
    cout << "=====================================\n";
    cout << "          Bun Talk Bakery Bill       \n";
    cout << "=====================================\n";
    for (int itemIndex : selectedItems) {
        cout << menu[itemIndex].name << " - $" << fixed << setprecision(2) << menu[itemIndex].price << endl;
    }
    cout << "=====================================\n";
    cout << "Total Bill: $" << fixed << setprecision(2) << total << endl;
    cout << "=====================================\n";

    // Save the bill to a file
    ofstream billFile("bill.txt");
    if (billFile.is_open()) {
        billFile << "=====================================\n";
        billFile << "          Bun Talk Bakery Bill       \n";
        billFile << "=====================================\n";
        for (int itemIndex : selectedItems) {
            billFile << menu[itemIndex].name << " - $" << fixed << setprecision(2) << menu[itemIndex].price << endl;
        }
        billFile << "=====================================\n";
        billFile << "Total Bill: $" << fixed << setprecision(2) << total << endl;
        billFile << "=====================================\n";
        billFile.close();
        cout << "Bill saved to 'bill.txt'." << endl;
    } else {
        cout << "Error: Unable to save the bill." << endl;
    }
}

// Main program
int main() {
    // Load user accounts from a text file (for simplicity)
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        User user;
        while (userFile >> user.username >> user.password) {
            users.push_back(user);
        }
        userFile.close();
    }

    // Load menu items from a text file (for simplicity)
	ifstream menuFile("menu.txt");
	if (menuFile.is_open()) {
    string line;
    while (getline(menuFile, line)) {
        stringstream ss(line);
        MenuItem item;
        if (ss >> item.name >> item.price) {
            menu.push_back(item);
        }
    }
    menuFile.close();
}


    int choice;
    while (true) {
        if (!loggedIn) {
        	cout << "\n";
            cout << "+---------------------------------+\n";
    		cout << "|      Welcome to Bun Talk       |\n";
    		cout << "+---------------------------------+\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Help\n";
            cout << "4. Exit\n";
            cout << "\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline character
            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    displayHelp(); // Display the help section
                    break;
                case 4:
                    cout << "Exiting Bun Talk Bakery Billing System . Goodbye!\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
        else {
        	cout << "\n";
            cout << "1. Display Menu\n";
            cout << "2. Select Items\n";
            cout << "3. Print Bill\n";
            cout << "4. Logout\n";
            cout << "\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline character
            switch (choice) {
                case 1:
                    displayMenu();
                    break;
                case 2:
                    int itemIndex;
                    cout << "Enter the item number to select (0 to stop): ";
                    while (cin >> itemIndex && itemIndex != 0) {
                        if (itemIndex >= 1 && itemIndex <= menu.size()) {
                            selectedItems.push_back(itemIndex - 1);
                        } else {
                            cout << "Invalid item number. Please try again.\n";
                        }
                        cout << "Enter another item number (0 to stop): ";
                    }
                    break;
                case 3:
                    if (selectedItems.empty()) {
                        cout << "No items selected.\n";
                    } else {
                        double total = calculateBill();
                         printAndSaveBill(total); // Print and save the bill
                    }
                    break;
                case 4:
                    loggedIn = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    return 0;
}
