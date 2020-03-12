#ifndef DOMPARSER_H
#define DOMPARSER_H

class QDomElement;
class QIODevice;
class QTreeWidget;
class QTreeWidgetItem;

class DomParser
{
public:
  DomParser(QIODevice *device, QTreeWidget *tree);

private:
  void parseEntry(const QDomElement &element,
                  QTreeWidgetItem   *parent);

  QTreeWidget *treeWidget;
  
};

#endif
