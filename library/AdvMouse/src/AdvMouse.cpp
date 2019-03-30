/*
  AdvMouse.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "AdvMouse.h"

#if defined(_USING_HID)

/*
static const uint8_t _hidReportDescriptor[] PROGMEM = {
  
  //  Mouse
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x85, 0x01,                    //     REPORT_ID (1)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
};*/
/*
static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01,   // Usage Page (Generic Desktop)
  0x09, 0x02,   // Usage (Mouse)
  0xA1, 0x01,   // Collection (Application)
  0x85, 0x01,   // HID report ID = 1
  // buttons
  0x05, 0x09,   //   Usage Page (Button)
  0x19, 0x01,   //   Usage Minimum (Button #1)
  0x29, 0x05,   //   Usage Maximum (Button #5)
  0x15, 0x00,   //   Logical Minimum (0)
  0x25, 0x01,   //   Logical Maximum (1)
  0x95, 0x05,   //   Report Count (5)
  0x75, 0x01,   //   Report Size (1)
  0x81, 0x02,   //   Input (Data, Variable, Absolute)  // byte 0
  // X, Y
  0x05, 0x01,   //   Usage Page (Generic Desktop)
  0x09, 0x30,   //   Usage (X)
  0x09, 0x31,   //   Usage (Y)
  0x16, 0x01, 0x80, //   Logical Minimum (-32,767)
  0x26, 0xFF, 0x7F, //   Logical Maximum (32,767)
  0x36, 0x01, 0x80, //   Physical Minimum (-32,767)
  0x46, 0xFF, 0x7F, //   Physical Maxiumum (32,767)
  0x75, 0x10,   //   Report Size (16),
  0x95, 0x02,   //   Report Count (2),
  0x81, 0x06,   //   Input (Data, Variable, Relative) // Byte 1-2, 3-4
  // Wheel
  0x09, 0x38,   //   Usage (Wheel)
  0x15, 0x81,   //   Logical Minimum (-127)
  0x25, 0x7F,   //   Logical Maximum (127)
  0x35, 0x81,   //   Phyiscal Minimum (-127)
  0x45, 0x7F,   //   Physical Maxiumum (127)
  0x75, 0x08,   //   Report Size (8)
  0x95, 0x01,   //   Report Count (1)
  0x81, 0x06,   //   Input (Data, Variable, Relative) // Byte 5
  0xC0      // End Collection
};
*/

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01,   // Usage Page (Generic Desktop)
  0x09, 0x02,   // Usage (Mouse)
  0xA1, 0x01,   // Collection (Application)
  0x85, 0x01,   // HID report ID = 1 
  0x05, 0x09,   //   Usage Page (Button)
  0x19, 0x01,   //   Usage Minimum (Button #1)
  0x29, 0x05,   //   Usage Maximum (Button #5)
  0x15, 0x00,   //   Logical Minimum (0)
  0x25, 0x01,   //   Logical Maximum (1)
  0x95, 0x05,   //   Report Count (5)
  0x75, 0x01,   //   Report Size (1)
  0x81, 0x02,   //   Input (Data, Variable, Absolute)
  0x95, 0x01,   //   Report Count (1)
  0x75, 0x03,   //   Report Size (3)
  0x81, 0x03,   //   Input (Constant) // Byte 1
  0x05, 0x01,   //   Usage Page (Generic Desktop)
  0x09, 0x30,   //   Usage (X)
  0x09, 0x31,   //   Usage (Y)
  0x16, 0x01, 0x80, //   Logical Minimum (-32,767)
  0x26, 0xFF, 0x7F, //   Logical Maximum (32,767)
  0x36, 0x01, 0x80, //   Physical Minimum (-32,767)
  0x46, 0xFF, 0x7F, //   Physical Maxiumum (32,767)
  0x75, 0x10,   //   Report Size (16),
  0x95, 0x02,   //   Report Count (2),
  0x81, 0x06,   //   Input (Data, Variable, Relative) // Byte 3, 5
  0x09, 0x38,   //   Usage (Wheel)
  0x15, 0x81,   //   Logical Minimum (-127)
  0x25, 0x7F,   //   Logical Maximum (127)
  0x35, 0x81,   //   Phyiscal Minimum (-127)
  0x45, 0x7F,   //   Physical Maxiumum (127)
  0x75, 0x08,   //   Report Size (8)
  0x95, 0x01,   //   Report Count (1)
  0x81, 0x06,   //   Input (Data, Variable, Relative) // Byte 6
  0xC0      // End Collection
};


//================================================================================
//================================================================================
//	Mouse

AdvMouse_::AdvMouse_(void) : _buttons(0)
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void AdvMouse_::begin(void) 
{
  _isReportSent = true;
}

void AdvMouse_::end(void) 
{
}

void AdvMouse_::click(uint8_t b)
{
	_buttons = b;
	move(0,0,0);
	_buttons = 0;
	move(0,0,0);
}

bool AdvMouse_::needSendReport(void)
{
  return !_isReportSent;
}

void AdvMouse_::move(int16_t x, int16_t y, signed char wheel)
{
	uint8_t m[6];
	m[0] = _buttons;
  m[1] = x & 0xFF;
  m[2] = (x>>8) & 0xFF;
  m[3] = y & 0xFF;
  m[4] = (y>>8) & 0xFF;
  m[5] = wheel;
	HID().SendReport(1,m,6);
  _isReportSent = true;
}

void AdvMouse_::buttonsWithoutMove(uint8_t b)
{
  if (b != _buttons)
  {
    _buttons = b;
    _isReportSent = false;
  }
}

void AdvMouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);   
	}
}

void AdvMouse_::press(uint8_t b) 
{
	buttons(_buttons | b);
}

void AdvMouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

void AdvMouse_::press_(uint8_t b) 
{
  buttonsWithoutMove(_buttons | b);
}

void AdvMouse_::release_(uint8_t b)
{
  buttonsWithoutMove(_buttons & ~b);
}


bool AdvMouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0) 
		return true;
	return false;
}

AdvMouse_ AdvMouse;

#endif
