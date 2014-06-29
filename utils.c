#include "utils.h"

float clockTick = 1.0 / 50;
float shipPosition = 0;

Position spaceTimeEquation(Position initialPosition, Velocity v) {
    Position newPosition = {
        initialPosition.x + v.x * clockTick,
        initialPosition.y + v.y * clockTick - (GRAVITY * clockTick * clockTick) / 2,
        initialPosition.z + v.z * clockTick,
    };
    
    return newPosition;
}

Velocity speedTimeEquation(Velocity initialVelocity) { 
    Velocity newVelocity = {
        initialVelocity.x,
        initialVelocity.y - GRAVITY * clockTick, 
        initialVelocity.z, 
    };
    
    return newVelocity;
}

float distance(Position a, Position b) { 
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

Position createPosition(double x, double  y, double z) {
   Position p = {x, y, z};
   return p;
}

int loadTexture(char *f) {
    GLubyte *loc;

    char l[1024];                 /* exagerada */
    int  larg,alt,prof;
    FILE *arq = fopen(f, "rb");
    if (arq == NULL) return 0;
    fgets(l,1024,arq);            /* por segurança */
    if (l[0] != 'P' || l[1] != '6') {
        fputs("Sem arquivo", stderr);
        fclose(arq);
        return 0;
    }
    /* pula os comentários */
    int c;
    while ((c = fgetc(arq)) == '#')
        fgets(l,1024,arq);
    ungetc(c,arq);                /* oops, não era # */

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, larg, alt, GL_RGB, GL_UNSIGNED_BYTE, loc);

    printf("(%d x %d) %d\n",larg, alt,prof);
    return 1;
}
