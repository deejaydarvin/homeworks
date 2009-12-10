namespace internal {

template < class Kernel_ >
class PPoint_2 {

public:

  //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! default constructor constructs origin
  PPoint_2() : 
    _m_x(0) // assumes that NT is constructible from SmallIntConstant
  {
  }

  //! constructor from two given coordinates
  PPoint_2(NT x) :
    _m_x(x), _m_y(x*x) // assumes that NT is copy-constructible
  {
  }
  
  //! returns x-coordinate of point
  NT x() const {
    return _m_x;
  }

 //! returns y-coordinate of point
  NT y() const {
    return _m_y;
  }
  
private:
  
  //! x-coordinate of point
  NT _m_x;

  //! y-coordinate of point
  NT _m_y;
};


//! orientation functor
template < class Kernel_ >
class POrientation_2 {

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

    std::cerr << "Parabolic Orientation_2 not complete!" << std::endl;

    if (p.x() < q.x()) { // assumes that NT has operator<(int)
      if (q.x() < r.x()) { 
        return -1;
      } 
    }
    // else
    return 0;
  }
};

} // namespace internal


//! a simple kernel for points on a parabola (and operations on them)
template < class NT_ >
class Parabolic_kernel_2 {

public:

  //! this instance's number type
  typedef NT_ NT;

  //! the instantiated template
  typedef Parabolic_kernel_2< NT > Self;

  // GEOMETRIC TYPES (ref-counted ones would are encouraged)

  //! type for point
  typedef internal::PPoint_2< Self > Point_2;
  
  // GEOMETRIC OPERATIONS (as functors)
  
  //! Orientation predicate
  typedef internal::POrientation_2< Self > Orientation_2;

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

