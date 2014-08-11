/* 
 * File:   DistanceConstraint.cpp
 * Author: johannes
 * 
 * Created on 7. August 2014, 14:45
 */

#include "DistanceConstraint.h"

DistanceConstraint::DistanceConstraint() {
    this->distance = 0.0f;
};

DistanceConstraint::DistanceConstraint(Particle* p0, Particle* p1) {
    this->distance = 0.0f;
    this->p0 = p0;
    this->p1 = p1;
    this->active = true;
};

DistanceConstraint::DistanceConstraint(const DistanceConstraint& orig) {
};

DistanceConstraint::~DistanceConstraint() {
};

void DistanceConstraint::update() {
    if (this->active) {
        _Vector3 diff = p0->position - p1->position;
        float d = sqrt(diff.dot(diff));

        float w = p0->invMass / (p0->invMass + p1->invMass);

        if (d != 0.0f) {
            _Vector3 delta = (w * (d - this->distance) / d) * diff;
            if (p0->dynamic) {
                p0->position -= delta;
            }

            if (p1->dynamic) {
                p1->position += delta;
            }
        }
    }
};
