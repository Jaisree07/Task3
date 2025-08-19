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
float calculateSubtotal(int quantity, float unitPrice) {
    return quantity * unitPrice;
}
void sortData() {
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