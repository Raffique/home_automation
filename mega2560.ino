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
const int SENSOR1 = 6;  //Light 1
const int SENSOR2 = 9;  //Light 2
const int SENSOR3 = 10;  //Light 3
const int SENSOR4 = 11;  //Light 4
const int SENSOR5 = 12;  //Fan 1
const int SENSOR6 = 13;  //Fan 2

/***********
**VARIBLES**
************/


void setup() {
  /*************************
  ***RELAY PIN MODE SETUP***
  **************************/
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(SENSOR1, OUTPUT); 
  pinMode(SENSOR2, OUTPUT); 
  pinMode(SENSOR3, OUTPUT); 
  pinMode(SENSOR4, OUTPUT); 
  pinMode(SENSOR5, OUTPUT); 
  pinMode(SENSOR6, OUTPUT); 


}

void loop() {

  checkVolts();
  
  if(AmpsCR1 > 0){
     digitalWrite(SENSOR1, HIGH);
  }
  else{
     digitalWrite(SENSOR1, LOW);
  }
 /*********************************************/  
  if(AmpsCR2 > 0){
     digitalWrite(SENSOR2, HIGH);
  }
  else{
     digitalWrite(SENSOR2, LOW);
  }
 /**********************************************/ 
  if(AmpsCR3 > 0){
     digitalWrite(SENSOR3, HIGH);
  }
  else{
     digitalWrite(SENSOR3, LOW);
  }
 /***********************************************/
 if(AmpsCR4 > 0){
     digitalWrite(SENSOR4, HIGH);
  }
  else{
     digitalWrite(SENSOR4, LOW);
  }
 /***********************************************/
 if(AmpsCR5 > 0){
     digitalWrite(SENSOR5, HIGH);
  }
  else{
     digitalWrite(SENSOR5, LOW);
  }
 /***********************************************/
 if(AmpsCR6 > 0){
     digitalWrite(SENSOR6, HIGH);
  }
  else{
     digitalWrite(SENSOR6, LOW);
  }
 /***********************************************/


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





