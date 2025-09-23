#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include "../model/Product.hpp"


// Use the standard namespace for cout, cin, vector, string, etc.
using namespace std;

// STUDENT INSTRUCTIONS:
// Your task is to fill in the logic for each function below.
// Read the comments in each function to know what it should do.

void addProduct(vector<Product>& products, int& nextId) {
    // INSTRUCTION:
    // 1. Create a new 'Product' object.
    // 2. Assign it a unique ID from 'nextId', then increase 'nextId' by 1.
    // 3. Ask for the product's name. Use `cin.getline(newProduct.name, 50)` to read it.
    // 4. Ask for quantity and price.
    // 5. Add the new product to the 'products' vector.
    Product newProduct;
    newProduct.id = nextId++;
    cin.ignore();
    cout <<"Enter product name: ";
    getline(cin, newProduct.name);

    cout <<"Enter quantity: ";
    cin >> newProduct.quantity;

    cout <<"Enter price: ";
    cin >> newProduct.price;

    products.push_back(newProduct);

}

void displayAllProducts(const vector<Product>& products) {
    // INSTRUCTION:
    // 1. Check if the 'products' vector is empty.
    // 2. If it is, print "Inventory is empty."
    // 3. If not, loop through and print each product's details in a clean table format.
    if (products.empty()) {
        cout <<"Inventory is empty." << endl; 
        return;
    }

    // 2. Print table header
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;

    cout << string(50, '-') << endl;

    // 3. Print product details
    for (const auto& p : products) {
        cout << left << setw(10) << p.id
             << setw(20) << p.name
             << setw(10) << p.quantity
             << fixed << setprecision(2) << setw(10) << p.price
             << endl;
    }
}

void searchProduct(const vector<Product>& products) {
    // INSTRUCTION:
    // 1. Ask the user to search by ID.
    // 2. Find the product with that ID and print its details.
    // 3. If not found, print a "Product not found" message.
    int searchId;
    cout<< "Enter product Id: ";
    cin >> searchId;

    for (const auto& p : products){
        if(p.id == searchId) {
            cout <<"Product is found!";
        }
        else{
            cout <<"Product not found!";
        }
    }
}

void updateProduct(vector<Product>& products) {
    // INSTRUCTION:
    // 1. Ask for the ID of the product to update.
    // 2. Find the product. If not found, print an error.
    // 3. If found, ask for the new quantity and price and update the product in the vector.
    int updateId;
    cout <<"Enter product ID to update: ";
    cin >> updateId;

    bool found = false;
    for (auto& p : products) {
        if (p.id == updateId) {
            cout << "Enter new quantity: ";
            cin >> p.quantity;

            cout << "Enter new price: ";
            cin >> p.price;

            cout << "Product updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found!\n";
    }
    
}

void deleteProduct(vector<Product>& products) {
    // INSTRUCTION:
    // 1. Ask for the ID of the product to delete.
    // 2. Find and remove it from the vector. (Hint: use `products.erase()`).
    // 3. If not found, print an error message.
    int deleteId;
    cout <<"Enter ID of Product to delete: ";
    cin >> deleteId;

    bool found = false;
    for (auto it = products.begin(); it != products.end(); ++it){
        if(it->id == deleteId){
           products.erase(it);
           cout <<"Product with ID " << deleteId << " Delete Succesful!" << endl;
           found = true;
           break;
        }

        if(!found){
            cout <<"Product with ID" << deleteId << "not found!" << endl;
        }
    }
}

void saveToFile(const vector<Product>& products, const string& filename) {
    // INSTRUCTION FOR BINARY FILE:
    // 1. Open the file for writing in binary mode. Example: `ofstream outFile(filename, ios::binary);`
    ofstream outFile(filename, ios::binary);
    // 2. If the file fails to open, print an error and return.
    if (!outFile){
        cout <<"Could not open file!" << endl;
        return;
    }
    // 3. Loop through each product in the 'products' vector.
    for (const auto& product : products) {
        // 4. For each product, write the entire object directly to the file.
        outFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    }
    // 5. Close the file
    outFile.close();
    cout << "Data saved successfully to " << filename << endl;
}

void loadFromFile(vector<Product>& products, int& nextId, const string& filename) {
    // INSTRUCTION FOR BINARY FILE:
    // 1. Open the file for reading in binary mode. 
    ifstream inFile(filename, ios::binary);
    // 2. If the file doesn't open, just return (it might be the first time running).
    if (!inFile){
        return;
    }
    // 3. Create a temporary 'Product' object to read data into.
    Product tempProduct;
    int highestId = 0;
    // 4. Use a while loop to read one Product object at a time from the file until you reach the end.
    while (inFile.read(reinterpret_cast<char*>(&tempProduct), sizeof(Product))){
        products.push_back(tempProduct);

        if (tempProduct.id > highestId) {
            highestId = tempProduct.id;
        }
        nextId = highestId + 1;
        inFile.close();
    }
    // 5. Inside the loop, add the loaded product to the 'products' vector.
    // 6. Keep track of the highest ID you find.
    // 7. After the loop, set 'nextId' to be (the highest ID + 1).
    // 8. Close the file.

}