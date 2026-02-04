# 🏥 Hospital Management System (C++)

A **console-based Hospital Management System** developed in **C++** using **file handling**, **structures**, **enums**, and **role-based access control**.  
This system manages **patients, staff, pharmacy inventory, billing, and authentication** in a simple but structured way.

---

## 📌 Features Overview

### 🔐 Authentication & Roles
- Secure **login system**
- Role-based access:
  - **Doctor**
  - **Nurse**
  - **Administrator**
- First-time system setup automatically creates an **Admin account**

---

### 👨‍⚕️ Patient Management (Doctor Access)
- Add new patient records
- Display all patients
- Search patient by ID
- Update patient details
- Delete patient records
- Discharge patients with billing integration
- Track:
  - Disease
  - Prescribed medicine
  - Medicine per day
  - Admission status

---

### 👥 Staff Management (Admin Only)
- Add staff members
- Assign roles (Doctor / Nurse / Admin)
- Manage salaries
- Update or delete staff records
- Automatically creates login credentials for staff

---

### 💊 Pharmacy Management (Admin Only)
- Add new medicines
- Categorize medicines:
  - Tablet
  - Syrup
  - Injection
- Update stock quantities
- Update prices
- Delete medicines
- Display full inventory
- Automatic stock deduction during patient discharge

---

### 💰 Billing System (Admin Only)
- Calculates:
  - Room charges (per day)
  - Consultation fee
  - Medicine cost
- Prevents discharge if medicine stock is insufficient
- Generates a detailed final bill
- Customizable hospital rates saved to file

---

## 📂 File Structure

| File Name | Purpose |
|---------|--------|
| `hospital.dat` | Stores patient records |
| `staff.dat` | Stores staff details |
| `users.dat` | Stores login credentials |
| `pharmacy.dat` | Stores medicine inventory |
| `rates.dat` | Stores billing rates |
| `temp.dat` | Temporary file for updates/deletes |

---

## 🧱 Technologies Used

- **Language:** C++
- **Concepts:**
  - File Handling (Binary files)
  - Structures & Enums
  - Role-Based Access Control
  - Input Validation
  - Modular Programming
- **Libraries:**
  - `<iostream>`
  - `<fstream>`
  - `<cstring>`
  - `<cctype>`
  - `<iomanip>`

