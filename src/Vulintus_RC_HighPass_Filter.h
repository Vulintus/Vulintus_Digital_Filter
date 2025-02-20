/*  
    Vulintus_RC_HighPass_Filter.h

    copyright 2025, Vulintus, Inc.

    Vulintus' simple RC high-pass filter class.

    UPDATE LOG:
      2025-02-19 - Drew Sloan - File first created, adapted from Jon Driscoll's
                                "FilterOnePole" library.

*/

#ifndef _VULINTUS_RC_HIGHPASS_FILTER_H_
#define _VULINTUS_RC_HIGHPASS_FILTER_H_


#include <Arduino.h>						          // Arduino main include file.

#include "./Vulintus_Digital_Filter.h"    // Vulintus digital filter base class.


//CLASSES ************************************************************************************************************//
class Vulintus_RC_HighPass_Filter : public Vulintus_Digital_Filter {

  public:

    // Constructor. //
    Vulintus_RC_HighPass_Filter(float freq, float initial_value = 0);
    
    // Destructor. //
    ~Vulintus_RC_HighPass_Filter(void);

    // Public Functions. //
    void begin();                                       // Initialization.
    
    // Update the filter with a new input value.
    float input(float new_value);                       // No specified read time.
    float input(float new_value, uint32_t read_time);   // Specified read time.

  private:
  
    // Private Variables. //    
    float _prev_input;                                  // Previous input value.
    float _prev_output;                                 // Previous output value.

};

#endif	//#ifndef _VULINTUS_RC_HIGHPASS_FILTER_H_