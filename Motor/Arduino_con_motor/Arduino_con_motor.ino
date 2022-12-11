#include <Servo.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
//ULTRASONICO
int trigPin = 4;
int echoPin = 5;
int ledPin = 52;//LED1
//MOTORES
int leftMotorPin = 2; //left motor pin
int rightMotorPin = 3; //left motor pin
Servo leftMotor;
Servo rightMotor;
SoftwareSerial mibt(12,13);

void setup()
{
  
  //////////
  Serial.begin(9600); 
  Serial.println("Serialprendido");
  mibt.begin(38400);
  ///////////
  pinMode(leftMotorPin,OUTPUT);
  pinMode(rightMotorPin,OUTPUT);
 
 //PINES ULTRASONICO
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ///////
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);

}
void loop()
{
    if(mibt.available()){
  StaticJsonDocument<200> doc;
  Serial.println(mibt.readStringUntil('?'));
  DeserializationError error = deserializeJson(doc, mibt.readStringUntil('?'));
   int X= doc["x"];
   int Y= doc["y"];  
    if((X > 45 && Y > 5) && (X < 55 && Y < 45)){ //ARRIBA
       rightMotorControl(map(Y, 52, 100, 0 , -255));
      leftMotorControl(map(Y, 52, 100, 0 , 255));
        Serial.println("Arriba");
    }
    else if((X > 45 && Y < 95) && (X < 55 && Y > 55)){
      rightMotorControl(map(Y, 48, 0, 0 , 255));
      leftMotorControl(map(Y, 48, 0, 0 , -255));//abajo
      Serial.println("Abajo");
    }
    else if ((X > 55 && X < 95) && ( Y > 45 && Y < 55)) {//derecha
       rightMotorControl(map(Y, 48, 0, 0 , -255));
      leftMotorControl(0);
       Serial.println("Derecha");
    }
    else if((Y > 45 && X > 5) && (Y < 55 && X < 45)){ //izquierda
       rightMotorControl(0);
      leftMotorControl(map(Y, 52, 100, 0 , 255));
        Serial.println("IZQUIERDA");
    }
  
    else {
      leftMotorControl(0);  
      rightMotorControl(0);
      Serial.println("parar");
    }
  }
    if(Serial.available()){
    mibt.write(Serial.read());
  }

   ////////////SENSOR ULTRASONICO ->
  int duration, distance;
  digitalWrite (trigPin, HIGH);
  delay (100);
  digitalWrite (trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance = (duration/2) / 29.1;
    Serial.print("Sensor Ultrasonico UNO: ");
      Serial.print(distance);  
      Serial.print("cm");
      Serial.println();

  if (distance < 30) {  // Change the number for long or short distances.
    digitalWrite (ledPin, HIGH);
  } else {
    digitalWrite (ledPin, LOW);
  }
}

int leftMotorControl(int value){
  leftMotor.write(map(value,-100,100,1000,2000));
}

int rightMotorControl(int value){
  rightMotor.write(map(value,-100,100,1000,2000));
}

 // delay(1000);
  //leftMotorControl(-100);
 // rightMotorControl(-100);
  //digitalWrite(13,LOW);
  //delay(1000);
