#include <Arduino.h>

#define VOL_L_LEFT 12
#define VOL_L_RIGHT 14

volatile int vol_l_counter = 0;
volatile int vol_l_left_turns = 0;
volatile int vol_l_right_turns = 0;
volatile int threshold = 200;
volatile unsigned long last_time;


void IRAM_ATTR onTurn() {
  //if ((millis() - last_time) < 50) {
  //  return;
  //}

  int vol_l_counter_next = digitalRead(VOL_L_LEFT) + digitalRead(VOL_L_RIGHT) * 2;

  if (vol_l_counter_next > vol_l_counter)
    vol_l_left_turns++;
  else
    vol_l_right_turns++;

  if (vol_l_left_turns > threshold) {
    Serial.println("Turn left");
    vol_l_left_turns = 0;
    vol_l_right_turns = 0;
  }
  else if (vol_l_right_turns > threshold) {
    Serial.println("Turn right");
    vol_l_left_turns = 0;
    vol_l_right_turns = 0;
  }

  vol_l_counter = vol_l_counter_next;
  last_time = millis();

}

void setup() {
  Serial.begin(9600);
  pinMode(VOL_L_LEFT, INPUT_PULLUP);
  pinMode(VOL_L_RIGHT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(VOL_L_LEFT), onTurn, CHANGE);
  attachInterrupt(digitalPinToInterrupt(VOL_L_RIGHT), onTurn, CHANGE);
}

void loop() {}