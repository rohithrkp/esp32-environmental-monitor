#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 disp(128,64 , &Wire, -1);
DHT df(4,DHT22);

enum SystemState
{
  NORMAL,
  WARNING,
  CRITICAL
};
float temp;
float humid;

bool alarmEnabled = false;
bool lastButtonState = HIGH;

SystemState State;
unsigned long priv=0;
int a;
#define BUTTON 25

void setup() {
  pinMode(14,OUTPUT);
  Wire.begin(21,22);
  disp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
  df.begin();
  pinMode(27, OUTPUT);
  pinMode(34, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  handleButton();

  if(millis()-priv>=2000){
    priv=millis();
    readSensor();
    toggleLED();
    hmLDR();
    readBuzzer();
    dispOLED();
  }
}

void readSensor(){
  temp=df.readTemperature();
  humid=df.readHumidity();
  if(temp>24){
    State=CRITICAL;
  }
  else if(temp<22){
    State=NORMAL;
  }
  else{
    State=WARNING;
  }
}
  
void hmLDR(){
  a=digitalRead(34);
}

void dispOLED(){
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(WHITE);
  disp.setCursor(0,0);
  disp.print("Temperature:");
  disp.println(temp);
  disp.setCursor(0,20);
  disp.print("Humidity:");
  disp.print(humid);
  disp.setCursor(0,30);
  disp.print("LDR");
  disp.print(a);
  Serial.print(temp);
  Serial.print(humid);
  disp.display();
}

void toggleLED(){
  if(State==NORMAL){
    digitalWrite(14,LOW);
  }
  else if(State==WARNING){
    digitalWrite(14,HIGH);
  }
  else if(State==CRITICAL){
    digitalWrite(14,HIGH);
  }
}

void handleButton() {

  bool currentButtonState = digitalRead(BUTTON);

  if (lastButtonState == HIGH && currentButtonState == LOW) {

    alarmEnabled = !alarmEnabled;
    delay(50);
  }

  lastButtonState = currentButtonState;
}

void readBuzzer(){
  if (alarmEnabled == true && State == CRITICAL){
    tone(27,6000);
  }  
  else {
    noTone(27);
  }
}

