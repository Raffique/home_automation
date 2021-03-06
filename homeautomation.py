#import Libraries
import RPi.GPIO as gpio
import pyrebase
import time

gpio.cleanup()
gpio.setmode(gpio.BOARD)

#PINS
R1 = 3 #gpio 2
R2 = 5 #gpio 3
R3 = 7 #gpio 4
R4 = 8 #UART0 TX
R5 = 10 #UART0 RX
R6 = 11 #gpio 17

S1 = 12 #gpio 18
S2 = 13 #gpio 27
S3 = 15 #gpio 22
S4 = 16 #gpio 23
S5 = 18 #gpio 24
S6 = 19 #gpio 10

B1 = 21 #gpio 9
B2 = 22 #gpio 25
B3 = 23 #gpio 11
B4 = 31 #gpio 6
B5 = 32 #gpio 12
B6 = 33 #gpio 13

RELAYS = [R1,R2,R3,R4,R5,R6]
SENSORS = [S1,S2,S3,S4,S5,S6]
BUTTONS = [B1,B2,B3,B4,B5,B6]
EQUIP = ["Light1", "Light2", "Light3", "Light4", "Fan1", "Fan2"]
ONS = ["\"Light 1 on\"", "\"Light 2 on\"", "\"Light 3 on\"", "\"Light 4 on\"", "\"Fan 1 on\"", "\"Fan 2 on\""]
OFFS = ["\"Light 1 off\"", "\"Light 2 off\"", "\"Light 3 off\"", "\"Light 4 off\"", "\"Fan 1 off\"", "\"Fan 2 off\""]
STATS = ["\"Light 1 status\"", "\"Light 2 status\"", "\"Light 3 status\"", "\"Light 4 status\"", "\"Fan 1 status\"", "\"Fan 2 status\""]


#RELAYS PINS
gpio.setup(R1, gpio.OUT, initial = gpio.HIGH)
gpio.setup(R2, gpio.OUT, initial = gpio.HIGH)
gpio.setup(R3, gpio.OUT, initial = gpio.HIGH)
gpio.setup(R4, gpio.OUT, initial = gpio.HIGH)
gpio.setup(R5, gpio.OUT, initial = gpio.HIGH)
gpio.setup(R6, gpio.OUT, initial = gpio.HIGH)

#SENSOR PINS
gpio.setup(S1, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.setup(S2, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.setup(S3, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.setup(S4, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.setup(S5, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.setup(S6, gpio.IN, pull_up_down = gpio.PUD_DOWN)

#BUTTON PINS
gpio.setup(B1, gpio.IN, pull_up_down = gpio.PUD_UP)
gpio.setup(B2, gpio.IN, pull_up_down = gpio.PUD_UP)
gpio.setup(B3, gpio.IN, pull_up_down = gpio.PUD_UP)
gpio.setup(B4, gpio.IN, pull_up_down = gpio.PUD_UP)
gpio.setup(B5, gpio.IN, pull_up_down = gpio.PUD_UP)
gpio.setup(B6, gpio.IN, pull_up_down = gpio.PUD_UP)


#Firebase Configuration
config = {
  "apiKey": "AlzaSyC_2yT71bUZAHS-3J8-2gAxvDeJv24f4NA",
  "authDomain": "home-automation-3d483.firebaseapp.com",
  "databaseURL": "https://home-automation-3d483.firebaseio.com",
  "storageBucket": ""
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()



def pulse(pin):
    gpio.output(pin, 0)
    time.sleep(0.5)
    gpio.output(pin, 1)
    
def report():
    for rep in range(0,6):
        if gpio.input(SENSORS[rep]) == True:
            db.child(EQUIP[rep]).set(ONS[rep])
        else:
            db.child(EQUIP[rep]).set(OFFS[rep])
            
def check_firebase():
    for rep in range(0,6):
        if db.child(EQUIP[rep]).get().val() == ONS[rep] and not(gpio.input(SENSORS[rep])):
            pulse(RELAYS[rep])
            print(ONS[rep])
        elif db.child(EQUIP[rep]).get().val() == OFFS[rep] and gpio.input(SENSORS[rep]):
            pulse(RELAYS[rep])
            print(OFFS[rep])
        elif db.child(EQUIP[rep]).get().val() == STATS[rep]:
            if gpio.input(SENSORS[rep]) == True:
                db.child(EQUIP[rep]).set(ONS[rep])
            else:
                db.child(EQUIP[rep]).set(OFFS[rep])
            print(STATS[rep])
            
def check_buttons():
    for rep in range(0,6):
        if not(gpio.input(BUTTONS[rep])):
            if gpio.input(SENSORS[rep]) == True:
                db.child(EQUIP[rep]).set(ONS[rep])
            else:
                db.child(EQUIP[rep]).set(OFFS[rep])
            while not(gpio.input(BUTTONS[rep])):
                pass
            
def check_buttons2():
    for rep in range(0,6):
        if not(gpio.input(BUTTONS[rep])):
          pulse(RELAYS[rep])
          while not(gpio.input(BUTTONS[rep])):
              pass

            
#Main once
time.sleep(5)
try:
  report()
  mode = 0
except:
  mode = 1

#Main loop
if mode == 0:
  while True:
    check_firebase()
    check_buttons()
else:
  while True:
    check_buttons2()
            
    
#pip3 install pyrebase
#pip3 install --upgrade google-auth-oauthlib
#led = db.child("Variable").get()
#print(led.val())
#db.child("Fan1").set("\"Fan 1 off\"")
#gpio.output(pin,1)
#gpio.input(pin)
