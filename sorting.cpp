#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

struct Transaction {
    string date;
    float amount;
    string description;
    string type;
};

void printTransactions(const vector<Transaction>& data) {
        cout<< left << setw(12) << "Date"
            << setw(20) << "Description"
            << setw(10) << "Amount"
            << setw(10) << "Type" << endl;
        cout<<string(54, '-') << endl;

        for(const auto& t : data) {
            cout << left << setw(12) << t.date
                    <<setw(20) << t.description
                    <<setw(10) << fixed << setprecision(2) << t.amount
                    <<setw(10) << t.type << endl;


        }
        cout << endl;
}

void merge( vector<Transaction>& arr, int left, int mid, int right) {
    vector<Transaction> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<Transaction> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j=0, k=left;
    while (i < L.size() && j < R.size()) {
        if (L[i].amount <= R[j].amount) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while ( i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];

}


void mergeSort(vector<Transaction>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right ) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right); 
}

bool compareDate(const Transaction& a, const Transaction& b) {
    return a.date < b.date;
}

int partition(vector<Transaction>& arr, int low, int high) {
    string pivot = arr[high].date;
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j].date <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(vector<Transaction>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void heapify(vector<Transaction>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1, r = 2* i + 2;

    if ( l < n && arr[l].type > arr[largest].type)
        largest = l;
    if ( r < n && arr[r].type > arr[largest].type)
        largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
}
void heapSort(vector<Transaction>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
vector<Transaction> getSampleTransaction() {
    return {
        {"2025-05-20", 2500.00, "Paycheck", "credit"},
        {"2025-05-21", 1200.00, "Rent",  "debit"},
        {"2025-05-22", 150.00, "Groceries",  "debit"},
        {"2025-05-23", 200.00, "Utilities",  "debit"},
        {"2025-05-24",  45.00, "Dividend", "credit"}
    };

}

// Output menu
int main () {
    vector<Transaction> transactions = getSampleTransaction();
    int choice;

    do {
        cout << "\n--- Financial Transaction Account ---\n";
        cout << "1. View Transactions\n";
        cout << "2. Sort by Amount (the merge sort)\n";
        cout << "3. Sort by Date (the quick sort)\n";
        cout << "4. Sort by Type (the heap sort)\n";
        cout << "5. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                printTransactions(transactions);
                break;
            case 2:
                mergeSort(transactions, 0, transactions.size() - 1);
                cout << "\nSorted by Amount (Merge Sort):\n";
                printTransactions(transactions);
                break;
            case 3:
                quickSort(transactions, 0, transactions.size() - 1);
                cout << "\nSorted by Date (Quick Sort):\n";
                printTransactions(transactions);
                break;
            case 4:
                heapSort(transactions);
                cout << "\nSorted by Type (Heap Sort):\n";
                printTransactions(transactions);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }while (choice != 5);
    return 0;

}
