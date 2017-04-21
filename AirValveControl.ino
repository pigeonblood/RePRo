 #define AIR_PIN 2
#define AUD_IN 0
#define IN_MIN_VALUE 256

void setup()
{
    pinMode(AIR_PIN, OUTPUT);
}

void loop(){
    int val = analogRead(AUD_IN);
    digitalWrite(AUD_PIN, (val > IN_MIN_VALUE)); //C言語では、比較演算子は1または0をint値で返す。
}
