/*  Vulintus_Digital_Filter.h

    copyright 2025, Vulintus, Inc.

    A collection of digital filter classes used in Vulintus devices' firmware.
    This library is largely a stripped-down derivation of Jon Driscoll's 
    "Filters" library that doesn't include as much testing and verification
    functionality.
    Single pole digital filter class commonly used in Vulintus firmware.

    UPDATE LOG:
      2025-02-18 - Drew Sloan - File first created, adapted from Jon Driscoll's
                                "FilterOnePole" library.

*/

#ifndef _VULINTUS_DIGITAL_FILTER_H_
#define _VULINTUS_DIGITAL_FILTER_H_

#include <Arduino.h>						// Arduino main include file.


// DEFINITIONS *******************************************************************************************************//

// Filter types. //
enum Vulintus_Filter_Type : uint8_t {
  SINGLE_POLE_HIGHPASS = 0x00,   // Single-pole high-pass filter.
  SINGLE_POLE_LOWPASS = 0x01,    // Single-pole low-pass filter.
  INTEGRATOR = 0x02,             // Trapezoidal integrator.
  DIFFERENTIATOR = 0x03,         // Difference quotient differentiator.
};

#define HIGHPASS SINGLE_POLE_HIGHPASS   // Set "HIGHPASS" as shorthand for "SINGLE_POLE_HIGHPASS".
#define LOWPASS SINGLE_POLE_LOWPASS     // Set "LOWPASS" as shorthand for "SINGLE_POLE_LOWPASS".


//CLASSES ************************************************************************************************************//
class Vulintus_Digital_Filter {

  public:

      // Constructor. //
      Vulintus_Digital_Filter(Vulintus_Filter_Type filter_type = SINGLE_POLE_HIGHPASS, \
          float freq = 1.0, float initial_value = 0);
      
      // Destructor. //
      ~Vulintus_Digital_Filter();
      
      // Public Variables. //
      float last_input;                       // Last input value.

      // Public Functions. //
      void begin();                           // Initialization.

      float cutoff_frequency(void);           // Get the cutoff frequency of the filter.
      float cutoff_frequency(float new_freq); // Set the cutoff frequency of the filter.
      
      float input(float new_value);           // Update the filter with a new input value.
      float output(void);                     // Return the current output value of the filter.
      

  private:

      // Private Variables. //
      Vulintus_Filter_Type _filter_type;      // Single-pole filter type.
      float _cutoff_freq;                     // Cutoff frequency of the filter.
      float _Y[2];                            // Current and previos output value.
      float _tau_micros;                      // Decay constant of the filter, in microseconds.
      uint32_t _last_micros;                  // Time of last update, in microseconds.

};

#endif	//#ifndef _VULINTUS_DIGITAL_FILTER_H_