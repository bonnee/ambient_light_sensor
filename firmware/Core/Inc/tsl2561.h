
#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <stm32f4xx.h>

#define TSL2561_CLIPPING_13MS \
	(4900)	///< # Counts that trigger a change in gain/integration
#define TSL2561_CLIPPING_101MS \
	(37000)	 ///< # Counts that trigger a change in gain/integration
#define TSL2561_CLIPPING_402MS \
	(65000)	 ///< # Counts that trigger a change in gain/integration

// Auto-gain thresholds
#define TSL2561_AGC_THI_13MS (4850)	   ///< Max value at Ti 13ms = 5047
#define TSL2561_AGC_TLO_13MS (100)	   ///< Min value at Ti 13ms = 100
#define TSL2561_AGC_THI_101MS (36000)  ///< Max value at Ti 101ms = 37177
#define TSL2561_AGC_TLO_101MS (200)	   ///< Min value at Ti 101ms = 200
#define TSL2561_AGC_THI_402MS (63000)  ///< Max value at Ti 402ms = 65535
#define TSL2561_AGC_TLO_402MS (500)	   ///< Min value at Ti 402ms = 500

typedef enum {
	TSL2561_OK = HAL_OK,
	TSL2561_TIMEOUT = HAL_TIMEOUT,
	TSL2561_SENSOR_CLIPPING
} tsl2561_status;

typedef enum {
	TSL2561_ADDR_FLOAT = 0b01110010,
	TSL2561_ADDR_LOW = 0b01010010,
	TSL2561_ADDR_HIGH = 0b10010010,
} tsl2561_addr;

typedef enum {
	TSL2561_VERSION_2560 = 0b0000,
	TSL2561_VERSION_2561 = 0b0001
} tsl2561_version;

typedef enum { TSL2561_GAIN_1X = 0b0, TSL2561_GAIN_16X = 0b10000 } tsl2561_gain;

typedef enum {
	TSL2561_INTTIME_13MS = 0b0,
	TSL2561_INTTIME_101MS = 0b01,
	TSL2561_INTTIME_402MS = 0b10
} tsl2561_inttime;

typedef struct tsl2561_ {
	uint8_t address;
	I2C_HandleTypeDef *interface;
	bool autogain;
	tsl2561_gain gain;
	tsl2561_inttime inttime;

	GPIO_TypeDef *int_port;
	uint16_t int_pin;
} tsl2561;

tsl2561_status tsl2561_init(tsl2561 *sensor);

tsl2561_status tsl2561_enable(tsl2561 *sensor);
tsl2561_status tsl2561_disable(tsl2561 *sensor);

tsl2561_status tsl2561_set_interrupt(tsl2561 *sensor, uint16_t min,
									 uint16_t max, uint8_t period);
tsl2561_status tsl2561_disable_interrupt(tsl2561 *sensor);

tsl2561_status tsl2561_read_ch0(tsl2561 *sensor, uint16_t *value);
tsl2561_status tsl2561_read_ch1(tsl2561 *sensor, uint16_t *value);
tsl2561_status tsl2561_get_luminosity(tsl2561 *sensor, uint16_t *broadband,
									  uint16_t *ir);
tsl2561_status tsl2561_get_data(tsl2561 *sensor, uint16_t *broadband,
								uint16_t *ir);
tsl2561_status tsl2561_get_lux(tsl2561 *sensor, uint16_t *lux);