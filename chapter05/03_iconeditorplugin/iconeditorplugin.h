#ifndef ICONEDITORPLUGIN_H
#define ICONEDITORPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class IconEditorPlugin: public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "iconeditorplugin.json")
#endif

  Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
  IconEditorPlugin(QObject *parent=0);

  QString name() const;
  QString includeFile() const;
  QString group() const;
  QIcon icon() const;
  QString toolTip() const;
  QString whatsThis() const;
  bool isContainer() const;
  QWidget* createWidget(QWidget *parent);
};

#endif
