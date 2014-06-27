#include "hud.h"

void renderHud(Velocity velocity, int life, Dimension cenarySize) {
    renderSpeed(velocity, cenarySize);
}

void renderSpeed(Velocity velocity, Dimension cenarySize) {
    //glPushMatrix();
    glTranslatef(100, WIN_HEIGHT - 20,0);
    glLineWidth(2); 
    glColor3f(0.2, 0.0, 0.4);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f( -80 * cos(velocity.z / MAX_VELOCITY * M_PI),
                    -80 * sin(velocity.z / MAX_VELOCITY * M_PI));
    glEnd();
    //glPopMatrix();
}

void renderLife(int life, Dimension cenarySize) {

}