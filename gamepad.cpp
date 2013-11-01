/* 
* -------------------------------------------------------------------------
* Arduino Leonardo  -  USB HID Gamepad - using internal pullup resistors
* -------------------------------------------------------------------------
* Copyright Vincent Morneault      October - November 2013
* VincentMorneault@gmail.com
* This code module is licensed public domain
* -------------------------------------------------------------------------
* Uses modified HID.cpp and USBAPI.h provided by "That Guy"
* at http://www.imaginaryindustries.com/blog/?p=80
*
* Based off code from Kevin Peat
* at https://github.com/devonshire/arduino-joystick
* -------------------------------------------------------------------------
*/

const int PIN_BUT_A = 2;
const int PIN_BUT_B = 3;
const int PIN_BUT_SELECT = 4;
const int PIN_BUT_START = 5;

const int PIN_BUT_UP = 6;
const int PIN_BUT_DOWN = 7;
const int PIN_BUT_LEFT = 8;
const int PIN_BUT_RIGHT = 9;


class Button {
private:
  int pin;
  boolean pressed;

public:
  Button();
  Button(int _pin) {
    pin = _pin;
    pressed = false;

    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
  }

  boolean isPressed() {
    return pressed;
  }

  int hasChanged() {
    if(!pressed && digitalRead(pin) == LOW) {
      pressed = true;
      return true;
    }
    else if(pressed && digitalRead(pin) == HIGH) {
      pressed = false;
      return true;
    }

    return false;
  }
};


Button *up, *down, *left, *right, *a, *b, *select, *start;

JoyState_t joySt;

void setup() {
  up = new Button(PIN_BUT_UP);
  down = new Button(PIN_BUT_DOWN);
  left = new Button(PIN_BUT_LEFT);
  right = new Button(PIN_BUT_RIGHT);

  a = new Button(PIN_BUT_A);
  b = new Button(PIN_BUT_B);
  start = new Button(PIN_BUT_START);
  select = new Button(PIN_BUT_SELECT);

  joySt.xAxis = 127;
  joySt.yAxis = 127;
  joySt.zAxis = 127;
  joySt.xRotAxis = 0;
  joySt.yRotAxis = 0;
  joySt.zRotAxis = 0;
  joySt.throttle = 0;
  joySt.rudder = 0;
  joySt.hatSw1 = 0;
  joySt.hatSw2 = 0;
  joySt.buttons = 0;
}

void loop() {
  if(up->hasChanged()) {
    joySt.yAxis = up->isPressed() ? 255 : 127;
  }

  if(down->hasChanged()) {
    joySt.yAxis = down->isPressed() ?  0 : 127;
  }

  if(left->hasChanged()) {
    joySt.xAxis = left->isPressed() ? 0 : 127;
  }

  if(right->hasChanged()) {
    joySt.xAxis = right->isPressed() ? 255 : 127;
  }

  if(a->hasChanged()) {
    joySt.buttons = a->isPressed() ? (joySt.buttons | 1) : (joySt.buttons & 254);
  }

  if(b->hasChanged()) {
    joySt.buttons = b->isPressed() ? (joySt.buttons | 2) : (joySt.buttons & 253);
  }

  if(start->hasChanged()) {

  }

  if(select->hasChanged()) {

  }

  Joystick.setState(&joySt);
}