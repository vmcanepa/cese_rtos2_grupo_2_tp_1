/*
 * Copyright (c) 2023 Sebastian Bedin <sebabedin@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author : Sebastian Bedin <sebabedin@gmail.com>
 */

/********************** inclusions *******************************************/

#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"

#include "task_button.h"
#include "task_led.h"
#include "task_ui.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration *****************************/

ao_led_handle_t led_red, led_green, led_blue;

//SemaphoreHandle_t hsem_button;
//SemaphoreHandle_t hsem_led;

/********************** external functions definition ************************/
void app_init(void)
{

	BaseType_t status;
	led_red.color = AO_LED_COLOR_RED;
	led_green.color = AO_LED_COLOR_GREEN;
	led_blue.color = AO_LED_COLOR_BLUE;

	status = xTaskCreate(task_button, "task_button", 128, NULL, tskIDLE_PRIORITY, NULL);
	while (pdPASS != status) { }



	task_ao_ui_init();



	status = xTaskCreate(task_led, "task_led", 128, (void* const)&led_red, tskIDLE_PRIORITY+1, NULL);
	while (pdPASS != status) { }

	status = xTaskCreate(task_led, "task_led", 128, (void* const)&led_green, tskIDLE_PRIORITY+1, NULL);
	while (pdPASS != status) { }

	status = xTaskCreate(task_led, "task_led", 128, (void* const)&led_blue, tskIDLE_PRIORITY+1, NULL);
	while (pdPASS != status) { }

	LOGGER_INFO("app init");

	cycle_counter_init();
}

/********************** end of file ******************************************/
