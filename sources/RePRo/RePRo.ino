#define LOG_OUT 1
#define FFT_N 256

#include <math.h>
#include <avr/pgmspace.h>

char buff[8];
int cnt = 0;

//MIDI69: ラ, FING_STEP[9]
const PROGMEM unsigned short FING_STEP[27][9] = {
  {LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},
  {2,2,2,2,2,2,2,2,2},
  {LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW},
  {2,2,2,2,2,2,2,2,2},
  {LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW},
  {LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW},
  {LOW,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH},
  {LOW,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW},
  {2,2,2,2,2,2,2,2,2},
  {LOW,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW},
  {LOW,HIGH,HIGH,LOW,HIGH,HIGH,LOW,LOW,LOW},
  {LOW,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW,LOW},
  {LOW,HIGH,LOW,HIGH,LOW,LOW,LOW,LOW,LOW},
  {LOW,LOW,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW},
  {LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW,LOW},
  {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,LOW,HIGH},
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH},
  {HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,LOW},
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,LOW,LOW},
  {HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW},
  {HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,LOW,HIGH},
  {HIGH,HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH,LOW}};

void setup() {
  Serial.begin(9600);
  for(int i = 1; i < 10; i++){
    pinMode(i , OUTPUT);
  }
  TIMSK0 = 0;
  ADCSRA = 0xe5;
  ADMUX = 0x40;
  DIDR0 = 0x01;
}

void loop() {
  cnt = 0;
  int val = 0;
  while(Serial.available()){
    cnt++;
    if(cnt == 7){
      break;
    }
    buff[cnt - 1] = Serial.read();
  }
  buff[cnt] = "\0";
  if(cnt != 0){
    val = atoi(buff);
    if(!(val < 0 || val > 27))
    {
      Play(FING_STEP[val]);
    }
  }
}

/*int GetMIDINote(int in){
  //FING_STEP[9] MIDI69, ラ,440Hz
  return round((log10(in / 440) / log10(2)) * 12 + 69);
}
*/
void Play(short fstep[9]){
  for(short i = 0; i < 9; i++){
    if(fstep[i] != 2){
      digitalWrite(i,fstep[i]);
    }
  }
}
