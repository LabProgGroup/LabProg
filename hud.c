#include "hud.h"

void renderHud(Velocity velocity, int life, Dimension cenarySize) {
    renderSpeed(velocity, cenarySize);
}

void renderSpeed(Velocity velocity, Dimension cenarySize) {
    int nSegments = 50;
    int i = 0;
    glPushMatrix();
    glTranslatef(100, WIN_HEIGHT - 20,0);
    glLineWidth(5); 
    glColor3f(1.0, 0.0, 1.0);
    //ponteiro do velocimetro
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f( -80 * cos(velocity.z / MAX_VELOCITY * M_PI),
                    -80 * sin(velocity.z / MAX_VELOCITY * M_PI));
        glVertex2f(-1, -1);
    glEnd();

    glColor3f(0.0, 1.0, 1.0);
    
    glBegin(GL_LINE_LOOP); 

    for(i = 0; i < nSegments; i++) 
    { 
        float theta = 2.0f * 3.1415926f * i / nSegments;//get the current angle 
        float x = -80 * cos(theta);//calculate the x component 
        float y = -80 * sin(theta);//calculate the y component 
        glVertex2f(x, y);//output vertex 

    } 
    glEnd(); 

    glPopMatrix();
}

void renderLife(int life, Dimension cenarySize) {

}