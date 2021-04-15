
#include "tsl2561.h"

#define RATIO_SCALE 9

#define SCALE 10
#define SCALE_13 0x7517
#define SCALE_101 0x0FE7

#define TSL2561_PACKAGE_T_FN_CL

// T, FN and CL package values
#define TSL2561_LUX_K1T (0x0040)  ///< 0.125 * 2^RATIO_SCALE
#define TSL2561_LUX_B1T (0x01f2)  ///< 0.0304 * 2^LUX_SCALE
#define TSL2561_LUX_M1T (0x01be)  ///< 0.0272 * 2^LUX_SCALE
#define TSL2561_LUX_K2T (0x0080)  ///< 0.250 * 2^RATIO_SCALE
#define TSL2561_LUX_B2T (0x0214)  ///< 0.0325 * 2^LUX_SCALE
#define TSL2561_LUX_M2T (0x02d1)  ///< 0.0440 * 2^LUX_SCALE
#define TSL2561_LUX_K3T (0x00c0)  ///< 0.375 * 2^RATIO_SCALE
#define TSL2561_LUX_B3T (0x023f)  ///< 0.0351 * 2^LUX_SCALE
#define TSL2561_LUX_M3T (0x037b)  ///< 0.0544 * 2^LUX_SCALE
#define TSL2561_LUX_K4T (0x0100)  ///< 0.50 * 2^RATIO_SCALE
#define TSL2561_LUX_B4T (0x0270)  ///< 0.0381 * 2^LUX_SCALE
#define TSL2561_LUX_M4T (0x03fe)  ///< 0.0624 * 2^LUX_SCALE
#define TSL2561_LUX_K5T (0x0138)  ///< 0.61 * 2^RATIO_SCALE
#define TSL2561_LUX_B5T (0x016f)  ///< 0.0224 * 2^LUX_SCALE
#define TSL2561_LUX_M5T (0x01fc)  ///< 0.0310 * 2^LUX_SCALE
#define TSL2561_LUX_K6T (0x019a)  ///< 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6T (0x00d2)  ///< 0.0128 * 2^LUX_SCALE
#define TSL2561_LUX_M6T (0x00fb)  ///< 0.0153 * 2^LUX_SCALE
#define TSL2561_LUX_K7T (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7T (0x0018)  ///< 0.00146 * 2^LUX_SCALE
#define TSL2561_LUX_M7T (0x0012)  ///< 0.00112 * 2^LUX_SCALE
#define TSL2561_LUX_K8T (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8T (0x0000)  ///< 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8T (0x0000)  ///< 0.000 * 2^LUX_SCALE

// CS package values
#define TSL2561_LUX_K1C (0x0043)  ///< 0.130 * 2^RATIO_SCALE
#define TSL2561_LUX_B1C (0x0204)  ///< 0.0315 * 2^LUX_SCALE
#define TSL2561_LUX_M1C (0x01ad)  ///< 0.0262 * 2^LUX_SCALE
#define TSL2561_LUX_K2C (0x0085)  ///< 0.260 * 2^RATIO_SCALE
#define TSL2561_LUX_B2C (0x0228)  ///< 0.0337 * 2^LUX_SCALE
#define TSL2561_LUX_M2C (0x02c1)  ///< 0.0430 * 2^LUX_SCALE
#define TSL2561_LUX_K3C (0x00c8)  ///< 0.390 * 2^RATIO_SCALE
#define TSL2561_LUX_B3C (0x0253)  ///< 0.0363 * 2^LUX_SCALE
#define TSL2561_LUX_M3C (0x0363)  ///< 0.0529 * 2^LUX_SCALE
#define TSL2561_LUX_K4C (0x010a)  ///< 0.520 * 2^RATIO_SCALE
#define TSL2561_LUX_B4C (0x0282)  ///< 0.0392 * 2^LUX_SCALE
#define TSL2561_LUX_M4C (0x03df)  ///< 0.0605 * 2^LUX_SCALE
#define TSL2561_LUX_K5C (0x014d)  ///< 0.65 * 2^RATIO_SCALE
#define TSL2561_LUX_B5C (0x0177)  ///< 0.0229 * 2^LUX_SCALE
#define TSL2561_LUX_M5C (0x01dd)  ///< 0.0291 * 2^LUX_SCALE
#define TSL2561_LUX_K6C (0x019a)  ///< 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6C (0x0101)  ///< 0.0157 * 2^LUX_SCALE
#define TSL2561_LUX_M6C (0x0127)  ///< 0.0180 * 2^LUX_SCALE
#define TSL2561_LUX_K7C (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7C (0x0037)  ///< 0.00338 * 2^LUX_SCALE
#define TSL2561_LUX_M7C (0x002b)  ///< 0.00260 * 2^LUX_SCALE
#define TSL2561_LUX_K8C (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8C (0x0000)  ///< 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8C (0x0000)  ///< 0.000 * 2^LUX_SCALE

#define COMMAND 0b11000000

enum {
	REG_CONTROL = 0x0,
	REG_TIMING = 0x1,
	REG_THRESHLOWLOW = 0x2,
	REG_THRESHLOWHIGH = 0x3,
	REG_THRESHHIGHLOW = 0x4,
	REG_THRESHHIGHHIGH = 0x5,
	REG_INTERRUPT = 0x6,
	REG_CRC = 0x8,
	REG_ID = 0xA,
	REG_DATA0LOW = 0xC,
	REG_DATA0HIGH = 0xD,
	REG_DATA1LOW = 0xE,
	REG_DATA1HIGH = 0xF
} registers;

tsl2561_status _set_gain(tsl2561 *sensor) {
	uint8_t cmd[2] = {COMMAND | REG_TIMING, sensor->gain | sensor->inttime};

	return HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
								   (uint8_t *)&cmd, 2, 5);
}

tsl2561_status tsl2561_init(tsl2561 *sensor) { return _set_gain(sensor); }

tsl2561_status tsl2561_enable(tsl2561 *sensor) {
	uint8_t cmd[2] = {COMMAND | REG_CONTROL, 0x3};
	return HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
								   (uint8_t *)&cmd, 2, 5);
}

tsl2561_status tsl2561_disable(tsl2561 *sensor) {
	uint8_t cmd[2] = {COMMAND | REG_CONTROL, 0x0};
	return HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
								   (uint8_t *)&cmd, 2, 5);
}

tsl2561_status tsl2561_set_interrupt(tsl2561 *sensor, uint16_t min,
									 uint16_t max, uint8_t period) {
	uint8_t cmd[3] = {COMMAND | REG_THRESHLOWLOW, (uint8_t)min,
					  (uint8_t)(min >> 8)};
	tsl2561_status status = HAL_I2C_Master_Transmit(
		sensor->interface, sensor->address, (uint8_t *)&cmd, 3, 5);
	if (status != HAL_OK) {
		return status;
	}

	cmd[0] = COMMAND | REG_THRESHHIGHLOW;
	cmd[1] = (uint8_t)max;
	cmd[2] = (uint8_t)(max >> 8);
	status = HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
									 (uint8_t *)&cmd, 3, 5);
	if (status != HAL_OK) {
		return status;
	}

	cmd[0] = COMMAND | REG_INTERRUPT;
	cmd[1] = 0b0001 | period;
	return HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
								   (uint8_t *)&cmd, 2, 5);
}

tsl2561_status tsl2561_disable_interrupt(tsl2561 *sensor) {
	uint8_t cmd[2] = {COMMAND | REG_INTERRUPT, 0b0};
	return HAL_I2C_Master_Transmit(sensor->interface, sensor->address,
								   (uint8_t *)&cmd, 2, 5);
}

tsl2561_status tsl2561_read_ch0(tsl2561 *sensor, uint16_t *value) {
	uint8_t cmd = COMMAND | REG_DATA0LOW;

	HAL_I2C_Master_Transmit(sensor->interface, sensor->address, (uint8_t *)&cmd,
							1, 5);

	if (HAL_I2C_Master_Receive(sensor->interface, sensor->address,
							   (uint8_t *)value, 2, 5) != HAL_OK) {
		return TSL2561_TIMEOUT;
	}

	return TSL2561_OK;
}

tsl2561_status tsl2561_read_ch1(tsl2561 *sensor, uint16_t *value) {
	uint8_t cmd = COMMAND | REG_DATA1LOW;
	HAL_I2C_Master_Transmit(sensor->interface, sensor->address, (uint8_t *)&cmd,
							1, 5);

	if (HAL_I2C_Master_Receive(sensor->interface, sensor->address,
							   (uint8_t *)value, 2, 5) != HAL_OK) {
		return TSL2561_TIMEOUT;
	}

	return TSL2561_OK;
}

tsl2561_status tsl2561_get_data(tsl2561 *sensor, uint16_t *broadband,
								uint16_t *ir) {
	tsl2561_status status = tsl2561_enable(sensor);
	if (status != TSL2561_OK) {
		return status;
	}

	if (sensor->inttime == TSL2561_INTTIME_13MS) {
		HAL_Delay(20);
	} else if (sensor->inttime == TSL2561_INTTIME_101MS) {
		HAL_Delay(120);
	} else {
		HAL_Delay(420);	 // nice
	}

	status = tsl2561_read_ch0(sensor, broadband);
	if (status != TSL2561_OK) {
		return status;
	}
	status = tsl2561_read_ch1(sensor, ir);

	tsl2561_disable(sensor);
	return status;
}

tsl2561_status tsl2561_get_luminosity(tsl2561 *sensor, uint16_t *broadband,
									  uint16_t *ir) {
	if (!sensor->autogain) {
		return tsl2561_get_data(sensor, broadband, ir);
	}

	bool valid = false;
	bool ag_check = false;
	do {
		uint16_t _b, _ir;
		uint16_t _hi, _lo;

		/* Get the hi/low threshold for the current integration time */
		switch (sensor->inttime) {
			case TSL2561_INTTIME_13MS:
				_hi = TSL2561_AGC_THI_13MS;
				_lo = TSL2561_AGC_TLO_13MS;
				break;
			case TSL2561_INTTIME_101MS:
				_hi = TSL2561_AGC_THI_101MS;
				_lo = TSL2561_AGC_TLO_101MS;
				break;
			default:
				_hi = TSL2561_AGC_THI_402MS;
				_lo = TSL2561_AGC_TLO_402MS;
				break;
		}

		tsl2561_status status = tsl2561_get_data(sensor, &_b, &_ir);
		if (status != TSL2561_OK) {
			return status;
		}

		/* Run an auto-gain check if we haven't already done so ... */
		if (!ag_check) {
			if ((_b < _lo) && (sensor->gain == TSL2561_GAIN_1X)) {
				/* Increase the gain and try again */
				sensor->gain = TSL2561_GAIN_16X;
				_set_gain(sensor);
				/* Drop the previous conversion results */
				status = tsl2561_get_data(sensor, &_b, &_ir);
				if (status != TSL2561_OK) {
					return status;
				}
				/* Set a flag to indicate we've adjusted the gain */
				ag_check = true;
			} else if ((_b > _hi) && (sensor->gain == TSL2561_GAIN_16X)) {
				/* Drop gain to 1x and try again */
				sensor->gain = TSL2561_GAIN_1X;
				_set_gain(sensor);
				/* Drop the previous conversion results */
				status = tsl2561_get_data(sensor, &_b, &_ir);
				if (status != TSL2561_OK) {
					return status;
				}
				/* Set a flag to indicate we've adjusted the gain */
				ag_check = true;
			} else {
				/* Nothing to look at here, keep moving ....
				   Reading is either valid, or we're already at the chips limits
				 */
				*broadband = _b;
				*ir = _ir;
				valid = true;
			}
		} else {
			/* If we've already adjusted the gain once, just return the new
			   results. This avoids endless loops where a value is at one
			   extreme pre-gain, and the the other extreme post-gain */
			*broadband = _b;
			*ir = _ir;
			valid = true;
		}
	} while (!valid);

	return TSL2561_OK;
}

tsl2561_status tsl2561_get_lux(tsl2561 *sensor, uint16_t *lux) {
	uint16_t broadband, ir;
	tsl2561_status status = tsl2561_get_luminosity(sensor, &broadband, &ir);
	if (status != TSL2561_OK) {
		return status;
	}

	uint16_t clipThreshold;
	switch (sensor->inttime) {
		case TSL2561_INTTIME_13MS:
			clipThreshold = TSL2561_CLIPPING_13MS;
			break;
		case TSL2561_INTTIME_101MS:
			clipThreshold = TSL2561_CLIPPING_101MS;
			break;
		default:
			clipThreshold = TSL2561_CLIPPING_402MS;
			break;
	}

	if (broadband > clipThreshold || ir > clipThreshold) {
		return TSL2561_SENSOR_CLIPPING;
	}

	uint32_t scale;
	// Set scaling for integration times != 402ms
	switch (sensor->inttime) {
		case TSL2561_INTTIME_13MS:
			scale = SCALE_13;
			break;
		case TSL2561_INTTIME_101MS:
			scale = SCALE_101;
			break;
		default:
			scale = 1 << SCALE;
	}

	if (sensor->gain == TSL2561_GAIN_1X) {
		scale = scale << 4;	 // 1 to 16x gain
	}

	uint32_t ch0;
	uint32_t ch1;
	// Scale the channels
	ch0 = (broadband * scale) >> SCALE;
	ch1 = (ir * scale) >> SCALE;

	// Find ratio between all light and ir
	uint32_t ratio = 0;
	if (ch0 != 0) {
		ratio = (ch1 << (RATIO_SCALE + 1)) / ch0;
	}

	// Round ratio
	ratio = (ratio + 1) >> 1;

	uint16_t b, m;

#ifdef TSL2561_PACKAGE_CS
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C)) {
		b = TSL2561_LUX_B1C;
		m = TSL2561_LUX_M1C;
	} else if (ratio <= TSL2561_LUX_K2C) {
		b = TSL2561_LUX_B2C;
		m = TSL2561_LUX_M2C;
	} else if (ratio <= TSL2561_LUX_K3C) {
		b = TSL2561_LUX_B3C;
		m = TSL2561_LUX_M3C;
	} else if (ratio <= TSL2561_LUX_K4C) {
		b = TSL2561_LUX_B4C;
		m = TSL2561_LUX_M4C;
	} else if (ratio <= TSL2561_LUX_K5C) {
		b = TSL2561_LUX_B5C;
		m = TSL2561_LUX_M5C;
	} else if (ratio <= TSL2561_LUX_K6C) {
		b = TSL2561_LUX_B6C;
		m = TSL2561_LUX_M6C;
	} else if (ratio <= TSL2561_LUX_K7C) {
		b = TSL2561_LUX_B7C;
		m = TSL2561_LUX_M7C;
	} else if (ratio > TSL2561_LUX_K8C) {
		b = TSL2561_LUX_B8C;
		m = TSL2561_LUX_M8C;
	}
#else
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T)) {
		b = TSL2561_LUX_B1T;
		m = TSL2561_LUX_M1T;
	} else if (ratio <= TSL2561_LUX_K2T) {
		b = TSL2561_LUX_B2T;
		m = TSL2561_LUX_M2T;
	} else if (ratio <= TSL2561_LUX_K3T) {
		b = TSL2561_LUX_B3T;
		m = TSL2561_LUX_M3T;
	} else if (ratio <= TSL2561_LUX_K4T) {
		b = TSL2561_LUX_B4T;
		m = TSL2561_LUX_M4T;
	} else if (ratio <= TSL2561_LUX_K5T) {
		b = TSL2561_LUX_B5T;
		m = TSL2561_LUX_M5T;
	} else if (ratio <= TSL2561_LUX_K6T) {
		b = TSL2561_LUX_B6T;
		m = TSL2561_LUX_M6T;
	} else if (ratio <= TSL2561_LUX_K7T) {
		b = TSL2561_LUX_B7T;
		m = TSL2561_LUX_M7T;
	} else if (ratio > TSL2561_LUX_K8T) {
		b = TSL2561_LUX_B8T;
		m = TSL2561_LUX_M8T;
	}
#endif

	ch0 = ch0 * b;
	ch1 = ch1 * m;

	uint32_t temp = 0;
	if (ch0 > ch1) {
		temp = ch0 - ch1;
	}

	temp += (1 << (SCALE - 1));

	*lux = temp >> SCALE;

	return TSL2561_OK;
}