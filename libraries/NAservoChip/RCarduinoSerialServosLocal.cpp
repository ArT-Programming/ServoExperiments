#include "RCArduinoSerialServosLocal.h"

/*----------------------------------------------------------------------------------------

This is essentially a derivative of the Arduino Servo Library created by Michael Margolis

As the technique is very similar to the Servo class, it can be useful to study in order
to understand the servo class.

What does the library do ? It uses a very inexpensive and common 4017 Counter IC
To generate pulses to independently drive up to 10 servos from two Arduino Pins

As previously mentioned, the library is based on the techniques used in the Arduino Servo
library created by Michael Margolis. This means that the library uses Timer1 and Timer1 output
compare register A.

OCR1A is linked to digital pin 9 and so we use digital pin 9 to generate the clock signal
for the 4017 counter.

Pin 12 is used as the reset pin.

*/

// Timer1 Output Compare A interrupt service routine
// call out class member function OCR1A_ISR so that we can
// access out member variables
ISR(TIMER1_COMPA_vect)
{
    CRCArduinoSerialServos::OCR1A_ISR();
}

void CRCArduinoSerialServos::OCR1A_ISR()
{
    // If the channel number is >= 10, we need to reset the counter
    // and start again from zero.
    // to do this we pulse the reset pin of the counter
    // this sets output 0 of the counter high, effectivley
    // starting the first pulse of our first channel
  if(m_sCurrentOutputChannelA >= RC_CHANNEL_OUT_COUNT)
  {
    // reset our current servo/output channel to 0
    m_sCurrentOutputChannelA = 0;

    // pulse reset on the counter - we set it high here
    PORTB|=16;

    // set the duration of the output pulse
    CRCArduinoSerialServos::setOutputTimerForPulseDurationA();

    // finish the reset pulse - we set it low here
    PORTB^=16;
 }
 else
 {
  // pulse the clock pin high
    PORTB|=2;

    // set the duration of the output pulse
    CRCArduinoSerialServos::setOutputTimerForPulseDurationA();

    // finish the clock pulse - set it back to low
    PORTB^=2;
  }
    // done with this channel so move on.
    m_sCurrentOutputChannelA++;
}
// After we set an output pin high, we need to set the timer to comeback for the end of the pulse
void CRCArduinoSerialServos::setOutputTimerForPulseDurationA()
{
  OCR1A = TCNT1 + m_unChannelOutA[m_sCurrentOutputChannelA];
}

#if defined(MORE_SERVOS_PLEASE)
// Timer1 Output Compare B interrupt service routine
// call out class member function OCR1B_ISR so that we can
// access out member variables
ISR(TIMER1_COMPB_vect)
{
    CRCArduinoSerialServos::OCR1B_ISR();
}

void CRCArduinoSerialServos::OCR1B_ISR()
{
    // If the channel number is >= 10, we need to reset the counter
    // and start again from zero.
    // to do this we pulse the reset pin of the counter
    // this sets output 0 of the counter high, effectivley
    // starting the first pulse of our first channel
  if(m_sCurrentOutputChannelB >= RC_CHANNEL_OUT_COUNT)
  {
    // reset our current servo/output channel to 10 -
    // Note that 10 is the first servo on output compare B
    m_sCurrentOutputChannelB = 0;

    // pulse reset on the counter - we set it high here
    PORTB|=32;

    // set the duration of the output pulse
    CRCArduinoSerialServos::setOutputTimerForPulseDurationB();

    // finish the reset pulse - we set it low here
    PORTB^=32;
 }
 else
 {
  // pulse the clock pin high
    PORTB|=4;

    // set the duration of the output pulse
    CRCArduinoSerialServos::setOutputTimerForPulseDurationB();

    // finish the clock pulse - set it back to low
    PORTB^=4;
  }
    // done with this channel so move on.
    m_sCurrentOutputChannelB++;
}

// After we set an output pin high, we need to set the timer to comeback for the end of the pulse
void CRCArduinoSerialServos::setOutputTimerForPulseDurationB()
{
  OCR1B = TCNT1 + m_unChannelOutB[m_sCurrentOutputChannelB];
}
#endif

// updates a channel to a new value, the class will continue to pulse the channel
// with this value for the lifetime of the sketch or until writeChannel is called
// again to update the value
void CRCArduinoSerialServos::writeMicroseconds(uint8_t nChannel,uint16_t unMicroseconds)
{
    // dont allow a write to a non existent channel
    if(nChannel > RCARDUINO_MAX_SERVOS)
        return;
  
  unMicroseconds += RCARDUINO_SERIAL_SERVO_MIN;
  // constraint the value just in case
  unMicroseconds = constrain(unMicroseconds,RCARDUINO_SERIAL_SERVO_MIN,RCARDUINO_SERIAL_SERVO_MAX);

#if defined(MORE_SERVOS_PLEASE)
  if(nChannel >= RC_CHANNEL_OUT_COUNT)
  {
    // disable interrupts while we update the multi byte value output value
    uint8_t sreg = SREG;
    cli();
     
    m_unChannelOutB[nChannel-RC_CHANNEL_OUT_COUNT] = microsecondsToTicks(unMicroseconds);

    // enable interrupts
    SREG = sreg;
    return;
  }
#endif
 
  // disable interrupts while we update the multi byte value output value
  uint8_t sreg = SREG;
  cli();
 
  m_unChannelOutA[nChannel] = microsecondsToTicks(unMicroseconds);

  // enable interrupts
  SREG = sreg;
}

uint16_t CRCArduinoSerialServos::ticksToMicroseconds(uint16_t unTicks)
{
    return unTicks / 2;
}

uint16_t CRCArduinoSerialServos::microsecondsToTicks(uint16_t unMicroseconds)
{
 return unMicroseconds * 2;
}

void CRCArduinoSerialServos::begin()
{
    // set the pins we will use for channel A (OCR1A) as outputs
    pinMode(9,OUTPUT); // clock uses OCR1A and should not be changed
    pinMode(12,OUTPUT); // reset, if you really needed to, you could change this, but remember to change it in the ISR as well

    // pulse reset
    digitalWrite(12,HIGH);
    digitalWrite(12,LOW);

#if defined (MORE_SERVOS_PLEASE)

    // set the pins we will use for channel B (OCR1B) as outputs
    pinMode(10,OUTPUT); // clock uses OCR1B and should not be changed
    pinMode(13,OUTPUT); // reset, if you really needed to, you could change this, but remember to change it in the ISR as well

    // pulse reset
    digitalWrite(13,HIGH);
    digitalWrite(13,LOW);

#endif

    TCNT1 = 0;              // clear the timer count  

    // Initilialise Timer1
    TCCR1A = 0;             // normal counting mode
    TCCR1B = 2;     // set prescaler of 64 = 1 tick = 4us

    // ENABLE TIMER1 OCR1A INTERRUPT to enabled the first bank (A) of ten servos
    TIFR1 |= _BV(OCF1A);     // clear any pending interrupts;
    TIMSK1 |=  _BV(OCIE1A) ; // enable the output compare interrupt 

#if defined(MORE_SERVOS_PLEASE)

    // ENABLE TIMER1 OCR1B INTERRUPT to enable the second bank (B) of 10 servos
    TIFR1 |= _BV(OCF1B);     // clear any pending interrupts;
    TIMSK1 |=  _BV(OCIE1B) ; // enable the output compare interrupt 

#endif

    OCR1A = TCNT1 + 4000; // Start in two milli seconds
}

// See the .h file
volatile uint16_t CRCArduinoSerialServos::m_unChannelOutA[RC_CHANNEL_OUT_COUNT];
uint8_t CRCArduinoSerialServos::m_sCurrentOutputChannelA;

#if defined(MORE_SERVOS_PLEASE)

volatile uint16_t CRCArduinoSerialServos::m_unChannelOutB[RC_CHANNEL_OUT_COUNT];
uint8_t CRCArduinoSerialServos::m_sCurrentOutputChannelB;

#endif

