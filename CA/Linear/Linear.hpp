#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

namespace CA
{

class Vector  ;
class Vector3 ;
class Vector4 ;

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
                 Vector3     (Vector3 & v) ;
                 Vector3     (double a,double b,double c) ;
    virtual     ~Vector3     (void) ;

    virtual int  type        (void) const ;

    virtual void zero        (void) ;

    virtual void setValues   (double a,double b,double c) ;

    Vector3 &    operator  = (Vector3 & v) ;

    Vector3 &    operator /= (double v) ;
    Vector3 &    operator *= (double v) ;

    Vector3 &    operator += (Vector3 & v) ;
    Vector3 &    operator -= (Vector3 & v) ;

    double       dot         (Vector3 & v) ;
    Vector3      cross       (Vector3 & v) ;

    double       square      (void) ;
    double       length      (void) ;

    Vector3 &    normalize   (void) ;

  protected:

  private:

} ;

Vector3 operator + (Vector3 & a,Vector3 & b) ;
Vector3 operator - (Vector3 & a,Vector3 & b) ;
Vector3 operator * (Vector3 & a,double    b) ;
Vector3 operator / (Vector3 & a,double    b) ;
double  operator * (Vector3 & a,Vector3 & b) ;
Vector3 cross      (Vector3 & a,Vector3 & b) ;

class Vector4 : public Vector
{
  public:

    explicit     Vector4     (void) ;
                 Vector4     (Vector3 & v) ;
                 Vector4     (Vector4 & v) ;
                 Vector4     (double a,double b,double c,double d = 0) ;
    virtual     ~Vector4     (void) ;

    virtual int  type        (void) const ;

    virtual void zero        (void) ;

    virtual void setValues   (double a,double b,double c,double d) ;

    Vector4 &    operator  = (Vector4 & v) ;

    Vector4 &    operator /= (double v) ;
    Vector4 &    operator *= (double v) ;

    Vector4 &    operator += (Vector4 & v) ;
    Vector4 &    operator -= (Vector4 & v) ;

    double       dot         (Vector4 & v) ;
    Vector4      cross       (Vector4 & v) ;
    Vector4      cross       (Vector4 & v,double d) ;

    double       square      (void) ;
    double       length      (void) ;

    Vector4 &    normalize   (void) ;

  protected:

  private:

} ;

Vector4 operator + (Vector4 & a,Vector4 & b) ;
Vector4 operator - (Vector4 & a,Vector4 & b) ;
Vector4 operator * (Vector4 & a,double    b) ;
Vector4 operator / (Vector4 & a,double    b) ;
double  operator * (Vector4 & a,Vector4 & b) ;
Vector4 cross      (Vector4 & a,Vector4 & b) ;

}

#endif // LINEAR_ALGEBRA_HPP
