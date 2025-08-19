#include <Arduino.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "Inputs.h"
#include "RotaryEncoder.h"
#include "Button.h"

// pin modes will be set here
RotaryEncoder leftEncoder = RotaryEncoder(LEFT_ENCODER_CLK, LEFT_ENCODER_DT);
RotaryEncoder rightEncoder = RotaryEncoder(RIGHT_ENCODER_CLK, RIGHT_ENCODER_DT);
Button buttonA = Button(BUTTON_A, 'd');
Button buttonB = Button(BUTTON_B, 'f');
Button buttonC = Button(BUTTON_C, 'j');
Button buttonD = Button(BUTTON_D, 'k');

Button buttonFXL = Button(FX_L, 'c');
Button buttonFXR = Button(FX_R, 'm');
Button buttonSTART = Button(START, 'q');

// https://arduinogetstarted.com/tutorials/arduino-rotary-encoder#content_how_to_program_for_rotary_encoder

void handleLeftKnob()
{
    int value = digitalRead(leftEncoder.dt_pin);
    // right turn 
    if (value == HIGH) {
      leftEncoder.counter_left = 0;
      if (++leftEncoder.counter_right > leftEncoder.deadzone) {
        // TODO: Figure out how much to accelerate
        Keyboard.write('5');
        leftEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      leftEncoder.counter_right = 0;
      if (++leftEncoder.counter_left > leftEncoder.deadzone) {
        // TODO: Figure out how much to accelerate
        Keyboard.write('4');
        leftEncoder.counter_left = 0;
      }
    }
}

void handleRightKnob()
{
    int value = digitalRead(rightEncoder.dt_pin);
    // right turn 
    if (value == HIGH) {
      rightEncoder.counter_left = 0;
      if (++rightEncoder.counter_right > rightEncoder.deadzone) {
        //Mouse.move(0, MOUSE_ACCELERATION, 0);
        Keyboard.write('2');
        rightEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      rightEncoder.counter_right = 0;
      if (++rightEncoder.counter_left > rightEncoder.deadzone) {
        //Mouse.move(0, -MOUSE_ACCELERATION, 0);
        Keyboard.write('3');
        rightEncoder.counter_left = 0;
      }
    }
}

void setup() {
  Keyboard.begin();
  Mouse.begin();
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_CLK), handleLeftKnob, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_CLK), handleRightKnob, RISING);
}

void loop() {
  
  buttonA.loop();
  buttonB.loop();
  buttonC.loop();
  buttonD.loop();
  buttonFXL.loop();
  buttonFXR.loop();
  buttonSTART.loop();
}