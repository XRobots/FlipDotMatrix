#include <Servo.h>

Servo servo1;   //top
Servo servo2;   // middle
Servo servo3;   // bottom

// wheel encoder interrupts
#define encoder0PinA 2      // encoder 1
#define encoder0PinB 3

volatile long encoder0Pos = 0;    // encoder 1
long encoder0Target = 0;
long encoderDiff = 0;

unsigned long currentMillis;
unsigned long previousMillis;
unsigned long previousFlipMillis;

int flipFlag = 20;
int flipDelay = 800;

int pattern[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int prevPattern[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float demandPos = 1;      // demand pos for linear axis

int topState = 0;     // demand state for servos
int middleState = 0;
int bottomState = 0;

int input;
int inputPrev;

void setup() {

    pinMode(encoder0PinA, INPUT_PULLUP);    // encoder pins
    pinMode(encoder0PinB, INPUT_PULLUP);

    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);

    servo1.attach(8);
    servo2.attach(9);
    servo3.attach(10);

   Serial.begin(115200);

   delay(1000);   


}

void loop() {

  currentMillis = millis();

    if (currentMillis - previousMillis >= 10) {  // start timed loop
          previousMillis = currentMillis;

          if (Serial.available()) {         // read serial terminal
                char c = Serial.read();
   
                input = (c - 'a') + 1;
          }

          if (input == 1) {         // all off
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 0;
             pattern[4] = 0;
             pattern[5] = 0;
             
             pattern[6] = 0;
             pattern[7] = 0;
             pattern[8] = 0;
             
             pattern[9] = 0;
             pattern[10] = 0;
             pattern[11] = 0;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }

          if (input == 2) {         // all on
             pattern[0] = 1;
             pattern[1] = 1;
             pattern[2] = 1;
             
             pattern[3] = 1;
             pattern[4] = 1;
             pattern[5] = 1;
             
             pattern[6] = 1;
             pattern[7] = 1;
             pattern[8] = 1;
             
             pattern[9] = 1;
             pattern[10] = 1;
             pattern[11] = 1;
             
             pattern[12] = 1;
             pattern[13] = 1;
             pattern[14] = 1; 
          }

          if (input == 3) {       // dice 1
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 0;
             pattern[4] = 0;
             pattern[5] = 0;
             
             pattern[6] = 0;
             pattern[7] = 1;
             pattern[8] = 0;
             
             pattern[9] = 0;
             pattern[10] = 0;
             pattern[11] = 0;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }


          if (input == 4) {      // dice 2
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 1;
             pattern[4] = 0;
             pattern[5] = 0;
             
             pattern[6] = 0;
             pattern[7] = 0;
             pattern[8] = 0;
             
             pattern[9] = 0;
             pattern[10] = 0;
             pattern[11] = 1;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }

          if (input == 5) {   // dice 3
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 1;
             pattern[4] = 0;
             pattern[5] = 0;
             
             pattern[6] = 0;
             pattern[7] = 1;
             pattern[8] = 0;
             
             pattern[9] = 0;
             pattern[10] = 0;
             pattern[11] = 1;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }

          if (input == 6) {   // dice 4
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 1;
             pattern[4] = 0;
             pattern[5] = 1;
             
             pattern[6] = 0;
             pattern[7] = 0;
             pattern[8] = 0;
             
             pattern[9] = 1;
             pattern[10] = 0;
             pattern[11] = 1;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }

          if (input == 7) {   // dice 5
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 1;
             pattern[4] = 0;
             pattern[5] = 1;
             
             pattern[6] = 0;
             pattern[7] = 1;
             pattern[8] = 0;
             
             pattern[9] = 1;
             pattern[10] = 0;
             pattern[11] = 1;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }

          if (input == 8) {   // dice 6
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 1;
             pattern[4] = 1;
             pattern[5] = 1;
             
             pattern[6] = 0;
             pattern[7] = 0;
             pattern[8] = 0;
             
             pattern[9] = 1;
             pattern[10] = 1;
             pattern[11] = 1;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 0; 
          }
          if (input == 9) {   // V
             pattern[0] = 1;
             pattern[1] = 0;
             pattern[2] = 0;
             
             pattern[3] = 0;
             pattern[4] = 1;
             pattern[5] = 0;
             
             pattern[6] = 0;
             pattern[7] = 0;
             pattern[8] = 1;
             
             pattern[9] = 0;
             pattern[10] = 1;
             pattern[11] = 0;
             
             pattern[12] = 1;
             pattern[13] = 0;
             pattern[14] = 0; 
          }
          if (input == 10) {   // !V
             pattern[0] = 0;
             pattern[1] = 0;
             pattern[2] = 1;
             
             pattern[3] = 0;
             pattern[4] = 1;
             pattern[5] = 0;
             
             pattern[6] = 1;
             pattern[7] = 0;
             pattern[8] = 0;
             
             pattern[9] = 0;
             pattern[10] = 1;
             pattern[11] = 0;
             
             pattern[12] = 0;
             pattern[13] = 0;
             pattern[14] = 1; 
          }

          // only update if there is new data

          if (input != inputPrev) {
            if (flipFlag == 21) {
              flipFlag = 0;
            }
            else if (flipFlag == 9) {
              flipFlag = 10;
            }
          }

          inputPrev = input;    // bookmark last state
                

          if (flipFlag == 0) {
            demandPos = 1;
            previousFlipMillis = currentMillis;
            flipFlag = 1;
          }
          else if (flipFlag == 1 && currentMillis - previousFlipMillis >= 200) {
            demandPos = 1.5;
            previousFlipMillis = currentMillis;
            flipFlag = 2;
          }
          else if (flipFlag > 1 && flipFlag < 8 && currentMillis - previousFlipMillis >= flipDelay) {
            /*if we are between 2 and 8 inclusive, all we do is increase the flag and set the demand position based on the previous state*/
            demandPos = (flipFlag + 2) / 2;
            previousFlipMillis = currentMillis;
            flipFlag = flipFlag + 1;
          }
          else if (flipFlag == 8 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 5;

            prevPattern[0] = pattern[0];      // bookmark pevious patter for counting down again      
            prevPattern[1] = pattern[1];
            prevPattern[2] = pattern[2];
           
            prevPattern[3] = pattern[3];      
            prevPattern[4] = pattern[4];
            prevPattern[5] = pattern[5];
           
            prevPattern[6] = pattern[6];
            prevPattern[7] = pattern[7];
            prevPattern[8] = pattern[8];
           
            prevPattern[9] = pattern[8];
            prevPattern[10] = pattern[10];
            prevPattern[11] = pattern[11];
           
            prevPattern[12] = pattern[12];
            prevPattern[13] = pattern[13];
            prevPattern[14] = pattern[14];
            
            previousFlipMillis = currentMillis;
            flipFlag = 9;
          }

          else if (flipFlag == 10) {
            demandPos = 5;            
            previousFlipMillis = currentMillis;
            flipFlag = 11;
          }

          else if (flipFlag == 11 && currentMillis - previousFlipMillis >= 200) {
            demandPos = 4.5;
            previousFlipMillis = currentMillis;
            flipFlag = 12;
          } 
          else if(flipFlag > 11 && flipFlag < 19 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = ((18-flipFlag)/2)+1;
            previousFlipMillis = currentMillis;
            flipFlag = flipFlag + 1;
          }
          else if(flipFlag == 19 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 1;         
            
            prevPattern[0] = pattern[3];        // bookmark previous for counting up again
            prevPattern[1] = pattern[4];
            prevPattern[2] = pattern[5];
           
            prevPattern[3] = pattern[6];
            prevPattern[4] = pattern[7];
            prevPattern[5] = pattern[8];
           
            prevPattern[6] = pattern[9];
            prevPattern[7] = pattern[10];
            prevPattern[8] = pattern[11];
           
            prevPattern[9] = pattern[12];
            prevPattern[10] = pattern[13];
            prevPattern[11] = pattern[14];

             
            previousFlipMillis = currentMillis;
            flipFlag = 20;
          }
          else if(flipFlag == 20 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 1;                    
            previousFlipMillis = currentMillis;
            flipFlag = 21;
          }


          // make sure we can drive linear axis from demand position
          // numbers start from 1 and go up in halfs
          // multiply by 2 to always get a whole number, and then minus 2 at the end to get a zero index
          int demandPosIndex = (int)((demandPos*2)-2);
          pos(demandPosIndex);

          //******** check if the linear axis got to the target yet ********
          //******** if it has draw the pattern *********
          
          encoderDiff = abs(encoder0Target - encoder0Pos);
          if (encoderDiff < 250) {    // if we got to the target then move the flip dot servos

                int stateIndex = abs(3 * (demandPos - 1));

                topState = pattern[stateIndex];
                middleState = pattern[stateIndex+1];
                bottomState = pattern[stateIndex+2];
          }
    
          
          // drive linear axis

          if (encoder0Target < encoder0Pos - 200) {   // allow for a deadzone of 250 encoder counts
              analogWrite(5, 255);
              analogWrite(4, 0);
          }
          else if (encoder0Target > encoder0Pos + 200) {   // allow for a deadzone of 250 encoder counts
              analogWrite(5, 0);
              analogWrite(4, 255);
          }

          else {
            analogWrite(4, 0);
            analogWrite(5, 0);
          }       
         
    }



  // make sure we can drive servos with a variable
  
  if (topState == 0) {
    top0();
  }
  
  else if (topState == 1) {
    top1();
  }
  
  if (middleState == 0) {
    middle0();
  }
  
  else if (middleState == 1) {
    middle1();
  }
  
  if (bottomState == 0) {
    bottom0();
  }
  
  else if (bottomState == 1) {
    bottom1();
  }

}

// servo positions - fine tuning goes in here for each servo

void top1() {
    servo1.write(50);    // top
}
void middle1() {
    servo2.write(50);    // middle
}
void bottom1() {
    servo3.write(40);    // bottom
}

void top0() {
    servo1.write(125);    // top
}
void middle0() {
    servo2.write(132);    // middle
}
void bottom0() {
    servo3.write(122);    // bottom
}

// linear axis positions - fine tuning goes in here for encoder feedback etc

void pos(int index) {
  // target always increases by 6000, so 0 index will start at 0 and go up in 6000s
  encoder0Target = 6000 * index;
}

void doEncoderA(){  

  //only read pins once per call to reduce hardware waits
  int pinAState = digitalRead(encoder0PinA);
  int pinBState = digitalRead(encoder0PinB);

  // look for a low-to-high on channel A
  if (pinAState == HIGH) { 
    // check channel B to see which way encoder is turning
    if (pinBState == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (pinBState == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  //only read pins once per call to reduce hardware waits
  int pinAState = digitalRead(encoder0PinA);
  int pinBState = digitalRead(encoder0PinB);

  // look for a low-to-high on channel B
  if (pinBState == HIGH) {   
   // check channel A to see which way encoder is turning
    if (pinAState == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (pinAState == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}
