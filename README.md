# GUI created with LVGL v8.3.11 and Pico-SDK

* LVGL has ST7789 driver port, that uses SPI non-blocking DMA when sending color data. Commands are sent with blocking SPI for the moment.
* Everything is implemented with IRQs, due to need for precise reading of data and updating screen elements.
* Altough not every ISR is short as possible, the system works for now, and maximum funcitonality for protoyping is required. Future work should include only flag changes in ISRs and do work in main loop - this could be done if multiple DMA communications are required which timing is critical.
