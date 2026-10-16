```cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
    Product* next;
};

Product* head = nullptr;

// Find a product using its ID
Product* findProduct(int id) {
    Product* temp = head;

    while (temp != nullptr) {
        if (temp->id == id)
            return temp;

        temp = temp->next;
    }

    return nullptr;
}

// Add a new product
void addProduct() {
    Product* p = new Product;

    cout << "Enter Product ID: ";
    cin >> p->id;

    if (findProduct(p->id) != nullptr) {
        cout << "Product ID already exists!\n";
        delete p;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Product Name: ";
    getline(cin, p->name);

    cout << "Enter Price: ";
    cin >> p->price;

    cout << "Enter Quantity: ";
    cin >> p->quantity;

    if (p->price < 0 || p->quantity < 0) {
        cout << "Price and quantity cannot be negative!\n";
        delete p;
        return;
    }

    p->next = nullptr;

    if (head == nullptr) {
        head = p;
    } else {
        Product* temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = p;
    }

    cout << "Product added successfully!\n";
}

// Display all products
void displayProducts() {
    if (head == nullptr) {
        cout << "Inventory is empty!\n";
        return;
    }

    cout << "\n--------------- INVENTORY ---------------\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Quantity" << '\n';

    Product* temp = head;

    while (temp != nullptr) {
        cout << left << setw(10) << temp->id
             << setw(20) << temp->name
             << setw(12) << fixed << setprecision(2)
             << temp->price
             << setw(10) << temp->quantity << '\n';

        temp = temp->next;
    }
}

// Search for a product
void searchProduct() {
    int id;

    cout << "Enter Product ID to search: ";
    cin >> id;

    Product* p = findProduct(id);

    if (p == nullptr) {
        cout << "Product not found!\n";
        return;
    }

    cout << "\nProduct Found!\n";
    cout << "ID       : " << p->id << '\n';
    cout << "Name     : " << p->name << '\n';
    cout << "Price    : " << p->price << '\n';
    cout << "Quantity : " << p->quantity << '\n';
}

// Update product stock
void updateStock() {
    int id, quantity;

    cout << "Enter Product ID: ";
    cin >> id;

    Product* p = findProduct(id);

    if (p == nullptr) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Current Quantity: " << p->quantity << '\n';
    cout << "Enter New Quantity: ";
    cin >> quantity;

    if (quantity < 0) {
        cout << "Quantity cannot be negative!\n";
        return;
    }

    p->quantity = quantity;

    cout << "Stock updated successfully!\n";
}

// Generate customer bill
void generateBill() {
    int id, quantity;
    double total = 0;
    char choice;

    if (head == nullptr) {
        cout << "Inventory is empty!\n";
        return;
    }

    cout << "\n========== CUSTOMER BILL ==========\n";

    do {
        cout << "\nEnter Product ID: ";
        cin >> id;

        Product* p = findProduct(id);

        if (p == nullptr) {
            cout << "Product not found!\n";
        } else {
            cout << "Product: " << p->name << '\n';
            cout << "Price: Rs. " << p->price << '\n';
            cout << "Available Stock: "
                 << p->quantity << '\n';

            cout << "Enter Quantity: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "Enter a valid quantity!\n";
            } else if (quantity > p->quantity) {
                cout << "Insufficient stock!\n";
            } else {
                double amount = p->price * quantity;

                p->quantity -= quantity;
                total += amount;

                cout << p->name << " x " << quantity
                     << " = Rs. " << fixed
                     << setprecision(2) << amount << '\n';
            }
        }

        cout << "Add another product? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n===================================\n";
    cout << "TOTAL BILL: Rs. "
         << fixed << setprecision(2) << total << '\n';
    cout << "===================================\n";
}

// Free dynamically allocated memory
void cleanup() {
    while (head != nullptr) {
        Product* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " SHOP INVENTORY & BILLING SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Stock\n";
        cout << "5. Generate Bill\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateStock();
                break;

            case 5:
                generateBill();
                break;

            case 6:
                cleanup();
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
```
