#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Preferences.h>
#include <Adafruit_PN532.h>

#define RST_PIN 27
#define SS_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_PN532 nfc(21, 22);

// Pengaturan pin tombol CHANGE dan OK
const int CHANGE_PIN = 14;
const int BACK_PIN = 12;
const int OK_PIN = 13;
const int maxAllowedCards = 3;
String allowedUIDs[maxAllowedCards];  // Array to store allowed UIDs
int numAllowedCards = 0;              // Number of cards currently in the array
int NFCAllowedCards = 0;
String NFCallowedUIDs[maxAllowedCards];

// Inisialisasi LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Deklarasi variabel menu
int currentMenu = 1;
int currentSubMenuRFID = 1, currentSubMenuNFC = 1;
int selectedCard = 1;
boolean inSubMenu = false;
boolean inListMenu = false;

Preferences preferences, NFCPreferences;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  SPI.begin();         // init SPI bus
  mfrc522.PCD_Init();  // init MFRC522
  nfc.begin();         // init PN532
  nfc.SAMConfig();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Inisialisasi pin tombol CHANGE dan OK sebagai input
  pinMode(CHANGE_PIN, INPUT_PULLUP);
  pinMode(BACK_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);

  // Begin Preferences with the app name and storage namespace
  preferences.begin("cardSaved", false);
  NFCPreferences.begin("NFCSaved", false);
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

void saveNFCToPreferences(String uid) {
  // Save the UID to preferences for NFC
  for (int i = 0; i < maxAllowedCards; i++) {
    String key = "NFC_UID_" + String(i);
    String value = NFCPreferences.getString(key.c_str(), "");
    if (value == "") {
      // Found an empty slot, save the UID
      NFCPreferences.putString(key.c_str(), uid);
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

  for (int i = 0; i < maxAllowedCards; i++) {
    String key = "NFC_UID_" + String(i);
    String uid = NFCPreferences.getString(key.c_str(), "");
    if (uid != "") {
      NFCallowedUIDs[NFCAllowedCards++] = uid;
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
    while (digitalRead(CHANGE_PIN) == LOW)
      ;

    // Ubah menu yang ditampilkan
    currentMenu++;
    if (currentMenu > 6) {
      currentMenu = 1;
    }

    // Tampilkan menu baru
    displayMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
    delay(200);
  }

  // Jika tombol OK ditekan
  if (okButton == LOW && !inSubMenu) {
    // Tunggu hingga tombol OK dilepaskan
    while (digitalRead(OK_PIN) == LOW)
      ;

    // Mengeksekusi menu yang dipilih berdasarkan variabel currentMenu
    executeMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol OK lagi
    delay(200);
  }
  if (backButton == LOW && !inSubMenu) {
    // Tunggu hingga tombol CHANGE dilepaskan
    while (digitalRead(BACK_PIN) == LOW)
      ;
    executeSleep();
    // Tampilkan menu baru
    displayMenu();

    // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
    delay(200);
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
    case 6:
      lcd.setCursor(0, 0);
      lcd.print("FZebro Menu:");
      lcd.setCursor(0, 1);
      lcd.print("6. Sleep");
      break;
  }
}

void executeMenu() {
  inSubMenu = true;  // Set to true when entering a sub-menu

  // Mengeksekusi menu yang dipilih berdasarkan variabel currentMenu
  switch (currentMenu) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("1. RFID");
      delay(500);
      executeSubMenuRFID();
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("2. NFC");
      delay(500);
      executeSubMenuNFC();
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("3. Infrared");
      delay(500);
      //executeSubMenuRFID();
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("4. RF");
      delay(500);
      //executeSubMenuRFID();
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("5. USB");
      delay(500);
      //executeSubMenuRFID();
      break;
    case 6:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You selected:");
      lcd.setCursor(0, 1);
      lcd.print("6. Sleep");
      executeSleep();
      break;
  }

  inSubMenu = false;  // Set back to false when sub-menu operation is completed
}

// FUNGSI SLEEP
void executeSleep() {
  inSubMenu = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sleep Mode in: ");
  lcd.setCursor(0, 1);
  for (int i = 3; i > 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print(" >> ");
    lcd.print(i);
    lcd.print(" seconds");
    delay(1000);  // Wait for one second
  }
  lcd.noBacklight();
  while (digitalRead(OK_PIN) == HIGH && digitalRead(CHANGE_PIN) == HIGH) {
    delay(1);
  }
  displayMenu();
  lcd.backlight();
  inSubMenu = false;
}

// FUNGSI RFID (MFRC522)
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
      while (digitalRead(CHANGE_PIN) == LOW)
        ;
      // Ubah menu yang ditampilkan
      currentSubMenuRFID++;
      if (currentSubMenuRFID > 4) {
        currentSubMenuRFID = 1;
      }
      // Tampilkan menu baru
      displaySubMenuRFID();

      // Tunggu selama 0,5 detik sebelum memeriksa tombol CHANGE lagi
      delay(200);
    }

    if (backButtonRFID == LOW) {
      while (digitalRead(BACK_PIN) == LOW)
        ;
      // Ubah menu yang ditampilkan
      inSubMenu = false;
      displayMenu();
      break;
    }

    if (okButtonRFID == LOW) {
      while (digitalRead(OK_PIN) == LOW)
        ;

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
      if (!accessGranted) {
        lcd.setCursor(0, 0);
        lcd.print("   New Card    ");
        lcd.setCursor(0, 1);
        lcd.print("== Detected! == ");
        delay(500);
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
            delay(500);
          } else {
            Serial.println("Cannot accept more cards, limit reached");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("XX   Limit    XX");
            lcd.setCursor(0, 1);
            lcd.print("XX  Reached!  XX");
            delay(1000);
          }
        } else if (digitalRead(OK_PIN) == LOW) {
          //Reject the card
          Serial.println("Card rejected");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("XX    Card    XX");
          lcd.setCursor(0, 1);
          lcd.print("XX  Rejected! XX");
          delay(1000);
        } else if (digitalRead(BACK_PIN) == LOW) {
          while (digitalRead(BACK_PIN) == LOW)
            ;
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
      while (digitalRead(BACK_PIN) == LOW)
        ;
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
  delay(1000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (numAllowedCards <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("RFID not found!");
    preferences.clear();
    delay(1000);
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
        while (digitalRead(CHANGE_PIN) == LOW)
          ;
        selectedCard++;
        if (selectedCard > numAllowedCards) {
          selectedCard = 1;
        }
        displayListRFID();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW)
          ;
        lcd.clear();
        break;  // Keluar dari loop jika OK ditekan
      }

      if (okButton == LOW) {
        while (digitalRead(OK_PIN) == LOW)
          ;

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
        delay(1000);

        // Save the changes to Preferences
        saveSettings();
        loadSettings();

        break;  // Keluar dari loop jika OK ditekan
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
      lcd.print(allowedUIDs[selectedCard - 1]);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(allowedUIDs[selectedCard - 1]);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(allowedUIDs[selectedCard - 1]);
      break;
  }
}
void executeRFIDView() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("List RFIDs...");
  delay(1000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (numAllowedCards <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("RFID not found!");
    delay(1000);
  } else {
    displayListRFID();
    inListMenu = true;
    while (inListMenu) {
      // Baca nilai tombol CHANGE dan OK
      int changeButton = digitalRead(CHANGE_PIN);
      int backButton = digitalRead(BACK_PIN);

      if (changeButton == LOW) {
        while (digitalRead(CHANGE_PIN) == LOW)
          ;
        selectedCard++;
        if (selectedCard > numAllowedCards) {
          selectedCard = 1;
        }
        displayListRFID();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW)
          ;

        if (numAllowedCards <= 0) {
          preferences.clear();
        }
        lcd.clear();
        break;  // Keluar dari loop jika OK ditekan
      }
    }
  }
  inSubMenu = true;
  displaySubMenuRFID();
}

// FUNGSI NFC (PN532)
void displaySubMenuNFC() {
  inSubMenu = true;
  // Clear LCD display
  lcd.clear();

  // Display menu based on currentSubMenuNFC variable
  switch (currentSubMenuNFC) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("NFC Menu:");
      lcd.setCursor(0, 1);
      lcd.print("1. Scan");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("NFC Menu:");
      lcd.setCursor(0, 1);
      lcd.print("2. View");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("NFC Menu:");
      lcd.setCursor(0, 1);
      lcd.print("3. Delete");
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("NFC Menu:");
      lcd.setCursor(0, 1);
      lcd.print("4. Back");
      break;
  }
}
void executeSubMenuNFC() {
  inSubMenu = true;
  displaySubMenuNFC();

  while (inSubMenu) {
    int okButtonNFC = digitalRead(OK_PIN);
    int changeButtonNFC = digitalRead(CHANGE_PIN);
    int backButtonNFC = digitalRead(BACK_PIN);

    if (changeButtonNFC == LOW) {
      while (digitalRead(CHANGE_PIN) == LOW)
        ;
      // Change displayed menu
      currentSubMenuNFC++;
      if (currentSubMenuNFC > 4) {
        currentSubMenuNFC = 1;
      }
      // Display new menu
      displaySubMenuNFC();
      delay(200);
    }

    if (backButtonNFC == LOW) {
      while (digitalRead(BACK_PIN) == LOW)
        ;
      // Change displayed menu
      inSubMenu = false;
      displayMenu();
      break;
    }

    if (okButtonNFC == LOW) {
      while (digitalRead(OK_PIN) == LOW)
        ;

      switch (currentSubMenuNFC) {
        case 1:
          // Option 1: Scan
          executeNFCTagScan();
          break;
        case 2:
          // Option 2: View
          executeNFCTagView();
          break;
        case 3:
          // Option 3: Delete
          executeNFCTagDelete();
          break;
        case 4:
          // Option 4: Back to Main Menu
          inSubMenu = false;
          displayMenu();
          break;
      }
    }
  }
}
void executeNFCTagScan() {
  bool scanDetected = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tap your NFC!");
  lcd.setCursor(0, 1);
  lcd.print("FlipperZebro");

  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  while (!scanDetected) {
    // Lakukan pengujian ulang untuk menghindari false positive
    if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
      // Cetak UID kartu RFID
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("UID:");
      lcd.setCursor(0, 1);
      String scannedUID = "";
      for (uint8_t i = 0; i < uidLength; i++) {
        Serial.print(uid[i] < 0x10 ? " 0" : " ");
        Serial.print(uid[i], HEX);
        lcd.print(uid[i] < 0x10 ? " 0" : " ");
        lcd.print(uid[i], HEX);
        scannedUID.concat(uid[i] < 0x10 ? " 0" : " ");
        scannedUID.concat(String(uid[i], HEX));
      }
      Serial.println("");
      delay(1000);
      // Check if the scanned UID is already in the list of allowed UIDs
      scannedUID.toUpperCase();
      bool accessGranted = false;
      for (int i = 0; i < NFCAllowedCards; i++) {
        if (scannedUID.substring(1) == NFCallowedUIDs[i]) {
          accessGranted = true;
          break;
        }
      }
      // If the scanned UID is not in the list, prompt the user to accept or reject the card
      if (!accessGranted) {
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
          if (NFCAllowedCards < maxAllowedCards) {
            NFCallowedUIDs[NFCAllowedCards++] = scannedUID.substring(1);
            Serial.println("New card added to the allowed list");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   New Card     ");
            lcd.setCursor(0, 1);
            lcd.print("== Accepted! == ");
            saveNFCToPreferences(scannedUID.substring(1));
            accessGranted = true;  // Set accessGranted to true when card is accepted
            delay(1000);
          } else {
            Serial.println("Cannot accept more cards, limit reached");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("XX   Limit    XX");
            lcd.setCursor(0, 1);
            lcd.print("XX  Reached!  XX");
            delay(1000);
          }
        } else if (digitalRead(OK_PIN) == LOW) {
          //Reject the card
          Serial.println("Card rejected");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("XX    Card    XX");
          lcd.setCursor(0, 1);
          lcd.print("XX  Rejected! XX");
          delay(1000);
        } else if (digitalRead(BACK_PIN) == LOW) {
          while (digitalRead(BACK_PIN) == LOW)
            ;
          lcd.clear();
          lcd.setCursor(0, 0);
          displaySubMenuNFC();
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
    }
    inSubMenu = true;
    scanDetected = true;
    displaySubMenuNFC();
    break;
  }
}
void executeNFCTagDelete() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deleting NFC...");
  delay(1000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (NFCAllowedCards <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("NFC not found!");
    NFCPreferences.clear();
    delay(1000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Select NFC");
    displayListNFC();
    inListMenu = true;
    while (inListMenu) {
      // Baca nilai tombol CHANGE dan OK
      int changeButton = digitalRead(CHANGE_PIN);
      int okButton = digitalRead(OK_PIN);
      int backButton = digitalRead(BACK_PIN);

      if (changeButton == LOW) {
        while (digitalRead(CHANGE_PIN) == LOW)
          ;
        selectedCard++;
        if (selectedCard > NFCAllowedCards) {
          selectedCard = 1;
        }
        displayListNFC();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW)
          ;
        lcd.clear();
        break;  // Keluar dari loop jika OK ditekan
      }

      if (okButton == LOW) {
        while (digitalRead(OK_PIN) == LOW)
          ;

        // Remove the selected card from Preferences
        String key = "NFC_UID_" + String(selectedCard - 1);
        NFCPreferences.remove(key.c_str());

        // Hapus kartu yang dipilih dari daftar
        String deletedUID = NFCallowedUIDs[selectedCard - 1];
        for (int i = selectedCard - 1; i < NFCAllowedCards - 1; i++) {
          NFCallowedUIDs[i] = NFCallowedUIDs[i + 1];
        }
        NFCAllowedCards--;

        if (NFCAllowedCards <= 0) {
          NFCPreferences.clear();
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("NFC Deleted!");
        lcd.setCursor(0, 1);
        lcd.print("UID: " + deletedUID);
        delay(1000);

        // Save the changes to Preferences
        saveSettings();
        loadSettings();

        break;  // Keluar dari loop jika OK ditekan
      }
    }
  }
  inSubMenu = true;
  displaySubMenuNFC();
}
void executeNFCTagView() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("List NFCs...");
  delay(1000);

  // Tampilkan daftar UID kartu yang sudah disimpan
  if (NFCAllowedCards <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("NFC not found!");
    delay(1000);
  } else {
    displayListNFC();
    inListMenu = true;
    while (inListMenu) {
      // Baca nilai tombol CHANGE dan OK
      int changeButton = digitalRead(CHANGE_PIN);
      int backButton = digitalRead(BACK_PIN);

      if (changeButton == LOW) {
        while (digitalRead(CHANGE_PIN) == LOW)
          ;
        selectedCard++;
        if (selectedCard > NFCAllowedCards) {
          selectedCard = 1;
        }
        displayListNFC();
      }

      if (backButton == LOW) {
        while (digitalRead(BACK_PIN) == LOW)
          ;

        if (NFCAllowedCards <= 0) {
          NFCPreferences.clear();
        }
        lcd.clear();
        break;  // Keluar dari loop jika OK ditekan
      }
    }
  }
  inSubMenu = true;
  displaySubMenuNFC();
}
void displayListNFC() {
  lcd.clear();
  switch (selectedCard) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(NFCallowedUIDs[selectedCard - 1]);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(NFCallowedUIDs[selectedCard - 1]);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(selectedCard);
      lcd.print(". Card UID:");
      lcd.setCursor(0, 1);
      lcd.print(NFCallowedUIDs[selectedCard - 1]);
      break;
  }
}

// Preferences
void saveSettings() {
  // End Preferences to save the changes
  NFCPreferences.end();
  preferences.end();
}
void loadSettings() {
  // Begin Preferences to load the settings
  preferences.begin("cardSaved", false);
  NFCPreferences.begin("NFCSaved", false);
}
