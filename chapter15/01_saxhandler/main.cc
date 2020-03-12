#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif
#include <iostream>

#include "saxhandler.h"

using namespace std;

bool parseFile(const QString &fileName)
{
    QStringList labels;
    labels << QObject::tr("Terms") << QObject::tr("Pages");

    QTreeWidget *treeWidget = new QTreeWidget;
    treeWidget->setHeaderLabels(labels);
    treeWidget->setWindowTitle(QObject::tr("SAX Handler"));
    treeWidget->show();

    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;
    SaxHandler handler(treeWidget);
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    return reader.parse(inputSource);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.count() < 2) {
        cerr << "Usage: saxhandler file1.xml..." << endl;
        return 1;
    }

    for (int i = 1; i < args.count(); ++i)
        parseFile(args[i]);

    return app.exec();
}
