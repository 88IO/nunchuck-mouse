#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#define JOYSTICK_BASE 130

static uint8_t nunchuck_data[6];

class Nunchuck_ {
private:
  void send_request() {
    Wire.beginTransmission(0x52);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
  }

  char decode_byte (char x) {
    return (x ^ 0x17) + 0x17;
  }

public:
  void begin() {
    Wire.begin();   
    Wire.beginTransmission(0x52);
    Wire.write((uint8_t)0x40);
    Wire.write((uint8_t)0x00);  
    Wire.endTransmission();
  }

  int read() {
      int cnt = 0;
      Wire.requestFrom(0x52, 6);
      while (Wire.available()) {
          nunchuck_data[cnt] = decode_byte(Wire.read());
          cnt++;
      }
      send_request();  // send request for next data payload
      // If we recieved the 6 bytes, then go print them
      if (cnt >= 5) {
          return 1;   // success
      }
      return 0; //failure
  }

  int button_z() {
    return !((nunchuck_data[5] >> 0) & 1); 
  }

  int button_c() {
    return !((nunchuck_data[5] >> 1) & 1); 
  }

  int joystick_x() {
    return nunchuck_data[0]; 
  }

  int joystick_y() {
    return nunchuck_data[1]; 
  }
};

extern Nunchuck_ Nunchuck;

#endif