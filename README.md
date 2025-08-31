# RFID-Based-Attendance-System
Automated attendance management system using RFID technology, which records entries by scanning RFID cards and updates attendance data in an Excel sheet for efficient tracking and record keeping.

# Features
- Scan RFID cards to log attendance instantly
- Show student name and roll number on LCD after scanning
- Send data to Excel (via PLX-DAQ) with date and time
- Prevents duplicate attendance within each session

# Hardware Used
- Arduino Uno (or compatible board)
- RFID Module (MFRC522)
- LCD Display (16x2, I2C interface)
- RFID cards/tags

# Libraries Required
- SPI.h
- MFRC522.h
- LiquidCrystal_I2C.h
- Wire.h

# Circuit Diagram
<img width="1440" height="928" alt="IMG_20250831_192725" src="https://github.com/user-attachments/assets/2e495653-e45f-476f-a8f6-659c402fa437" />



# How to Set Up
1. Connect MFRC522 RFID module to Arduino as per standard SPI wiring.
2. Connect the 16x2 I2C LCD display to Arduino.
3. Upload the provided code to Arduino.
4. Install PLX-DAQ (for serial data to Excel) on your computer.
5. Open Excel and PLX-DAQ, set up labels as in the code.

# How it Works
- The system waits for an RFID card to be scanned.
- On recognizing a card, it checks against predefined UIDs in the code.
- If the card is valid and not already marked, it displays the name and roll number on the LCD, and sends the attendance with date and time to Excel.
- If the card is scanned again, it indicates "Already Exist" to avoid duplicate marking.

## Code Snippet
