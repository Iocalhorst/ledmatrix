#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 7
#define R_PIN 0
#define G_PIN 3
#define B_PIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t white = strip.Color(255, 255, 255);
uint32_t black = strip.Color(0, 0, 0);
uint32_t purple = strip.Color(0, 255, 255);
uint32_t color;
int choice;
long nr=0;
const int matrix_width=10;
const int matrix_height=30;
long currentmillis;
long oldmillis;
long intervall=32;
short fader1=0;
short fader2=0;
short fader3=0;


uint32_t myColors[] = {magenta, red, green, blue, yellow, white, black, purple};

void putpixel(long x,long y,uint32_t col) {

  // check for matrix_boundaries
  if ((x<=matrix_width) and (x>=0) and (y<=matrix_height) and (y>=0)) {
          nr=y*matrix_width; 
//inefficient;
nr=y*matrix_width; //y offset. has to skip line.length for to get 1 pixel 
if (y%2==0) {nr+=x;};
if (y%2==1) {nr+=(-1*x)+matrix_width-1;};
 
//conditional_operator =y and 1   // get the last bit 
// conditional_operator =y xor 1   // flip that bit, same as c= !c
// now we "insert bot terms into one equasion / a sequence of arithmetic operations
//term1 (takes care for even rows)     : +x*(conditional_operator)   /now zeros out for the lines 0,2,4...
//term2 (takes care for the odd)       : -x*(conditional_operator)   //to "count other way" direction
//term3 (the offset for the odd rows)  :  +10*conditional operator) (for the offset 


//long conditional_operator=!(y && 0b0000000000000001);   // might be unnessecary to user long here... whatever
//nr+=conditional_operator*x + conditional_operator*(10-x);

  
  
  strip.setPixelColor(nr,col);}
  }

struct particle {
  long x=0;
  long y=0;
  uint32_t c;
  
  //float vx=0;
  //fl4oat vy=0;
  };

particle raindrops[50];

 void draw(long x2, long y2 , uint32_t c2) {
  putpixel(x2,y2,c2);
 /* Serial.print("x : ");
Serial.print(x);
Serial.print(" y : ");
Serial.println(y);*/
  }

class cRain  
  {
    public:
      Crain() 
      {
          float heavyness=50;
          int amount_raindrops=10;
            
      
          

      }
      void updateSelf(float elapsedTime){}
      
      void drawSelf(){
        for (int i=0;i<50;i++) {
          draw(10-raindrops[i].y,raindrops[i].x,raindrops[i].c);
          }
        }

      

      
  
  };


void setup() {
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(0);
  //Serial.begin(9600);
  oldmillis=millis();
     for (int i2=0;i2<50;i2++) {
            raindrops[i2].x=random(30);
            raindrops[i2].y=random(10);
            raindrops[i2].c=strip.Color(64,0,32+random(224));
          }
}

void apply_rules(){
  for (int i2=0;i2<50;i2++) {
            raindrops[i2].y++;
            if ((raindrops[i2].y)>10) {raindrops[i2].x=random(30);raindrops[i2].y=0;}
          }
  };

//list<particle> listParticless;

  cRain myrain=cRain();

  
void loop() {
fader1=255-analogRead(A5)/4;
fader2=255-analogRead(A3)/4;
fader3=255-analogRead(A1)/4;

strip.fill(strip.Color(fader1,fader2,fader3));
if (random(128)==1) {strip.fill(strip.Color(64+random(64),64+random(64),random(64)));
delay(40);
};

myrain.drawSelf();

currentmillis=millis();
 if ((currentmillis-oldmillis)>=intervall) {apply_rules();oldmillis=currentmillis;}
strip.show();
strip.clear();

}
