#include <QtGui>
#include <QtWidgets>

#include "flowchartsymbolpicker.h"


FlowChartSymbolPicker::FlowChartSymbolPicker(const QMap<int, QString> &symbolMap, QWidget *parent)
  : QDialog(parent)
{
  id = -1;

  listWidget = new QListWidget;
  listWidget->setIconSize(QSize(60, 60));

  QMapIterator<int, QString> i(symbolMap);

  while (i.hasNext()) {
    i.next();
    QListWidgetItem *item = new QListWidgetItem(i.value(), listWidget);
    item->setIcon(iconForSymbol(i.value()));
    item->setData(Qt::UserRole, i.key());
  }

  okButton = new QPushButton(tr("OK"));
  okButton->setDefault(true);

  cancelButton = new QPushButton(tr("Cancel"));

  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(okButton);
  buttonLayout->addWidget(cancelButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(listWidget);
  mainLayout->addLayout(buttonLayout);
  setLayout(mainLayout);

  setWindowTitle(tr("Flowchart Symbol Picker"));
}


void
FlowChartSymbolPicker::done(int result)
{
  id = -1;
  if (result == QDialog::Accepted) {
    QListWidgetItem *item = listWidget->currentItem();
    if (item) {
      id = item->data(Qt::UserRole).toInt();
    }
  }
  QDialog::done(result);
}


QIcon
FlowChartSymbolPicker::iconForSymbol(const QString &symbolName)
{
  QString fileName = ":/images/" + symbolName.toLower();
  fileName.replace(' ', '-');
  return QIcon(fileName);
}

