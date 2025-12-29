#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    int age;
    char address[100];
    char phone[15];

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Address: ";
        cin.getline(address, 100);

        cout << "Enter Phone Number: ";
        cin.getline(phone, 15);
    }

    void display() const {
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(6) << age
             << setw(25) << address
             << setw(15) << phone << endl;
    }
};

// Function Prototypes
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    do {
        cout << "\n===== STUDENT DATABASE SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

// View All Students
void viewStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    cout << left << setw(6) << "ID"
         << setw(20) << "Name"
         << setw(6) << "Age"
         << setw(25) << "Address"
         << setw(15) << "Phone\n";
    cout << "--------------------------------------------------------------\n";

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {
    Student s;
    int searchId;
    bool found = false;

    ifstream file("students.dat", ios::binary);

    cout << "Enter Student ID to search: ";
    cin >> searchId;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == searchId) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Update Student
void updateStudent() {
    Student s;
    int updateId;
    bool found = false;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Student ID to update: ";
    cin >> updateId;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == updateId) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));
            found = true;
            cout << "Student record updated successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Delete Student
void deleteStudent() {
    Student s;
    int deleteId;
    bool found = false;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    cout << "Enter Student ID to delete: ";
    cin >> deleteId;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id != deleteId) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found.\n";
}

