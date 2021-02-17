#ifndef FILECOPYER_H
#define FILECOPYER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QVector>
#include <QThread>
#include <profile.h>
#include <crypto/blockcipher.h>
#include <crypto/aes.h>

enum tENCRYPT_DECRYPT
{
    ENCRYPT, DECRYPT
};

class FileCopyer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint64 chunksize READ chunkSize WRITE setChunkSize)
    Q_PROPERTY(QVector<QString> sourcePaths READ sourcePaths WRITE setSourcePaths)
    Q_PROPERTY(QVector<QString> destinationPaths READ destinationPaths WRITE setDestinationPaths)

    static const int DEFAULT_CHUNK_SIZE = 126976;
    QVector<QString> src, dst;
    qint64 _chunk;

    encryptor::tPROFILE _prof;

public:
    explicit FileCopyer(QThread*, encryptor::tPROFILE*, QString* pw, tENCRYPT_DECRYPT);
    virtual ~FileCopyer();
    qint64 chunkSize() const { return _chunk; }

    void setChunkSize(qint64 ch) { _chunk = ch; }
    QVector<QString> sourcePaths() const { return src; }
    void setSourcePaths(const QVector<QString>& _src) { src = _src; }

    QVector<QString> destinationPaths() const { return dst; }
    void setDestinationPaths(const QVector<QString>& _dst) { dst = _dst; }

protected slots:
    void copy();

signals:
    void copyProgress(qint64, qint64);
    void finished(bool);
};

#endif // FILECOPYER_H
