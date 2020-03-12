#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QDialog>
#include <QMap>

class QIcon;
class QListWidget;
class QPushButton;

class FlowChartSymbolPicker : public QDialog
{
    Q_OBJECT

public:
    FlowChartSymbolPicker(const QMap<int, QString> &symbolMap,
                          QWidget *parent = 0);

    int selectedId() const { return id; }
    void done(int result);

private:
    QIcon iconForSymbol(const QString &symbolName);

    QListWidget *listWidget;
    QPushButton *okButton;
    QPushButton *cancelButton;
    int id;
};

#endif
