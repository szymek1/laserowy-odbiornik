/*
void one_plus() - gdy napiecie narasta, czyli pada światło lasera, dopisuje 1;
void zero_plus() - gdy napiecie maleje, czyli światło lasera nie pada, dopisuje 0;
void state() - co odcinek czasu, zgodny z tym jak szybko laser może emitować sygnał
sprawdza jakie jest napięcie na ustalone po jednej z funkcji one/zero_plus, jeśli jest "low"
tzn. że laser wciąż pada i należy w tym okresie czasu dopisać 1, jeśli jest "high" tzn. że laser dalej nie pada
i należy dopisać 0;

*/

#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(12, 11, 10, 9, 3, 2);

int s0 = 4;
int s1 = 5;
int s2 = 6;
int s3 = 7;
int out = 8;
int frequency = 0;

String voltage = "high";
int tab[10] = {0,0,0,0,0,0,0,0,0,0};
int i = 0;

void state();
void one_plus();
void zero_plus();

void setup() {
   Serial.begin(9600);
   lcd.begin(16, 2);
 pinMode(s0, OUTPUT);
 pinMode(s1, OUTPUT);
 pinMode(s2, OUTPUT);
 pinMode(s3, OUTPUT);
 pinMode(out, INPUT);

 digitalWrite(s0, HIGH);
 digitalWrite(s1, LOW);

 Timer1.initialize(20);//microseconds!
 Timer1.attachInterrupt(state);
 attachInterrupt(digitalPinToInterrupt(out),one_plus,RISING);
 attachInterrupt(digitalPinToInterrupt(out),zero_plus,FALLING);
}

void loop() {
 if(i == 9){
  for(i = 0; i < 10; i++){
    lcd.print(tab[i]);
    }
  }

}

void state(){
  if(voltage == "low"){
    tab[i] = 1;
    i++;
    }
  if(voltage == "high"){
    tab[i] = 0;
    i++;
    }  
  }

void one_plus(){
  tab[i] = 1;
  voltage = "low";
  i++;
  }  
void zero_plus(){
  tab[i] = 0;
  voltage = "high";
  i++;
  }

  
