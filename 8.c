// Develop a menu driven program to animate a flag using Bezier Curve algorithm
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define pi 3.1416

static int win;
static float th = 0;
typedef float point[2];

point p1[] = {{2, 10}, {3, 11}, {5, 9}, {6, 10}};
float u[] = {0, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1};
point des[100];
float color1[3] = {0.5, 0.5, 0.5};
float color2[3] = {0.5, 0.5, 0.5};

void config(int w, int y) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 20.0, 0.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void curve() {
  for (int i = 0; i < 11; i++) {
    des[i][0] = (pow((1 - u[i]), 3) * p1[0][0]) +
                (3 * (u[i] * pow((1 - u[i]), 2) * p1[1][0])) +
                3 * pow(u[i], 2) * (1 - u[i]) * p1[2][0] +
                pow(u[i], 3) * p1[3][0];
    des[i][1] = (pow((1 - u[i]), 3) * p1[0][1]) +
                (3 * (u[i] * pow((1 - u[i]), 2) * p1[1][1])) +
                3 * pow(u[i], 2) * (1 - u[i]) * p1[2][1] +
                pow(u[i], 3) * p1[3][1];
  }

  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < 11; i++) {
    glVertex2fv(des[i]);
  }
  glEnd();
}
void render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(4.0);
  glPushMatrix();
  glColor3fv(color1);
  for (int i = 0; i < 20; i++) {
    glTranslatef(0, 0.05, 0.0);
    curve();
  }
  glColor3fv(color2);
  for (int i = 0; i < 20; i++) {
    glTranslatef(0, 0.05, 0.0);
    curve();
  }

  glPopMatrix();
  glPushMatrix();
  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  glVertex2f(1.5, 2);
  glVertex2f(2, 2);
  glVertex2f(2, 12.5);
  glVertex2f(1.5, 12.5);
  glEnd();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}
void animate() {

  p1[1][0] += 0.001 * sin(th * pi / 20);
  p1[1][1] += 0.0005 * sin(th * pi / 20);
  p1[2][0] -= 0.001 * sin((th)*pi / 30);
  p1[2][1] -= 0.0005 * sin((th)*pi / 30);
  p1[3][0] -= 0.001 * sin(th * pi / 20);
  p1[3][1] -= 0.0005 * sin((th)*pi / 20);

  th += 0.01;
  glutPostRedisplay();
}
void menu(int id) {
  if (id == 1) {
    color1[0] = 1;
    color1[1] = 0;
    color1[2] = 0;
    color2[0] = 0;
    color2[1] = 0;
    color2[2] = 1;
  }
  if (id == 2) {

    color1[0] = 1;
    color1[1] = 0;
    color1[2] = 0;
    color2[0] = 1;
    color2[1] = 1;
    color2[2] = 0;
  }
  if (id == 0) {
    glutDestroyWindow(win);
    exit(0);
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  win = glutCreateWindow("flag");
  glutDisplayFunc(render);
  glutReshapeFunc(config);
  glutIdleFunc(animate);
  glutCreateMenu(menu);
  glutAddMenuEntry("red, blue", 1);
  glutAddMenuEntry("red,yellow", 2);
  glutAddMenuEntry("Exit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
}
