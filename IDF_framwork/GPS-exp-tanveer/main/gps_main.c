#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const int RX_BUF_SIZE = 1024;

// Define GPS UART
#define GPS_UART_NUM UART_NUM_0
#define TX_PIN 11
#define RX_PIN 10
#define portTICK_RATE_MS 1000

// UART initialization for GPS
void init_gps_uart() {
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_RTC,
    };
    uart_param_config(GPS_UART_NUM, &uart_config);
    uart_set_pin(GPS_UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(GPS_UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

// Helper function to parse latitude and longitude from NMEA sentence
void parse_gpgga_sentence(char* nmea_sentence) {
    char *token;
    int field_number = 0;
    char latitude[10] = {0};
    char longitude[11] = {0};
    char lat_direction = '\0';  // Initialize to null character
    char lon_direction = '\0';  // Initialize to null character

    token = strtok(nmea_sentence, ",");
    while (token != NULL) {
        field_number++;
        
        // Latitude is field 3 and 4 in GPGGA
        if (field_number == 3) {
            strcpy(latitude, token);
        } else if (field_number == 4) {
            lat_direction = token[0];
        }
        
        // Longitude is field 5 and 6 in GPGGA
        if (field_number == 5) {
            strcpy(longitude, token);
        } else if (field_number == 6) {
            lon_direction = token[0];
        }
        
        token = strtok(NULL, ",");
    }
    
    // Print the parsed latitude and longitude
    if (strlen(latitude) > 0 && strlen(longitude) > 0) {
        printf("Latitude: %s %c, Longitude: %s %c\n", latitude, lat_direction, longitude, lon_direction);
    } else {
        printf("Failed to parse GPS data.\n");
    }
}

void gps_task(void *arg) {
    uint8_t data[RX_BUF_SIZE];
    char nmea_sentence[128];
    int sentence_index = 0;

    while (1) {
        int len = uart_read_bytes(GPS_UART_NUM, data, RX_BUF_SIZE, 20 / portTICK_RATE_MS);
        if (len > 0) {
            for (int i = 0; i < len; i++) {
                char c = (char)data[i];
                
                // Look for end of NMEA sentence (new line)
                if (c == '\n') {
                    nmea_sentence[sentence_index] = '\0';
                    
                    // Check if it's a GPGGA sentence (global positioning system fix data)
                    if (strstr(nmea_sentence, "$GPGGA") != NULL) {
                        // printf(nmea_sentence);
                        parse_gpgga_sentence(nmea_sentence);
                    }
                    
                    // Reset for the next sentence
                    sentence_index = 0;
                } else if (c != '\r') {
                    // Accumulate characters for the sentence
                    nmea_sentence[sentence_index++] = c;
                }
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    // Initialize GPS UART
    init_gps_uart();

    // Create the GPS task
    xTaskCreate(gps_task, "gps_task", 4096, NULL, 10, NULL);
}