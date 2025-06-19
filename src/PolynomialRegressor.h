#ifndef POLYNOMIAL_REGRESSOR_H
#define POLYNOMIAL_REGRESSOR_H

#include <cstddef>
#include <cstdint>

/**
 * @brief Configuration structure for the polynomial regression model.
 *
 * Users of the library must create an instance of this structure and populate it with the necessary parameters.
 */
struct RegressorConfig
{
    const float *terms;  /**< Pointer to an array of polynomial coefficients (ordered from lowest to highest degree, c₀, c₁, c₂, ...). */
    size_t num_terms;    /**< Total number of coefficients in the array. */
    int min_input_value; /**< Minimum valid raw ADC input value. */
    int max_input_value; /**< Maximum valid raw ADC input value. */
};

/**
 * @brief A class for processing data using a polynomial regression model.
 */
class PolynomialRegressor
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the regressor with default values.
     */
    PolynomialRegressor();

    /**
     * @brief Initializes the regressor with the provided configuration.
     *
     * @param config The configuration structure containing all model parameters.
     * @return bool True if initialization is successful, false otherwise (e.g., invalid configuration).
     */
    bool begin(const RegressorConfig &config);

    /**
     * @brief Processes a raw sensor value and returns the calibrated output.
     *
     * @param raw_sensor_value The raw value from the sensor.
     * @return float The computed polynomial result.
     */
    [[nodiscard]] float process(int raw_sensor_value) const;

private:
    RegressorConfig _config; /**< Internal copy of the configuration. */
    bool _is_initialized;    /**< Flag indicating whether the regressor has been initialized. */
};

#endif // POLYNOMIAL_REGRESSOR_H