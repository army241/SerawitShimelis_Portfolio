# 💳 Payment Processing System (Java OOP Demo)

This project demonstrates key **Object-Oriented Programming (OOP)** concepts in Java:

- Method Overloading (Compile-time Polymorphism)
- Method Overriding (Runtime Polymorphism)
- Inheritance
- Dynamic Method Dispatch

---

# 📌 1. Base Class: `Payment`

The `Payment` class acts as a general template for all payment types.

## 🔹 Method Overloading

The class contains three methods with the same name but different parameters:

```java
public void processPayment(double amount)
public void processPayment(double amount, String currency)
public void processPayment(double amount, String currency, String paymentMethod)