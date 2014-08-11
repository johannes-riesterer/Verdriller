/* 
 * File:   defines.h
 * Author: johannes
 *
 * Created on 22. Juli 2014, 15:19
 */

#ifndef DEFINES_H
#define	DEFINES_H

#include <cmath>


//Using std
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <iostream>
using namespace std;



//Configure Eigen3
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>


using namespace Eigen;
typedef Matrix3f _Matrix3;
typedef Vector3f _Vector3;
typedef Matrix4f _Matrix4;



//Configure Cgal
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_vertex_base_3.h>
#include <CGAL/Simple_cartesian.h>

#include "Particle.h"
class Particle;
//Define own Vertex
//---------------------------------------------------------------------
//---------------------------------------------------------------------

template < class GT, class Vb = CGAL::Triangulation_vertex_base_3<GT> >
class My_vertex_base
: public Vb {
public:
    typedef typename Vb::Vertex_handle Vertex_handle;
    typedef typename Vb::Cell_handle Cell_handle;
    typedef typename Vb::Point Point;

    template < class TDS2 >
    struct Rebind_TDS {
        typedef typename Vb::template Rebind_TDS<TDS2>::Other Vb2;
        typedef My_vertex_base<GT, Vb2> Other;
    };

    My_vertex_base() {
    }

    My_vertex_base(const Point& p)
    : Vb(p) {
    }

    My_vertex_base(const Point& p, Cell_handle c)
    : Vb(p, c) {
    }

    //Put additional properties of vertex here
    //---------------------------------------------------------------------
    Particle *particle;
};

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Simple_cartesian<float> K;
typedef CGAL::Triangulation_data_structure_3<My_vertex_base<K> > Tds;

//Cgal types for later use
//---------------------------------------------------------------------
typedef CGAL::Delaunay_triangulation_3<K, Tds> Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Point Point3;
typedef Delaunay::Cell_handle Cell_handle;
typedef Delaunay::Finite_cells_iterator Finite_cells_iterator;


#endif	/* DEFINES_H */

