/*  

  Vulintus_Digital_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_Digital_Filter.h" for documentation and change log.

*/

#include "./Vulintus_Digital_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_Digital_Filter::Vulintus_Digital_Filter(Vulintus_Filter_Type filter_type, \
        float freq, float initial_value)
    : _filter_type(filter_type), _cutoff_freq(freq)
{
    last_input = initial_value;     // Set the initial input value.
    _Y[0] = initial_value;          // Set the initial output value.
    _Y[1] = initial_value;          // Set the previous output value.
}


// Destructor. //
Vulintus_Digital_Filter::~Vulintus_Digital_Filter(void)
{

}


// Initialization.
void Vulintus_Digital_Filter::begin(void)
{
    cutoff_frequency(_cutoff_freq);     // Calculate the decay constant, in microseconds.
    _last_micros = micros();            // Fetch the first update time.
}


// Get the cutoff frequency of the filter.
float Vulintus_Digital_Filter::cutoff_frequency(void)
{
    return _cutoff_freq;                        // Return the cutoff frequency.
}


// Set the cutoff frequency of the filter.
float Vulintus_Digital_Filter::cutoff_frequency(float new_freq)
{
    _cutoff_freq = new_freq;                    // Set the new cutoff frequency.
    _tau_micros = 1.0 / (2.0 * PI * new_freq);  // Set the decay constant, τ = 1/ω, in seconds.
    _tau_micros *= 1e6;                         // Convert the decay constant to microseconds.
    return _cutoff_freq;                        // Return the cutoff frequency.
}


// Update the filter with a new input value, using the current micros() time.
float Vulintus_Digital_Filter::input(float new_value)
{
    uint32_t read_time = micros();                      // Grab the current microsecond clock time.
    return input(new_value, read_time);                 // Update the filter with the new value.
}        


// Update the filter with a new input value, using the specified micros() time.
float input(float new_value, uint32_t read_time)
{
    uint32_t dt = read_time - _last_micros;             // Calculate the time since last update.
    _last_micros = read_time;                           // Update the last update time.

    _Y[1] = _Y[0];                                      // Shift the current output value to the previous.
    last_input = new_value;                             // Update the input value.

    uint32_t tau_samples = _tau_micros / dt;            // Calculate the decay constant in samples.

    float amp_factor;                                   // Amplitude factor for the filter.
    #ifdef ARM_FLOAT
        amp_factor = expf(-1.0/tau_samples);            // This equals 1 if called quickly.
    #else
        amp_factor = exp(-1.0/tau_samples);             // This equals 1 if called quickly.
    #endif

    _Y[0] = (1.0-amp_factor)*last_input + amp_factor*_Y[1];     // Calculate the new output value.

    return output();                                    // Return the current output value.
}      

// Return the current output value of the filter.
float Vulintus_Digital_Filter::output(void)
{
    float output_val;                           // Output value to return.
    switch (_filter_type) {                     // Switch between the different filter types.

        case SINGLE_POLE_HIGHPASS:              // High-pass filter.
            output_val = last_input - _Y[0];    // The output is the difference.
            break;

        case SINGLE_POLE_LOWPASS:               // Low-pass filter.
            output_val = _Y[0];                 // The output is the last value.
            break;

        case INTEGRATOR:                        // Trapezoidal integrator.
            output_val = _Y[0];                 // Same output as low-pass filter...
            output_val *= _tau_micros;          // ...but normalized.
            output_val *= 1.0e6;                // Convert the timescale back to seconds.
            break;
            
        case DIFFERENTIATOR:                    // Difference quotient differentiator.
            output_val = last_input - _Y[0];    // Same output as high-pass filter...
            output_val /= _tau_micros;          // ...but normalized.
            output_val *= 1.0e6;                // Convert the timescale back to seconds.
            break;

    }
    return output_val;                          // Return the output value.
}  