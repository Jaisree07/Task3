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

int parseDate(const std::string &date) {
    int d, m, y;
    char sep;
    std::stringstream ss(date);
    ss >> d >> sep >> m >> sep >> y;
    return y * 10000 + m * 100 + d;
}


void sortData() {
    std::ifstream inFile("sales.csv");
    if (!inFile.is_open()) {
        std::cout << "Error opening sales.csv file" << std::endl;
        return;
    }

    std::vector<std::vector<std::string>> records;
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string field;

        while (std::getline(ss, field, ',')) row.push_back(field);
        if (row.size() == 5) records.push_back(row);
    }
    inFile.close();

    std::sort(records.begin(), records.end(),
              [](const auto& a, const auto& b) {
                  int da = parseDate(a[1]);
                  int db = parseDate(b[1]);
                  return da < db;
              });

    std::ofstream outFile("temp.csv", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cout << "Error creating temp.csv file." << std::endl;
        return;
    }

    for (const auto& row : records) {
        outFile << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "\n";
    }

    std::cout << "Data sorted by date and saved to temp.csv successfully." << std::endl;
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


