#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <QtCore>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef unsigned long long               SUID        ; // Single Unique Identifier
typedef long long                        TUID        ; // Timestamp for Star date calendar
typedef long double                      MUID        ; // Timestamp for floating Star date calendar
typedef int                              CUID        ; // Type IDs : Language ID , Type ID and so on
typedef unsigned long long               FUID        ; // Flags
typedef QList     < bool               > BOOLs       ; // List of Boolean
typedef QList     < TUID               > TUIDs       ; // List of TUID
typedef QList     < CUID               > CUIDs       ; // List of Type IDs
typedef QMap      < QString , QString  > KMAPs       ; // String maps
typedef QMap      < QString , int      > UMAPs       ; // String maps to integer
typedef QMap      < QString , SUID     > ZMAPs       ; // String maps to SUID
typedef QMap      < QString , bool     > LMAPs       ; // String maps to bool
typedef QMap      < QString , double   > OMAPs       ; // String maps to double
typedef QMap      < QString , QVariant > WMAPs       ; // String maps to variant
typedef QMap      < SUID    , SUID     > SMAPs       ; // SUID conversion
typedef QMap      < SUID    , TUID     > GMAPs       ; // TUID conversion
typedef QMap      < SUID    , int      > RMAPs       ; // SUID maps to integer
typedef QMap      < SUID    , bool     > XMAPs       ; // UUID Boolean maps
typedef QMap      < SUID    , QString  > NAMEs       ; // SUID maps to name
typedef QMap      < int     , SUID     > CMAPs       ; // integer maps to SUID
typedef QMap      < int     , TUID     > YMAPs       ; // integer maps to TUID
typedef QMap      < int     , QString  > EMAPs       ; // int maps to QString
typedef QMap      < int     , bool     > BMAPs       ; // Boolean maps
typedef QMap      < int     , int      > IMAPs       ; // Integer maps
typedef QMap      < int     , double   > DMAPs       ; // Double maps
typedef QMap      < int     , void *   > HMAPs       ; // Hull maps
typedef QMap      < void *  , void *   > AMAPs       ; // Pointer to Pointer map
typedef QMultiMap < SUID    , SUID     > NMAPs       ; // Multi SUID maps
typedef QPair     < TUID    , SUID     > TMAP        ; // Time map
typedef QPair     < QString , QString  > VMAP        ; // String pair
typedef QPair     < int     , void *   > PMAP        ; // Property pair
typedef QList     < void    *          > VOIDs       ; // pointers
typedef QList     < TMAP               > TMAPs       ; // Time map items
typedef QList     < VMAP               > VMAPs       ; // String pairs
typedef QList     < PMAP               > PMAPs       ; // Property pairs
typedef QList     < QUrl               > URLs        ;
typedef QList     < QVariant           > QVariants   ;
typedef QStringList                      QStrings    ;
typedef QVector   < int                > VectorInt   ;
typedef QList     < QByteArray         > ByteArrays  ; // QByteArray lists
typedef QList     < QVariant           > VarArgs     ; // Variable paraments
typedef QList     < VarArgs            > VarArgLists ; // paraments list
typedef QList     < unsigned int       > Colors      ; // Color list

namespace CA
{

class Destroyer
{
  public:

    explicit     Destroyer  (void) ;
    virtual     ~Destroyer  (void) ;

    virtual bool Recycling  (void) ;
    virtual bool Destructor (void) ;

  protected:

  private:

} ;

class Mutex
{
  public:

    enum MutexType    {
      MutexDefault    ,
      MutexNormal     ,
      MutexErrorCheck ,
      MutexRecursive
    }                 ;

    explicit     Mutex        (void) ;
    virtual     ~Mutex        (void) ;

    void         setMutexType (MutexType MT) ;

    int          lock         (void) ;
    int          unlock       (void) ;
    int          locked       (void) ;
    int          tryLock      (void) ;
    int          tryLock      (int msecs) ;

  protected:

    void         releaseMutex (void) ;

    virtual void Wait         (void) ;

  private:

    void * MutexPacket ;

} ;

#ifdef Q_OS_WIN
#define THREADSTACKSIZE ( 16 * 1024 * 1024 )
typedef unsigned int (*ThreadFunction)(LPVOID arg) ;
#endif

class ThreadData
{
  public:

    enum ThreadState {
      Idle     = 0   ,
      Active   = 1   ,
      Deactive = 2   ,
      Recycle  = 3 } ;

    int            Id          ;
    int            Type        ;
    int            Priority    ;
    int            Status      ;
    int            Running     ;
    QVariants      Arguments   ;
    WMAPs          Properties  ;
    int            StackSize   ;
    bool           Reservation ;
    bool           isContinue  ;
    bool         * Controller  ;
    void         * Extra       ;

    #ifdef Q_OS_WIN
    HANDLE         Thread      ;
    DWORD          ThreadID    ;
    unsigned int   dwThreadID  ;
    #endif
    ThreadFunction Function    ;

    explicit         ThreadData  (void) ;
    virtual         ~ThreadData  (void) ;

    void             Start       (void) ;
    void             Stop        (void) ;
    void             Join        (void) ;
    bool             yield       (void) ;
    bool             cancel      (void) ;
    void             TryCancel   (void) ;

    int              setPriority (int priority) ;

    #ifdef Q_OS_WIN
    static DWORD     ThreadId    (void) ;
    #endif

    bool             isSelf      (void) ;

    bool             Run         (void * data) ;
    bool             Go          (void * data) ;

} ;

class Thread
{
  public:

    int                   running     ;
    int                   StackSize   ;
    bool                  isContinue  ;
    bool                  Reservation ;
    ThreadData            Data        ;
    QList<ThreadData *>   AllThreads  ;

    explicit  Thread                   (int stackSize,bool reservation) ;
    explicit  Thread                   (void) ;
    virtual ~ Thread                   (void) ;

    int                   setPriority  (int priority) ;

    virtual void          start        (void) ;
    virtual ThreadData  * start        (int Type) ;
    virtual ThreadData  * start        (int Type,QVariants    & arguments) ;
    virtual ThreadData  * start        (int Type,ThreadFunction ExternalThread) ;
    virtual ThreadData  * drawer       (void) ;
    virtual int           DrawerId     (void) ;
    virtual void          quit         (void) ;
    virtual void          suspend      (void) ;
    virtual void          resume       (void) ;
    virtual void          terminate    (void) ;
    virtual void          cleanup      (void) ;
    virtual bool          proceed      (void) ;
    virtual bool          finalize     (int interval = 20) ;
    virtual bool          NotStopped   (void) ;
    virtual bool          IsContinue   (void) ;
    virtual bool          IsContinue   (bool go) ;
    virtual bool          IsContinue   (int Id) ;
    virtual bool          IsContinue   (ThreadData * data) ;
    virtual bool          IsContinue   (bool go,ThreadData * data) ;
    virtual bool          IsContinue   (int action,ThreadData * data) ;
    virtual int           IsRunning    (QList<ThreadData *> & threads,bool purge = false) ;
    virtual int           exit         (int exitcode) ;

    void                  actualRun    (void) ;
    void                  actualRun    (int Type,ThreadData * data) ;
    void                  actualJoin   (void) ;

    #ifdef Q_OS_WIN
    HANDLE                Id           (void) ;
    #endif

    static  void          msleep       (int msecs) ;
    static  void          skip         (int msecs) ;

  protected:

    virtual void          ThreadEvent  (void) ;
    virtual void          run          (void) ;
    virtual void          run          (int Type,ThreadData * Data) ;

    virtual bool          detection    (void) ;
    virtual bool          recycle      (void) ;

  private:

    QMutex * tsLocker ;

    #ifdef Q_OS_WIN
    static unsigned int   SingleThread (LPVOID arg) ;
    static unsigned int   MultiThread  (LPVOID arg) ;
    #endif

} ;

}

#endif // SYSTEM_HPP
