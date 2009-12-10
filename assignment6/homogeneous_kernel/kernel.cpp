#include <iostream>
#include <list>

#include "Cartesian_kernel_2.h"
#include "Parabolic_kernel_2.h"
#include "Convex_hull_2.h"

#include <CGAL/Gmpq.h>

template < class NT >
void homogenous() {
  
  typedef Homogenous_kernel_2< NT > Kernel_2;

  typedef typename Kernel_2::Point_2 Point_2;

  // construct some points
  Point_2 o;
  Point_2 p1(1); // requires NT to be ConstructibleFromSmallInt
  Point_2 p2(5);
  Point_2 pl(2);
  Point_2 pr(4);
  
  // orientation of points with functor
  typename Kernel_2::Orientation_2 orientation;
  std::cout << "Orientation(o,p1,p2) = " << orientation(o,p1,p2)
            << std::endl;
  std::cout << "Orientation(o,p1,pl) = " << orientation(o,p1,pl)
            << std::endl;
  std::cout << "Orientation(o,p1,pr) = " << orientation(o,p1,pr)
            << std::endl;
  

  // orientation of points with function
  Kernel_2 kernel;
  std::cout << "Orientation(o,p1,p2) = " << kernel.orientation(o,p1,p2)
            << std::endl;
  std::cout << "Orientation(o,p1,pl) = " << kernel.orientation(o,p1,pl)
            << std::endl;
  std::cout << "Orientation(o,p1,pr) = " << kernel.orientation(o,p1,pr)
            << std::endl;

  std::list< Point_2 > input;
  input.push_back(o);
  input.push_back(p1);
  input.push_back(p2);
  input.push_back(pl);
  input.push_back(pr);

  // Convex hull
  typedef Convex_hull_2< Kernel_2 > CH_2;
  
  std::list< Point_2 > hull;
  CH_2 ch;
  ch(input.begin(), input.end(), std::back_inserter(hull));
  
}


int main() {
  
  /*std::cout << "CARTESIAN with 'double'" << std::endl;
  cartesian< double >();
  std::cout << std::endl;


  std::cout << "CARTESIAN with 'int'" << std::endl;
  cartesian< int >();
  std::cout << std::endl;

  std::cout << "CARTESIAN with 'unsigned int' " 
            << "- evil, because of '-1' in input" << std::endl;
  cartesian< unsigned int >();
  std::cout << std::endl;

  std::cout << "CARTESIAN with 'CGAL::Gmpq'" << std::endl;
  cartesian< CGAL::Gmpq >();
  std::cout << std::endl;
 
 
  std::cout << "CARTESIAN with 'double'" << std::endl;
  cartesian< double >();
  std::cout << std::endl;
  
  std::cout << "PARABOLIC with 'int'" << std::endl;
  parabolic< int >();
  std::cout << std::endl;

  std::cout << "PARABOLIC with 'unsigned int' " 
            << "- evil, because of '-1' in input" << std::endl;
  parabolic< unsigned int >();
  std::cout << std::endl;

  std::cout << "PARABOLIC with 'CGAL::Gmpq'" << std::endl;
  parabolic< CGAL::Gmpq >();
  std::cout << std::endl; */

  std::cout << "PARABOLIC with 'int'" << std::endl;
  parabolic< int >();
  std::cout << std::endl;

  std::cout << "PARABOLIC with 'unsigned int' " 
            << "- evil, because of '-1' in input" << std::endl;
  parabolic< unsigned int >();
  std::cout << std::endl;

  std::cout << "PARABOLIC with 'CGAL::Gmpq'" << std::endl;
  parabolic< CGAL::Gmpq >();
  std::cout << std::endl;


}
