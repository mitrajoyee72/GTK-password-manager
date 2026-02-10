# GTK Password Manager 🔐

A lightweight **desktop password vault** written in **C** using **GTK+ 3**.  
The application provides a simple graphical interface for storing, viewing, searching, and managing credentials locally.

> ⚠️ This project is intended for **educational and learning purposes**.  
> It is **not** designed for production-grade security use.

---

## ✨ Features

- Master password protection  
- Add, view, search, and delete credentials  
- Credentials grouped by service  
- Clean GTK-based graphical user interface  
- Lightweight local storage  
- Simple XOR-based data obfuscation  
- No external dependencies beyond GTK and GLib  

---

## 🛠 Technologies Used

- **C (GCC)**
- **GTK+ 3**
- **GLib**
- **pkg-config**

---


---

## 🚀 Build & Run

### Requirements

- GCC compiler  
- GTK+ 3 development libraries  
- pkg-config  

### Compile

```bash
gcc `pkg-config --cflags gtk+-3.0` src/vault.c -o vault `pkg-config --libs gtk+-3.0`
./vault


