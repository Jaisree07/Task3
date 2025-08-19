#include<iostream>
#include<fstream>
#include<sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>   
#include<vector>
#include<algorithm>
#include <map>
#include <iomanip> 
#include "main.h"
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

void search() {
    string searchID;
    cout << "Enter the Sale ID to search: ";
    cin >> searchID;

    ifstream file("sales.csv");
    if (!file.is_open()) {
        cout << "Error opening sales.csv file" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string saleID, date, itemName, quantity, unitPrice;
        getline(ss, saleID, ',');
        getline(ss, date, ',');
        getline(ss, itemName, ',');
        getline(ss, quantity, ',');
        getline(ss, unitPrice, ',');

        if (saleID == searchID) {
            cout << "\nSale Record Found:\n";
            cout << "Sale ID: " << saleID << "\n";
            cout << "Date: " << date << "\n";
            cout << "Item Name: " << itemName << "\n";
            cout << "Quantity: " << quantity << "\n";
            cout << "Unit Price: " << unitPrice << "\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Sale ID not found." << endl;
    }
}


void update() {
    read();

    string updateID;
    cout << "\nEnter the Sale ID to update: ";
    cin >> updateID;

    ifstream inFile("sales.csv");
    ofstream tempFile("temp.csv");

    if (!inFile || !tempFile) {
        cout << "Error opening file" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string saleID, date, itemName, quantity, unitPrice;

        getline(ss, saleID, ',');
        getline(ss, date, ',');
        getline(ss, itemName, ',');
        getline(ss, quantity, ',');
        getline(ss, unitPrice, ',');

        if (saleID == updateID) {
            found = true;

            cout << "\nExisting Data:\n";
            cout << "Date: " << date << "\nItem Name: " << itemName
                 << "\nQuantity: " << quantity << "\nUnit Price: " << unitPrice << endl;

            int option;
            cout << "\nWhat do you want to update?\n";
            cout << "1. Date\n2. Item Name\n3. Quantity\n4. Unit Price\n5. All Fields\n";
            cout << "Enter your choice: ";
            cin >> option;

            switch(option) {
                case 1:
                    cout << "Enter new Date (DD-MM-YYYY): ";
                    cin >> date;
                    break;
                case 2:
                    cout << "Enter new Item Name: ";
                    cin >> ws;
                    getline(cin, itemName);
                    break;
                case 3:
                    cout << "Enter new Quantity: ";
                    cin >> quantity;
                    break;
                case 4:
                    cout << "Enter new Unit Price: ";
                    cin >> unitPrice;
                    break;
                case 5:
                    cout << "Enter new Date (DD-MM-YYYY): ";
                    cin >> date;
                    cout << "Enter new Item Name: ";
                    cin >> ws;
                    getline(cin, itemName);
                    cout << "Enter new Quantity: ";
                    cin >> quantity;
                    cout << "Enter new Unit Price: ";
                    cin >> unitPrice;
                    break;
                default:
                    cout << "Invalid choice. No update made for this record.\n";
            }

            tempFile << saleID << "," << date << "," << itemName << "," << quantity << "," << unitPrice << "\n";
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("sales.csv");
        rename("temp.csv", "sales.csv");
        cout << "\nData updated successfully.\n";
        read();
    } else {
        remove("temp.csv");
        cout << "\nSale ID not found. No updates made.\n";
    }
}



void deletedata() {
    read(); 
    string deleteID;
    cout << "Enter the Sale ID to be deleted: " << endl;
    cin >> deleteID;

    ifstream inFile("sales.csv");
    ofstream tempFile("temp.csv");

    if (!inFile || !tempFile) {
        cout << "Error opening files" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string saleID;
        getline(ss, saleID, ',');

        if (saleID == deleteID) {
            found = true;
            continue;  
        }

        tempFile << line << endl;  
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("sales.csv");
        rename("temp.csv", "sales.csv");
        cout << "Sale ID " << deleteID << " deleted successfully" << endl;
    } else {
        remove("temp.csv");
        cout << "Sale ID not found" <<endl;
    }
    read();
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
      
       while(true){
       cout << "1. Create\n2. Read\n3. Update\n4. Delete\n5. Sort\n6. Search\n7.Report" << endl;
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
        sortData();
        break;

        case 6:
        search();
        break;

        case 7:
        report();
        break;
        
        case 8:
        cout << "Exit" << endl;
        exit(0);

        default:
        cout << "Invalid so please enter a number between 1 and 8" << endl;
       }
}
}