class RotaryEncoder {

public:
  int clk_pin;
  int dt_pin;
  int sensitivity;
  volatile int counter_left = 0;
  volatile int counter_right = 0;

  volatile int axis_value = 0;
  int axis_increments = 1;
  int max_axis_value = 1023;

  int left_turn_button;
  int right_turn_button;
  volatile bool turned_left = false;
  volatile bool turned_right = false;
  long last_change = 0;
  long change_wait_time = 50;

  RotaryEncoder(int clk_pin, int dt_pin, int sensitivity = 1, int left_turn_button = 0, int right_turn_button = 0)
   : clk_pin(clk_pin), dt_pin(dt_pin), sensitivity(sensitivity), left_turn_button(left_turn_button), right_turn_button(right_turn_button) {
    pinMode(clk_pin, INPUT_PULLUP);
    pinMode(dt_pin, INPUT_PULLUP);
  }

  #ifdef USE_AXES
  int nextAxisValue() {
    return (axis_value = (axis_value + axis_increments) % (max_axis_value + 1));
  }
  int previousAxisValue() {
    axis_value -= axis_increments;
    if (axis_value < 0)
      axis_value = max_axis_value;
    return axis_value;
  }
  #else
  void loop(Joystick_ joystick) {
    if (turned_left) {
      turned_left = false;
      last_change = millis();
      joystick.setButton(left_turn_button-1, 1);
      joystick.setButton(right_turn_button-1, 0);
      return;
    }
    else if (turned_right) {
      turned_right = false;
      last_change = millis();
      joystick.setButton(right_turn_button-1, 1);
      joystick.setButton(left_turn_button-1, 0);
      return;
    }
    // wait for a certain time until the button should be released
    if (millis() - last_change > change_wait_time) {
      joystick.setButton(left_turn_button-1, 0);
      joystick.setButton(right_turn_button-1, 0);
    }
  }
  #endif
};