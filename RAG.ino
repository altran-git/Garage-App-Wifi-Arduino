/*
 * Socket App
 *
 * A simple socket application example using the WiShield 1.0
 */

#include <WiShield.h>
#include <MsTimer2.h>
#include "uip.h"

//EMAIL//extern "C" unsigned char smtp_send();

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {192,168,1,80};	// IP address of WiShield
unsigned char gateway_ip[] = {192,168,1,1};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {"net2g"};		// max 32 bytes

unsigned char security_type = 3;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"trakmasterrs"};	// max 64 characters

// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = {
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
};

// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
char incoming[50];
int doorStatus;
int sendData = 0;
//EMAIL//int sendEmail = 0;

//EMAIL//void email() {
  //EMAIL//Serial.println("Sending SMTP...");
  //EMAIL//delay(1000);
  //EMAIL//if(digitalRead(4) == 0)
  //EMAIL//{
    //EMAIL//smtp_send();
  //EMAIL//}
//EMAIL//}

extern "C" {
  // Define function ser_print() declared in socketapp.c
  void ser_print(char* buffer) {
    Serial.print(buffer);
  }
}

void setup()
{
  WiFi.init();
  //Serial.begin(9600);
  //Serial.println("Ready...");
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  //EMAIL//attachInterrupt(1, email, FALLING);
}

void loop()
{
  WiFi.run();
    
  if('\0' != incoming[0]) {
      if(strcmp(incoming, "#$13vdY%1$@&8Ggk@3!") == 0)
      {
        //Send Pulse Signal to Relay
        //Serial.println(incoming);
        digitalWrite(5, HIGH);
        delay(500);  
        digitalWrite(5, LOW);    
      }
      else if(strcmp(incoming, "STATUS") == 0)
      {
        //Request for Garage Door Status
        //Serial.println(incoming);
        doorStatus = digitalRead(4);
        sendData = 1;
      }
      incoming[0] = '\0';
  }
  
  //check pin 9 to see if unit disconnects
  if(digitalRead(9) == 0){
    WiFi.init();
  }
}
