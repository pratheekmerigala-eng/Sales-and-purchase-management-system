# Sales-and-purchase-management-system
# Sales & Product Management System

## Functional Requirements
- Manage a list of products with unique IDs, names, prices, and stock quantities.
- Add new products to the inventory.
- View all products with their current stock, units sold, and revenue.
- Update the stock quantity of existing products.
- Record sales, updating stock, units sold, and total revenue accordingly.
- Search for products by their ID and display detailed information.
- Save all product data to a file and load it on program start to persist information.

## Features
- Command-line interface with a simple menu for easy navigation.
- Persistent data storage in a text file (`products.txt`) for product details and sales history.
- Stock management to update inventory quantities.
- Sales recording with automatic calculation of revenue per product and total revenue.
- Search function for quick lookup of products by ID.
- Input validation for basic error handling (e.g., unique product IDs, positive sale quantities).
- Supports up to 100 products.

## How to Run the Project
1. Save the provided C code in a file named `main.c`.
2. Open a terminal or command prompt in the directory containing `main.c`.
3. Compile the program using GCC:
   - On Linux/macOS:
     ```
     gcc main.c -o inventory
     ```
   - On Windows (with MinGW or similar):
     ```
     gcc main.c -o inventory.exe
     ```
4. Run the executable:
   - On Linux/macOS:
     ```
     ./inventory
     ```
   - On Windows:
     ```
     inventory.exe
     ```
5. Use the menu to add products, list products, update stock, record sales, search products, and save & exit.
6. The product data will be saved in `products.txt` automatically on exit and loaded on the next run.

## Screenshots (Console Output Samples)

```
===== Sales & Product Management System =====
1. Add Product
2. List All Products
3. Update Stock
4. Record Sale
5. Search Product by ID
6. Save & Exit
Enter your choice: 2

ID    Name                 Price      Stock      Sold       Revenue   
-------------------------------------------------------------------
1     Pen                  10.50      95         5          52.50     
2     Notebook             25.00      50         10         250.00    

Total revenue (all products): 302.50

Press Enter to continue...

```

```
Enter product ID to sell: 1
Enter quantity to sell: 3
Sale recorded successfully!
Product: Pen
Quantity sold: 3
Total amount: 31.50
```
