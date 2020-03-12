#include <QtCore>
#include <cstdlib>
#include <iostream>

using namespace std;

const int DataSize = 100000;
const int BufferSize = 4096;
char buffer[BufferSize];

QSemaphore freeSpace(BufferSize);
QSemaphore usedSpace(0);

class Producer : public QThread
{
public:
    void run();
};

void Producer::run()
{
  for (int i = 0; i < DataSize; ++i) {
    freeSpace.acquire();
    buffer[i % BufferSize] = "ACGT"[uint(rand()) % 4];
    usedSpace.release();
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
    usedSpace.acquire();
    cerr << buffer[i % BufferSize];
    freeSpace.release();
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
