unsigned long topBarTimer;
unsigned long topBarStartTime;

unsigned long ledPlantTimer;
unsigned long ledPlantStartTime;

unsigned long shootTimer;
unsigned long shootStartTime;

unsigned long globalTimer;
unsigned long globalStartTime;

unsigned long gameTimer;
unsigned long gameStartTime;

unsigned long gameoverTimer;
unsigned long gameoverStartTime;
boolean lose = false;
boolean shoot = false;

const int poten = A7;
int potenValue;
int gameSpeed;

const int btn = 13;
boolean btnReading;

byte currentCol[8] = {0,0,0,0,0,0,0,0};
byte gameOverFace1[8] = {
  0,
  B10100101,
  B01000010,
  B10100101,
  0,
  0,
  B00011000,
  B00100100
  };

byte gameOverFace2[8] = {0,0,0,0,0,0,0,0};


void setup() {
  // put your setup code here, to run once:
  DDRD = B11111111;
  DDRC = B111111;
  DDRB = B11;
  PORTD = B0;
  PORTC = B0;
  PORTB = B0;
  pinMode(poten, INPUT);
  pinMode(btn, INPUT);
  //Serial.begin(9600);
}

void Frame (byte col_values[]) {
  const int delayTime = 1;
  PORTC = B111111;
  PORTB = B11;
  for(byte x = 0; x<6; x++) {
    PORTC ^= (B100000>>x);
    PORTD = col_values[x];
    delay(delayTime);
    PORTC = B111111;
  }
  for(byte x=0; x<2; x++) {
    PORTB ^= B10>>x;
    PORTD = col_values[x+6];
    delay(delayTime);
    PORTB = B11;
  }
}

void TopBar(byte colArray[], int interval) {
  
  topBarTimer = millis() - topBarStartTime;

  if(topBarTimer <= interval) {
    colArray[0] = B01111111;
  } else if(topBarTimer <= interval*2) {
    colArray[0] = B00111111;
  } else if(topBarTimer <= interval*3) {
    colArray[0] = B10011111;
  } else if(topBarTimer <= interval*4) {
    colArray[0] = B11001111;
  } else if(topBarTimer <= interval*5) {
    colArray[0] = B11100111;
  } else if(topBarTimer <= interval*6) {
    colArray[0] = B11110011;
  } else if(topBarTimer <= interval*7) {
    colArray[0] = B11111001;
  } else if(topBarTimer <= interval*8) {
    colArray[0] = B11111100;
  } else if(topBarTimer <= interval*9) {
    colArray[0] = B11111110;
  } else {
    topBarStartTime = millis();
  }  
}

void LedPlant(byte colArray[], int interval) {
  ledPlantTimer = millis() - ledPlantStartTime;

  if(ledPlantTimer <= interval) {
    colArray[7] = B10000000;
  } else if(ledPlantTimer <= interval*2) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
  } else if(ledPlantTimer <= interval*3) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
    colArray[5] = B10000000;
  } else if(ledPlantTimer <= interval*4) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
    colArray[5] = B10000000;
    colArray[4] = B10000000;
  } else if(ledPlantTimer <= interval*5) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
    colArray[5] = B10000000;
    colArray[4] = B10000000;
    colArray[3] = B10000000;
  } else if(ledPlantTimer <= interval*6) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
    colArray[5] = B10000000;
    colArray[4] = B10000000;
    colArray[3] = B10000000;
    colArray[2] = B10000000;
  } else if(ledPlantTimer <= interval*7) {
    colArray[7] = B10000000;
    colArray[6] = B10000000;
    colArray[5] = B10000000;
    colArray[4] = B10000000;
    colArray[3] = B10000000;
    colArray[2] = B10000000;
    colArray[1] = B10000000;
  } else if(shoot == true) {
    ledPlantStartTime = millis();
    for (byte i=1; i<7; i++) {
      colArray[i] = 0;
    }
  } else {
    GameOver();
    gameStartTime = millis();
    lose = false;
    Reset(currentCol);
  }
}

void ControlPlant(byte colArray[]) {
  potenValue = analogRead(poten);
  potenValue = map(potenValue,1023, 0, 0, 7);
  /*for(byte i=7; i>0; i--) {
    colArray[i] = colArray[i] >> potenValue;
  }*/
  colArray[1] = colArray[1] >> potenValue;
  colArray[2] = colArray[2] >> potenValue;
  colArray[3] = colArray[3] >> potenValue;
  colArray[4] = colArray[4] >> potenValue;
  colArray[5] = colArray[5] >> potenValue;
  colArray[6] = colArray[6] >> potenValue;
  colArray[7] = colArray[7] >> potenValue;
}

void ShootControl(byte colArray[]) {
  
  //Serial.println(btnReading);
  for(byte i=1; i<8; i++) {
    colArray[i] = colArray[i+1];
  } 
  colArray [7] = 0;
}

void Reset(byte colArray[]) {
  ledPlantStartTime = millis();
  topBarStartTime = millis();
  shoot = false;
}

 void LoseOrNot(byte colArray[]) {
  if(colArray[0] == (colArray[0] | colArray[1]) ) {
    lose = true;
  } else {
    lose = false;
  }
}

void GameOver() {
  gameoverStartTime = millis();
  gameoverTimer = millis() - gameoverStartTime;
  while(gameoverTimer <= 2000){
    gameoverTimer = millis() - gameoverStartTime;
    if(gameoverTimer <= 500) {
      Frame(gameOverFace1);
    } else if(gameoverTimer <= 1000) {
      Frame(gameOverFace2);
    } else if(gameoverTimer <= 1500) {
      Frame(gameOverFace1);
    } else {
      Frame(gameOverFace2);
    }
  }
}
  
void loop() {
  
  gameTimer = millis()-gameStartTime;
  if(gameTimer <= 15000) {
    gameSpeed = 1000;
  } else if (gameTimer <= 30000) {
    gameSpeed = 200;
  } else {
    gameSpeed = 100;
  }
  
  btnReading = digitalRead(btn);
  if(btnReading == HIGH) {
    shoot = true;
    for(byte i=0;i<6;i++) {
      ShootControl(currentCol);
      while(globalTimer<=10) {
        globalTimer = millis()-globalStartTime;
        Frame(currentCol);
        //Serial.println(currentCol[1]);
      }
      globalStartTime = millis();
      globalTimer = millis()-globalStartTime;
    }
    LoseOrNot(currentCol);
    if(lose == true) {
      GameOver();
      gameStartTime = millis();
      lose = false;
    }
    Reset(currentCol); 
  } else {
    TopBar(currentCol,gameSpeed);
    LedPlant(currentCol, 1000);
    ControlPlant(currentCol);
    Frame(currentCol);
  }
}
