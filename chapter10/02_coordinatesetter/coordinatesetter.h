#ifndef COORDINATESETTER_H
#define COORDINATESETTER_H

#include <QDialog>
#include <QList>
#include <QPointF>

class QPushButton;
class QTableWidget;

class CoordinateSetter : public QDialog
{
    Q_OBJECT

public:
    CoordinateSetter(QList<QPointF> *coords, QWidget *parent = 0);

    void done(int result);

private slots:
    void addRow();

private:
    QTableWidget *tableWidget;
    QPushButton *addRowButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QList<QPointF> *coordinates;
};

#endif
