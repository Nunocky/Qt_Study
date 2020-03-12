#ifndef TEXTARTDIALOG_H
#define TEXTARTDIALOG_H

#include <QDialog>
#include <QList>

class QListWidget;
class TextArtInterface;

class TextArtDialog : public QDialog
{
    Q_OBJECT

public:
    TextArtDialog(const QString &text, QWidget *parent = 0);

    QPixmap selectedPixmap() const;

private:
    void loadPlugins();
    void populateListWidget(const QString &text);

    QListWidget *listWidget;
    QList<TextArtInterface *> interfaces;
};

#endif
