#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QList>
#include <QMap>


struct Data {
public:
    QString key;
    double value;
};

class IFileReader
{
public:
    virtual QList<Data> readFile(const QString& filePath) = 0;
    virtual ~IFileReader() {}
};

class SqliteFileReader : public IFileReader
{
public:
    QList<Data> readFile(const QString& filePath) override;
};

class JsonFileReader : public IFileReader
{
public:
    QList<Data> readFile(const QString& filePath) override;
};

#endif // FILEREADER_H
