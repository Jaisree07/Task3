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

    std::cout << "Data sorted by date and saved to temp.csv successfully" << std::endl;
}


void report() {
    ifstream file("temp.csv");
    if (!file) {
        cout << "Error opening temp.csv" << endl;
        return;
    }

    vector<vector<string>> records;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> row;
        string field;

        while (getline(ss, field, ',')) row.push_back(field);
        if (row.size() == 5) records.push_back(row);
    }
    file.close();

    sort(records.begin(), records.end(), [](const auto& a, const auto& b) {
        return parseDate(a[1]) < parseDate(b[1]);
    });

    ofstream reportFile("report.txt");
    if (!reportFile) {
        cout << "Error creating report.txt" << endl;
        return;
    }

    time_t now = time(0);
    reportFile << "Report.txt\n\n";
    reportFile << "Date: " << ctime(&now) << endl;
    reportFile << "Sales Report : Stationary Items Sold" << endl;
    reportFile << string(100, '-') << "\n";
    reportFile << left << setw(15) << "Date" << setw(12) << "SaleID" << setw(15) << "ItemName"
               << setw(12) << "Quantity" << setw(10) << "Price" << setw(12) << "SalesAmount" << "\n";
    reportFile << string(100, '-') << "\n";

    float grandTotal = 0.0f;
    string currentDate = "";
    float subtotal = 0.0f;

    for (const auto& record : records) {
        string saleID = record[0];
        string date = record[1];
        string itemName = record[2];
        int quantity = stoi(record[3]);
        float price = stof(record[4]);
        float amount = quantity * price;

        if (date != currentDate && !currentDate.empty()) {
            reportFile << string(100, '-') << "\n";
            reportFile << right << setw(89) << "Subtotal for " + currentDate + " is :" 
                       << fixed << setprecision(2) << setw(10) << subtotal << "\n";
            reportFile << string(100, '-') << "\n";
            subtotal = 0;
        }

        currentDate = date;
        subtotal += amount;
        grandTotal += amount;

        reportFile << left << setw(15) << date
                   << setw(12) << saleID
                   << setw(15) << itemName
                   << setw(12) << quantity
                   << setw(10) << fixed << setprecision(2) << price
                   << setw(12) << fixed << setprecision(2) << amount << "\n";
    }

    if (!records.empty()) {
        reportFile << string(100, '-') << "\n";
        reportFile << right << setw(89) << "Subtotal for " + currentDate + " is :" 
                   << fixed << setprecision(2) << setw(10) << subtotal << "\n";
        reportFile << string(100, '-') << "\n";
    }

    reportFile << right << setw(89) << "Grand Total:" 
               << fixed << setprecision(2) << setw(10) << grandTotal << "\n";
    reportFile << string(100, '-') << "\n";

    reportFile.close();
    cout << "Report generated successfully in report.txt\n";
}


