/*  

  Vulintus_Digital_Filter.cpp
  
  copyright 2025, Vulintus, Inc.

  See "Vulintus_Digital_Filter.h" for documentation and change log.

*/

#include "./Vulintus_Digital_Filter.h"     // Library header.


// CLASS PUBLIC FUNCTIONS ****************************************************// 

// Constructor. //
Vulintus_Digital_Filter::Vulintus_Digital_Filter(void)
{

}


// Destructor. //
Vulintus_Digital_Filter::~Vulintus_Digital_Filter(void)
{

}


// Get the cutoff frequency of the filter.
float Vulintus_Digital_Filter::cutoff_frequency(void)
{
    float tau = _tau_micros * 1e-6;             // Convert the decay constant to seconds.
    float cutoff_freq = 1.0 / (2.0 * PI * tau); // Calculate the cutoff frequency.
    return cutoff_freq;                         // Return the cutoff frequency.
}


// Set the cutoff frequency of the filter.
float Vulintus_Digital_Filter::cutoff_frequency(float new_freq)
{
    // The cutoff frequency of an RC filter is given by:
    // f_c = 1 / (2πτ), where τ = RC.
    // The decay constant, τ, is the time it takes for the filter to decay to
    // 1/e of its original value. Solving the previous equation for τ, we get:
    // τ = 1 / (2πf_c).
    
    _tau_micros = 1.0 / (2.0 * PI * new_freq);  // Set the decay constant, τ = 1/ω, in seconds.
    _tau_micros *= 1e6;                         // Convert the decay constant to microseconds.
    return new_freq;                            // Return the cutoff frequency.
}


// Update the filter with a new input value (No specified read time).
float Vulintus_Digital_Filter::input(float new_value)
{
    return (float) 0;
}


// Update the filter with a new input value.
float Vulintus_Digital_Filter::input(float new_value, uint32_t read_time)
{
    return (float) 0;
} 