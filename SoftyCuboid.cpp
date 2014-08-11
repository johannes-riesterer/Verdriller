/* 
 * File:   SoftyCuboid.cpp
 * Author: johannes
 * 
 * Created on 30. Juli 2014, 14:47
 */

#include "SoftyCuboid.h"
#include "Physics.h"
#include "DistanceConstraint.h"

SoftyCuboid::SoftyCuboid(float a, float b, float c, int res_a, int res_b, int res_c) {
    this->gravity = true;
    this->a = a;
    this->b = b;
    this->c = c;

    //construct a cube starting in (0,0,0) with lengt a, b, c and equivariant vertices with distance res_a, res_b and res_c accordingly 
    for(int i = 0; i<= res_a; i++) {
        for(int j = 0; j<= res_b; j++) {
            for(int k = 0; k<= res_c; k++) {
        
                //create particle
                Particle *aParticle = new Particle();
        
                //set position
                aParticle->position(0) = i* a/float(res_a);
                aParticle->position(1) = k* b/float(res_b);
                aParticle->position(2) = j* c/float(res_c);
                
                //set reference position
                aParticle->referencePosition = aParticle->position;
            
                //add to particles list
                this->particles.push_back(aParticle);
                
                //insert into delaunay mesh and get reference to the new vertex
                Vertex_handle newVertex = this->referenceMesh.insert(Point3(aParticle->position(0),aParticle->position(1),aParticle->position(2)));
                
                //add the reference of the particle to newVertex
                newVertex->particle = aParticle;
                
                //initialise external constraints
                //left side is not dynamic
                if(i == 0 || i == res_a) {
                    Particle *ankerParticle = new Particle();
                    ankerParticle->position = aParticle->position;
                    ankerParticle->dynamic = false;
                    DistanceConstraint *ankerConstraint = new DistanceConstraint(ankerParticle, aParticle);
                    this->externalConstraints.push_back(ankerConstraint);
                }
           }
        }
    }
    
    
    //initialise internal constraints
    Finite_cells_iterator cit;
    for(cit = this->referenceMesh.finite_cells_begin(); cit != this->referenceMesh.finite_cells_end(); cit++) {
        
        SoftConstraint *aSoftConstraint = new SoftConstraint(cit->vertex(0)->particle, cit->vertex(1)->particle, cit->vertex(2)->particle, cit->vertex(3)->particle);
        
        //set volume of undeformed cell
        float volume = Verdriller::_computeVolumeOfCell(cit);
        aSoftConstraint->undeformedVolume = volume;
        
        //add constraint to internal constraint list of softbody
        this->internalSoftConstraints.push_back(aSoftConstraint);
    }
};

SoftyCuboid::SoftyCuboid(const SoftyCuboid& orig) {
}

SoftyCuboid::~SoftyCuboid() {
}

