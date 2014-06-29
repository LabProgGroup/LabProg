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

float eyex = 0, eyey = 6.5, eyez = 24;
float keyWalk = 1.0;

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
    GLfloat lightZeroColor[]  = {0.5, 0.5, 0.5, .5f};
    GLfloat light_position[]  = {20, 30, -5, 1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);

    renderShip(sh);
    renderCenario(cenario);
    renderShotQ(enemyShotQ);
    renderShotQ(shipShotQ);
    //glClear(GL_DEPTH_BUFFER_BIT);
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
    updateShipPosition(sh);
    updateFocus(sh);
    insideKeeper(sh, cenario->dimension);
    shipPosition = sh->position.z;
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
    if (b == GLUT_RIGHT_BUTTON && (s == GLUT_DOWN)) {
        printf("Botado direito pressionado!\n");
        return;
    }
    if (b == GLUT_MIDDLE_BUTTON) {
        printf("Botado do meio pressionado!\n");
        return;
    } 
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
    if (k == 'u')
        eyey += keyWalk;
    if (k == 'j')
        eyey -= keyWalk;
}

void teclUp(unsigned char k, int x, int y) {
    clearVelocity(sh, k);
}

void sptecl(int k, int x, int y) {
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
    sh = createShip(createPosition(0, 0, 0));
    shipShotQ = createShotQueue();
    enemyShotQ = createShotQueue();
    Dimension cenDim = {90, 50, 1000000};
    cenario = createCenario(cenDim);

    /* parte OpenGL */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);

    glutCreateWindow("EP-River Raid");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    if (loadTexture("night.pbm") == 0)
        fputs("Não carregou a textura\n", stderr);
    glutSetCursor(GLUT_CURSOR_NONE); 
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutReshapeFunc(reshape); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(tecl);
    glutKeyboardUpFunc(teclUp);
    glutMouseFunc(mouse);
    glutSpecialFunc(sptecl);
    glutPassiveMotionFunc(move);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
