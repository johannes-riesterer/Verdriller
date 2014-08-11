/* 
 * File:   DistanceConstraint.h
 * Author: johannes
 *
 * Created on 7. August 2014, 14:45
 */

#ifndef DISTANCECONSTRAINT_H
#define	DISTANCECONSTRAINT_H
#include "Constraint.h"
#include "defines.h"
#include "Particle.h"

class DistanceConstraint : public Constraint{
public:
    
    Particle *p0;
    Particle *p1;
    
    float distance;
    
    DistanceConstraint();
    DistanceConstraint(Particle*, Particle*);
    DistanceConstraint(const DistanceConstraint& orig);
    virtual ~DistanceConstraint();
    
    
    void update();
    
private:

};

#endif	/* DISTANCECONSTRAINT_H */

