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
   glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
   glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
   renderShip(sh);
   glutSwapBuffers(); // Flush the OpenGL buffers to the window  
} 

void reshape (int width, int height) {  
glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
  
}  

void printCenario(Cenario *cenario) {
    printf("\nCenario:\n\tDimensions: %f %f %f", cenario->dimension.x, cenario->dimension.y, cenario->dimension.z);
    printf("\n\tEnemies: %p\n", (void *)cenario->enemies);
}

void printEnemyQueue(EnemyQueue *queue) {
    EnemyNode *node = queue->head->next;
    
    printf("\nQueue:\n\tHead: %p %p %p", (void *)queue->head, (void *)queue->head->enemy, queue->head->next);
    printf("\n\tlastNode: %p", (void *)queue->lastNode);
    printf("\n\tfirst: %p last: %p", (void *)queue->first, (void *)queue->last);
    
    while (node != queue->head) {
        printf("\n\tNode: %p %p %p z: %f x: %f", (void *)node, (void *)node->enemy, (void *)node->next, node->enemy->position.z, node->enemy->position.x);
        node = node->next;
    }
    printf("\n");
}

void printPosition(Position position) {
    printf("\nPosition:\n\tx: %f\n\ty: %f\n\tz: %f\n", position.x, position.y, position.z);
}

void printVelocity(Position position) {
    printf("\nVelocity:\n\tx: %f\n\ty: %f\n\tz: %f\n", position.x, position.y, position.z);
}

void printEnemy(Enemy *enemy) {
    printf("\nEnemy:\n\t%p\n\tlife: %d\n\tprecision: %d", enemy, enemy->life, enemy->precision);
    printPosition(enemy->position);
}

void printScore(Ship *ship) {
    printf("\nScore: %.2f\n", traveledDistance);
}

void printShip(Ship *ship) {
    printf("\nShip:\n\tLife: %d", ship->life);
    printPosition(ship->position);
    printVelocity(ship->velocity);
    printScore(ship);
}

void printShot(Shot *shot) {
    printf("\nShot:\n\tdamage: %d", shot->damage);
    printPosition(shot->position);
    printVelocity(shot->velocity);
}

Key readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    return keyPressed;
}

int main(int argc, char * argv[]) {
    /* parte OpenGL */
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutReshapeFunc(reshape);
    glutInitWindowSize(1200, 768);
    glViewport(0,0,1200, 760);
    
    glutCreateWindow("EP-River Raid");
  
    
    sh = createShip(createPosition(0., .4, 10.));
    /*if (sh->position == NULL) {
      printf("blal");
      return 0;
    }*/
    glClearColor(1,1,1,1);
    glutDisplayFunc(display); 
    glutMainLoop();
    
    
    return 0;
}

