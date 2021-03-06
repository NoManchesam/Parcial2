
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#include "3D_bib.h"
#include "Ship.h"
#include <stack>
#include <unistd.h>
#include <time.h>
//unsigned int sleep(unsigned int seconds);


//Declaracion de variables
int change=10;

//Variables dimensiones de la pantalla
int WIDTH=500;
int HEIGTH=500;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=100.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=10.0;
float EYE_Y=5.0;
float EYE_Z=10.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Variables para dibujar los ejes del sistema
float X_MIN=-20;
float X_MAX=20;
float Y_MIN=-20;
float Y_MAX=20;
float Z_MIN=-100;
float Z_MAX=20;

//Se declara el objeto para utilizar las operaciones 3D
Operaciones3D Op3D;
float Theta  = 0;
float ThetaX = 0;
float ThetaY = 0;
float ThetaZ = 0;
//Matriz e0;
Ship myShip(&Op3D);
Ship myShip2(&Op3D);
Ship myShip3(&Op3D);

float p2[3]={0.0,5.0,0.0};
//Carro micarro(&Op3D);
//Chofer michofer(&Op3D);
//Llantas llanta1(&Op3D); llanta2(&Op3D);


//funciones de control generales


void dibujaEsc(){
    //myShip2.setAnimation(false);
    Op3D.push();
    //Op3D.RotacionParalela('Y',10,0,0);
    //Escala Start
    //Op3D.scale(0.5,0.5,0.5);
    //Op3D.MultM(Op3D.E, Op3D.A, Op3D.A);
    //Escala End
    myShip.draw();
    //Traslate Start
    if(myShip2.edo_translate){
        Op3D.translate(-5,1,-3);
        Op3D.MultM(Op3D.T, Op3D.A, Op3D.A);
    }
    myShip2.setTranslation(false);
    //Traslate End

    //Op3D.imprimeMatriz(Op3D.A); //Comprobar valores de Matriz A
    Op3D.push();
    if(myShip2.edo_rotate){
        myShip2.setDeltaAxisRotation(p2);
        myShip2.RotacionLibre();
    }
    myShip2.setRotation(false);
    myShip2.draw();


    Op3D.pop();

    if(myShip3.edo_translate){
        Op3D.translate(-2,0,-2);
        Op3D.MultM(Op3D.T, Op3D.A, Op3D.A);
    }
    myShip3.setTranslation(false);

    Op3D.push();
    if(myShip3.edo_rotate){
        myShip3.setDeltaAxisRotation(p2);
        myShip3.RotacionLibre();
    }
    myShip2.setRotation(false);
    myShip3.draw();
    Op3D.pop();
    //myShip2.
    //Op3D.push(); //Carro push
    //Op3D.translate(2,3,1);

    //ship.draw(); //Conductor

    //Op3D.pop(); //Carro pop

    //Dibujar llanta
    //Op3D.push();
    //Op3D.translate(-2,-3,-1);

    //Op3D.pop(&Op3D.A1);


    Op3D.pop();
    Op3D.imprimeMatriz(Op3D.A); //Comprobar valores de Matriz A
    //glFlush();
    //glutSwapBuffers();
}

//-------------------------------------------------------------------------
//funciones callbacks
void idle(void)
{
    /*
    Op3D.push();
    Op3D.RotacionParalela('Y',1,0,0);
    Op3D.pop();
    */
    dibujaEsc();
    glutPostRedisplay();
    glutSwapBuffers();

    //glFlush();
    usleep(60000);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

}

static void keys(unsigned char key, int x, int y)
{
    switch(key){
                case 'd':
                     Theta = 0;
                     ThetaX = 1;
                     ThetaY = 0;
                     ThetaZ = 0;
                     break;
                case 'a':
                     Theta = 0;
                     ThetaX =-1;
                     ThetaY = 0;
                     ThetaZ = 0;
                     break;
                case 'w':
                     Theta = 0;
                     ThetaY =1;
                     ThetaX = 0;
                     ThetaZ = 0;
                     break;
                case 's':
                     Theta = 0;
                     ThetaY =-1;
                     ThetaX = 0;
                     ThetaZ = 0;
                     break;
                case 'q':
                     Theta = 0;
                     ThetaZ =1;
                     ThetaX = 0;
                     ThetaY = 0;
                     break;
                case 'e':
                     Theta = 0;
                     ThetaZ =-1;
                     ThetaX = 0;
                     ThetaY = 0;
                     break;
                case 'z':
                     Theta = 1;
                     ThetaZ = 0;
                     ThetaX = 0;
                     ThetaY = 0;
                     break;
                case 'x':
                     Theta = -1;
                     ThetaZ = 0;
                     ThetaX = 0;
                     ThetaY = 0;
                     break;
                default:
                     Theta = 0;
                     ThetaX = 0;
                     ThetaY = 0;
                     ThetaZ = 0;
                     break;
    }
    glutPostRedisplay();
}


void drawAxis()
{
     glShadeModel(GL_SMOOTH);
     glLineWidth(3.0);
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(0.5f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,0.5f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,0.5f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
     glLineWidth(1.0);
 }

//--------------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Op3D.LoadIdentity();
    drawAxis();
    glColor3f(1.0f,1.0f,1.0f);


    //Op3D.push();
    //Op3D.translate(-20.0,-20.0,-80.0);
    //Op3D.rotateXYZ(180.0,P1,P2);
    //myShip.draw();
    //Op3D.pop();
    glutSwapBuffers();
}

void init()
{
    //dibujaEsc();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);
    dibujaEsc();
	//prepara los parametros de ajuste del objeto
    //myShip.setDeltaDegRotation(30.0);
    //myShip.setRotation(TRUE);
    //myShip.setDeltaAxisTranslation(vT);
    //myShip.setTranslation(TRUE);
    //myShip.setAnimation(TRUE);

    Theta = 1;
    ThetaX = 1;
    ThetaY = 1;
    ThetaZ = 1;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Parcial 2");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
