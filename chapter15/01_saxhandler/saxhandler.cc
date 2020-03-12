#include <QtGui>
#include <QtWidgets>

#include "saxhandler.h"


SaxHandler::SaxHandler(QTreeWidget *tree)
{
  treeWidget = tree;
  currentItem = 0;
}

bool 
SaxHandler::startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &attributes)
{
  if (qName == "entry") {
    if (currentItem) {
      currentItem = new QTreeWidgetItem(currentItem);
    }
    else {
      currentItem = new QTreeWidgetItem(treeWidget);
    }

    currentItem->setText(0, attributes.value("term"));

  }
  else if (qName == "page") {
    currentText.clear();
  }

  return true;
}


bool 
SaxHandler::endElement(const QString &namespaceURI,
                       const QString &localName,
                       const QString &qName)
{
  if (qName == "entry") {
    currentItem = currentItem->parent();
  }
  else if (qName == "page") {
    if (currentItem) {
      QString allPages = currentItem->text(1);
      if(!allPages.isEmpty()) {
        allPages += ", ";
      }
      allPages += currentText;
      currentItem->setText(1, allPages);
    }
  }

  return true;
}


bool 
SaxHandler::characters(const QString &str)
{
  currentText += str;
  return true;
}

bool 
SaxHandler::fatalError(const QXmlParseException &exception)
{
  return false;
}
