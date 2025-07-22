#if !defined(SPI0_DMA_H)
#define SPI0_DMA_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "lvgl.h"

void set_disp_drv(lv_disp_drv_t * disp_drv);
void dma_handler();

void spi0_dma_init();
void dma_reinit(void * data, size_t length);
void dma_unclaim();

#endif // SPI0_DMA_H
