#include <stdio.h>
#include "cenario.h"
#include "enemyQueue.h"
#include "enemy.h"
#include "utils.h"
#include "ship.h"
#include "shotQueue.h"

Ship *sh;
Shot *shot;
ShotQueue *shipShotsQueue;
ShotQueue *enemyShotsQueue;
Velocity shotV = {0.7, 0.7, 50.};

/* chão */
static GLfloat floorVertices[4][3] = {
  {  10.0,  0.0, 1000.0 },		/* SE */
  { -10.0,  0.0, 1000.0 },		/* SD */
  { -10.0,  0.0,  -20.0 },		/* ID */
  {  10.0,  0.0,  -20.0 },		/* IE */
};

/* parede esq */
static GLfloat leftVertices[4][3] = {
  { -10.0,  0.0, 1000.0 },		/* SE */
  { -20.0, 10.0, 1000.0 },		/* SD */
  { -20.0, 10.0,  -20.0 },		/* ID */
  { -10.0,  0.0,  -20.0 },		/* IE */
};

/* parede dir */
static GLfloat rightVertices[4][3] = {
  {  10.0,  0.0,  1000.0 },
  {  20.0, 10.0,  1000.0 },
  {  20.0, 10.0,   -20.0 },
  {  10.0,  0.0,   -20.0 },
};

/* fundo */
#define S  500
#define LL 97
static GLfloat fundoVertices[4][3] = {
  {-S, -S, LL},
  { S, -S, LL},
  { S,  S, LL},
  {-S,  S, LL},
};


int mousePosition;
void display (void) {  
     GLfloat sup, inf, dir, esq;
    
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
    
    gluLookAt(
        0, 0, 7, //olho
        0, 0, 0, //o ponto que estou olhando
        0, 1, 0);
           
   sup = 1.00;
  inf = 0.27;
  esq = 0.00;
  dir = 1.00;
   
  glColor3f(.0, 1.0, 1.0);
    //glEnable(GL_TEXTURE_2D);
    
   /*Rendera o ship */
    renderShip(sh);
   /*Rendera os tiros*/
    if (!isShotQueueEmpty(shipShotsQueue)) {
        ShotNode *stNode = shipShotsQueue->head->next;
        while (stNode != shipShotsQueue->head) {
            updateShot(stNode->shot);
            renderShot(stNode->shot);
            stNode = stNode->next;
        }
    } 
   
   glutSwapBuffers(); // Flush the OpenGL buffers to the window  
} 

void reshape (int width, int height) {  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
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

static int
loadTexture(char *f)
{
  GLubyte *loc;

  char l[1024];					/* exagerada */
  int  larg,alt,prof;
  FILE *arq = fopen(f, "rb");
  if (arq == NULL) return 0;
  fgets(l,1024,arq);			/* por segurança */
  if (l[0] != 'P' || l[1] != '6') {
	fputs("Sem arquivo", stderr);
	fclose(arq);
	return 0;
  }
  /* pula os comentários */
  int c;
  while ((c = fgetc(arq)) == '#')
		 fgets(l,1024,arq);
  ungetc(c,arq);				/* oops, não era # */

  if (fscanf(arq, "%d %d %d\n", &larg, &alt, &prof) != 3) {
	fputs("Erro no formato\n", stderr);
    fclose(arq);
	return 0;
  }

  /* Setup RGB image for the texture. */
  loc = (GLubyte*) malloc(larg*alt*3);
  if (loc == NULL) {
	fputs("Sem arquivo", stderr);
	fclose(arq);
	return 0;
  }
  fread(loc, sizeof(GLubyte), larg*alt*3, arq);
  fclose(arq);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  				  GL_LINEAR_MIPMAP_LINEAR);
  
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, larg, alt,
  					GL_RGB, GL_UNSIGNED_BYTE, loc);

  printf("(%d x %d) %d\n",larg, alt,prof);
  return 1;
}


void readKey() {
    Key keyPressed;
    scanf("%d", &keyPressed);
    switch(keyPressed) {
    case(SPACE):
        shot = createShot(createPosition(sh->position.x, sh->position.y, sh->position.z), shotV, 10);
        enqueueShot(shot, shipShotsQueue);
        printf("llol");
        break;
    case UP: case DOWN: case RIGHT: case LEFT:
        updateVelocity(sh, keyPressed);
    
    default:
        sh->velocity.x = 0;
        sh->velocity.y = 0;
        sh->velocity.z = INITIAL_VELOCITY;
        break;    
    }
}

int main(int argc, char * argv[]) {
    /* parte OpenGL */
    shipShotsQueue = createShotQueue();
    enemyShotsQueue = createShotQueue();
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
   
    glViewport(0,0,1200, 760);
    
    glutCreateWindow("EP-River Raid");
    
    sh = createShip(createPosition(0., .0, 0.));
   
    glClearColor(1,1,1,1);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
     glutSpecialFunc(readKey); 
    glutMainLoop();
    
    
    return 0;
}

