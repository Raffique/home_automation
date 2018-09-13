#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

void Mega_Status(String obj, int n);
void Command(String instr);
void Firebase_Status();
void changes();

String item[] = {"", "", "", "", "", ""};
String last_item[] = {"", "", "", "", "", ""};
String OnState[] = {"Light 1 on","Light 2 on","Light 3 on","Light 4 on","Fan 1 on","Fan 2 on"};
String OffState[] = {"Light 1 off","Light 2 off","Light 3 off","Light 4 off","Fan 1 off","Fan 2 off"};
String states[] = {"Light 1 status","Light 2 status","Light 3 status","Light 4 status","Fan 1 status","Fan 2 status"};
String equip[] = {"Light1", "Light2", "Light3", "Light4", "Fan1", "Fan2"};

// Set these to run example.
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  delay(5000);
  /*** UPDATES VARIBLES IN FIREBASE DATABASE UPON POWERING ON OF SYSTEM ***/
  for(int num = 0; num <= 5; num++){
    Mega_Status(states[num], num);
  }
//////////////////////////////////////////////////////////////////////////////
}



void loop() {
  
    Firebase_Status();
    changes();

}

/******************** FUNCTIONS ************************************/

/***  CHECK STATE OF APPLIANCES AND UPDATE FIREBASE  ***/
void Mega_Status(String obj, int n){
///////////////////////////////////////////////////////////////////////////////
  char sym;
  String wordz;
  
  Command(obj);
  //delay(200);
  
  do{
    sym = Serial.read();

    if(sym == '\n'){
      Firebase.setString(equip[n], wordz);
      item[n] = wordz;
      last_item[n];
      //---------------------------------
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /message failed:");
          Serial.println(Firebase.error());  
          return;
      }
      wordz = "";
    }
    else{
    wordz += sym;
    }
  }while(sym != '\n');
/////////////////////////////////////////////////////////////////////////////  
}

void Command(String instr){
  Serial1.println(instr);
}

/*** UPDATE VARIABLES FROM THE FIREBASE DATAVASE ***/
void Firebase_Status(){
  for(int n = 0; n <= 5; n++){
    item[n] = Firebase.getString(equip[n]);
    if (Firebase.failed()) {
            Serial.print("getting /message failed:");
            Serial.println(Firebase.error());  
            return;
        }
  }
}

/*** CHECK FOR ANY NEW COMMANDS  ***/
void changes(){
  for(int m = 0; m <= 5; m++){
    if(last_item[m] != item[m]){
      if(item[m] == states[m]){
        Mega_Status(states[m], m);
      }
      else{
        Command(item[m]);
        //delay(200);
        Mega_Status(states[m], m);
      }
    }
  }
}
