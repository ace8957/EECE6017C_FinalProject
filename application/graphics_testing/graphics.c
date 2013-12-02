#include "graphics.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct color colorRGB(unsigned char red, unsigned char green, unsigned char blue)

{
    struct color c = {
        .red = red,
        .green = green,
        .blue = blue
    };
    return c;
}

void drawText(int x, int y, const char * text_ptr)
{
    float colors[4];
    const char *curChar = text_ptr;
    glGetFloatv(GL_CURRENT_COLOR, colors);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRasterPos2i(x, y);
        while(*curChar) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *curChar);
            ++curChar;
        }
    glPopMatrix();
    glColor4fv(colors);
    return;
}

void drawBox(int x, int y, int width, int height, struct color c)
{
    float colors[4];
    glGetFloatv(GL_CURRENT_COLOR, colors);
    glColor4f(c.red/255.0f, c.green/255.0f, c.blue/255.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x+width, y);
        glVertex2i(x+width, y+height);
        glVertex2i(x, y+height);
    glEnd();
    glColor4fv(colors);
    return;
}
