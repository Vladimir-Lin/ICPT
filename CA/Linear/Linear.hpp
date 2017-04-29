#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

namespace CA
{

class Vector
{
  public:

    explicit     Vector   (int items) ;
    explicit     Vector   (double * address) ;
    virtual     ~Vector   (void) ;

    virtual int  type     (void) const ;

  protected:

    double * V ;
    double * P ;

    virtual void allocate (int items) ;

  private:

} ;

}

#endif // LINEAR_ALGEBRA_HPP
