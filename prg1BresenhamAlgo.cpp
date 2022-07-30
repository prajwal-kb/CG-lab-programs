// Implement Bresenhem's line drawing Algorithm for all types of slope.

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLfloat X1, Y1, X2, Y2;
void Draw() {
  GLfloat M, P, dx, dy, x, y, t;
  glClear(GL_COLOR_BUFFER_BIT);

  if ((X2 - X1) == 0)
    M = (Y2 - Y1);
  else
    M = (Y2 - Y1) / (X2 - X1);

  if (fabs(M) < 1) {
    if (X1 > X2) {
      t = X1;
      X1 = X2;
      X2 = t;
      t = Y1;
      Y1 = Y2;
      Y2 = t;
    }
    dx = fabs(X2 - X1);
    dy = fabs(Y2 - Y1);
    P = 2 * dy - dx;
    x = X1;
    y = Y1;

    glBegin(GL_POINTS);
    while (x <= X2) {
      glVertex2f(x, y);
      x = x + 1;
      if (P >= 0) {
        if (M < 1)
          y = y + 1;
        else
          y = y - 1;
        P = P + 2 * dy - 2 * dx;
      } else {
        y = y;
        P = P + 2 * dy;
      }
    }
    glEnd();
  }
  if (fabs(M) >= 1) {
    if (Y1 > Y2) {
      t = X1;
      X1 = X2;
      X2 = t;
      t = Y1;
      Y1 = Y2;
      Y2 = t;
    }
    dx = fabs(X2 - X1);
    dy = fabs(Y2 - Y1);
    P = 2 * dx - dy;
    x = X1;
    y = Y1;

    glBegin(GL_POINTS);
    while (y <= Y2) {
      glVertex2f(x, y);
      y = y + 1;
      if (P >= 0) {
        if (M >= 1)
          x = x + 1;
        else
          x = x - 1;
        P = P + 2 * dx - 2 * dy;
      } else {
        x = x;
        P = P + 2 * dx;
      }
    }
    glEnd();
  }
  glFlush();
}

void MyInit() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 500, 0, 500);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
  printf("Enter the two points:");
  printf("\nEnter the values for X1,Y1 : ");
  scanf("%f %f", &X1, &Y1);
  printf("\nEnter the values for X2,Y2 : ");
  scanf("%f %f", &X2, &Y2);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Bresenhem's Line Drawing Algorithm");
  MyInit();
  glutDisplayFunc(Draw);
  glutMainLoop();
  return 0;
}
