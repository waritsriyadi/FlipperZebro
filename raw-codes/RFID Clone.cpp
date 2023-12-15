#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Preferences.h>

#define RST_PIN 27
#define SS_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Pengaturan pin tombol CHANGE dan OK
const int CHANGE_PIN = 14;
const int BACK_PIN = 13;
const int OK_PIN = 12;
const int maxAllowedCards = 3;
String allowedUIDs[maxAllowedCards];  // Array to store allowed UIDs
int numAllowedCards = 0;  // Number of cards currently in the array

// Inisialisasi LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Deklarasi variabel menu
int currentMenu = 1;
int currentSubMenuRFID = 1;
int selectedCard = 1;
boolean inSubMenu = false;
boolean inListMenu = false;

Preferences preferences;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  mfrc522.PCD_Init(); // init MFRC522

 // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

 // Inisialisasi pin tombol CHANGE dan OK sebagai input
  pinMode(CHANGE_PIN, INPUT_PULLUP);
  pinMode(BACK_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);
  // Begin Preferences with the app name and storage namespace
  preferences.begin("cardSaved", false);
  loadFromPreferences();

  // Tampilkan menu awal
  displayMenu();
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

void loop() {
 // Baca nilai tombol CHANGE dan OK
 int changeButton = digitalRead(CHANGE_PIN);
 int okButton = digitalRead(OK_PIN);
 int backButton = digitalRead(BACK_PIN);

 // Jika tombol CHANGE ditekan dan tidak sedang di dalam sub-menu
 if (changeButton == LOW && !inSubMenu) {
    // Tunggu hingga tombol CHANGE dilepaskan
    while (digitalRead(CHANGE_PIN) == LOW);

    // Ubah menu yang ditampilkan
    currentMenu++;
    if (currentMenu > 5) {
      currentMenu = 1;
    }

    // Tampilkan menu baru
    displayMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
    delay(500);
 }

 // Jika tombol OK ditekan
 if (okButton == LOW && !inSubMenu) {
    // Tunggu hingga tombol OK dilepaskan
    while (digitalRead(OK_PIN) == LOW);

    // Mengeksekusi menu yang dipilih berdasarkan variabel currentMenu
    executeMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol OK lagi
    delay(500);
 }
  if (backButton == LOW && !inSubMenu) {
    // Tunggu hingga tombol CHANGE dilepaskan
    while (digitalRead(BACK_PIN) == LOW);

    // Tampilkan menu baru
    displayMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
    delay(500);
 }
}

void displayMenu() {
 // Hapus tampilan LCD
 lcd.clear();

 // Tampilkan menu sesuai variabel currentMenu
 switch (currentMenu) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("1. RFID");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("2. NFC");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("3. Infrared");
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("4. RF");
      break;
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("5. USB");
      break;
 }
}

void executeMenu() {
 inSubMenu = true; // Set to true when entering a sub-menu

 // Mengeksekusi menu yang dipilih berdasarkan variabel currentMenu
 switch (currentMenu) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("1. RFID");
      delay(1000);
      executeSubMenuRFID();
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("2. NFC");
      delay(1000);
      //executeSubMenuRFID();
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("3. IR");
      delay(1000);
      //executeSubMenuRFID();
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("4. RF");
      delay(1000);
      //executeSubMenuRFID();
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("5. USB");
      delay(1000);
      //executeSubMenuRFID();
      break;
 }

 inSubMenu = false; // Set back to false when sub-menu operation is completed
}

void displaySubMenuRFID() {
 inSubMenu = true;
 // Hapus tampilan LCD
 lcd.clear();

 // Tampilkan menu sesuai variabel currentMenu
 switch (currentSubMenuRFID) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("RFID Menu:");
      lcd.setCursor(0, 1);
      lcd.print("1. Scan");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("RFID Menu:");
      lcd.setCursor(0, 1);
      lcd.print("2. View");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("RFID Menu:");
      lcd.setCursor(0, 1);
      lcd.print("3. Delete");
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("RFID Menu:");
      lcd.setCursor(0, 1);
      lcd.print("4. Back");
      break;
 }
}

void executeSubMenuRFID() {
 inSubMenu = true;
 displaySubMenuRFID();

 while (inSubMenu) {
    int okButtonRFID = digitalRead(OK_PIN);
    int changeButtonRFID = digitalRead(CHANGE_PIN);
    int backButtonRFID = digitalRead(BACK_PIN);

    if (changeButtonRFID == LOW) {
      while (digitalRead(CHANGE_PIN) == LOW);
          // Ubah menu yang ditampilkan
      currentSubMenuRFID++;
      if (currentSubMenuRFID > 4) {
        currentSubMenuRFID = 1;
      }
      // Tampilkan menu baru
      displaySubMenuRFID();

      // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
      delay(500);
    }

    if (backButtonRFID == LOW) {
      while (digitalRead(BACK_PIN) == LOW);
          // Ubah menu yang ditampilkan
      inSubMenu = false;
      displayMenu();
      break;
    }

    if (okButtonRFID == LOW) {
      while (digitalRead(OK_PIN) == LOW);

      switch (currentSubMenuRFID) {
        case 1:
          // Pilihan 1: Scan
          executeRFIDScan();
          break;
        case 2:
          // Pilihan 2: View
          executeRFIDView();
          break;
        case 3:
          // Pilihan 3: Delete
          executeRFIDDelete();
          break;
        case 4:
          // Pilihan 3: Back to Main Menu
          inSubMenu = false;
          displayMenu();
          break;
      }
    }
  }
}

void executeRFIDScan() {
  bool scanDetected = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tap your Card!");
  lcd.setCursor(0, 1);
  lcd.print("FlipperZebro");

 // Lakukan pengujian ulang untuk menghindari false positive
  while (!mfrc522.PICC_IsNewCardPresent() && !mfrc522.PICC_ReadCardSerial() && !scanDetected) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      // Cetak UID kartu RFID
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("UID:");
      lcd.setCursor(0, 1);
      String content = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        lcd.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      delay(2000);
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
        lcd.print("   New Card    ");
        lcd.setCursor(0, 1);
        lcd.print("== Detected! == ");
        //delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Save New Card ?");
        lcd.setCursor(0, 1);
        lcd.print(" 1: YES | 2: NO ");

        while (digitalRead(OK_PIN) == HIGH && digitalRead(CHANGE_PIN) == HIGH && digitalRead(BACK_PIN) == HIGH) {
          delay(100);
        }
        
        if (digitalRead(CHANGE_PIN) == LOW) {
        // Accept the card and save it to the allowed list
          if (numAllowedCards < maxAllowedCards) {
            allowedUIDs[numAllowedCards++] = content.substring(1);
            Serial.println("New card added to the allowed list");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   New Card     ");
            lcd.setCursor(0, 1);
            lcd.print("== Accepted! == ");
            saveToPreferences(content.substring(1));
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
        } else if (digitalRead(OK_PIN) == LOW) {
          //Reject the card
          Serial.println("Card rejected");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("XX    Card    XX");
          lcd.setCursor(0, 1);
          lcd.print("XX  Rejected! XX");
          delay(2000);
        } else if (digitalRead(BACK_PIN) == LOW) {
          lcd.clear();
          lcd.setCursor(0, 0);
          displaySubMenuRFID();
          break;
        }
      }
      if (accessGranted) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Your Card     ");
        lcd.setCursor(0, 1);
        lcd.print(" Already Saved!  ");
        delay(1000);
      }
      scanDetected = true;
      inSubMenu = true;
      displaySubMenuRFID();
      break;
    } else if (digitalRead(BACK_PIN) == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        displaySubMenuRFID();
        break;
    }
  }
}

void executeRFIDDelete() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deleting RFID...");
  delay(2000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (numAllowedCards <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("RFID not found!");
    preferences.clear();
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Select RFID");
    displayListRFID();
    inListMenu = true;
    while (inListMenu) {
      // Baca nilai tombol CHANGE dan OK
      int changeButton = digitalRead(CHANGE_PIN);
      int okButton = digitalRead(OK_PIN);
      int backButton = digitalRead(BACK_PIN);

      if (changeButton == LOW) {
        while (digitalRead(CHANGE_PIN) == LOW);
        selectedCard++;
        if (selectedCard > numAllowedCards) { 
          selectedCard = 1;
        }
        displayListRFID();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW);
        lcd.clear();
        break; // Keluar dari loop jika OK ditekan
      }

      if (okButton == LOW) {
        while (digitalRead(OK_PIN) == LOW);

        // Remove the selected card from Preferences
        String key = "UID_" + String(selectedCard - 1);
        preferences.remove(key.c_str());

        // Hapus kartu yang dipilih dari daftar
        String deletedUID = allowedUIDs[selectedCard - 1];
        for (int i = selectedCard - 1; i < numAllowedCards - 1; i++) {
          allowedUIDs[i] = allowedUIDs[i + 1];
        }
        numAllowedCards--;

        if (numAllowedCards <= 0) {
          preferences.clear();
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RFID Deleted!");
        lcd.setCursor(0, 1);
        lcd.print("UID: " + deletedUID);
        delay(2000);

        // Save the changes to Preferences
        saveSettings();
        loadSettings();

        break; // Keluar dari loop jika OK ditekan
      }
    }
  }

  inSubMenu = true;
  displaySubMenuRFID();
}

void displayListRFID() {
  lcd.clear();
  switch (selectedCard) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(allowedUIDs[selectedCard-1]);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(allowedUIDs[selectedCard-1]);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(allowedUIDs[selectedCard-1]);
      break;
    }
}

void executeRFIDView() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("List RFIDs...");
  delay(2000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (numAllowedCards <= 0){
    lcd.setCursor(0, 1);
    lcd.print("RFID not found!");
    delay(2000);
  } else {
    displayListRFID();
    inListMenu = true;
    while (inListMenu) {
      // Baca nilai tombol CHANGE dan OK
      int changeButton = digitalRead(CHANGE_PIN);
      int backButton = digitalRead(BACK_PIN);

      if (changeButton == LOW) {
        while (digitalRead(CHANGE_PIN) == LOW);
        selectedCard++;
        if (selectedCard > numAllowedCards) {
          selectedCard = 1;
        }
        displayListRFID();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW);

        if (numAllowedCards <= 0) {
          preferences.clear();
        }
        lcd.clear();
        break; // Keluar dari loop jika OK ditekan
      }
    }
  }
  inSubMenu = true;
  displaySubMenuRFID();
}

void saveSettings() {
  // End Preferences to save the changes
  preferences.end();
}

void loadSettings() {
  // Begin Preferences to load the settings
  preferences.begin("cardSaved", false);
}