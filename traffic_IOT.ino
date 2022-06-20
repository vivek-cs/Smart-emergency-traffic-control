#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
#define RST_PIN 9
#define buzzer 7
MFRC522 mfrc522(SS_PIN, RST_PIN);

int Lane1[] = {A0,A1,A2}; // Lane 1 Red, Yellow and Green
int Lane2[] = {A3,A4,A5};// Lane 2 Red, Yellow and Green
int Lane3[] = {7,6,5};// Lane 3 Red, Yellow and Green
int Lane4[] = {4,3,2};// Lane 4 Red, Yellow and Green

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  for (int i = 0; i < 3; i++)
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(Lane1[i], LOW); 
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
  
}

void loop() 
{
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], LOW);
  delay(7000);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane2[2], LOW);
  delay(1000);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(7000);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane2[2], LOW);
  delay(1000);
  
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
 if (content.substring(1) == "50 3A CE 30") //change here the UID of the card/cards that you want to give access
 {
    Serial.println("Authorized access");
    Serial.println();
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(7000);
  sms();
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane2[2], LOW);
  delay(1000);
}
}

void sms()
{
  Serial.begin(9600); //Baud rate of the GSM/GPRS Module
  Serial.print("\r");
  delay(1000);
  //Serial.print(“AT+CMGF=1\r”);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+919491359459\"\r");    
  delay(1000);
  Serial.print("Ambulance current location: https://maps.app.goo.gl/vW6AtDcFaERak4nF8");   
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
}
