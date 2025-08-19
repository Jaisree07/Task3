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
using namespace std;

void read();

float calculateSubtotal(int quantity, float unitPrice) {
    return quantity * unitPrice;
}
void report() {
    ifstream file("temp.csv");
    if (!file.is_open()) {
        cout << "Error opening temp.csv" << endl;
        return;
    }

    map<string, vector<vector<string>>> salesData;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string saleID, date, itemName, quantityStr, unitPriceStr;

        getline(ss, saleID, ',');
        getline(ss, date, ',');
        getline(ss, itemName, ',');
        getline(ss, quantityStr, ',');
        getline(ss, unitPriceStr, ',');

        vector<string> record = {saleID, itemName, quantityStr, unitPriceStr};
        salesData[date].push_back(record);
    }
    file.close();

    ofstream reportFile("report.txt");
    if (!reportFile.is_open()) {
        cout << "Error creating report.txt" << endl;
        return;
    }

    time_t now = time(0);
    char* dt = ctime(&now);
    reportFile << "Report.txt\n\n";
    reportFile << "c: " << dt << endl;
    reportFile << "Sales Report : Stationary Items Sold\n";
    reportFile << "---------------------------------------------------------------------------------------------------\n";
    reportFile << left << setw(15) << "Date" << setw(12) << "SaleID" << setw(15) << "ItemName"
               << setw(12) << "Quantity" << setw(10) << "Price" << setw(12) << "SalesAmount" << "\n";
    reportFile << "---------------------------------------------------------------------------------------------------\n";

    float grandTotal = 0;

    for (auto& entry : salesData) {
        string date = entry.first;
        float subtotal = 0;

        for (auto& record : entry.second) {
            string saleID = record[0];
            string itemName = record[1];
            int quantity = stoi(record[2]);
            float price = stof(record[3]);
            float amount = quantity * price;
            subtotal += amount;

            reportFile << left << setw(15) << date
                       << setw(12) << saleID
                       << setw(15) << itemName
                       << setw(12) << quantity
                       << setw(10) << price
                       << setw(12) << amount << "\n";
        }

        reportFile << "---------------------------------------------------------------------------------------------------\n";
        reportFile << "Subtotal for " << date << " is :" << subtotal << "\n";
        reportFile << "---------------------------------------------------------------------------------------------------\n";
        grandTotal += subtotal;
    }

    reportFile << "Grand Total:" << grandTotal << "\n";
    reportFile << "---------------------------------------------------------------------------------------------------\n";

    reportFile.close();
    cout << "Report generated successfully in report.txt\n";
}


// void report() {
//     ifstream file("sales.csv");
//     if (!file.is_open()) {
//         cout << "Error opening sales.csv" << endl;
//         return;
//     }

//     // Map to group records by date
//     map<string, vector<vector<string>>> salesData;
//     string line;

//     // Read data and group by date
//     while (getline(file, line)) {
//         if (line.empty()) continue;
//         stringstream ss(line);
//         string saleID, date, itemName, quantityStr, unitPriceStr;

//         getline(ss, saleID, ',');
//         getline(ss, date, ',');
//         getline(ss, itemName, ',');
//         getline(ss, quantityStr, ',');
//         getline(ss, unitPriceStr, ',');

//         vector<string> record = {saleID, itemName, quantityStr, unitPriceStr};
//         salesData[date].push_back(record);
//     }
//     file.close();

//     ofstream reportFile("report.txt");
//     if (!reportFile.is_open()) {
//         cout << "Error creating report.txt" << endl;
//         return;
//     }

//     time_t now = time(0);
//     char* dt = ctime(&now);
//     reportFile << "Report.txt\n\n";
//     reportFile << "c: " << dt << endl;
//     reportFile << "Sales Report : Stationary Items Sold\n";
//     reportFile << "---------------------------------------------------------------------------------------------------\n";
//     reportFile << left << setw(15) << "Date" << setw(12) << "SaleID" << setw(15) << "ItemName"
//                << setw(12) << "Quantity" << setw(10) << "Price" << setw(12) << "SalesAmount" << "\n";
//     reportFile << "---------------------------------------------------------------------------------------------------\n";

//     float grandTotal = 0;

//     for (auto& entry : salesData) {
//         string date = entry.first;
//         float subtotal = 0;

//         for (auto& record : entry.second) {
//             string saleID = record[0];
//             string itemName = record[1];
//             int quantity = stoi(record[2]);
//             float price = stof(record[3]);
//             float amount = quantity * price;
//             subtotal += amount;

//             reportFile << left << setw(15) << date
//                        << setw(12) << saleID
//                        << setw(15) << itemName
//                        << setw(12) << quantity
//                        << setw(10) << price
//                        << setw(12) << amount << "\n";
//         }

//         reportFile << "---------------------------------------------------------------------------------------------------\n";
//         reportFile << "Subtotal for " << date << " is :" << subtotal << "\n";
//         reportFile << "---------------------------------------------------------------------------------------------------\n";
//         grandTotal += subtotal;
//     }

//     reportFile << "Grand Total:" << grandTotal << "\n";
//     reportFile << "---------------------------------------------------------------------------------------------------\n";

//     reportFile.close();
//     cout << "Report generated successfully in report.txt\n";
//}


int generateRandomSaleID() {
    int min = 0, max = 9999;
    return min + rand() % (max - min + 1);
}

void sort() {
    ifstream inFile("sales.csv");
    if (!inFile.is_open()) {
        cout << "Error opening sales.csv file." << endl;
        return;
    }

    vector<vector<string>> records;
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> row;
        string field;

        while (getline(ss, field, ',')) {
            row.push_back(field);
        }

        if (row.size() == 5) {
            records.push_back(row);
        }
    }

    inFile.close();

    sort(records.begin(), records.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[1] < b[1]; 
    });

    ofstream outFile("temp.csv");
    if (!outFile.is_open()) {
        cout << "Error creating temp.csv file." << endl;
        return;
    }

    for (const auto& row : records) {
        outFile << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "\n";
    }

    //outFile.close();
    read();
    cout << "Data sorted by date and saved to temp.csv successfully." << endl;
}

int parseDate(const std::string &date) {
    int d, m, y;
    char sep;
    std::stringstream ss(date);
    ss >> d >> sep >> m >> sep >> y;
    return y * 10000 + m * 100 + d;
}

void sort() {
    std::ifstream inFile("sales.csv");
    if (!inFile.is_open()) {
        std::cout << "Error opening sales.csv file." << std::endl;
        return;
    }

    std::map<int, std::string> db;
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string saleIDStr, rest;
        std::getline(ss, saleIDStr, ',');
        std::getline(ss, rest); // rest: date,itemName,qty,price
        int saleID = std::stoi(saleIDStr);
        db[saleID] = rest;
    }
    inFile.close();

    std::vector<std::pair<int, std::string>> records(db.begin(), db.end());

    std::sort(records.begin(), records.end(),
              [&](auto &a, auto &b) {
                  std::stringstream ssA(a.second), ssB(b.second);
                  std::string dateA, dateB;
                  std::getline(ssA, dateA, ',');
                  std::getline(ssB, dateB, ',');
                  return parseDate(dateA) < parseDate(dateB);
              });

    std::ofstream temp("temp.csv", std::ios::trunc);
    if (!temp.is_open()) {
        std::cout << "Error creating temp.csv file." << std::endl;
        return;
    }

    for (auto &entry : records) {
        temp << entry.first << "," << entry.second << "\n";
    }
    temp.close();

    std::cout << "Data sorted correctly by date and saved into temp.csv\n";
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
       cout << "1. Create\n2. Read\n3. Update\n4. Deletedata\n5. Sort\n6. Search\n7.Report" << endl;
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


int main(){
    crud();
}