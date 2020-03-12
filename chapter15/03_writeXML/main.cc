#include <QtGui>
#include <QtWidgets>
#include <QDomDocument>

int main(int argc, char* argv[])
{
  const int Indent = 4;
  
  QDomDocument doc;
  QDomElement root = doc.createElement("doc");
  QDomElement quote = doc.createElement("quote");
  QDomElement translation = doc.createElement("translation");
  QDomText latin = doc.createTextNode("Ars longa vita brevis");
  QDomText english = doc.createTextNode("Art if long, life is short");

  doc.appendChild(root);
  root.appendChild(quote);
  root.appendChild(translation);
  quote.appendChild(latin);
  translation.appendChild(english);

  QFile file("out.xml");
  if (!file.open(QIODevice::WriteOnly)) {
    return -1;
  }

  QTextStream out(&file);
  doc.save(out, Indent);

  return 0;
}
