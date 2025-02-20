/*  

  Vulintus_RC_HighPass_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_RC_HighPass_Filter.h" for documentation and change log.

*/

#include "./Vulintus_RC_HighPass_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_RC_HighPass_Filter::Vulintus_RC_HighPass_Filter(float freq, float initial_value)
{
    _cutoff_freq = freq;                // Set the cutoff frequency.
    X = initial_value;                  // Set the initial input value.
    output = initial_value;             // Set the initial output value.
    _prev_output = initial_value;       // Set the previous output value.
}


// Destructor. //
Vulintus_RC_HighPass_Filter::~Vulintus_RC_HighPass_Filter(void)
{

}


// Initialization.
void Vulintus_RC_HighPass_Filter::begin(void)
{
    cutoff_frequency(_cutoff_freq);     // Calculate the decay constant, in microseconds.
    _last_micros = micros();            // Fetch the first update time.
}


// Update the filter with a new input value (no specified read time).
float Vulintus_RC_HighPass_Filter::input(float new_value)
{
    uint32_t read_time = micros();          // Grab the current microsecond clock time.
    return input(new_value, read_time);     // Pass the current microsecond clock time as the read time.
}


// Update the filter with a new input value (specified read time).
float Vulintus_RC_HighPass_Filter::input(float new_value, uint32_t read_time)
{
    // We'll first calculate the time since the time separation between samples:
    // Δt = t[i] - t[i-1]
    float delta_t = read_time - _last_micros;               // Calculate the time since last update.
    _last_micros = read_time;                               // Update the last update time.

    _prev_input = X;                                        // Shift the current input value to the previous.
    _prev_output = output;                                  // Shift the current output value to the previous.
    X = new_value;                                          // Update the input value.

    // For a simple RC high-pass filter, we'll first calculate the smoothing 
    // factor, α, which is given by:
    //
    // α = τ / (τ + Δt)
    //
    // where τ is the decay constant. Then we'll calculate the new output value
    // from the recurrence relation, which is given by:
    //
    // y[i] = α * y[i-1] + α * (x[i] - x[i-1]).
    //
    // https://en.wikipedia.org/wiki/High-pass_filter#Discrete-time_realization

    float alpha = _tau_micros / (_tau_micros + delta_t);
    output = alpha * _prev_output + alpha * (X - _prev_input);

    return output;                                          // Return the current output value.
}      