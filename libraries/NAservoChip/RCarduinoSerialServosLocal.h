
/**************************************************************************************
// RCArduinoChannels by DuaneB is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
//
// http://rcarduino.blogspot.com
//
*****************************************************************************************************************************/

#ifndef __RCARDUINOSERIALSERVOS__
#define __RCARDUINOSERIALSERVOS__

#include "Arduino.h"

// COMMENT OR UNCOMMENT THIS LINE TO ENABLE THE SECOND BANK OF SERVOS
#define MORE_SERVOS_PLEASE 1
// the second bank of servos uses pin 10 (clock) and 13 (reset) to drive an additional ten servos.
// the first bank uses pin 9 (clock) and 12 (reset)

// THIS IS FOR ADVANCED USERS ONLY -
//
// Change the channel out count to adjust the frequency,
//
// BEFORE DOING THIS VERIFY THAT YOUR SERVOS AND ESCS ARE COMPATIBLE
// WITH HIGHER AND VARIABLE REFRESH RATES
//
// The library blindly pulses all ten servos one and after another
// If you change the RC_CHANNEL_OUT_COUNT to 4 servos, the library will pulse them more frequently than
// it can ten -
// 10 servos at 1500us = 15ms = 66Hz
// 4 Servos at 1500us = 6ms = 166Hz
// if you wanted to go even higher, run two servos on each 4017
// 2 Servos at 1500us = 3ms = 333Hz
#define RC_CHANNEL_OUT_COUNT 10

#if defined (MORE_SERVOS_PLEASE)
#define RCARDUINO_MAX_SERVOS (RC_CHANNEL_OUT_COUNT*2)
#else
#define RCARDUINO_MAX_SERVOS (RC_CHANNEL_OUT_COUNT)
#endif

// Minimum and Maximum servo pulse widths, you could change these,
// Check the servo library and use that range if you prefer
#define RCARDUINO_SERIAL_SERVO_MIN 700
#define RCARDUINO_SERIAL_SERVO_MAX 2500

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CRCArduinoSerialServos
//
// A class for generating signals in combination with a 4017 Counter
//
// Output upto 10 Servo channels using just digital pins 9 and 12
// 9 generates the clock signal and must be connected to the clock pin of the 4017
// 12 generates the reset pulse and must be connected to the master reset pin of the 4017
//
// The class uses Timer1, as this prevents use with the servo library
// The class uses pins 9 and 12
// The class does not adjust the servo frame to account for variations in pulse width,
// on the basis that many RC transmitters and receivers designed specifically to operate with servos
// output signals between 50 and 100hz, this is the same range as the library
//
// Use of an additional pin would provide for error detection, however using pin 12 to pulse master reset
// at the end of every frame means that the system is essentially self correcting
//
// Note
// This is a simplified derivative of the Arduino Servo Library created by Michael Margolis
// The simplification has been possible by moving some of the flexibility provided by the Servo library
// from software to hardware.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CRCArduinoSerialServos
{
public:
    CRCArduinoSerialServos();

    // configures timer1
    static void begin();

    // called by the timer interrupt service routine, see the cpp file for details.
    static void OCR1A_ISR();
   
#if defined(MORE_SERVOS_PLEASE)
    static void OCR1B_ISR();
#endif

    // called to set the pulse width for a specific channel, pulse widths are in microseconds - degrees are for wimps !
    static void writeMicroseconds(uint8_t nChannel,uint16_t nMicroseconds);

protected:
    // this sets the value of the timer1 output compare register to a point in the future
    // based on the required pulse with for the current servo
    static void setOutputTimerForPulseDurationA();
   
    // Records the current output channel values in timer ticks
    // Manually set by calling writeChannel, the function adjusts from
    // user supplied micro seconds to timer ticks
    volatile static uint16_t m_unChannelOutA[RC_CHANNEL_OUT_COUNT];
    // current output channel, used by the timer ISR to track which channel is being generated
    static uint8_t m_sCurrentOutputChannelA;
   
#if defined(MORE_SERVOS_PLEASE)
    // Optional channel B for servo number 10 to 19
    volatile static uint16_t m_unChannelOutB[RC_CHANNEL_OUT_COUNT];
    static uint8_t m_sCurrentOutputChannelB;
    static void setOutputTimerForPulseDurationB();
#endif

    // two helper functions to convert between timer values and microseconds
    static uint16_t ticksToMicroseconds(uint16_t unTicks);
    static uint16_t microsecondsToTicks(uint16_t unMicroseconds);
};

#endif

