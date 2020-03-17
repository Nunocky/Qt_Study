#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>

class MyTableWidget : public QTableWidget
{
  Q_OBJECT

public:
  MyTableWidget(QWidget *parent=0);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void startDrag(void);
  void dropEvent(QDropEvent *event);
  
private:
  QPoint startPos;

  QString selectionAsPlainText(void);
  void deleteSelection(void);
  QString toCsv(const QString &plainText);
  QString toHtml(const QString &plainText);

};


#endif
