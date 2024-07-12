//=============================================================================
//       Greg Friedholm Copyright (c) 2017
//-----------------------------------------------------------------------------
//       Tamper.c
//-----------------------------------------------------------------------------
//  This file contains functions that drive the MMA8653FC Accelerometer
//  device used for tamper detection.
//=============================================================================

#include "Types.h"
#include "Accelerometer.h"
#include "Beeper.h"
#include "Gpio.h"
#include "History.h"
#include "Timers.h"
#include "Tamper.h"
#include <zephyr.h>
#include <logging/log.h>
#include <stdlib.h>

LOG_MODULE_REGISTER(tamper);
#define CONTROL_LINE_TAMPER_PIN DT_GPIO_PIN(DT_NODELABEL(tamper), gpios)
#define MOVING_AVERAGE_SIZE 15

bool CalculateSigmaDelta(void);

static uint16_t stabilityCounter = 0;
static uint16_t tamperActiveCounter = 0;
static uint16_t maxStabilityCounter = DEF_TAMPER_INACTIVE_COUNTER;
static uint16_t maxTamperActiveCounter = DEF_TAMPER_ACTIVE_COUNTER;
static uint16_t tamperSettings;
static bool lastTamperState = TAMPER_INACTIVE;
static bool fFirstTamperReport = true;

// These two numbers must add up to 1
// Adjust for smoother/rougher hysteresis
float Sigma_Immediate  =  (float)ACCEL_TAMPER_IMMEDIATE_DEFAULT/100;
float Sigma_Historical =  (float)ACCEL_TAMPER_HISTORICAL_DEFAULT/100;

// Adjust for tamper max delta threshold
uint16_t Delta_Threshold = ACCEL_TAMPER_THRESHOLD_DEFAULT;

int16_t XAxis = 0;
int16_t YAxis = 0;
int16_t ZAxis = 0;

int16_t XAxis_Immediate = 0;
int16_t YAxis_Immediate = 0;
int16_t ZAxis_Immediate = 0;

int16_t XAxis_Historical = 0;
int16_t YAxis_Historical = 0;
int16_t ZAxis_Historical = 0;


void accel_moving_average(int16_t* x_channel, int16_t *y_channel, int16_t *z_channel) {
  static int16_t x_buffer[MOVING_AVERAGE_SIZE] = {0};
  static int16_t y_buffer[MOVING_AVERAGE_SIZE] = {0};
  static int16_t z_buffer[MOVING_AVERAGE_SIZE] = {0};
  static uint8_t len = 0;
  int32_t x_sum = 0;
  int32_t y_sum = 0;
  int32_t z_sum = 0;
  int8_t i;

  if(len < MOVING_AVERAGE_SIZE) {
	    len++; 
        x_buffer[(MOVING_AVERAGE_SIZE-1)-len] = *x_channel;  
		y_buffer[(MOVING_AVERAGE_SIZE-1)-len] = *y_channel;  
		z_buffer[(MOVING_AVERAGE_SIZE-1)-len] = *z_channel;  
  } else {
	  for(i=0;i<(MOVING_AVERAGE_SIZE-1);i++) {
		  x_buffer[(MOVING_AVERAGE_SIZE-1)-i] = x_buffer[(MOVING_AVERAGE_SIZE-1)-i-1];
		  y_buffer[(MOVING_AVERAGE_SIZE-1)-i] = y_buffer[(MOVING_AVERAGE_SIZE-1)-i-1];
		  z_buffer[(MOVING_AVERAGE_SIZE-1)-i] = z_buffer[(MOVING_AVERAGE_SIZE-1)-i-1];
	  }
      x_buffer[0] = *x_channel;
	  y_buffer[0] = *y_channel;
	  z_buffer[0] = *z_channel;
	  for(i=0;i<MOVING_AVERAGE_SIZE;i++) {
		  x_sum += x_buffer[i];
		  y_sum += y_buffer[i];
		  z_sum += z_buffer[i];
	  }
	  *x_channel = x_sum/MOVING_AVERAGE_SIZE;
	  *y_channel = y_sum/MOVING_AVERAGE_SIZE;
	  *z_channel = z_sum/MOVING_AVERAGE_SIZE;
  }
}

void SigmaDeltaInit(void)
{
	uint8_t SI_byte = SystemFeatures.OpSettings[ACCEL_TAMPER_SIGMA] & ACCEL_TAMPER_IMMEDIATE_MASK;
	uint8_t SH_byte = SystemFeatures.OpSettings[ACCEL_TAMPER_SIGMA] >> 8;

	if (100 == (SI_byte + SH_byte)) {
		Sigma_Immediate = (float)(SI_byte) / 100;
		Sigma_Historical = (float)(SH_byte) / 100;
		Delta_Threshold = SystemFeatures.OpSettings[ACCEL_TAMPER_SIGMA2] & ACCEL_TAMPER_THRESHOLD_MASK;
	}
}

bool CalculateSigmaDelta(void) {
	if (XAxis_Immediate == 0 && YAxis_Immediate == 0 && ZAxis_Immediate == 0) {
		// Seed all values
		XAxis_Immediate = XAxis;
		YAxis_Immediate = YAxis;
		ZAxis_Immediate = ZAxis;

		XAxis_Historical = XAxis;
		YAxis_Historical = YAxis;
		ZAxis_Historical = ZAxis;
	} else {
		XAxis_Immediate = XAxis_Immediate * (1 - Sigma_Immediate) + XAxis * Sigma_Immediate;
		YAxis_Immediate = YAxis_Immediate * (1 - Sigma_Immediate) + YAxis * Sigma_Immediate;
		ZAxis_Immediate = ZAxis_Immediate * (1 - Sigma_Immediate) + ZAxis * Sigma_Immediate;

		XAxis_Historical = XAxis_Historical * (1 - Sigma_Historical) + XAxis * Sigma_Historical;
		YAxis_Historical = YAxis_Historical * (1 - Sigma_Historical) + YAxis * Sigma_Historical;
		ZAxis_Historical = ZAxis_Historical * (1 - Sigma_Historical) + ZAxis * Sigma_Historical;
		if (
			abs(MAX(XAxis_Historical, XAxis_Immediate) - MIN(XAxis_Historical, XAxis_Immediate)) > Delta_Threshold ||
			abs(MAX(YAxis_Historical, YAxis_Immediate) - MIN(YAxis_Historical, YAxis_Immediate)) > Delta_Threshold ||
			abs(MAX(ZAxis_Historical, ZAxis_Immediate) - MIN(ZAxis_Historical, ZAxis_Immediate)) > Delta_Threshold) {
			return true;
		}
	}
	return false;
}

// CheckForTamper checks the accelerometer for a possible tamper situation and signals if one is active.
void CheckForTamper(void) {
	uint16_t countDown;

	tamperSettings = SystemFeatures.OpSettings[OPERATION_INDEX];
	tamperSettings &= (ENABLE_TAMPER_CNTRL_LINE | ENABLE_TAMPER_EVENTS);

	maxStabilityCounter = SystemFeatures.OpSettings[EXT_OPERATION_INDEX];
	maxStabilityCounter &= TAMPER_STABILITY_COUNT_MASK;
	maxStabilityCounter >>= 8;
	if (0 == maxStabilityCounter) {
		maxStabilityCounter = DEF_TAMPER_INACTIVE_COUNTER;
	}

	maxTamperActiveCounter = SystemFeatures.OpSettings[EXT_OPERATION_INDEX];
	maxTamperActiveCounter &= TAMPER_ACTIVE_COUNT_MASK;
	maxTamperActiveCounter >>= 12;
	if (0 == maxTamperActiveCounter) {
		maxTamperActiveCounter = DEF_TAMPER_ACTIVE_COUNTER;
	}

	if ((0 == TamperCountDown) && (0 != tamperSettings)) {
		GetXYZData(&XAxis, &YAxis, &ZAxis);
        if (!isFWBuildProductionTest()) {   
            accel_moving_average(&XAxis, &YAxis, &ZAxis);
        }
		if (CalculateSigmaDelta()) {
			if (tamperActiveCounter < maxTamperActiveCounter) {
				tamperActiveCounter++;
			} else {
				stabilityCounter = 0;
				SetTamper(TAMPER_ACTIVE);
			}
		} else {
			//
			// Tamper must remain stable in an inactive state before
			// a tamper state of inactive is declared.
			//
			tamperActiveCounter = 0;
			if (stabilityCounter < maxStabilityCounter) {
				stabilityCounter++;
			} else if (stabilityCounter == maxStabilityCounter) {
				SetTamper(TAMPER_INACTIVE);
				// Increment stabilityCounter > MAX_STABILITY_COUNTER
				// This halts reports until the next tamper active condition.
				stabilityCounter++;
			}
		}
	
		if ((TAMPER_ACTIVE == lastTamperState) || (TRUE == fTamperAlarmOn)) {
		
			if ((0 == (SystemFeatures.OpSettings[OPERATION_INDEX] & OSDP_AUTO_DETECT_ACTIVE)) &&
				(0 != (SystemFeatures.OpSettings[OPERATION_INDEX] & (ENABLE_TAMPER_AUDIO_ALARM)))) {
				fTamperAlarmOn = TRUE;
				BeeperOn(); // Turn on Tamper Alarm
			}
		}

		//
		// Set the timer for the next tamper check.
		//
		countDown = (SystemFeatures.OpSettings[DEF_TAMPER_CONFIG_INDEX] &
					 TAMPER_COUNTDOWN_MASK);
		if (0 == countDown) {
			countDown = DEF_TAMPER_COUNTDOWN;
		}
		SetTimerValue(TAMPER_COUNT_DOWN_TIMER, countDown);
	}
}

// SetTamper sets the tamper line to active or inactive.

void SetTamper(bool tamperState) {
	uint8_t eventVal;
	//LOG_ERR("%s",tamperState?"ACTIVE":"INACTIVE");
	//
	// Store any tamper event
	//
	if (TAMPER_ACTIVE == tamperState) { 
		eventVal = HOST_EVENT_TAMPER_ACTIVE;
	} else {
		eventVal = HOST_EVENT_TAMPER_INACTIVE;
	}
	StoreEventForHost(eventVal);

	//
	// Drive the Tamper control line if configured to do so.
	//
	if ((0 != (tamperSettings & ENABLE_TAMPER_CNTRL_LINE)) ||
            isFWBuildProductionTest()) {
		if (tamperState) {
			gpio_set(CONTROL_LINE_TAMPER_PIN);
		} else {
			gpio_unset(CONTROL_LINE_TAMPER_PIN);
		}
	}

	//
	// Report Tamper Events if configured to do so.
	//
	if (0 != (tamperSettings & ENABLE_TAMPER_EVENTS)) {
		//
		// Transmit the tamper event.
		//
		if (0 == (SystemFeatures.OpSettings[OPERATION_INDEX] & OSDP_AUTO_DETECT_ACTIVE)) {
			if ((0 == (SystemFeatures.OpSettings[OPERATION_INDEX] & REPORT_TAMPER_STATE_CHANGE_ONLY)) ||
				(lastTamperState != tamperState) ||
				(true == fFirstTamperReport)) {
				TransmitEvent(eventVal);
			}
		}
	}
	lastTamperState = tamperState;
	fFirstTamperReport = FALSE;
}

// GetTamperState returns the last tamper state measured.
bool GetTamperState(void)
{
	return lastTamperState;
}