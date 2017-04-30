#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

namespace CA
{

class Vector
{
  public:

    explicit         Vector   (int items) ;
    explicit         Vector   (double * address) ;
    virtual         ~Vector   (void) ;

    virtual int      type     (void) const ;
    virtual double * values   (void) ;

  protected:

    double * V ;
    double * P ;

    virtual void     allocate (int items) ;

  private:

} ;

class Vector3 : public Vector
{
  public:

    explicit     Vector3     (void) ;
    virtual     ~Vector3     (void) ;

    virtual int  type        (void) const ;

    void         zero        (void) ;

    Vector3 &    operator += (Vector3 & v) ;
    Vector3 &    operator -= (Vector3 & v) ;

  protected:

  private:

} ;

class Vector4 : public Vector
{
  public:

    explicit     Vector4  (void) ;
    virtual     ~Vector4  (void) ;

    virtual int  type     (void) const ;

  protected:

  private:

} ;

}

#endif // LINEAR_ALGEBRA_HPP
