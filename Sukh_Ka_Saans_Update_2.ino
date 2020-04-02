

#include <LiquidCrystal.h>
#include <Servo.h>

//--------------------------

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//--------------------------



const int FASTEST_FREQUENCY = 45; // in "breaths per minute"
const int SLOWEST_FREQUENCY = 1; // in "breaths per minute"
const int SERVO_START = 0; // angle in degrees. Will correspond to "0" on the 0-500 volume range
const int SERVO_MAX = 180; // angle in degrees. Will correspond to "500" on the 0-500 volume range




Servo myservo;
int servopin (8);

char buffer[16]; //buffer for sprintf for LCD display.
unsigned long loopTimer = 0;
unsigned long breathStart = 0;
int loopPeriod = 50; // loop period in milliseconds; eg 100 = 10Hz

//--------------------------------------

void setup() {
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  lcd.begin(16, 2);
  lcd.print("Ventilator On");

  myservo.attach (servopin);
  myservo.write (SERVO_START);
  delay (1000);
  
  loopTimer = millis ();
  breathStart = loopTimer;
}



void loop() {
 
  unsigned long currentTime = millis();

  // this loop executes once every loopPeriod milliseconds
  if ( (currentTime - loopTimer) >= loopPeriod ) {
    loopTimer = currentTime;
    


    // read in potentiometer values
    int pot0 = analogRead (A0);
    int pot1 = analogRead (A1);

    // calculate values used for display
    int breathFrequency = map (pot0, 0, 1023, SLOWEST_FREQUENCY, FASTEST_FREQUENCY);
    int breathDepthDisplayValue = map (pot1, 0, 1023, 0, 500); // 0..500 scale used for display only. 

    // write the display values
    lcd.setCursor(0, 1);
    sprintf(buffer,"BPM:%2d  ",breathFrequency);
    lcd.print(buffer);

    lcd.setCursor(8, 12);
    sprintf(buffer,"VOL:%3d ",breathDepthDisplayValue);
    lcd.print(buffer);



    //calculate values used for setting values
    unsigned long breathLength = 60000 / breathFrequency; // length = period in milliseconds = 60000 / frequency
    //unsigned long breathLength = map (pot0, 0, 1023, 60000 / SLOWEST_FREQUENCY, 60000 / FASTEST_FREQUENCY); 
    unsigned long breathDepth = map (pot1, 0, 1023, SERVO_START, SERVO_MAX); // breathDepth measured in degrees for the servo. 



    //Check if we've started a new breath
    if ( (currentTime - breathStart) >= breathLength) {
      breathStart = currentTime;
    }


    //Work out how far we are through the current breath, then set the servo target accordingly. 
    float howFarThroughBreath = (currentTime - breathStart) / (float) breathLength; //0...1 scale for how far through the whole breath cycle we currently are,
    float targetDepthFactor; // 0...1 scale for how deep the "diaphragm" should currently be; equals 1.0 when howFarThroughBreath=0.5
    if (howFarThroughBreath >= 0.5) {
      //we're breathing out
      targetDepthFactor = (1.0 - howFarThroughBreath) * 2.0;
    } else {
      //we're breathing in
      targetDepthFactor = howFarThroughBreath * 2.0;
    }

    int servoTarget = (int) (targetDepthFactor * (breathDepth - SERVO_START) + 0.5);
    myservo.write (servoTarget);


  }


}
