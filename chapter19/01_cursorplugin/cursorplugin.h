#ifndef CURSORPLUGIN_H
#define CURSORPLUGIN_H

#include <QImageIOPlugin>

class CursorPlugin : public QImageIOPlugin
{
    Q_PLUGIN_METADATA(IID "com.software-inc.TextArt.QImageIOHandlerFactoryInterface" FILE "cursor.json")

public:
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format) const;
};

#endif
