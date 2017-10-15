/*
 * Cue Lamp, 8x8 LED Dot Matrix MAX7219
 */

#define DP_CS   6
#define DP_CLK  7
#define DP_DATA 5

const int goBlink = 100;
const int aliveMax = 50;

String serialBuff = "";

void setup() {
  pinMode(DP_CS, OUTPUT);
  pinMode(DP_CLK, OUTPUT);
  pinMode(DP_DATA, OUTPUT);
  Serial.begin(9600);
  displayInit();
}

void loop() {
  while(Serial.available() > 0) {
    char inChar = (char)Serial.read();
    if(inChar == '\n') {
      // ===========================================
      if(serialBuff == "STBY") {
        displayStby();
      } else if(serialBuff == "CANCEL") {
        displayAlive(1);
      } else if(serialBuff == "READY-ON") {
        displayAlive(1);
      } else if(serialBuff == "READY-OFF") {
        displayAlive(0);
      } else if(serialBuff == "GO") {
        displayGo();
        delay(50);
        displayAlive(1);
      }
      // ===========================================
      serialBuff = "";
    } else {
      serialBuff += inChar;
    }
  }
}

void spiWrite(int line, uint8_t data) {
  digitalWrite(DP_CS, LOW);
  shiftOut(DP_DATA, DP_CLK, MSBFIRST, line);
  shiftOut(DP_DATA, DP_CLK, MSBFIRST, data);
  digitalWrite(DP_CS, HIGH);
}

void displayInit() {
  spiWrite(0x09, 0);  // Decode Mode : Matrix
  spiWrite(0x0a, 7);  // Intensity 7
  spiWrite(0x0b, 7);  // Scan Limit 7
  spiWrite(0x0c, 1);  // Display On
  for(int i=1; i<=8; i++) spiWrite(i, 0);
  delay(10);
  displayIntoIdle();
  displayIntoIdle();
  displayIntoIdle();
}

void displayAlive(int onoff) {
    if(onoff) {
      spiWrite(1, 0x00);
      spiWrite(2, 0x00);
      spiWrite(3, 0x00);
      spiWrite(4, 0x18);
      spiWrite(5, 0x18);
      spiWrite(6, 0x00);
      spiWrite(7, 0x00);
      spiWrite(8, 0x00);
    } else if(onoff == 0) {
      for(int i=1; i<=8; i++) {
        spiWrite(i, 0x00);
      }
    }
}

void displayStby() {
  spiWrite(1, 0xff);
  spiWrite(2, 0x81);
  spiWrite(3, 0x81);
  spiWrite(4, 0x81);
  spiWrite(5, 0x81);
  spiWrite(6, 0x81);
  spiWrite(7, 0x81);
  spiWrite(8, 0xff);
}

void displayGo() {
  for(int i=1; i<=8; i++) {
    spiWrite(i, 0xff);
  }
  delay(goBlink);
  spiWrite(0x0c, 0);
  delay(goBlink);
  spiWrite(0x0c, 1);
  delay(goBlink);
  spiWrite(0x0c, 0);
  delay(goBlink);
  spiWrite(0x0c, 1);
  delay(goBlink);
  spiWrite(0x0c, 0);
  delay(goBlink);
  spiWrite(0x0c, 1);
  delay(goBlink);
  for(int i=1; i<=8; i++) {
    spiWrite(i, 0x00);
  }
  displayIntoIdle();
}

void  displayIntoIdle() {  
  spiWrite(1, 0x81);
  spiWrite(4, 0);
  spiWrite(5, 0);
  spiWrite(8, 0x81);
  delay(100);
  spiWrite(1, 0);
  spiWrite(2, 0x42);
  spiWrite(7, 0x42);
  spiWrite(8, 0);
  delay(100);
  spiWrite(2, 0);
  spiWrite(3, 0x24);
  spiWrite(6, 0x24);
  spiWrite(7, 0);
  delay(100);
  spiWrite(3, 0);
  spiWrite(4, 0x18);
  spiWrite(5, 0x18);
  spiWrite(6, 0);
  delay(200);
}
