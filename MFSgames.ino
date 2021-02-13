// Preprocessor part --------------------------------------

#define BTN1   A1
#define BTN2   A2
#define BTN3   A3

#define num0   0b11000000
#define num1   0b11111001
#define num2   0b10100100
#define num3   0b10110000
#define num4   0b10011001
#define num5   0b10010010
#define num6   0b10000010
#define num7   0b11111000
#define num8   0b10000000
#define num9   0b10010000

#define DOTCHR 0b10000000

// Gloabal variables --------------------------------------

byte digits[] = {0xf8, 0xf4, 0xf2, 0xf1};
byte introMask[][4] = {
  {0b11111111, 0b11111111, 0b11111111, 0b11111110},
  {0b11111111, 0b11111111, 0b11111110, 0b11111110},
  {0b11111111, 0b11111110, 0b11111110, 0b11111110},
  {0b11111110, 0b11111110, 0b11111110, 0b11111110},
  {0b11011110, 0b11111110, 0b11111110, 0b11111110},
  {0b10011110, 0b11111110, 0b11111110, 0b11111111},
  {0b10011010, 0b11111110, 0b11111111, 0b11111111},
  {0b10010010, 0b11111111, 0b11111111, 0b11111111},
  {0b10010010, 0b11111111, 0b11111111, 0b11111111},

  {0b10010010, 0b11101111, 0b11111111, 0b11111110},
  {0b10010010, 0b11001111, 0b11111110, 0b10111111},
  {0b10010010, 0b10001110, 0b10111111, 0b11110111},
  {0b10010010, 0b10001110, 0b11110111, 0b11111111},
  {0b10010010, 0b10000110, 0b11111111, 0b11111111},
  {0b10010010, 0b10000110, 0b11111111, 0b11111111},

  {0b10010010, 0b10000110, 0b11110111, 0b11111111},
  {0b10010010, 0b10000110, 0b11100011, 0b11111111},
  {0b10010010, 0b10000110, 0b11000011, 0b11111111},
  {0b10010010, 0b10000110, 0b11000010, 0b11111111},
  {0b10010010, 0b10000110, 0b11000010, 0b11111111},

  {0b10010010, 0b10000110, 0b11000010, 0b11111001},
  {0b10010010, 0b10000110, 0b11000010, 0b11001111},
  {0b10010010, 0b10000110, 0b11000010, 0b11001001},
  {0b10010010, 0b10000110, 0b11000010, 0b11001000},
  {0b10010010, 0b10000110, 0b11000010, 0b10001000},
  {0b10010010, 0b10000110, 0b11000010, 0b10001000},
  {0b10010010, 0b10000110, 0b11000010, 0b10001000},
  {0b11111111, 0b11111111, 0b11111111, 0b11111111},
  {0b10010010, 0b10000110, 0b11000010, 0b10001000},
  {0b11111111, 0b11111111, 0b11111111, 0b11111111},
  {0b10010010, 0b10000110, 0b11000010, 0b10001000},
};

byte menuMap[] = {
  num1, num2, num3, num4
};

byte dotMenuPos = 0;

typedef enum {
  IntroMode,
  MenuMode,
  Game1Mode
} Mode_t;

Mode_t nowMode = IntroMode;

bool btnStates[] = {0, 0, 0};


// Fuctions declorations ----------------------------------

void chr(byte Data, byte digit);
void printMap(byte pmap[]);
void printIntro();
void btnCheck();
void displayNow();


// Main code ----------------------------------------------

void setup() {
  Serial.begin(9600);
  
  // Pins for display  
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);   
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  if (nowMode == IntroMode) printIntro();

  nowMode = MenuMode;
}

void loop() {
  btnCheck();
  displayNow();

  delay(1);
}


// Functions defenitions ----------------------------------

void displayNow() {
  switch (nowMode) {
    case MenuMode:
      printMap(menuMap);
      break;
  }
}

void btnCheck() {
  if (!digitalRead(BTN1) && !btnStates[0]) {
    switch (nowMode) {
      case MenuMode:
        if (--dotMenuPos > 3) dotMenuPos = 3;
        break;
    }
  }

  if (!digitalRead(BTN2) && !btnStates[1]) {
     switch (nowMode) {
      case MenuMode:
        if (++dotMenuPos > 3) dotMenuPos = 0;
        break;
    }
  }

  if (!digitalRead(BTN3) && !btnStates[2]) {
    
  }
  
  btnStates[0] = !digitalRead(BTN1);
  btnStates[1] = !digitalRead(BTN2);
  btnStates[2] = !digitalRead(BTN3);
}

void printIntro() {
  for (float i = 0; i < sizeof(introMask)/sizeof(introMask[0]); i += 0.005)
    printMap(introMask[int(floor(i))]);
}

void printMap(byte pmap[]) {
//  if (nowMode == MenuMode) pmap[dotMenuPos] += DOTCHR;
  
  for (byte i = 0; i < 4; ++i) {
    chr(((nowMode == MenuMode)&&(dotMenuPos == i))?pmap[i]+DOTCHR:pmap[i], 3-i);
  }
}

void chr (byte Data, byte digit) {
  digitalWrite (4, LOW);
  shiftOut(8, 7, MSBFIRST, Data);
  shiftOut(8, 7, MSBFIRST, digits[digit]);
  digitalWrite (4, HIGH);
}
