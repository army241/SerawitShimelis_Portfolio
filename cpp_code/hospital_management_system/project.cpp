#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;

enum MenuOption {
    ADD_PATIENT = 1, DISPLAY_PATIENTS, SEARCH_PATIENT,
    DELETE_PATIENT, UPDATE_PATIENT, DISCHARGE_PATIENT,
    MANAGE_STAFF, MANAGE_PHARMACY, MANAGE_BILLING, EXIT
};

enum PatientStatus {
    STATUS_DISCHARGED,
    STATUS_ADMITTED
};

enum StaffRole { DOCTOR=1, NURSE, ADMINISTRATOR};

// Global variable to track the logged-in user's permissions
StaffRole currentSessionRole;

enum MedCategory { TABLET = 1, SYRUP, INJECTION};

struct User {
    char username[30];
    char password[30];
    StaffRole role;
};

struct Patient
{
    int id;
    char name[50];
    int age;
    char disease[50];
    char prescribedMedicine[50];
    char doctor[50];
    PatientStatus status;
    int MedsPerDay;
    int prescribedMedID;
};

struct Medicine {
    int medID;
    char name[50];
    MedCategory category;
    int quantity;
    double pricePerUnit;
};


struct Staff {
    int staffID;
    char name[50];
    StaffRole role;
    double salary;
};

struct HospitalRates {
    double roomRate;
    double consultFee;
};

HospitalRates currentRates = {1000.0, 500}; // Default values

// ================= FUNCTION DECLARATIONS =================
void addPatient();
void displayPatients();
void searchPatient();
void deletePatient();
void updatePatient();
bool idExists(int);
void dischargePatient();
int checkStock(int medID, double &price);
void subtractPharmacyStock(int medID, int quantityUsed);
void registerUser();
bool login();
void manageBilling();
void generateBill(int patientID, int days, int selectedMedID);
string getRoleName(StaffRole role);
void staffMenu();
void addStaff();
bool staffIDExists(int id);
void displayStaff();
void updateStaff();
void deleteStaff();
string getCategoryName(MedCategory cat);
void pharmacyMenu();
void addMedicine();
void updateMedicine();
void displayInventory();
void DeleteMedicine();
void menu();

// ================= MAIN =================
int main() {
    // Check if the system has been initialized
    ifstream userFile("users.dat", ios::binary | ios::ate);

    // If file doesn't exist or is empty, this is the FIRST run
    if (!userFile || userFile.tellg() == 0) {
        userFile.close(); // Close the read handle
        cout << "--- FIRST TIME SETUP: INITIALIZE ADMIN ACCOUNT ---\n";
        registerUser();
        cout << "Setup complete! Please log in to continue.\n";
    } else {
        userFile.close();
    }

    // Normal program flow starts here
    if (login()) {
        menu();
    } else {
        cout << "Access Denied. Exiting...\n";
    }

    return 0;
}

// ================= MENU =================
void menu()
{
    int input;
char proceed;
    do
    {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Patient Record\n";
        cout << "2. Display All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Delete Patient Record\n";
        cout << "5. Update Patient Record\n";
        cout << "6. Discharge A patient\n";
        cout << "7. Manage Staff\n";
        cout << "8. Manage Pharmacy\n";
        cout << "9. Manage The Bill\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> input))
        {
            cout << "Invalid input! Enter number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        MenuOption choice = static_cast<MenuOption>(input);

        switch (choice)
        {
        case ADD_PATIENT:
            if (currentSessionRole==DOCTOR)
            {
                addPatient();
            }
            else
            {
                cout<<"Request denied. Only Doctors can perform this activity\n";
            }
            break;
        case DISPLAY_PATIENTS:
            displayPatients();
            break;
        case SEARCH_PATIENT:
            searchPatient();
            break;
        case DELETE_PATIENT:
            if (currentSessionRole==DOCTOR)
            {
                deletePatient();
            }
            else
            {
                cout<<"Request denied. Only Doctors can perform this activity\n";
            }
            break;
        case UPDATE_PATIENT:
            if (currentSessionRole==DOCTOR)
            {
               updatePatient();
            }
            else
            {
                cout<<"Request denied. Only Doctors can perform this activity\n";
            }
            break;
        case DISCHARGE_PATIENT:
            if (currentSessionRole==DOCTOR)
            {
                dischargePatient();
            }
            else
            {
                cout<<"Request denied. Only Doctors can perform this activity\n";
            }
            break;
        case MANAGE_STAFF:
            if (currentSessionRole==ADMINISTRATOR)
            {
                staffMenu();
            }
            else
            {
                cout<<"Request denied. Only Admins can perform this activity\n";
            }
            break;
        case MANAGE_PHARMACY:
            if (currentSessionRole==ADMINISTRATOR)
            {
                pharmacyMenu();
            }
            else
            {
                cout<<"Request denied. Only Admins can perform this activity\n";
            }
            break;
        case MANAGE_BILLING:
            if (currentSessionRole==ADMINISTRATOR)
            {
                manageBilling();
            }
            else
            {
                cout<<"Request denied. Only Admins can perform this activity\n";
            }
            break;
        case EXIT:
            cout << "Exiting...\n";
            exit(0);
            break;
        default:
            cout << "Invalid choice!\n";
        }
        //
        if (input == 10) break;

        while (true) {
            cout << "\nTask finished. Do you want to return to the main menu? (y/n): ";
            cin >> proceed;
            proceed = tolower(proceed);

            if (proceed == 'y' || proceed == 'n') {
                break; // Valid input
            } else {
                cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        if (proceed == 'n') {
            cout << "Exiting program...\n";
           exit(0);
        }

        cin.ignore(1000, '\n'); // Clean buffer
    } while (input != 10);
}

// ================= ADD PATIENT =================
void addPatient() {
    char again;
    double tempPrice;
    int medID;
    do{Patient p;
        ofstream file("hospital.dat", ios::binary | ios::app);

        cout << "\nEnter Patient ID: ";


        while (true)
        {
            if (!(cin >> p.id))
            {
                cout << "Invalid ID! Enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if (idExists(p.id))
            {
                cout << "ID already taken! Enter a different ID: ";
                continue;
            }

            break;  // valid and unique
        }


        cin.ignore();

        cout << "Enter Name: ";
        while (true)
        {
            cin.getline(p.name, 50);
            if (isalpha(p.name[0]))
                break;
            cout << "Invalid name! Enter letters only: ";
        }

        cout << "Enter Age: ";
        while (!(cin >> p.age))
        {
            if (!(cin >> p.age)) {
                cout << "Invalid! Enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }


            if (p.age < 0 || p.age > 130) {
                cout << "Impossible age! Enter 0-130: ";
                continue;
            }

        break;
        }
        cin.ignore();

        cout << "Enter Disease: ";
        while (true)
        {
            cin.getline(p.disease, 50);
            if (isalpha(p.disease[0]))
                break;
            cout << "Invalid disease name! Enter letters: ";
        }

        cout << "Enter prescribed Medicine Name\n";
        while (true)
        {
            cin.getline(p.prescribedMedicine, 50);
            if (isalpha(p.prescribedMedicine[0]))
                break;
            cout << "Invalid Medicine name! Enter letters: ";
        }
        cout << "Enter prescribed Medicine Per Day\n";
        while(!(cin >> p.MedsPerDay)) {
            cout << "Invalid! Enter a number: ";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        p.status=STATUS_ADMITTED;

        while (true) {
            cout << "Enter Prescribed Medicine ID: ";
            cin >> medID;

            int stock = checkStock(medID, tempPrice);

            if (stock == -1) {
                cout << "(!) This Medicine does not exist in stock.\n";
            } else if (stock == 0) {
                cout << "(!) Warning: This medicine is currently OUT OF STOCK.\n";
            } else {
                cout << "--> Medicine Found. Current Stock: " << stock
                     << " units (Price: ETB" << tempPrice << ")\n";
                p.prescribedMedID = medID;
                break; // Valid selection
            }
        }
        cin.ignore();
        cout << "Enter Doctor Name: ";
        while (true)
        {
            cin.getline(p.doctor, 50);
            if (isalpha(p.doctor[0]))
                break;
            cout << "Invalid doctor name! Enter letters: ";
        }
        file.write((char *)&p, sizeof(p));
        file.close();

        cout << "Patient added successfully!\n";

        // Ask to repeat this specific task
        while (true) {
            cout << "Would you like to add another patient? (y/n): ";
            cin >> again;
            again = tolower(again); // Handle 'Y' or 'y'

            if (again == 'y' || again == 'n') {
                cin.ignore(1000, '\n'); // Clean the buffer
                break; // Valid input, exit the "trap" loop
            } else {
                cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No.\n";
                cin.clear();           // Clear any error flags
                cin.ignore(1000, '\n'); // Clear the rest of the invalid line
            }
        }

    } while (again == 'y');
}

// ================= DISPLAY =================
    void displayPatients() {
        Patient p;
        ifstream file("hospital.dat", ios::binary);
        if (!file) { cout << "No records found!\n"; return; }

        cout << "\n" << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Age" << setw(15)<<"Disease" <<setw(15)<< "Status" <<setw(25)<< "Prescribed Medicine" <<setw(25) <<"PrescribedMedID" << setw(25) << "MedsPerDay" <<setw(15) <<"Doctor Name"<<endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        while (file.read((char *)&p, sizeof(p))) {
            cout << left << setw(5) << p.id
                 << setw(15) << p.name
                 << setw(10) << p.age << setw(15)<< p.disease <<  setw(15) << (p.status == STATUS_ADMITTED? "Admitted" : "Discharged") << setw(25) <<p.prescribedMedicine <<setw(25)<< p.prescribedMedID <<setw(25) << p.MedsPerDay <<setw(15) << p.doctor << endl;

        }
        file.close();
    }


// ================= SEARCH =================
void searchPatient()
{
    Patient p;
    int searchId;
    bool found = false;

    ifstream file("hospital.dat", ios::binary);
    if (!file)
    {
        cout << "No records found!\n";
        return;
    }

    cout << "\nEnter Patient ID to search: ";
    while (!(cin >> searchId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(1000, '\n'); // Clear buffer for clean flow

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.id == searchId)
        {
            cout << "\n--- Patient Record Found ---";
            cout << "\nID:       " << p.id
                 << "\nName:     " << p.name
                 << "\nAge:      " << p.age
                 << "\nDisease:  " << p.disease
                 << "\nDoctor:   " << p.doctor
                 << "\nStatus:   " << (p.status == STATUS_ADMITTED? "Admitted" : "Discharged")
                 << "\nPrescribed Medicine: " << p.prescribedMedicine
                 << "\nPrescribedMedID: " << p.prescribedMedID
                 << "\nMedsPerDay: " <<p.MedsPerDay
                 << "\n----------------------------\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Patient ID " << searchId << " not found!\n";

    file.close();
}

// ================= DELETE =================
void deletePatient()
{
    Patient p;
    int deleteId;
    bool found = false;

    ifstream file("hospital.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Patient ID to delete: ";
    while (!(cin >> deleteId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.id != deleteId)
            temp.write((char *)&p, sizeof(p));
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("hospital.dat");
    rename("temp.dat", "hospital.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Patient not found!\n";
}

// ================= UPDATE =================
void updatePatient() {
    Patient p;
    int updateId;
    bool found = false;
    char admissionChoice;
    double tempPrice;
    int medID;

    ifstream file("hospital.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Patient ID to update: ";
    while (!(cin >> updateId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();

    while (file.read((char *)&p, sizeof(p))) {
        if (p.id == updateId)
        {
            found=true;
            cout << "Enter New Name: ";
            while (true)
            {
                cin.getline(p.name, 50);
                if (isalpha(p.name[0]))
                    break;
                cout << "Invalid name! Enter letters: ";
            }

            cout << "Enter New Age: ";
            while (!(cin >> p.age))
            {
                cout << "Invalid age! Enter number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Enter New Disease: ";
            while (true)
            {
                cin.getline(p.disease, 50);
                if (isalpha(p.disease[0]))
                    break;
                cout << "Invalid disease! Enter letters: ";
            }
            cout << "Enter the prescribed Medicine: ";
            while (true)
            {
                cin.getline(p.prescribedMedicine, 50);
                if (isalpha(p.prescribedMedicine[0]))
                    break;
                cout << "Invalid Medicine name! Enter letters: ";
            }
            cout << "Enter prescribed Medicine ID: ";
            while (true)
            {
                cout << "\nEnter Prescribed Medicine ID: ";
                cin >> medID;

                int stock = checkStock(medID, tempPrice);

                if (stock == -1) {
                    cout << "(!) This Medicine ID does not exist in the system. Try again.\n";
                } else if (stock == 0) {
                    cout << "(!) Warning: This medicine is currently OUT OF STOCK.\n";
                } else {
                    cout << "--> Medicine Found. Current Stock: " << stock
                         << " units (Price: ETB" << tempPrice << ")\n";
                    p.prescribedMedID = medID;
                    break; // Valid selection
                }
            }
            cout << "Enter Number of Medicines Prescribed per Day: ";
            while (!(cin >> p.MedsPerDay) || p.MedsPerDay < 0) {
                cout << "Invalid input! Enter a positive number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();
            cout << "Enter New Doctor Name: ";
            while (true)
            {
                cin.getline(p.doctor, 50);
                if (isalpha(p.doctor[0]))
                    break;
                cout << "Invalid doctor name! Enter letters: ";
            }

            while (true)
            {
                cout << "Is the patient currently admitted? (y/n): ";
                cin >> admissionChoice;

                // Convert to lowercase to make checking easier
                admissionChoice = tolower(admissionChoice);

                if (admissionChoice == 'y' || admissionChoice == 'n')
                {
                    p.status = (admissionChoice == 'y') ? STATUS_ADMITTED : STATUS_DISCHARGED;
                    break; // Exit the validation loop
                }
                else
                {
                    cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
                    cin.clear();           // Clear error flags
                    cin.ignore(1000, '\n'); // Discard invalid input
                }
            }
            cin.ignore(); // Final buffer clear for the next iteration
        }
            temp.write((char *)&p, sizeof(p));

    }
        file.close();
        temp.close();

        remove("hospital.dat");
        rename("temp.dat", "hospital.dat");

        if (found)
            cout << "Record updated successfully!\n";
        else
            cout << "Patient not found!\n";
    }
    bool idExists(int id)
    {
        ifstream file("hospital.dat", ios::binary);
        Patient temp;

        while (file.read((char *)&temp, sizeof(temp)))
        {
            if (temp.id ==id)
            {
                file.close();
                return true;   // ID already taken
            }
        }

        file.close();
        return false;          // ID is free
    }
void dischargePatient() {
    Patient p;
    int id, days;
    bool found = false;

    fstream file("hospital.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout<<"Cannot open file!\n";
    }
    cout << "Enter the ID of the patient you want to discharge: ";
    if (!(cin >> id)) {
        cout << "Invalid input! Please enter a numeric ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        file.close();
        return;
    }

    while (file.read((char *)&p, sizeof(p))) {
        if (p.id == id) {
            found = true;
            if (p.status == STATUS_DISCHARGED) {
                cout << "Patient is already discharged!\n";
                break;
            }

            // Update Status
            p.status = STATUS_DISCHARGED;

            // Collect Billing Info
            cout << "How many days was the patient admitted? ";
            while (!(cin >> days) || days < 1) {
                cout << "Invalid input! Enter number of days (min 1): ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            // Write back to file
            file.seekp(-static_cast<int>(sizeof(p)), ios::cur);
            file.write((char *)&p, sizeof(p));

            cout << "\nProcessing discharge for " << p.name << "...\n";

            // ALL BILLING INTEGRATION
            generateBill(id, days,p.prescribedMedID);

            cout << "Patient with ID " << id << " discharged successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Patient ID " << id << " not found.\n";
    }

    file.close();
}

void registerUser() {

        User newUser;
        // Open in append mode to keep existing users
        ofstream file("users.dat", ios::binary | ios::app);

        cout << "\n--- Register Staff Member ---\n";
        cout << "Enter username: ";
        cin >> newUser.username;
        cout << "Enter password: ";
        cin >> newUser.password;
        newUser.role=ADMINISTRATOR;
        file.write((char*)&newUser, sizeof(User));
        file.close();

        cout << "Admin registered successfully!\n";

        // Logic to repeat or exit


}

bool login() {
    User u;
    int inputRoleInt;
    char inputUser[30], inputPass[30];
    const int MAX_ATTEMPTS = 3;

    for (int attempts = 1; attempts <= MAX_ATTEMPTS; attempts++) {
        ifstream file("users.dat", ios::binary);
        bool found = false;

        cout << "\n========== LOGIN PAGE ==========\n";
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        while (true) {
            cout << "Role (1:Doc, 2:Nurse, 3:Admin): ";

            // Check if the input is actually an integer
            if (!(cin >> inputRoleInt)) {
                cout << "Error: Please enter a number.\n";
                cin.clear();
                cin.ignore(1000, '\n'); // Discard the bad text input
                continue;               // Restart the loop
            }

            // Check if the number is within the valid range
            if (inputRoleInt >= 1 && inputRoleInt <= 3) {
                break; // VALID INPUT: Exit the loop
            } else {
                cout << "Invalid choice! Please enter a number between 1 and 3.\n";
            }
        }


        StaffRole selectedRole = static_cast<StaffRole>(inputRoleInt);
        while (file.read((char*)&u, sizeof(u))) {
            if (strcmp(u.username, inputUser) == 0 && strcmp(u.password, inputPass) == 0 && u.role==selectedRole) {
                currentSessionRole = u.role;
                found = true;
                break;
            }
        }
        file.close();

        if (found) {
            cout << "Login Successful!\n";
            return true;
        } else {
            cout << "Invalid credentials!";
            if (attempts < MAX_ATTEMPTS) {
                cout << " Try again.\n";
            }
        }
    }

    cout << "\nToo many failed attempts. System locking down...\n";
    return false;
}
string getRoleName(StaffRole role) {
    switch(role) {
    case DOCTOR:
        return "Doctor";
    case NURSE:
        return "Nurse";
    case ADMINISTRATOR:
        return "Admin";
    default:
        return "invalid";
    }
}

void staffMenu() {
    int choice;
    char proceed;
    do {
        cout << "\n--- STAFF MANAGEMENT SYSTEM ---\n";
        cout << "1. Add New Staff\n";
        cout << "2. Display All Staff\n";
        cout << "3. Update Staff (Salary/Role)\n";
        cout << "4. Delete Staff Record\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1: addStaff(); break;
        case 2: displayStaff(); break;
        case 3: updateStaff(); break;
        case 4: deleteStaff(); break;
        case 5: menu();
            break;
        default: cout << "Invalid choice!\n";
        }
            if (choice == 5) break;

            while (true) {
                cout << "\nTask finished. Do you want to return to the menu? (y/n): ";
                cin >> proceed;
                proceed = tolower(proceed);

                if (proceed == 'y' || proceed == 'n') {
                    break; // Valid input
                } else {
                    cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            if (proceed == 'n') {
                cout << "Returning to Main Menu...\n";
                return;

            }

            cin.ignore(1000, '\n'); // Clean buffer


    } while (choice != 5);
}

void addStaff()
{char again;
    int roleChoice;
   do{
       Staff s;
       User u;
    ofstream stafffile("staff.dat", ios::binary | ios::app);
    ofstream userfile("users.dat", ios::binary | ios::app);
        cout << "\nEnter Staff ID: ";
        while (!(cin >> s.staffID) || staffIDExists(s.staffID)) {
            cout << "Invalid or Duplicate ID! Enter unique number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore(); // Clean buffer
       cout << "Enter Staff Name: ";
       while (true)
       {
           cin.getline(s.name, 50);
           if (isalpha(s.name[0]))
               break;
           cout << "Invalid name! Enter letters only: ";
       }

       cout << "Enter UserName for login: ";
       while (true)
       {
           cin.getline(u.username, 30);
           if (isalpha(u.username[0]))
               break;
           cout << "Invalid name! Enter letters only: ";
       }

       cout << "Enter Staff Password: ";
       cin.getline(u.password, 30);

        cout << "Select Role (1:Doctor, 2:Nurse, 3:Admin): ";
        while (!(cin >> roleChoice) || roleChoice < 1 || roleChoice > 3) {
            cout << "Invalid Role! Choose 1-3: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        s.role = static_cast<StaffRole>(roleChoice);
        u.role = static_cast<StaffRole>(roleChoice);
cin.ignore();
        cout << "Enter Monthly Salary: ";
        cin >> s.salary;

        stafffile.write((char*)&s, sizeof(Staff));
       userfile.write((char*)&u, sizeof(User));
       userfile.close();
        stafffile.close();
        cout << "\nStaff record added successfully!\n";
        while (true) {
            cout << "Would you like to add another Staff? (y/n): ";
            cin >> again;
            again = tolower(again); // Handle 'Y' or 'y'

            if (again == 'y' || again == 'n') {
                cin.ignore(1000, '\n'); // Clean the buffer
                break; // Valid input, exit the "trap" loop
            } else {
                cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No.\n";
                cin.clear();           // Clear any error flags
                cin.ignore(1000, '\n'); // Clear the rest of the invalid line
            }
        }
    }while (again=='y');
}

bool staffIDExists(int id) {
    ifstream file("staff.dat", ios::binary);
    Staff temp;
    if (file.is_open())
    {
        while (file.read((char*)&temp, sizeof(temp))) {
            if (temp.staffID == id) return true;
        }
    }
    else
    {
        cout << "\nNo staff records found!\n";
    }
    return false;
}

void displayStaff() {
    Staff s;
    ifstream file("staff.dat", ios::binary);
    if (!file) { cout << "\nNo staff records found!\n"; return; }

    cout << "\n" << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(15) << "Role" << setw(10) << "Salary" << endl;
    cout << string(60, '-') << endl;

    while (file.read((char*)&s, sizeof(s))) {
        cout << left << setw(10) << s.staffID
             << setw(25) << s.name
             << setw(15) << getRoleName(s.role)
             << "ETB" << fixed << setprecision(2) << s.salary << endl;
    }
    file.close();
}

void updateStaff() {
    int id;
    bool found = false;
    int roleChoice;
    Staff s;
    fstream file("staff.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Staff ID to update: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.staffID == id) {
            found = true;
            cout << "Updating record for: " << s.name << endl;

            cout << "Enter New Salary: ";
            cin >> s.salary;

            cout << "Enter New Role (1:Doctor, 2:Nurse, 3:Admin): ";
            cin >> roleChoice;
            s.role = static_cast<StaffRole>(roleChoice);

            // Move write-pointer back to the start of this specific record
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            file.write((char*)&s, sizeof(s));
            break;
        }
    }

    if (found) cout << "Update successful!\n";
    else cout << "Staff member not found.\n";
    file.close();
}

void deleteStaff() {
    int id;
    bool found = false;
    Staff s;
    ifstream file("staff.dat", ios::binary);
    ofstream temp("temp_staff.dat", ios::binary);

    cout << "\nEnter Staff ID to delete: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.staffID != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();
    remove("staff.dat");
    rename("temp_staff.dat", "staff.dat");

    if (found) cout << "Staff member removed from system.\n";
    else cout << "Staff ID not found.\n";
}

string getCategoryName(MedCategory cat) {
    switch (cat) {
    case TABLET: return "Tablet";
    case SYRUP: return "Syrup";
    case INJECTION: return "Injection";
    default: return "invalid";
    }
}

void addMedicine()
{char again;
    do{ Medicine m;
        ofstream file("pharmacy.dat", ios::binary | ios::app);

        cout << "\n--- Add New Medicine ---" << endl;
        cout << "Enter Medicine ID: ";
        cin >> m.medID;
        cin.ignore();
        cout << "Enter Medicine Name: ";
        cin.getline(m.name, 50);

        int catChoice;
        cout << "Category (1:Tablet, 2:Syrup, 3:Injection): ";
        cin >> catChoice;
        m.category = static_cast<MedCategory>(catChoice);

        cout << "Enter Initial Quantity: ";
        cin >> m.quantity;
        cout << "Enter Price Per Unit: ";
        cin >> m.pricePerUnit;

        file.write((char*)&m, sizeof(Medicine));
        file.close();
        cout << "Medicine added to inventory successfully!\n";

    while (true) {
        cout << "Would you like to add another Medicine? (y/n): ";
        cin >> again;
        again = tolower(again); // Handle 'Y' or 'y'

        if (again == 'y' || again == 'n') {
            cin.ignore(1000, '\n'); // Clean the buffer
            break; // Valid input, exit the "trap" loop
        } else {
            cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No.\n";
            cin.clear();           // Clear any error flags
            cin.ignore(1000, '\n'); // Clear the rest of the invalid line
        }
    }
}while (again=='y');

}

void displayInventory() {
    Medicine m;
    ifstream file("pharmacy.dat", ios::binary);
    if (!file) { cout << "\nInventory is empty!\n"; return; }

    cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name"
         << setw(15) << "Category" << setw(10) << "Stock" << setw(10) << "Price" << endl;
    cout << string(65, '-') << endl;

    while (file.read((char*)&m, sizeof(m))) {
        cout << left << setw(8) << m.medID
             << setw(20) << m.name
             << setw(15) << getCategoryName(m.category)
             << setw(10) << m.quantity
             << "ETB" << fixed << setprecision(2) << m.pricePerUnit << endl;
    }
    file.close();
}

void updateMedicine() {
    int id, choice;
    bool found = false;
    Medicine m;
    fstream file("pharmacy.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Medicine ID to update: ";
    cin >> id;

    while (file.read((char*)&m, sizeof(m))) {
        if (m.medID == id) {
            found = true;
            cout << "1. Update Stock Quantity\n2. Update Price\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                int newStock;
                cout << "Current Stock: " << m.quantity << ". Enter amount to ADD: ";
                cin >> newStock;
                m.quantity += newStock; // Incremental update
            } else {
                cout << "Current Price: " << m.pricePerUnit << ". Enter New Price: ";
                cin >> m.pricePerUnit;
            }

            file.seekp(-static_cast<int>(sizeof(m)), ios::cur);
            file.write((char*)&m, sizeof(m));
            break;
        }
    }
    if (found)
        cout << "Inventory updated!\n";
    else
        cout << "Medicine not found.\n";
    file.close();
}

void pharmacyMenu() {
    int choice;
    char proceed;
    do {
        cout << "\n===== PHARMACY INVENTORY =====\n";
        cout << "1. Add Medicine\n2. View Inventory\n3. Update Stock/Price\n4. Delete Medicine\n5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
        case 1: addMedicine(); break;
        case 2: displayInventory(); break;
        case 3: updateMedicine(); break;
        case 4: DeleteMedicine(); break;
        case 5: menu(); break;
       default: cout << "Invalid choice.\n";
        }
        if (choice == 5) break;

        while (true) {
            cout << "\nTask finished. Do you want to return to the menu? (y/n): ";
            cin >> proceed;
            proceed = tolower(proceed);

            if (proceed == 'y' || proceed == 'n') {
                break; // Valid input
            } else {
                cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        if (proceed == 'n') {
            cout << "Returning to Main Menu..\n";
            return;

        }

        cin.ignore(1000, '\n'); // Clean buffer

    } while (choice != 5);
}

void DeleteMedicine()
{
    int id;
    bool found = false;
    Medicine m;
    ifstream file("pharmacy.dat", ios::binary);
    ofstream temp("temp_pharmacy.dat", ios::binary);

    cout << "\nEnter Medicine ID to delete: ";
    cin >> id;

    while (file.read((char*)&m, sizeof(m))) {
        if (m.medID != id) {
            temp.write((char*)&m, sizeof(m));
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();

    remove("pharmacy.dat");
    rename("temp_pharmacy.dat", "pharmacy.dat");

    if (found) cout << "Medicine deleted successfully!\n";
    else cout << "Medicine not found!\n";
}

void generateBill(int patientID, int days, int selectedMedID) {
    Patient p;
    Medicine m;
    bool patientFound = false;
    bool medFound = false;
    double unitPrice = 0.0;
    int currentStock = 0;
    double totalMedCost;
    double roomTotal;
    double grandTotal;

    // Retrieve Patient Data
    ifstream pFile("hospital.dat", ios::binary);
    while (pFile.read((char*)&p, sizeof(p))) {
        if (p.id == patientID) {
            patientFound = true;
            break;
        }
    }
    pFile.close();

    if (!patientFound) {
        cout << "\n[ERROR] Patient not found. Cannot generate bill.\n";
        return;
    }

    // Retrieve Medicine Data & Verify Stock
    ifstream mFile("pharmacy.dat", ios::binary);
    while (mFile.read((char*)&m, sizeof(m))) {
        if (m.medID == selectedMedID) {
            medFound = true;
            unitPrice = m.pricePerUnit;
            currentStock = m.quantity;
            break;
        }
    }
    mFile.close();

    if (!medFound) {
        cout << "\n[ERROR] Medicine ID " << selectedMedID << " not found in inventory!\n";
        return;
    }

    // Safety Check: Is there enough stock to cover the full stay?
    int totalMedsUsed = days * p.MedsPerDay;

    if (totalMedsUsed > currentStock) {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        cout << "\n[INVENTORY ALERT] STOCK INSUFFICIENT";
        cout << "\nRequired: " << totalMedsUsed << " units";
        cout << "\nAvailable: " << currentStock << " units";
        cout << "\nDischarge blocked until inventory is corrected.";
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        return;
    }

    // Financial Calculations
    ifstream rateFile("rates.dat", ios::binary);
    if (rateFile) {
        HospitalRates loadRates;
        rateFile.read((char*)&loadRates, sizeof(HospitalRates));
        // Only update if the read was successful and file wasn't empty
        if (rateFile.gcount() == sizeof(HospitalRates)) {
            currentRates = loadRates;
        }
        rateFile.close();
    }
    roomTotal = days * currentRates.roomRate;
    totalMedCost = totalMedsUsed * unitPrice;
    grandTotal = roomTotal + currentRates.consultFee + totalMedCost;
    // Display the Final Bill
    cout << "\n==========================================";
    cout << "\n           FINAL HOSPITAL BILL            ";
    cout << "\n==========================================";
    cout << "\nPatient Name:     " << p.name;
    cout << "\nPatient ID:       " << p.id;
    cout << "\nDuration of Stay: " << days << " days";
    cout << "\n------------------------------------------";
    cout << "\nRoom Charges:     ETB" << fixed << setprecision(2) << roomTotal;
    cout << "\nConsultation Fee: ETB" << currentRates.consultFee;
    cout << "\nMedicine Charges: ETB" << totalMedCost;
    cout << "\n  (Med ID: " << selectedMedID << " | " << totalMedsUsed << " units)";
    cout << "\n------------------------------------------";
    cout << "\nGRAND TOTAL:      ETB" << grandTotal;
    cout << "\n==========================================\n";

    // Finalize Transaction
    subtractPharmacyStock(selectedMedID, totalMedsUsed);
    cout << "Patient " << p.id << " has been officially cleared for discharge.\n";
}
void manageBilling() {
    if (currentSessionRole != ADMINISTRATOR) {
        cout << "\n[ACCESS DENIED] Only Administrators can modify service prices.\n";
        return;
    }

    // Try to load existing rates first so we show current data
    ifstream inFile("rates.dat", ios::binary);
    if (inFile) {
        inFile.read((char*)&currentRates, sizeof(HospitalRates));
        inFile.close();
    }

    cout << "\n--- UPDATE SERVICE PRICES ---";
    cout << "\nCurrent Room Rate: ETB " << currentRates.roomRate;
    cout << "\nEnter New Room Rate: ";
    while (!(cin >> currentRates.roomRate)) {
        cout << "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Current Consultation Fee: ETB " << currentRates.consultFee;
    cout << "\nEnter New Fee: ";
    while (!(cin >> currentRates.consultFee)) {
        cout << "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Save the new rates to the file
    ofstream outFile("rates.dat", ios::binary | ios::trunc);
    if (outFile) {
        outFile.write((char*)&currentRates, sizeof(HospitalRates));
        outFile.close();
        cout << "\nPrices updated and saved to system successfully!\n";
    } else {
        cout << "\n[ERROR] Could not save rates to file.\n";
    }
}

int checkStock(int medID, double &price) {
    Medicine m;
    ifstream file("pharmacy.dat", ios::binary);
    if (!file) return -1;

    while (file.read((char*)&m, sizeof(m))) {
        if (m.medID == medID) {
            price = m.pricePerUnit; // Capture price for reference
            file.close();
            return m.quantity;
        }
    }
    file.close();
    return -1;
}

void subtractPharmacyStock(int medID, int quantityUsed) {
    fstream file("pharmacy.dat", ios::binary | ios::in | ios::out);
    Medicine m;
    bool updated = false;

    while (file.read((char*)&m, sizeof(m))) {
        if (m.medID == medID) {
            m.quantity -= quantityUsed; // Deduct units

            // Move pointer back to the start of this specific record
            file.seekp(-static_cast<int>(sizeof(m)), ios::cur);
            file.write((char*)&m, sizeof(m));
            updated = true;
            break;
        }
    }
    file.close();
    if (updated) cout << "Inventory updated: " << quantityUsed << " units deducted.\n";
}
