

#include<iostream>
#include <fstream>
#include <string>
#include<windows.h>
#include<conio.h>
using namespace std;

// structure of account holder
struct account {
    string name, accNo, gender, dob, email;
    string accountType, branch, openDate;
    int balance, pin;

    // ATM related (instead of attendance/workingHours)
    int transactions;
    int dailyLimit;
    int withdrawLimit;

    string address, contact;
};

account list[100];
int total = 0;


void saveToFile() {
    ofstream fout("atm_data.txt");
    for (int i = 0; i < total; i++) {
        fout << list[i].name << " " << list[i].accNo << " " << list[i].gender << " "
             << list[i].dob << " " << list[i].email << " "
             << list[i].accountType << " " << list[i].branch << " " << list[i].openDate << " "
             << list[i].balance << " " << list[i].pin << " "
             << list[i].transactions << " " << list[i].dailyLimit << " " << list[i].withdrawLimit << " "
             << list[i].address << " " << list[i].contact << "\n";
    }
    fout.close();
}


void loadFromFile() {
    ifstream fin("atm_data.txt");
    total = 0;
    while (fin >> list[total].name >> list[total].accNo >> list[total].gender
               >> list[total].dob >> list[total].email
               >> list[total].accountType >> list[total].branch >> list[total].openDate
               >> list[total].balance >> list[total].pin
               >> list[total].transactions >> list[total].dailyLimit >> list[total].withdrawLimit
               >> list[total].address >> list[total].contact) {
        total++;
    }
    fin.close();
}


void  accountdata() {
    int choice;
    cout << "How many accounts do you want to enter? ";
    cin >> choice;
    cin.ignore(); // buffer clear

    for (int i = total; i < total + choice; i++) {
        cout << "\n\n ======= Enter data for Account ========= " << i + 1 << " =====" << endl;

        cout << "Account Holder Name : ";
        getline(cin, list[i].name);
        cout << "Account Number : ";
        getline(cin, list[i].accNo);
        cout << "Gender : ";
        getline(cin, list[i].gender);

        cout << "Date of Birth (DD/MM/YYYY): ";
        getline(cin, list[i].dob);
        cout << "Email ID : ";
        getline(cin, list[i].email);
        cout << "Account Type (Saving/Current) : ";
        getline(cin, list[i].accountType);
        cout << "Branch : ";
        getline(cin, list[i].branch);

        cout << "Account Open Date : ";
        getline(cin, list[i].openDate);

        cout << "Balance : ";
        cin >> list[i].balance;

        cout << "PIN (4 digit) : ";
        cin >> list[i].pin;

        cout << "Transactions : ";
        cin >> list[i].transactions;

        cout << "Daily Limit : ";
        cin >> list[i].dailyLimit;

        cout << "Withdraw Limit : ";
        cin >> list[i].withdrawLimit;

        cin.ignore(); // buffer clear

        cout << "Address : ";
        getline(cin, list[i].address);

        cout << "Contact : ";
        getline(cin, list[i].contact);
    }
    total += choice;
    saveToFile();
}




void show() {
    if (total != 0) {
        for (int i = 0; i < total; i++) {
            cout << "\n ===== Data of Account " << i + 1 << " =====" << endl;
            cout << "Name : " << list[i].name << endl;
            cout << "Account No : " << list[i].accNo << endl;
            cout << "Gender : " << list[i].gender << endl;
            cout << "DOB : " << list[i].dob << endl;
            cout << "Email : " << list[i].email << endl;

            cout << "Account Type : " << list[i].accountType << endl;
            cout << "Branch : " << list[i].branch << endl;
            cout << "Open Date : " << list[i].openDate << endl;

            cout << "Balance : " << list[i].balance << endl;
            cout << "PIN : " << list[i].pin << endl;

            cout << "Transactions : " << list[i].transactions << endl;
            cout << "Daily Limit : " << list[i].dailyLimit << endl;
            cout << "Withdraw Limit : " << list[i].withdrawLimit << endl;

            cout << "Address : " << list[i].address << endl;
            cout << "Contact : " << list[i].contact << endl;
        }
    } else {
        cout << "No account records available....!" << endl;
    }
}


void search() {
    if (total != 0) {
        string accNo;
        cout << "Enter Account Number to search : ";
        cin >> accNo;
        for (int i = 0; i < total; i++) {
            if (accNo == list[i].accNo) {
                cout << "\n========= Record found for=========== " << list[i].name << endl;
                cout << "Account No : " << list[i].accNo << endl;
                cout << "Account Type : " << list[i].accountType << endl;
                cout << "Balance : " << list[i].balance << endl;
                return;
            }
        }
        cout << "No such account found!" << endl;
    } else {
        cout << "Record is empty!" << endl;
    }
}
 
void update() {
    if (total != 0) {
        string accNo;
        cout << "Enter Account Number to update : ";
        cin >> accNo;
        for (int i = 0; i < total; i++) {
            if (accNo == list[i].accNo) {
                cout << "\n Previous Data for " << list[i].name << endl;
                cout << "Balance : " << list[i].balance << endl;

                cout << "\n Enter new data :" << endl;
                cout << "Name : ";
                 cin >> list[i].name;
                cout << "Balance : "; 
                cin >> list[i].balance;

                saveToFile();
                return;
            }
        }
        cout << "No such account found !" << endl;
    } else {
        cout << "Record is empty........!" << endl;
    }
}


void del() {
    if (total != 0) {
        char user;
        cout << "Press 1 to delete full record :" << endl;
        cout << "Press 2 to delete specific record :" << endl;
        user = getch();
        if (user == '1') {
            total = 0;
            saveToFile();
            cout << "All records deleted." << endl;
        } else if (user == '2') {
            string accNo;
            cout << "Enter Account Number to delete : ";
            cin >> accNo;
            for (int i = 0; i < total; i++) {
                if (accNo == list[i].accNo) {
                    for (int j = i; j < total - 1; j++) {
                        list[j] = list[j + 1];
                    }
                    total--;
                    saveToFile();
                    cout << "Record deleted........." << endl;
                    return;
                }
            }
            cout << "Account not found." << endl;
        }
    } else {
        cout << "Record is empty .....!" << endl;
    }
}


int main() {
    loadFromFile();

    cout << "\n\n\n\t =============ATM Management System=============== ";
    cout << "\n\n\n\t Sign up " << endl;
    string username, password;
    cout << " Enter username : ";
     cin >> username;
    cout << " Enter password : "; 
    cin >> password;

    cout << " Creating ID please wait ";
    for (int i = 0; i < 8; i++) { cout << ". "; Sleep(200); }
    cout << " \n ID created successfully!" << endl;
    system("cls");

Start:
    system("CLS");
    cout << "\n\n\n\t============ Login===============" << endl;
    string username1, password1;
    cout << " username : "; cin >> username1;
    cout << " password : "; cin >> password1;
    if (username1 == username && password1 == password) {
        cout << "\n Login Successful!\n";
        system("CLS");
        char user;
        while (1) {
            cout << "\n\n Press 1 to enter account data " << endl;
            cout << " Press 2 to show account data " << endl;
            cout << " Press 3 to search account " << endl;
            cout << " Press 4 to update account " << endl;
            cout << " Press 5 to delete account " << endl;
            cout << " Press 6 to logout " << endl;
            cout << " Press 7 to exit " << endl;

            user = getch();
            system("CLS");
            switch (user) {
                case '1': 
                accountdata();
                 break;
                case '2': 
                show();
                 break;
                case '3':
                 search(); 
                 break;
                case '4':
                 update(); 
                 break;
                case '5': 
                del(); 
                break;
                case '6': 
                goto Start;
                case '7':
                 exit(0);
                default: cout << " Invalid input " << endl; break;
            }
        }
    } else {
        cout << "\n\n\t Username or Password incorrect. " << endl;
        Sleep(1000);
        goto Start;
    }
}
