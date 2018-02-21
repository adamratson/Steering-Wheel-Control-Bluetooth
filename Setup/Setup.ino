#define numOfButtons 6
#define ANALOG_PIN 0

// add one to num of buttons to account for the normal condition
int resistanceValues[numOfButtons + 1] = {0};
String buttonMeaning[numOfButtons] = {"Volume up", "Volume down", "Next song", "Previous song", "Arrow", "Circle"};
// rV[0] is the normal 
// rV[x+1] is bM[x]

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println("Dont press any buttons");
  delay(3000);
  resistanceValues[0] = measureResistance();
  Serial.println("Measured the normal resistance.");
  // find the size of the array in bytes, divide it by the size of the first object it holds to get the number of objects it holds
  for (int i = 1; i <= sizeof(resistanceValues)/sizeof(resistanceValues[0]); ++i){
    Serial.println("Press "+buttonMeaning[i-1]);
    resistanceValues[i] = measureResistance();
  }
}

int measureResistance(){
  int raw= 0;
  int Vin= 5;
  
  float Vout= 0;
  float R1= 180;
  float R2= 0;
  float buffer= 0;
  
  raw = analogRead(ANALOG_PIN);
  if(raw){
    buffer= raw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    R2= R1 * buffer;
    return R2;
  }
}

