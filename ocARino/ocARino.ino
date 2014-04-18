//OcARina V1.0
//Kyle Mcaslan 18/04/14
//requires Teensy 3.0 and Teensyduino software

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  //touch pins
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);  
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  //LED pins
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);

}

void loop() 


{  
  //begin reading midi
  usbMIDI.read();
  
  //read touch pins and activate midi note
  int note;
  while (touchRead(15) > 3000){
    note = 62;
  }
  while (touchRead(16) > 3000){
    note = 64;
  }
  while (touchRead(17) > 3000){
    note = 66;
  }
  while (touchRead(18) > 3000){
    note = 67;
  }
  while (touchRead(19) > 3000){
    note = 69;
  }
  while (touchRead(22) > 3000){
    note = 72;
  }


  //decide if the fan is being blown
  // a small threshhold is used to avoid glitches
  if (analogRead(A0)/8 > 20 ){
    usbMIDI.sendNoteOn(note ,analogRead(A0)/8, 2);
    //fade LEDs according to fan speed
    analogWrite(4,analogRead(A0)/4);
    analogWrite(2,analogRead(A0)/4);
  }
  //turn note and LEDs off
  else {
    usbMIDI.sendNoteOff(note ,analogRead(A0)/8, 2);
    analogWrite(4,10);
    analogWrite(2,10);
  }

  delay(1);
}
