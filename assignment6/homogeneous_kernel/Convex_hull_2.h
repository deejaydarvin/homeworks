//! class stub for convex hull
template < class Kernel_ >
class Convex_hull_2 {
  
public:
  //! this instance's template parameter
  typedef Kernel_ Kernel_2;

  //! the kernel's point type
  typedef typename Kernel_2::Point_2 Point_2;

  //! function-call operator to compute lower envelope
  template < class InputIterator, class OutputIterator >
  OutputIterator operator()(InputIterator begin, InputIterator end,
                            OutputIterator result) {
    
    /* CONVEX HULL algorithm for points in [begin,end)
     */

    InputIterator it = begin;
    
    while (it != end) {
      
      Point_2 p = *it;
    
      // do process p


      // next 
      it++;
    }

    return result;
  }
  
};
