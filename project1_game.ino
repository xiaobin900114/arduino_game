unsigned long startTime = 0;

byte A[] = {  B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
byte L[] = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

byte O2[] = {
  B00111100,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B00000000,
  B00000000
};



byte LetterLove[] = {
  B11100111,
  B10011001,
  B10000001,
  B10000001,
  B10000001,
  B01000010,
  B00100100,
  B00011000
};

byte currentCol[8] = {
  B0,
  B0,
  B0,
  B0,
  B0,
  B0,
  B0,
  B0
};



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

void TopBar(byte topBar[], int runTime) {
    //use a for loop to control the first column 
  for(byte i=0; i<8; i++) {
    topBar[0] = B11111111;
    
    topBar[0] ^= (B11000000 >> i);

    //use a while loop to control and display the top bar
    
    unsigned long loopTime = 0;
    
    while (loopTime <= runTime) {
      Frame(topBar);
      loopTime = millis() - startTime;
    }
    startTime = millis();
  }
}

void loop() {
  TopBar(currentCol,1000);
}
