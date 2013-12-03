
extern struct registered_devices devices;

int init_dev(void)
{
    // We are using the rs232, ps2, pixel_buffer, and char_buffer
    alt_up_ps2_dev *keyboardDev;
    keyboardDev = alt_up_ps2_open_dev("/dev/PS2_Port");
    if(keyboardDev == NULL) {
        printf("No PS/2 controller present!\n");
    }
    else {
        // Initialize the PS/2 Communication
    	char kbdRead;
    	// reset the device
    	alt_up_ps2_write_data_byte(keyboardDev, 0xFF);

    	// Wait for an ACK
    	alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	while(kbdRead != 0xFA) {
    		alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	}

    	// Wait for the BAT Result
    	alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	while(kbdRead != 0xAA && kbdRead != 0xFC) {
    		alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	}
    	if(kbdRead == 0xFC) {
    		printf("Error with the PS/2 device!\n");
    	}

    	// Disable scanning
    	alt_up_ps2_write_data_byte(keyboardDev, 0xF5);
    	// Wait for an ACK
    	alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	while(kbdRead != 0xFA) {
    		alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	}

    	// Ask device to identify
    	alt_up_ps2_write_data_byte(keyboardDev, 0xF2);
    	// Wait for an ACK
    	alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	while(kbdRead != 0xFA) {
    		alt_up_ps2_read_data_byte(keyboardDev, &kbdRead);
    	}
    	// Receive the identifier, may be up to 2 bytes. If two bytes, then first byte will be
    	// 0xAB
    	char newRead;
    	alt_up_ps2_read_data_byte(keyboardDev, &newRead);
    	while(newRead == kbdRead) {
    		kbdRead = newRead;
    		alt_up_ps2_read_data_byte(keyboardDev, &newRead);
    	}
    	if(newRead == 0xAB) {
    		while(newRead == kbdRead) {
    			kbdRead = newRead;
    			alt_up_ps2_read_data_byte(keyboardDev, &newRead);
    		}

    	}
    	else {

    	}

        devices.ps2_dev = keyboardDev;
    }

    alt_up_rs232_dev *serialDev;
    serialDev = alt_up_rs232_open_dev("/dev/Serial_Port");
    if(serialDev == NULL) {
        printf("No RS-232 controller present!\n");
    }
    else {
        // Initialize the Serial connection

        devices.serial_dev = serialDev;
    }

    alt_up_char_buffer_dev *charBufDev;
    charBufDev = alt_up_char_buffer_open_dev("/dev/VGA_Char_Buffer");
    if(charBufDev == NULL) {
        printf("No VGA character buffer controller present!\n");
    }
    else {
        // Initialize the Character Buffer

        devices.char_buf_dev = charBufDev;
    }

    alt_up_pixel_buffer_dma_dev *pixBufDev;
    pixBufDev = alt_up_pixel_buffer_dma_open_dev("/dev/VGA_Pixel_Buffer");
    if(pixBufDev == NULL) {
        printf("No VGA pixel buffer controller present!\n");
    }
    else {
        // Initialize the Pixel Buffer

        devices.pix_buf_dev = pixBufDev;
    }

}
