#include <SoftwareSerial.h>

#define RX_PIN D3
#define TX_PIN D4

// resistance values for the buttons
#define normal 3480
#define volUp 152
#define volDown 77
#define next 430
#define previous 737
#define arrow 1376
#define circle 263

// values for finding resistance
int analogPin= 0;
int raw= 0;
int Vin= 5;

float Vout= 0;
float R1= 180;
float R2= 0;
float buffer= 0;

SoftwareSerial BTSerial(RX_PIN, TX_PIN);

void setup(){
  BTSerial.begin(115200);
}

void loop(){
  raw = analogRead(analogPin);
  if(raw){
    buffer= raw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    R2= R1 * buffer;
    
    // for each expected value of R2, send a command to the BT module
    // all the keys are self explantory except circle represents mute and arrow is play/pause
    if((R2 > volUp * 0.95) && (R2 < volUp * 1.05)){
        BTSerial.println("VOLUME_UP");
    } else if((R2 > volDown * 0.95) && (R2 < volDown * 1.05)){
        BTSerial.println("VOLUME_DOWN");
    } else if((R2 > next * 0.95) && (R2 < next * 1.05)){
        BTSerial.println("NEXTSONG");
    } else if((R2 > previous * 0.95) && (R2 < previous * 1.05)){
        BTSerial.println("PREVIOUSSONG");
    } else if((R2 > arrow * 0.95) && (R2 < arrow * 1.05)){
        BTSerial.println("PLAYPAUSE");
    } else if((R2 > circle * 0.95) && (R2 < circle * 1.05)){
        BTSerial.println("MUTE");
    }

    delay(250);
  }
}

