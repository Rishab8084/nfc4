/* SPI Slave example, sender (uses SPI master driver)

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#include "nfc4.h"

nfc4_t nfc4;

char *TAG = "LOGGER";

void application_init(void)
{
    /**< Click config object. */
    esp_err_t error_flag;

    nfc4_cfg_t nfc4_cfg;

    // Click initialization.
    nfc4_cfg_setup(&nfc4_cfg);
    ESP_LOGW(TAG, "nfc4_cfg_setup() %s:%d", __FILE__, __LINE__);

    esp_err_t init_flag = nfc4_init(&nfc4, &nfc4_cfg);
    ESP_LOGW(TAG, "nfc4_init() %s:%d STATUS: %d", __FILE__, __LINE__, init_flag);


    error_flag = nfc4_default_cfg(&nfc4);
    ESP_LOGW(TAG, "nfc4_default_cfg() %s:%d STATUS: %d", __FILE__, __LINE__, init_flag);
}


void application_task ( void )
{
    uint8_t tag_uid[ 10 ] = { 0 };
    uint8_t uid_len = 0;

    esp_err_t ret = nfc4_get_mifare_tag_uid( &nfc4, tag_uid, &uid_len);

    ESP_LOGW(TAG, "=========================================================");
    ESP_LOGW(TAG, "=============================== %d ======================", ret);
    ESP_LOGW(TAG, "=========================================================");

    if( NFC4_OK == ret)
    {
        ESP_LOGE( TAG, "======================= Tag UID: =============================" );
        for ( uint8_t cnt = 0; cnt < uid_len; cnt++ )
        {
            printf("%.2X", ( uint16_t ) tag_uid[ cnt ] );
        }
        printf("\r\n" );
        vTaskDelay( pdMS_TO_TICKS(500));
    }
}

// Main application
void app_main(void)
{
    
    application_init();
    ESP_LOGE(TAG, "================== APPLICATION INIT FINISHED ================");
    while (1)
    {
        ESP_LOGE(TAG, "=============================================================================================");
        ESP_LOGE(TAG, "====================================APPLICATION TASK START===================================");
        ESP_LOGE(TAG, "=============================================================================================");
        application_task();
        ESP_LOGE(TAG, "=============================================================================================");
        ESP_LOGE(TAG, "====================================APPLICATION TASK END=====================================");
        ESP_LOGE(TAG, "=============================================================================================");
    }
}
