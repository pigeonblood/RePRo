 #define AIR_PIN 2
#define AUD_IN 0
#define IN_MIN_VALUE 256

void setup()
{
    pinMode(AIR_PIN, OUTPUT);
}

void loop(){
    int val = analogRead(AUD_IN);
    if(val > IN_MIN_VALUE || -val > IN_MIN_VALUE){
        digitalWrite(AIR_PIN, HIGH);
    }else{
        digitalWrite(AIR_PIN,LOW);
    }
}
