/*  

  Vulintus_IIR_HighPass_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_IIR_HighPass_Filter.h" for documentation and change log.

*/

#include "./Vulintus_IIR_HighPass_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_IIR_HighPass_Filter::Vulintus_IIR_HighPass_Filter(float freq, float initial_value)
{
    _cutoff_freq = freq;                // Set the cutoff frequency.
    X = initial_value;                  // Set the initial input value.
    output = initial_value;             // Set the initial output value.
    _prev_output = initial_value;       // Set the previous output value.
}


// Destructor. //
Vulintus_IIR_HighPass_Filter::~Vulintus_IIR_HighPass_Filter(void)
{

}


// Initialization.
void Vulintus_IIR_HighPass_Filter::begin(void)
{
    cutoff_frequency(_cutoff_freq);     // Calculate the decay constant, in microseconds.
    _last_micros = micros();            // Fetch the first update time.
}


// Update the filter with a new input value (no specified read time).
float Vulintus_IIR_HighPass_Filter::input(float new_value)
{
    uint32_t read_time = micros();          // Grab the current microsecond clock time.
    return input(new_value, read_time);     // Pass the current microsecond clock time as the read time.
}


// Update the filter with a new input value (specified read time).
float Vulintus_IIR_HighPass_Filter::input(float new_value, uint32_t read_time)
{
    // We'll first calculate the time since the time separation between samples:
    // Δt = t[i] - t[i-1]
    float delta_t = read_time - _last_micros;               // Calculate the time since last update.
    _last_micros = read_time;                               // Update the last update time.

    _prev_input = X;                                        // Shift the current input value to the previous.
    _prev_output = output;                                  // Shift the current output value to the previous.
    X = new_value;                                          // Update the input value.

    // For IIR high-pass filters, we'll calculate the new output value from the 
    // recurrence relation:
    //
    // y[i] = α * (x[i] - x[i-1]) + α * y[i-1]
    //
    // The factor, α, is given by:
    //
    // α = e^(-Δt/τ)
    //
    // where Δt is the time between samples and τ is the decay constant. 
    // However, calls to the exp() function can be computationally expensive. So 
    // long as Δt is small compared to τ, we can quickly approximate α like so:
    //
    // α = τ / (τ + Δt)
    // 
    // The error difference between the exponential calculation and the 
    // approximation is less than 1% for τ/Δt > 7 and less than 0.1% for 
    // τ/Δt > 22.
    //
    // https://en.wikipedia.org/wiki/High-pass_filter#Discrete-time_realization

    float alpha;                                            // Declare the alpha factor.             
    float tau_dt_ratio = _tau_micros / delta_t;             // Calculate ratio τ/Δt.
    if (tau_dt_ratio > 7) {                                 // If τ/Δt is greater than 7...
        alpha = _tau_micros / (_tau_micros + delta_t);      // Use the τ / (τ + Δt) approximation (error will be < 1%).
    }
    else {                                                  // Otherwise, for longer Δt...                       
        alpha = exp(-delta_t / _tau_micros);                // Use the e^(-Δt/τ) calculation.
    }
    output = alpha * (X - _prev_input) + alpha * _prev_output;
    
    return output;                                          // Return the current output value.
}      