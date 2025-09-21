#include <Arduino.h>
#include <Joystick.h>
#include "Inputs.h"
#include "RotaryEncoder.h"
#include "Button.h"

// pin modes will be set here
RotaryEncoder leftEncoder = RotaryEncoder(LEFT_ENCODER_CLK, LEFT_ENCODER_DT, 10, VOL_L_LEFT_TURN_JOYSTICK, VOL_L_RIGHT_TURN_JOYSTICK);
RotaryEncoder rightEncoder = RotaryEncoder(RIGHT_ENCODER_CLK, RIGHT_ENCODER_DT, 10, VOL_R_LEFT_TURN_JOYSTICK, VOL_R_RIGHT_TURN_JOYSTICK);

Button buttonSTART = Button(START, START_JOYSTICK);

Button buttonA = Button(BUTTON_A, BUTTON_A_JOYSTICK);
Button buttonB = Button(BUTTON_B, BUTTON_B_JOYSTICK);
Button buttonC = Button(BUTTON_C, BUTTON_C_JOYSTICK);
Button buttonD = Button(BUTTON_D, BUTTON_D_JOYSTICK);

Button buttonFXL = Button(FX_L, FXL_JOYSTICK);
Button buttonFXR = Button(FX_R, FXR_JOYSTICK);

// https://github.com/MHeironimus/ArduinoJoystickLibrary
Joystick_ Joystick(
  0x15,
  JOYSTICK_TYPE_JOYSTICK,
  #ifdef USE_AXES
  7,
  #else
  11,
  #endif
  0,
  #ifdef USE_AXES
  true,
  true,
  #else
  false,
  false,
  #endif
  false,
  false,
  false,
  false,
  false, 
  false, 
  false,
  false,
  false);

// https://arduinogetstarted.com/tutorials/arduino-rotary-encoder#content_how_to_program_for_rotary_encoder

void handleLeftKnob()
{
    int value = digitalRead(leftEncoder.dt_pin);
    // right turn 
    if (value == HIGH) {
      leftEncoder.counter_left = 0;
      if (++leftEncoder.counter_right > leftEncoder.sensitivity) {
        #ifdef USE_AXES
        Joystick.setXAxis(leftEncoder.nextAxisValue());
        #else
        leftEncoder.turned_right = true;
        #endif
        leftEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      leftEncoder.counter_right = 0;
      if (++leftEncoder.counter_left > leftEncoder.sensitivity) {
        #ifdef USE_AXES
        Joystick.setXAxis(leftEncoder.previousAxisValue());
        #else
        leftEncoder.turned_left = true;
        #endif
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
        #ifdef USE_AXES
        Joystick.setYAxis(rightEncoder.previousAxisValue());
        #else
        rightEncoder.turned_right = true;
        #endif
        rightEncoder.counter_right = 0;
      }
    }
    // left turn
    else {
      rightEncoder.counter_right = 0;
      if (++rightEncoder.counter_left > rightEncoder.sensitivity) {
        #ifdef USE_AXES
        Joystick.setYAxis(rightEncoder.nextAxisValue());
        #else
        rightEncoder.turned_left = true;
        #endif
        rightEncoder.counter_left = 0;
      }
    }
}

void setup() {
  Joystick.begin();
  Serial.begin(9600);
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

  #ifndef USE_AXES
  leftEncoder.loop(Joystick);
  rightEncoder.loop(Joystick);
  #endif
}