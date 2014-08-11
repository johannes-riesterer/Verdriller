/* 
 * File:   Particle.h
 * Author: johannes
 *
 * Created on 24. Juli 2014, 14:29
 */

#ifndef PARTICLE_H
#define	PARTICLE_H
#include "defines.h"

class Particle {
public:
    //bool to turn on and off dynamic simulation of the particle
    bool dynamic;
    
    //bool to turn on and off  gravitational force
    bool gravity;
    
    //the initial position of the particle. 
    _Vector3 referencePosition;
    
   
    _Vector3 position;
   
    //position before time inegration. Mainly needed for velocityupdate
    _Vector3 positionBeforeUpdate;
    //The velocity of the particle
    _Vector3 velocity;
    
    //Forces acting on the particle
    _Vector3 force;

    //The inverse mass of the particle
    float invMass;
    
    //the mass of the particle
    float mass;

    

    Particle();
    Particle(const Particle& orig);
    virtual ~Particle();

    //update the position of the particle according to velocity, forces and deltaTime
    void updatePosition(float);
    
    void updateVelocity(float);

private:

};

#endif	/* PARTICLE_H */

