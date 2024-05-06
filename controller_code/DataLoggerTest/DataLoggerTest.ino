#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_PCF8523 rtc;

const int CS_PIN = 10;
const int SIGNAL_PIN = A7 ;
const int INT_PIN = 2 ;

String fileName = "data.log" ;

String data = "" ;
int dataRaw = 0 ;
volatile bool dataFlag = true ;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Initializing RTC
  Serial.print("Initializing RTC...") ;
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  Serial.println("RTC initiialized.") ;

  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, setting the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    //
    // Note: allow 2 seconds after inserting battery or applying external power
    // without battery before calling adjust(). This gives the PCF8523's
    // crystal oscillator time to stabilize. If you call adjust() very quickly
    // after the RTC is powered, lostPower() may still return true.
  }
  rtc.start();
  Serial.println("RTC Started") ;


  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(CS_PIN)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  //Log that the board has restarted
  data = rtc.now().timestamp() ;
  data += "\t" ;
  data += "Reboot: Lost power... Starting log" ;
  writeSD(data) ;

  //Attach an interrupt to the RTC timer
  pinMode(INT_PIN, INPUT_PULLUP) ;
  attachInterrupt(digitalPinToInterrupt(INT_PIN), rtcInterrupt, FALLING) ;

}

void loop() {

  //Read the data only at specified intervals
  if (dataFlag){
    dataFlag = false ;
    //Start a countdown timer until the next data logging
    rtc.enableCountdownTimer(PCF8523_FrequencyMinute, 1) ;

    //Always Start a log line with the time stamp
    data = rtc.now().timestamp() ;
    data += "\t" ;


    //Read in the useful data
    dataRaw = analogRead(SIGNAL_PIN) ;
    data += "Sound: " ;
    data += String(dataRaw) ;

    //Write a line to the csv file
    writeSD(data) ; 
  }

}

//Wrapper to write a string t othe SD card
void writeSD(String line){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(fileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(line);
    dataFile.close();
    // print to the serial port too:
    Serial.println(line);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  }
}

//RTC ISR to start the data logging
void rtcInterrupt(){
  dataFlag = true ;
}




