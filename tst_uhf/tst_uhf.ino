/**
 * J4210U UHF Reader/Writer demo.
 *
 * @author: Ejaz Jamil
*/

#include <Arduino.h>
#include "J4210U.h"

#if defined(__AVR_ATmega2560__) || defined(ESP32)
#define UART2 Serial2

#elif defined(__TM4C1294NCPDT__)
#define UART2 Serial7
#else
Serial.begin(9600);
Serial.println("The Example does not support this MCU");
#endif

J4210U uhf(&UART2, 57600);
ReaderInfo ri;
void getMemoryContent(J4210U &uhf, ScanData *sd) {
}

void getTID(J4210U &uhf, ScanData *sd) {
  cprintf(">>> getTID() STARTED:\n");
  char epcnum[sd->epclen * 2];
  bytes2hex(sd->EPCNUM, sd->epclen, epcnum);
  cprintf("Getting TID for EPCNUM: %s\n", epcnum);

  unsigned char tid[16];
  unsigned char tidlen = 0;
  if (!uhf.GetTID(sd->EPCNUM, sd->epclen, tid, &tidlen)) {
    //uhf.printtag(i);
    char str[32];
    bytes2hex(sd->EPCNUM, sd->epclen, str);
    cprintf("TID: %s\n", str);
  } else {
    cprintf("Failed to obtain TID.\n");
  }
  cprintf("getInventory() ENDED <<<\n");
}

void getTagInfo(J4210U &uhf, ScanData *sd) {
}

int getInventory(J4210U &uhf) {
  cprintf("\n>>> getInventory() STARTED:\n");
  // ReaderInfo ri;
  // uhf.GetSettings(&ri);
  // uhf.printsettings(&ri);

  // ri.ScanTime = 200;
  // ri.BeepOn = 0;
  // if (!uhf.SetSettings(&ri)) {
  //   cprintf("Failed to set settings.\n");
  // } else {
  //   uhf.GetSettings(&ri);
  //   uhf.printsettings(&ri);
  // }
  int n = uhf.Inventory(false);
  cprintf("Found %d tags.\n", n);
  for (int i = 0; i < n; i++) {
    uhf.printtag(i);
  }
  cprintf("getInventory() ENDED <<<\n");
  return n;
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  // pinMode(22, OUTPUT);
  // digitalWrite(22, HIGH);
  Serial.begin(115200);  // for serial monitor
  UART2.begin(57600);    //Rx2, Tx2 pin for the Reader

  int n = getInventory(uhf);
  for (int i = 0; i < n; i++) {
    ScanData *sd = uhf.GetResult(i);
    if (sd == 0)
      break;
    cprintf("Getting TID for tag %d\n", i);
    unsigned char tid[16];
    unsigned char tidlen = 0;
    if (uhf.GetTID(sd->EPCNUM, sd->epclen, tid, &tidlen)) {
      uhf.printtag(i);
      char str[32];
      bytes2hex(tid, tidlen, str);
      cprintf("TID: %s\n", str);
    }
  }
  uhf.GetSettings(&ri);
  Serial.print(ri.BeepOn);

  ri.BeepOn = 1;
  ri.Power = 26;
  uhf.SetSettings(&ri);
}

// the loop routine runs over and over again forever:
void loop() {


  uhf.GetSettings(&ri);
  Serial.print(ri.BeepOn);
  int n = getInventory(uhf);
  uhf.GetSettings(&ri);
  Serial.println(n);
  delay(3000);
}
