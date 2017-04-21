#define LOG_OUT 1
#define FFT_N 256
#define AIR_CV 1

#include <FFT.h> 

void setup() {
  for(int i = 0; i < 9; i++){
    pinMode(i + 1, OUTPUT);
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
  if(fft_log_out == 0){
  	digitalWrite(AIR_CV, LOW);
  }else{
  	digitalWrite(AIR_CV, HIGH);
  }
}
