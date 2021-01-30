#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QPoint>

namespace encryptor
{
    enum tAESMODES
    {
        MODE_ECB = 0,
        MODE_CBC = 1,
        MODE_CFB = 2,
        MODE_OFB = 3,
        MODE_CTR = 4
    };

    struct tPROFILE
    {
        QPoint          _placement;
        tAESMODES       _mode;
        qint32          _preserveFile;
        qint32          _makeDefault;
        qint32          _setTargetDir;
        QString         _targetDir;
        QString         _defProfile;
        QString         _lastDir;
    };
}

#endif // PROFILE_H
