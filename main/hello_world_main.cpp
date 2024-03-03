#include "driver/i2s.h"
#include <math.h>
#include "config.h"
#include "Phasor.h"

static const uint16_t Volume = 1023;
static uint32_t Value32Bit;
size_t BytesWritten;
//TODO: Atualizar driver i2s
// Array with the sine wave
static int16_t sine_wave[1024];

Phasor phs;

// Phasor variables
// static double phasor = 0.0;
// static double frequency = 220.0; // Default frequency
float sweep = 0.0;

// Function that generates the sine wave
void generate_sine_wave()
{
    for (int i = 0; i < 1024; i++)
    {
        sine_wave[i] = (int16_t)(Volume * sin(2.0 * M_PI * i / 1024));
    }
}

void audio_callback()
{

    int16_t OutputValue = sine_wave[(int)(phs.Process() * 1024)];
    // int OutputValue = 10;

    Value32Bit = (OutputValue << 16) | (OutputValue & 0xffff);

    // Output the combined 32-bit value
    i2s_write(i2s_num, &Value32Bit, 4, &BytesWritten, portMAX_DELAY);
}

extern "C" void app_main(void)
{
    // Generate the sine wave before entering the loop
    generate_sine_wave();
    i2s_driver_install(i2s_num, &i2s_config, 0, NULL);
    i2s_set_pin(i2s_num, &pin_config);
    phs.Init(44100, 440);

    while (1)
    {
        // Set the frequency (you can change this dynamically as needed)
        phs.SetFreq(sweep);
        if (sweep < 1000)
        {
            sweep += 0.01;
        }
        else
        {
            sweep = 0;
        }

        audio_callback();
    }
}
