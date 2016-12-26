

#define RS485Transmit    HIGH
#define RS485Receive     LOW

int result = 0;
#define BUTTON_PIN 11
#define BUTTON_LED_PIN 10

#define SENSOR1 2
#define SENSOR2 3
#define SENSOR3 4
#define SENSOR4 5
int enabled_game = false;

#define WRITE_EN_PIN 8

char startGameA[] = "STARTA";
char stopGameA[] = "STOPA:%d";
int hit=3;


  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LED_PIN, OUTPUT);
  pinMode(WRITE_EN_PIN, OUTPUT);

  pinMode(SENSOR1, INPUT_PULLUP);
  pinMode(SENSOR2, INPUT_PULLUP);
  pinMode(SENSOR3, INPUT_PULLUP);
  pinMode(SENSOR4, INPUT_PULLUP);


  digitalWrite(BUTTON_LED_PIN, HIGH);
  digitalWrite(WRITE_EN_PIN, RS485Receive);

  void setup() {
    delay(3000);
    Serial.begin(9600);
      while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
}
void loop() {

 if ( enabled_game == false)
  if (digitalRead(BUTTON_PIN)==LOW)
  {
    delay(100);
    if (digitalRead(BUTTON_PIN) == LOW)
    {
      digitalWrite(BUTTON_LED_PIN, LOW);
      digitalWrite(WRITE_EN_PIN, RS485Transmit);
      delay(100);
      enabled_game = true;
      Serial.print(startGameA);
      Serial.print("\n");
      delay(100);
      digitalWrite(WRITE_EN_PIN, RS485Receive);
    }


  }else{
     digitalWrite(BUTTON_LED_PIN, HIGH);
  }


  if ( enabled_game == true) {
     hit = 3;
    if (  digitalRead(SENSOR1) == LOW )
    {
      hit++;

    }
    if (   digitalRead(SENSOR2) == LOW )
    {
      hit++;
    }
    if (   digitalRead(SENSOR3) == LOW )
    {
      hit++;
    }
    if (    digitalRead(SENSOR4) == LOW )
    {
      hit++;
    }



    if (hit >3)
    {
        int  randNumber = random(0, 6);
hit+=randNumber;
      if(hit>10)
        hit=10;
      char command[25] = "";
      sprintf(command,
              stopGameA,
              hit  );
      enabled_game = false;

      digitalWrite(WRITE_EN_PIN, RS485Transmit);
      delay(100);
      Serial.print(command);
      Serial.print("\n");
      delay(100);
      digitalWrite(WRITE_EN_PIN, RS485Receive);

       hit=3;
       for(int i=0; i<5 ; i++){
         digitalWrite(BUTTON_LED_PIN, HIGH);
      delay(100);
      digitalWrite(BUTTON_LED_PIN, LOW);
      delay(100);
       }


    }

  }



}



void animateButton1() {
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(BUTTON_LED_PIN, HIGH);
    delay(50 * i);
    digitalWrite(BUTTON_LED_PIN, LOW);
    delay(2000 / i);
  }

}

void animateButton2()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(BUTTON_LED_PIN, HIGH);
    delay(100);
    digitalWrite(BUTTON_LED_PIN, LOW);
    delay(1000);
  }
}
