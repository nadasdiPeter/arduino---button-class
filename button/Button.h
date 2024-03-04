/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 *   Description:  Button class for arduino projects
 * 
 *       TOGGLE-BUTTON:
 *          - isPressed():  Returns the state of the button. For every buttonpress the state changes from ON to OFF 
 *                          or from OFF to ON and stays in that position till the next button press.
 * 
 *       PRESS-BUTTON:
 *          - isPressed():  Returns true (pressed) as long as the button is pressed.
 *          - onPressed():  Returns true only ones per state changes, - when the button goes from not pressed to pressed.
 *          - onReleased(): Returns true only ones per state changes, - when the button goes from pressed to not pressed.
 *          - shortPressed(): Returns true (pressed) if the buttonPress is shorter than a defined time period. (Default: 1.5 sec)
 *          - longPressed():  Returns true (pressed) if the buttonPress is longer than a defined time period. (Default: 1.5 sec)
 **/

#ifndef BUTTON_H
   #define BUTTON_H

#include <Arduino.h>

#define BUTTON_PRESS_DELAY_TIME                          100
#define DEFAULT_BUTTON_LONG_PRESS_TIME                   1500

enum buttonMode               { press_button, toggle_button };
enum buttonState              { not_pressed, pressed };
enum buttonToggleState        { off, on };
enum buttonResistor           { pull_up_resistor, pull_down_resistor };

class Button
{
   private:
      byte m_Pin;
      buttonState m_State;
      buttonMode m_Mode;
      buttonResistor m_Resistor;
      buttonToggleState m_ToggleState;
      unsigned long int m_Last_Time_State_Changed_ms;
      unsigned long int m_Button_Press_Started_ms;
      unsigned long int m_Button_LongPress_ms;
      bool m_OnPressed;
      bool m_OnReleased;

      /**
       * Returns the current state of the button without any delay protection
       */
      buttonState readState();

   public:
      /**
       * Constructor of the BUTTON class Should not use the default constructore.
       */
      Button();
      
      /**
       * Constructor of the BUTTON class.
       *
       * @param pin The pin of the microcontroller where the BUTTON connected
       * @param resistor The type of the used resistor: pull_up_resistor / pull_down_resistor
       * @param mode The way the button should work: press_button / toggle_button
       */
      Button(byte pin, buttonResistor resistor, buttonMode mode);

      /**
       * Constructor of the BUTTON class.
       *
       * @param pin The pin of the microcontroller where the BUTTON connected
       * @param resistor The type of the used resistor: pull_up_resistor / pull_down_resistor
       * @param mode The way the button should work: press_button / toggle_button
       * @param sate The initial state of the button: pressed / not_pressed
       */
      Button(byte pin, buttonResistor resistor, buttonMode mode, buttonState state);

      /**
       * Defines the pin mode and of the BUTTON.
       */
      void init();

      /**
       * Sets the time limit of the long button press.
       */
      void set_LongPress(unsigned long int long_press_limit);

      /**
       * Returns true (pressed) as long as the button is pressed in press_button mode.
       * Returns the state of the button in toggle_button mode.
       * 
       * @returns buttonState: not_pressed, pressed
       */
      buttonState isPressed();

      /**
       * Returns if the button short-pressed or not.
       * Only works in press_button mode.
       * 
       * @returns buttonState: not_pressed, pressed
       */
      buttonState shortPressed();

      /**
       * Returns if the button long-pressed or not.
       * Only works in press_button mode.
       * 
       * @returns buttonState: not_pressed, pressed
       */
      buttonState longPressed();

      /**
       * Returns true if the button was just pressed.
       * Only works in press_button mode.
       * 
       * @returns true, false
       */
      bool onPressed();

      /**
       * Returns true if the button was just released.
       * Only works in press_button mode.
       * 
       * @returns true, false
       */
      bool onReleased();
};

#endif /* BUTTON_H */