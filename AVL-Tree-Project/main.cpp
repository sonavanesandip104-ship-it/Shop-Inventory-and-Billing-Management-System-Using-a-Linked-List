#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Product {
int id;
string name;
double price;
};

struct Node {
Product product;
Node* left;
Node* right;
int height;

Node(Product p) {
    product = p;
    left = nullptr;
    right = nullptr;
    height = 1;
}

};

int getHeight(Node* node) {
if (node == nullptr)
return 0;

return node->height;

}

int getBalance(Node* node) {
if (node == nullptr)
return 0;
return getHeight(node->left) - getHeight(node->right);


}

Node* rightRotate(Node* y) {
Node* x = y->left;
Node* T2 = x->right;


x->right = y;
y->left = T2;

y->height = 1 + max(getHeight(y->left),
                    getHeight(y->right));

x->height = 1 + max(getHeight(x->left),
                    getHeight(x->right));

return x;


}

Node* leftRotate(Node* x) {
Node* y = x->right;
Node* T2 = y->left;


y->left = x;
x->right = T2;

x->height = 1 + max(getHeight(x->left),
                    getHeight(x->right));

y->height = 1 + max(getHeight(y->left),
                    getHeight(y->right));

return y;


}

Node* insertProduct(Node* root, Product p) {
if (root == nullptr)
return new Node(p);

if (p.price < root->product.price) {
    root->left = insertProduct(root->left, p);
}
else if (p.price > root->product.price) {
    root->right = insertProduct(root->right, p);
}
else {
    cout << "A product with this price already exists.\n";
    cout << "This version uses unique prices as AVL keys.\n";
    return root;
}

root->height = 1 + max(getHeight(root->left),
                       getHeight(root->right));

int balance = getBalance(root);

// Left-Left Case
if (balance > 1 &&
    p.price < root->left->product.price) {
    return rightRotate(root);
}

// Right-Right Case
if (balance < -1 &&
    p.price > root->right->product.price) {
    return leftRotate(root);
}

// Left-Right Case
if (balance > 1 &&
    p.price > root->left->product.price) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
}

// Right-Left Case
if (balance < -1 &&
    p.price < root->right->product.price) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
}

return root;


}

void displayProducts(Node* root) {
if (root == nullptr)
return;


displayProducts(root->left);

cout << left << setw(10) << root->product.id
     << setw(25) << root->product.name
     << "Rs. " << fixed << setprecision(2)
     << root->product.price << '\n';

displayProducts(root->right);


}

void searchPriceRange(Node* root, double minPrice,
double maxPrice, int& count) {
if (root == nullptr)
return;


if (root->product.price > minPrice) {
    searchPriceRange(root->left, minPrice,
                     maxPrice, count);
}

if (root->product.price >= minPrice &&
    root->product.price <= maxPrice) {
    cout << left << setw(10) << root->product.id
         << setw(25) << root->product.name
         << "Rs. " << fixed << setprecision(2)
         << root->product.price << '\n';

    count++;
}

if (root->product.price < maxPrice) {
    searchPriceRange(root->right, minPrice,
                     maxPrice, count);
}


}

int main() {
Node* root = nullptr;
int choice;
int nextId = 1;


do {
    cout << "\n====================================\n";
    cout << " ONLINE SHOPPING APPLICATION\n";
    cout << "        USING AVL TREE\n";
    cout << "====================================\n";
    cout << "1. Add Product\n";
    cout << "2. Display All Products\n";
    cout << "3. Search Products by Price Range\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";

    if (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
    }

    if (choice == 1) {
        Product p;

        p.id = nextId++;

        cout << "Enter Product Name: ";
        getline(cin >> ws, p.name);

        cout << "Enter Product Price: ";

        if (!(cin >> p.price) || p.price < 0) {
            cout << "Invalid price. Product not added.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            nextId--;
            continue;
        }

        root = insertProduct(root, p);
    }
    else if (choice == 2) {
        if (root == nullptr) {
            cout << "No products available.\n";
        }
        else {
            cout << "\n--- Product Inventory ---\n";
            cout << left << setw(10) << "ID"
                 << setw(25) << "Product Name"
                 << "Price\n";

            cout << "---------------------------------------------\n";
            displayProducts(root);
        }
    }
    else if (choice == 3) {
        double minPrice, maxPrice;

        cout << "Enter Minimum Price: ";

        if (!(cin >> minPrice)) {
            cout << "Invalid minimum price.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cout << "Enter Maximum Price: ";

        if (!(cin >> maxPrice)) {
            cout << "Invalid maximum price.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (minPrice < 0 || maxPrice < minPrice) {
            cout << "Invalid price range.\n";
            continue;
        }

        cout << "\n--- Products in Price Range ---\n";
        cout << left << setw(10) << "ID"
             << setw(25) << "Product Name"
             << "Price\n";

        int count = 0;

        searchPriceRange(root, minPrice, maxPrice, count);

        if (count == 0) {
            cout << "No products found in this price range.\n";
        }
        else {
            cout << "Total matching products: " << count << '\n';
        }
    }
    else if (choice == 4) {
        cout << "Thank you for using the application!\n";
    }
    else {
        cout << "Invalid choice. Please try again.\n";
    }

} while (choice != 4);


}


