#include <QtGui>
#include <QtWidgets>

#include "MyTableWidget.h"

MyTableWidget::MyTableWidget(QWidget *parent)
  : QTableWidget(parent)
{
}

void MyTableWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    startPos = event->pos();
  }
  QTableWidget::mousePressEvent(event);
}

void MyTableWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton) {
    int distance = (event->pos() - startPos).manhattanLength();
    if (distance >= QApplication::startDragDistance()) {
      startDrag();
    }
  }
}


void MyTableWidget::startDrag()
{
  QString plainText = selectionAsPlainText();

  if (plainText.isEmpty()) {
    return;
  }

  QMimeData *mimeData = new QMimeData;
  mimeData->setText(plainText);
  mimeData->setHtml(toHtml(plainText));
  mimeData->setData("text/csv", toCsv(plainText).toUtf8());

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  if (drag->start(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
    deleteSelection();
  }
}

QString MyTableWidget::selectionAsPlainText()
{
  return "Red\tGreen\tBlue\nCyan\tYellow\tMagenta";
}

void MyTableWidget::deleteSelection(void)
{
}

QString MyTableWidget::toCsv(const QString &plainText)
{
  QString result = plainText;

  result.replace("\\", "\\\\");
  result.replace("\"", "\\\"");
  result.replace("\t", "\", \"");
  result.replace("\n", "\"\n\"");
  result.prepend("\"");
  result.append("\"");
  return result;
}


QString MyTableWidget::toHtml(const QString &plainText)
{
  QString result = plainText.toHtmlEscaped();
  result.replace("\t","<td>");
  result.replace("\n","\n<tr><td>");
  result.prepend("<table>\n<tr><td>");
  result.append("\n</table>");

  return result;
}


