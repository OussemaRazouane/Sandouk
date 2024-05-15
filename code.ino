

#include <Arduino.h>
#include <Ps3Controller.h>

#define buz 13
// Right motor
#define ad 22
#define rd 23
// Left motor
#define ag 12
#define rg 14

#define freq 1000
#define ad_c 5
#define ag_c 4

#define rd_c 3
#define rg_c 6
#define resolution 8

#define speed9wiya 250
#define speedmtwasta 190
#define speedth3ifa 145

void forward(int speed) {
  ledcWrite(ad_c, speed); //ad
  ledcWrite(ag_c, speed); //ag
  ledcWrite(rd_c, 0);  //rd
  ledcWrite(rg_c, 0);  //rg

}

void backward(int speed) {
  ledcWrite(ad_c, 0); //ad
  ledcWrite(ag_c, 0); //ag
  ledcWrite(rd_c, speed);  //rd
  ledcWrite(rg_c, speed);  //rg

}
void right(int speed) {
  ledcWrite(ad_c, 0); //ad
  ledcWrite(ag_c, speed); //ag
  ledcWrite(rd_c, speed);  //rd
  ledcWrite(rg_c, 0);  //rg
}
void left(int speed) {
  ledcWrite(ad_c, speed); //ad
  ledcWrite(ag_c, 0); //ag
  ledcWrite(rd_c, 0);  //rd
  ledcWrite(rg_c, speed);  //rg
}

void forward_right(){
  ledcWrite(ad_c, 0);
  ledcWrite(ag_c, 200);
  ledcWrite(rd_c, 125);
  ledcWrite(rg_c, 0);
}
void forward_left(){
  ledcWrite(ad_c, 200);
  ledcWrite(ag_c, 0);
  ledcWrite(rd_c, 0);
  ledcWrite(rg_c, 125);   
}
void backward_right(){
  ledcWrite(ad_c, 125);
  ledcWrite(ag_c, 0);
  ledcWrite(rd_c, 0);
  ledcWrite(rg_c, 200); 
}
void backward_left(){
  ledcWrite(ad_c, 0);
  ledcWrite(ag_c, 125);
  ledcWrite(rd_c, 200);
  ledcWrite(rg_c, 0);  
}

void stop() {
  ledcWrite(ad_c, 0);
  ledcWrite(ag_c, 0);
  ledcWrite(rg_c, 0);
  ledcWrite(rd_c, 0);
}



void onConnect() {
  Serial.println("Connected!");
}

void onDisConnect() {
  stop();
}

void setup() {
  Ps3.begin("00:00:00:00:00:00");
  pinMode(ad, OUTPUT);
  pinMode(rd, OUTPUT);
  pinMode(ag, OUTPUT);
  pinMode(rg, OUTPUT);
  pinMode(buz,OUTPUT);
  ledcSetup(rd_c, freq, resolution);
  ledcAttachPin(ad, rd_c);

  ledcSetup(ag_c, freq, resolution);
  ledcAttachPin(ag, ag_c);
  
  ledcSetup(ad_c, freq, resolution);
  ledcAttachPin(rd, ad_c);

  ledcSetup(rg_c, freq, resolution);
  ledcAttachPin(rg, rg_c);

 
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisConnect);
  Ps3.begin();
  Serial.println("Ready");

}
void notify() {

  int y = Ps3.data.analog.stick.ly; // Forward/backward car movement
  int x = Ps3.data.analog.stick.rx; // Left/right car movement
  bool l1=Ps3.data.button.l1;
  bool r1=Ps3.data.button.r1;
  bool tri=Ps3.data.button.triangle;
  bool up=Ps3.data.button.up;
  bool dow=Ps3.data.button.down;
  bool lef=Ps3.data.button.left;
  bool rig=Ps3.data.button.right;
  bool cross=Ps3.data.button.cross;
  int speed=0;
  if(l1){
    speed=speed9wiya;
  }else if(r1){
    speed=speedmtwasta;
  }else if(tri){
    speed=speedth3ifa;
  }
  if(speed !=0){
    if((y <= -50 || up) && (x >= 50 || rig)){
      forward_right();
    }else if((y <= -50 || up) && (x <= -50 || lef)){
      forward_left();
    }else if (y <= -50 || up) {
      forward(speed);
      Serial.println("forward");
    } else if (y >= 50 || dow) {
      backward(speed);
      Serial.println("backward");
    } else if (x >= 50 || rig) {
      right(speed);
      Serial.println("right");
    } else if (x <= -50 || lef) {
      left(speed);
      Serial.println("left");
    }else {
      stop();
      Serial.println("stop");
    }
  }else {
    stop();
    Serial.println("stop");
  }
  if(cross){
    tone(buz,2800);
  }else{
    noTone(buz);
  }
}

void loop() {
}
