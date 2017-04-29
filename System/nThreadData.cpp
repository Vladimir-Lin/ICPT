// This is Windows Version Of Thread Data

#include "System.hpp"

#include <process.h>

CA::ThreadData:: ThreadData  ( void  )
               : Id          ( 0     )
               , Type        ( 0     )
               , Priority    ( 0     )
               , Status      ( 0     )
               , Running     ( Idle  )
               , StackSize   ( 0     )
               , Reservation ( false )
               , isContinue  ( true  )
               , Controller  ( NULL  )
               , Extra       ( NULL  )
{
}

CA::ThreadData::~ThreadData (void)
{
}

void CA::ThreadData::Start(void)
{
  Running = Active   ;
}

void CA::ThreadData::Stop(void)
{
  Running = Deactive ;
}

void CA::ThreadData::Join(void)
{
  if ( Running != Deactive ) return           ;
  ::WaitForSingleObject ( Thread , INFINITE ) ;
  Running = Recycle                           ;
}

bool CA::ThreadData::yield(void)
{
  return (bool)::SwitchToThread ( ) ;
}

bool CA::ThreadData::cancel(void)
{
  return false ;
}

void CA::ThreadData::TryCancel(void)
{
}

int CA::ThreadData::setPriority(int priority)
{
  Priority = priority                        ;
  ::SetThreadPriority  ( Thread , priority ) ;
  return priority                            ;
}

DWORD CA::ThreadData::ThreadId(void)
{
  DWORD TID = ::GetCurrentThreadId ( ) ;
  return TID                           ;
}

bool CA::ThreadData::isSelf(void)
{
  return ( ThreadId() == ThreadID ) ;
}

bool CA::ThreadData::Run(void * data)
{
  int ss = 0                                                        ;
  if ( Reservation ) ss = StackSize                                 ;
  #ifdef Q_OS_WIN64
  Thread = (HANDLE) ::_beginthreadex                                (
                      NULL                                          ,
                      ss                                            ,
                      Function                                      ,
                      (LPVOID) data                                 ,
                      0                                             ,
                      & dwThreadID                                ) ;
  #elif Q_OS_WIN32
  Thread = (HANDLE) ::_beginthreadex                                (
                      NULL                                          ,
                      ss                                            ,
                      (unsigned int (__stdcall *)(void *)) Function ,
                      (LPVOID) data                                 ,
                      0                                             ,
                      & dwThreadID                                ) ;
  #endif
  return ( NULL != Thread )                                         ;
}

bool CA::ThreadData::Go(void * data)
{
  if ( Active == Running ) return false ;
  do                                    {
    if ( ! Run ( data ) )               {
      ::Sleep ( 5 )                     ;
    }                                   ;
  } while ( NULL == Thread )            ;
  Status = 0                            ;
  return true                           ;
}
