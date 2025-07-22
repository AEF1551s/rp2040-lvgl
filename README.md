# GUI created with LVGL v8.3.11 and Pico-SDK

* LVGL has ST7789 driver port, that uses SPI non-blocking DMA when sending color data. Commands are sent with blocking SPI for the moment.
* Everything is implemented with IRQs, due to need for precise reading of data and updating screen elements.