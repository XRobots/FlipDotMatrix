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
   
                if (c == 'a')  {
                    input = 1;
                }                
                else if (c == 'b') {
                    input = 2;
                }
                else if (c == 'c') {
                    input = 3;
                }
                else if (c == 'd') {
                    input = 4;
                }
                else if (c == 'e') {
                    input = 5;
                }
                else if (c == 'f') {
                    input = 6;
                }
                else if (c == 'g') {
                    input = 7;
                }
                else if (c == 'h') {
                    input = 8;
                }
                else if (c == 'i') {
                    input = 9;
                }
                else if (c == 'j') {
                    input = 10;
                }
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
          else if (flipFlag == 2 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 2;
            previousFlipMillis = currentMillis;
            flipFlag = 3;
          }
          else if (flipFlag == 3 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 2.5;
            previousFlipMillis = currentMillis;
            flipFlag = 4;
          }
          else if (flipFlag == 4 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 3;
            previousFlipMillis = currentMillis;
            flipFlag = 5;
          }
          else if (flipFlag == 5 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 3.5;
            previousFlipMillis = currentMillis;
            flipFlag = 6;
          }
          else if (flipFlag == 6 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 4;
            previousFlipMillis = currentMillis;
            flipFlag = 7;
          }
          else if (flipFlag == 7 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 4.5;
            previousFlipMillis = currentMillis;
            flipFlag = 8;
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
          else if(flipFlag == 12 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 4;
            previousFlipMillis = currentMillis;
            flipFlag = 13;
          }
          else if (flipFlag == 13 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 3.5;
            previousFlipMillis = currentMillis;
            flipFlag = 14;
          }
          else if (flipFlag == 14 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 3;
            previousFlipMillis = currentMillis;
            flipFlag = 15;
          }
          else if (flipFlag == 15 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 2.5;
            previousFlipMillis = currentMillis;
            flipFlag = 16;
          }
          else if (flipFlag == 16 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 2;
            previousFlipMillis = currentMillis;
            flipFlag = 17;
          }
          else if(flipFlag == 17 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 1.5;
            previousFlipMillis = currentMillis;
            flipFlag = 18;
          }
          else if(flipFlag == 18 && currentMillis - previousFlipMillis >= flipDelay) {
            demandPos = 1;
            previousFlipMillis = currentMillis;
            flipFlag = 19;
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

          if (demandPos == 1) {
            pos1();
          }
          else if (demandPos == 1.5) {
            pos1a();
          }
          else if (demandPos == 2) {
            pos2();
          }
          else if (demandPos == 2.5) {
            pos2a();
          }
          else if (demandPos == 3) {
            pos3();
          }
          else if (demandPos == 3.5) {
            pos3a();
          }
          else if (demandPos == 4) {
            pos4();
          }
          else if (demandPos == 4.5) {
            pos4a();
          }
          else if (demandPos == 5) {
            pos5();
          }     

          //******** check if the linear axis got to the target yet ********
          //******** if it has draw the pattern *********
          
          encoderDiff = abs(encoder0Target - encoder0Pos);
          if (encoderDiff < 250) {    // if we got to the target then move the flip dot servos

                if (demandPos == 1) {             // flip
                  topState = pattern[0];
                  middleState = pattern[1];
                  bottomState = pattern[2];
                }
                if (demandPos == 1.5) {           // intermediate         
                  topState = prevPattern[0];
                  middleState = prevPattern[1];
                  bottomState = prevPattern[2];
                }
                else if (demandPos == 2) {        // flip
                  topState = pattern[3];
                  middleState = pattern[4];
                  bottomState = pattern[5];
                }
                if (demandPos == 2.5) {           // intermediate 
                  topState = prevPattern[3];
                  middleState = prevPattern[4];
                  bottomState = prevPattern[5];
                }
                else if (demandPos == 3) {        // flip
                  topState = pattern[6];
                  middleState = pattern[7];
                  bottomState = pattern[8];
                }
                if (demandPos == 3.5) {           // intermediate 
                  topState = prevPattern[6];
                  middleState = prevPattern[7];
                  bottomState = prevPattern[8];
                }
                else if (demandPos == 4) {        // flip
                  topState = pattern[9];
                  middleState = pattern[10];
                  bottomState = pattern[11];
                }
                if (demandPos == 4.5) {           // intermediate 
                  topState = prevPattern[9];
                  middleState = prevPattern[10];
                  bottomState = prevPattern[11];
                }
                else if (demandPos == 5) {        // flip
                  topState = pattern[12];
                  middleState = pattern[13];
                  bottomState = pattern[14];
                }

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

void pos1() {
  encoder0Target = 0;
}

void pos1a() {
  encoder0Target = 6000;
}

void pos2() {
  encoder0Target = 12000;
}

void pos2a() {
  encoder0Target = 18000;
}

void pos3() {
  encoder0Target = 24000;
}

void pos3a() {
  encoder0Target = 30000;
}

void pos4() {
  encoder0Target = 36000;
}

void pos4a() {
  encoder0Target = 42000;
}

void pos5() {
  encoder0Target = 48000;
}


void doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}
