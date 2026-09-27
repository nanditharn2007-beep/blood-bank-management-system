#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
using namespace std;

enum BloodGroup { A_POS, A_NEG, B_POS, B_NEG, AB_POS, AB_NEG, O_POS, O_NEG };

string bloodGroupToString(BloodGroup bg) {
    switch (bg) {
        case A_POS:  return "A+";
        case A_NEG:  return "A-";
        case B_POS:  return "B+";
        case B_NEG:  return "B-";
        case AB_POS: return "AB+";
        case AB_NEG: return "AB-";
        case O_POS:  return "O+";
        case O_NEG:  return "O-";
        default:     return "Unknown";
    }
}

struct Donor {
    int donorID;
    string name;
    int age;
    BloodGroup bloodGroup;
    string contact;
};

vector<Donor> donors;
int inventory[8] = {0, 0, 0, 0, 0, 0, 0, 0};

bool isValidBloodGroup(int bg) {
    return (bg >= 0 && bg <= 7);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void registerDonor() {
    Donor d;
    cout << "\n--- Register New Donor ---\n";
    cout << "Enter Donor ID: ";
    cin >> d.donorID;
    clearInputBuffer();
    cout << "Enter Name: ";
    getline(cin, d.name);
    cout << "Enter Age: ";
    cin >> d.age;
    clearInputBuffer();

    int bg;
    do {
        cout << "Enter Blood Group (0=A+, 1=A-, 2=B+, 3=B-, 4=AB+, 5=AB-, 6=O+, 7=O-): ";
        cin >> bg;
        if (!isValidBloodGroup(bg)) {
            cout << "Invalid blood group! Please enter a number between 0 and 7.\n";
            clearInputBuffer();
        }
    } while (!isValidBloodGroup(bg));

    clearInputBuffer();
    d.bloodGroup = static_cast<BloodGroup>(bg);

    cout << "Enter Contact Number: ";
    getline(cin, d.contact);

    donors.push_back(d);
    cout << "\n✓ Donor registered successfully!\n";
}

void searchDonor(int id) {
    bool found = false;
    for (auto& d : donors) {
        if (d.donorID == id) {
            cout << "\n--- Donor Found ---\n";
            cout << "Donor ID   : " << d.donorID << "\n";
            cout << "Name       : " << d.name << "\n";
            cout << "Age        : " << d.age << "\n";
            cout << "Blood Group: " << bloodGroupToString(d.bloodGroup) << "\n";
            cout << "Contact    : " << d.contact << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n✗ Donor not found!\n";
    }
}

void listAllDonors() {
    if (donors.empty()) {
        cout << "\n✗ No donors registered yet.\n";
        return;
    }

    cout << "\n==== ALL DONORS ====\n";
    for (auto& d : donors) {
        cout << "\nDonor ID   : " << d.donorID;
        cout << "\nName       : " << d.name;
        cout << "\nAge        : " << d.age;
        cout << "\nBlood Group: " << bloodGroupToString(d.bloodGroup);
        cout << "\nContact    : " << d.contact;
        cout << "\n----------------------------\n";
    }
}

void searchByBloodGroup(BloodGroup bg) {
    bool found = false;
    cout << "\n--- Donors with Blood Group " << bloodGroupToString(bg) << " ---\n";

    for (auto& d : donors) {
        if (d.bloodGroup == bg) {
            cout << "\nDonor ID   : " << d.donorID;
            cout << "\nName       : " << d.name;
            cout << "\nAge        : " << d.age;
            cout << "\nContact    : " << d.contact;
            cout << "\n----------------------------\n";
            found = true;
        }
    }
s
    if (!found) {
        cout << "\n✗ No donors found for this blood group.\n";
    }
}

void addBlood(BloodGroup bg, int units) {
    if (units <= 0) {
        cout << "\n✗ Invalid units! Please enter a positive number.\n";
        return;
    }

    inventory[bg] += units;
    cout << "\n✓ " << units << " units of " << bloodGroupToString(bg) << " added successfully.\n";
}

void requestBlood(BloodGroup bg, int units) {
    if (units <= 0) {
        cout << "\n✗ Invalid units! Please enter a positive number.\n";
        return;
    }

    if (inventory[bg] >= units) {
        inventory[bg] -= units;
        cout << "\n✓ " << units << " units of " << bloodGroupToString(bg) << " issued successfully.\n";
    } else {
        cout << "\n✗ Insufficient stock for " << bloodGroupToString(bg) << "!\n";
        cout << "Available units: " << inventory[bg] << "\n";
    }
}

void displayInventory() {
    cout << "\n==== BLOOD INVENTORY ====\n";
    cout << "A+  : " << inventory[0] << " units\n";
    cout << "A-  : " << inventory[1] << " units\n";
    cout << "B+  : " << inventory[2] << " units\n";
    cout << "B-  : " << inventory[3] << " units\n";
    cout << "AB+ : " << inventory[4] << " units\n";
    cout << "AB- : " << inventory[5] << " units\n";
    cout << "O+  : " << inventory[6] << " units\n";
    cout << "O-  : " << inventory[7] << " units\n";
}

int main() {
    int choice;

    do {
        cout << "\n=== BLOOD BANK MANAGEMENT SYSTEM ===\n";
        cout << "1. Register Donor\n";
        cout << "2. Search Donor by ID\n";
        cout << "3. List All Donors\n";
        cout << "4. Search Donors by Blood Group\n";
        cout << "5. Add Blood to Inventory\n";
        cout << "6. Request Blood\n";
        cout << "7. View Blood Inventory\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";

        cin >> choice;
        clearInputBuffer();

        int id, units, bg;

        switch (choice) {
            case 1:
                registerDonor();
                break;

            case 2: {
                cout << "Enter Donor ID: ";
                cin >> id;
                clearInputBuffer();
                searchDonor(id);
                break;
            }

            case 3:
                listAllDonors();
                break;

            case 4: {
                do {
                    cout << "Enter Blood Group (0=A+, 1=A-, 2=B+, 3=B-, 4=AB+, 5=AB-, 6=O+, 7=O-): ";
                    cin >> bg;

                    if (!isValidBloodGroup(bg)) {
                        cout << "Invalid blood group! Please enter a number between 0 and 7.\n";
                        clearInputBuffer();
                    }
                } while (!isValidBloodGroup(bg));

                clearInputBuffer();
                searchByBloodGroup(static_cast<BloodGroup>(bg));
                break;
            }

            case 5: {
                do {
                    cout << "Enter Blood Group (0=A+, 1=A-, 2=B+, 3=B-, 4=AB+, 5=AB-, 6=O+, 7=O-): ";
                    cin >> bg;

                    if (!isValidBloodGroup(bg)) {
                        cout << "Invalid blood group! Please enter a number between 0 and 7.\n";
                        clearInputBuffer();
                    }
                } while (!isValidBloodGroup(bg));

                clearInputBuffer();

                cout << "Units to add: ";
                cin >> units;
                clearInputBuffer();

                addBlood(static_cast<BloodGroup>(bg), units);
                break;
            }

            case 6: {
                do {
                    cout << "Enter Blood Group (0=A+, 1=A-, 2=B+, 3=B-, 4=AB+, 5=AB-, 6=O+, 7=O-): ";
                    cin >> bg;

                    if (!isValidBloodGroup(bg)) {
                        cout << "Invalid blood group! Please enter a number between 0 and 7.\n";
                        clearInputBuffer();
                    }
                } while (!isValidBloodGroup(bg));

                clearInputBuffer();

                cout << "Units needed: ";
                cin >> units;
                clearInputBuffer();

                requestBlood(static_cast<BloodGroup>(bg), units);
                break;
            }

            case 7:
                displayInventory();
                break;

            case 8:
                cout << "\nThank you for using Blood Bank Management System.\n";
                break;

            default:
                cout << "\n✗ Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}