/*  

  Vulintus_IIR_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_IIR_Filter.h" for documentation and change log.

*/

#include "./Vulintus_IIR_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_IIR_Filter::Vulintus_IIR_Filter(Vulintus_Filter_Type ftype, float freq, float initial_value)
{
    filter_type = ftype;                // Set the filter type.
    cutoff_frequency(freq);             // Calculate the decay constant, in microseconds.
    pX = initial_value;                  // Set the initial input value.
    output = initial_value;             // Set the initial output value.
    _prev_output = initial_value;       // Set the previous output value.
    _last_micros = micros();            // Fetch the first update time.
}


// Destructor. //
Vulintus_IIR_Filter::~Vulintus_IIR_Filter(void)
{

}


// Update the filter with a new input value (no specified read time).
float Vulintus_IIR_Filter::input(float new_value)
{
    uint32_t read_time = micros();          // Grab the current microsecond clock time.
    return input(new_value, read_time);     // Pass the current microsecond clock time as the read time.
}


// Update the filter with a new input value (specified read time).
float Vulintus_IIR_Filter::input(float new_value, uint32_t read_time)
{
    // We'll first calculate the time between samples:
    // Δt = t[i] - t[i-1]
    float delta_t = read_time - _last_micros;               // Calculate the time since last update.
    _last_micros = read_time;                               // Update the last update time.
    
    _prev_input = pX;                                        // Shift the current input value to the previous.
    _prev_output = output;                                  // Shift the current output value to the previous.
    pX = new_value;                                          // Update the input value.

    if (filter_type == NO_FILTER) {                         // If the filter is disabled...
        output = pX;                                         // The output is the input.
        return output;                                      // Return the current output value.
    }

    // For IIR low-pass filters, we'll calculate the new output value from the 
    // recurrence relation:
    //        
    // y[i] = (1 - α) * x[i] + α * y[i-1]           (low-pass)
    //
    // y[i] = α * (x[i] - x[i-1]) + α * y[i-1]      (high-pass)
    //
    // The factor, α, is given by:
    //
    // α = 1 - e^(-Δt/τ)
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

    float alpha;                                            // Declare the alpha factor.             
    float tau_dt_ratio = _tau_micros / delta_t;             // Calculate ratio τ/Δt.
    if (tau_dt_ratio > 7) {                                 // If τ/Δt is greater than 7...
        alpha = _tau_micros / (_tau_micros + delta_t);      // Use the τ / (τ + Δt) approximation (error will be < 1%).
    }
    else {                                                  // Otherwise, for longer Δt...                       
        alpha = exp(-delta_t / _tau_micros);                // Use the e^(-Δt/τ) calculation.
    }

    if (filter_type == LOWPASS) {                                   // If the filter is a low-pass filter...
        output = (1 - alpha) * pX + alpha * _prev_output;           // Calculate the new output value.
    }
    else {                                                          // Otherwise, if the filter is a high-pass filter...
        output = alpha * (pX - _prev_input) + alpha * _prev_output; // Calculate the new output value.
    }

    return output;                                          // Return the current output value.
}      