#include "../../lvgl/lvgl.h"
#include "../../lvgl/lv_conf.h"

//void ILI9341_flush(struct _disp_drv_t *, const lv_area_t * , lv_color_t * );
void ILI9341_flush(lv_disp_drv_t *, const lv_area_t * , lv_color_t * );
void DMA_ILI9341_SPI_TransmitComplete_Callback();
