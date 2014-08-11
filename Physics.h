/* 
 * File:   Physics.h
 * Author: johannes
 *
 * Created on 25. Juli 2014, 10:08
 */

#ifndef PHYSICS_H
#define	PHYSICS_H
#include "defines.h"
#include "Softy.h"
#include "SoftConstraint.h"
#include "Constraint.h"

class Physics {
public:
    
    int constraintIterations;
    
    //list of all Softbodies 
    list<Softy*> simulatedBodies;
    
    //list of all externel constraints
    list<Constraint*> constraints;
    
    float deltaTime;

    Physics();
    Physics(const Physics& orig);
    virtual ~Physics();
    
    void update(float);
    void updateSofties(float);
    
private:

};



#endif	/* PHYSICS_H */
namespace Verdriller {
    
    
    float _computeVolumeOfCell(Cell_handle); 
    void drawMesh(Delaunay);
    void update(float);
    
    
}
