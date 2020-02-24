/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 7;
const int echoPin = 6;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  pinMode(9, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.clear();
  Serial.begin(9600);
}
int distance(int nomeasurments=20)//ret distance to object in front olf the toilet
{
  const int trigPin = 7;
  const int echoPin = 6;
  long duration;
  long distanceSum=0;
  for (int i=0;i<nomeasurments;i++)//we take avg of series of measurments to minimaze influence of false data
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceSum+=duration;
    lcd.setCursor(11, 1);
    lcd.print(duration*0.034/2);
    //if (duration*0.034/2>80){delay(1000);};
    lcd.print("      ");
  }
  
  return(distanceSum*0.034/2/nomeasurments);
}

//set up measurments
//lcd.print("Let's begun setup measurments \n If you'd like to skip press button");
//delay(1000);
//set up to be added 



int dist;
int trigtime=5000;//sec
int i, i1;
int state;
unsigned long st,ct;
int threshold=48;
float mean, var;
bool state1;
int tlength=50;
int standlength=30;

void loop() {
  lcd.setCursor(0, 0);  lcd.print("standby");
  while(!digitalRead(9)){};
  lcd.clear();
  lcd.print("start");
  st=millis();
  ct=st;
  state1=0;
  state=0;
  
  while((ct-st)<4000 ){
    ct=millis();
    Serial.print(ct-st);
      Serial.print("\n");
    if (distance(50)<(tlength+standlength))
    {state1=1;};}
  
  if(state1){
    i=0;
    i1=0;//количество раз растояние больше чем нужно поменять
    mean=0;
    var=0;
    lcd.clear();
    lcd.print("measure");
    st=millis();
    
    while ((i1<=3) && (i<200)){//!поменять добавить???может не надо количество непрвильных раз
      dist=distance();
      //lcd.setCursor(7, 1);
      //lcd.print(dist);
      if (dist>(tlength+standlength)){i1++;};
      Serial.print(dist);Serial.print(";");Serial.print(i);
      Serial.print("\n");
      //Serial.println(dist);
      mean+=dist;
      var+=dist*dist;
      i++;     
     //lcd.setCursor(0, 0);
     //lcd.print(i);
    }
    
    ct=millis();  
    mean/=i;
    var/=i;  
    var-=mean*mean;  Serial.print(ct-st); Serial.print("; ");Serial.print(mean);Serial.print(var);Serial.print(";state ");  
    
    if ((i>50)&&(mean<=(tlength+standlength))){
     if(mean<0,75*tlength){
       i1=0;
       while(i1<4){if(((millis()-st)/1000)%2==0){if(distance(30)>tlength){i1++; };};};
       ct=millis();
       Serial.print(ct);Serial.print(";st ");
      Serial.print(st);
      Serial.print("\n");
       lcd.setCursor(11, 1);
       lcd.print(ct-st);
    //if (duration*0.034/2>80){delay(1000);};
       lcd.print("      ");
       delay(5000);
       if((ct-st)<45000){
        state=1;}
       else {
        state=2;}}
      else{
       if (var<threshold){
        state=1;}
       else {
        state=3;}}
    }
  }
  Serial.print(state);Serial.print("--------------\n");
  lcd.clear();lcd.setCursor(0, 1);  lcd.print("state"); lcd.print(state);
  delay(3000);
  
  
 /* i=0;
  mean=0;
  var=0;
  st=millis();
  while ((distance()<(50+20)) && (i<50)){//поменять добавить && послед раcстоение >
   dist[i]=distance();
   Serial.print(dist[i]);
   Serial.print("\n");
   //Serial.println(dist[i]);
   mean+=dist[i];
   var+=dist[i]*dist[i];
   
   i++;
   
   //lcd.setCursor(0, 0);
   //lcd.print(i);
  
  }
  ct=millis();
  
  mean/=i;
  var/=i;
  
  var-=mean*mean;
  Serial.print(mean);
  Serial.print(":");
  Serial.print(var);
  Serial.print("\n");
  lcd.setCursor(0, 0);
  lcd.print((ct-st)/1000);
  lcd.setCursor(0, 1);
  lcd.print(mean);
  lcd.print(":");lcd.print(var);
  lcd.print("       ");
  //lcd.print(mean);
  //lcd.print((mean.int())+":"+(var.int()));
  
  
  
  
  if (
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;

  delay(100);
  lcd.print("    ");
  Serial.print(digitalRead(9)*80);
  Serial.print(",");
  Serial.println(distanceCm);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(9) == HIGH) {
    // turn LED on:
    lcd.setCursor(0, 1);
    lcd.print("detected    ");
    lcd.setCursor(0, 0);
    lcd.print(distanceCm);
  } else {
    // turn LED off:
    lcd.setCursor(0, 1);
    lcd.print("not detected");
    lcd.setCursor(0, 0);
    lcd.print(distanceCm);
  }
  */
}
