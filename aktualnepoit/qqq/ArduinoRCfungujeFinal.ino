int step= 0;
int volt = 0;
int pin_analog = A1,
i = 0, 
pin_pwm = 9;
double w = 2;
float y = 0, 
output = 0, 
eLast = 0, 
eCum = 0;
unsigned long now = 0, 
lastTime = 0, 
timeChange = 0;
int a=1024; 
int b=5; 
double c=1.16;




void setup()
{
  pinMode(pin_pwm, OUTPUT);
  Serial.begin(9600);

w=w*a*c/b;
 pinMode(0,OUTPUT);
 pinMode(1,OUTPUT);
 pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
}





void loop()
{
w=analogRead(A0);


//w=w*b*c/a;
  for (i=0;i<100;i++) {
    y=analogRead(pin_analog);
   output = ComputePID(w, y);
   output=map(output, 0, 1023, 0, 255);
    analogWrite(pin_pwm, output);
y=y*b/a;


   delay(10);
step++;


 if (y > 4.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
digitalWrite(2, HIGH);
digitalWrite(11, HIGH);
digitalWrite(11, HIGH);
}
 else if (y > 4 && y <= 4.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
digitalWrite(2, HIGH);
digitalWrite(11, HIGH);
digitalWrite(0, LOW);
}
 else if (y > 3.5 && y <= 4)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
digitalWrite(2, HIGH);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 3 && y <= 3.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 2.5 && y <= 3)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 2 && y <= 2.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 1.5 && y <= 2)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 1 && y <= 1.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, HIGH);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y > 0.5 && y <= 1)
{
digitalWrite(10, HIGH);
digitalWrite(8, HIGH);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}
 else if (y >= 0 && y <= 0.5)
{
digitalWrite(10, HIGH);
digitalWrite(8, LOW);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(1, LOW);
digitalWrite(0, LOW);
digitalWrite(11, LOW);
}












  }
     Serial.println(y);

}
double ComputePID(double wish, double input){
  double Kp = 10, Ki = 0.1, Kd = 0, out = 0, e = 0;
  now = millis(); 
  timeChange = (now - lastTime);
  e = wish - input;
  eCum += e * timeChange;
  if(eCum>1000){
    eCum=1000;
  }
  if(eCum<-1000){
    eCum=-1000;
  }
  out = (Kp*e)+(Ki*eCum)+(Kd*((e-eLast)/timeChange));
  eLast = e;
  lastTime = now;
  if(out>1023){
    out=1023;
  }
  if(out<0){
    out=0;
  }
  return out;
}
