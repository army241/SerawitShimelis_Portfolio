# 🎯 Number Guessing Game (Java)

## 📌 Overview

This is a simple **Number Guessing Game** written in Java.
The program generates a random number between **1 and 100**, and the player tries to guess it. After each guess, the program gives feedback whether the guess is **too high**, **too low**, or **correct**.

---

## 🚀 Features

* Random number generation between 1 and 100
* User input handling using `Scanner`
* Feedback system (Too high / Too low)
* Counts number of attempts
* Simple and interactive command-line interface

---

## 🛠️ Technologies Used

* Java (JDK 8 or higher)
* `java.util.Scanner`
* `java.util.Random`

---

## ▶️ How to Run

### 1. Compile the program

```bash
javac Main.java
```

### 2. Run the program

```bash
java Main
```

---

## 🎮 How to Play

1. Run the program.
2. Enter your guess when prompted.
3. The program will tell you:

   * **Too low** → Guess a higher number
   * **Too high** → Guess a lower number
   * **Correct** → You win!
4. Keep guessing until you find the correct number.

---

## 📊 Example Output

```
Welcome to the Number Guessing Game!
I'm thinking of a number between 1 and 100.
Can you guess what it is?

Enter your guess: 50
Too low! Try again.

Enter your guess: 75
Too high! Try again.

Enter your guess: 63
Congratulations! You guessed the number in 3 tries.
```

---

## 💡 Possible Improvements

* Add difficulty levels (easy, medium, hard)
* Limit number of attempts
* Add option to replay the game
* Handle invalid input (non-integer values)

---

## 📄 License

This project is open-source and free to use for learning purposes.
