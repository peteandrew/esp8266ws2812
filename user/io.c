
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */


#include <esp8266.h>

#define LEDGPIO 2
#define BTNGPIO 0

static ETSTimer resetBtntimer;
static ETSTimer ledFlashTimer;

static char ledFlashing=0;


void ICACHE_FLASH_ATTR setLedFlashState(int ena) {
	if (ena) {
		ledFlashing = 1;
  } else {
		ledFlashing = 0;
	}
}

char ICACHE_FLASH_ATTR getLedFlashState(void) {
	return ledFlashing;
}

static void ICACHE_FLASH_ATTR resetBtnTimerCb(void *arg) {
	static int resetCnt=0;
	if (!GPIO_INPUT_GET(BTNGPIO)) {
		resetCnt++;
	} else {
		if (resetCnt>=6) { //3 sec pressed
			wifi_station_disconnect();
			wifi_set_opmode(0x3); //reset to AP+STA mode
			os_printf("Reset to AP mode. Restarting system...\n");
			system_restart();
		}
		resetCnt=0;
	}
}

static void ICACHE_FLASH_ATTR ledFlashTimerCb(void *arg) {
	if (!ledFlashing) return;

	//Do blinky stuff
	if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << LEDGPIO))
	{
		// set gpio low
		gpio_output_set(0, (1 << LEDGPIO), 0, 0);
	}
	else
	{
		// set gpio high
		gpio_output_set((1 << LEDGPIO), 0, 0, 0);
	}
}

void ioInit() {
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
	gpio_output_set(0, 0, (1<<LEDGPIO), (1<<BTNGPIO));
	os_timer_disarm(&resetBtntimer);
	os_timer_setfn(&resetBtntimer, resetBtnTimerCb, NULL);
	os_timer_arm(&resetBtntimer, 500, 1);

	os_timer_disarm(&ledFlashTimer);
	os_timer_setfn(&ledFlashTimer, ledFlashTimerCb, NULL);
	os_timer_arm(&ledFlashTimer, 500, 1);
}
