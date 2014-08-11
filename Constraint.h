/* 
 * File:   Constraint.h
 * Author: johannes
 *
 * Created on 31. Juli 2014, 11:20
 */

#ifndef CONSTRAINT_H
#define	CONSTRAINT_H

class Constraint {
public:
    //switch on and off constraint
    bool active;
    
    Constraint();
    Constraint(const Constraint& orig);
    virtual ~Constraint();
    virtual void update() = 0;
private:

};

#endif	/* CONSTRAINT_H */

