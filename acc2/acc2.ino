
#include <Wire.h>
#include "BMA250.h"
#include "DSRTCLib.h"
#include <SD.h>
#include <SPI.h>

// Initialize shields
BMA250 accel;
DS1339 RTC = DS1339();

// RTC variable
char astr[20];
char tstr[20];


// SD card constants and variables
int fileID = 0;
char fname[] = "acc000.txt";
File myFile;
int SDpin = 10;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  // options: BMA250_range_16g, BMA250_range_8g, BMA250_range_4g, BMA250_range_2g
  // options: BMA250_update_time_64ms, BMA250_update_time_32ms, BMA250_update_time_16ms, BMA250_update_time_8ms, BMA250_update_time_4ms, BMA250_update_time_2ms, BMA250_update_time_1ms, BMA250_update_time_05ms
  // question: the BMA250 spec sheet says frequency
  accel.begin(BMA250_range_2g, BMA250_update_time_64ms);  //This sets up the BMA250 accelerometer
  RTC.start(); // ensure RTC oscillator is running, if not already
  pinMode(SDpin,OUTPUT);  // set up SD card
  if (!SD.begin(10)) {
    Serial.println(F("SDcard initialization failed!"));
    return;
  }
  Serial.println(F("SDcard initialization done."));
  // generate a uniq filename
  for (int i=0; i<=999; i++) {
    if (!SD.exists(fname)) {
      myFile = SD.open(fname,FILE_WRITE);
      myFile.close();
      break;
    }
    // if still in for loop, the increment file name
    fname[3] = i/100 + '0';
    fname[4] = (i%100)/10 + '0';
    fname[5] = i%10 + '0';
  }
  Serial.print(F("Using fname = "));
  Serial.println(fname);

}


void loop()
{
  accel.read();  //This function gets new data from the accelerometer
  sprintf(astr,"%03d %03d %03d",accel.X,accel.Y,accel.Z);
//  Serial.println((accel.rawTemp*0.5)+24.0,1);

  RTC.readTime();
  sprintf(tstr,"%04d%02d%02dT%02d%02d%02d",int(RTC.getYears()),int(RTC.getMonths()),int(RTC.getDays()),int(RTC.getHours()),int(RTC.getMinutes()),int(RTC.getSeconds()));

  // Write the same data to the SD card
  myFile = SD.open(fname, FILE_WRITE);
  myFile.print(RTC.date_to_epoch_seconds());
  myFile.print(" ");
  myFile.print(tstr);
  myFile.print(" ");
  myFile.print(millis());
  myFile.print(" ");
  
  myFile.println(astr);
  myFile.close();

  delay(100);  //We'll make sure we're over the 64ms update time set on the BMA250
}

