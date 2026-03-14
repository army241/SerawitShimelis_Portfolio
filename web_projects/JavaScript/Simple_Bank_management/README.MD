# Bank Account Management Program

## 📌 Project Overview
The **Bank Account Management Program** is a simple JavaScript project that simulates basic banking operations. It allows users to create a bank account, deposit money, withdraw money, track transactions, and view account history.

This project demonstrates the use of **JavaScript classes, objects, arrays, and methods** to build a structured program.

---

## 🎯 Features

- Create a bank account with an initial balance of **$0**
- Deposit money into the account
- Withdraw money from the account
- Prevent invalid deposits and withdrawals
- Store all transactions in a transaction history
- View the current balance
- List all deposits
- List all withdrawals

---

## 🛠 Technologies Used

- JavaScript (ES6)
- Object-Oriented Programming (OOP)
- Arrays and Objects

---

## 📂 Project Structure

```
Simple_Bank_Management/
│
├── source_code.js
└── README.md
```

---

## ⚙️ How the Program Works

The program defines a **BankAccount class** that manages the account balance and transaction history.

### Main Components

**Constructor**
- Initializes the account balance to `0`
- Creates an empty `transactions` array

**Deposit Method**
- Adds money to the account
- Stores the transaction
- Updates the balance

**Withdraw Method**
- Removes money from the account
- Ensures sufficient balance
- Records the withdrawal

**Check Balance**
- Returns the current account balance

**List Deposits**
- Displays all deposit transactions

**List Withdrawals**
- Displays all withdrawal transactions

---

## 💻 Example Usage

```javascript
const myAccount = new BankAccount();

myAccount.deposit(100);
myAccount.deposit(50);
myAccount.withdraw(20);

console.log(myAccount.checkBalance());
console.log(myAccount.listAllDeposits());
console.log(myAccount.listAllWithdrawals());
```

### Example Output

```
Successfully deposited $100. New balance: $100
Successfully deposited $50. New balance: $150
Successfully withdrew $20. New balance: $130

Current balance: $130
Deposits: 100,50
Withdrawals: 20
```

---

## 📊 Transaction Structure

Each transaction is stored as an object:

```javascript
{
  type: "deposit",
  amount: 100
}
```

or

```javascript
{
  type: "withdraw",
  amount: 50
}
```

---

## 🚀 Learning Goals

This project helps practice:

- JavaScript classes
- Object-oriented programming
- Array methods (`push`, `filter`, `map`)
- Data management with objects
- Writing clean and structured code

---

## ✅ Project Requirements

- Minimum **5 transactions**
- At least **2 deposits**
- At least **2 withdrawals**
- Final balance **greater than $100**

---

## 📄 License

This project is created for educational purposes and is free to use and modify.