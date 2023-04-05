#include <GL/glut.h>  
#include <math.h>
#define PI 3.1415927

//swing

GLfloat angle_s = 0.0; // Angle of rotation for the swing
GLfloat timeStep = 0.05; // Time step for the simulation
GLfloat time = 0.0; // Time elapsed since the simulation started

//Animation
GLfloat animYRot = 0.0;

GLfloat curtainY = 0.0;

GLfloat openY = 0.0;

GLfloat fanY = 0.0;

//variables to move the camera
GLfloat camX = 0.0;
GLfloat camY = 0.0;
GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceX = 0.0;
GLfloat sceY = 0.0;
GLfloat sceZ = 0.0;

//variables to move the snowman
GLfloat objX = 0.0;
GLfloat objY = 0.0;
GLfloat objZ = 0.0;

void init() {
    glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    //glShadeModel(GL_SMOOTH); // this is default, you may not set it
    glEnable(GL_NORMALIZE);

}


void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;

    glBegin(GL_LINES);



    const GLfloat orange1[4] = { 1.0, 0.0, 0.0, 1.0 };
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matwhite);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matwhite);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, orange1);
    //glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);

    for (line = -60; line <= 60; line += step) {
        glVertex3f(line, -0.4, 60);
        glVertex3f(line, -0.4, -60);

        glVertex3f(60, -0.4, line);
        glVertex3f(-60, -0.4, line);
    }
    glEnd();
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(3.5);

    glPushMatrix();



    const GLfloat red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, red);
    //glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);

    //glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);

    glPopMatrix();


    glPushMatrix();

    const GLfloat blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
    //glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);

    //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);

    glPopMatrix();

    glPushMatrix();

    const GLfloat green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glMaterialfv(GL_FRONT, GL_AMBIENT, green);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, green);
     //glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);

     //glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);

    glPopMatrix();



    glEnd();
}

void wall(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glBegin(GL_QUADS);

    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);

    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);

    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);

    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);

    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);

    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);


    glEnd();
    glPopMatrix();

}

void draw_tube(GLfloat radius, GLfloat height) {
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */

    glBegin(GL_TRIANGLE_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
}
void draw_cylinder(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */

    draw_tube(radius, height);

    /** Draw the circle on top of cylinder */

    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
    /** Draw the circle on bottom of cylinder */
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

}


void table() {
    glPushMatrix();
    glTranslatef(8.0, 4.0, 2.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(4, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 4.0, -2.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(4, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0, 4.0, 2.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(4, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0, 4.0, -2.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(4, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 8.0, 0.0);
    wall(10, 0.3, 3);
    glPopMatrix();

}

void tables() {
    glPushMatrix();
    for (int i = -15; i <= 30; i+= 10 ) {
    glPushMatrix();
    glTranslatef(10, 0, i);
    glScalef(0.75, 0.75, 0.75);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 0, i);
    glScalef(0.75, 0.75, 0.75);
    table();
    glPopMatrix();
    }
    glPopMatrix();

}

void chair() {
    glPushMatrix();
    glTranslatef(2.0, 3.0, 1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(6, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, 2.0, -1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(2, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 3.0, 1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(6, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 2.0, -1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(2, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 4.0, 0.0);
    wall(2.5, 0.2, 1.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 8.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    wall(2.5, 0.2, 1.6);
    glPopMatrix();
}

void chairs() {
    glPushMatrix();
    for (int i = 0; i <= 40; i += 10) {

        glPushMatrix();
        glTranslatef(10, 1, -10 + i);
        glScalef(0.5, 0.5, 0.5);
        chair();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(15, 1, -10 + i);
        glScalef(0.5, 0.5, 0.5);
        chair();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-10, 1, -10 + i);
        glScalef(0.5, 0.5, 0.5);
        chair();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-15, 1, -10 + i);
        glScalef(0.5, 0.5, 0.5);
        chair();
        glPopMatrix();
    
    }

    glPopMatrix();
}

void coupbord() {

    glPushMatrix();
    wall(5,0.2,5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10.0, 0 );
    wall(5, 0.2, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(5, 0.2, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5, 5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    wall(5, 0.2, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5, -5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    wall(5, 0.2, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.9, 4.9, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(4.9, 0.2, 4.9);
    glPopMatrix();
}


void coupbord_handle() {
    const GLfloat yellow2[4] = { 1.0f, 1.0f, 0.5f, 1.0f };
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);


        glPushMatrix();
        glTranslatef(-5.1, 5.0, 4.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        wall(2, 0.1, 0.2);
        glPopMatrix();
    glPopMatrix();

}

void fan_blades() {
    glPushMatrix();
    glTranslatef(4.0, 0.0, 0.0);
    wall(4, 0.2, 1);
    glPopMatrix();

}

void fan() {

    glPushMatrix();
    glTranslatef(0.0, 5.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    draw_cylinder(0.2, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 4.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    draw_cylinder(1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 3.75, 0.0);
    GLfloat i = 0.0;
    for (i = 0; i <= 360; i += 72.0) {
        glPushMatrix();
        glRotatef(i + animYRot, 0.0, 1.0, 0.0);
        fan_blades();
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

void door() {
    glPushMatrix();
    glRotatef(openY, 0.0, 1.0, 0.0);
    glTranslatef(8.0, 12, 0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    wall(8, 1, 12);
    glPopMatrix();
}


void base() {
    glPushMatrix();
    glTranslatef(30, 15, 40.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 15, 40.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 15, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 15, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 15, -40.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 15, -40.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(15, 2.5, 2.5);
    glPopMatrix();
}

void cuirtain_strip() {
    glPushMatrix();
    glTranslatef(0, -12.5, 0.0);
    glRotatef(curtainY, 0.0, 1.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    wall(12.5, 1.0, 0.1);
    glPopMatrix();
}
void curtain() {
    glPushMatrix();
    glTranslatef(0, 0.5, 0.0);
    draw_cylinder(0.2, 30);
    glPopMatrix();

    glPushMatrix();

    GLfloat j = 0.0;
    for (j; j <= 30; j += 2.3) {

        glPushMatrix();
        glTranslatef(0, 0.0, j);
        draw_tube(0.3, 0.2);
        cuirtain_strip();
        glPopMatrix();
    }

    glPopMatrix();
}

void window() {
    //vertical bars
    glPushMatrix();
    glTranslatef(0, 0, 15.0);
    wall(10, 1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -15.0);
    wall(10, 1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5, 0, -5.0);
    wall(7, 1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5, 0, 5.0);
    wall(7, 1.5, 0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-2.5, 0, 10.0);
    glPopMatrix();

    //Horizontal bar
    glPushMatrix();
    glTranslatef(-10.0, 0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wall(15, 1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0, 0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wall(15, 1.5, 0.5);
    glPopMatrix();


    //walls of left wall
    glPushMatrix();
    glTranslatef(5.0, 0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wall(14, 1.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0, 17.5);
    wall(15, 1, 2.50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0, -17.5);
    wall(15, 1, 2.50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12.5, 0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wall(15, 1, 2.50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5, 0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wall(15, 1, 2.50);
    glPopMatrix();


}

void floor() {
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    const GLfloat grey3[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glPushMatrix();
    for (int i = -35; i <=40;i+=20) {

        for (int j = -25; j <= 30;j+=20) {
                glPushMatrix();
                glTranslatef(j, 1, i);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
                glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
                glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
                wall(5, 1, 5);
                glPopMatrix();
        }

    }
    glPopMatrix();

    glPushMatrix();
    for (int i = -25; i <= 40; i += 20) {

        for (int j = -25; j <= 30; j += 20) {
            glPushMatrix();

            glTranslatef(j, 1, i);        
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey3);
            glMaterialfv(GL_FRONT, GL_AMBIENT, grey3);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
            wall(5, 1, 5);
            glPopMatrix();
        }

    }
    glPopMatrix();


    //
    glPushMatrix();
    for (int i = -25; i <= 40; i += 20) {

        for (int j = -15; j <= 30; j += 20) {

            glPushMatrix();
            glTranslatef(j, 1, i);            
            glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
            glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
            wall(5, 1, 5);
            glPopMatrix();
        }

    }
    glPopMatrix();

    glPushMatrix();
    for (int i = -35; i <= 40; i += 20) {

        for (int j = -15; j <= 30; j += 20) {
            glPushMatrix();
            glTranslatef(j, 1, i);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey3);
            glMaterialfv(GL_FRONT, GL_AMBIENT, grey3);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

            wall(5, 1, 5);
            glPopMatrix();
        }
    }
    glPopMatrix();

}

void cilin() {

    const GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    const GLfloat grey2[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat grey3[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glPushMatrix();
    glTranslatef(0,-1,38);
    wall(30,0.5,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, -38);
    wall(30, 0.5, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28, -1, 0);
    glRotatef(90.0,0,1,0);
    wall(38, 0.5, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-28, -1, 0);
    glRotatef(90.0, 0, 1, 0);
    wall(38, 0.5, 2);
    glPopMatrix();

    glPushMatrix();
    for (int i = -35; i <= 40; i += 20) {

        for (int j = -25; j <= 30; j += 20) {
            glPushMatrix();
            glTranslatef(j, 0, i);
               glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
            glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
            wall(5, 0.5, 5);
            glPopMatrix();

        }

    }
    glPopMatrix();

    glPushMatrix();
    for (int i = -35; i <= 40; i += 20) {

        for (int j = -15; j <= 30; j += 20) {
            glPushMatrix();
            glTranslatef(j, 0, i);


            glMaterialfv(GL_FRONT, GL_DIFFUSE, grey2);
            glMaterialfv(GL_FRONT, GL_AMBIENT, grey2);
            glMaterialfv(GL_FRONT, GL_SPECULAR,matwhite);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
            wall(5, 0.5, 5);
            glPopMatrix();
        }

    }
    glPopMatrix();


    glPushMatrix();
    for (int i = -25; i <= 40; i += 20) {
        glPushMatrix();
        glTranslatef(0, 0, i);

   
        glMaterialfv(GL_FRONT, GL_DIFFUSE, grey3);
        glMaterialfv(GL_FRONT, GL_AMBIENT, grey3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
        wall(30, 0.5, 5);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -1, i);

        glMaterialfv(GL_FRONT, GL_DIFFUSE, matwhite);
        glMaterialfv(GL_FRONT, GL_AMBIENT, matwhite);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
        wall(3, 0.5, 3);
        glPopMatrix();



    }
    glPopMatrix();

}

void roof() {
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(0,10,-35);
    glVertex3f(0, 10, 35);
    glVertex3f(40,0,50);
    glVertex3f(40, 0,-50);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 10, -35);
    glVertex3f(0, 10, 35);
    glVertex3f(-40, 0, 50);
    glVertex3f(-40, 0, -50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(40, 0, 50);
    glVertex3f(-40, 0, 50);
    glVertex3f(0, 10, 35);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(40, 0, -50);
    glVertex3f(-40, 0, -50);
    glVertex3f(0, 10, -35);
    glEnd();


    glPopMatrix();
}

void swing() {
    glPushMatrix();
    glRotatef(angle_s, 1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(5, -15, 0);
        //glRotatef(angle_s, 0.0, 0.0, 1.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        wall(15, 1, 1);//right wall
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5, -15, 0);
        //glRotatef(angle_s, 0.0, 0.0, 1.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        wall(15, 1, 1);//right wall
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -30, 0);
        //glRotatef(angle_s, 0.0, 0.0, 1.0);
        //glRotatef(90.0, 0.0, 0.0, 1.0);
        wall(5, 1, 2);//right wall
        glPopMatrix();
    glPopMatrix();
}

void classroom() {
    const GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    const GLfloat yellow[4] = { 1.0f, 1.0f, 0.75f, 1.0f };
    const GLfloat yellow1[4] = { 0.7f, 0.7f, 0.6f, 1.0f };
    const GLfloat brown[4] = { 0.7f, 0.075f, 0.0f, 1.0f };
    const GLfloat brown2[4] = { 0.3f, 0.075f, 0.0f, 1.0f };
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };


    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
    glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glTranslatef(0, -1, 0);
    wall(40, 1, 50);//pawment
    glPopMatrix();


    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
        glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

        glPushMatrix();
        glTranslatef(30, 15, 0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        wall(15, 1, 40);//right wall
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0, 15, -40);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        wall(30, 1, 15);//back wall
        glPopMatrix();


        //front wall
        glPushMatrix();
        glTranslatef(19, 15, 40);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        wall(11, 1, 15);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-19, 15, 40);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        wall(11, 1, 15);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, 27, 40.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        wall(8, 1, 3);
        glPopMatrix();



        //left wall
        glPushMatrix();
        glTranslatef(-30.0, 15, 20.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        window();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-30.0, 15, -20.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        window();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 30, 0);
        cilin();//cilin
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, 0);
        floor();//floor
        glPopMatrix();


   glPopMatrix();

   //ground
   glPushMatrix();
   glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
   glMaterialfv(GL_FRONT, GL_AMBIENT, green);
   glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
   glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
   glTranslatef(0, -2, 0);
   wall(150,1,100);
   glPopMatrix();

   //coupbord
   glPushMatrix();
       for (int i = 10; i <= 30;i+=10) {
       glPushMatrix();
       glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow1);
       glMaterialfv(GL_FRONT, GL_AMBIENT, yellow1);
       glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
       glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
       glTranslatef(25, 0, i);
       coupbord();
       coupbord_handle();
       
       glPopMatrix();

       }


   glPopMatrix();

   glPushMatrix();
 
       glPushMatrix();
       glMaterialfv(GL_FRONT, GL_DIFFUSE, brown2);
       glMaterialfv(GL_FRONT, GL_AMBIENT, brown2);
       glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
       glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
       glTranslatef(25, 0, -25);
       coupbord();
       coupbord_handle();
        glPopMatrix();

       glPushMatrix();
       glMaterialfv(GL_FRONT, GL_DIFFUSE, brown2);
       glMaterialfv(GL_FRONT, GL_AMBIENT, brown2);
       glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
       glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
       glTranslatef(25, 10, -25);
       coupbord();
       coupbord_handle();
       glPopMatrix();

   glPopMatrix();

   glPushMatrix();
   glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow1);
   glMaterialfv(GL_FRONT, GL_AMBIENT, yellow1);
   glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
   glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
   glTranslatef(-20, 0, -25);
   glRotatef(180.0,0.0,1.0,0.0);
   coupbord();
   coupbord_handle();
   glPopMatrix();

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
        glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

        //curtains
        glPushMatrix();
        glTranslatef(-26.0, 25, -35.0);
        curtain();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-26.0, 25, 5.0);
        curtain();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glTranslatef(0.0, 16, -36.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    wall(16, 1, 8);//blakboard
    glPopMatrix();


    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    base();

    glPushMatrix();
   
        glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
        glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
        glPushMatrix();
        glTranslatef(-8, 0, 40);
        door();

        glPopMatrix();
        //teacher table
        glPushMatrix();
        glTranslatef(0, 3, -25);
        table();
        glPopMatrix();
        //teacher chair
        glPushMatrix();
        
        glTranslatef(0, 3, -32);
        glRotatef(180.0, 0.0, 1.0, 0.0);
        glScalef(1.5, 1.5, 1.5);
        chair();

        glPopMatrix();


        //roof
        glPushMatrix();
        glTranslatef(0, 28.2, 0);
        roof();//roof
        glPopMatrix();


    glPopMatrix();

    //door
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glPushMatrix();
    glTranslatef(-8, 0, 40);
    door();

    glPopMatrix();


    //students table
    glPushMatrix();
    glTranslatef(0, 3, 0);
    tables();
    glPopMatrix();

    //student chairs
    glPushMatrix();
    glTranslatef(0,3,0);
    chairs();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
    glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glPushMatrix();
    glTranslatef(0, 23, -20);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 23, 0);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 23, 20);
    fan();
    glPopMatrix();
    glPopMatrix();


}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* positioned the light source */
    

    //glEnable(GL_LIGHT0);
    GLfloat position1[] = { 0.0,28.0,-38.0,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position1);

   glEnable(GL_LIGHT2);
    GLfloat position3[] = { 0.0,200.0,100.0,0.1 };
    glLightfv(GL_LIGHT2, GL_POSITION, position3);

    // set light intensities 
    GLfloat paleYellow[] = { 1.0,1.0,0.75,0.0 };
    GLfloat black[] = { 0.0,0.0,0.0,0.0 };
    GLfloat white[] = { 1.0,1.0,1.0,0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, paleYellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT2, GL_AMBIENT, black);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, paleYellow);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);

    glPushMatrix();
    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0 + camX, 15.0 + camY, 100.0 + camZ, 0.0, 10.0, -50.0, 0.0, 9.0, 0.0);

    glRotatef(sceY, 0.0, 1.0, 0.0);
    glTranslatef(sceX, 0, 0);
    //Draw a grid on the xz plane
    //glColor3f(1, 1, 1);
    //drawGrid();
    //draw the three axes
    //drawAxes();

    classroom();
    //window();
    //curtain();
    //table();
    //coupbord();
    //cilin();
   

    glPopMatrix();



    glutSwapBuffers();

}

//Animation timer function
void timer(int x) {
    if (animYRot == 360.0)
        animYRot = 0.0;
    else
        animYRot += 2.0;
  
/*
    angle_s = 45.0 * sin(time); // Update the angle using a sine function
    time += timeStep; // Increment the time by the time step

*/

    glutPostRedisplay();
    glutTimerFunc(60.0, timer, 1);
}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 1;

    if (key == GLUT_KEY_DOWN)
        camY -= 1;

    if (key == GLUT_KEY_RIGHT)
        sceY += 1;

    if (key == GLUT_KEY_LEFT)
        sceY -= 1;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    //glEnable(GL_LIGHT1);
    GLfloat position1[] = { 0.0,23.0,0.0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, position1);



    GLfloat paleYellow[] = { 1.0,1.0,0.75,0.50 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, paleYellow);
    GLfloat white[] = { 1.0,1.0,1.0,0.5 };
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);


      if (key == '@')//light on
          glEnable(GL_LIGHT1); 
          

      if (key == '#')// light off
          glDisable(GL_LIGHT1);


    if (key == 'A')
        camZ += 1;

    if (key == 'a')// cam move z axis
        camZ -= 1;

    if (key == 'B')
        camY += 1;

    if (key == 'b')// object move z asis
        camY -= 1;

    if (key == 'D')
        camX += 1;

    if (key == 'd')// Scen move x asis
        camX -= 1;

    if (openY <= 160.0)
        if (key == 'o')
            openY += 15.0;//open
    if (openY > 0.0)
        if (key == 'O')
            openY -= 15.0;//close

    if (curtainY <= 0.0)
        if (key == 'c')
            curtainY = 90.0;//open
    if (curtainY >= 90.0)
        if (key == 'C')
            curtainY = 0.0;//close

    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum 
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 150.0);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, timer, 1);
    init();
    glutMainLoop();


    return 0;
}