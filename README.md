# Button class

- TOGGLE-BUTTON:
  - isPressed():  Returns the state of the button. For every buttonpress the state changes from ON to OFF or from OFF to ON and stays in that position till the next button press.

- PRESS-BUTTON:
  - isPressed():  Returns true (pressed) as long as the button is pressed.
  - onPressed():  Returns true only ones per state changes, - when the button goes from not pressed to pressed.
  - onReleased(): Returns true only ones per state changes, - when the button goes from pressed to not pressed.
  - shortPressed(): Returns true (pressed) if the buttonPress is shorter than a defined time period.
  - longPressed():  Returns true (pressed) if the buttonPress is longer than a defined time period.
