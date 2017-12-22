/**
 ******************************************************************************
 * File Name          : main.c
 * Description        : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2017 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#define SINTBLSTEPS 360

unsigned char sintbl[3 * SINTBLSTEPS] = { 0x80, 0xEE, 0x11, 0x82, 0xED, 0x10,
		0x84, 0xEC, 0x0F, 0x86, 0xEA, 0x0E, 0x88, 0xE9, 0x0D, 0x8B, 0xE8, 0x0C,
		0x8D, 0xE7, 0x0B, 0x8F, 0xE5, 0x0A, 0x91, 0xE4, 0x09, 0x94, 0xE3, 0x08,
		0x96, 0xE1, 0x08, 0x98, 0xE0, 0x07, 0x9A, 0xDE, 0x06, 0x9C, 0xDD, 0x06,
		0x9E, 0xDB, 0x05, 0xA1, 0xDA, 0x04, 0xA3, 0xD8, 0x04, 0xA5, 0xD6, 0x03,
		0xA7, 0xD5, 0x03, 0xA9, 0xD3, 0x02, 0xAB, 0xD1, 0x02, 0xAD, 0xD0, 0x02,
		0xAF, 0xCE, 0x01, 0xB1, 0xCC, 0x01, 0xB3, 0xCA, 0x01, 0xB6, 0xC9, 0x00,
		0xB8, 0xC7, 0x00, 0xBA, 0xC5, 0x00, 0xBC, 0xC3, 0x00, 0xBD, 0xC1, 0x00,
		0xBF, 0xBF, 0x00, 0xC1, 0xBD, 0x00, 0xC3, 0xBB, 0x00, 0xC5, 0xB9, 0x00,
		0xC7, 0xB7, 0x00, 0xC9, 0xB5, 0x01, 0xCB, 0xB3, 0x01, 0xCC, 0xB1, 0x01,
		0xCE, 0xAF, 0x01, 0xD0, 0xAD, 0x02, 0xD2, 0xAB, 0x02, 0xD3, 0xA9, 0x02,
		0xD5, 0xA7, 0x03, 0xD7, 0xA5, 0x03, 0xD8, 0xA2, 0x04, 0xDA, 0xA0, 0x04,
		0xDB, 0x9E, 0x05, 0xDD, 0x9C, 0x06, 0xDE, 0x9A, 0x06, 0xE0, 0x98, 0x07,
		0xE1, 0x95, 0x08, 0xE3, 0x93, 0x09, 0xE4, 0x91, 0x09, 0xE6, 0x8F, 0x0A,
		0xE7, 0x8C, 0x0B, 0xE8, 0x8A, 0x0C, 0xE9, 0x88, 0x0D, 0xEB, 0x86, 0x0E,
		0xEC, 0x84, 0x0F, 0xED, 0x81, 0x10, 0xEE, 0x7F, 0x11, 0xEF, 0x7D, 0x12,
		0xF0, 0x7B, 0x14, 0xF1, 0x78, 0x15, 0xF2, 0x76, 0x16, 0xF3, 0x74, 0x17,
		0xF4, 0x72, 0x19, 0xF5, 0x70, 0x1A, 0xF6, 0x6D, 0x1B, 0xF7, 0x6B, 0x1D,
		0xF7, 0x69, 0x1E, 0xF8, 0x67, 0x20, 0xF9, 0x65, 0x21, 0xFA, 0x62, 0x23,
		0xFA, 0x60, 0x24, 0xFB, 0x5E, 0x26, 0xFB, 0x5C, 0x27, 0xFC, 0x5A, 0x29,
		0xFC, 0x58, 0x2B, 0xFD, 0x56, 0x2C, 0xFD, 0x53, 0x2E, 0xFE, 0x51, 0x30,
		0xFE, 0x4F, 0x31, 0xFE, 0x4D, 0x33, 0xFE, 0x4B, 0x35, 0xFF, 0x49, 0x37,
		0xFF, 0x47, 0x39, 0xFF, 0x45, 0x3B, 0xFF, 0x43, 0x3C, 0xFF, 0x41, 0x3E,
		0xFF, 0x3F, 0x40, 0xFF, 0x3D, 0x42, 0xFF, 0x3B, 0x44, 0xFF, 0x3A, 0x46,
		0xFF, 0x38, 0x48, 0xFE, 0x36, 0x4A, 0xFE, 0x34, 0x4C, 0xFE, 0x32, 0x4E,
		0xFE, 0x31, 0x50, 0xFD, 0x2F, 0x52, 0xFD, 0x2D, 0x54, 0xFD, 0x2B, 0x57,
		0xFC, 0x2A, 0x59, 0xFC, 0x28, 0x5B, 0xFB, 0x26, 0x5D, 0xFA, 0x25, 0x5F,
		0xFA, 0x23, 0x61, 0xF9, 0x22, 0x63, 0xF9, 0x20, 0x66, 0xF8, 0x1F, 0x68,
		0xF7, 0x1D, 0x6A, 0xF6, 0x1C, 0x6C, 0xF5, 0x1B, 0x6E, 0xF5, 0x19, 0x71,
		0xF4, 0x18, 0x73, 0xF3, 0x17, 0x75, 0xF2, 0x15, 0x77, 0xF1, 0x14, 0x7A,
		0xF0, 0x13, 0x7C, 0xEF, 0x12, 0x7E, 0xEE, 0x11, 0x80, 0xEC, 0x10, 0x82,
		0xEB, 0x0F, 0x85, 0xEA, 0x0E, 0x87, 0xE9, 0x0D, 0x89, 0xE7, 0x0C, 0x8B,
		0xE6, 0x0B, 0x8E, 0xE5, 0x0A, 0x90, 0xE3, 0x09, 0x92, 0xE2, 0x08, 0x94,
		0xE1, 0x07, 0x96, 0xDF, 0x07, 0x99, 0xDE, 0x06, 0x9B, 0xDC, 0x05, 0x9D,
		0xDB, 0x05, 0x9F, 0xD9, 0x04, 0xA1, 0xD7, 0x04, 0xA3, 0xD6, 0x03, 0xA6,
		0xD4, 0x03, 0xA8, 0xD2, 0x02, 0xAA, 0xD1, 0x02, 0xAC, 0xCF, 0x01, 0xAE,
		0xCD, 0x01, 0xB0, 0xCC, 0x01, 0xB2, 0xCA, 0x01, 0xB4, 0xC8, 0x00, 0xB6,
		0xC6, 0x00, 0xB8, 0xC4, 0x00, 0xBA, 0xC2, 0x00, 0xBC, 0xC0, 0x00, 0xBE,
		0xBE, 0x00, 0xC0, 0xBC, 0x00, 0xC2, 0xBB, 0x00, 0xC4, 0xB9, 0x00, 0xC6,
		0xB7, 0x00, 0xC8, 0xB5, 0x01, 0xC9, 0xB2, 0x01, 0xCB, 0xB0, 0x01, 0xCD,
		0xAE, 0x01, 0xCF, 0xAC, 0x02, 0xD1, 0xAA, 0x02, 0xD2, 0xA8, 0x03, 0xD4,
		0xA6, 0x03, 0xD6, 0xA4, 0x03, 0xD7, 0xA2, 0x04, 0xD9, 0xA0, 0x05, 0xDA,
		0x9D, 0x05, 0xDC, 0x9B, 0x06, 0xDD, 0x99, 0x07, 0xDF, 0x97, 0x07, 0xE0,
		0x95, 0x08, 0xE2, 0x92, 0x09, 0xE3, 0x90, 0x0A, 0xE5, 0x8E, 0x0B, 0xE6,
		0x8C, 0x0B, 0xE7, 0x8A, 0x0C, 0xE9, 0x87, 0x0D, 0xEA, 0x85, 0x0E, 0xEB,
		0x83, 0x0F, 0xEC, 0x81, 0x11, 0xED, 0x7E, 0x12, 0xEE, 0x7C, 0x13, 0xF0,
		0x7A, 0x14, 0xF1, 0x78, 0x15, 0xF2, 0x75, 0x16, 0xF3, 0x73, 0x18, 0xF4,
		0x71, 0x19, 0xF4, 0x6F, 0x1A, 0xF5, 0x6D, 0x1C, 0xF6, 0x6A, 0x1D, 0xF7,
		0x68, 0x1F, 0xF8, 0x66, 0x20, 0xF8, 0x64, 0x22, 0xF9, 0x62, 0x23, 0xFA,
		0x5F, 0x25, 0xFA, 0x5D, 0x26, 0xFB, 0x5B, 0x28, 0xFC, 0x59, 0x29, 0xFC,
		0x57, 0x2B, 0xFC, 0x55, 0x2D, 0xFD, 0x53, 0x2E, 0xFD, 0x51, 0x30, 0xFE,
		0x4F, 0x32, 0xFE, 0x4D, 0x34, 0xFE, 0x4A, 0x36, 0xFE, 0x48, 0x37, 0xFF,
		0x46, 0x39, 0xFF, 0x44, 0x3B, 0xFF, 0x43, 0x3D, 0xFF, 0x41, 0x3F, 0xFF,
		0x3F, 0x41, 0xFF, 0x3D, 0x43, 0xFF, 0x3B, 0x45, 0xFF, 0x39, 0x47, 0xFF,
		0x37, 0x49, 0xFF, 0x35, 0x4B, 0xFE, 0x33, 0x4D, 0xFE, 0x32, 0x4F, 0xFE,
		0x30, 0x51, 0xFE, 0x2E, 0x53, 0xFD, 0x2D, 0x55, 0xFD, 0x2B, 0x57, 0xFC,
		0x29, 0x59, 0xFC, 0x28, 0x5C, 0xFB, 0x26, 0x5E, 0xFB, 0x24, 0x60, 0xFA,
		0x23, 0x62, 0xFA, 0x21, 0x64, 0xF9, 0x20, 0x66, 0xF8, 0x1E, 0x69, 0xF8,
		0x1D, 0x6B, 0xF7, 0x1C, 0x6D, 0xF6, 0x1A, 0x6F, 0xF5, 0x19, 0x71, 0xF4,
		0x18, 0x74, 0xF3, 0x16, 0x76, 0xF2, 0x15, 0x78, 0xF1, 0x14, 0x7A, 0xF0,
		0x13, 0x7D, 0xEF, 0x11, 0x7F, 0xEE, 0x10, 0x81, 0xED, 0x0F, 0x83, 0xEC,
		0x0E, 0x85, 0xEB, 0x0D, 0x88, 0xEA, 0x0C, 0x8A, 0xE8, 0x0B, 0x8C, 0xE7,
		0x0A, 0x8E, 0xE6, 0x0A, 0x91, 0xE4, 0x09, 0x93, 0xE3, 0x08, 0x95, 0xE2,
		0x07, 0x97, 0xE0, 0x06, 0x99, 0xDF, 0x06, 0x9C, 0xDD, 0x05, 0x9E, 0xDC,
		0x05, 0xA0, 0xDA, 0x04, 0xA2, 0xD9, 0x03, 0xA4, 0xD7, 0x03, 0xA6, 0xD5,
		0x02, 0xA8, 0xD4, 0x02, 0xAB, 0xD2, 0x02, 0xAD, 0xD0, 0x01, 0xAF, 0xCE,
		0x01, 0xB1, 0xCD, 0x01, 0xB3, 0xCB, 0x01, 0xB5, 0xC9, 0x00, 0xB7, 0xC7,
		0x00, 0xB9, 0xC5, 0x00, 0xBB, 0xC4, 0x00, 0xBD, 0xC2, 0x00, 0xBF, 0xC0,
		0x00, 0xC1, 0xBE, 0x00, 0xC3, 0xBC, 0x00, 0xC4, 0xBA, 0x00, 0xC6, 0xB8,
		0x00, 0xC8, 0xB6, 0x01, 0xCA, 0xB4, 0x01, 0xCC, 0xB2, 0x01, 0xCE, 0xB0,
		0x01, 0xCF, 0xAE, 0x02, 0xD1, 0xAC, 0x02, 0xD3, 0xA9, 0x03, 0xD4, 0xA7,
		0x03, 0xD6, 0xA5, 0x04, 0xD8, 0xA3, 0x04, 0xD9, 0xA1, 0x05, 0xDB, 0x9F,
		0x05, 0xDC, 0x9D, 0x06, 0xDE, 0x9A, 0x07, 0xDF, 0x98, 0x08, 0xE1, 0x96,
		0x08, 0xE2, 0x94, 0x09, 0xE4, 0x92, 0x0A, 0xE5, 0x8F, 0x0B, 0xE6, 0x8D,
		0x0C, 0xE8, 0x8B, 0x0D, 0xE9, 0x89, 0x0E, 0xEA, 0x87, 0x0F, 0xEB, 0x84,
		0x10, 0xED, 0x82, 0x11, 0xEE, 0x80, 0x12, 0xEF, 0x7E, 0x13, 0xF0, 0x7B,
		0x14, 0xF1, 0x79, 0x16, 0xF2, 0x77, 0x17, 0xF3, 0x75, 0x18, 0xF4, 0x73,
		0x19, 0xF5, 0x70, 0x1B, 0xF6, 0x6E, 0x1C, 0xF6, 0x6C, 0x1E, 0xF7, 0x6A,
		0x1F, 0xF8, 0x67, 0x21, 0xF9, 0x65, 0x22, 0xF9, 0x63, 0x24, 0xFA, 0x61,
		0x25, 0xFB, 0x5F, 0x27, 0xFB, 0x5D, 0x28, 0xFC, 0x5A, 0x2A, 0xFC, 0x58,
		0x2C, 0xFD, 0x56, 0x2D, 0xFD, 0x54, 0x2F, 0xFD, 0x52, 0x31, 0xFE, 0x50,
		0x33, 0xFE, 0x4E, 0x34, 0xFE, 0x4C, 0x36, 0xFE, 0x4A, 0x38, 0xFF, 0x48,
		0x3A, 0xFF, 0x46, 0x3C, 0xFF, 0x44, 0x3E, 0xFF, 0x42, 0x40, 0xFF, 0x40,
		0x42, 0xFF, 0x3E, 0x43, 0xFF, 0x3C, 0x45, 0xFF, 0x3A, 0x47, 0xFF, 0x38,
		0x49, 0xFF, 0x36, 0x4C, 0xFE, 0x35, 0x4E, 0xFE, 0x33, 0x50, 0xFE, 0x31,
		0x52, 0xFD, 0x2F, 0x54, 0xFD, 0x2E, 0x56, 0xFD, 0x2C, 0x58, 0xFC, 0x2A,
		0x5A, 0xFC, 0x29, 0x5C, 0xFB, 0x27, 0x5E, 0xFB, 0x25, 0x61, 0xFA, 0x24,
		0x63, 0xF9, 0x22, 0x65, 0xF9, 0x21, 0x67, 0xF8, 0x1F, 0x69, 0xF7, 0x1E,
		0x6B, 0xF7, 0x1C, 0x6E, 0xF6, 0x1B, 0x70, 0xF5, 0x1A, 0x72, 0xF4, 0x18,
		0x74, 0xF3, 0x17, 0x77, 0xF2, 0x16, 0x79, 0xF1, 0x15, 0x7B, 0xF0, 0x13,
		0x7D, 0xEF, 0x12, 0x7F, 0xEE, 0x11 };

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim1_up;
DMA_HandleTypeDef hdma_tim3_ch4_up;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/**
 * @brief  Configure the DMA Burst to transfer Data from the memory to the TIM peripheral
 * @param  htim : TIM handle
 * @param  BurstBaseAddress : TIM Base address from where the DMA will start the Data write
 *         This parameter can be one of the following values:
 *            @arg TIM_DMABASE_CR1
 *            @arg TIM_DMABASE_CR2
 *            @arg TIM_DMABASE_SMCR
 *            @arg TIM_DMABASE_DIER
 *            @arg TIM_DMABASE_SR
 *            @arg TIM_DMABASE_EGR
 *            @arg TIM_DMABASE_CCMR1
 *            @arg TIM_DMABASE_CCMR2
 *            @arg TIM_DMABASE_CCER
 *            @arg TIM_DMABASE_CNT
 *            @arg TIM_DMABASE_PSC
 *            @arg TIM_DMABASE_ARR
 *            @arg TIM_DMABASE_RCR
 *            @arg TIM_DMABASE_CCR1
 *            @arg TIM_DMABASE_CCR2
 *            @arg TIM_DMABASE_CCR3
 *            @arg TIM_DMABASE_CCR4
 *            @arg TIM_DMABASE_BDTR
 *            @arg TIM_DMABASE_DCR
 * @param  BurstRequestSrc : TIM DMA Request sources
 *         This parameter can be one of the following values:
 *            @arg TIM_DMA_UPDATE: TIM update Interrupt source
 *            @arg TIM_DMA_CC1: TIM Capture Compare 1 DMA source
 *            @arg TIM_DMA_CC2: TIM Capture Compare 2 DMA source
 *            @arg TIM_DMA_CC3: TIM Capture Compare 3 DMA source
 *            @arg TIM_DMA_CC4: TIM Capture Compare 4 DMA source
 *            @arg TIM_DMA_COM: TIM Commutation DMA source
 *            @arg TIM_DMA_TRIGGER: TIM Trigger DMA source
 * @param  BurstBuffer : The Buffer address.
 * @param  BurstLength : DMA Burst length. This parameter can be one value
 *         between: TIM_DMABURSTLENGTH_1TRANSFER and TIM_DMABURSTLENGTH_18TRANSFERS.
 * @retval HAL status
 */
extern void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMAPeriodElapsedCplt(DMA_HandleTypeDef *hdma) {
	TIM_HandleTypeDef* htim =
			(TIM_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;

	htim->State = HAL_TIM_STATE_READY;

	HAL_TIM_PeriodElapsedCallback(htim);
}
void TIM_DMATriggerCplt(DMA_HandleTypeDef *hdma) {

	TIM_HandleTypeDef* htim =
			(TIM_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;

	htim->State = HAL_TIM_STATE_READY;

	HAL_TIM_TriggerCallback(htim);
}

HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart_2(TIM_HandleTypeDef *htim,
		TIM_HandleTypeDef *htim_trg, uint32_t BurstBaseAddress,
		uint32_t BurstRequestSrc, uint32_t* BurstBuffer, uint32_t BurstLength,
		uint16_t BufferLength) {
	/* Check the parameters */
	assert_param(IS_TIM_DMABURST_INSTANCE(htim->Instance));
	assert_param(IS_TIM_DMABURST_INSTANCE(htim_trg->Instance));
	assert_param(IS_TIM_DMA_BASE(BurstBaseAddress));
	assert_param(IS_TIM_DMA_SOURCE(BurstRequestSrc));
	assert_param(IS_TIM_DMA_LENGTH(BurstLength));

	if ((htim->State == HAL_TIM_STATE_BUSY)) {
		return HAL_BUSY;
	} else if ((htim->State == HAL_TIM_STATE_READY)) {
		if ((BurstBuffer == 0U) && (BurstLength > 0U)) {
			return HAL_ERROR;
		} else {
			htim->State = HAL_TIM_STATE_BUSY;
		}
	}
	switch (BurstRequestSrc) {
	case TIM_DMA_UPDATE: {
		/* Set the DMA Period elapsed callback */
		htim_trg->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback =
				TIM_DMAPeriodElapsedCplt;

		/* Set the DMA error callback */
		htim_trg->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim_trg->hdma[TIM_DMA_ID_UPDATE],
				(uint32_t) BurstBuffer, (uint32_t) &htim->Instance->DMAR, /*((BurstLength) >> 8U) + 1U*/
				BufferLength);
	}
		break;
	case TIM_DMA_CC1: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMADelayPulseCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t) BurstBuffer,
				(uint32_t) &htim->Instance->DMAR, ((BurstLength) >> 8U) + 1U);
	}
		break;
	case TIM_DMA_CC2: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMADelayPulseCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t) BurstBuffer,
				(uint32_t) &htim->Instance->DMAR, ((BurstLength) >> 8U) + 1U);
	}
		break;
	case TIM_DMA_CC3: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMADelayPulseCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t) BurstBuffer,
				(uint32_t) &htim->Instance->DMAR, ((BurstLength) >> 8U) + 1U);
	}
		break;
	case TIM_DMA_CC4: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMADelayPulseCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t) BurstBuffer,
				(uint32_t) &htim->Instance->DMAR, ((BurstLength) >> 8U) + 1U);
	}
		break;
	case TIM_DMA_COM: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_COMMUTATION]->XferCpltCallback =
				TIMEx_DMACommutationCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_COMMUTATION]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_COMMUTATION],
				(uint32_t) BurstBuffer, (uint32_t) &htim->Instance->DMAR,
				((BurstLength) >> 8U) + 1U);
	}
		break;
	case TIM_DMA_TRIGGER: {
		/* Set the DMA Period elapsed callback */
		htim->hdma[TIM_DMA_ID_TRIGGER]->XferCpltCallback = TIM_DMATriggerCplt;

		/* Set the DMA error callback */
		htim->hdma[TIM_DMA_ID_TRIGGER]->XferErrorCallback = TIM_DMAError;

		/* Enable the DMA channel */
		HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_TRIGGER], (uint32_t) BurstBuffer,
				(uint32_t) &htim->Instance->DMAR, ((BurstLength) >> 8U) + 1U);
	}
		break;
	default:
		break;
	}
	/* configure the DMA Burst Mode */
	htim->Instance->DCR = BurstBaseAddress | BurstLength;

	/* Enable the TIM DMA Request */
	__HAL_TIM_ENABLE_DMA(htim_trg, BurstRequestSrc);

	htim->State = HAL_TIM_STATE_READY;

	/* Return function status */
	return HAL_OK;
}

/* USER CODE END 0 */

int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();

	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim1);
//	HAL_TIM_DMABurst_WriteStart(&htim1, TIM_DMABASE_CCR1, TIM_DMA_UPDATE,
//			(uint32_t *) sintbl, TIM_DMABURSTLENGTH_3TRANSFERS);

//	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_DMABurst_WriteStart_2(&htim1, &htim3, TIM_DMABASE_CCR1,
	TIM_DMA_UPDATE, sintbl, TIM_DMABURSTLENGTH_3TRANSFERS, 3 * SINTBLSTEPS);
	HAL_Delay(1000);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 128);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 128);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 128);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;
	GPIO_InitTypeDef gpiodef;
	gpiodef.Mode = GPIO_MODE_OUTPUT_PP;
	gpiodef.Pin = GPIO_PIN_8;
	gpiodef.Pull = GPIO_NOPULL;
	gpiodef.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &gpiodef);

	while (1) {
		/* USER CODE END WHILE */
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
		HAL_Delay(400);
		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */

}

/** System Clock Configuration
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM1 init function */
static void MX_TIM1_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 3200 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 255;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	HAL_TIM_MspPostInit(&htim1);

}

/* TIM3 init function */
static void MX_TIM3_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 1000 - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 32;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/** 
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {
	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

	/* DMA interrupt init */
	/* DMA1_Channel3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	/* DMA1_Channel5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/** Configure pins as 
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 * Free pins are configured automatically as Analog (this feature is enabled through
 * the Code Generation settings)
 */
static void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOD_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

	/*Configure GPIO pins : PC13 PC14 PC15 */
	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PA0 PA1 PA2 PA3
	 PA4 PA5 PA6 PA11
	 PA12 PA13 PA14 PA15 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12
			| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB2 PB10 PB11 PB12
	 PB13 PB14 PB15 PB3
	 PB4 PB5 PB6 PB7
	 PB9 */
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
			| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4
			| GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PB8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char * file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */

}

#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
