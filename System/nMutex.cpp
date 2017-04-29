// This is Windows Version Of Mutex

#include "System.hpp"

typedef struct           {
  CRITICAL_SECTION mutex ;
  int              count ;
} WindowMutex            ;

CA::Mutex:: Mutex       (void)
          : MutexPacket (NULL)
{
  setMutexType ( MutexDefault ) ;
}

CA::Mutex::~Mutex(void)
{
  releaseMutex ( ) ;
}

void CA::Mutex::Wait(void)
{
  ::Sleep ( 1 ) ;
}

void CA::Mutex::setMutexType(MutexType MT)
{
  Q_UNUSED ( MT )                                                ;
  ////////////////////////////////////////////////////////////////
  WindowMutex * WM = (WindowMutex *) MutexPacket                 ;
  if ( NULL != WM ) releaseMutex ( )                             ;
  ////////////////////////////////////////////////////////////////
  WM          = (WindowMutex *) ::malloc ( sizeof(WindowMutex) ) ;
  MutexPacket = WM                                               ;
  WM -> count = 0                                                ;
  ////////////////////////////////////////////////////////////////
  ::InitializeCriticalSection ( & ( WM -> mutex ) )              ;
}

void CA::Mutex::releaseMutex(void)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM ) return                       ;
  ::DeleteCriticalSection ( & ( WM -> mutex )  ) ;
  ::free                  ( MutexPacket        ) ;
  MutexPacket = NULL                             ;
}

int CA::Mutex::lock(void)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM      ) return 0                ;
  if ( WM -> count > 0 ) return 0                ;
  ::EnterCriticalSection ( & ( WM -> mutex ) )   ;
  WM -> count = 1                                ;
  return 1                                       ;
}

int CA::Mutex::unlock(void)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM       ) return 0               ;
  if ( WM -> count <= 0 ) return 1               ;
  ::LeaveCriticalSection ( & ( WM -> mutex ) )   ;
  WM -> count = 0                                ;
  return 1                                       ;
}

int CA::Mutex::locked(void)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM ) return 0                     ;
  return ( ( WM -> count ) > 0 )                 ;
}

int CA::Mutex::tryLock(void)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM ) return 0                     ;
  while ( ( WM -> count ) > 0 ) Wait ( )         ;
  return lock ( )                                ;
}

int CA::Mutex::tryLock(int msecs)
{
  WindowMutex * WM = (WindowMutex *) MutexPacket ;
  if ( NULL == WM ) return 0                     ;
  int cnt = 0                                    ;
  while ( ( WM -> count ) > 0 )                  {
    if ( cnt > msecs ) return 0                  ;
    Wait ( )                                     ;
    cnt++                                        ;
  }                                              ;
  return lock ( )                                ;
}
