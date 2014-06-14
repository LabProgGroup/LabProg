#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"

Ship *sh;
float eyex = 0, eyey = 1.5, eyez = 3;
GLfloat lightZeroColor[]  = {0.5, 0.5, 0.5, .5f};
GLfloat light_position[]  = {20, 30, -5, 1};

void display (void) {  
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);  /* Coordenadas do modelo */
    glLoadIdentity();
    gluLookAt(
        eyex, eyey, eyez,
        0, 0, 0,
        0, 1, 0);

                    
    /* as luzes mudam de lugar pois a matriz modelview muda. */
    /* LUZ 0 */
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);

    renderShip(sh);

    renderParedes();

    glutSwapBuffers(); 
} 

void renderParedes() {
    glColor4f(0.22, 0.22, 0.3, 0.3);
    /* Parede direita */
    GLfloat paredeColor[]  = {0.22, 0.22, 0.22};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, paredeColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  paredeColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  paredeColor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
    
    glBegin(GL_QUADS);
    {
        glNormal3f(-1, 1, 0);
        glVertex3f(10, 0, 0);
        glVertex3f(5, -5, 0);
        glVertex3f(5, -5, -1000);
        glVertex3f(10, 0, -1000);
    }
    glEnd();

    /* Parede esquerda */
    glBegin(GL_QUADS);
    {
        glNormal3f(1, 1, 0);
        glVertex3f(-10, 0, 0);
        glVertex3f(-5, -5, 0);
        glVertex3f(-5, -5, -1000);
        glVertex3f(-10, 0, -1000);
    }
    glEnd();

    /* Rio */
    GLfloat rioColor[]  = {0.43, 0.73, 0.9};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rioColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  rioColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  rioColor);
    glColor4f(0.43, 0.73, 0.9, 0.9);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 1, 0);
        glVertex3f(-5, -5, 0);
        glVertex3f(5, -5, 0);
        glVertex3f(5, -5, -1000);
        glVertex3f(-5, -5, -1000);
    }
    glEnd();
}

void reshape (int width, int height) { 
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
} 


Key readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    return keyPressed;
}

void timer(int node) {
  glutTimerFunc(50, timer ,1);
  glutPostRedisplay();
}

void tecl(unsigned char k, int x, int y)
{
    switch (k) {
        case 'w':
            eyey += 0.1;
            break;
        case 's':
            eyey -= 0.1;
            break;
    }
}

void sptecl(int k, int x, int y)
{
    switch (k) {
        case GLUT_KEY_UP:
            eyez += 0.1;
            break;
        case GLUT_KEY_DOWN:
            eyez -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            eyex -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            eyex += 0.1;
            break;
    }
}

int main(int argc, char * argv[]) {
    /* parte OpenGL */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200, 768);

    glutCreateWindow("EP-River Raid");
    
    sh = createShip(createPosition(0, 0, 0));

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glutReshapeFunc(reshape); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(tecl);
    glutSpecialFunc(sptecl);
    glutTimerFunc(50, timer, 1);

    glutMainLoop();

    return 0;
  }

