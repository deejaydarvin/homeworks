#include <CGAL/basic.h>

namespace internal {

template < class Kernel_ >
class Point_2 {

public:

  //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! default constructor constructs origin
  Point_2() : 
    _m_x(0), _m_y(0),_m_w(1) // assumes that NT is constructible from SmallIntConstant
  {
  }

  //! constructor from two given coordinates
  Point_2(NT x, NT y) :
    _m_x(x), _m_y(y) // assumes that NT is copy-constructible
  {
	  _m_w=gcd(x,y); //If we installed CGAL, we might use its gcd as well
	  _m_x= x * _m_w;
	  _m_y= y * _m_w;
  }
  
  //! returns x-coordinate of point
  NT x() const {
    return _m_x/_m_w;
  }

 //! returns y-coordinate of point
  NT y() const {
    return _m_y/_m_w;
  }

  NT x_en() const {
    return _m_x;
  }

  NT y_en() const {
    return _m_x;
  }

  NT common_den() const {
    return _m_w;
  }

  

  
private:
  
  //! x-coordinate of point
  NT _m_x;

  //! y-coordinate of point
  NT _m_y;

  //! common denominator
  NT _m_w;
};


//! orientation functor
template < class Kernel_ >
class Orientation_2 {

public:

   //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! the kernel's point type
  typedef typename Kernel_::Point_2 Point_2;

  //! function call operator
  // (instead of int a 'enumeration is encouraged)
  int operator()(const Point_2& p, const Point_2& q, const Point_2& r) const {
	  NT px=p.x_en();
	  NT qx=q.x_en();
	  NT rx=r.x_en();
	  NT py=p.y_en();
	  NT qy=q.y_en();
	  NT ry=r.y_en();
	  NT pw=p.common_den();
	  NT qw=q.common_den();
	  NT rw=r.common_den();

	  float pxd=fl(px); apxd=abs(pxd);
	  float qxd=fl(qx); aqxd=abs(qxd);
	  float rxd=fl(rx); arxd=abs(rxd);
	  float pyd=fl(py); apyd=abs(pyd);
	  float qyd=fl(qy); aqyd=abs(qyd);
	  float ryd=fl(ry); aryd=abs(ryd);
	  float pwd=fl(pw); apwd=abs(pwd);
	  float qwd=fl(qw); aqwd=abs(qwd);
	  float rwd=fl(rw); arwd=abs(rwd);

	  float dettilde = pwd*(qxd*ryd - qyd*rxd) - qwd*(pxd*ryd - pyd*rxd) + rwd*(pxd*qyd - pyd*qxd);

	  float mes = apwd*(aqxd*aryd + aqyd*arxd) - aqwd*(apxd*aryd + apyd*arxd) + arwd*(apxd*aqyd + apyd*aqxd); //shouldnt MINNORM appear here?

	  if(abs(dettilde) > 9*uu*mes) //uu should be declared somewhere...
	  {
		  if (dettilde < 0) { // assumes that NT has operator<(int)
			  return -1;
		  } else if (dettilde > 0) { // assumes that NT has operator<(int)
			  return 1;
		  }	
	  }
	  // else
	  NT det= pw*(qx*ry - qy*rx) - qw*(px*ry - py*rx) + rw*(px*qy - py*qx);
	  return sign(det);
  }
};

} // namespace internal


//! a simple cartesian kernel for points (and operations on them)
template < class NT_ >
class homogenous_Cartesian_kernel_2 {

	public:

		//! this instance's number type
		typedef NT_ NT;

		//! the instantiated template
		typedef homogenous_Cartesian_kernel_2< NT > Self;

		// GEOMETRIC TYPES (ref-counted ones would are encouraged)

		//! type for point
		typedef internal::Point_2< Self > Point_2;

		// GEOMETRIC OPERATIONS (as functors)

		//! orientation predicate
		typedef internal::Orientation_2< Self > Orientation_2;

		//! instance of orientation predicate
		Orientation_2 orientation_2_object() {
			return Orientation_2();
		}

		// GEOMETRIC OPERATIONS (as functions)

		//! orientation test
		int orientation(const Point_2& p, const Point_2& q, const Point_2& r) const {
			Orientation_2 orientation_functor;
			return orientation_functor(p,q,r);
		}

};

