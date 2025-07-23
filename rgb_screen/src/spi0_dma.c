#include "spi0_dma.h"

static const int gpio_din = 3;
static const int gpio_clk = 2;
static const int gpio_cs = 17;
static const int gpio_dc = 16;

static volatile uint dma_tx;

static lv_disp_drv_t *disp_drv_dma;

void set_disp_drv(lv_disp_drv_t *disp_drv)
{
    disp_drv_dma = disp_drv;
}

static void dma_handler()
{
    dma_hw->ints0 = 1u << dma_tx;
    lv_disp_flush_ready(disp_drv_dma);
}

void spi0_dma_init()
{
    spi_init(spi0, 200 * 1000 * 1000);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_set_function(gpio_din, GPIO_FUNC_SPI);
    gpio_set_function(gpio_clk, GPIO_FUNC_SPI);

    gpio_init(gpio_cs);
    gpio_init(gpio_dc);

    gpio_set_dir(gpio_cs, GPIO_OUT);
    gpio_set_dir(gpio_dc, GPIO_OUT);

    dma_tx = dma_claim_unused_channel(true);

    dma_channel_set_irq0_enabled(dma_tx, true);

    // Configure the processor to run dma_handler() when DMA IRQ 0 is asserted
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

void dma_reinit(void *data, size_t length)
{
    dma_channel_config c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(spi0, true));
    dma_channel_configure(dma_tx, &c,
                          &spi_get_hw(spi0)->dr, // write address
                          data,                  // read address
                          length,                // element count (each element is of size transfer_data_size)
                          true);                 // don't start yet

    dma_channel_wait_for_finish_blocking(dma_tx);
}

void dma_unclaim()
{
    dma_channel_unclaim(dma_tx);
}