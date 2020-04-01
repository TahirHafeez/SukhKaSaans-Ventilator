// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(7,8,9,10,11,12);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//int pos ;
int volum = A0; // Potentiometer one is attached for angle/volume
int rate = A1;  // Potentiometer two is attached for breath rate/delay
int volumeVal = 0 ;
//int startAngle = 0; // it will put servo on 0 angle at start

// Function to print volume and breath rate on lcd display

void show_on_lcd(int volum, int rate ){
 int rev = 30 ;
 int newrev = analogRead(rate)/34 ;
 int fin = rev - newrev ;
lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
lcd.print("Volume : "); // Prints Sensor Val: to LCD
lcd.print(analogRead(volum)/2); // Prints value of potentio 1 to LCD
lcd.setCursor(0,1); // Sets the cursor to col 0 and row 1
lcd.print("Interval : "); // Prints Sensor Val: to LCD
lcd.print(fin); // Prints value on Potentio 2 to LCD

}

void setup()
{
  Serial.begin(9600);
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
lcd.clear();

pinMode(volum, INPUT);
pinMode(rate, INPUT);
// I attached servo motor to pin 4 on arduino
myservo.attach(8);

}

void loop()
{

int pos;  
volumeVal = analogRead(volum); // reads the value of the potentiometer (value between 0 and 1023)
volumeVal = map(volumeVal, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
myservo.write(volumeVal);

int pot_b_rate = analogRead(rate);

int b_rate = pot_b_rate / 34 ;

int vol_limit = (analogRead(volum))/6;

  for(pos = 0; pos <= vol_limit; pos += 1){
  myservo.write(pos);
  show_on_lcd(volum, rate);
  delay(b_rate);
  } 
  for(pos = vol_limit; pos >= 0; pos -= 1){                       
  myservo.write(pos);
  show_on_lcd(volum, rate);
  delay(b_rate);
  
  } 

    

}
