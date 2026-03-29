  int J_VRX = A0;
  int J_VRY = A1;
  int BUTTON = 12;
  int SPEAKER = A5;

  int leds[] = {13, 2, 4, 5, 6}; 
  int leds2[] = {7, 8, 9, 10, 11}; 

  int speed = 0;
  int playerPosition = 0;
  int secretGoal = 0;
  int sp = 0;
  uint32_t timer;

  void setup() {
    for (int i = 0; i < 5; i++) {
      pinMode(leds[i], OUTPUT);
    }
    for (int i = 0; i < 5; i++) {
      pinMode(leds2[i], OUTPUT);
    }

    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(SPEAKER, OUTPUT);

    randomSeed(analogRead(A1) + analogRead(A2) + micros());
    secretGoal = random(0, 5);

    digitalWrite(leds2[secretGoal], HIGH);
    timer = millis();

    Serial.begin(9600);
  }

  //Reset old, unused leds on player led-line
  void resetPlayerLeds() {
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  //Turn off goal leds, generating new number
  void resetGoalLeds() {
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds2[i], LOW);
    }
    secretGoal = random(0, 5);
    digitalWrite(leds2[secretGoal], HIGH);
    tone(SPEAKER, 200);
    delay(50);
    noTone(SPEAKER);
  }

  //Get player position(0-4)
  int getPlayerPosition() {
    for (int i = 0; i < 5; i++) {
      if (digitalRead(leds[i]) == HIGH) {
        return i;
      }
    }
  }

  void sadMusic() {
    tone(SPEAKER, 440, 200); 
    delay(250);
    tone(SPEAKER, 415, 200); 
    delay(250);
    tone(SPEAKER, 392, 200); 
    delay(250);
    tone(SPEAKER, 370, 400); 
    delay(450);

  }

  void loop() {
    int y = map(analogRead(J_VRY), 0, 1023, -1, 1);
    float speed = y;

    if (millis() - timer >= 2000) {
      timer = millis();
      for (int i = 0; i < 5; i++) {
        digitalWrite(leds2[i], HIGH);
      }

      sadMusic();
      timer = millis();
      resetGoalLeds();
    }

    //Checking for win condition
    if (digitalRead(12) == LOW && playerPosition == secretGoal) {

      for (int i = 0; i < 5; i++) {
        digitalWrite(leds2[i], HIGH);
      }

      tone(SPEAKER, 20);
      delay(50);
      noTone(SPEAKER);

      delay(1500);
      timer = millis();
      resetGoalLeds();
    }

    //If player makes mistake
    if (digitalRead(12) == LOW && playerPosition != secretGoal) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(leds[i], HIGH);
      }

      sadMusic();
      
      resetPlayerLeds();
      timer = millis();
      resetGoalLeds();
    }
    
    sp += speed;
    sp = constrain(sp, 0, 4);

    if (getPlayerPosition() != playerPosition) {
      tone(SPEAKER, 1000);
      delay(40);
      noTone(SPEAKER);
    }

    playerPosition = getPlayerPosition();

    delay(80);
    resetPlayerLeds();
    digitalWrite(leds[sp], HIGH);   
  }
