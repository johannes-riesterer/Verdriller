/* 
 * File:   SoftConstraint.cpp
 * Author: johannes
 * 
 * Created on 25. Juli 2014, 10:14
 */

#include "SoftConstraint.h"

SoftConstraint::SoftConstraint() {
};

SoftConstraint::SoftConstraint(Particle *p0, Particle *p1, Particle *p2, Particle *p3) {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;

    this->D_m.col(0) << p0->referencePosition - p3->referencePosition;
    this->D_m.col(1) << p1->referencePosition - p3->referencePosition;
    this->D_m.col(2) << p2->referencePosition - p3->referencePosition;

    this->kappa = 0.1f;
    this->nu = 0.01f;
    this->lameMu = this->kappa/(2.0f * (1.0f + this->nu));
    this->lameLambda = this->kappa * this->nu/((1.0f + this->nu) * (1.0f - 2.0f*this->nu));
    
    this->active = true;
    
};

SoftConstraint::SoftConstraint(const SoftConstraint& orig) {
};

SoftConstraint::~SoftConstraint() {
};

//---------------------------------------------------------------
// Update
//---------------------------------------------------------------

//update values. Order matters
void SoftConstraint::updateDefGrad() {
    this->D_s.col(0) << p0->position - p3->position;
    this->D_s.col(1) << p1->position - p3->position;
    this->D_s.col(2) << p2->position - p3->position;

    this->defGrad = D_s * D_m.inverse();
    
    float det = defGrad.determinant();
    //check if cell is degenerated, i.e. det(defgrad) <= 0)
    if(det<= 0) {
        
        this->degenrated = true;
        //compute singular value decomposition of defGrad
        JacobiSVD<_Matrix3> svd(this->defGrad, ComputeFullU | ComputeFullV);
        MatrixXf F_sing = svd.singularValues();
        MatrixXf U  = svd.matrixU();
        MatrixXf V  = svd.matrixV();
        
        this->U = U;
        this->V = V;
        
        //find smalles Element and negate corresponding colums
         int smallestEntry = 0;
         
         if(F_sing(1) < F_sing(0)) {
             smallestEntry = 1;
         }
         if(F_sing(2) < F_sing(smallestEntry)) {
             smallestEntry = 2;
         }
         
         F_sing(smallestEntry) = - F_sing(smallestEntry);
        U.col(smallestEntry) = -U.col(smallestEntry);
         //compose new defGrad
  
        _Matrix3 F;
         F << F_sing(0), 0.0f, 0.0f,
              0.0f, F_sing(1), 0.0f,                
              0.0f, 0.0f, F_sing(2);
         
    
        this->defGrad = F;
        //cout << "det <0"; 
    }
    
    else {
        this->degenrated = false;
    }
    
 
};


void SoftConstraint::updateStrainEnergyField() {
    _Matrix3 F_tF = defGrad.transpose() * defGrad;
    this->I_1 = F_tF.trace();
    this->I_3 = F_tF.determinant();
    this->strainEnergyField = ((this->lameMu/2.0f)*(this->I_1 - log(this->I_3) - 3.0f)) 
                            + ((this->lameLambda/8.0f) * log(this->I_3) * log(this->I_3)); 
};

void SoftConstraint::updatePiolaKirchhoffTensor() {
    _Matrix3 F_trinv = this->defGrad.transpose();
    F_trinv = F_trinv.inverse().eval();
    
    this->piolaKirchhoffTensor = (this->lameMu * (this->defGrad - F_trinv)) 
                               + (this->lameLambda * log(I_3)/2.0f * F_trinv);
    
    //handle degenerated cells
    if(this->degenrated) {
        this->piolaKirchhoffTensor = this->U * this->piolaKirchhoffTensor * this->V.adjoint();
    }
};

void SoftConstraint::updateStrainEnergyFunction() {
    this->strainEnergyFunction = this->undeformedVolume *this->strainEnergyField; 
};



void SoftConstraint::updateNabla() {
    _Matrix3 tmp = this->undeformedVolume * this->piolaKirchhoffTensor * (((this->D_m).transpose()).inverse());
    this->nabla0 = tmp.col(0); 
    this->nabla1 = tmp.col(1);
    this->nabla2 = tmp.col(2);
    this->nabla3 = -(this->nabla0 + this->nabla1 + this->nabla2);
};
void SoftConstraint::updateLambda() {
    float tmp = this->p0->invMass * this->nabla0.dot(this->nabla0) 
              + this->p1->invMass * this->nabla1.dot(this->nabla1)
              + this->p2->invMass * this->nabla2.dot(this->nabla2)
              + this->p3->invMass * this->nabla3.dot(this->nabla3);
    if(abs(tmp) > 0.0f) {
            this->lambda = -this->strainEnergyFunction/tmp;
             
    }
    else {
        this->lambda = 0.0f;
    }

    
};




//call this method to update values in correct order
void SoftConstraint::updateValues() {
    this->updateDefGrad();
    this->updateStrainEnergyField();
    this->updatePiolaKirchhoffTensor();
    this->updateStrainEnergyFunction();
    this->updateNabla();
    this->updateLambda();
   
    
};

//apply position corrections to involved particles
void SoftConstraint::updatePositions() {
    if(this->p0->dynamic) {
            this->p0->position += this->p0->invMass * this->lambda * this->nabla0;
    }
    
    if(this->p1->dynamic) {
        this->p1->position += this->p1->invMass * this->lambda * this->nabla1;
    }
    
    if(this->p2->dynamic) {
           this->p2->position += this->p2->invMass * this->lambda * this->nabla2;
    }
    if(this->p3->dynamic) { 
        this->p3->position += this->p3->invMass * this->lambda * this->nabla3;
    }
};

void SoftConstraint::update() {
    if(this->active) {
        this->updateValues();
        this->updatePositions();
    }
};