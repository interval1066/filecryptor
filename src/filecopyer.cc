#include <QDebug>
#include <filecopyer.h>
#include <crypto/aes256.h>
#include <crypto/byte_block.h>

FileCopyer::FileCopyer(QThread* _thread, QString& pw) //:
    : _keyBytes(pw)
{
    moveToThread(_thread);
    setChunkSize(DEFAULT_CHUNK_SIZE);
    QObject::connect(_thread, &QThread::started, this, &FileCopyer::copy);

    //uint8_t* initializationVector;
    std::string textInitializationVector;

    //QByteArray ba = pw->toLocal8Bit();
    //_keyBytes = (uint8_t*)strdup(ba.constData());
    _keyByteSize = sizeof(_keyBytes);

    QObject::connect(this, &FileCopyer::finished, _thread, &QThread::quit);
    QObject::connect(this, &FileCopyer::finished, this, &FileCopyer::deleteLater);
    QObject::connect(_thread, &QThread::finished, _thread, &QThread::deleteLater);

    //if(profile->_mode == encryptor::MODE_ECB)
      //  crypto::BlockCipher* algorithm = new crypto::AES(_keyBytes, _keyByteSize);
}

FileCopyer::~FileCopyer() { }

void FileCopyer::copy()
{
    if (src.isEmpty() || dst.isEmpty()) {
        qWarning() << QStringLiteral("source or destination paths are empty!");
        emit finished(false);
        return;
    }

    if (src.count() != dst.count()) {
        qWarning() << QStringLiteral("source or destination paths don't match!");
        emit finished(false);
        return;
    }

    qint64 total = 0, written = 0;
    for (auto&& f : src)
        total += QFileInfo(f).size();
    qInfo() << QStringLiteral("%1 bytes should be write in total").arg(total);

    crypto::AES256 aes(_keyBytes.toUtf8().constData());
    int indx = 0;
    //qInfo() << QStringLiteral("writing with chunk size of %1 byte").arg(chunkSize());
    while (indx < src.count()) {

        const auto dstPath = dst.at(indx);
        QFile srcFile(src.at(indx));
        QFile dstFile(dstPath);

        if (QFile::exists(dstPath)) {
            qInfo() << QStringLiteral("file %1 alreasy exists, overwriting...").arg(dstPath);
            QFile::remove(dstPath);
        }

        if (!srcFile.open(QFileDevice::ReadOnly)) {
            qWarning() << QStringLiteral("failed to open %1 (error:%1)").arg(srcFile.errorString());
            indx++;
            continue; // skip
        }

        if (!dstFile.open(QFileDevice::WriteOnly)) {
            qWarning() << QStringLiteral("failed to open %1 (error:%1)").arg(dstFile.errorString());
            indx++;
            continue; // skip
        }
        qInfo() << indx << " " << src.count();
        std::ifstream ifs(srcFile.fileName().toStdString().c_str(), std::ifstream::in);
        std::ofstream ofs(dstFile.fileName().toStdString().c_str(), std::ifstream::out);

        aes.encrypt(ifs, ofs);

        srcFile.close();
        dstFile.close();
        indx++;
    }

    if (total == written) {
        qInfo() << QStringLiteral("progress finished, %1 bytes of %2 has been written").arg(written).arg(total);
        emit finished(true);
    }
    else
        emit finished(false);
}
