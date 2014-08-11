/* 
 * File:   Physics.cpp
 * Author: johannes
 * 
 * Created on 25. Juli 2014, 10:08
 */

#include "Physics.h"

#include <GL/glut.h>

Physics::Physics() {
    this->constraintIterations = 10;
}

Physics::Physics(const Physics& orig) {
}

Physics::~Physics() {
}

void Physics::update(float deltaTime) {

    //update sofbodies
    list<Softy*>::iterator aSofty;
    for (aSofty = this->simulatedBodies.begin(); aSofty != this->simulatedBodies.end(); aSofty++) {
        (*aSofty)->update(deltaTime);

    }


    for (aSofty = this->simulatedBodies.begin(); aSofty != this->simulatedBodies.end(); aSofty++) {
        for (int i = 0; i< this->constraintIterations; i++) {
            (*aSofty)->updateSoftConstraints();
            (*aSofty)->updateExternalConstraints();

        }
    }


    for (aSofty = this->simulatedBodies.begin(); aSofty != this->simulatedBodies.end(); aSofty++) {
        (*aSofty)->updateVelocity(deltaTime);

    }

};

// Namespace Verdriller
//----------------------------------------------------------------------------


float Verdriller::_computeVolumeOfCell(Cell_handle cell) {

    //Formula taken from http://mathworld.wolfram.com/Tetrahedron.html

    _Matrix4 volMatrix;
    Point3 p0 = cell->vertex(0)->point();
    Point3 p1 = cell->vertex(1)->point();
    Point3 p2 = cell->vertex(2)->point();
    Point3 p3 = cell->vertex(3)->point();

    volMatrix << p0.x(), p0.y(), p0.z(), 1.0f,
            p1.x(), p1.y(), p1.z(), 1.0f,
            p2.x(), p2.y(), p2.z(), 1.0f,
            p3.x(), p3.y(), p3.z(), 1.0f;

    float vol = 1.0f / 6.0f * volMatrix.determinant();

    return abs(vol);
};

void Verdriller::drawMesh(Delaunay mesh) {

    for (Finite_cells_iterator cit = mesh.finite_cells_begin(); cit != mesh.finite_cells_end(); cit++) {

        _Vector3 p0 = cit->vertex(0)->particle->position;
        _Vector3 p1 = cit->vertex(1)->particle->position;
        _Vector3 p2 = cit->vertex(2)->particle->position;
        _Vector3 p3 = cit->vertex(3)->particle->position;

        glPointSize(4);
        glBegin(GL_POINTS);

        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(p0.x(), p0.y(), p0.z());
        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());
        glVertex3f(p3.x(), p3.y(), p3.z());
        glEnd();
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(p0.x(), p0.y(), p0.z());
        glVertex3f(p1.x(), p1.y(), p1.z());

        glVertex3f(p0.x(), p0.y(), p0.z());
        glVertex3f(p2.x(), p2.y(), p2.z());

        glVertex3f(p0.x(), p0.y(), p0.z());
        glVertex3f(p3.x(), p3.y(), p3.z());


        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());

        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p3.x(), p3.y(), p3.z());

        glVertex3f(p2.x(), p2.y(), p2.z());
        glVertex3f(p3.x(), p3.y(), p3.z());
        glEnd();
    }

};

