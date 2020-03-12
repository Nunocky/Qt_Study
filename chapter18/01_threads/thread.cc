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
  stopped = true;
}


void
Thread::run()
{
  while (!stopped) {
    cerr << qPrintable(messageStr);
  }

  stopped = false;
  cerr << endl;
}

