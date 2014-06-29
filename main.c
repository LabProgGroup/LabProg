#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"
#include "hud.h"

#define SHOT_DAMAGE 10

Ship *sh;
Shot *shot;
ShotQueue* shipShotQ;
ShotQueue* enemyShotQ;
Cenario* cenario;
Position mouseP;

float eyex = 0, eyey = 10.5, eyez = 34;//24;

void display (void) {  
    glClearColor(0.99f, 0.5f, 0.99f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_NORMALIZE);

    renderShip(sh);
    renderCenario(cenario);
    renderShotQ(enemyShotQ);
    renderShotQ(shipShotQ);

    Velocity aimV = getAimV(mouseP.x, mouseP.y, sh, cenario->dimension.x, cenario->dimension.y);
    renderAim(sh, aimV, 5);

    /*2D part (HUD)*/
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
    renderHud(sh->velocity, sh->life, sh->focus, cenario->dimension);
    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); 
    /*End of 2D part*/

    glutSwapBuffers(); 
}

void timer(int n) {
    shipPosition = sh->position.z;

    updateShipPosition(sh);
    updateFocus(sh);
    insideKeeper(sh, cenario->dimension);
    refreshCenario(cenario, sh->position);    

    if (verifyShipColision(sh, cenario))
        sh->velocity.z /= 2;
    if (n == 0 && shouldShoot(sh->position, cenario->enemies->first->position))
        enqueueShot(shootFromEnemy(cenario->enemies->first, sh, 10), enemyShotQ);

    verifyEnemiesShotColision(cenario, shipShotQ);
    updateShotQueue(shipShotQ);
    updateShotQueue(enemyShotQ);
    rmFarShots(enemyShotQ, cenario);
    rmFarShots(shipShotQ, cenario);

    n = n + clockTick * 1000;
    if (n > 1000)
        n = 0;

    glutTimerFunc(clockTick * 1000, timer , n);
    glutPostRedisplay();
}

void reshape (int width, int height) { 
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLfloat)width / (GLfloat)height, 1.0, 8000.0);
    glMatrixMode(GL_MODELVIEW);
} 

void mouse(int b, int s, int x, int y)
{
    if (b == GLUT_LEFT_BUTTON && (s == GLUT_DOWN)) {
        Velocity aimV = getAimV(mouseP.x, mouseP.y, sh, cenario->dimension.x, cenario->dimension.y);
        Shot* shot = shootFromShip(sh, aimV, SHOT_DAMAGE);
        enqueueShot(shot, shipShotQ);
        return;
    }
}

void move(int x, int y) {
    mouseP.x = x;
    mouseP.y = y;
    mouseP.z = 0;
}

void tecl(unsigned char k, int x, int y) {
    updateVelocity(sh, k);
}

void teclUp(unsigned char k, int x, int y) {
    clearVelocity(sh, k);
}

int main(int argc, char * argv[]) {
    sh = createShip(createPosition(0, 0, 0), 1);
    shipShotQ = createShotQueue();
    enemyShotQ = createShotQueue();
    Dimension cenDim = {40, 20, 100000};
    cenario = createCenario(cenDim);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);

    glutCreateWindow("EP-River Raid");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eyex, eyey, eyez,
        0, 0, 0,
        0, 1, 0);
    GLfloat lightZeroColor[]  = {0.5, 0.5, 0.5, .5f};
    GLfloat lightPosition[]  = {0, 30, 10, 1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);

    
	
    
    glGenTextures(1, &idEnemy);
    glGenTextures(1, &idBackground);
    glGenTextures(1, &idShipBase);
    glGenTextures(1, &idShipCream);
     
    if (loadTexture("shipCream.ppm", idShipCream) == 0)
       fputs("Não carregou a textura da nave\n", stderr);
       
    if (loadTexture("shipBase.ppm", idShipBase) == 0) 
       fputs("Não carregou a textura da nave\n", stderr);
       
    if (loadTexture("night.pbm", idBackground) == 0)
       fputs("Não carregou a textura do fundo\n", stderr);
    
    if (loadTexture("cox.ppm", idEnemy) == 0)
        fputs("Não carregou a textura\n", stderr);
    
    
    glutSetCursor(GLUT_CURSOR_NONE); 
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutReshapeFunc(reshape); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(tecl);
    glutKeyboardUpFunc(teclUp);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(move);

    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
