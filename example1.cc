#include "GL/glut.h"
#include "GL/glu.h"
#include <glm/glm.hpp>
double x=1, g_orientation = 45.0, l_orientation = 0.0, g_posX = 0, g_posY = 0, g_posZ = 0;
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
    gluPerspective(120,1.0f,1.0f,100.0f);
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
    

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(g_orientation, 0, 1.0, 0.0);
    glRotatef(l_orientation, 1.0, 0, 0.0);
    glTranslatef(-g_posX, -g_posY, -g_posZ);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawGrid();
    theCube();//make cursor
    
    //glRotatef(45,20,20,0);//get angled perspective 
    //glLoadIdentity();
    //glTranslatef(-1,0,-1.0);

    
   
    
    glutSwapBuffers();
    glScalef(x, x, x);
}
void keyBoard(unsigned char key, int x, int y)
{
switch (key) {
case 'q': // up
g_posY = g_posY + 1.0;
break;
case 'e': // down
g_posY = g_posY - 1.0;
break;
case 'a': // up
g_posX = g_posX + 1.0;
break;
case 'd': // down
g_posX = g_posX - 1.0;
break;
case 'w': // up
g_posZ = g_posZ + 1.0;
break;
case 's': // down
g_posZ = g_posZ - 1.0;
break;
case 'z': // left
g_orientation = g_orientation - 15.0;
break;
case 'x': // right
g_orientation = g_orientation + 15.0;
break;
case 'c': // down
l_orientation = l_orientation - 15.0;
break;
case 'n': // up
l_orientation = l_orientation + 15.0;
break;
case '+': // forwards
x = x+0.1; 
//g_posX = g_posX + sin(g_orientation / 180.0 * M_PI);
//g_posZ = g_posZ - cos(g_orientation / 180.0 * M_PI);
break;
case '-': // backwards
x = x-0.1;
//g_posX = g_posX - sin(g_orientation / 180.0 * M_PI);
//g_posZ = g_posZ + cos(g_orientation / 180.0 * M_PI);
break;

}
glutPostRedisplay();
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
 



int main(int argc, char *argv[])
{
    
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(800,600);
glutCreateWindow("Triangle");

glutDisplayFunc(&display);
glutKeyboardFunc(&keyBoard);//(unsigned char key, int x, int y)
glutMainLoop();
return 0;
}
