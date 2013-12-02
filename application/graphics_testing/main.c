#include <GL/glut.h>
#include <stdio.h>
#include "graphics.h"
#include "ui.h"

/* Test graphics + ui 
0 - water
2 - miss
4 - hit
8 - ships
*/
int boardYours[] = {
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
};

int boardTheirs[] = {
    0,0,0,0,0,0,0,0,0,0,
    0,2,0,0,0,0,8,0,0,0,
    8,0,0,0,0,0,4,0,0,0,
    8,0,0,0,2,0,4,0,0,0,
    8,0,0,8,8,0,0,0,8,0,
    8,0,0,0,2,0,0,0,4,0,
    2,0,0,0,0,0,0,0,8,0,
    0,0,8,4,8,8,4,0,0,0,
    0,0,0,0,0,0,0,2,0,0,
    0,0,0,0,2,0,0,0,0,0,
};

void render(void);
void key(unsigned char key, int x, int y);
void resize(int width, int height);

static int dispToggle;

int main(int nargs, char *argv[])
{
    glutInit(&nargs, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(VGA_WIDTH, VGA_HEIGHT);
    glutCreateWindow("Test of graphics functions");

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    glutKeyboardFunc(key);
    glutMainLoop();

}

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(dispToggle) {
        displayMenu("Menu", 4, "Option 1", "Option 2", "Option 3", "Option 4");
    }
    else {
        displayBoard(boardYours,1);
        displayBoard(boardTheirs,0);
    }
    glutSwapBuffers();
}

void key(unsigned char key, int x, int y)
{
    if(key == 's') {
        dispToggle = (dispToggle) ? 0 : 1;
        render();
    }
    else if(key == 'q') {
        exit(0);
    }
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, VGA_WIDTH, VGA_HEIGHT, 0, -1, 1);
}

