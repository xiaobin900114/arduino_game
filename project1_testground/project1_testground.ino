unsigned long topBarTimer;
unsigned long topBarStartTime;

unsigned long ledPlantTimer;
unsigned long ledPlantStartTime;

const int poten = A7;
int potenValue;


byte currentCol[8] = {0,0,0,0,0,0,0,0};
byte colTest[8] = {B1000,B1000,B1000,B1000,B1000,B1000,B1000,B1000};

void setup() {
  // put your setup code here, to run once:
  DDRD = B11111111;
  DDRC = B111111;
  DDRB = B11;
  PORTD = B0;
  PORTC = B0;
  PORTB = B0;
  pinMode(poten, INPUT);
}

void Frame (byte col_values[]) {
  PORTC = B111111;
  PORTB = B11;
  for(byte x = 0; x<6; x++) {
    PORTC ^= (B100000>>x);
    PORTD = col_values[x];
    delay(1);
    PORTC = B111111;
  }
  for(byte x=0; x<2; x++) {
    PORTB ^= B10>>x;
    PORTD = col_values[x+6];
    delay(1);
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
    colArray[6] = B10000000;
  } else if(ledPlantTimer <= interval*3) {
    colArray[5] = B10000000;
  } else if(ledPlantTimer <= interval*4) {
    colArray[4] = B10000000;
  } else if(ledPlantTimer <= interval*5) {
    colArray[3] = B10000000;
  } else if(ledPlantTimer <= interval*6) {
    colArray[2] = B10000000;
  } else if(ledPlantTimer <= interval*7) {
    colArray[1] = B10000000;
  } else {
    ledPlantStartTime = millis();
    for (byte i=1; i<7; i++) {
      colArray[i] = 0;
    }
  }
}

void ControlPlant(byte colArray[]) {
  potenValue = analogRead(poten);
  potenValue = map(potenValue, 0, 1023, 0, 7);
  /*for(byte i=7; i>0; i--) {
    colArray[i] = colArray[i] >> potenValue;
  }*/

  colArray[0] >>= 1;
  colArray[1] >>0;
  colArray[2] >>1;
  colArray[3] = B1000>>0;
  colArray[4] = B1000 >>1;
  colArray[5] = B1000 >>0;
  colArray[6] = colArray[6] >>1;
  colArray[7] = colArray[7] >>0;
}
  
void loop() {
  //TopBar(currentCol,500);
  //LedPlant(currentCol, 1000);
  ControlPlant(colTest);
  
  Frame(colTest);
}
