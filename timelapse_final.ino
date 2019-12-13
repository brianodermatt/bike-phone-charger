#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>            
// ON Arduino : GND of camera and SD, 5V of camera and SD
// TX of camera on 2, RX of camera on 3
// CS(pin 4 on SD board) on 10, MOSI on 11, MISO on 12, SCK on 13

#define chipSelect 10

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(2, 3);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

//==============================================================================
void setup() {
  if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
  Serial.begin(9600);
  SD.begin(chipSelect);
}

void loop() {
  cam.begin();
  for (int i = 0; i < 20; i++){
    cam.setImageSize(VC0706_160x120);
  }
  cam.takePicture();
  // Create an image with the name IMAGExx.JPG
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for (int i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }
  // Open the file for writing
  File imgFile = SD.open(filename, FILE_WRITE);

  // Get the size of the image (frame) taken  
  uint16_t jpglen = cam.frameLength();

  int32_t time = millis();
  pinMode(8, OUTPUT);
  // Read all the data up to # bytes!
  while (jpglen > 0) {
    // read 32 bytes at a time;
    uint8_t *buffer;
    uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
    buffer = cam.readPicture(bytesToRead);
    imgFile.write(buffer, bytesToRead);
    jpglen -= bytesToRead;
  }
  imgFile.close();
  time = millis() - time;
  delay(10);
}
