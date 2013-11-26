#ifndef GRAPHICS_H
#define GRAPHICS_H 1

struct color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

#define COLOR_HIT colorRGB(255, 0, 0)

#define COLOR_MISS colorRGB(255, 255, 0)

#define COLOR_WATER colorRGB(0, 0, 255)

#define COLOR_SHIP colorRGB(128, 128, 128)

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
