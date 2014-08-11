/* 
 * File:   Softy.cpp
 * Author: johannes
 * 
 * Created on 24. Juli 2014, 15:06
 */

#include "Softy.h"


Softy::Softy() {
}

Softy::Softy(const Softy& orig) {
}

Softy::~Softy() {
}

void Softy::update(float deltaTime) {

    list<Particle*>::iterator aParticle;
    
    //integrate unconstrainted position of all particles
    for(aParticle = this->particles.begin(); aParticle != this->particles.end(); aParticle++) {
        (*aParticle)->gravity = this->gravity;
        (*aParticle)->updatePosition(deltaTime);
    }

    
    //update Velocity of all particles
    for(aParticle = this->particles.begin(); aParticle != this->particles.end(); aParticle++) {
        (*aParticle)->updateVelocity(deltaTime);
    }
};

void Softy::updateSoftConstraints() {
      //correct position of particles coresponding to internal constraints
    list<SoftConstraint*>::iterator aSoftConstraint;
    for(aSoftConstraint = this->internalSoftConstraints.begin(); aSoftConstraint != this->internalSoftConstraints.end(); aSoftConstraint++) {
        (*aSoftConstraint)->update();   
    }
};

void Softy::updateExternalConstraints() {
     
    //correct position of particles coresponding to external constraints
    list<Constraint*>::iterator anExternalConstraint;
    for(anExternalConstraint = this->externalConstraints.begin(); anExternalConstraint != this->externalConstraints.end(); anExternalConstraint++) {
        (*anExternalConstraint)->update();   
    }
};


void Softy::updateVelocity(float deltaTime) {

    list<Particle*>::iterator aParticle;
    
    //update Velocity of all particles
    for(aParticle = this->particles.begin(); aParticle != this->particles.end(); aParticle++) {
        (*aParticle)->updateVelocity(deltaTime);
    }
};
