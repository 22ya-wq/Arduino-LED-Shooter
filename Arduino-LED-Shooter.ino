int J_VRX = A0;
int J_VRY = A1;
int J_SW = 3;
int BUTTON = 12;

int leds[] = {13, 2, 4, 5, 6}; 
int leds2[] = {7, 8, 9, 10, 11}; 

int speed = 0;
int playerPosition = 0;
int secretGoal = 0;
int sp = 0;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(leds2[i], OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(J_SW, INPUT_PULLUP);

  randomSeed(analogRead(A1) + analogRead(A2) + micros());
  secretGoal = random(0, 5);

  digitalWrite(leds2[secretGoal], HIGH);
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
}

//Updating player position(0-4)
void updatePlayerPosition() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(leds[i]) == HIGH) {
      playerPosition = i;
    }
  }
}

void loop() {
  int y = map(analogRead(J_VRY), 0, 1023, -1, 2);
  float speed = y;

  updatePlayerPosition();
  //Checking for win condition
  if (digitalRead(12) == LOW && playerPosition == secretGoal) {

    for (int i = 0; i < 5; i++) {
      digitalWrite(leds2[i], HIGH);
    }
    delay(1500);
    resetGoalLeds();

    digitalWrite(leds2[secretGoal], HIGH);
  }

  sp += speed;
  sp = constrain(sp, 0, 4);
  delay(80);
  resetPlayerLeds();
  digitalWrite(leds[sp], HIGH);   
}