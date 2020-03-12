#include <QtGui>
#include <QtWidgets>
#include <QUiLoader>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  QUiLoader uiloader;
  QFile file("sortdialog.ui");
  QWidget *sortDialog = uiloader.load(&file);

  if (sortDialog) {
    sortDialog->show();
  }

  return app.exec();
}
