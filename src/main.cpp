//open serial plotter in arduino application to see plots
#include <Arduino.h>
double y;
double x;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  x = 10*sin( 2.0*PI*( millis() / 5000.0 ) ); // update your variables like usual
  y = 10*cos( 2.0*PI*( millis() / 5000.0 ) ); 


  //to plot multiple values, need to serial print each and the final is serial.println
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);
  delay(20);
}