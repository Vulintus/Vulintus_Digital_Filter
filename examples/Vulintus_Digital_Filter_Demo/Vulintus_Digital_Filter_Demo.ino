/*  

    Vulintus_Digital_Filter_Demo.ino

    copyright 2025, Vulintus, Inc.

    Example demonstrating the use of the Vulintus_Digital_Filter class.

    UPDATE LOG:
      2025-02-19 - Drew Sloan - Example first created.

*/


// Included libraries. // 
#include <Vulintus_Digital_Filter.h>        // Vulintus digital filter library.

// Serial communication constants. // 
#define SERIAL_BAUD_RATE  115200            // Serial baud rate.

// Digital filter. //
const float CUTOFF_FREQ = 1.0;                          // Cutoff frequency of the filter, in Hz
// Vulintus_IIR_LowPass_Filter test_filter(CUTOFF_FREQ);   // Creae a low-pass filter.
// Vulintus_RC_LowPass_Filter test_filter(CUTOFF_FREQ);    // Create an RC low-pass filter.
Vulintus_RC_HighPass_Filter test_filter(CUTOFF_FREQ);   // Create an RC high-pass filter.

// Sampling and print timing. //
const float SAMPLE_FREQ = 1000;         // Sampling frequency, in Hz.
uint32_t sample_period;                 // Sampling period, in microseconds.
uint32_t next_sample;                   // Sampling timer.
const float PRINT_FREQ = 15;            // Print frequency, in Hz.
uint32_t print_period;                  // Print period, in microseconds.
uint32_t next_print;                    // Print timer.
const float TEST_FREQUENCY = 1;         // Frequency of the square-wave test signal, in Hz.
const float TEST_AMPLITUDE = 1.0;       // Amplitude of the square-wave test signal.
uint32_t test_phase_period;             // Test phase period, in microseconds.
bool test_phase = true;                 // Current phase of the square-wave test signal.
uint32_t next_test_phase;               // Phase-switching timer for the test signal.


// INITIALIZATION ************************************************************// 
void setup() {

    // Initialize serial data transmission.
    Serial.begin(SERIAL_BAUD_RATE);           

    // Initialize the digital filter.
    test_filter.begin();                                // Initialize the filter.

    // Test signal timing.
    float temp_phase_period = 1e3 / TEST_FREQUENCY;     // Calculate the period of the test signal, in milliseconds.
    test_phase_period = (uint32_t)temp_phase_period;    // Convert the period to an integer.
    next_test_phase = millis() + test_phase_period;     // Set the first phase-switching time.

    // Calculate the print period.
    float temp_print_period = 1e3 / PRINT_FREQ;         // Calculate the print period, in milliseconds.
    print_period = (uint32_t) temp_print_period;        // Convert the print period to an integer.
    next_print = millis() + print_period;               // Set the first print time.

    // Calculate the sampling period.
    float temp_sample_period = 1e6 / SAMPLE_FREQ;       // Calculate the sampling period, in microseconds.
    sample_period = (uint32_t)temp_sample_period;       // Convert the sampling period to an integer.
    next_sample = micros() + sample_period;             // Set the first sampling time.

    // while (1) {
    //   Serial.print("test_phase_period = ");
    //   Serial.println(test_phase_period);
    //   Serial.print("print_period = ");
    //   Serial.println(print_period);
    //   Serial.print("sample_period = ");
    //   Serial.println(sample_period);
    //   Serial.println();
    //   delay(1000);
    // }

}


// MAIN LOOP *****************************************************************// 
void loop() {

  // On each scheduled sample, update the filter with the test signal.
  if (micros() > next_sample) {                 // If it's time to sample the test signal...

    if (test_phase) {                           // If the test signal is in the positive phase.
      test_filter.input(TEST_AMPLITUDE);        // Update the filter with the positive amplitude.
    } else {                                    // If the test signal is in the negative phase.
      test_filter.input(-TEST_AMPLITUDE);       // Update the filter with the negative amplitude.
    }
    next_sample += sample_period;               // Set the next sample time.

    if (millis() > next_test_phase) {           // If it's time to switch the test signal phase...
      test_phase = !test_phase;                 // Switch the test signal phase.
      next_test_phase += test_phase_period;     // Set the next phase-switching time.
    }

    if (millis() > next_print) {                // If it's time to print the filter output...
      Serial.print("RAW:");                     // Raw signal label.         
      Serial.print(test_filter.X,3);            // Print the most recent filter input.
      Serial.print(",FILTERED:");               // Filtered signal label.
      Serial.println(test_filter.output,3);     // Print the filter cutoff frequency.
      next_print += print_period;               // Set the next print time.
    }

  }    
}
  

