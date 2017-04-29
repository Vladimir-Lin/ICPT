// This is Windows Version Of Thread

#include "System.hpp"

#include <process.h>

#ifdef QT_DEBUG
#define TRACECLASSES 1
#endif

CA::Thread:: Thread      (int stackSize,bool reservation)
           : running     ( 0                            )
           , StackSize   ( stackSize                    )
           , isContinue  ( true                         )
           , Reservation ( reservation                  )
{
  Data . Properties [ "Class" ] = QVariant(QString("CA::Thread")) ;
  tsLocker = new QMutex ( )                                      ;
}

CA::Thread:: Thread      ( void            )
           : running     ( 0               )
           , isContinue  ( true            )
           , StackSize   ( THREADSTACKSIZE )
           , Reservation ( false           )
{
  Data . Properties [ "Class" ] = QVariant(QString("CA::Thread")) ;
  tsLocker = new QMutex ( )                                      ;
}

CA::Thread::~Thread(void)
{
  #ifdef TRACECLASSES
  QString cns = Data.Properties["Class"].toString()           ;
  CA::printf(QString("%1(%2) => %3").arg(FunctionString).arg(cns).arg(running),true,true) ;
  if ( AllThreads . count ( ) > 0 )                           {
    for (int i=0;i<AllThreads.count();i++)                    {
      ThreadData * d = AllThreads[i]                          ;
      CA::printf(QString("%1 => %2(%3)").arg(d->Id).arg(d->Type).arg(d->Running),true,true) ;
    }                                                         ;
  }                                                           ;
  CA::printf ( QString("%1 finalize").arg(cns) , true , true ) ;
  #endif
  finalize ( 5 )  ;
  delete tsLocker ;
  #ifdef TRACECLASSES
  CA::printf(QString("%1 stopped").arg(cns),true,true)         ;
  #endif
}

int CA::Thread::setPriority(int priority)
{
  return Data . setPriority ( priority ) ;
}

void CA::Thread::start(void)
{
  if ( running == 1 ) return                ;
  ///////////////////////////////////////////
  while ( ! recycle ( ) ) skip ( 100 )      ;
  ///////////////////////////////////////////
  Data . Running     = 0                    ;
  Data . Extra       = this                 ;
  Data . Function    = Thread::SingleThread ;
  Data . StackSize   = StackSize            ;
  Data . Reservation = Reservation          ;
  ///////////////////////////////////////////
  Data . Go ( this )                        ;
}

CA::ThreadData * CA::Thread::start(int Type)
{
  return start(Type,CA::Thread::MultiThread) ;
}

CA::ThreadData * CA::Thread::start(int Type,VarArgs & arguments)
{
  cleanup ( )                                ;
  ThreadData * data = new ThreadData ( )     ;
  ThreadData * last = NULL                   ;
  tsLocker -> lock   ( )                     ;
  if ( AllThreads . count ( ) > 0 )          {
    last = AllThreads . last ( )             ;
  }                                          ;
  tsLocker -> unlock ( )                     ;
  ////////////////////////////////////////////
  data -> Running      = 0                   ;
  data -> Type         = Type                ;
  data -> Function     = Thread::MultiThread ;
  data -> Arguments    = arguments           ;
  data -> Extra        = this                ;
  data -> StackSize    = StackSize           ;
  data -> Reservation  = Reservation         ;
  data -> Controller   = Data . Controller   ;
  ////////////////////////////////////////////
  if ( NULL != last )                        {
    data -> Id = last -> Id + 1              ;
  } else data -> Id = 1                      ;
  ////////////////////////////////////////////
  if ( ! data -> Go ( data ) )               {
    delete data                              ;
    return NULL                              ;
  }                                          ;
  tsLocker -> lock   ( )                     ;
  AllThreads << data                         ;
  tsLocker -> unlock ( )                     ;
  ////////////////////////////////////////////
  return data                                ;
}

CA::ThreadData * CA::Thread::start(int Type,CA::ThreadFunction ExternalThread)
{
  cleanup ( )                              ;
  ThreadData * data = new ThreadData ( )   ;
  ThreadData * last = NULL                 ;
  tsLocker -> lock   ( )                   ;
  if ( AllThreads . count ( ) > 0 )        {
    last = AllThreads . last ( )           ;
  }                                        ;
  tsLocker -> unlock ( )                   ;
  //////////////////////////////////////////
  data -> Running      = 0                 ;
  data -> Type         = Type              ;
  data -> Function     = ExternalThread    ;
  data -> Extra        = this              ;
  data -> StackSize    = StackSize         ;
  data -> Reservation  = Reservation       ;
  data -> Controller   = Data . Controller ;
  //////////////////////////////////////////
  if ( NULL != last )                      {
    data->Id = last->Id + 1                ;
  } else data->Id = 1                      ;
  //////////////////////////////////////////
  if ( ! data -> Go ( data ) )             {
    delete data                            ;
    return NULL                            ;
  }                                        ;
  tsLocker -> lock   ( )                   ;
  AllThreads << data                       ;
  tsLocker -> unlock ( )                   ;
  //////////////////////////////////////////
  return data                              ;
}

CA::ThreadData * CA::Thread::drawer(void)
{
  if ( Data . isSelf ( ) ) return &Data                                     ;
  ThreadData * ti = NULL                                                    ;
  tsLocker -> lock   ( )                                                    ;
  for (int i = 0 ; ( NULL == ti ) && ( i < AllThreads . count ( ) ) ; i++ ) {
    if ( AllThreads [ i ] -> isSelf ( ) )                                   {
      ti = AllThreads [ i ]                                                 ;
    }                                                                       ;
  }                                                                         ;
  tsLocker -> unlock ( )                                                    ;
  return ti                                                                 ;
}

int CA::Thread::DrawerId(void)
{
  ThreadData * td = drawer ( ) ;
  if ( NULL == td ) return -1  ;
  return td -> Id              ;
}

bool CA::Thread::NotStopped(void)
{
  if ( ! isContinue              ) return false ;
  if ( NULL == Data . Controller ) return true  ;
  return * ( Data . Controller )                ;
}

bool CA::Thread::IsContinue(void)
{
  if ( ! isContinue                   ) return false ;
  if ( NULL != Data . Controller )                   {
    if ( ! ( *( Data . Controller ) ) ) return false ;
  }                                                  ;
  ////////////////////////////////////////////////////
  ThreadData * d = drawer ( )                        ;
  if ( NULL == d                      ) return false ;
  if ( ! d -> isContinue ) return false              ;
  if ( NULL != d -> Controller )                     {
    if ( ! ( *( d -> Controller   ) ) ) return false ;
  }                                                  ;
  return true                                        ;
}

bool CA::Thread::IsContinue(int Id)
{
  if ( ! isContinue                   ) return false     ;
  if ( NULL != Data . Controller )                       {
    if ( ! ( *( Data . Controller ) ) ) return false     ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  for (int i = 0 ; i < AllThreads . count ( ) ; i++ )    {
    if ( Id == AllThreads [ i ] -> Id )                  {
      ThreadData * d = AllThreads [ i ]                  ;
      if ( ! d -> isContinue ) return false              ;
      if ( NULL != d -> Controller )                     {
        if ( ! ( *( d -> Controller   ) ) ) return false ;
      }                                                  ;
      return true                                        ;
    }                                                    ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  return ( Id == Data . Id )                             ;
}

bool CA::Thread::IsContinue(ThreadData * d)
{
  if ( ! isContinue      ) return false              ;
  if ( NULL == d         ) return false              ;
  if ( ! d -> isContinue ) return false              ;
  ////////////////////////////////////////////////////
  if ( NULL != d -> Controller )                     {
    if ( ! ( *( d -> Controller   ) ) ) return false ;
  }                                                  ;
  ////////////////////////////////////////////////////
  if ( NULL != Data . Controller )                   {
    if ( ! ( *( Data . Controller ) ) ) return false ;
  }                                                  ;
  ////////////////////////////////////////////////////
  return true                                        ;
}

bool CA::Thread::IsContinue(int action,ThreadData * d)
{ Q_UNUSED          ( action ) ;
  return IsContinue ( d      ) ;
}

bool CA::Thread::IsContinue(bool go)
{
  if ( ! go ) return false ;
  return IsContinue ( )    ;
}

bool CA::Thread::IsContinue(bool go,ThreadData * d)
{
  if ( ! go ) return false ;
  return IsContinue ( d )  ;
}

int CA::Thread::IsRunning(QList<ThreadData *> & threads,bool purge)
{
  if ( threads . count ( ) <= 0 ) return 0          ;
  ///////////////////////////////////////////////////
  int                 count = 0                     ;
  QList<ThreadData *> stopped                       ;
  for (int i = 0 ; i < threads . count ( ) ; i++ )  {
    int R = threads [ i ] -> Running                ;
    switch ( R )                                    {
      case ThreadData::Idle                         :
      case ThreadData::Recycle                      :
      break                                         ;
      case ThreadData::Active                       :
        count ++                                    ;
      break                                         ;
      case ThreadData::Deactive                     :
        stopped << threads [ i ]                    ;
      break                                         ;
    }                                               ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( ! purge ) return count                       ;
  ///////////////////////////////////////////////////
  for (int i = 0 ; i < stopped . count ( ) ; i++ )  {
    int index = threads . indexOf ( stopped [ i ] ) ;
    if ( index >= 0 ) threads . takeAt ( index )    ;
  }                                                 ;
  ///////////////////////////////////////////////////
  return count                                      ;
}

unsigned int CA::Thread::SingleThread(void * arg)
{
  Thread     * nthread  = (Thread     *) arg                   ;
  ThreadData * data     = (ThreadData *) & ( nthread -> Data ) ;
  ::srand                 ( ::time ( NULL ) )                  ;
  ::srand                 ( ::rand (      ) )                  ;
  nthread -> Data . ThreadID = ThreadData::ThreadId ( )        ;
  nthread -> running  = ThreadData::Active                     ;
  nthread -> Data . Start (                 )                  ;
  nthread -> actualRun    (                 )                  ;
  nthread -> Data . Stop  (                 )                  ;
  nthread -> running  = ThreadData::Deactive                   ;
  ::_endthreadex          ( 0               )                  ;
  return 0                                                     ;
}

unsigned int CA::Thread::MultiThread(void * arg)
{
  ThreadData * data    = (ThreadData *) arg         ;
  Thread     * nthread = (Thread     *) data->Extra ;
  ::srand              ( ::time ( NULL )     )      ;
  ::srand              ( ::rand (      )     )      ;
  data    -> ThreadID = ThreadData::ThreadId ( )    ;
  data    -> Start     (                     )      ;
  nthread -> actualRun ( data -> Type , data )      ;
  data    -> Stop      (                     )      ;
  ::_endthreadex       ( 0                   )      ;
  return 0                                          ;
}

void CA::Thread::quit(void)
{
}

void CA::Thread::suspend(void)
{
  ::SuspendThread(Data.Thread);
}

void CA::Thread::resume(void)
{
  ::ResumeThread(Data.Thread);
}

void CA::Thread::terminate(void)
{
  ::WaitForSingleObject(Data.Thread,INFINITE);
}

bool CA::Thread::proceed(void)
{
  return true ;
}

int CA::Thread::exit(int exitcode)
{
  ::ExitThread(exitcode);
}

void CA::Thread::actualRun(void)
{
  run();
}

void CA::Thread::actualRun(int Type,CA::ThreadData * data)
{
  run ( Type , data ) ;
}

void CA::Thread::ThreadEvent(void)
{
}

void CA::Thread::run(void)
{
}

void CA::Thread::run(int Type,CA::ThreadData * data)
{
  Q_UNUSED(Type) ;
  Q_UNUSED(data) ;
}

void CA::Thread::actualJoin(void)
{
  ::WaitForSingleObject(Data.Thread,INFINITE) ;
  running = 3                                 ;
}

bool CA::Thread::detection(void)
{
  if ( finalize ( 5 ) ) return false ;
  if ( running == 0   ) return false ;
  return ( running == 1 )            ;
}

bool CA::Thread::recycle(void)
{
  if (running==0) return true  ;
  if (running==1) return false ;
  if (running==2) actualJoin() ;
  if (running==3) running = 0  ;
  return (running==0)          ;
}

void CA::Thread::cleanup(void)
{
  QList<CA::ThreadData *> Dead                        ;
  tsLocker -> lock   ( )                              ;
  for (int i=0;i<AllThreads.count();i++)              {
    if (AllThreads[i]->Running==ThreadData::Deactive) {
      Dead << AllThreads[i]                           ;
    }                                                 ;
  }                                                   ;
  tsLocker -> unlock ( )                              ;
  if (Dead.count()<=0) return                         ;
  for (int i=0;i<Dead.count();i++)                    {
    CA::ThreadData * data = Dead[i]                   ;
    int           index                               ;
    data -> Join ( )                                  ;
    tsLocker -> lock   ( )                            ;
    index = AllThreads.indexOf(data)                  ;
    if (index>=0)                                     {
      AllThreads . takeAt ( index )                   ;
      delete data                                     ;
    }                                                 ;
    tsLocker -> unlock ( )                            ;
  }                                                   ;
}

bool CA::Thread::finalize(int interval)
{
  isContinue = false                             ;
  while ( ( ThreadData::Idle != running )       ||
          ( AllThreads . count ( ) > 0  )      ) {
    //////////////////////////////////////////////
    switch ( running )                           {
      case ThreadData::Idle                      :
      case ThreadData::Active                    :
      break                                      ;
      case ThreadData::Deactive                  :
        Data . Join ( )                          ;
        running = ThreadData::Recycle            ;
      break                                      ;
      case ThreadData::Recycle                   :
        running = ThreadData::Idle               ;
      break                                      ;
    }                                            ;
    //////////////////////////////////////////////
    if ( AllThreads . count ( ) > 0 )            {
      ThreadData * data = NULL                   ;
      tsLocker -> lock   ( )                     ;
      data = AllThreads . last ( )               ;
      tsLocker -> unlock ( )                     ;
      if ( NULL != data )                        {
        int tid                                  ;
        switch ( data -> Running )               {
          case ThreadData::Idle                  :
          case ThreadData::Active                :
          break                                  ;
          case ThreadData::Deactive              :
            data -> Join ( )                     ;
          break                                  ;
          case ThreadData::Recycle               :
            tsLocker -> lock   ( )               ;
            tid = AllThreads . indexOf ( data )  ;
            if ( tid >= 0 )                      {
              AllThreads . takeAt ( tid )        ;
            }                                    ;
            tsLocker -> unlock ( )               ;
            delete data                          ;
          break                                  ;
        }                                        ;
      } else                                     {
        tsLocker -> lock   ( )                   ;
        AllThreads . takeFirst ( )               ;
        tsLocker -> unlock ( )                   ;
      }                                          ;
    }                                            ;
    //////////////////////////////////////////////
    msleep      ( interval )                     ;
    ThreadEvent (          )                     ;
  }                                              ;
  return true                                    ;
}

HANDLE CA::Thread::Id(void)
{
  return Data . Thread ;
}

void CA::Thread::msleep(int msecs)
{
  ::Sleep ( msecs ) ;
}

void CA::Thread::skip(int msecs)
{
  QDateTime N = QDateTime::currentDateTime ( )                     ;
  while ( N . msecsTo ( QDateTime::currentDateTime ( ) ) < msecs ) {
    qApp -> processEvents ( )                                      ;
    ::Sleep ( 1 )                                                  ;
  }                                                                ;
}
