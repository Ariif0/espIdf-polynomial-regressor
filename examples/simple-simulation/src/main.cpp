#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "esp_system.h"
#include "esp_random.h"
#include "PolynomialRegressor.h"

static const char *TAG = "LIB_TEST";

// Global instance of the PolynomialRegressor library
PolynomialRegressor waterLevelSensor;

/**
 * @brief Task to run the simulation of sensor data processing.
 * 
 * Generates random ADC values, processes them using the PolynomialRegressor, and logs the results.
 * 
 * @param pvParameters Task parameters (not used).
 */
void simulation_task(void *pvParameters) {
    ESP_LOGI(TAG, "Simulation task running...");

    for (;;) {
        uint32_t raw_adc = (esp_random() % 3600) + 200; // Random ADC value between 200 and 3800
        float water_height = waterLevelSensor.process(raw_adc);

        ESP_LOGI(TAG, "Simulated ADC: %4lu -> Calculated Height: %5.2f cm", raw_adc, water_height);

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Main application entry point.
 * 
 * Configures and initializes the PolynomialRegressor library, then starts the simulation task if initialization is successful.
 */
extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Configuring PolynomialRegressor library for water level sensor simulation...");

    // Define polynomial coefficients
    static const float my_coefficients[] = {
        1.0f,  // c₀
        29.0f, // c₁
        20.0f  // c₂
    };
    
    // Create and populate configuration structure
    RegressorConfig my_config;
    my_config.terms = my_coefficients;
    my_config.num_terms = sizeof(my_coefficients) / sizeof(my_coefficients[0]);
    my_config.min_input_value = 200;
    my_config.max_input_value = 3800;
    
    // Initialize the library with the configuration
    if (waterLevelSensor.begin(my_config)) {
        ESP_LOGI(TAG, "Library initialization successful. Starting task.");
        xTaskCreate(simulation_task, "simulation_task", 4096, NULL, 5, NULL);
    } else {
        ESP_LOGE(TAG, "Failed to initialize library!");
    }
}