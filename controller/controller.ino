#include <Arduino.h>
#include <Joystick.h>
#include "Inputs.h"
#include "RotaryEncoder.h"
#include "Button.h"

// pin modes will be set here
RotaryEncoder leftEncoder = RotaryEncoder(LEFT_ENCODER_CLK, LEFT_ENCODER_DT);
RotaryEncoder rightEncoder = RotaryEncoder(RIGHT_ENCODER_CLK, RIGHT_ENCODER_DT);

Button buttonSTART = Button(START, START_JOYSTICK);

Button buttonA = Button(BUTTON_A, BUTTON_A_JOYSTICK);
Button buttonB = Button(BUTTON_B, BUTTON_B_JOYSTICK);
Button buttonC = Button(BUTTON_C, BUTTON_C_JOYSTICK);
Button buttonD = Button(BUTTON_D, BUTTON_D_JOYSTICK);

Button buttonFXL = Button(FX_L, FXL_JOYSTICK);
Button buttonFXR = Button(FX_R, FXR_JOYSTICK);

// https://github.com/MHeironimus/ArduinoJoystickLibrary
Joystick_ Joystick(0x15, JOYSTICK_TYPE_JOYSTICK, 7, 0, true, true, false, false, false, false, false, false, false, false, false);

// https://arduinogetstarted.com/tutorials/arduino-rotary-encoder#content_how_to_program_for_rotary_encoder

void handleLeftKnob()
{
    int value = digitalRead(leftEncoder.dt_pin);
    // right turn 
    if (value == HIGH) {
      leftEncoder.counter_left = 0;
      if (++leftEncoder.counter_right > leftEncoder.sensitivity) {
        Joystick.setXAxis(leftEncoder.nextAxisValue());
        leftEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      leftEncoder.counter_right = 0;
      if (++leftEncoder.counter_left > leftEncoder.sensitivity) {
        Joystick.setXAxis(leftEncoder.previousAxisValue());
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
      if (++rightEncoder.counter_right > rightEncoder.sensitivity) {
        Joystick.setYAxis(rightEncoder.previousAxisValue());
        rightEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      rightEncoder.counter_right = 0;
      if (++rightEncoder.counter_left > rightEncoder.sensitivity) {
        Joystick.setYAxis(rightEncoder.nextAxisValue());
        rightEncoder.counter_left = 0;
      }
    }
}

void setup() {
  Joystick.begin();
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_CLK), handleLeftKnob, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_CLK), handleRightKnob, RISING);
}

void loop() {
  
  buttonA.loop(Joystick);
  buttonB.loop(Joystick);
  buttonC.loop(Joystick);
  buttonD.loop(Joystick);
  buttonFXL.loop(Joystick);
  buttonFXR.loop(Joystick);
  buttonSTART.loop(Joystick);
}