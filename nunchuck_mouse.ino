/*
 * WiiChuckDemo -- 
 *
 * 2008 Tod E. Kurt, http://thingm.com/
 *
 */

#include <Arduino.h>
#include <Wire.h>
#include <Mouse.h>
#include "Nunchuck.h"

byte z, c;
int x, y;
int z_hold;

void setup()
{
  Serial.begin(9600);
  Nunchuck.begin();
  Mouse.begin();
}

void loop()
{
  if (Nunchuck.read()) {

    x = (Nunchuck.joystick_x() - JOYSTICK_BASE) / 3;
    y = (JOYSTICK_BASE - Nunchuck.joystick_y()) / 3;

    z = Nunchuck.button_z();
    c = Nunchuck.button_c(); 

    if (abs(x) > 3 || abs(y) > 3) {
      if (z)
        Mouse.move(0, 0, y > 0 ? -1 : 1);
      else
        Mouse.move(x, y, 0);
    }

    if (c) {
      if (!Mouse.isPressed(MOUSE_RIGHT) || !Mouse.isPressed(MOUSE_LEFT)) {
        if (z)
          Mouse.press(MOUSE_RIGHT);
        else
          Mouse.press(MOUSE_LEFT);
      }
    } else {
      if (Mouse.isPressed(MOUSE_RIGHT)) 
        Mouse.release(MOUSE_RIGHT);
      else if (Mouse.isPressed(MOUSE_LEFT))
        Mouse.release(MOUSE_LEFT);
    }
    
    Serial.print("x: "); Serial.print(x, DEC);
    Serial.print("\ty: "); Serial.print(y, DEC);
    Serial.print("\tz: "); Serial.print((byte)z, DEC);
    Serial.print("\tc: "); Serial.println((byte)c, DEC);    
  }

  delay(25);
}
