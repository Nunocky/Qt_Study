#include <QtGui>
#include <QtWidgets>
#include <QtXml>

#include "domparser.h"

DomParser::DomParser(QIODevice *device, 
                     QTreeWidget *tree)
{
  treeWidget = tree;

  QString errorStr;
  int errorLine;
  int errorColumn;

  QDomDocument doc;
  if (!doc.setContent(device, true, &errorStr, &errorLine, &errorColumn)) {
    QMessageBox::warning(0,
                         QObject::tr("DOM Parser"),
                         QObject::tr("Parse error at line %1, column %2\n%3")
                         .arg(errorLine)
                         .arg(errorColumn)
                         .arg(errorStr));
    return;
  }

  QDomElement root = doc.documentElement();
  if (root.tagName() != "bookindex") {
    return;
  }

  QDomNode node = root.firstChild();
  while(!node.isNull()) {
    if (node.toElement().tagName() == "entry") {
      parseEntry(node.toElement(), 0);
    }
    node = node.nextSibling();
  }
}

void
DomParser::parseEntry(const QDomElement &element,
                      QTreeWidgetItem *parent)
{
  QTreeWidgetItem *item;
  if (parent) {
    item = new QTreeWidgetItem(parent);
  }
  else {
    item = new QTreeWidgetItem(treeWidget);
  }

  item->setText(0, element.attribute("term"));

  QDomNode node = element.firstChild();

  while(!node.isNull()) {
    if (node.toElement().tagName() == "entry") {
      parseEntry(node.toElement(), item);
    }
    else if (node.toElement().tagName() == "page") {
      QDomNode childNode = node.firstChild();
      while(!childNode.isNull()) {
        if (childNode.nodeType() == QDomNode::TextNode) {
          QString page = childNode.toText().data();
          QString allPages =  item->text(1);
          if (!allPages.isEmpty()) {
            allPages += ", ";
          }
          allPages += page;
          item->setText(1, allPages);
          break;
        }
        childNode = childNode.nextSibling();
      }
    }
    node = node.nextSibling();
  }
}
