/*
 * presepe 1.0
 * REQUIRES: FastLED 3.1.0
 * 
 * Arduino Uno:  OK
 * Arduino Nano: OK
 * Digispark:    OK
 * 
 */


#include "FastLED.h"

// definisce il numero di led da comnadare nella striscia
#define NUM_LEDS 20

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
// elemento 0 = quanti sono i led da comandare
// elemento 1, 2... la lista dei led

void firePit(int ledarray[]);

// array degli effetti, primo numero = quanti sono i led, poi sequenza dei led

//effetto fuoco
int fuoco_led[] = {1,0};
int fuoco2_led[] = {1,5};

int water0_led[] = {1,1};
int water1_led[] = {1,2};
int water2_led[] = {1,3};


//sequenze di lampeggio
int lampeggia_led_A[]={6,4,7,9,11,13,15};
int lampeggia_led_B[]={5,6,8,10,12,14};
int lampeggia_led_C[]={3,1,2,3};

//quante fasi ha ogni sequenza.
//esempio: acceso e spento = 2
//esempio: giallo, rosso, verde = 3
int lampeggia_sequenza_A = 2;
int lampeggia_sequenza_B = 4;

int lampeggia_sequenza_C = 4;


//quali colori devono lampeggiare
//primo   numero = colore
//secondo numero = luminosità
//terzo   numero = saturazione

int lampeggia_colori_A[2][3]={
  {32,255,100},
  {32,255,0}
  };

int lampeggia_colori_B[4][3]={
  {60,255,100},
  {96,255,100},
  {128,255,100},
  {128,255,100}
  };

int lampeggia_colori_C[4][3]={
  {135,255,100},
  {165,255,100},
  {145,255,100},
  {155,255,100}
  };

int lampeggia_conta_A = 0;
int lampeggia_conta_B = 0;
int lampeggia_conta_C = 0;

int lampa(int cycle, int maxN, int ledarray[], int seqarray[][3]);

int giornonotte_led[]= {4,16,17,18,19};
int giornonotte_conta = 0;

int giornonotte(int cycle, int ledarray[]);

int bright = 255;
int fade = 32;

unsigned long pi_previousA = 0;
const long pi_intervalA = 750;

unsigned long pi_previousB = 0;
const long pi_intervalB = 1000;

unsigned long pi_previousC = 0;
const long pi_intervalC = 250;

unsigned long pi_previousGN = 0;
const long pi_intervalGN = 200;

unsigned long pi_previousF = 0;
unsigned long pi_previousF2 = 0;


unsigned long pi_previousW0 = 0;
unsigned long pi_previousW1 = 0;
unsigned long pi_previousW2 = 0;

void setup() {
//  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
//  pinMode(13, OUTPUT);
 }

void loop() {
  unsigned long current = millis();

// effetto lampeggia A
  if (current - pi_previousA >= pi_intervalA) {
    pi_previousA = current;
    lampeggia_conta_A = lampa(lampeggia_conta_A, lampeggia_sequenza_A, lampeggia_led_A, lampeggia_colori_A);
  }

// effetto lampeggia B
  if (current - pi_previousB >= pi_intervalB) {
    pi_previousB = current;
    lampeggia_conta_B = lampa(lampeggia_conta_B, lampeggia_sequenza_B, lampeggia_led_B, lampeggia_colori_B);
  }
/*
// effetto lampeggia C
  if (current - pi_previousC >= pi_intervalC) {
    pi_previousC = current;
    lampeggia_conta_C = lampa(lampeggia_conta_C, lampeggia_sequenza_C, lampeggia_led_C, lampeggia_colori_C);
  }
*/

// effetto giornonotte
  if (current - pi_previousGN >= pi_intervalGN) {
    pi_previousGN = current;
    giornonotte_conta = giornonotte(giornonotte_conta, giornonotte_led);
  }

// effetto fuoco
  if (current - pi_previousF >= random(20, 80)) {
    pi_previousF = current;
    firePit(fuoco_led);
  }

// effetto fuoco2
  if (current - pi_previousF2 >= random(20, 80)) {
    pi_previousF2 = current;
    firePit(fuoco2_led);
  }

// effetto acqua
  if (current - pi_previousW0 >= random(100, 300)) {
    pi_previousW0 = current;
    h2o(water0_led);
  }

// effetto acqua
  if (current - pi_previousW1 >= random(100, 300)) {
    pi_previousW1 = current;
    h2o(water1_led);
  }

// effetto acqua
  if (current - pi_previousW2 >= random(100, 300)) {
    pi_previousW2 = current;
    h2o(water2_led);
  }


}

void firePit(int ledarray[]){
    for (int i = 0; i < ledarray[0]; i++){
    int C = random(0, 32); //color red, orange and yellow
    int B = random(50, 255); // bright  
    int S = random(255); //sat
    leds[ledarray[i+1]] = CHSV(C,255,B);
  }
  FastLED.show();
}


void h2o(int ledarray[]){
    for (int i = 0; i < ledarray[0]; i++){
    int C = random(130, 160); //color red, orange and yellow
    int B = random(50, 150); // bright  
    int S = random(255); //sat
    leds[ledarray[i+1]] = CHSV(C,255,B);
  }
  FastLED.show();
}

int giornonotte(int cycle, int ledarray[]){
  int C = 16; //color
  int B = sin8(cycle);      // bright  
  int S = sin8(cycle+128);  //saturation
  for (int i = 0; i < ledarray[0]; i++){
    leds[ledarray[i+1]] = CHSV(C,S,B);
  }
  FastLED.show();
  cycle ++;
  return cycle;
}


int lampa(int cycleLM, int maxN, int ledarray[], int seqarray[][3]){
  if (cycleLM>maxN-1) {
    cycleLM=0;
  }
  for (int i = 0; i<ledarray[0]; i++){
    leds[ledarray[i+1]]= CHSV(seqarray[cycleLM][0],seqarray[cycleLM][1],seqarray[cycleLM][2]);
  }
 
  FastLED.show();  
  cycleLM++;
  return cycleLM;
}


