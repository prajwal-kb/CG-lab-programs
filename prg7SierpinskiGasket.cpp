// design, develop and implement recursively subdivide a tetrahedron to from 3D
// sierpinski Gasket. The number of recursive steps is to be spiecified by the
// user.

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef float point[3];

point v[] = {{0, 0, 1}, {0, 1, 0}, {-1, -0.5, 0}, {1, -0.5, 0}};
int n;

void triangle(point a, point b, point c) {
  glBegin(GL_POLYGON);
  glVertex2fv(a);
  glVertex2fv(b);
  glVertex2fv(c);
  glEnd();
}

void divideTriangle(point a, point b, point c, int m) {
  point v1, v2, v3;
  int j;
  if (m > 0) {
    for (j = 0; j < 3; j++) {
      v1[j] = (a[j] + b[j]) / 2;
      v2[j] = (a[j] + c[j]) / 2;
      v3[j] = (c[j] + b[j]) / 2;
    }
    divideTriangle(a, v1, v2, m - 1);
    divideTriangle(c, v2, v3, m - 1);
    divideTriangle(b, v3, v1, m - 1);
  } else {
    triangle(a, b, c);
  }
}

void tetrahedron(int m) {
  glColor3f(1, 0, 0);
  divideTriangle(v[0], v[1], v[2], m);
  glColor3f(0, 1, 0);
  divideTriangle(v[3], v[2], v[1], m);
  glColor3f(0, 0, 1);
  divideTriangle(v[0], v[3], v[1], m);
  glColor3f(0, 0, 0);
  divideTriangle(v[0], v[2], v[3], m);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  tetrahedron(n);
  glFlush();
}

void myReshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w,
            -10, 10);
  else
    glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2,
            -10, 10);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

int main(int argv, char **argc) {
  printf("No of division:\n");
  scanf("%d", &n);
  glutInit(&argv, argc);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("3D Gasket");
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glEnable(GL_DEPTH_TEST);
  glClearColor(1, 1, 1, 0);
  glutMainLoop();
}
