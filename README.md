# Vulintus_Digital_Filter

A collection of Arduino-compatible digital filter classes used in Vulintus devices' firmware. This library started as a stripped-down fork of [Jon Driscoll's "Filters"](https://github.com/JonHub/Filters) library, but now differs somewhat in the calculations based on our own interpretations. Basic [examples](examples/) for Arduino are included. This library is, as always, a work-in-progress.

---

## Simple Infinite Impulse Response (IIR) Filters

The most basic low- or high-pass filters, "[Vulintus_IIR_Filter](src/IIR_Filters/Vulintus_IIR_Filter.h)," are designed as single-pole discretized RC filters. The implementation of these filters is adapted largely from the Wikipedia pages for [low-pass](https://en.wikipedia.org/wiki/Low-pass_filter#Difference_equation_through_discrete_time_sampling) and [high-pass](https://en.wikipedia.org/wiki/High-pass_filter#Discrete-time_realization) filters.

For IIR filters, we'll calculate new output values for the filter from the recurrence relation, which is derived from basic RC circuit models for low-pass and high-pass filters:

   y\[i\] = (1 - α) * x\[i\] + α * y\[i-1\]           (low-pass)

   y\[i\] = α * (x\[i\] - x\[i-1\]) + α * y\[i-1\]    (high-pass)

These equations differ because the RC circuit models for low-pass and high-pass filters differ by flipping the position of the capacitor and resistor. For both equations, x\[i\] and x\[i-1\] are the current and previous raw signal samples, and y\[1\] and y\[i-1\] are the current and previous filter output values. The factor, α, for both equations, is given by:

   α = e^(-Δt/τ)

where Δt is the time between samples and τ is the decay constant (τ = RC). However, calls to the exp() function can be computationally expensive. So long as Δt is small compared to τ, we can quickly approximate α like so:

   α = τ / (τ + Δt)

The error difference between the exponential calculation and the approximation is less than 1% for τ/Δt > 7 and less than 0.1% for τ/Δt > 22.
