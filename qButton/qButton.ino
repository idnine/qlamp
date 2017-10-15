/*
 * qLamp Button
 */

#define BTN_STBY 7
#define BTN_GO   6
#define LED_RED  5
#define LED_GRN  4

bool chkBtn1 = false;
bool chkBtn2 = false;
bool chkReady = false;
int cntReady = 0;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GRN, OUTPUT);
  pinMode(BTN_STBY, INPUT);
  pinMode(BTN_GO, INPUT);

  Serial.begin(9600);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GRN, LOW);
}

void loop() {
  int inChk1 = digitalRead(BTN_STBY);
  int inChk2 = digitalRead(BTN_GO);

  if(!chkBtn1 && (inChk1 == 0) && !chkBtn2 && (inChk2 == 1)) {
    // ============================= STBY
    chkBtn1 = true;
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GRN, LOW);
    Serial.write("STBY\n");
    delay(100);
  } else if(chkBtn1 && (inChk1 == 0) && !chkBtn2 && (inChk2 == 0)) {
    // ============================= GO
    chkBtn2 = true;
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GRN, HIGH);
    Serial.write("GO\n");
    delay(700);
    //chkBtn1 = false;
    //chkBtn2 = false;
    digitalWrite(LED_GRN, LOW);
  } else if(chkBtn1 && (inChk1 == 1)) {
    // ============================= CANCEL
    chkBtn1 = false;
    if(chkBtn2) {
      chkBtn2 = false;
      digitalWrite(LED_GRN, LOW);
    } else {
      Serial.write("CANCEL\n");
    }
    digitalWrite(LED_RED, LOW);
    delay(100);
  } else if(!chkBtn1 && !chkBtn2) {
    // ================================= READY MODE
    if(cntReady == 14) {
      if(chkReady) {
        digitalWrite(LED_RED, HIGH);
        Serial.write("READY-ON\n");
        chkReady = false;
        //delay(100);
      } else {
        digitalWrite(LED_RED, LOW);
        Serial.write("READY-OFF\n");
        chkReady = true;
        //delay(100);
      }
      cntReady = 0;
    }
    cntReady++;
    delay(50);
  }
}
