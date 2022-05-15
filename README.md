# Arduino Project
RFID, FINGERPRINT, AND KEYPAD BASED DOOR LOCK WITH ALERT SYSTEM USING ARDUINO
> Three-factor authentication security door lock

## Basic Operations

On power-up, the LCD prompt a message * *"Security Door lock, Scan your fingerprint first."* * If the user correctly scans their fingerprint that has been enrolled in the chip, the blue led lights for a few seconds. If not, LCD will prompt a message indicating an error while the red led, and the piezo buzzer will be activated for a few seconds. If scanning fingerprint is now successful, the user must tap their card for RFID. If the serial number of that card matches the information embedded in the source code, the blue led lights for a few seconds. If the serial number doesn't match, LCD will prompt a message indicating an error while the red led, and the piezo buzzer will be activated for a few seconds. If scanning the RFID is now successful, the user must type their password via matrix keypad while the blue led lights for a few seconds that is enough to open the solenoid lock. 

In the alert system, the GSM module will notify the user if someone taps the wrong tag, type the incorrect password, and try to scan their fingerprint that is not enrolled. It also notifies the user if the solenoid lock is open and close.

## Schematic Diagram

![Diagram](https://user-images.githubusercontent.com/99194388/168485882-e00e2f0c-57ae-46e7-a0af-9cb13901d0e1.png)
