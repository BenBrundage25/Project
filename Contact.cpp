#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <termios.h>
using namespace std;

class Contact {
private:
    char fName[50], lName[50], address[50], email[50];
    long long phoneNum;

public:
    void createContact() {
        cout <<"Enter their first name: ";
        cin >> fName;

        cout << "Enter their last name: ";
        cin >> lName;
        
        cout << "Enter their phone number: ";
        cin >> phoneNum;

        cout << "Enter address: ";
        cin >> address;

        cout << "Enter email: ";
        cin >> email;
    }   

    void showContact() {
        cout << "Name: " << fName << " " << lName << endl;
        cout << "Phone: " << phoneNum << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
    }

    void writeOnFile() {
        char ch;
        ofstream f1;
        f1.open("CMS.dat", ios::binary | ios::app);
        do {
            createContact();
            f1.write(reinterpret_cast<char*>(this), sizeof(*this));
            cout << "Do you have more data?(y/n): ";
            cin >> ch;
        }while(ch == 'y');

        cout << "Contact has been Successfully Created... ";
        f1.close();
    }

    void readFromFile() {
        ifstream f2;
        f2.open("CMS.dat", ios::binary);

        cout << "\n------------------------------\n";
        cout << "Contact Database";
        cout << "\n------------------------------\n";

        while(!f2.eof()) {
            if (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                showContact();
                cout << "\n------------------------------\n";
            }
        }
        f2.close();
    }

    void searchOnFile() {
        ifstream f3;
        long long phone;
        cout << "Phone number: ";
        cin >> phone;
        f3.open("CMS.dat", ios::binary);

        while (!f3.eof()) {
            if (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (phone == phoneNum) {
                    showContact();
                    return;
                }
            }
        }
        cout << "\n\nNo record found";
        f3.close();
    }

    void deleteFromFile() {
        long long phone;
        int flag = 0;
        ofstream f4;
        ifstream f5;

        f5.open("CMS.dat", ios::binary);
        f4.open("temp.dat", ios::binary);

        cout << "Enter phone no. to delete:: ";
        cin >> phone;

        while (!f5.eof()) {
            if (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (phoneNum != phone) {
                    f4.write(reinterpret_cast<char*>(this), sizeof(*this));
                }
                else flag = 1;
            }
        }
        f5.close();
        f4.close();
        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        if (flag == 1) {
            cout << "\tContact Deleted...";
        }
        else {
            cout << "\tContact Not Found...";
        }
    }

    void editContact() {
        long long phone;
        fstream f6;

        cout << "Edit contact";
        cout << "\n------------------------------\n";
        cout << "Enter the phone number that you would like to edit: ";
        cin >> phone;

        f6.open("CMS.dat", ios::binary|ios::out|ios::in);

        while (!f6.eof()) {
            if (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                if (phone == phoneNum) {
                    createContact(); 

                    int pos = static_cast<int>(-1 * sizeof(*this));
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char*>(this), sizeof(*this));
                    cout << "\n\n\tContact Successfully Updated/...";
                    return;
                }
            }
        }
        cout << "\n\nNo Record Found";
        f6.close();
    }
};

int main() {

    int choice;

    system("clear");

    cout << "\n\n\n\n\n\n\n\n\n\t\t * Welcome to your Contact Database *";
    
    Contact c1;

    while(1) {
        system("clear");
        cout << "\n\nContact Database\n";
        cout << "\nMain Menu";
        cout << "\n------------------------------\n";
        cout << "[1] Add a new Contact\n";
        cout << "[2] List all Contacts\n";
        cout << "[3] Search\n";
        cout << "[4] Delete a Contact\n";
        cout << "[5] Edit an existing Contact\n";
        cout << "[0] Exit";
        cout << "\n------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
            system("clear");
            c1.writeOnFile();
            break;
            
            case 2:
            system("clear");
            c1.readFromFile();
            break;

            case 3:
            system("clear");
            c1.searchOnFile();
            break;

            case 4:
            system("clear");
            c1.deleteFromFile();
            break;

            case 5:
            c1.editContact();
            break;

            case 0:
            system("clear");
            cout << "\n\n\n\t\t\tThank you for using your Contact Database.\n\n";
            exit(0);
            break;

            default:
            cout << "Invalid input.\n";
            break;
        }
    
        int opt;
        cout << "\n\nWould you like to continue?\n[1]Main Menu\n[0]Exit\n";
        cin >> opt;

        if (opt == 0) {
            cout << "\n\n\n\t\t\tThank you for using your Contact Database.\n\n";
            exit(0);
        }
        
    }
    
    return 0;
}