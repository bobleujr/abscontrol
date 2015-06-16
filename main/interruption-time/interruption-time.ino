const int sensorB = 3;

volatile byte pulsesB;  // number of pulses
// The number of pulses per revolution
// depends on your index disc!!
unsigned long lastInterruption;
unsigned long elapsedTime;

void counterB()
 {
    //Update count
      
      pulsesB++;
      unsigned long currentTime = micros();

      elapsedTime = currentTime - lastInterruption;
      Serial.println(elapsedTime, DEC);
      lastInterruption = micros();
        
      
 }
 
void setup()
{

    
    
    //SPEED SENSOR CONFIG
    Serial.begin(9600);
    //Use statusPin to flash along with interrupts
    pinMode(sensorB, INPUT);
    //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
    //Triggers on FALLING (change from HIGH to LOW)
    attachInterrupt(1, counterB, FALLING);
    // Initialize
    pulsesB = 0;
}
void loop()
{
  
  
}
