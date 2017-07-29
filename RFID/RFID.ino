#include<string.h>

#include "MFRC522.h"      //RC522 Library
#include <SPI.h>          //SPI library

#define USE_SERIAL Serial


void dump_byte_array(byte *buffer, byte bufferSize);                    //Function declaration
#define RST_PIN 2 // RST‐PIN for RC522 ‐ RFID ‐ SPI ‐ Modul GPIO15        
#define SS_PIN 105 // SDA‐PIN for RC522 ‐ RFID ‐ SPI ‐ Modul GPIO2
MFRC522 mfrc522(SS_PIN, RST_PIN); 

String Result=" ";
String ch;
long count = 0;
int id_tag;


void setup() 
{
  Serial.begin(115200);       // Initialize serial communications
  SPI.begin();                // Initialize SPI bus
  Serial.println("SPI initialized");
  mfrc522.PCD_Init();         // Initialize MFRC522
  Serial.println("PCD Initialized");
  for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
}

void loop() 
{
//   Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    delay(50);
    return;
  }
//   Function to select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial())
    {
      delay(50);
      return;
    }
//   Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);         //Function calling(uidByte is an array member in uid structure,size is another member in uid structure,size:no of bytes in uid here, it is 4)
  Serial.println();                                               

  delay(1000);
}



 //Helper routine to dump a byte array as hex values to Serial

  void dump_byte_array(byte *buffer, byte bufferSize)         //Function defnition(*buffer-to pass array into a function we should pass pointer)
  {
    String res=" ";                                           //declaring empty string
    for (byte i = 0; i < bufferSize; i++) 
    {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], DEC);
      int n=(int)buffer[i];                                 //converting byte into an integer 
      String s=String(n);                                   //converting an integer into string
      res=String(res+s);
    }

    
    Serial.println();
    Serial.print("string form:");
    Serial.print(res);
    if(res == " 23831241197")
    {
        id_tag = 1;
        count++;
        Serial.println("ID = 1");
    }
    else if(res == " 2101284638")
    {
        id_tag = 2;
        count++;
        Serial.println("ID = 2");
    }
    else if(res == " 137224221102")
    {
        id_tag = 3;
        count++;
        if(count > 20)
        {
            count = 0;
            Serial.println("ID = 3");
        }
            
    }
    else if(res == " 105870101")
    {
        id_tag = 4;
        count++;
        Serial.println("ID = 4");
    }
    else if(res == " 185139236102")
    {
        id_tag = 5;
        count++;
        Serial.println("ID = 5");
    }

    String s=String(13);
    res=String(s+String("ram"));
    Serial.println();
    Serial.print(res);
    String a=String(14);
    Serial.println();
    res=String(s+String("ram")+a);
    Serial.print(res);
    
    
  }

