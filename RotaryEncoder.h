class RotaryEncoder {

public:
  int clk_pin;
  int dt_pin;
  int deadzone;
  volatile int counter_left = 0;
  volatile int counter_right = 0;

  RotaryEncoder(int clk_pin, int dt_pin, int deadzone = 100) : clk_pin(clk_pin), dt_pin(dt_pin), deadzone(deadzone) {
    pinMode(clk_pin, INPUT_PULLUP);
    pinMode(dt_pin, INPUT_PULLUP);
  }
};