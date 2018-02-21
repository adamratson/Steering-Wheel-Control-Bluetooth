#include <SoftwareSerial.h>

#define RX_PIN 3
#define TX_PIN 2

// resistance values for the buttons
#define normalRValue 3480
#define volUpRValue 152
#define volDownRValue 77
#define nextRValue 430
#define previousRValue 737
#define arrowRValue 1376
#define circleRValue 263

// values for finding resistance
int analogPin= 5;
int raw= 0;
int Vin= 5;

float Vout= 0;
float R1= 180;
float R2= 0;
float buffer= 0;

SoftwareSerial BTSerial(RX_PIN, TX_PIN);

void setup(){
  BTSerial.begin(115200);
  Serial.begin(9600);
}

void loop(){
  Serial.println(R2);
  raw = analogRead(analogPin);
  if(raw){
    buffer= raw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    R2= R1 * buffer;
    
    // for each expected value of R2, send a command to the BT module
    // all the keys are self explantory except circle represents mute and arrow is play/pause
    if((R2 > volUpRValue * 0.95) && (R2 < volUpRValue * 1.05)){
      byte volumeUp[] = {0xFD, 0x03, 0x03, 0x10, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(volumeUp, sizeof(volumeUp));
    } else if((R2 > volDownRValue * 0.95) && (R2 < volDownRValue * 1.05)){
      byte volumeDown[] = {0xFD, 0x03, 0x03, 0x20, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(volumeDown, sizeof(volumeDown));
    } else if((R2 > nextRValue * 0.95) && (R2 < nextRValue * 1.05)){
      byte next[] = {0xFD, 0x03, 0x03, 0x100, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(next, sizeof(next));
    } else if((R2 > previousRValue * 0.95) && (R2 < previousRValue * 1.05)){
      byte previous[] = {0xFD, 0x03, 0x03, 0x200, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(previous, sizeof(previous));
    } else if((R2 > arrowRValue * 0.95) && (R2 < arrowRValue * 1.05)){
      byte playPause[] = {0xFD, 0x03, 0x03, 0x80, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(playPause, sizeof(playPause));
    } else if((R2 > circleRValue * 0.95) && (R2 < circleRValue * 1.05)){
      byte mute[] = {0xFD, 0x03, 0x03, 0x40, 0x00, 0xFD, 0x03, 0x03, 0x00, 0x00};
      BTSerial.write(mute, sizeof(mute));
    }
  }
  delay(250);
}

