#include <driver/i2s.h>
#include <math.h>

// I2S configuration
const i2s_port_t i2s_num = I2S_NUM_0; // I2S port number
const int i2s_sample_rate = 44100;    // Sample rate in Hz
const int i2s_bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT; // Bits per sample
const int i2s_channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT; // Stereo format

// Sine wave parameters
const float frequency = 100; // Frequency of the sine wave in Hz
const int amplitude = 10000;  // Amplitude of the sine wave

void setup() {
  // I2S configuration
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = i2s_sample_rate,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = 0, // Default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = true, // Auto clear TX descriptor on underflow
    .fixed_mclk = 0
  };

  // I2S pin configuration
  i2s_pin_config_t pin_config = {
    .bck_io_num = 26,   // BCK pin
    .ws_io_num = 25,    // WS pin
    .data_out_num = 22, // DATA out pin
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // Install and start I2S driver
  i2s_driver_install(i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin(i2s_num, &pin_config);

  // Set the sample rate
  i2s_set_clk(i2s_num, i2s_sample_rate, i2s_bits_per_sample, I2S_CHANNEL_STEREO);
}

void loop() {
  generateSineWave();
}

void generateSineWave() {
  const int sampleCount = i2s_sample_rate / frequency; // Number of samples per wave cycle
  int16_t samples[sampleCount * 2]; // Stereo samples array

  for (int i = 0; i < sampleCount; i++) {
    int16_t sample = (int16_t)(amplitude * sinf(2.0f * M_PI * i / sampleCount));
    samples[i * 2] = sample;     // Left channel
    samples[i * 2 + 1] = sample; // Right channel
  }

  // Write samples to I2S
  size_t bytes_written;
  i2s_write(i2s_num, samples, sizeof(samples), &bytes_written, portMAX_DELAY);
}
