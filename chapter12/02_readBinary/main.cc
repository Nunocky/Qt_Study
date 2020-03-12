#include <cstdio>

#include <QMap>
#include <QColor>
#include <QFile>
#include <QDataStream>

int main(int argc, char* argv[])
{

  QFile file("out.dat");
  if (!file.open(QIODevice::ReadOnly)) {
    fprintf(stderr, "file open failed.\n");
    return -1;
  }
  
  QDataStream in(&file);
  in.setVersion(QDataStream::Qt_5_14);

  quint32 value;
  QMap<QString, QColor> map;
  
  in >> value;
  in >> map;

  printf("%x\n", value);

  return 0;
}
