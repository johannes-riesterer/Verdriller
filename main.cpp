/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 22. Juli 2014, 14:39
 */

#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>

#include "defines.h"
#include "SoftyCuboid.h"
#include "Physics.h"

using namespace Verdriller;
Physics physics;

#define window_width  1280              
#define window_height 1024
Delaunay T;

float newTime = 0.0;
float currentTime = 0.0;
float frameTime = 0.0;
float accomulator = 0.0;

SoftyCuboid *cuboid;
/*
 * 
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(0.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    list<Softy*>::iterator aSofty;
    for(aSofty = physics.simulatedBodies.begin(); aSofty != physics.simulatedBodies.end(); aSofty++) {
        drawMesh((*aSofty)->referenceMesh);
    }
    
    
    //calculate delta time since last call 
    newTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    frameTime = newTime - currentTime;
    currentTime = newTime;
    
    //update physics
    physics.update(frameTime);
      
    
    //swap buffers
    glutSwapBuffers();
    glutPostRedisplay();

}

void idle() {
      

};

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, .1, 1000);
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY) {
    
    //activate and deactivate gravity
    if(key == 'g') {
        cuboid->gravity =  !cuboid->gravity;
    }
    
    //activate and deactivate right constraints
    if(key == 'a') {
        int i = 0;
        list<Constraint*>::iterator anExternalConstraint;
        for(anExternalConstraint = cuboid->externalConstraints.begin(); anExternalConstraint != cuboid->externalConstraints.end(); anExternalConstraint++) {
            if(i > 3) {  
                    (*anExternalConstraint)->active = ! (*anExternalConstraint)->active;   
            }
             i++;
        }
    }
    
    
    
}

void GL_Setup(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(45, (float) width / height, .1, 100);


    cuboid = new SoftyCuboid(5.0,0.5,0.5, 10, 1, 1);
    physics.simulatedBodies.push_back(cuboid);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Verdriller");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    GL_Setup(window_width, window_height);
    glutMainLoop();

    return 0;
}

