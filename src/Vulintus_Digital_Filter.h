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


// DEFINITIONS *******************************************************************************************************//

enum Vulintus_Filter_Type : uint8_t {
  NO_FILTER = 0x00,      // No filter, filter is disabled.
  LOWPASS = 0x01,        // Low-pass filter.
  HIGHPASS = 0x02,       // High-pass filter.
};

#define Vulintus_LowPass_Filter Vulintus_IIR_LowPass_Filter     // Use the single-pole IIR filter as the default low-pass filter.
#define Vulintus_HighPass_Filter Vulintus_IIR_HighPass_Filter   // Use the single-pole IIR filter as the default high-pass filter.


//CLASSES ************************************************************************************************************//
class Vulintus_Digital_Filter {

  public:

      // Constructor. //
      Vulintus_Digital_Filter(void);
      
      // Destructor. //
      ~Vulintus_Digital_Filter(void);
      
      // Public Variables. //
      Vulintus_Filter_Type filter_type = LOWPASS;   // Filter type, low pass by default.
      float pX;                                     // Last input value.
      float output;                                 // Current output value.

      // Public Functions. //
      // ** NOTE ** : The filters don't need an initialization function because 
      // they have no hardware components that would require a delay before
      // initialization. All filter setup can occur in the constructor.

      // Set/get the cutoff frequency of the filter.
      float cutoff_frequency(void);
      float cutoff_frequency(float new_freq);
      
      // Update the filter with a new input value.
      virtual float input(float new_value);                       // No specified read time.
      virtual float input(float new_value, uint32_t read_time);   // Specified read time.

  protected:

      // Private Variables. //
      float _tau_micros;                      // Decay constant of the filter, in microseconds.
      uint32_t _last_micros;                  // Time of last update, in microseconds.

};


// CHILD CLASSES *****************************************************************************************************//
#include "./IIR_Filters/Vulintus_IIR_Filter.h"    // Single pole IIR_Filters.


#endif	//#ifndef _VULINTUS_DIGITAL_FILTER_H_