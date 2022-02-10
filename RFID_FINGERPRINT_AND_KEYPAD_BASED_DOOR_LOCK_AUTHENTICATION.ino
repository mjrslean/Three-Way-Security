//All required libraries
#include <Adafruit_Fingerprint.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);
SoftwareSerial sim800(5, 6);  // SoftwareSerial SIM800(Rx, Tx)
LiquidCrystal_I2C lcd(0x27, 20, 2);
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)   

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//Initialize Pins for LED's, relay and piezo buzzer
String number = "";   //Change your number with your country code
const int PiezoPin = 1;    
const int RedPin= 2;
const int BluePin= 3;
const int RelayPin = 4;

char password[6];  
boolean RFIDMode = true;
boolean FINGERPRINTMode = true; // boolean to change modes

char initial_password[6] = {'5', '4', '3', '4', '2', '1'};  // Variable to store initial password
// String to store CardUID of tag. 
String cardUID ="";   //Change it with your Card's UID 

char key_pressed = 0; //Variable to store incoming keys
uint8_t i = 0;  

//Defining how many rows and columns your keypad have
const byte rows = 4;
const byte columns = 3;

//Keypad pin map
char keymap[rows][columns] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
  };

//Initializing pins for keypad
byte row_pins[rows] = {A1, A5, A4, A3};
byte column_pins[columns] = {A2, A0, 0};

//Create instance for keypad
Keypad keypad = Keypad(makeKeymap(keymap), row_pins, column_pins, rows, columns);

void setup() {
  pinMode(RedPin, OUTPUT); 
  pinMode(BluePin, OUTPUT); 
  pinMode(PiezoPin, OUTPUT);     
  pinMode(RelayPin, OUTPUT);     

  SPI.begin();      
  mfrc522.PCD_Init();   
  lcd.init();   
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SECURITY DOOR ");
  lcd.setCursor(0, 1);
  lcd.print("     LOCK    ");

   //Turn on the LED
  digitalWrite(RedPin, HIGH); 
  digitalWrite(BluePin, HIGH); 
  delay(500); 
   //Turn off the LED
  digitalWrite(BluePin, LOW); 
  digitalWrite(RedPin, LOW); 
  delay(500); 
  
  //Turn on the LED
  digitalWrite(RedPin, HIGH); 
  digitalWrite(BluePin, HIGH); 
  delay(500);
  //Turn off the LED
  digitalWrite(BluePin, LOW); 
  digitalWrite(RedPin, LOW); 
  delay(500); 
  
   //Arduino communicates with SIM800 at a baud rate of 9600
  sim800.begin(9600);
   //AT command to set SIM800 to SMS mode
  sim800.print("AT+CMGF=1\r");
  delay(100);
   //Set module to send SMS data to serial out upon receipt
  sim800.print("AT+CNMI=1,2,0,0,0\r");
  delay(100);
  
  finger.begin(57600);
 if (finger.verifyPassword()) {
   lcd.setCursor(0, 0);
   lcd.print("  FINGERPRINT ");
   lcd.setCursor(0, 1);
   lcd.print("SENSOR CONNECTED");
 }
 else  {
   lcd.setCursor(0, 0);
   lcd.print("UNABLE TO FOUND");
   lcd.setCursor(0, 1);
   lcd.print("SENSOR");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("CHECK CONNECTIONS");
   while (1) {
     delay(1);
   }
 }
 lcd.clear();
}

void loop() {
  
  if(FINGERPRINTMode == true) {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)  {
      lcd.setCursor(0, 0);
      lcd.print("PLEASE SCAN YOUR");
      lcd.setCursor(0, 1);
      lcd.print("  FINGER FIRST  ");
      return -1;
    }
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)  {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  MESSY IMAGE");
        lcd.setCursor(0, 1);
        lcd.print("  TRY AGAIN");
        digitalWrite(PiezoPin, HIGH);
        digitalWrite(RedPin, HIGH);
        SENDSMS("SECURITY DOOR LOCK\nSOMEONE TRIED WITH A WRONG FINGERPRINT\n");
        delay(3000);
        digitalWrite(RedPin, LOW);
        digitalWrite(PiezoPin, LOW);
        lcd.clear();
        return -1;
    }

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)  {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("NOT VALID FINGER");
        digitalWrite(PiezoPin, HIGH);
        digitalWrite(RedPin, HIGH);
        SENDSMS("SECURITY DOOR LOCK\nSOMEONE TRIED WITH A WRONG FINGERPRINT\n");
        delay(3000);
        digitalWrite(RedPin, LOW);
        digitalWrite(PiezoPin, LOW);
        lcd.clear();
        return -1;
    }

    // found a match!
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  FINGERPRINT   ");
    lcd.setCursor(0, 1);
    lcd.print("    MATCHED     ");
    digitalWrite(BluePin, HIGH);
    delay(3000);
    digitalWrite(BluePin, LOW);
    lcd.clear();
    FINGERPRINTMode = false ;
  }

  
   if (FINGERPRINTMode == false) {
    lcd.setCursor(0, 0);
    lcd.print(" PUT YOUR CARD ");
    lcd.setCursor(0, 1);
    lcd.print(" TO THE READER ");
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    //Reading from the card
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();

    if (tag.substring(1) == cardUID)
    {
      // If UID of tag is matched.
      lcd.clear();
      lcd.print("  TAG MATCHED   ");
      digitalWrite(BluePin, HIGH);
      delay(3000);
      digitalWrite(BluePin, LOW);
      lcd.clear();
      lcd.print("ENTER PASSWORD:");
      lcd.setCursor(0, 1);
      while(FINGERPRINTMode == false) {
          key_pressed = keypad.getKey(); 
          if (key_pressed)
          {
            password[i++] = key_pressed; 
            lcd.print("*");
          }
          if (i == 6) // If 6 keys are completed
          {
            delay(200);
            if (!(strncmp(password, initial_password, 6))) 
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" DOOR UNLOCKED");
              lcd.setCursor(0, 1);
              lcd.print("    WELCOME");
              digitalWrite(RelayPin, HIGH); 
              digitalWrite(BluePin, HIGH);
              SENDSMS("SECURITY DOOR LOCK\nDOOR OPENED\n");
              delay(5000);
              digitalWrite(BluePin, LOW);
              digitalWrite(RelayPin, LOW); 
              lcd.clear();
              i = 0;
              FINGERPRINTMode = true; 
            }
            else  
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("   INCORRECT   ");
              lcd.setCursor(0, 1);
              lcd.print("   PASSWORD   ");
              digitalWrite(PiezoPin, HIGH);
              digitalWrite(RedPin, HIGH);
              SENDSMS("SECURITY DOOR LOCK\nSOMEONE TRIED WITH A WRONG PASSWORD\n");
              delay(3000);
              digitalWrite(PiezoPin, LOW);
              digitalWrite(RedPin, LOW);
              lcd.clear();
              i = 0;
              FINGERPRINTMode = false; 
            }
          }
       }
    }
    else
    {
      // If UID of tag is not matched.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WRONG TAG SHOWN");
      lcd.setCursor(0, 1);
      lcd.print("ACCESS DENIED");
      digitalWrite(PiezoPin, HIGH);
      digitalWrite(RedPin, HIGH);
      SENDSMS("SECURITY DOOR LOCK\nSOMEONE TRIED WITH A WRONG TAG\n");
      delay(3000);
      digitalWrite(RedPin, LOW);
      digitalWrite(PiezoPin, LOW);
      lcd.clear();
    }
  }
}

void SENDSMS(String message) {

  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println("AT+CMGS=\"" + number + "\"\r");
  delay(500);
  sim800.println(message);
  delay(500);
  sim800.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  sim800.println();
  delay(1000);
  
}
