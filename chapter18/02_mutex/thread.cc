#include <QMutexLocker>

#include <iostream>
#include "thread.h"


using namespace std;

Thread::Thread()
{
  stopped = false;
}

void
Thread::setMessage(const QString &message)
{
  messageStr = message;
}


void
Thread::stop()
{
//  mutex.lock();
  QMutexLocker locker(&mutex);
  stopped = true;
//  mutex.unlock();
}


void
Thread::run()
{
  forever {
    QMutexLocker locker(&mutex);
//    mutex.lock();
    if (stopped) {
      stopped = false;
//      mutex.unlock();
      break;
    }
//    mutex.unlock();
      
    cerr << qPrintable(messageStr);
  }
}

