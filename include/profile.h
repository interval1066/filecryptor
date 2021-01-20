#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

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
        tAESMODES mode;
        qint32 preserveFile;
        qint32 makeDefault;
        qint32 setTargetDir;
        QString targetDir;
        QString defProfile;
    };
}

#endif // PROFILE_H
