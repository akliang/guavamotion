
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>

// CONFIG:
// SD-CS pin to digital10
// push button (active high) to digital7

// SD card constants and variables
int fileID = 0;
char fname[] = "acc000.txt";
File myFile;
int SDpin = 10;

// sensor constants and variables
const int ax = A0;
const int ay = A1;
const int az = A2;
int rx=0;
int ry=0;
int rz=0;

// pushbutton for stop
int breakpin = 7;

// RTC variables
RTC_DS1307 rtc;


void setup() {
  Serial.begin(9600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  
  Serial.print("Initializing SD card..");
  pinMode(SDpin,OUTPUT);
  
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  pinMode(breakpin, INPUT);
  
  // generate a uniq filename
  for (int i=0; i<=999; i++) {
    if (!SD.exists(fname)) {
      myFile = SD.open(fname,FILE_WRITE);
      myFile.close();
      break;
    }
    // if still in for loop, the increment file name
    fname[3] = i/100 + '0';
    fname[4] = i/10 + '0';
    fname[5] = i%10 + '0';
  }
  Serial.print("Using fname = ");
  Serial.println(fname);
  
  
  
  
  
}

void loop() {
  
  DateTime now = rtc.now();

  //analogReference(EXTERNAL);
  
  if (digitalRead(breakpin)==LOW) {
    rx = analogRead(ax);
    ry = analogRead(ay);
    rz = analogRead(az);
    
    Serial.print(now.unixtime());
    Serial.print(" ");
    Serial.print(now.year(), DEC);
    Serial.print(now.month(), DEC);
    Serial.print(now.day(), DEC);
    Serial.print("T");
    Serial.print(now.hour(), DEC);
    Serial.print(now.minute(), DEC);
    Serial.print(now.second(), DEC);
    Serial.print(" ");
    Serial.print(millis());
    Serial.print(" ");
    
    Serial.print("Xdir=");
    Serial.print(rx);
    Serial.print(" ");
    Serial.print("Ydir=");
    Serial.print(ry);
    Serial.print(" ");
    Serial.print("Zdir=");
    Serial.println(rz);
    
    // Write the same data to the SD card
    myFile = SD.open(fname, FILE_WRITE);
    myFile.print(now.unixtime());
    myFile.print(" ");
    myFile.print(now.year(), DEC);
    myFile.print(now.month(), DEC);
    myFile.print(now.day(), DEC);
    myFile.print("T");
    myFile.print(now.hour(), DEC);
    myFile.print(now.minute(), DEC);
    myFile.print(now.second(), DEC);
    myFile.print(" ");
    myFile.print(millis());
    myFile.print(" ");
    
    myFile.print(rx);
    myFile.print(" ");
    myFile.print(ry);
    myFile.print(" ");
    myFile.println(rz);
    myFile.close();
    
    delay(20);
  } else {
    exit(0);
  }
  
}
