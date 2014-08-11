/* 
 * File:   Particle.cpp
 * Author: johannes
 * 
 * Created on 24. Juli 2014, 14:29
 */

#include "Particle.h"

Particle::Particle() {
    this->dynamic = true;
    this->mass = 1.0f;
    this->invMass = 1.0f / this->mass;
    this->gravity = true;
    
    this->force(0) = 0.0f;
    this->force(1) = 0.0f;
    this->force(2) = 0.0f;
    
    
    this->velocity(0) = 0.0f;
    this->velocity(1) = 0.0f;
    this->velocity(2) = 0.0f;
};

Particle::Particle(const Particle& orig) {
};

Particle::~Particle() {
};

void Particle::updatePosition(float deltaTime) {
    
    if(this->dynamic) {
        
        //store position before update 
        this->positionBeforeUpdate = this->position;
    
        //integrate position over time
        this->velocity+= deltaTime * this->invMass * this->force;
        this->position += deltaTime * this->velocity;
    
        //clear external forces and add gravity
        this->force(0) = 0.0f;
        if(this->gravity) {
                this->force(1) = -9.8f;
        }
        else {
                this->force(1) = 0.0;
        }
        this->force(2) = 0.0f;
    }
};

void Particle::updateVelocity(float deltaTime) {
    if(this->dynamic) {
            this->velocity = (1.0f/deltaTime) * (this->position - this->positionBeforeUpdate);
    }
};
