class Button {

public:
  int pin;
  char input_character;
  int debounce_delay;

  volatile int last_button_state;
  volatile int button_state;

  volatile unsigned long last_debounce_time;

  Button(int pin, char input_character, int debounce_delay = 5) : pin(pin), debounce_delay(debounce_delay), input_character(input_character) {
    pinMode(pin, INPUT_PULLUP);
    last_debounce_time = 0;
    last_button_state = HIGH;
  }

  void loop() {
    int reading = digitalRead(pin);

    if (reading != last_button_state) {
      last_debounce_time = millis();
    }
  
    if ((millis() - last_debounce_time) > debounce_delay) {
      if (reading != button_state) {
        button_state = reading;
        if (button_state == LOW)
          Keyboard.press(input_character);
        else
          Keyboard.release(input_character);
      }
    }

    last_button_state = reading;
  }
};