/**
* Създайте програма, която чете и съхранява данни от CSV файловете
 * "Products.csv", "Orders.csv" и "Stock.csv".
 * Програмата трябва да използва функциите:
 * "getOrders()", "getProducts()", "getStocks()" за обработка на данните.
 * Трябва да се проверява дали количествата на продуктите са достатъчни
 * за изпълнение на всички поръчки.
 * Ако количествата не достигат, трябва да се създаде файл "orderForSeller.txt",
 * който да съдържа ясен текст с необходимите продукти за поръчка.
 * В склада всеки продукт трябва да има минимално количество 3.
 **/


#include <iostream>
#include <fstream>

using namespace std;
struct Order {
    int OrderID;
    string CustomerName;
    int ProductID;
    int Qty;
};
struct Products {
    int ProductID;
    string ProductName;
    double PriceForBuyer;
    double PriceForSeller;
};
struct Stock {
    int ProductID;
    int Qty;
};
struct CalculateProductsQty {
    int ProductID;
    int QtyToSell;
    int QtyOnStock;
    int QtyToBuy;
};
bool getOrders(Order o[], int size) {
    ifstream order("Orders.csv");
    if (!order.is_open()) {
        cerr << "404! File 'Orders.csv' is not founds!";
        return false;
    }
    string line;
    int i = 0;
    getline(order,line);
    while(getline(order,line)) {
        string fields[4];
        int index = 0;
        for (char c : line) {
            if (c == ',') index++;
            else fields[index] += c;
        }
        if (index == 3 && i < size) {
            o[i].OrderID = stoi(fields[0]);
            o[i].CustomerName = fields[1];
            o[i].ProductID = stoi(fields[2]);
            o[i].Qty = stoi(fields[3]);
            i++;
        }
    }

    order.close();
    return true;
}
bool getProducts(Products p[], int size) {
    ifstream product("Products.csv");
    if (!product.is_open()) {
        cerr << "404! File 'Products.csv' is not founds!";
        return false;
    }
    string line;
    int i = 0;
    getline(product,line);
    while(getline(product,line)) {
        string fields[4];
        int index = 0;
        for (char c : line) {
            if (c == ',') index++;
             else fields[index] += c;
        }
        if (index == 3 && i < size) {
            p[i].ProductID = stoi(fields[0]);
            p[i].ProductName = fields[1];
            p[i].PriceForBuyer = stoi(fields[2]);
            p[i].PriceForSeller = stoi(fields[3]);
            i++;
        }
    }
    product.close();
    return true;
}
bool getStocks(Stock s[], int size) {
    ifstream stock("Stock.csv");
    if (!stock.is_open()) {
        cerr << "404! File 'Stock.csv' is not founds!";
        return false;
    }
    string line;
    int i = 0;
    getline(stock,line);
    while(getline(stock,line)) {
        string fields[2];
        int index = 0;
        for (char c : line) {
            if (c == ',') index++;
            else fields[index] += c;
        }

        if (index == 1 && i < size) {
            s[i].ProductID = stoi(fields[0]);
            s[i].Qty = stoi(fields[1]);
            i++;
        }
    }

    stock.close();
    return true;
}

void calculateProdictsQ(CalculateProductsQty cp[], int size, Order o[], int sizeO, Products p[], int sizeP, Stock s[], int sizeS) {
    for (int i = 0; i < size; i++) {
        cp[i].ProductID = p[i].ProductID;
        cp[i].QtyToSell = 0;
        cp[i].QtyOnStock = 0;
        cp[i].QtyToBuy = 0;
        for (int j = 0; j < sizeO;j++ ) {
            if (cp[i].ProductID == o[j].ProductID) {
                cp[i].QtyToSell += o[j].Qty;
            }
        }
        for (int j = 0; j < sizeS;j++ ) {
            if (cp[i].ProductID == s[j].ProductID) {
                cp[i].QtyOnStock += s[j].Qty;
            }
        }
        cp[i].QtyToBuy = (cp[i].QtyToSell - cp[i].QtyOnStock) + 3;
    }
}

void createOrderToSeller(CalculateProductsQty cp[], int size, Products p[]) {
    ofstream file("orderForSeller.txt");
    if (!file.is_open()) {
        cerr << "404! File 'orderForSeller.txt' is not found!";
    }
    file << "Products needed to purches are: " << endl;
    int j = 1;
    for (int i = 0; i < size; i++) {
        if (cp[i].QtyToBuy > 0) {
            file << j << ". Name of product: " << p[i].ProductName << ", needed quantity: " << cp[i].QtyToBuy << endl;
            j++;
        }
    }
    cout << "Created order to buyer!";
    file.close();
}
int main() {


    //Creating arrays with objects
    int sizeOrders = 100;
    int sizeProducts = 100;
    int sizeStocks = 100;
    int sizeOfCalculateProducts = 100;
    Order orders[sizeOrders];
    Products products[sizeProducts];
    Stock stocks[sizeStocks];
    CalculateProductsQty calculateProdicts[sizeOfCalculateProducts];
    if (!getOrders(orders,sizeOrders)) return 1;
    if (!getProducts(products,sizeProducts)) return 1;
    if (!getStocks(stocks,sizeStocks)) return 1;

    calculateProdictsQ(calculateProdicts,sizeOfCalculateProducts, orders, sizeOrders, products, sizeProducts, stocks,sizeStocks);
    createOrderToSeller(calculateProdicts,sizeOfCalculateProducts, products);


}