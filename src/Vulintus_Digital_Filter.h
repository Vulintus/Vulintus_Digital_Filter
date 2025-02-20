/*  
    Vulintus_Digital_Filter.h

    copyright 2025, Vulintus, Inc.

    A collection of digital filter classes used in Vulintus devices' firmware.
    This library started as a stripped-down fork of Jon Driscoll's "Filters" 
    library, but has since grown to include a variety of digital filters used by
    Vulintus.

    UPDATE LOG:
      2025-02-18 - Drew Sloan - Library first created, adapted from Jon 
                                Driscoll's "Filters" library.                                

*/

#ifndef _VULINTUS_DIGITAL_FILTER_H_
#define _VULINTUS_DIGITAL_FILTER_H_

#include <Arduino.h>						// Arduino main include file.


//CLASSES ************************************************************************************************************//
class Vulintus_Digital_Filter {

  public:

      // Constructor. //
      Vulintus_Digital_Filter(void);
      
      // Destructor. //
      ~Vulintus_Digital_Filter(void);
      
      // Public Variables. //
      float X;                                // Last input value.
      float output;                           // Current output value.

      // Public Functions. //
      virtual void begin();                   // Initialization.

      // Set/get the cutoff frequency of the filter.
      float cutoff_frequency(void);
      float cutoff_frequency(float new_freq);
      
      // Update the filter with a new input value.
      virtual float input(float new_value);                       // No specified read time.
      virtual float input(float new_value, uint32_t read_time);   // Specified read time.

  protected:

      // Private Variables. //
      float _cutoff_freq;                     // Cutoff frequency of the filter.
      float _tau_micros;                      // Decay constant of the filter, in microseconds.
      uint32_t _last_micros;                  // Time of last update, in microseconds.

};


// CHILD CLASSES *****************************************************************************************************//
#include "./Vulintus_IIR_LowPass_Filter.h"    // Single pole IIR low-pass filter.
#include "./Vulintus_RC_LowPass_Filter.h"     // Simple RC low-pass filter.
#include "./Vulintus_RC_HighPass_Filter.h"    // Simple RC high-pass filter.


// DEFINITIONS *******************************************************************************************************//
#define Vulintus_LowPass_Filter Vulintus_IIR_LowPass_Filter     // Use the IIR filter as the default low-pass filter.
#define Vulintus_HighPass_Filter Vulintus_RC_HighPass_Filter    // Use the simple RC filter as the default high-pass filter.


#endif	//#ifndef _VULINTUS_DIGITAL_FILTER_H_