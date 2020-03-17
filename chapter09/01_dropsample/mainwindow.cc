#include <QtGui>
#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow()
{
  textEdit = new QTextEdit();
  setCentralWidget(textEdit);

  textEdit->setAcceptDrops(false);
  setAcceptDrops(true);

  setWindowTitle("Text Editor");
}

void
MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("text/uri-list")) {
    event->acceptProposedAction();
  }
}

void
MainWindow::dropEvent(QDropEvent *event)
{
  QList<QUrl> urls = event->mimeData()->urls();
  if (urls.isEmpty()) {
    return;
  }

  QString fileName = urls.first().toLocalFile();
  if (fileName.isEmpty()) {
    return;
  }

  if (readFile(fileName)) {
    setWindowTitle(tr("%1 - %2").arg(fileName).arg("Drag File"));
  }
}

bool
MainWindow::readFile(const QString &fileName)
{
  // TODO IMPLEMENT THIS
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly)) {
    return false;
  }

  QString str;

  QTextStream in(&file);
  str = in.readAll();

  textEdit->setText(str);


  return true;
}

