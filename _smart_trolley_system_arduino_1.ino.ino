#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// LCD & RFID
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Buttons & Buzzer
const int remove_button = 2;
const int add_button = 3;
const int reset_button = 4;
const int buzzer_Pin = 5;

// Item Structure
struct Item {
  String name;
  String uid;
  int price;
};

// Item Database
const int number_of_item = 4;
const Item item_list[number_of_item] = {
  {"Tata salt",   "9F FC 54 1C", 100},
  {"Milk Powder", "04 EB BC A3", 50},
  {"Bournvita",   "13 1F A3 0D", 20},
  {"Ball_Pen",    "E3 68 DC 12", 10},
};

int bill_amount = 0;
bool add_mode = true;

void beep() {
  digitalWrite(buzzer_Pin, HIGH);
  delay(200);
  digitalWrite(buzzer_Pin, LOW);
}

void displayMessage(String line1, String line2, int d = 2000) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(line1);
  lcd.setCursor(0, 1); lcd.print(line2);
  delay(d);
}

void setup() {
  pinMode(remove_button, INPUT);
  pinMode(add_button, INPUT);
  pinMode(reset_button, INPUT);
  pinMode(buzzer_Pin, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();
  displayMessage("Smart Trolley", "Billing System");
  displayMessage("Start purchasing", "your items", 1500);

  Serial.println("Ready to scan RFID tags...");
}

void loop() {
  // Button Handling
  if (digitalRead(remove_button)) {
    add_mode = false;
    displayMessage("Mode:", "Remove Items");
  }
  if (digitalRead(add_button)) {
    add_mode = true;
    displayMessage("Mode:", "Add Items");
  }
  if (digitalRead(reset_button)) {
    bill_amount = 0;
    displayMessage("Trolley Reset", "Bill cleared");
  }

  // RFID Scan
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  // Read UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uid += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uid += " ";
  }
  uid.toUpperCase();
  Serial.println("Scanned UID: " + uid);

  // Check if UID matches any item
  bool item_found = false;
  for (int i = 0; i < number_of_item; i++) {
    if (uid.equalsIgnoreCase(item_list[i].uid)) {
      item_found = true;

      if (add_mode) {
        bill_amount += item_list[i].price;
        beep();
        displayMessage(item_list[i].name, String(item_list[i].price) + " Rs");
      } else {
        bill_amount -= item_list[i].price;
        if (bill_amount < 0) bill_amount = 0;
        beep();
        displayMessage(item_list[i].name, "Removed");
      }
      break;
    }
  }

  if (!item_found) {
    displayMessage("Unknown Item", "Not in database");
  }

  // Display Total Bill
  displayMessage("Total Bill:", String(bill_amount) + " Rs", 1500);
}

