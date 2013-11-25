#ifndef GRAPHICS_H
#define GRAPHICS_H 1

#define VGA_WIDTH 320 
#define VGA_HEIGHT 240

struct color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

#define COLOR_RED struct color {\
    .red = 255;\
    .green = 0;\
    .blue = 0;\
}

#define COLOR_GREEN struct color {\
    .red = 0;\
    .green = 255;\
    .blue = 0;\
}

#define COLOR_BLUE struct color {\
    .red = 0;\
    .green = 0;\
    .blue = 255;\
}

inline struct color colorRGB(unsigned char red, unsigned char green, unsigned char blue);

/*
 * Write a line of text to the screen with the top left corner at (x, y)
 * @param x Where the text begins along the horizontal axis
 * @param y Where the text begins along the vertical axis
 * @param text_ptr Null terminated string to be displayed
 */
void drawText(int x, int y, char * text_ptr);

/*
 * Draw a filled rectangle of the specified color.
 * @param x Absolute screen position of the left side of the box
 * @param y Absolute screen position of the top of the box
 * @param width How wide the box is, in pixels
 * @param height How tall the box is, in pixels
 * @param c Color the box should be
 */
void drawBox(int x, int y, int width, int height, struct color c);

#endif //GRAPHICS_H
