#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define NAME_LEN 50
#define DATA_FILE "products.txt"

typedef struct {
    int id;
    char name[NAME_LEN];
    float price;
    int quantity;      // current stock
    int unitsSold;     // total units sold
    float revenue;     // total revenue from this product
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;
float totalRevenue = 0.0f;

// ---------- Utility Functions ---------- //

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard
    }
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Find product index by ID, return -1 if not found
int findProductIndexById(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------- File Handling ---------- //

// File format (one product per line):
// id|name|price|quantity|unitsSold|revenue
void loadProductsFromFile() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        // No file yet, not an error for first run
        return;
    }

    productCount = 0;
    totalRevenue = 0.0f;

    while (!feof(fp) && productCount < MAX_PRODUCTS) {
        Product p;
        int read = fscanf(
            fp,
            "%d|%49[^|]|%f|%d|%d|%f\n",
            &p.id,
            p.name,
            &p.price,
            &p.quantity,
            &p.unitsSold,
            &p.revenue
        );

        if (read == 6) {
            products[productCount++] = p;
            totalRevenue += p.revenue;
        }
    }

    fclose(fp);
}

void saveProductsToFile() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(
            fp,
            "%d|%s|%.2f|%d|%d|%.2f\n",
            products[i].id,
            products[i].name,
            products[i].price,
            products[i].quantity,
            products[i].unitsSold,
            products[i].revenue
        );
    }

    fclose(fp);
}

// ---------- Core Operations ---------- //

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Cannot add more products. Storage full.\n");
        return;
    }

    Product p;
    printf("Enter product ID: ");
    if (scanf("%d", &p.id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (findProductIndexById(p.id) != -1) {
        printf("Product with ID %d already exists.\n", p.id);
        return;
    }

    printf("Enter product name: ");
    fgets(p.name, NAME_LEN, stdin);
    // remove trailing newline
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter product price: ");
    if (scanf("%f", &p.price) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter initial quantity (stock): ");
    if (scanf("%d", &p.quantity) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    p.unitsSold = 0;
    p.revenue = 0.0f;

    products[productCount++] = p;
    printf("Product added successfully!\n");
}

void listProducts() {
    if (productCount == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Price", "Stock", "Sold", "Revenue");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < productCount; i++) {
        printf("%-5d %-20s %-10.2f %-10d %-10d %-10.2f\n",
               products[i].id,
               products[i].name,
               products[i].price,
               products[i].quantity,
               products[i].unitsSold,
               products[i].revenue);
    }

    printf("\nTotal revenue (all products): %.2f\n", totalRevenue);
}

void updateStock() {
    int id;
    printf("Enter product ID to update stock: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    int index = findProductIndexById(id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Current stock for %s (ID %d): %d\n",
           products[index].name, products[index].id, products[index].quantity);
    printf("Enter new stock quantity: ");

    int newQty;
    if (scanf("%d", &newQty) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    products[index].quantity = newQty;
    printf("Stock updated successfully.\n");
}

void recordSale() {
    int id, qty;
    printf("Enter product ID to sell: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    int index = findProductIndexById(id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Enter quantity to sell: ");
    if (scanf("%d", &qty) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (qty <= 0) {
        printf("Quantity must be positive.\n");
        return;
    }

    if (qty > products[index].quantity) {
        printf("Not enough stock. Available: %d\n", products[index].quantity);
        return;
    }

    float amount = products[index].price * qty;
    products[index].quantity -= qty;
    products[index].unitsSold += qty;
    products[index].revenue += amount;
    totalRevenue += amount;

    printf("Sale recorded successfully!\n");
    printf("Product: %s\n", products[index].name);
    printf("Quantity sold: %d\n", qty);
    printf("Total amount: %.2f\n", amount);
}

void searchProduct() {
    int id;
    printf("Enter product ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    int index = findProductIndexById(id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    Product p = products[index];
    printf("\nProduct Details:\n");
    printf("ID       : %d\n", p.id);
    printf("Name     : %s\n", p.name);
    printf("Price    : %.2f\n", p.price);
    printf("In Stock : %d\n", p.quantity);
    printf("Units Sold: %d\n", p.unitsSold);
    printf("Revenue  : %.2f\n", p.revenue);
}

// ---------- Menu ---------- //

void printMenu() {
    printf("\n===== Sales & Product Management System =====\n");
    printf("1. Add Product\n");
    printf("2. List All Products\n");
    printf("3. Update Stock\n");
    printf("4. Record Sale\n");
    printf("5. Search Product by ID\n");
    printf("6. Save & Exit\n");
    printf("=============================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    loadProductsFromFile();

    while (1) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer(); // clear after reading menu choice

        switch (choice) {
            case 1:
                addProduct();
                pressEnterToContinue();
                break;
            case 2:
                listProducts();
                pressEnterToContinue();
                break;
            case 3:
                updateStock();
                pressEnterToContinue();
                break;
            case 4:
                recordSale();
                pressEnterToContinue();
                break;
            case 5:
                searchProduct();
                pressEnterToContinue();
                break;
            case 6:
                saveProductsToFile();
                printf("Data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}