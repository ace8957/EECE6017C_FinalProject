#ifndef GRAPHICS_H
#define GRAPHICS_H 1

struct color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

#define COLOR_RED {\
    .red = 255;\
    .green = 0;\
    .blue = 0;\
}

#define COLOR_WHITE {\
    .red = 255;\
    .green = 255;\
    .blue = 0;\
}

#define COLOR_BLUE {\
    .red = 0;\
    .green = 0;\
    .blue = 255;\
}

#define COLOR_GREY {\
    .red = 128;\
    .green = 128;\
    .blue = 128;\
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
