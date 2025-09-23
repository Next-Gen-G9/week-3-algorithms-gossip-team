#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include "utils/crud.hpp"

// Use the standard namespace to simplify code
using namespace std;

void showMenu() {
    cout << "\n===== Inventory Management System =====\n";
    cout << "1. Add New Product\n";
    cout << "2. Display All Products\n";
    cout << "3. Search for a Product\n";
    cout << "4. Update Product Details\n";
    cout << "5. Delete Product\n";
    cout << "6. Save and Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Product> inventory;
    int nextProductId = 1;
    const string filename = "inventory.dat"; // Using .dat for binary data is a common convention

    // Load existing data from the file at the start
    loadFromFile(inventory, nextProductId, filename);

    int choice;
    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
        }

        switch (choice) {
            case 1:
                addProduct(inventory, nextProductId);
                break;
            case 2:
                displayAllProducts(inventory);
                break;
            case 3:
                searchProduct(inventory);
                break;
            case 4:
                updateProduct(inventory);
                break;
            case 5:
                deleteProduct(inventory);
                break;
            case 6:
                saveToFile(inventory, filename);
                cout << "Inventory saved. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}