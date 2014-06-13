#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"

Ship *sh;

void display (void) {  
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_MODELVIEW);  /* Coordenadas do modelo */
    glLoadIdentity();
    gluLookAt(
        0, 1, 2,
        0, 0, 0,
        0, 1, 0);

   renderShip(sh);

   glutSwapBuffers(); // Flush the OpenGL buffers to the window  
} 

void reshape (int width, int height) {  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
    gluPerspective(70, (GLfloat)width / (GLfloat)height, 1.0, 500.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
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

int main(int argc, char * argv[]) {
    /* parte OpenGL */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200, 768);
    // glViewport(0,0,1200, 760);
    glEnable(GL_DEPTH_TEST);      /* Uso de profundidade */
    glEnable(GL_BLEND);

    glutCreateWindow("EP-River Raid");
    
    sh = createShip(createPosition(0, 0, 0));

    glClearColor(1,1,1,1);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display); 
    glutTimerFunc(50, timer, 1);
    glutMainLoop();


    return 0;
  }

