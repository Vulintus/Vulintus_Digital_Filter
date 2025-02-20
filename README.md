# Vulintus_Digital_Filter

A collection of Arduino-compatible digital filter classes used in Vulintus devices' firmware. This library started as a stripped-down fork of Jon Driscoll's "Filters" library, but has since grown to include a variety of digital filters used by Vulintus. Basic examples for Arduino are included. This library is, as always, a work-in-progress.

---

## Simple Infinite Impulse Response (IIR) Filters

The the most basic low- and high-pass filters, "Vulintus_IIR_LowPass_Filter" and "Vulintus_IIR_HighPass_Filter", respectively, are designed as single-pole discretized RC filters. The implementation of these filters is adapted largely from the Wikipedia pages for \[low-pass\](https://en.wikipedia.org/wiki/Low-pass_filter#Difference_equation_through_discrete_time_sampling) and \[high-pass\](https://en.wikipedia.org/wiki/High-pass_filter#Discrete-time_realization) filters.

For IIR high-pass filters, we'll calculate new output values for the filter from the recurrence relation, which is derived from a basic RC circuit model for a low-pass filter:

   y\[i\] = (1 - α) * x\[i\] + α * y\[i-1\].

The calculations for an IIR high-pass filter is similar to the low-pass case, but the RC circuit model for a high-pass filter flips the position of the capacitor and resistor, so that the recurrence relation works out to:

   y\[i\] = α * (x\[i\] - x\[i-1\]) + α * y\[i-1\]

For both equations, x\[i\] and x\[i-1\] are the current and previous raw signal samples, and y\[1\] and y\[i-1\] are the current and previous filter output values. The factor, α, for both equations is given by:

   α = e^(-Δt/τ)

where Δt is the time between samples and τ is the decay constant (τ = RC). However, calls to the exp() function can be computationally expensive. So long as Δt is small compared to τ, we can quickly approximate α like so:

   α = τ / (τ + Δt)

The error difference between the exponential calculation and the approximation is less than 1% for τ/Δt > 7 and less than 0.1% for τ/Δt > 22.