#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_rs232.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"

/*
 * This structure holds a pointer to each of the open devices
*/
struct registered_devices {
	alt_up_ps2_dev *ps2_dev;
	alt_up_rs232_dev *serial_dev;
	alt_up_char_buffer_dev *char_buf_dev;
	alt_up_pixel_buffer_dma_dev *pix_buf_dev;
};
