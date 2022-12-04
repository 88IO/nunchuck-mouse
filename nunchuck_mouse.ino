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
      Mouse.move(x, y, 0);
    }

    if (c) {
      if (!Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.press(MOUSE_LEFT);
      }
    } else {
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
      }
    }
    
    if (z) {
      if (!Mouse.isPressed(MOUSE_RIGHT)) {
        Mouse.press(MOUSE_RIGHT);
      }
    } else {
      if (Mouse.isPressed(MOUSE_RIGHT)) {
        Mouse.release(MOUSE_RIGHT);
      }
    }

    Serial.print("x: "); Serial.print(x, DEC);
    Serial.print("\ty: "); Serial.print(y, DEC);
    Serial.print("\tz: "); Serial.print((byte)z, DEC);
    Serial.print("\tc: "); Serial.println((byte)c, DEC);    
  }

  delay(25);
}
