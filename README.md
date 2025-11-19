# Simple ATM Console Application

A simple C++ console-based ATM application that uses a text file (`Clients.txt`) to store client records. This project demonstrates basic file I/O, struct usage, menu-driven interaction, and simple validation logic — suitable for Advanced learning C++ and console applications.

---

## Features

* Login by **Account Number** and **PIN** (5 attempts limit)
* Quick withdraw with predefined amounts (20, 50, 100, 200, 400, 600, 800, 1000)
* Normal withdraw (must be a multiple of 5 and <= account balance)
* Deposit (must be a positive integer)
* Check balance
* Data persistence using a text file (`Clients.txt`) with a custom separator

---

## Project Structure

* `main.cpp` — Contains the full ATM console application code.
* `Clients.txt` — Data file storing clients; each line represents a client record.

> The project is purposely single-file and minimal to keep it easy to inspect and modify.

---

## Clients File Format (`Clients.txt`)

Each client is stored on a single line using the separator `#//#` with the following fields, in order:

1. AccountNumber (string)
2. PINCode (string)
3. Name (string)
4. Phone (string)
5. AccountBalance (double)

**Example line:**

```
1001#//#1234#//#Mohamed Ragheb Omar#//#0123456789#//#7500.00
```

> Notes:
>
> * The code parses each line using the `#//#` separator. Keep this separator intact.
> * `AccountBalance` is parsed as a `double` using `std::stod`.

---

## Requirements

* Windows OS (tested on Windows 10/11)
* Visual Studio Community 2022 (or any C++ compiler supporting C++11 or later)

---

## Build & Run (Visual Studio Community 2022)

1. Open Visual Studio Community 2022.
2. Create a new **Console App** (C++).
3. Replace the generated `main.cpp` contents with the provided source code.
4. Make sure `Clients.txt` is placed in the same folder as the executable (or project working directory). You can add `Clients.txt` to the project for convenience.
5. Build the project (`Build > Build Solution`) and run (`Debug > Start Without Debugging` or press `Ctrl+F5`).

Alternative CLI compile (Developer Command Prompt):

```
cl /EHsc main.cpp
main.exe
```

---

## How to Use

* Run the program.
* Enter your **Account Number** and **PIN**.
* If credentials are valid you will see the ATM main menu:

  * 1 — Quick Withdraw
  * 2 — Normal Withdraw
  * 3 — Deposit
  * 4 — Check Balance
  * 5 — Logout

### Quick Withdraw

Choose one of the predefined options. The program will ask for confirmation before completing the transaction.

### Normal Withdraw

Enter an amount that is a multiple of 5 and less than or equal to your balance.

### Deposit

Enter a positive amount (integer). Confirm to add to the balance.

---

## Important Implementation Details & Behaviour

* Login attempts are limited to **5**. After that the login fails.
* The application saves client records back to `Clients.txt` after every deposit/withdraw by rewriting the file.
* The application stores PIN codes in plain text in `Clients.txt`. **This is not secure** and shouldn't be used in production.

---

## Suggested Improvements (Nice-to-have)

* Store PINs hashed (e.g. use salted hashing) instead of plain text.
* Implement an admin mode for creating/updating/deleting clients.
* Replace the text-file storage with a lightweight database (SQLite).
* Add input sanitization for names/phones and improved error handling.
* Improve user interface and localization (support multiple languages).

---

## Known Issues / Limitations

* Plain text PIN storage (security risk).
* No concurrency control — simultaneous runs may cause data races when writing the file.
* Phone and name fields are not validated beyond being stored as strings.
* Deleting clients uses `MarkForDelete` but no UI is provided in the current code to set this flag.

---

## Sample `Clients.txt` (3 sample users)

```
1001#//#1234#//#Mohamed Ragheb Omar#//#0123456789#//#7500.00
1002#//#4321#//#Alaa Mahmoud#//#01011112222#//#1500.50
1003#//#9999#//#Sara Ali#//#01122334455#//#250.75
```

---

## Contribution

If you'd like to contribute or suggest features, feel free to open issues or send pull requests. Keep changes focused and document any new functions or data formats.

---

## License

This project is provided under the **MIT License** — feel free to reuse and adapt the code. Include attribution if you plan to publish derivative work.

---

## Author

Mohamed Ragheb Omar

---
