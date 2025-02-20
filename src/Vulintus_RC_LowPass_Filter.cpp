/*  

  Vulintus_RC_LowPass_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_RC_LowPass_Filter.h" for documentation and change log.

*/

#include "./Vulintus_RC_LowPass_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_RC_LowPass_Filter::Vulintus_RC_LowPass_Filter(float freq, float initial_value)
{
  _cutoff_freq = freq;                // Set the cutoff frequency.
  X = initial_value;                  // Set the initial input value.
  output = initial_value;             // Set the initial output value.
  _prev_output = initial_value;       // Set the previous output value.
}


// Destructor. //
Vulintus_RC_LowPass_Filter::~Vulintus_RC_LowPass_Filter(void)
{

}


// Initialization.
void Vulintus_RC_LowPass_Filter::begin(void)
{
  cutoff_frequency(_cutoff_freq);     // Calculate the decay constant, in microseconds.
  _last_micros = micros();            // Fetch the first update time.
}


// Update the filter with a new input value (no specified read time).
float Vulintus_RC_LowPass_Filter::input(float new_value)
{
    uint32_t read_time = micros();          // Grab the current microsecond clock time.
    return input(new_value, read_time);     // Pass the current microsecond clock time as the read time.
}


// Update the filter with a new input value, using the specified micros() time.
float Vulintus_RC_LowPass_Filter::input(float new_value, uint32_t read_time)
{
  // We'll first calculate the time since the time separation between samples:
  // Δt = t[i] - t[i-1]
  float delta_t = read_time - _last_micros;           // Calculate the time since last update.
  _last_micros = read_time;                           // Update the last update time.

  _prev_output = output;                              // Shift the current output value to the previous.
  X = new_value;                                      // Update the input value.

  // For a simple RC low-pass filter, we'll first use the difference equation 
  // given by:
  //
  // y[i] = β * y[i-1] + (1 - β) * x[i]
  //
  // where
  //
  // β = e^(-ω0 * Δt).
  //
  // Substituting with ω0 = 1/τ for the β calculation, we get:
  //
  // β = e^(-Δt/τ).
  //
  // https://en.wikipedia.org/wiki/Low-pass_filter#Difference_equation_through_discrete_time_sampling

    float beta = exp(-delta_t / _tau_micros);
    output = beta * _prev_output + (1 - beta) * X;

  return output;                                      // Return the current output value.
}