#include "hud.h"

void renderHud(Velocity velocity, int life, Dimension cenarySize) {
    renderSpeed(velocity, cenarySize);
    renderLife(life, cenarySize);
}

void renderSpeed(Velocity velocity, Dimension cenarySize) {
    int nSegments = 100;
    int i = 0;
    int size = WIN_WIDTH / 12;
    glPushMatrix();
    glTranslatef(size + 20, WIN_HEIGHT - 20,0);
    
    //ponteiro do velocimetro
    glLineWidth(3); 
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.0, 0.1);
    for (i = 0; i < 50; i++) {
        glVertex2f(10 * cos((i / 50.0) * 2 * M_PI), 10 * sin((i / 50.0) * 2 * M_PI));
    }
    glEnd();

    glColor3f(1.0, 0.0, .1);
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex2f(0.0, -0.5);
        glVertex2f(-0.9 * size * cos(velocity.z / MAX_VELOCITY * M_PI),
                   -0.9 * size * sin(velocity.z / MAX_VELOCITY * M_PI));
    glEnd();

    //borda do velocimetro
    glLineWidth(2);
    glColor3f(0.4, .0, 0.4);
    glBegin(GL_LINE_LOOP); 
    for (i = 0; i < nSegments; i++) 
    { 
        float theta = M_PI * i / nSegments;
        float x = -size * cos(theta);
        float y = -size * sin(theta);
        glVertex2f(x, y);
    } 
    glEnd(); 

    glPointSize(5);
    glBegin(GL_LINES);
    for (i = 0; i < 15; i++) {
        glVertex2f(-0.95 * size * cos((i / 15.0) * M_PI),
                   -0.95 * size * sin((i / 15.0) * M_PI));
        glVertex2f(-0.9 * size * cos((i / 15.0) * M_PI),
                   -0.9 * size * sin((i / 15.0) * M_PI));
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); 
    glColor3f(1.0, 0.5, 0.5);
    for (i = 0; i < nSegments; i++) 
    { 
        float theta = M_PI * i / nSegments;
        float x = -size * cos(theta);
        float y = -size * sin(theta);
        glVertex2f(x, y);
    } 
    glEnd(); 

    glPopMatrix();
}

void renderLife(int life, Dimension cenarySize) {
    //desenha a cruz
    int i;
    glPushMatrix();
    float size = WIN_WIDTH / 80;
    
    glTranslatef(WIN_WIDTH - (size + 20), WIN_HEIGHT - 30,0);

    //cruz
    glLineWidth(1);
    glColor3f(.2, 1, .2);
    glBegin(GL_LINE_LOOP); 
        glVertex2f(0, 0);
        glVertex2f(0, size/2);
        glVertex2f(size/2, size/2);
        glVertex2f(size/2, 0);
        glVertex2f(size, 0);
        glVertex2f(size, -size/2);
        glVertex2f(size/2, -size/2);
        glVertex2f(size/2, -size);
        glVertex2f(0, -size);
        glVertex2f(0, -size/2);
        glVertex2f(-size/2,-size/2);
        glVertex2f(-size/2, 0);
    glEnd();

    //barra da vida
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.8 * size/2, -1.5 * size);
        glVertex2f(-0.8 * size/2, -15 * size/2 * (life / 100.0));
        glVertex2f(0.8 * size, -15 * size/2 * (life / 100.0));
        glVertex2f(0.8 * size, - 1.5 * size);
    glEnd();

    //borda da vida
    glLineWidth(2);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.8 * size/2, -1.5 * size);
        glVertex2f(-0.8 * size/2, -15 * size/2);
        glVertex2f(0.8 * size, -15 * size/2);
        glVertex2f(0.8 * size, - 1.5 * size);
    glEnd();


    glPopMatrix();
}   