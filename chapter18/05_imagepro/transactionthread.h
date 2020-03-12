#ifndef TRANSACTIONTHREAD_H
#define TRANSACTIONTHREAD_H

#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QQueue>

class Transaction
{
public:
  virtual ~Transaction() { }

  virtual QImage apply(const QImage &image) = 0;
  virtual QString message() = 0;
};

class FlipTransaction : public Transaction
{
public:
  FlipTransaction(Qt::Orientation orientation);

  QImage apply(const QImage &image);
  QString message();

private:
  Qt::Orientation orientation;
};

class ResizeTransaction : public Transaction
{
public:
  ResizeTransaction(const QSize &size);

  QImage apply(const QImage &image);
  QString message();

private:
  QSize size;
};

class ConvertDepthTransaction : public Transaction
{
public:
  ConvertDepthTransaction(int depth);

  QImage apply(const QImage &image);
  QString message();

private:
  int depth;
};

class TransactionThread : public QThread
{
  Q_OBJECT

public:
  ~TransactionThread();
  void addTransaction(Transaction *transact);
  void setImage(const QImage &image);
  QImage image();

signals:
  void transactionStarted(const QString &message);
  void allTransactionsDone();

protected:
  void run();

private:
  QMutex mutex;
  QWaitCondition waitCondition;
  QImage currentImage;
  QQueue<Transaction *> transactions;
};

#endif
