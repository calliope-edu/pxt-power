/**
 * (c) 2021, Micro:bit Educational Foundation and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "pxt.h"

#if MICROBIT_CODAL

#include "Timer.h"
#include "MicroBitCompat.h"

#ifndef MICROBIT_ID_MAKECODE_POWER
#define MICROBIT_ID_MAKECODE_POWER 9000
#endif

#endif // MICROBIT_CODAL


enum class FullPowerSource {
    //% block="Knopf A"
    A  = MICROBIT_ID_BUTTON_A,
    //% block="Knopf B"
    B  = MICROBIT_ID_BUTTON_B,
    //% block="Pin P0"
    P0 = MICROBIT_ID_IO_P0,
    //% block="Pin P1"
    P1 = MICROBIT_ID_IO_P1,
    //% block="Pin P2"
    P2 = MICROBIT_ID_IO_P2
};

enum class LowPowerMode {
    //% block="weiterlaufen"
    Continue = 0,
    //% block="warten"
    Wait = 1
};

enum class LowPowerEnable {
    //% block="verhindern"
    Prevent,
    //% block="erlauben"
    Allow
};


//% block="Power"
//% icon="\uf011"
//% color=#AA278D
namespace power {

#if MICROBIT_CODAL
int timerEventValue  = 1;
#endif // MICROBIT_CODAL

void lowPowerRequest(LowPowerMode mode = LowPowerMode::Continue);

/**
  * Request low power when the next idle
  * @param mode If Continue, then return immediately; if Wait, then pause until a power-up event occurs 
  */
//% help=power/low-power-request
//% group="Energieverbrauch"
//% weight=700
//% block="niedrigen Verbauch anfordern||und $mode"
//%
void lowPowerRequest(LowPowerMode mode) {
#if MICROBIT_CODAL
    if ( mode == LowPowerMode::Wait)
        uBit.power.deepSleep();
    else
        uBit.power.deepSleepAsync();
#else
    uBit.sleep(0);
#endif
} 


/**
  * Pause for a fixed interval, and request low power when idle.
  * @param interval The period of time to pause, in milliseconds.
  */
//% help=power/low-power-for
//% group="Energieverbrauch"
//% weight=600
//% interval.shadow=longTimePicker
//% block="niedrigen Verbauch für $interval ms anfordern"
//%
void lowPowerPause(int interval) {
#if MICROBIT_CODAL
    uBit.power.deepSleep(interval);
#else
    uBit.sleep(interval);
#endif
}


/**
  * Prevent or allow low power.
  * Prevent and allow requests should occur in pairs.
  * The default is to allow.
*/
//% help=power/low-power-enable
//% weight=500
//% block="niedrigen Verbrauch %enable"
//%
void lowPowerEnable(LowPowerEnable enable) {
#if MICROBIT_CODAL
    switch ( enable)
    {
        case LowPowerEnable::Prevent:
            uBit.power.powerDownDisable();
            break;

        case LowPowerEnable::Allow:
            uBit.power.powerDownEnable();
            break;

        default:
            break;
    }
#endif
}


/**
  * Determine if low power is enabled
*/
//% help=power/low-power-is-enabled
//%
bool lowPowerIsEnabled() {
#if MICROBIT_CODAL
    return uBit.power.powerDownIsEnabled();
#else
    return false;
#endif
}


/**
  * Do something repeatedy with full power using a timer.
  * @param interval the time (in ms) for the timer.
  * @param code the code to execute
  */
//% help=power/full-power-every
//% group="Energieverbrauch"
//% weight=800
//% blockAllowMultiple=1
//% interval.shadow=longTimePicker
//% afterOnStart=true
//% block="normalen Verbrauch alle $interval ms"
//%
void fullPowerEvery(int interval, Action code) {
#if MICROBIT_CODAL
    registerWithDal( MICROBIT_ID_MAKECODE_POWER, timerEventValue, code);
    // CODAL_TIMER_EVENT_FLAGS_WAKEUP makes the timer event trigger power up
    system_timer_event_after( 0, MICROBIT_ID_MAKECODE_POWER, timerEventValue, CODAL_TIMER_EVENT_FLAGS_WAKEUP);
    system_timer_event_every( interval, MICROBIT_ID_MAKECODE_POWER, timerEventValue++, CODAL_TIMER_EVENT_FLAGS_WAKEUP);
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}


/**
  * Set whether the source should trigger full power.
  * @param source the source to set
  * @param enable true to trigger full power
  */
//% help=power/full-power-source-enable
//%
void fullPowerSourceEnable(FullPowerSource source, bool enable) {
#if MICROBIT_CODAL
    switch ( source)
    {
        case FullPowerSource::A:
          uBit.buttonA.wakeOnActive(enable ? 1 : 0);
          break;

        case FullPowerSource::B:
          uBit.buttonB.wakeOnActive(enable ? 1 : 0);
          break;

        case FullPowerSource::P0:
        case FullPowerSource::P1:
        case FullPowerSource::P2:
        {
            MicroBitPin *pin = getPin((int)source);
            pin->wakeOnActive(enable ? 1 : 0);
            break;
        }
        default:
            break;
    }
#endif
}


/**
  * Determine if the source will trigger full power.
  * @param source the source to check
  * @return true if the source will trigger full power
  */
//% help=power/full-power-source-is-enabled
//%
bool fullPowerSourceIsEnabled(FullPowerSource source) {
#if MICROBIT_CODAL
    switch ( source)
    {
        case FullPowerSource::A:
          return uBit.buttonA.isWakeOnActive() ? true : false;
          break;

        case FullPowerSource::B:
          return uBit.buttonB.isWakeOnActive() ? true : false;
          break;
        
        case FullPowerSource::P0:
        case FullPowerSource::P1:
        case FullPowerSource::P2:
        {
            MicroBitPin *pin = getPin((int)source);
            return pin->isWakeOnActive() ? true : false;
            break;
        }
        default:
          break;
    }
#endif
    return false;
}


/**
  * Set the source to trigger full power.
  * @param source the source to set
  */
//% help=power/full-power-on
//% group="Energieverbrauch"
//% weight=900
//% block="normalen Verbrauch mit %source aktivieren"
//%
void fullPowerOn(FullPowerSource source) {
  fullPowerSourceEnable(source, true);
}


} // namespace power
