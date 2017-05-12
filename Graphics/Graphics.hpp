#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <cmath>

#define FastCos cos
#define FastSin sin

#include "Linear.hpp"
#include "Geometry.hpp"
#include "Catastrophe.hpp"
#include "Physics.hpp"
#include "System.hpp"

namespace CA
{

class Material
{
  public:

    enum            {
      AMBIENT   = 0 ,
      DIFFUSE   = 1 ,
      SPECULAR  = 2 ,
      SHININESS = 3 ,
      EMISSION  = 4 ,
      ENABLING  = 5
    }               ;

    explicit           Material   (void) ;
    virtual           ~Material   (void) ;

    unsigned long long Id         (void) ;
    void               setId      (unsigned long long id) ;

    QString            Name       (void) const ;
    void               setName    (QString name) ;

    int                Face       (int index) const ;
    void               setFace    (int index,int face) ;

    Vector4          & Data       (int index) ;
    Vector4          & setData    (int    index ,
                                   double v1    ,
                                   double v2    ,
                                   double v3    ,
                                   double v4  ) ;

    bool               isEnabled  (int index) const ;
    bool               setEnabled (int index,bool enabled) ;

    void               Execute    (void) ;

  protected:

    QString            name            ;
    unsigned long long uuid            ;
    int                Faces     [ 5 ] ;
    bool               Booleans  [ 6 ] ;
    Vector4            Ambient         ;
    Vector4            Diffuse         ;
    Vector4            Specular        ;
    Vector4            Shininess       ;
    Vector4            Emission        ;

  private:

    void               Materialfv ( GLenum    face     ,
                                    GLenum    pname    ,
                                    Vector4 & params ) ;

} ;

class Light
{
  public:

    enum               {
      POSITION    =  0 ,
      SPOT        =  1 ,
      SPOTAT      =  2 ,
      AMBIENT     =  3 ,
      DIFFUSE     =  4 ,
      SPECULAR    =  5 ,
      CUTOFF      =  6 ,
      ATTENUATION =  7 ,
      COLORS      =  8 ,
      ACQUIRE     =  9 ,
      DELETION    = 10 ,
    }                  ;

    explicit           Light             (void) ;
    virtual           ~Light             (void) ;

    unsigned long long Id                (void) ;
    void               setId             (unsigned long long id) ;

    QString            Name              (void) const ;
    void               setName           (QString name) ;

    bool               isEnabled         (void) const ;
    int                LightIndex        (void) const ;
    void               setIndex          (int index) ;

    void               Enable            (void) ;
    void               Disable           (void) ;

    void               AssignPosition    (void) ;
    void               AssignColors      (void) ;
    void               AssignSpots       (void) ;
    void               AssignAttenuation (void) ;

    void               Execute           (void) ;

    Vector4          & Data              (int index) ;
    Vector4          & setData           (int    index ,
                                          double v1    ,
                                          double v2    ,
                                          double v3    ,
                                          double v4  ) ;
    bool               isEnabled         (int index) const ;
    bool               setEnabled        (int index,bool enabled) ;

  protected:

    QString            name           ;
    unsigned long long uuid           ;
    int                Index          ;
    bool               Booleans [ 5 ] ;
    Vector4            Position       ;
    Vector4            Direction      ;
    Vector4            SpotAt         ;
    Vector4            Ambient        ;
    Vector4            Diffuse        ;
    Vector4            Specular       ;
    Vector4            CutOff         ;
    Vector4            Attenuation    ;
    Vector4            DA             ;
    Vector4            DDS            ;

  private:

    void     Lightfv                     ( GLenum    light    ,
                                           GLenum    pname    ,
                                           Vector4 & params ) ;

} ;

class Lights
{
  public:

    bool    LocalViewer ;
    bool    TwoSides    ;
    Vector4 Ambient     ;

    explicit           Lights      (void) ;
    virtual           ~Lights      (void) ;

    unsigned long long MaxUuid     (void) ;

    void               Prepare     (void) ;

    void               Enable      (void) ;
    void               Disable     (void) ;
    void               LightModels (void) ;
    void               Lighting    (void) ;
    void               Execute     (void) ;

    int                count       (void) ;
    int                addLight    (Light * light) ;
    void               takeLight   (unsigned long long id) ;
    Light            * At          (unsigned long long id) ;
    Light            * Pos         (int index) ;

  protected:

    int            MaxLights ;
    QList<Light *> lights    ;

  private:

} ;

class Camera
{
  public:

    enum                {
      EYE         = 0   ,
      AT          = 1   ,
      UP          = 2   ,
      ORTHOGONAL  = 0   ,
      FRUSTUM     = 1   ,
      PERSPECTIVE = 2   ,
      NOTHING     = 0   ,
      LOOKAT      = 1 } ;

    explicit    Camera     (void) ;
    virtual    ~Camera     (void) ;

    Vector4   & value      (int index = EYE) ;

    void        setRegion  (QRectF & region) ;
    void        setRegion  (double left ,double top     ,
                            double width,double height) ;

    void        Orthogonal (double Left  , double Bottom , double Near  ,
                            double Right , double Top    , double Far ) ;
    void        Frustum    (double Left  , double Bottom , double Near  ,
                            double Right , double Top    , double Far ) ;
    void        Projection (double FOV                     ,
                            double width , double height   ,
                            double Near  , double Far    ) ;
    void        Projection (double FOV                     ,
                            double width , double height ) ;
    void        Projection (double FOV) ;
    void        Look       (Vector4 & Eye,Vector4 & At,Vector4 & Up) ;

    void        Prepare    (void) ;
    void        Push       (void) ;
    void        Pop        (void) ;

    void        LookAt     (void) ;
    void        Viewport   (void) ;

  protected:

    int       Mode    ;
    int       Stare   ;

    Vector4   Eye     ;
    Vector4   At      ;
    Vector4   Up      ;
    Vector4   From    ;
    Vector4   To      ;

    QRectF    Region  ;

    Matrix4x4 Project ;

    Matrix4x4 Model   ;
    Matrix4x4 GetIn   ;
    Matrix4x4 GetOut  ;

  private:

    void doOrthogonal      (void) ;
    void doFrustum         (void) ;
    void doPerspective     (void) ;

} ;

class Position
{
  public:

    Vector4 T ;
    Vector4 R ;
    Vector4 A ;
    Vector4 S ;

    explicit Position (void) ;
    virtual ~Position (void) ;

    void     Push     (void) ;
    void     Pop      (void) ;

  protected:

  private:

} ;

class Texture
{
  public:

    explicit Texture      (void) ;
    virtual ~Texture      (void) ;

    bool     loadResource (QString resource) ;
    bool     Bind         (void) ;
    bool     Release      (void) ;
    void     Render       (void) ;

  protected:

    GLuint   TID      ;
    QImage * Image    ;
    QSize    Original ;
    QSize    Size     ;

    bool     bindError    (void) ;
    bool     BindTexture  (QImage * image,GLuint & id) ;

  private:

    int      MipSize      (int size) ;
    QSize    MipSize      (QSize & size) ;

} ;

class Ball : public Ellipsoid
{
  public:

    explicit Ball           (void) ;
    virtual ~Ball           (void) ;

    bool     loadTexture    (QString res) ;

    void     DrawLongtitude (int x,int y) ;
    void     DrawLatitude   (int x,int y) ;
    void     DrawWire       (int x,int y) ;

    void     Render         (void) ;
    void     Surface        (void) ;

  protected:

    Vector4   radius  ;
    Texture * texture ;

    void     PushPoints     (int n,int gaps,double * points) ;

  private:

} ;

}

#endif // OBJECTS_HPP
