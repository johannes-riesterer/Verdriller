/* 
 * File:   SoftConstrain.h
 * Author: johannes
 *
 * Created on 25. Juli 2014, 10:14
 */

#ifndef SOFTCONSTRAIN_H
#define	SOFTCONSTRAIN_H

#include "defines.h"
#include "Constraint.h"

class SoftConstraint : Constraint {
public:
    
    Particle * p0;
    Particle * p1;
    Particle * p2;
    Particle * p3;
    float undeformedVolume;
   
    float lameLambda;
    float lameMu;
    
    float kappa;
    float nu;

    //handling of degenerated cells
    bool degenrated;
    _Matrix3 U;
    _Matrix3 V;
    
    SoftConstraint();
    SoftConstraint(Particle*, Particle*, Particle*, Particle*);
    SoftConstraint(const SoftConstraint& orig);
    
    virtual ~SoftConstraint();
    
    void update();
    
    
    
private:

    _Matrix3 D_m;
    _Matrix3 D_s;
    _Matrix3 defGrad;
    _Matrix3 piolaKirchhoffTensor;
    float strainEnergyField;
    
    _Vector3 nabla0;
    _Vector3 nabla1;
    _Vector3 nabla2;
    _Vector3 nabla3;
    
    float strainEnergyFunction;
    
    float lambda;
    
    float I_1;
    float I_3;
    
    void updateDefGrad();
    void updateLambda();
    void updateNabla();
    void updateStrainEnergyField();
    void updatePiolaKirchhoffTensor();
    void updateStrainEnergyFunction();
    void updateValues();
    void updatePositions();
};

#endif	/* SOFTCONSTRAIN_H */

