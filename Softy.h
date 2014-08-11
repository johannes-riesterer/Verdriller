/* 
 * File:   Softy.h
 * Author: johannes
 *
 * Created on 24. Juli 2014, 15:06
 */

#ifndef SOFTY_H
#define	SOFTY_H
#include "Particle.h"
#include "SoftConstraint.h"
#include "defines.h"

class Softy {
public:
    
    bool gravity;
    
    //list of all particles which form the softbody
    list<Particle*> particles;
    
    //list of all internal constraints
    list<SoftConstraint*> internalSoftConstraints;

    //list of all external constraints
    list<Constraint*> externalConstraints;
    
    //reference topology of the softbody
    Delaunay referenceMesh;
    
    
    //material properties
    float mass;
    float kappa;
    float nu;
    
    Softy();
    Softy(const Softy& orig);
    virtual ~Softy();
    
    void update(float);
    void updateSoftConstraints();
    void updateExternalConstraints();
    void updateVelocity(float);
    
private:

};

#endif	/* SOFTY_H */

