#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte card_ID[7];
byte Name1[4] = {0xBF, 0x48, 0x8E, 0x1F};
byte Name2[4] = {0x8D, 0xEE, 0x08, 0x49};
byte Name3[4] = {0xC3, 0x6A, 0x09, 0x49};
byte Name4[4] = {0xB6, 0xD1, 0x08, 0x49};
byte Name5[4] = {0x02, 0xCD, 0x08, 0x49};
byte Name6[4] = {0xE5, 0x85, 0x0C, 0x81};

int NumbCard[6] = {0};
int j = -1;
String Name;
String Number;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Scan ID card");

  // Initialize PLX-DAQ with separate date and time columns
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Name,Number,Date,Time");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    card_ID[i] = mfrc522.uid.uidByte[i];
  }

  if (compareUID(card_ID, Name1)) {
    Name = "RAJATH HM"; Number = "22EC077"; j = 0;
  } else if (compareUID(card_ID, Name2)) {
    Name = "SHASHIDHAR"; Number = "22EC090"; j = 1;
  } else if (compareUID(card_ID, Name3)) {
    Name = "RAKSHITH"; Number = "22EC080"; j = 2;
  } else if (compareUID(card_ID, Name4)) {
    Name = "SAGAR N"; Number = "22EC085"; j = 3;
  } else if (compareUID(card_ID, Name5)) {
    Name = "CHIDU"; Number = "22EC015"; j = 4;
  } else if (compareUID(card_ID, Name6)) {
    Name = "CHIDU"; Number = "22EC015"; j = 5;
  }

  if (j != -1 && NumbCard[j] == 0) {
    NumbCard[j] = 1;
    
    // Send data with DATE and TIME commands for PLX-DAQ
    Serial.print("DATA,");
    Serial.print(Name);
    Serial.print(",");
    Serial.print(Number);
    Serial.print(",");
    Serial.print("DATE"); // PLX-DAQ will replace DATE with current date
    Serial.print(",");
    Serial.print("TIME"); // PLX-DAQ will replace TIME with current time
    Serial.println();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(Name);
    lcd.setCursor(0, 1);
    lcd.print(Number);
    delay(2000);
  } 
  else if (j != -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Already Exist");
    delay(2000);
  }
  
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Scan ID card");
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

bool compareUID(byte cardID[7], byte predefinedUID[4]) {
  for (byte i = 0; i < 4; i++) {
    if (cardID[i] != predefinedUID[i]) {
      return false;
    }
  }
  return true;
}
