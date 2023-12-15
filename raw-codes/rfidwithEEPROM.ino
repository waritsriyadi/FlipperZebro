#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Preferences.h>

#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 
#define ACCEPT_BUTTON 13 // ESP32 pin GPIO13
#define REJECT_BUTTON 12 // ESP32 pin GPIO12

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

// Define the maximum number of allowed cards
const int maxAllowedCards = 5;
String allowedUIDs[maxAllowedCards];  // Array to store allowed UIDs
int numAllowedCards = 0;  // Number of cards currently in the array

Preferences preferences;  // Preferences object for storing data persistently

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  pinMode(ACCEPT_BUTTON, INPUT_PULLUP);  // Accept button
  pinMode(REJECT_BUTTON, INPUT_PULLUP);  // Reject button

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
  lcd.print("Tap your Card!");
  lcd.setCursor(0, 1);
  lcd.print("FlipperZebro");

  // Begin Preferences with the app name and storage namespace
  preferences.begin("cardSaved", false);

  // Load allowed UIDs from preferences
  loadFromPreferences();
}

void saveToPreferences(String uid) {
  // Save the UID to preferences
  for (int i = 0; i < maxAllowedCards; i++) {
    String key = "UID_" + String(i);
    String value = preferences.getString(key.c_str(), "");
    if (value == "") {
      // Found an empty slot, save the UID
      preferences.putString(key.c_str(), uid);
      break;
    }
  }
}

void loadFromPreferences() {
  // Load the UIDs from preferences
  for (int i = 0; i < maxAllowedCards; i++) {
    String key = "UID_" + String(i);
    String uid = preferences.getString(key.c_str(), "");
    if (uid != "") {
      allowedUIDs[numAllowedCards++] = uid;
    }
  }
}

void clearPreferences() {
  // Clear all saved UIDs from preferences
  for (int i = 0; i < maxAllowedCards; i++) {
    String key = "UID_" + String(i);
    preferences.remove(key.c_str());
  }
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor and LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UID Card: ");
  lcd.setCursor(0, 1);
  Serial.print("UID tag :");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    lcd.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();

  // Check if the scanned UID is already in the list of allowed UIDs
  content.toUpperCase();
  bool accessGranted = false;
  for (int i = 0; i < numAllowedCards; i++) {
    if (content.substring(1) == allowedUIDs[i]) {
      accessGranted = true;
      break;
    }
  }

  // If the scanned UID is not in the list, prompt the user to accept or reject the card
  if (!accessGranted && numAllowedCards < maxAllowedCards) {
    lcd.setCursor(0, 0);
    lcd.print("    New Card    ");
    lcd.setCursor(0, 1);
    lcd.print(" == Detected! ==");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Save New Card ?");
    lcd.setCursor(0, 1);
    lcd.print(" 1: YES | 2: NO ");

    // Wait for user input
    while (digitalRead(ACCEPT_BUTTON) == HIGH && digitalRead(REJECT_BUTTON) == HIGH) {
      delay(100);
    }

    if (digitalRead(ACCEPT_BUTTON) == LOW) {
      // Accept the card and save it to the allowed list
      if (numAllowedCards < maxAllowedCards) {
        allowedUIDs[numAllowedCards++] = content.substring(1);
        Serial.println("New card added to the allowed list");
        saveToPreferences(content.substring(1));  // Save the UID to preferences
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   New Card     ");
        lcd.setCursor(0, 1);
        lcd.print("== Accepted! == ");
        accessGranted = true;  // Set accessGranted to true when card is accepted
        delay(2000);
      } else {
        Serial.println("Cannot accept more cards, limit reached");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("XX   Limit    XX");
        lcd.setCursor(0, 1);
        lcd.print("XX  Reached!  XX");
        delay(2000);
      }
    } else if (digitalRead(REJECT_BUTTON) == LOW) {
      // Reject the card
      Serial.println("Card rejected");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("XX    Card    XX");
      lcd.setCursor(0, 1);
      lcd.print("XX  Rejected! XX");
      delay(2000);
    }
  }

  // Display result
  Serial.print("Message : ");
  if (accessGranted) {
    Serial.println("Authorized access");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     Access     ");
    lcd.setCursor(0, 1);
    lcd.print(" == Granted! == ");
    delay(2000);
  } else {
    Serial.println("Access denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("XX   Access   XX");
    lcd.setCursor(0, 1);
    lcd.print("XX   Denied!  XX");
    delay(2000);
  }

  // Reset the LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tap your Card!");
  lcd.setCursor(0, 1);
  lcd.print("FlipperZebro");

  delay(3000);
}

void saveSettings() {
  // End Preferences to save the changes
  preferences.end();
}

void loadSettings() {
  // Begin Preferences to load the settings
  preferences.begin("cardSaved", false);
}
