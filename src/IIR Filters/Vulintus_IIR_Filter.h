/*  

  Vulintus_IIR_Filter.h

  copyright 2025, Vulintus, Inc.

  Vulintus' Infinite Impulse Response (IIR) low-pass filter class.

  UPDATE LOG:
    2025-02-19 - Drew Sloan - File first created, adapted from Jon Driscoll's
                              "FilterOnePole" library.
*/

#ifndef _Vulintus_IIR_Filter_H_
#define _Vulintus_IIR_Filter_H_


#include <Arduino.h>						          // Arduino main include file.

#include "./Vulintus_Digital_Filter.h"    // Vulintus digital filter base class.


//CLASSES ************************************************************************************************************//
class Vulintus_IIR_Filter : public Vulintus_Digital_Filter {

  public:

    // Constructor. //
    Vulintus_IIR_Filter(Vulintus_Filter_Type ftype = LOWPASS, float freq = 1.0, float initial_value = 0);
    
    // Destructor. //
    ~Vulintus_IIR_Filter(void);

    // Public Functions. //

    // Update the filter with a new input value.
    float input(float new_value);                       // No specified read time.
    float input(float new_value, uint32_t read_time);   // Specified read time.

    
  private:
  
    // Private Variables. //    
    float _prev_input;                                  // Previous input value.
    float _prev_output;                                 // Previous output value.

};


// CHILD CLASSES *****************************************************************************************************//

class Vulintus_IIR_LowPass_Filter : public Vulintus_IIR_Filter {

  public:
          
      Vulintus_IIR_LowPass_Filter(float freq = 1.0, float initial_value = 0) 
          : Vulintus_IIR_Filter(LOWPASS, freq, initial_value)
      { 
          //empty
      }

};


class Vulintus_IIR_HighPass_Filter : public Vulintus_IIR_Filter {

  public:
  
      Vulintus_IIR_HighPass_Filter(float freq = 1.0, float initial_value = 0) 
          : Vulintus_IIR_Filter(HIGHPASS, freq, initial_value)
      { 
          //empty
      }

};


#endif	//#ifndef _Vulintus_IIR_Filter_H_