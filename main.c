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
Cenario* cenario;
//Velocity shotV = {0.7, 0.7, 50.};
float eyex = 0, eyey = 8.5, eyez = 20;
float keyWalk = 1.0;
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

    /* as luzes mudam de lugar pois a matriz modelview muda. */
    /* LUZ 0 */
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);

    renderShip(sh);
    renderShotQ(enemyShotQ);
    renderCenario(cenario);
    renderShotQ(shipShotQ);

    glutSwapBuffers(); 
}

void reshape (int width, int height) { 
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLfloat)width / (GLfloat)height, 1.0, 5000.0);
    glMatrixMode(GL_MODELVIEW);
} 



void timer(int node) {
    updateShipPosition(sh);
    insideKeeper(sh, cenario->dimension);
    shipPosition = sh->position.z;
    refreshCenario(cenario, sh->position);
    if (verifyShipColision(sh, cenario))
        sh->velocity.z = 0;

    rmFarShots(sh->position.z, shipShotQ);
    glutTimerFunc(1, timer ,1);
    glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
    printf("xis: %d\n", x);
    printf("Y: %d\n", y);
    if (b == GLUT_RIGHT_BUTTON && (s == GLUT_DOWN)) {
        printf("Botado direito pressionado!\n");
        return;
    }
    if (b == GLUT_MIDDLE_BUTTON) {
        printf("Botado do meio pressionado!\n");
        return;
    } 
    if (b == GLUT_LEFT_BUTTON && (s == GLUT_DOWN)) {
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
        return;
    }
}

void move(int x, int y)
{
    /*printf("\nPosicao do mouse: %d %d", x, y);*/
    glutPostRedisplay();
}

Key readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    return keyPressed;
}

void tecl(unsigned char k, int x, int y)
{
    updateVelocity(sh, k);
    if (k == 'w')
        eyey += keyWalk;
    if (k == 's')
        eyey -= keyWalk;
}

void teclUp(unsigned char k, int x, int y) {
    clearVelocity(sh, k);
}

void sptecl(int k, int x, int y)
{
    switch (k) {
        case GLUT_KEY_UP:
            eyez += keyWalk;
            break;
        case GLUT_KEY_DOWN:
            eyez -= keyWalk;
            break;
        case GLUT_KEY_LEFT:
            eyex -= keyWalk;
            break;
        case GLUT_KEY_RIGHT:
            eyex += keyWalk;
            break;
    }
}

int main(int argc, char * argv[]) {
    shipShotQ = createShotQueue();
    enemyShotQ = createShotQueue();

    Dimension cenDim = {90, 50, 1000};
    cenario = createCenario(cenDim);

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

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutReshapeFunc(reshape); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(tecl);
    glutKeyboardUpFunc(teclUp);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(move);
    glutSpecialFunc(sptecl);
    glutTimerFunc(1, timer, 1);

    glutMainLoop();

    return 0;
}
