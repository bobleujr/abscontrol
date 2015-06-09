const int sensorA = 2; 
const int sensorB = 3;

unsigned int rpmA, rpmB;     // rpm reading
volatile byte pulsesA, pulsesB;  // number of pulses
unsigned long timeold; 
// The number of pulses per revolution
// depends on your index disc!!
unsigned int pulsesperturn = 32;

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
    pulsesB = 0;q
    rpmB = 0;
    timeold = 0;
    
}
void loop()
{
    
   if (millis() - timeold >= 300){  /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
 
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
   
   

    Serial.print("RPM  A = ");
    Serial.println(rpmA,DEC);
    Serial.print("RPM B = ");
    Serial.println(rpmB,DEC);
     
     //Restart the interrupt processing
     attachInterrupt(0, counterA, FALLING);
     attachInterrupt(1, counterB, FALLING);
   } 
   
  
}
