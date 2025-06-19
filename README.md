# ESPIDF Polynomial Regressor Library


<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg?style=for-the-badge">
  <img alt="Framework" src="https://img.shields.io/badge/Framework-ESP--IDF-red.svg?style=for-the-badge">
  <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge">
</p>

-----

### 📖 Description

A simple and efficient C++ library for the ESP32 (using the ESP-IDF framework) to process sensor data using a configurable polynomial regression model. Ideal for handling sensors with a non-linear response.

## Installation

The easiest way to add this library to your PlatformIO project is to add the following line to your `platformio.ini` file:

```ini
lib_deps =
    https://github.com/Ariif0/espIdf-polynomial-regressor
```

## Quick Start

Please see the `examples` folder for a complete, runnable project that shows how to initialize and use the library within your `app_main`.

## API Reference

### `struct RegressorConfig`

A struct to hold the model's configuration.

  - `const float* terms`: Pointer to your array of coefficients (ordered from the lowest degree to the highest, i.e., c₀, c₁, c₂, ...).
  - `size_t num_terms`: The total number of terms in the coefficient array.
  - `int min_input_value`: The minimum valid raw input value.
  - `int max_input_value`: The maximum valid raw input value.

### `class PolynomialRegressor`

  - `bool begin(const RegressorConfig& config)`: Initializes the regressor object with your configuration.
  - `float process(int raw_sensor_value) const`: Processes a raw input value and returns the calculated result.

### 👤 Author

Developed and maintained by **Muhamad Arif Hidayat**.

### 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.