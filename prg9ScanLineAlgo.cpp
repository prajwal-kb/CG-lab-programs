#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float X1, Y1, X2, Y2, X3, Y3, X4, Y4;
int fillFlag = 0, win;
int re[500], le[500];

void edgedetect(float X1, float Y1, float X2, float Y2, int *le, int *re) {
  float M, temp;
  int i;

  if ((Y2 - Y1) < 0) {
    temp = Y1;
    Y1 = Y2;
    Y2 = temp;

    temp = X1;
    X1 = X2;
    X2 = temp;
  }

  if ((Y2 - Y1) != 0)
    M = (X2 - X1) / (Y2 - Y1);
  else
    M = X2 - X1;

  float X = X1;

  for (i = Y1; i <= Y2; i++) {
    if (X < le[i])
      le[i] = X;
    if (X > re[i])
      re[i] = X;

    X += M;
  }
}

void draw_pixel(int x, int y) {
  glColor3f(1.0, 1.0, 0.0);

  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void scanfill(float X1, float Y1, float X2, float Y2, float X3, float Y3,
              float X4, float Y4) {
  int i, Y;

  for (i = 0; i < 500; i++) {
    le[i] = 500;
    re[i] = 0;
  }

  edgedetect(X1, Y1, X2, Y2, le, re);
  edgedetect(X2, Y2, X3, Y3, le, re);
  edgedetect(X3, Y3, X4, Y4, le, re);
  edgedetect(X4, Y4, X1, Y1, le, re);

  for (Y = 0; Y < 500; Y++)
    for (i = le[Y]; i < re[Y]; i++)
      draw_pixel(i, Y);
}

void display() {

  X1 = 200.0, Y1 = 200.0, X2 = 100.0, Y2 = 300.0, X3 = 200.0, Y3 = 400.0,
  X4 = 300.0, Y4 = 300.0;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);

  glBegin(GL_LINE_LOOP);
  glVertex2f(X1, Y1);
  glVertex2f(X2, Y2);
  glVertex2f(X3, Y3);
  glVertex2f(X4, Y4);
  glEnd();

  if (fillFlag == 1)
    scanfill(X1, Y1, X2, Y2, X3, Y3, X4, Y4);

  glFlush();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void fillMenu(int option) {
  if (option == 1)
    fillFlag = 1;
  else if (option == 2)
    fillFlag = 2;
  else {
    glutDestroyWindow(win);
    exit(0);
  }

  display();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  win = glutCreateWindow("Scan LIne Algorithm");
  init();
  glutDisplayFunc(display);
  glutCreateMenu(fillMenu);
  glutAddMenuEntry("Fill Polygon", 1);
  glutAddMenuEntry("Empty Polygon", 2);
  glutAddMenuEntry("Exit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
}
