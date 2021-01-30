#include <include/settings.h>
#include <iostream>

void
iSettings::getSettings(encryptor::tPROFILE& appProfile)
{
    Profile p((void**)&appProfile);
    iSettings s(p);

    s._appSettings->beginGroup("MAINUI");
    GETPROFILE()->_placement.setX(s._appSettings->value("winx").toInt());
    GETPROFILE()->_placement.setY(s._appSettings->value("winy").toInt());

    s._appSettings->endGroup();
    s._appSettings->beginGroup("ENCRPYOPTIONS");
    int mode = s._appSettings->value("mode").toInt();

    switch(mode) {
    case encryptor::MODE_ECB:
        GETPROFILE()->_mode = encryptor::MODE_ECB;
        break;

    case encryptor::MODE_CBC:
        GETPROFILE()->_mode = encryptor::MODE_CBC;
        break;

    case encryptor::MODE_CFB:
        GETPROFILE()->_mode = encryptor::MODE_CFB;
        break;

    case encryptor::MODE_OFB:
        GETPROFILE()->_mode = encryptor::MODE_OFB;
        break;

    case encryptor::MODE_CTR:
        GETPROFILE()->_mode = encryptor::MODE_CTR;
        break;

    default:
        GETPROFILE()->_mode = encryptor::MODE_CBC;
        break;
    }

    GETPROFILE()->_defProfile = s._appSettings->value("defProfile").toString();
    GETPROFILE()->_lastDir = s._appSettings->value("lastDir").toString();
    GETPROFILE()->_makeDefault = s._appSettings->value("makeDefault").toInt();

    GETPROFILE()->_preserveFile = s._appSettings->value("preserveFile").toInt();
    GETPROFILE()->_setTargetDir = s._appSettings->value("setTarget").toInt();
    GETPROFILE()->_targetDir = s._appSettings->value("targetDir").toString();

    s._appSettings->endGroup();
}

void
iSettings::putSettings(encryptor::tPROFILE& appProfile)
{
    Profile p((void**)&appProfile);
    iSettings s(p);

    s._appSettings->beginGroup("MAINUI");
    s._appSettings->setValue("winx", GETPROFILE()->_placement.x());
    s._appSettings->setValue("winy", GETPROFILE()->_placement.y());

    s._appSettings->endGroup();
    s._appSettings->beginGroup("ENCRPYOPTIONS");
    s._appSettings->setValue("mode", GETPROFILE()->_mode);

    s._appSettings->setValue("defProfile", GETPROFILE()->_defProfile);
    s._appSettings->setValue("lastDir", GETPROFILE()->_lastDir);
    s._appSettings->setValue("makeDefault", GETPROFILE()->_makeDefault);

    s._appSettings->setValue("preserveFile", GETPROFILE()->_preserveFile);
    s._appSettings->setValue("setTarget", GETPROFILE()->_setTargetDir);
    s._appSettings->setValue("targetDir", GETPROFILE()->_targetDir);

    s._appSettings->endGroup();
}
