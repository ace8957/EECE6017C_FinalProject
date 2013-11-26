#include "graphics.h"

/**
 * convert a 24-bit color down to a 16-bit color. Assumes
 * the 16-bit color has the layout:
 * R    G   B     R   G   B
 * ---------- --> ---------
 * 8    8   8     5   6   5
 */
inline short colorAsShort(struct color c)
{
    unsigned int redComponent = ((unsigned int)c.red*32)/255;
    unsigned int greenComponent = ((unsigned int)c.green*64)/255;
    unsigned int blueComponent = ((unsigned int)c.blue*32)/255;
    short ret = (redComponent&0x1F)<<(11) | (greenComponent&0x3F)<<(5) | (blueComponent&0x1F);
    return ret;
}

inline struct color colorRGB(unsigned char red, unsigned char green, unsigned char blue)
{
    struct color c = {
        .red = red,
        .green = green,
        .blue = blue
    };
    return c;
}

void drawText(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

void drawBox(int x, int y, int width, int height, struct color c)
{
	int offset, row, col;
  	volatile short * pixel_buffer = (short *) 0x08000000;	// VGA pixel buffer

	/* assume that the box coordinates are valid */
	for (row = y; row <= y+height; ++row)
	{
		for(col = x; col < x+width; ++col)
        {
            // From this calculation, it appears that the pixel buffer is laid out as 320 rows of 512 columns
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = colorAsShort(c);	// compute halfword address, set pixel
			++col;
		}
	}
}
