class Button {

public:
  int pin;
  int joystick_button;
  int debounce_delay;

  volatile int last_button_state;
  volatile int button_state;

  volatile unsigned long last_debounce_time;

  Button(int pin, char joystick_button, int debounce_delay = 5) : pin(pin), debounce_delay(debounce_delay), joystick_button(joystick_button) {
    pinMode(pin, INPUT_PULLUP);
    last_debounce_time = 0;
    last_button_state = HIGH;
  }

  void loop(Joystick_ joystick) {
    int reading = digitalRead(pin);

    if (reading != last_button_state) {
      last_debounce_time = millis();
    }
  
    if ((millis() - last_debounce_time) > debounce_delay) {
      if (reading != button_state) {
        button_state = reading;
        if (button_state == LOW)
          joystick.setButton(joystick_button-1, 1);
        else
          joystick.setButton(joystick_button-1, 0);
      }
    }

    last_button_state = reading;
  }
};