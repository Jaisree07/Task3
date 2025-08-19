#include<iostream>
#include<fstream>
#include<sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>   
using namespace std;

int generateRandomSaleID() {
    int min = 0, max = 9999;
    return min + rand() % (max - min + 1);
}

void read() {
    ifstream file("sales.csv");
    if (!file.is_open()) {
        cout << "Error opening sales.csv file" << endl;
        return;
    }
    string line;
    cout << "Sales Records" << endl;
    cout << "SaleID\t\tDate\t\tItem Name\tQuantity\tUnit Price\n";

    while (getline(file, line)) {
        if (line.empty()) 
        continue;
        stringstream ss(line);
        string saleID, date, itemName, quantity, unitPrice;
        getline(ss, saleID, ',');
        getline(ss, date, ',');
        getline(ss, itemName, ',');
        getline(ss, quantity, ',');
        getline(ss, unitPrice, ',');

        cout << saleID << "\t\t" << date << "\t" << itemName << "\t\t"
             << quantity << "\t\t" << unitPrice << endl;
    }

    file.close();
}

void search(){
    cout<<"hiii";
}
void update(){
    cout<<"hiiii";
}
void deletedata(){
    cout<<"delete";
}

void sort(){
    cout<<"hii";
}

void create() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }

    string UnitPricedate, itemName, date;
    int quantity;
    float unitPrice;
    cout << "Enter UnitPriceDate (DD-MM-YYYY): " << endl;
    cin >> date;
    int saleID = generateRandomSaleID();
    cout << "Enter item name: " << endl;
    cin >> ws; 
    getline(cin, itemName);
    cout << "Enter Item quantity: " << endl;
    cin >> quantity;
    cout << "Enter Unit price: " << endl;
    cin >> unitPrice;

    ofstream file("sales.csv", ios::app);
    if (!file) {
        cout << "Error opening sales.csv file" << endl;
        return;
    }
    file << saleID << "," << date << "," << itemName << "," << quantity << "," << unitPrice << "\n";
    if (file.good()) {
        cout << "Data added successfully with Sale ID: " << saleID << endl;
    } else {
        cout << "Error writing data to file" << endl;
    }

    file.close();
}


void crud(){
       cout << "Enter the choice for CRUD to be performed" << endl;
       cout << "1. Create\n2. Read\n3. Update\n4. Sort\n5. Search" << endl;
       int choice;
       cin >> choice;
       switch(choice){
        case 1:
        create();
        break;

        case 2:
        read();
        break;

        case 3:
        update();
        break;

        case 4:
        deletedata();
        break;

        case 5:
        sort();
        break;

        case 6:
        search();
        break;

        default:
        cout << "Invalid so please enter a number between 1 and 5" << endl;
       }
}


int main(){
    cout << "hi";
    crud();
}