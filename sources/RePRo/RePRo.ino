#define LOG_OUT 1
#define FFT_N 256

#include <FFT.h> 
#include <math.h>
#include <avr/pgmspace.h>

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
  for(int i = 1; i < 10; i++){
    pinMode(i , OUTPUT);
  }
  TIMSK0 = 0;
  ADCSRA = 0xe5;
  ADMUX = 0x40;
  DIDR0 = 0x01;
}

void loop() {
  cli();
  for (int i = 0 ; i < 512 ; i += 2) {
    while(!(ADCSRA & 0x10));
    ADCSRA = 0xf5;
    byte m = ADCL;
    byte j = ADCH;
    int k = (j << 8) | m;
    k -= 0x0200;
    k <<= 6;
    fft_input[i] = k;
    fft_input[i+1] = 0;
  }
  fft_window();
  fft_reorder();
  fft_run();
  fft_mag_log();
  sei();
  int n = GetMIDITone(fft_log_out) - 60;
  if(!(n < 0 || n > 27))
  {
    Play(FING_STEP[n]);
  }
}
int GetMIDITone(int in){
  //FING_STEP[9] MIDI69, ラ,440Hz
  return round((log10(in / 440)) / (log10(2)) + 69);
}

void Play(short fstep[9]){
  for(short i = 0; i < 9; i++){
    if(fstep[i] != 2){
      digitalWrite(i,fstep[i]);
    }
  }
}
