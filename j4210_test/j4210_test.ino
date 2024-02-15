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
Serial.begin(115200);
Serial.println("The Example does not support this MCU");
#endif

J4210U uhf(&UART2, 115200);

// void getMemoryContent(J4210U &uhf, ScanData *sd)
// {
// }

// void getTID(J4210U &uhf, ScanData *sd)
// {
//   cprintf(">>> getTID() STARTED:\n");
//   char epcnum[sd->epclen * 2];
//   bytes2hex(sd->EPCNUM, sd->epclen, epcnum);
//   cprintf("Getting TID for EPCNUM: %s\n", epcnum);

//   unsigned char tid[16];
//   unsigned char tidlen = 0;
//   if (!uhf.GetTID(sd->EPCNUM, sd->epclen, tid, &tidlen))
//   {
//     // uhf.printtag(i);
//     char str[32];
//     bytes2hex(sd->EPCNUM, sd->epclen, str);
//     cprintf("TID: %s\n", str);
//   }
//   else
//   {
//     cprintf("Failed to obtain TID.\n");
//   }
//   cprintf("getInventory() ENDED <<<\n");
// }

int getInventory(J4210U &uhf) {
  cprintf("\n>>> getInventory() STARTED:\n");
  int n = uhf.Inventory(false);
  cprintf("Found %d tags.\n", n);
  for (int i = 0; i < n; i++) {
    uhf.printtag(i);
  }
  cprintf("getInventory() ENDED <<<\n");
  return n;
}
ReaderInfo ri;
TagInfo ti;
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.

  Serial.begin(115200);  // for serial monitor
  UART2.begin(115200);   // Rx2, Tx2 pin for the Reader

  int n = getInventory(uhf);
  char str[32];
  for (int i = 0; i < n; i++) {
    ScanData *sd = uhf.GetResult(i);
    if (sd == 0)
      break;
    cprintf("Getting TID for tag %d\n", i);
    unsigned char tid[16];
    unsigned char tidlen = 0;
    // if(sd->EPCNUM)
    bytes2hex(sd->EPCNUM, sd->epclen, str);
    if (!strcmp("E2000019340901840570DDC1", str)) {
      Serial.printf("epcnum = %s found at index %d\n", str, i);
      if (uhf.GetTID(sd->EPCNUM, sd->epclen, tid, &tidlen)) {
        // uhf.printtag(i);
        bytes2hex(tid, tidlen, str);
        // bytes2hex(sd->EPCNUM, sd->epclen, str);
        uhf.GetTagInfo(tid, &ti);
        Serial.printf("tid %s, taginfo: chip %s\n", str, ti.chip);
        cprintf("TID: %s\n", str);
        // Serial.printf("epcnum = %s\n", str);
      }
    } else {
      Serial.printf("not found\n");
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // int n = uhf.Inventory(false);
  // for (int i = 0; i < n; i++)
  // {
  //   ScanData *sd = uhf.GetResult(i);
  //   if (sd == 0)
  //     break;
  //   char str[32];
  //   bytes2hex(sd->EPCNUM, sd->epclen, str);
  //   Serial.printf("EPC %2d is %s\n", i, str);
  // }

  // int n = getInventory(uhf);
  // for (int i = 0; i < n; i++)
  // {
  //   ScanData *sd = uhf.GetResult(i);
  //   if (sd == 0)
  //     break;
  //   cprintf("Getting TID for tag %d\n", i);
  //   unsigned char tid[16];
  //   unsigned char tidlen = 0;
  //   if (uhf.GetTID(sd->EPCNUM, sd->epclen, tid, &tidlen))
  //   {
  //     uhf.printtag(i);
  //     char str[32];
  //     bytes2hex(tid, tidlen, str);
  //     cprintf("TID: %s\n", str);
  //   }
  // }

  // uhf.GetSettings(&ri);
  // Serial.print(ri.BeepOn);

  delay(3000);
}
