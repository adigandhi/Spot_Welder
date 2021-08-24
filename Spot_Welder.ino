/*
  Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached from pin 2 to +5V
  - 10 kilohm resistor attached from pin 2 to ground
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPinUp = 9;       // the number of the pushbutton pin
const int buttonPinDown = 11;    // the number of the pushbutton pin
const int buttonWeld = 8;    // the number of the pushbutton pin

//OutPut
const int ledPin4 = 2;      // the number of the LED pin
const int ledPin3 = 3;      // the number of the LED pin
const int ledPin2 = 4;      // the number of the LED pin
const int ledPin1 = 5;      // the number of the LED pin
const int ledPin0 = 6;      // the number of the LED pin
const int ledPin5 = 13;      // the number of the LED pin
const int WeldOutput = 12;      // the number of the LED pin

// Variables will change:
bool ledState0 = LOW;         // the current state of the output pin
bool ledState1 = LOW;         // the current state of the output pin
bool ledState2 = LOW;         // the current state of the output pin
bool ledState3 = LOW;         // the current state of the output pin
bool ledState4 = LOW;         // the current state of the output pin
bool ledState5 = LOW;         // the current state of the output pin
bool weld = LOW;
int buttonStateUp = LOW;             // the current readButtonUp from the input pin
int buttonStateDown = LOW;             // the current buttonStateDown from the input pin
int buttonStateWeld = LOW;             // the current buttonStateWeld from the input pin
int lastButtonStateUp = LOW;   // the previous readButtonUp from the input pin
int lastButtonStateDown = LOW;   // the previous buttonStateDown from the input pin
int lastButtonStateWeld = LOW;   // the previous buttonStateWeld from the input pin
long WeldTimer = 20000;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long LedBlinkDelay = 0;  // the last time the output pin was toggled
unsigned long LedBlinkLast = 0;  // the last time the output pin was toggled


//LED update function

void update_led(void) {
  digitalWrite(ledPin0, ledState0);
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  digitalWrite(ledPin4, ledState4);
}
void setup() {
  pinMode(buttonPinUp, INPUT);
  pinMode(buttonPinDown, INPUT);
  pinMode(buttonWeld, INPUT);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(WeldOutput, OUTPUT);

  // set initial LED state
  update_led();
  digitalWrite(ledPin5, ledState5);

  Serial.begin(115200);

  // prints title with ending line break
  Serial.print("ASCII Table ~ Character Map");

  lastDebounceTime = millis();
}



void loop() {

  // read the state of the switch into a local variable:
  int readButtonUp   = digitalRead(buttonPinUp);
  int readButtonDown = digitalRead(buttonPinDown);
  int readButtonWeld = digitalRead(buttonWeld);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if ((readButtonUp != lastButtonStateUp) || (readButtonDown != lastButtonStateDown) || (readButtonWeld != lastButtonStateWeld)) { 
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the readButtonUp is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the buttonStateUp state has changed:
    if (readButtonUp != buttonStateUp) {
//      Serial.print("\nUp\n");
      buttonStateUp = readButtonUp;
      // only update timer if the new button state is HIGH
      if (buttonStateUp == HIGH) {
        WeldTimer += 10000;
        if(WeldTimer > 500000){
          WeldTimer = 500000;
        }
//        Serial.print(WeldTimer);
//        lastButtonStateUp = readButtonUp;
      }
    }

    // if the buttonStateDown state has changed:
    if (readButtonDown != buttonStateDown) {
//      Serial.print("\nDown\n");
      buttonStateDown = readButtonDown;
      // only update timer if the new button state is HIGH
      if (buttonStateDown == HIGH) {
        WeldTimer -= 10000;
        if(WeldTimer < 10000){
          WeldTimer = 10000;
        }
//        Serial.print(WeldTimer);
      }
    }

    // if the buttonStateWeld state has changed:
    if (readButtonWeld != buttonStateWeld) {
//      Serial.print("\nWeld\n");
      buttonStateWeld = readButtonWeld;
      // only update timer if the new button state is HIGH
      if (buttonStateWeld == HIGH) {
        weld = HIGH;
      }
    }
  }

  // set the LED:
  LedBlinkDelay = millis();
  if((WeldTimer >= 10000) && (WeldTimer <= 100000)){
    if(LedBlinkDelay - LedBlinkLast >=  (WeldTimer/200)){
      ledState0 = !ledState0;
      ledState1 = LOW;
      ledState2 = LOW;
      ledState3 = LOW;
      ledState4 = LOW;
      update_led();
      
      LedBlinkLast = millis();
    }
  }else if((WeldTimer >= 100000) && (WeldTimer <= 200000)){
    if(LedBlinkDelay - LedBlinkLast >=  ((WeldTimer- 100000)/200)){
      ledState0 = HIGH;
      ledState1 = !ledState1;
      ledState2 = LOW;
      ledState3 = LOW;
      ledState4 = LOW;
      
      update_led();
      LedBlinkLast = millis();
    }
  }else if((WeldTimer >= 200000) && (WeldTimer <= 300000)){
    if(LedBlinkDelay - LedBlinkLast >=  ((WeldTimer- 200000)/200)){
      ledState0 = HIGH;
      ledState1 = HIGH;
      ledState2 = !ledState2;
      ledState3 = LOW;
      ledState4 = LOW;
     
      update_led();
      LedBlinkLast = millis();
    }
  }else if((WeldTimer >= 300000) && (WeldTimer <= 400000)){
    if(LedBlinkDelay - LedBlinkLast >=  ((WeldTimer- 300000)/200)){
      ledState0 = HIGH;
      ledState1 = HIGH;
      ledState2 = HIGH;
      ledState3 = !ledState3;
      ledState4 = LOW;
      
      update_led();
      LedBlinkLast = millis();
    }
  }else if((WeldTimer >= 400000) && (WeldTimer <= 500000)){
    if(LedBlinkDelay - LedBlinkLast >=  ((WeldTimer- 400000)/200)){
      ledState0 = HIGH;
      ledState1 = HIGH;
      ledState2 = HIGH;
      ledState3 = HIGH;
      ledState4 = !ledState4;
      update_led();
      LedBlinkLast = millis();
    }
  }

  if(weld == HIGH) {
    delay(500);
    digitalWrite(WeldOutput, HIGH);
    digitalWrite(ledPin5, HIGH);
    delay((WeldTimer/1000));
    digitalWrite(WeldOutput, LOW);
    digitalWrite(ledPin5, LOW);
    weld = LOW;
  }
  

  // save the readButtonUp. Next time through the loop, it'll be the lastButtonStateUp:
  lastButtonStateUp = readButtonUp;
  lastButtonStateDown = readButtonDown;
  lastButtonStateWeld = readButtonWeld;
}
