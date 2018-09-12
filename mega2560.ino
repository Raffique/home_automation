/*********************
********COMMANDS******
**********************
**  Light 1 on    ** 
**  Light 1 off   **
**  Light 1 status  **
**  Light 2 on    **
**  Light 2 off   **
**  Light 2 status  **
**  Light 3 on    **
**  Light 3 off   **
**  Light 3 status  **
**  Light 4 on    **
**  Light 4 off   **
**  Light 4 status  **
**  Fan 1 on    **
**  Fan 1 off   **
**  Fan 1 status  **
**  Fan 2 on    **
**  Fan 2 off   **
**  Fan 2 status  **
**  All status    **
**********************/


/**********************
**Voltage Reader PINS**
***********************/
const int CR1 = A0;   //Light 1
const int CR2 = A1;   //Light 2
const int CR3 = A2;  //Light 3
const int CR4 = A3;  //Light 4
const int CR5 = A4;  //Fan 1
const int CR6 = A5;  //Fan 2

/**********************
**RAW VALUES DECLARED**
***********************/
int RawValue_CR1 = 0; //Light 1
int RawValue_CR2 = 0; //Light 2
int RawValue_CR3 = 0; //Light 3
int RawValue_CR4 = 0; //Light 4
int RawValue_CR5 = 0; //Fan 1
int RawValue_CR6 = 0; //Fan 2

/***************************
** VOLTAGE VALUES DECLARED**
****************************/
double Voltage_CR1 = 0; //Light 1
double Voltage_CR2 = 0; //Light 2
double Voltage_CR3 = 0; //Light 3
double Voltage_CR4 = 0; //Light 4
double Voltage_CR5 = 0; //Fan 1
double Voltage_CR6 = 0; //Fan 2

/****************************
** AMPERAGE VALUES DECLARED**
*****************************/
double AmpsCR1 = 0; //Light 1
double AmpsCR2 = 0; //Light 2
double AmpsCR3 = 0; //Light 3
double AmpsCR4 = 0; //Light 4
double AmpsCR5 = 0; //Fan 1
double AmpsCR6 = 0; //Fan 2

/***************************
**RELAY PINS DECLARED**
****************************/
const int RELAY1 = 6;  //Light 1
const int RELAY2 = 9;  //Light 2
const int RELAY3 = 10;  //Light 3
const int RELAY4 = 11;  //Light 4
const int RELAY5 = 12;  //Fan 1
const int RELAY6 = 13;  //Fan 2

/***********
**VARIBLES**
************/


void setup() {
  /*************************
  ***RELAY PIN MODE SETUP***
  **************************/
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(RELAY1, OUTPUT); digitalWrite(RELAY1, HIGH);
  pinMode(RELAY2, OUTPUT); digitalWrite(RELAY2, HIGH);
  pinMode(RELAY3, OUTPUT); digitalWrite(RELAY3, HIGH);
  pinMode(RELAY4, OUTPUT); digitalWrite(RELAY4, HIGH);
  pinMode(RELAY5, OUTPUT); digitalWrite(RELAY5, HIGH);
  pinMode(RELAY6, OUTPUT); digitalWrite(RELAY6, HIGH);


}

String data = "";
void check_message(String data);
void SendText(String text);

void loop() {
	
	char sym = Serial.read();
	if(sym == '\n'){
		checkVolts();
		check_message(data);
		data = "";
	}
	else{
		data += sym;
	}

}


// Function to Check Volts
void checkVolts(){
  RawValue_CR1 = analogRead(CR1);
  Voltage_CR1 = (RawValue_CR1 / 1023.0) * 5000; // Gets you mV
  AmpsCR1 = ((Voltage_CR1 - 2500) / 66);
  
  RawValue_CR2 = analogRead(CR2);
  Voltage_CR2 = (RawValue_CR2 / 1023.0) * 5000; 
  AmpsCR2 = ((Voltage_CR2 - 2500) / 66);

  
  RawValue_CR3 = analogRead(CR3);
  Voltage_CR3 = (RawValue_CR3 / 1023.0) * 5000;
  AmpsCR3 = ((Voltage_CR3 - 2500) / 66);

    
  RawValue_CR4 = analogRead(CR4);
  Voltage_CR4 = (RawValue_CR4 / 1023.0) * 5000;
  AmpsCR4 = ((Voltage_CR4 - 2500) / 66);

    
  RawValue_CR5 = analogRead(CR5);
  Voltage_CR5 = (RawValue_CR5 / 1023.0) * 5000;
  AmpsCR5 = ((Voltage_CR5 - 2500) / 66);

    
  RawValue_CR6 = analogRead(CR6);
  Voltage_CR6 = (RawValue_CR6 / 1023.0) * 5000;
  AmpsCR6 = ((Voltage_CR6 - 2500) / 66);

}


void pulse(int pin){
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
}


void SendText(String text){
	Serial1.println(text);
	
}

void check_message(String var){
	
    if(var == String("Light 1 on")){
      if(AmpsCR1 <= 5){
          pulse(RELAY1);
      }
    }
    else if(var == String("Light 1 off")){
      if(AmpsCR1 > 5){
          pulse(RELAY1);
      }
    } 
    else if(var == String("Light 1 status")){
      if(AmpsCR1 > 5){
          SendText("Light 1 ON");
      }else{
        SendText("Light 1 OFF");
      }
    } 
    else if(var == String("Light 2 on")){
      if(AmpsCR2 <= 5){
          pulse(RELAY2);
      }
    } 
    else if(var == String("Light 2 off")){
      if(AmpsCR2 > 5){
          pulse(RELAY2);
      }
    } 
    else if(var == String("Light 2 status")){
      if(AmpsCR2 > 5){
          SendText("Light 2 ON");
      }else{
        SendText("Light 2 OFF");
      }
    } 
    else if(var == String("Light 3 on")){
      if(AmpsCR3 <= 5){
          pulse(RELAY3);
      }
    } 
    else if(var == String("Light 3 off")){
      if(AmpsCR3 > 5){
          pulse(RELAY3);
      }
    } 
    else if(var == String("Light 3 status")){
      if(AmpsCR3 > 5){
          SendText("Light 3 ON");
      }else{
        SendText("Light 3 OFF");
      }
    } 
    else if(var == String("Light 4 on")){
      if(AmpsCR4 <= 5){
          pulse(RELAY4);
      }
    } 
    else if(var == String("Light 4 off")){
      if(AmpsCR4 > 5){
          pulse(RELAY4);
      }
    } 
    else if(var == String("Light 4 status")){
      if(AmpsCR4 > 5){
          SendText("Light 4 ON");
      }else{
        SendText("Light 4 OFF");
      }
    } 
    else if(var == String("Fan 1 on")){
      if(AmpsCR5 <= 5){
          pulse(RELAY5);
      }
    } 
    else if(var == String("Fan 1 off")){
      if(AmpsCR5 > 5){
          pulse(RELAY5);
      }
    } 
    else if(var == String("Fan 1 status")){
      if(AmpsCR5 > 5){
          SendText("FAN 1 ON");
      }else{
        SendText("FAN 1 OFF");
      }
    } 
    else if(var == String("Fan 2 on")){
      if(AmpsCR6 <= 5){
          pulse(RELAY6);
      }
    } 
    else if(var == String("Fan 2 off")){
      if(AmpsCR6 > 5){
          pulse(RELAY6);
      }
    }  
    else if(var == String("Fan 2 status")){
      if(AmpsCR6 > 5){
          SendText("FAN 2 ON");
      }
      else{
        SendText("FAN 2 OFF");
      }
    } 
    
    else if(var == String("All status")){
      String sendText="";
      //////////////////////////////////////////////
      if(AmpsCR1 > 5){
        sendText = String("Light1 On");
      }
      else{
        sendText = String("Light1 Off");
      }
      /////////////////////////////////////////////
      if(AmpsCR2 > 5){
        sendText = String(sendText + " Light2 On");
      }
      else{
        sendText = String(sendText + " Light2 Off");
      }
      ////////////////////////////////////////////
      if(AmpsCR3 > 5){
        sendText = String(sendText + " Light3 On");
      }
      else{
        sendText = String(sendText + " Light3 Off");
      }
      /////////////////////////////////////////////
      if(AmpsCR4 > 5){
        sendText = String(sendText + " Light4 On");
      }
      else{
        sendText = String(sendText + " Light4 Off");
      }
      ////////////////////////////////////////////
      if(AmpsCR5 > 5){
        sendText = String(sendText + " Fan1 On");
      }
      else{
        sendText = String(sendText + " Fan1 Off");
      }
      /////////////////////////////////////////////
      if(AmpsCR6 > 5){
        sendText = String(sendText + " Fan2 On");
      }
      else{
        sendText = String(sendText + " Fan2 Off");
      }
      ////////////////////////////////////////////

      SendText(sendText);
    }
  
}


