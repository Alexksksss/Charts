#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QList>
#include <QMap>

class IFileReader
{
public:
    virtual QList<QMap<QString, QString>> readFile(const QString& filePath) = 0;
    virtual ~IFileReader() {}
};

class SqliteFileReader : public IFileReader
{
public:
    QList<QMap<QString, QString>> readFile(const QString& filePath) override;
};

class JsonFileReader : public IFileReader
{
public:
    QList<QMap<QString, QString>> readFile(const QString& filePath) override;
};

#endif // FILEREADER_H
