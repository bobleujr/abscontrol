#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity
 
const int sensorA = 2; 
const int sensorB = 3;

unsigned int rpmA, rpmB;     // rpm reading
volatile byte pulsesA, pulsesB;  // number of pulses
unsigned long timeold; 
// The number of pulses per revolution
// depends on your index disc!!
unsigned int pulsesperturn = 20;

 void counterA()
 {
    //Update count
      pulsesA++;
      
 }

void counterB()
 {
    //Update count
      pulsesB++;
 }
 
void setup()
{
    //LCD CONFIG
    lcd.begin(16,2);
    
    
    //SPEED SENSOR CONFIG
    Serial.begin(9600);
    //Use statusPin to flash along with interrupts
    pinMode(sensorA, INPUT);
    pinMode(sensorB, INPUT);
    //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
    //Triggers on FALLING (change from HIGH to LOW)
    attachInterrupt(0, counterA, FALLING);
    attachInterrupt(1, counterB, FALLING);
    // Initialize
    pulsesA = 0;
    rpmA = 0;
    pulsesB = 0;
    rpmB = 0;
    timeold = 0;
    
}
void loop()
{
   
  // delay before next reading:
  /* delay(1000);
   lcd.clear();
   lcd.write(analogRead(sensorA));
   //Sensor B
   lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Leitura");
    lcd.setCursor(0, 1);
    lcd.print(analogRead(sensorA));
    */
    
   if (millis() - timeold >= 1000){  /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
 
      //Don't process interrupts during calculations
      detachInterrupt(0);
      detachInterrupt(1);
      //Note that this would be 60*1000/(millis() - timeold)*pulses if the interrupt
      //happened once per revolution
      rpmA = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulsesA;
      rpmB = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulsesB;
      
      timeold = millis();
      pulsesA = 0;
      pulsesB = 0;
   
   
     
     lcd.clear();
     
     //Sensor B
     lcd.backlight();
     lcd.setCursor(0, 0);
     lcd.print("RPMA = "+rpmA);
     lcd.setCursor(0, 1);
     lcd.print("RPMA = "+rpmB);
     //Restart the interrupt processing
     attachInterrupt(0, counterA, FALLING);
     attachInterrupt(1, counterB, FALLING);
   } 
   
  
}
