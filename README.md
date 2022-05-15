# Arduino Project
RFID, FINGERPRINT, AND KEYPAD BASED DOOR LOCK WITH ALERT SYSTEM USING ARDUINO 
> Three-factor authentication security door lock

## Basic Operations

On power-up, the LCD prompt a message *"Security Door lock, Scan your fingerprint first."* If the user correctly scans their fingerprint that has been enrolled in the chip, the blue led lights for a few seconds. If not, LCD will prompt a message indicating an error while the red led, and the piezo buzzer will be activated for a few seconds. If scanning fingerprint is now successful, the user must tap their card for RFID. If the serial number of that card matches the information embedded in the source code, the blue led lights for a few seconds. If the serial number doesn't match, LCD will prompt a message indicating an error while the red led, and the piezo buzzer will be activated for a few seconds. If scanning the RFID is now successful, the user must type their password via matrix keypad while the blue led lights for a few seconds that is enough to open the solenoid lock. 

In the alert system, the GSM module will notify the user if someone taps the wrong tag, type the incorrect password, and try to scan their fingerprint that is not enrolled. It also notifies the user if the solenoid lock is open and close.

## Devices Used

- Arduino Uno R3 ATMEGA328
- I2C 1602A LCD Display
- 4x3 Matrix Module Keypad
- NFC RFID MFRC522
- Fingerprint Sensor
- Sim800L GSM Module with 3DBi Antenna
- 12V Electromagnetic Lock
- 4201 Piezo Buzzer
- 5V Relay Module
- Blue and Red Superbright LED

## Required Libraries to Install
> Tools -> Manage Libraries
1. GSM
2. Keypad
3. LiquidCrystal I2C
4. Adafruit Fingerprint Sensor Library
5. MFRC522

## Software Set-Up for RFID and Fingerprint Sensor

**FINGERPRINT SENSOR**

> To start with, we will enroll fingerprints via Arduino.
In enrolling via Arduino. open **Files ->Examples ->Adafruit Fingerprint Sensor Library -> enroll** then upload it to your Arduino.
<div class="inline">
<img src="https://user-images.githubusercontent.com/99194388/168488031-35f7919e-2044-4170-ad2b-de6c8e9578e6.png" width="400">
<img src="https://user-images.githubusercontent.com/99194388/168488011-66cb81f4-67ef-483a-9e3f-894c0b75a9a9.png" width="400">

</div> <br>

> To test if the fingerprint scanner can really detect your fingerprint, go to:
open **Files -> Examples -> Adafruit Fingerprint Sensor Library -> fingerprint** and upload it to your Arduino.
Open up the serial monitor at 9600 baud and when prompted, place your finger against the sensor. You should see the message below. “Confidence” is a score number (from 0 to 255) that indicates how good of a match the print is. The higher the value, the better match we have.
<div class="inline">
<img src="https://user-images.githubusercontent.com/99194388/168488050-4cdb799a-d89c-4896-9ff1-8cd7de30ddb0.png" width="400">
<img src="https://user-images.githubusercontent.com/99194388/168488065-7ddd7d1f-0104-4cd8-82fb-43152308dd8e.png" width="400">
</div>

<br><br>
**RFID MFRC522**

>To start with, we need to identify the card UID.
In knowing via Arduino. open **Files ->Examples -> MFRC522 -> DumpInfo** then upload it to your Arduino.
Open up the serial monitor at 9600 baud and when prompted, tap your card and keychain tag against the sensor. You should see the message below. Card UID is the unique number that identifies the RFID tag.

<div class="inline">
<img src="https://user-images.githubusercontent.com/99194388/168488180-6d909d2e-cf39-4c2d-8444-a20594414a96.png" width="400">
<img src="https://user-images.githubusercontent.com/99194388/168488178-d04603ad-26d3-4bf8-ae7a-7785274f412a.png" width="400">
</div>

## Schematic Diagram

<img src="https://user-images.githubusercontent.com/99194388/168485882-e00e2f0c-57ae-46e7-a0af-9cb13901d0e1.png" width="600">

## Output
<img src="https://user-images.githubusercontent.com/99194388/168486520-8dc28796-bbc6-4122-907b-7eb82f07c57b.jpg" width="600">
<img src="https://user-images.githubusercontent.com/99194388/168486577-e783cfc3-55d8-4c80-80f5-f7eb2b007ec9.jpg" width="600">


