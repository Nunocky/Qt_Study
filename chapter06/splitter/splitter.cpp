#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    QTextEdit *editor1 = new QTextEdit;
    QTextEdit *editor2 = new QTextEdit;
    QTextEdit *editor3 = new QTextEdit;

    QSplitter splitter(Qt::Horizontal);
    splitter.addWidget(editor1);
    splitter.addWidget(editor2);
    splitter.addWidget(editor3);

    editor1->setPlainText("Mon enfant, ma soeur,\n"
                          "Songe à la douceur\n"
                          "D'aller là-bas vivre ensemble,\n"
                          "Aimer à loisir,\n"
                          "Aimer et mourir\n"
                          "Au pays qui te ressemble.");
    editor2->setPlainText("My child, my sister,\n"
                          "think of the sweetness\n"
                          "of going there to live together!\n"
                          "To love at leisure,\n"
                          "to love and to die\n"
                          "in a country that is the image of you!");
    editor3->setPlainText("Mein Kind, meine Schwester,\n"
                          "denke an den Traum\n"
                          "dort hin(unter) zu gehen um zusammen\n"
                          "zu leben und in aller Ruhe zu lieben,\n"
                          "Zu lieben und zu sterben\n"
                          "in dem Land, das dir gleicht.");

    splitter.setWindowTitle(QObject::tr("Splitter"));
    splitter.show();
    return app.exec();
}
