//
include <Arduino.h>;
int rPin = 9;
int gPin = 10;
int bPin = 11;

int ledGlobalstatus = 0;

void setup(){
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    if(message.equals("SET_RGB")){
       Serial.println("Waiting for RGB");
       int red = Serial.parseInt();
       int green = Serial.parseInt();
       int blue = Serial.parseInt();
       Serial.print(red);
       Serial.print(green);
       Serial.println(blue);
       analogWrite(rPin, red);
       analogWrite(gPin, green);
       analogWrite(bPin, blue);
    } else if(message.equals("SET_LED_STATUS")){
       Serial.println("Waiting for LED Status");

    	String messageLedStatus = Serial.readStringUntil(';');
      	Serial.println(messageLedStatus);
      	if(messageLedStatus.equals("FAST")){
      		ledGlobalstatus = 1;
            Serial.println("FAST MODE");
      	}else if(messageLedStatus.equals("SLOW")){
      		ledGlobalstatus = 2;
          	Serial.println("SLOW MODE");
      	}else if(messageLedStatus.equals("ON")){
      		ledGlobalstatus = 3;
          	Serial.println("ON MODE");
        }
    } else if(message.equals("GET_PHOTO_STATUS")){
      Serial.println("Sending photo Status");
    	Serial.print("PHOTO:");
        Serial.println(analogRead(A0));
    }else if(message.equals("GET_TEMP_STATUS")){
      Serial.println("Sending temp Status");
    	Serial.print("TEMP:");
        Serial.println(analogRead(A1));
    }
  }


  switch(ledGlobalstatus){
  	case 0:
    	ledOff();
    break;
    case 1:
    	ledFast();
    break;
    case 2:
    	ledSlow();
    break;
    case 3:
    	ledOn();
    break;
  }


  delay(100);
} // loop

void ledFast(){
	digitalWrite(7,HIGH);
  	delay(200);
  	digitalWrite(7,LOW);
  	delay(200);
}

void ledSlow(){
	digitalWrite(7,HIGH);
  	delay(2000);
  	digitalWrite(7,LOW);
  	delay(2000);
}

void ledOn(){
	digitalWrite(7,HIGH);
  	delay(500);
}

void ledOff(){
  	digitalWrite(7,LOW);
  	delay(500);
}

