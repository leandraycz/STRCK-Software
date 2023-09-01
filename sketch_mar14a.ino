//Podporovaný hardware:
//Lafvin Smart Turtle Robot Car kit

//Vyžaduje:
//import souboru HC-SR06.zip přes Sketch -> Include Library -> Add .ZIP library z orignálního CD dodávaného k hardwaru.
//import souboru IRremote.zip přes Sketch -> Include Library -> Add .ZIP library z orignálního CD dodávaného k hardwaru.

//Import knihoven
#include <Servo.h> //Import knihovny pro servo
#include "SR04.h" //Import knihovny pro ultrasonický sensor
#include <IRremote.h> //Import knihovny pro IR receiver

//Deklarace pinout
int SERVO_PIN = 6;  //pin servo motoru
int TRIGGER_PIN = A1;  //pin ultrasonického senzoru (trigger)
int ECHO_PIN = A0; //pin ultrasonického sensoru (echo)
int IR_RECEIVER_PIN = 3; //pin IR příjímače
int MOTOR_PIN_1 = 12;   //motor pinout
int MOTOR_PIN_2 = 11;   //
int MOTOR_PIN_3 = 10;   //
int MOTOR_PIN_4 = 9;    //motor pinout
int LEFT_SENSOR_PIN = 2;  //pin levého line tracking sensoru
int MIDDLE_SENSOR_PIN = 4;  //pin prostředního line tracking sensoru
int RIGHT_SENSOR_PIN = 5; //pin pravého line tracking sensoru

// Deklace proměnných 
String input;   //vstup do uživatele
int servoPosition = 90; //Pozice serva
Servo servo;
SR04 UltraSonic = SR04(ECHO_PIN, TRIGGER_PIN);
IRrecv IR_Receiver(IR_RECEIVER_PIN);
decode_results results;  
String lastIRReceived;
String mode = "1";
unsigned char SL;        //state of left sensor
unsigned char SM;        //state of middle sensor
unsigned char SR;        //state of right sensor

//Deklarace ovladače
#define IR_UP 0x00ff629d  //šipka nahoru
#define IR_LEFT 0x00ff22dd  //šipka doleva
#define IR_RIGHT 0x00ffc23d  //šipka doprava
#define IR_DOWN 0x00ffa857  //šipka dolů
#define IR_OK 0x00ff02fd  //tlačítko OK
#define IR_1 0x00ff6897  //tlačítko 1
#define IR_2 0x00ff9867  //tlačítko 2
#define IR_3 0x00ffb04f  //tlačítko 3
#define IR_4 0x00ff30cf  //tlačítko 4
#define IR_5 0x00ff18e7  //tlačítko 5
#define IR_6 0x00ff7a85  //tlačítko 6
#define IR_7 0x00ff10ef  //tlačítko 7
#define IR_8 0x00ff38c7  //tlačítko 8
#define IR_9 0x00ff5aa5  //tlačítko 9
#define IR_0 0x00ff4ab5  //tlačítko 0
#define IR_STAR 0x00ff42bd  //tlačítko hvězda
#define IR_CROSS 0x00ff52ad  //tlačítko křížek

//Informace
String developerName = "Radim Krejcirik";
String year = "2023";
String version = "0.3 beta";

void MoveForward(){  //Posune želvu dopředu
  digitalWrite(MOTOR_PIN_1,HIGH);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,HIGH);
  delay(1000); 
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,LOW);  
}

void MoveBack(){  //Posune želvu dozadu
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,HIGH);
  digitalWrite(MOTOR_PIN_3,HIGH);
  digitalWrite(MOTOR_PIN_4,LOW);
  delay(1000);
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,LOW);    
}

void MoveLeft(){  //Posune želvu doleva 
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,HIGH);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,HIGH);
  delay(100);
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,LOW);
}

void MoveRight(){ //Posune želvu doprava
  digitalWrite(MOTOR_PIN_1,HIGH);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,HIGH);
  digitalWrite(MOTOR_PIN_4,LOW);
  delay(100);
  digitalWrite(MOTOR_PIN_1,LOW);
  digitalWrite(MOTOR_PIN_2,LOW);
  digitalWrite(MOTOR_PIN_3,LOW);
  digitalWrite(MOTOR_PIN_4,LOW);  
}

void setup(){ //Automaticky generovaná metoda SETUP
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(MIDDLE_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);

  Serial.begin(9600); //Nastavení rychlosti COM portu na 9600
  servo.attach(SERVO_PIN); //Nastaví servo na pin 6
  IR_Receiver.enableIRIn(); //Aktivuje IR receiver
  servo.write(servoPosition); //Posune servo na výcohzí pozici
  Serial.println("System started"); //Vypsání zprávy "System started"
}

void loop(){
  if(Serial.available()){
    input = Serial.readStringUntil('\n');

    if(input.equals("servo left")){ //Otočí servo doleva
      if(servoPosition < 180){
        servoPosition = servoPosition + 5;
        servo.write(servoPosition);
      }else{
        Serial.println("Servo maximal position reached");
      }
    }
    
    else if(input.equals("servo right")){ //Otočí servo doprava
      if(servoPosition > 0) {
        servoPosition = servoPosition - 5;
        servo.write(servoPosition);
      }else{
        Serial.println("Servo maximal position reached");
      }
    }
    
    else if(input.equals("servo position")){  //Vypíše pozici serva
      Serial.print("Servo position: ");
      Serial.println(servoPosition);
    }
    
    else if(input.equals("us distance")){ //Vypíše vzdálenost od ultrasonického senzoru
      Serial.print(UltraSonic.Distance());
      Serial.println(" cm");
    }
    
    else if(input.equals("move forward")){  //Posune želvu dopředu
      if(mode.equals("2")){
        MoveForward();
      }
      else{
        Serial.println("This feature is not available in this mode");
      }                                          
    } 
    
    else if(input.equals("move left")){ //Otoči želvu doleva
      if(mode.equals("2")){
        MoveLeft();
      }
      else{
        Serial.println("This feature is not available in this mode");
      }                       
    }  
    
    else if(input.equals("move right")){ //Otočí želvu doprava  
      if(mode.equals("2")){
        MoveRight();
      }
      else{
        Serial.println("This feature is not available in this mode");
      }                    
    }
       
    else if(input.equals("move back")){ //Posune želvu dozadu
      if(mode.equals("2")){
        MoveBack();
      }
      else{
        Serial.println("This feature is not available in this mode");
      }
              
    }
         
    else if(input.equals("ir last")){ //Vypíše poslední přijatou hodnotu z IR přijímače
      if (lastIRReceived.equals("")){
        Serial.println("No last IR received");        
      }else{
        Serial.println(lastIRReceived);
      }      
    }
                
    else if(input.equals("about")){ //Vypíše informace o firmwaru
      Serial.println("--- About firmware ---");
      Serial.print("Version: ");       
      Serial.println(version);  
      Serial.print("Developed by: ");
      Serial.println(developerName);
      Serial.print("Year: ");
      Serial.println(year);                
    }
     
    else if(input.equals("mode 1")){ //Změní herní mód na 1(IR ovládání serva)
      mode = 1;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,LOW); 
      Serial.println("Mode has been changed to 1");          
    } 
       
    else if(input.equals("mode 2")){ //Změní herní mód na 2(IR ovládání pohybu)
      mode = 2;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,LOW); 
      Serial.println("Mode has been changed to 2");          
    }

    else if(input.equals("mode 3")){ //Změní herní mód na 3(Line tracking)
      mode = 3;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,LOW); 
      Serial.println("Mode has been changed to 3");          
    }

    else if(input.equals("mode 4")){ //Změní herní mód na 4(Vyhýbání se překážkám doprava)
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,LOW);
      Serial.println("Mode has been changed to 4"); 
    }

    else if(input.equals("mode 5")){ //Mění herní mód na 5(Vyhýbání se překážkám doleva)
      mode = 5;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);  
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);  
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,LOW); 
      Serial.println("Mode has been changed to 5"); 
    }
    
    else if(input.equals("mode")){ //Vypíše aktuální herní mód
      Serial.print("Actual mode: ");
      Serial.println(mode);             
    }
    
    else if(input.equals("help")){ //Vypíše nápovědu
      Serial.println("--------------------------------------- help ----------------------------------------");
      Serial.println("servo left - move servo to left direction.            about - show about information.");
      Serial.println("servo right - move servo to right direction.          mode 1 - change mode to 1.");
      Serial.println("servo position - show servo position.                 mode 2 - change mode to 2.");
      Serial.println("us distance - show distance from ultrasonic sensor.   mode 3 - change mode to 3.");
      Serial.println("ir last - show last value received by IR receiver.    mode 4 - change mode to 4.");      
      Serial.println("move forward - moves the turtle forward.              mode 5 - change mode to 5."); 
      Serial.println("move left - moves the turtle left.                    mode - show actual mode.");
      Serial.println("move right - moves the turtle right.");     
      Serial.println("move back - moves the turtle back.");
      Serial.println("-------------------------------------------------------------------------------------");
    }
    
    else{ //V případě, že je zadán neznámý příkaz, vypíše "Invalid command"
      Serial.println("Invalid command");
    } 
  }
  if(IR_Receiver.decode(&results)){
    lastIRReceived = "";
    lastIRReceived = results.value;
    unsigned long Key;
    Key = results.value;     
    switch(Key){
      case IR_LEFT: //šipka doleva
        if(mode.equals("1")){          
          if(servoPosition > 0){
            servoPosition = servoPosition - 5;
            servo.write(servoPosition);
          }       
        }
        if(mode.equals("2")){            
          MoveLeft(); 
        }        
        break;
      case IR_RIGHT:  //Šipka doprava
        if(mode.equals("1")){
          if(servoPosition < 180){
            servoPosition = servoPosition + 5;
            servo.write(servoPosition);
          }
        }
        if(mode.equals("2")){
          MoveRight();
        }                      
        break; 
      case IR_DOWN: //Šipka dolů
        if(mode.equals("2")){          
          MoveForward();
        } 
        break;  
      case IR_UP: //Šipka nahoru                                             
        if(mode.equals("2")){          
          MoveBack();
        } 
        break;  
      case IR_1:  //Tlačítko 1
        mode = 1;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW) ; 
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,LOW);   
        break; 
      case IR_2:  //Tlačítko 2
        mode = 2;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,LOW);
        break;   
      case IR_3:  //Tlačítko 3
        mode = 3;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW); 
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,LOW);
        break; 
      case IR_4:  //Tlačítko 4
        mode = 4;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW); 
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,LOW);
        break;  
      case IR_5:  //Tlačítko 5
        mode = 5;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW); 
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);  
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);  
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,LOW);                    
    }    
    IR_Receiver.resume();    
  }
  
  if(mode.equals("3")){
    SL = digitalRead(LEFT_SENSOR_PIN);
    SM = digitalRead(MIDDLE_SENSOR_PIN);
    SR = digitalRead(RIGHT_SENSOR_PIN);
    if (SM == HIGH){
      if (SL == LOW & SR == HIGH){
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,HIGH);
        digitalWrite(MOTOR_PIN_3,HIGH);
        digitalWrite(MOTOR_PIN_4,LOW);
      }
      else if (SR == LOW & SL == HIGH){
        digitalWrite(MOTOR_PIN_1,HIGH);
        digitalWrite(MOTOR_PIN_2,LOW );
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,HIGH);
      }
      else{
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,HIGH);
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,HIGH); 
      }
    }
    else{
      if (SL== LOW & SR == HIGH){
        digitalWrite(MOTOR_PIN_1,LOW);
        digitalWrite(MOTOR_PIN_2,HIGH);
        digitalWrite(MOTOR_PIN_3,HIGH);
        digitalWrite(MOTOR_PIN_4,LOW);
      }
      else if (SR == LOW & SL == HIGH){
        digitalWrite(MOTOR_PIN_1,HIGH);
        digitalWrite(MOTOR_PIN_2,LOW );
        digitalWrite(MOTOR_PIN_3,LOW);
        digitalWrite(MOTOR_PIN_4,HIGH);
      }
      else{
        digitalWrite(MOTOR_PIN_1,HIGH);
        digitalWrite(MOTOR_PIN_2,LOW);
        digitalWrite(MOTOR_PIN_3,HIGH);
        digitalWrite(MOTOR_PIN_4,LOW);
        delay(100);
        digitalWrite(MOTOR_PIN_1,HIGH);
        digitalWrite(MOTOR_PIN_2,HIGH);
        digitalWrite(MOTOR_PIN_3,HIGH);
        digitalWrite(MOTOR_PIN_4,HIGH); 
      }
    }
  }

  if(mode.equals("4")){
    if(UltraSonic.Distance() < 10){
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,HIGH);
      digitalWrite(MOTOR_PIN_3,HIGH);
      digitalWrite(MOTOR_PIN_4,LOW);
      delay(500);
      digitalWrite(MOTOR_PIN_1,HIGH);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,HIGH);
      digitalWrite(MOTOR_PIN_4,LOW);
      delay(500);
    }else{
      digitalWrite(MOTOR_PIN_1,HIGH);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,HIGH);
    }
  }

  if(mode.equals("5")){
    if(UltraSonic.Distance() < 10){
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,HIGH);
      digitalWrite(MOTOR_PIN_3,HIGH);
      digitalWrite(MOTOR_PIN_4,LOW);
      delay(500);
      digitalWrite(MOTOR_PIN_1,LOW);
      digitalWrite(MOTOR_PIN_2,HIGH);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,HIGH);
      delay(500);
    }else{
      digitalWrite(MOTOR_PIN_1,HIGH);
      digitalWrite(MOTOR_PIN_2,LOW);
      digitalWrite(MOTOR_PIN_3,LOW);
      digitalWrite(MOTOR_PIN_4,HIGH);
    }
  }
}