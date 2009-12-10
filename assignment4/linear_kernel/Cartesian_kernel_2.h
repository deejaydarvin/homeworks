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
    _m_x(0), _m_y(0) // assumes that NT is constructible from SmallIntConstant
  {
  }

  //! constructor from two given coordinates
  Point_2(NT x, NT y) :
    _m_x(x), _m_y(y) // assumes that NT is copy-constructible
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

template < class Kernel_ >
class Segment_2 {

public:

  //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! default constructor seqment from Origin to Origin
  Segment_2() : 
    _m_p(), _m_q() // assumes that NT is constructible from SmallIntConstant
  {
  }

  //! constructor from two given points
  Segment_2(Point_2 p, Point_2 q) :
    _m_p(p), _m_q(q) 
  {
  }
  
  //! returns the first point
  NT p() const {
    return _m_p;
  }

  //! returns the second point
  NT q() const {
    return _m_q;
  }
  
private:
  
  //! One of the both points
  Point_2 _m_p;

  //! The other point
  Point_2 _m_q;
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
    NT det = 
      (q.x() - p.x()) * (r.y() - p.y()) - 
      (q.y() - p.y()) * (r.x() - p.x());
    
    if (det < 0) { // assumes that NT has operator<(int)
      return -1;
    } else if (det > 0) { // assumes that NT has operator<(int)
      return 1;
    }
    // else
    return 0;
  }
};

//! x-compare functor
template < class Kernel_ >
class x_compare_2 {

public:

   //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! the kernel's point type
  typedef typename Kernel_::Point_2 Point_2;

  //! function call operator
  // (instead of int a 'enumeration is encouraged)
  int operator()(const Point_2& p, const Point_2& q) const {
    NT px = p.x(); NT py = p.y();
    if (x < y) { // assumes that NT has operator<(int)
      return -1;
    } else if (x > y) { // assumes that NT has operator<(int)
      return 1;
    }
    // else
    return 0;
  }
};

//! xy-compare functor
template < class Kernel_ >
class xy_compare_2 {

public:

   //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! the kernel's point type
  typedef typename Kernel_::Point_2 Point_2;

  //! function call operator
  // (instead of int a 'enumeration is encouraged)
  int operator()(const Point_2& p, const Point_2& q) const {
    NT px = p.x();
    NT py = p.y();
    NT qx = q.x();
    NT qy = q.y();
    if (px < qx) { // assumes that NT has operator<(int)
      return -1;
    } else if (px > qx) { // assumes that NT has operator<(int)
      return 1;
    }
    else{
      if (py < qy) { // assumes that NT has operator<(int)
	return -1;
      } else if (py > qy) { // assumes that NT has operator<(int)
	return 1;
      }
      else{
	return 0;
      }
    }
  }
};

//! min_end functor
template < class Kernel_ >
class min_end_2 {

public:

   //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! the kernel's point type
  typedef typename Kernel_::Point_2 Point_2;

  //! function call operator
  // (instead of int a 'enumeration is encouraged)
  int operator()(const Segment_2& s) const {
    Point_2 p = s.p();
    qoint_2 q = s.q();
    if(xy_compare_2(p, q) != -1)
    { 
      return p;
    }
    else
    {
      return q;
    }
  }
};

//! max_end functor
template < class Kernel_ >
class max_end_2 {

public:

   //! this instance's template parameter
  typedef Kernel_ Kernel;

  //! the kernel's number type
  typedef typename Kernel_::NT NT;

  //! the kernel's point type
  typedef typename Kernel_::Point_2 Point_2;

  //! function call operator
  // (instead of int a 'enumeration is encouraged)
  int operator()(const Segment_2& s) const {
    Point_2 p = s.p();
    qoint_2 q = s.q();
    if(xy_compare_2(p, q) != 1)
    { 
      return p;
    }
    else
    {
      return q;
    }
  }
};

} // namespace internal


//! a simple cartesian kernel for points (and operations on them)
template < class NT_ >
class Cartesian_kernel_2 {

  public:

    //! this instance's number type
    typedef NT_ NT;

    //! the instantiated template
    typedef Cartesian_kernel_2< NT > Self;

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

