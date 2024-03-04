#include "button.h"

Button::Button()
{
   /* Do not use */
}


Button::Button(byte pin, buttonResistor resistor, buttonMode mode)
{
   m_Pin = pin;
   m_Resistor = resistor;
   m_Mode = mode;
   m_State = not_pressed;
   m_ToggleState = off;
   m_Button_Press_Started_ms = 0;
   m_Button_LongPress_ms = DEFAULT_BUTTON_LONG_PRESS_TIME;
   m_OnPressed = false;
   m_OnReleased = false;
}


Button::Button(byte pin, buttonResistor resistor, buttonMode mode, buttonState state)
{
   m_Pin = pin;
   m_Resistor = resistor;
   m_Mode = mode;
   m_State = state;
   m_ToggleState = (state == pressed) ? on : off;
   m_Button_Press_Started_ms = 0;
   m_Button_LongPress_ms = DEFAULT_BUTTON_LONG_PRESS_TIME;
   m_OnPressed = false;
   m_OnReleased = false;
}


void Button::init()
{
   pinMode(m_Pin, INPUT);
}


void Button::set_LongPress(unsigned long int long_press_limit)
{
   m_Button_LongPress_ms = long_press_limit;
}


buttonState Button::readState()
{
   if (m_Resistor == pull_down_resistor)
      return (digitalRead(m_Pin) == HIGH) ? pressed : not_pressed;
   else
      return (digitalRead(m_Pin) == HIGH) ? not_pressed : pressed;
}


buttonState Button::isPressed()
{
   buttonState cur_state = readState();

   if( cur_state != m_State )
   {
      unsigned long now = millis();
      if(m_Last_Time_State_Changed_ms + BUTTON_PRESS_DELAY_TIME <= now)
      {
         m_Last_Time_State_Changed_ms = now;
         if( m_State == pressed )
         {
            m_OnPressed = false;
            m_OnReleased = true;
         }
         else
         {
            m_OnPressed = true;
            m_OnReleased = false;
         }
         m_State = cur_state;
         m_Button_Press_Started_ms = (m_State == pressed) ? now : m_Button_Press_Started_ms;

         if( cur_state == pressed && m_Mode == toggle_button )
         {
            m_ToggleState = (m_ToggleState == off) ? on : off;
         }
      }
   }

   if (m_Mode == press_button)
      return m_State;
   else
      return (m_ToggleState == on) ? pressed : not_pressed;
}


buttonState Button::shortPressed()
{
   if(m_Mode == press_button)
   {
      if(isPressed() == not_pressed && m_Button_Press_Started_ms != 0)
         if( millis() - m_Button_Press_Started_ms < m_Button_LongPress_ms) 
         {
            m_Button_Press_Started_ms = 0;
            return pressed;
         }
   }
   return not_pressed;
}


buttonState Button::longPressed()
{
   if(m_Mode == press_button)
   {
      isPressed();
      if(m_Button_Press_Started_ms != 0)
         if(millis() - m_Button_Press_Started_ms > m_Button_LongPress_ms)
         {
            m_Button_Press_Started_ms = 0;
            return pressed;
         }
   }
   return not_pressed;
}


bool Button::onPressed()
{
   if(m_Mode == press_button)
   {
      isPressed();
      if( m_OnPressed )
      {
         m_OnPressed = false;
         return true;
      }
   }
   return false;
}


bool Button::onReleased()
{
   if(m_Mode == press_button)
   {
      isPressed();
      if( m_OnReleased )
      {
         m_OnReleased = false;
         return true;
      }
   }
   return false;
}