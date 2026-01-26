# 🏦 ATM Management System (Procedural C++)

A robust, console-based **ATM Simulation** that manages bank accounts and transactions through persistent file storage. 

### 🚀 The Challenge
This project was developed after mastering the **C++ Fundamentals** and **File Handling**. It showcases the ability to build a complex system using **Procedural Programming** only. 

The main challenge was managing data (Reading/Updating/Deleting) in text files and maintaining state throughout the application without the use of Object-Oriented Programming (OOP) or advanced databases.

---

## 🛠 Features

- **🔐 Secure Login:** - Validates Account Number and PIN.
  - Limits login attempts (Security feature: 5 failed attempts lockout).
- **💸 Transaction Management:**
  - **Quick Withdraw:** Fixed amounts for faster UX.
  - **Normal Withdraw:** Custom amounts with balance sufficiency checks.
  - **Deposit:** Real-time balance updates.
- **📊 Account Services:** - Check balance instantly.
  - Data persistence: All changes are saved to `Clients.txt` immediately.
- **💻 Clean UI:** Modularized console screens with clear navigation.

---

## 🏗 Built With (The Fundamentals)

Since this project was built **pre-OOP**, it relies on:
- **Structs:** For organizing client data (Account, PIN, Balance, etc.).
- **Vectors:** For in-memory data manipulation before syncing with files.
- **File Handling (`fstream`):** To ensure data isn't lost after closing the program.
- **Pass-by-Reference:** To optimize performance and modify data across functions.
- **String Parsing:** Custom logic to split and process line-based data.

---

## 📂 Project Structure

- `ATM.cpp`: The core engine containing the logic for login, transactions, and file sync.
- `Clients.txt`: The database (Text-based) where all client records are stored.

---

## 🚀 How to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YourUsername/ATM-System-Core-CPP.git](https://github.com/YourUsername/ATM-System-Core-CPP.git)
   ```
2. Ensure Clients.txt is in the same directory as your source code.

3. Compile:
   ```bash
   g++ ATM.cpp -o ATM_System
   ```
4. Run:
   ```bash
   ./ATM_System
   ```
---

👨‍💻 Author
Mohamed Ragheb Mastering the foundations to build better architectures.

---

If you find this procedural implementation helpful, feel free to give it a ⭐!
