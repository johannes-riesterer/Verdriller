/* 
 * File:   SoftyCuboid.h
 * Author: johannes
 *
 * Created on 30. Juli 2014, 14:47
 */

#ifndef SOFTYCUBOID_H
#define	SOFTYCUBOID_H
#include "Softy.h"


class SoftyCuboid : public Softy {
public:
    
    int resolution;
    float a;
    float b;
    float c;
    
    SoftyCuboid(float a, float b , float c, int res_a, int res_b, int res_c);
    SoftyCuboid(const SoftyCuboid& orig);
    virtual ~SoftyCuboid();

    
private:

};

#endif	/* SOFTYCUBOID_H */

