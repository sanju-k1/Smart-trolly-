# 🛒 Smart Trolley Billing System (Arduino + RFID)

## 📌 Overview
This project implements a **Smart Shopping Trolley** using an **Arduino Uno**, **RFID reader**, **LCD display**, and **buttons**.  
The trolley automatically scans items using RFID tags, calculates the total bill, and allows customers to **add**, **remove**, or **reset** items easily.

---

## ✅ Features
- 📡 **RFID-based item detection**
- 🖥️ **LCD display** for real-time billing updates
- 🔔 **Buzzer alerts** for add/remove confirmation
- 🟢 **Button controls** for add/remove/reset modes
- 💾 Efficient and modular Arduino code
- 🧾 Displays total bill dynamically

---

## 🛠️ Components Used
- Arduino Uno  
- RFID Module (MFRC522)  
- I2C LCD Display (16x2)  
- Push Buttons (3x)  
- Buzzer  
- Breadboard, Jumpers, Power Supply  

---

## 🔗 Circuit Connections
| **Component**     | **Arduino Pin** |
|--------------------|-----------------|
| RFID SDA          | D10            |
| RFID SCK          | D13            |
| RFID MOSI         | D11            |
| RFID MISO         | D12            |
| RFID RST          | D9             |
| RFID VCC/GND      | 3.3V / GND     |
| LCD SDA/SCL       | SDA/SCL pins   |
| Buttons           | D2, D3, D4     |
| Buzzer            | D5             |

---

## 📜 How to Use
1. **Upload the Arduino Sketch** (`SmartTrolley.ino`) using Arduino IDE.  
2. Power up the Arduino and connect all components.  
3. Scan RFID-tagged items to add them to the bill.  
4. Use:
   - **Add Button (D3)** → Add item mode  
   - **Remove Button (D2)** → Remove item mode  
   - **Reset Button (D4)** → Clear all items  
5. Total bill is displayed on LCD.

---

## 📹 Demonstration
🔗 [Click here to watch the demo video](https://drive.google.com/drive/folders/1mvK7PZbYQR-pgF0nceUr77cgtExvruEN?usp=sharing)

---

## 📂 Project Structure
