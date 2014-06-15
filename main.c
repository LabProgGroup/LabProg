#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"

#define SHOT_DAMAGE 10

Ship *sh;
Shot *shot;
ShotQueue* shipShotQ;
ShotQueue* enemyShotQ;
//Velocity shotV = {0.7, 0.7, 50.};
float eyex = 0, eyey = 1.5, eyez = 3;
GLfloat lightZeroColor[]  = {0.5, 0.5, 0.5, .5f};
GLfloat light_position[]  = {20, 30, -5, 1};

void display (void) {  
    glClearColor(0.99f, 0.5f, 0.99f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);  /* Coordenadas do modelo */
    glLoadIdentity();
    gluLookAt(
        eyex, eyey, eyez,
        0, 0, 0,
        0, 1, 0);

    renderBackground();
                    
    /* as luzes mudam de lugar pois a matriz modelview muda. */
    /* LUZ 0 */
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);


    renderShip(sh);

    renderParedes();

    renderShotQ(shipShotQ);
    renderShotQ(enemyShotQ);


    glutSwapBuffers(); 
}

void reshape (int width, int height) { 
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
} 



void timer(int node) {
    updateShipPosition(sh);
    glutTimerFunc(clockTick * 1000, timer ,1);
    glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
    printf("xis: %d\n", x);
    printf("Y: %d\n", y);
    if (b == GLUT_RIGHT_BUTTON) {
        Position shotP;
        shotP.x = sh->position.x;
        shotP.y = sh->position.y;
        shotP.z = 0;

        int yShot = (WIN_HEIGHT - y) / 1.6; /*Talvez essa cte '1.6' mude para outros tamanhos*/
        Velocity shotV;
        shotV.x = (x != HALF_WIN_WIDTH) ? (x - HALF_WIN_WIDTH) / 10 : 0;
        shotV.y = (yShot != HALF_WIN_HEIGHT) ? (yShot - HALF_WIN_HEIGHT) / 10 : 0;
        shotV.z = 50.;
        shot = createShot(shotP, shotV, SHOT_DAMAGE);
        enqueueShot(shot, shipShotQ);
        printf("terminei! x = %d y = %d shtx = %f shty = %f \n", x, yShot, shotV.x, shotV.y);
        return;
    }
    if (b == GLUT_MIDDLE_BUTTON) {
        printf("Botado do meio pressionado!\n");
        return;
    }
    if (b == GLUT_LEFT_BUTTON) {
        printf("Botado esquerdo pressionado!\n");
        return;
    }
}

void move(int x, int y)
{
    /*printf("\nPosicao do mouse: %d %d", x, y);*/
    glutPostRedisplay();      /* força o redesenho */
}

Key readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    return keyPressed;
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
    shipShotQ = createShotQueue();
    enemyShotQ = createShotQueue();
    
    /* parte OpenGL */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);

    glutCreateWindow("EP-River Raid");
    sh = createShip(createPosition(0, 0, 0));
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    if (loadTexture("girl-jpg.ppm") == 0)
    fputs("Não carregou a textura\n", stderr);

    glutReshapeFunc(reshape); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(tecl);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(move);
    glutSpecialFunc(sptecl);
    glutTimerFunc(clockTick * 1000, timer, 1);

    glutMainLoop();

    return 0;
  }

