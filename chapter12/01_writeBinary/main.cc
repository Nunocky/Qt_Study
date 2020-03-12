#include <QMap>
#include <QColor>
#include <QFile>
#include <QDataStream>

int main(int argc, char* argv[])
{
  QMap<QString, QColor> map;
  map.insert("red",   Qt::red);
  map.insert("green", Qt::green);
  map.insert("blue",  Qt::blue);

  QFile file("out.dat");
  if (!file.open(QIODevice::WriteOnly)) {
    return -1;
  }

  QDataStream out(&file);
  out.setVersion(QDataStream::Qt_5_14);

  out << quint32(0x12345678);
  out << map;

  return 0;
}
