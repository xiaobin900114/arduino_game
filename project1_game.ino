unsigned long topBarTimer;
unsigned long topBarstartTime;

byte currentCol[8] = {0,0,0,0,0,0,0,0};

void setup() {
  // put your setup code here, to run once:
  DDRD = B11111111;
  DDRC = B111111;
  DDRB = B11;
  PORTD = B0;
  PORTC = B0;
  PORTB = B0;
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

void TopRunningBar(byte topBar[], byte mask) {
  topBar[0] = B11111111;
  
  topBar[0] ^= (B11000000 >> mask);
}

void TopBar(byte colArray[], int interval) {
  
  topBarTimer = millis() - topBarstartTime;


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
    topBarstartTime = millis();
  }  
}

void GrowingLed(byte colArray[], int interval) {
  //for(byte i=1;i<7; i++) {
   // colArray[i] = 0;
  //}
  byte lightUp = B10000000;
  unsigned long startTime2 = 0;

  unsigned long loopTime = 0;
  
  loopTime = millis() - startTime2;
  
  if(loopTime <= interval) {
    colArray[7] = lightUp;
  } else if(loopTime <= (interval*2) ) {
    colArray[6] = lightUp;
  } else {
    startTime2 = millis();
  }

  Frame(colArray);
  
}

void loop() {
  TopBar(currentCol,500);

  
  Frame(currentCol);
}
