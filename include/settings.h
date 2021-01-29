#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFileInfo>
#include <memory>

#define GETPROFILE() static_cast<encryptor::tPROFILE*>(static_cast<void*>(s.getProfile()))

class Profile
{
    void** _profile;

public:
    explicit Profile(void** p) : _profile(p) {}
    void setProfile(void** p) { _profile = p; }
    void** getProfile(void) { return _profile; }
};

class iSettings
{
protected:
    std::unique_ptr<QSettings> _appSettings;
    std::unique_ptr<Profile> _profile;

public:
    iSettings(Profile& profile)
    {
        _appSettings = std::unique_ptr<QSettings>();
        _profile = std::make_unique<Profile>(profile);
    }

    ~iSettings()
    {
        _appSettings->sync();
    }

    void Init()
    {
        auto appname = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
        auto settings = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        _appSettings = std::make_unique<QSettings>();
    }

    void** getProfile(void) { return _profile.get()->getProfile(); }
};

#endif
