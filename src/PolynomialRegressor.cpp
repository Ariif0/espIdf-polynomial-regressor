#include "PolynomialRegressor.h"
#include <algorithm>

/**
 * @brief Default constructor for PolynomialRegressor.
 *
 * Initializes the regressor with default values, setting the configuration to empty and the initialization flag to false.
 */
PolynomialRegressor::PolynomialRegressor() : _is_initialized(false)
{
    _config.terms = nullptr;
    _config.num_terms = 0;
    _config.min_input_value = 0;
    _config.max_input_value = 0;
}

/**
 * @brief Initializes the regressor with the provided configuration.
 *
 * Validates the input configuration and stores it internally if valid.
 *
 * @param config The configuration structure containing model parameters.
 * @return bool True if initialization is successful, false if the configuration is invalid (e.g., null terms, zero terms, or invalid input range).
 */
bool PolynomialRegressor::begin(const RegressorConfig &config)
{
    if (config.terms == nullptr || config.num_terms == 0 || config.min_input_value >= config.max_input_value)
    {
        return false;
    }

    _config = config;
    _is_initialized = true;
    return true;
}

/**
 * @brief Processes a raw sensor value to produce a calibrated output using the polynomial model.
 *
 * Clamps the input value to the valid range, normalizes it, and evaluates the polynomial using Horner's method.
 *
 * @param raw_sensor_value The raw sensor value to process.
 * @return float The computed polynomial result, or 0.0f if the regressor is not initialized.
 */
float PolynomialRegressor::process(int raw_sensor_value) const
{
    if (!_is_initialized)
    {
        return 0.0f;
    }

    int clamped_value = std::clamp(raw_sensor_value, _config.min_input_value, _config.max_input_value);

    float range = static_cast<float>(_config.max_input_value - _config.min_input_value);
    if (range == 0)
        return _config.terms[0];

    float normalized_input = (static_cast<float>(clamped_value - _config.min_input_value)) / range;

    float result = 0.0f;
    for (int i = _config.num_terms - 1; i >= 0; --i)
    {
        result = _config.terms[i] + (normalized_input * result);
    }

    return result;
}