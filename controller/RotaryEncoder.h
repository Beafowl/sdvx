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

  RotaryEncoder(int clk_pin, int dt_pin, int sensitivity = 1) : clk_pin(clk_pin), dt_pin(dt_pin), sensitivity(sensitivity) {
    pinMode(clk_pin, INPUT_PULLUP);
    pinMode(dt_pin, INPUT_PULLUP);
  }

  int nextAxisValue() {
    return (axis_value = (axis_value + axis_increments) % (max_axis_value + 1));
  }
  int previousAxisValue() {
    axis_value -= axis_increments;
    if (axis_value < 0)
      axis_value = max_axis_value;
    return axis_value;
  }
};