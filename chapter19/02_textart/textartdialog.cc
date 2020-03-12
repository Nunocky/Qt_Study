#include <QtGui>
#include <QtWidgets>

#include "textartdialog.h"
#include "textartinterface.h"

TextArtDialog::TextArtDialog(const QString &text, QWidget *parent)
  : QDialog(parent)
{
  listWidget = new QListWidget;
  listWidget->setViewMode(QListWidget::IconMode);
  listWidget->setMovement(QListWidget::Static);
  listWidget->setIconSize(QSize(260, 80));

  QPushButton *okButton = new QPushButton(tr("OK"));
  okButton->setDefault(true);

  QPushButton *cancelButton = new QPushButton(tr("Cancel"));

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

  loadPlugins();
  populateListWidget(text);

  setWindowTitle(tr("Text Art"));
}

QPixmap TextArtDialog::selectedPixmap() const
{
  if (!listWidget->currentItem())
    return QPixmap();

  return qvariant_cast<QPixmap>(
    listWidget->currentItem()->data(Qt::DecorationRole));
}

void TextArtDialog::loadPlugins()
{
  QDir pluginDir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
  if (pluginDir.dirName().toLower() == "debug"
      || pluginDir.dirName().toLower() == "release")
    pluginDir.cdUp();
#elif defined(Q_OS_MAC)
  if (pluginDir.dirName() == "MacOS") {
    pluginDir.cdUp();
    pluginDir.cdUp();
    pluginDir.cdUp();
  }
#endif
  if (!pluginDir.cd("plugins"))
    return;

  foreach (QString fileName, pluginDir.entryList(QDir::Files)) {
    QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
    if (TextArtInterface *interface =
        qobject_cast<TextArtInterface *>(loader.instance()))
      interfaces.append(interface);
  }
}

void TextArtDialog::populateListWidget(const QString &text)
{
  QSize iconSize = listWidget->iconSize();
  QPen pen(QColor("darkseagreen"));

  QLinearGradient gradient(0, 0, iconSize.width() / 2,
                           iconSize.height() / 2);
  gradient.setColorAt(0.0, QColor("darkolivegreen"));
  gradient.setColorAt(0.8, QColor("darkgreen"));
  gradient.setColorAt(1.0, QColor("lightgreen"));

  QFont font("Helvetica", iconSize.height(), QFont::Bold);

  foreach (TextArtInterface *interface, interfaces) {
    foreach (QString effect, interface->effects()) {
      QListWidgetItem *item = new QListWidgetItem(effect,
                                                  listWidget);
      QPixmap pixmap = interface->applyEffect(effect, text, font,
                                              iconSize, pen,
                                              gradient);
      item->setData(Qt::DecorationRole, pixmap);
    }
  }
  listWidget->setCurrentRow(0);
}
