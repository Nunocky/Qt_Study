#include <QtCore>
#include <cstdlib>
#include <iostream>

using namespace std;

const int DataSize = 100000;
const int BufferSize = 4096;
char buffer[BufferSize];

QWaitCondition bufferIsNotFull;
QWaitCondition bufferIsNotEmpty;
QMutex mutex;
int usedSpace = 0;

class Producer : public QThread
{
public:
  void run();
};

void Producer::run()
{
  for (int i = 0; i < DataSize; ++i) {
    mutex.lock();
    while (usedSpace == BufferSize) {
      bufferIsNotFull.wait(&mutex);
    }
    buffer[i % BufferSize] = "ACGT"[uint(rand()) % 4];
    ++usedSpace;
    bufferIsNotEmpty.wakeAll();
    mutex.unlock();
  }
}

class Consumer : public QThread
{
public:
  void run();
};

void Consumer::run()
{
  for (int i = 0; i < DataSize; ++i) {
    mutex.lock();
    while (usedSpace == 0) {
      bufferIsNotEmpty.wait(&mutex);
    }
    cerr << buffer[i % BufferSize];
    --usedSpace;
    bufferIsNotFull.wakeAll();
    mutex.unlock();
  }
  cerr << endl;
}

int main()
{
  Producer producer;
  Consumer consumer;
  producer.start();
  consumer.start();
  producer.wait();
  consumer.wait();
  return 0;
}
