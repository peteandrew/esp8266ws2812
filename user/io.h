#ifndef IO_H
#define IO_H

void ICACHE_FLASH_ATTR setLedFlashState(int ena);
char ICACHE_FLASH_ATTR getLedFlashState(void);
void ioInit(void);

#endif
