#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
  QFile file("sf-book.txt");

  if (!file.open(QIODevice::WriteOnly)) {
    return -1;
  }

  QTextStream out(&file);

  out << "Thomas M. Disch: " << 334 << endl;

  return 0;
}
