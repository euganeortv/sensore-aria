#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_CCS811.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println("Inizializzazione del display fallita!");
    for(;;);
  }

   if(!ccs.begin()){
    Serial.println("Inizializzazione del sensore fallita!");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      display.clearDisplay();

      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("EUGANEORTV");

      display.setCursor(0, 20);
      display.print("CO2 ");
      display.print(ccs.geteCO2());
      display.println("ppm");

      display.setCursor(0, 40);
      display.print("VOC ");
      display.print(ccs.getTVOC());
      display.println("ppb");
      
      display.display(); 
    } else{
      Serial.println("Errore!");
      while(1);
    }
  }
  delay(500);
}
