# Vulintus_Digital_Filter

Arduino-compatible digital filter library used in Vulintus devices' firmware.

---

## Simple Infinite Response Filters

The simple low- and high-pass filters are designed as [discretized RC filters](https://en.wikipedia.org/wiki/Low-pass_filter#Discrete-time_realization).
𝜏 = RC

y_i = x_i * ( dt / ( RC + dt ) ) + y_i-1 * ( RC / ( RC + dt ) )
y_i = α * x_i + ( 1 - α ) * y_i-1
α = dt / ( RC + dt ) = dt / ( 𝜏 + dt )

## Two-Pole Filters

The driven, damped [harmonic oscillator](http://en.wikipedia.org/wiki/Harmonic_oscillator) equation is:

   a + 2*ζ*ω0*v + ω0²*x = F(t)/m

in which

    * a = 1 constant in the equation
    * ζ = the damping factor
    * ω0 = the natural frequency of the oscillator
    * v = the velocity of the oscillator
    * x = the displacement of the oscillator
    * F(t) = the external force applied to the oscillator as a function of time
    * m = the mass of the oscillator

The quality factor, Q, is related to the damping factor by

   Q = ½ζ

It is useful to normalize the force to the spring constant, k, so a force of F will result in the oscillator resting at a position x = F. This allows the oscillator to be used as a lowpass filter, where the position X functions as the output voltage V.

Setting a = v = 0, and solving for m, gives:

   m = 1/w0

Such that the final equation is:

   a + 2*ζ*ω0*v + ω0²*x = ω0²*F(t)

For determining the energy, E, you must know the effective spring constant, which is
found from the equation (for undampened, where w0 = w):

   w0² = k/m
   w0 = k

The energy is then calculated:

    E = 0.5*k*x² + 0.5*m*v²
      = 0.5*w0*x² + 0.5*v²/w0

Filter types (such as Bessel or Butterworth) are defined by specific quality factors. The quality factor also defines a relationship between f0 (the undamped resonance frequency) and the -3 dB frequency of the filter.

For a Butterworth filter, these values are 
(see figures 8.26 and 8.32 Bessel)
(See Analog Devices note AN-649)
http://www.analog.com/static/imported-files/application_notes/447952852AN-649_0.pdf
http://www.analog.com/library/analogDialogue/archives/43-09/EDCh%208%20filter.pdf


Butterworth
    F_0=1
	F_(-3dB)=1
	Q=1/√2

Bessel
    F_0=1.2754
    F_(-3dB)=1
    Q=1/√3

(note – ramp time for a Bessel filter is about 1/(2F_0 ) )

