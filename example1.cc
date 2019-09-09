#include "GL/glut.h"
#include "GL/glu.h"
#include <glm/glm.hpp>

struct matrix{
    double x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4,q1,q2,q3,q4;
};

struct triangle{
    double x1,x2,x3,y1,y2,y3,z1,z2,z3;
};
void update()
{
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_TRIANGLES);
glColor3f(1.0, 0.5, 0.0); // red
glVertex3f(-0.017452, 0.0, 0.0); // vertex to the left
glVertex3f(0.017452, 0.0, 0.0); // vertex to the right
glVertex3f(0.0, 0.999847, 0.0); // vertex to the top
glEnd();
glFlush();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35,1.0f,0.0f,1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1,0.1,0.1,1);
}
void makeRingSegment(glm::mat4 a){
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_TRIANGLES);
glVertex3f(a[0][0], a[0][1], a[0][2]); // vertex to the left
glVertex3f(a[1][0], a[1][1], a[1][2]); // vertex to the right
glVertex3f(a[2][0], a[2][1], a[2][2]); // vertex to the top
//glVertex3f(a[0][3], a[1][3], a[2][3]);
glEnd();
glFlush();
}

void maketriangle(triangle i)
{
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_TRIANGLES);
glColor3f(1.0, 0.5, 0.0); // red
glVertex3f(i.x1, i.y1, i.z1); // vertex to the left
glVertex3f(i.x2, i.y2, i.z2); // vertex to the right
glVertex3f(i.x3, i.y3, i.z3); // vertex to the top
glEnd();
glFlush();
}

void theCube(){
    glColor3f(1,1,1);
    glutSolidCube(0.4);
}

void drawGrid(){
    for(int i = 0; i < 40; i++){
        glPushMatrix();
        if(i<20){glTranslatef(0,0,i);}
        if(i>=20){glTranslatef(i-20,0,0); glRotatef(-90,0,1,0);}
        glBegin(GL_LINES);
        glColor3f(1,1,1); glLineWidth(1);
        glVertex3f(0,-0.1,0);glVertex3f(19,-0.1,0);
        glEnd();
        glPopMatrix();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
   glTranslatef(-13,0,10);

    glRotatef(40,1,1,0);//get angled perspective 
   
    drawGrid();
    theCube();//make cursor
    glutSwapBuffers();
    
}

void ring()
{
    triangle i;
        i.x1 = -0.3, i.y1 = -1.0, i.z1 = 0.0,
    i.x2 = 0.3, i.y2 = -1.0, i.z2 = 0.0,
    i.x3 = 0.0, i.y3 = -0.5, i.z3 = 0.0;
    glm::mat4 seg = glm::mat4(
    //                x   y   z
        glm::vec4(  -0.2 ,0.0 ,0.0 ,0.0),
        glm::vec4(  0.2  ,0.0 ,0.0 ,0.0),
        glm::vec4(  0.0  ,0.1 ,0.0 ,0.0),
        glm::vec4(  0.0  ,0.0 ,0.0 ,0.0)
    );
    glm::mat4 rotateZ = glm::mat4(
    //                x   y   z
        glm::vec4(  cos(1*M_PI) ,sin(1*M_PI) ,0.0 ,0.0),
        glm::vec4(  -sin(1*M_PI) ,cos(1*M_PI) ,0.0 ,0.0),
        glm::vec4(  0.0  ,0.0 ,1.0 ,0.0),
        glm::vec4(  0.0  ,0.0 ,0.0 ,1.0)
    );
    
    makeRingSegment(rotateZ*seg);
}
 
    /*c.x1 = a.x1*b.x1+ a.x2*b.y1 + a.x3*b.z1 + a.x4*b.q1,
    c.x2 = a.x1*b.x2+ a.x2*b.y2 + a.x3*b.z2 + a.x4*b.q2,
    c.x3 =a.x1*b.x3+ a.x2*b.y3 + a.x3*b.z3 + a.x4*b.q3,
    c.x4 = a.x1*b.x4+ a.x2*b.y4 + a.x3*b.z4 + a.x4*b.q4,
    c.y1 = a.y1*b.x1+ a.y2*b.y1 + a.y3*b.z1 + a.y4*b.q1,
    c.y2 = a.y1*b.x2+ a.y2*b.y2 + a.y3*b.z2 + a.y4*b.q2,
    c.y3 = a.y1*b.x3+ a.y2*b.y3 + a.y3*b.z3 + a.y4*b.q3,
    c.y4 = a.y1*b.x4+ a.y2*b.y4 + a.y3*b.z4 + a.y4*b.q4,
    c.z1 = a.z1*b.x1+ a.z2*b.y1 + a.z3*b.z1 + a.z4*b.q1,
    c.z2 = a.z1*b.x2+ a.z2*b.y2 + a.z3*b.z2 + a.z4*b.q2,
    c.z3 = a.z1*b.x3+ a.z2*b.y3 + a.z3*b.z3 + a.z4*b.q3,
    c.z4 = a.z1*b.x4+ a.z2*b.y4 + a.z3*b.z4 + a.z4*b.q4,
    c.q1 = a.q1*b.x1+ a.q2*b.y1 + a.q3*b.z1 + a.q4*b.q1,
    c.q2 = a.q1*b.x2+ a.q2*b.y2 + a.q3*b.z2 + a.q4*b.q2,
    c.q3 = a.q1*b.x3+ a.q2*b.y3 + a.q3*b.z3 + a.q4*b.q3,
    c.q4 = a.q1*b.x4+ a.q2*b.y4 + a.q3*b.z4 + a.q4*b.q4;*/




int main(int argc, char *argv[])
{
    
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(800,600);
glutCreateWindow("Triangle");
glutDisplayFunc(&display);
glutMainLoop();
return 0;
}