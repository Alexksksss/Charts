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
    virtual QList<Data> readFile(const QString) = 0;
    virtual ~IFileReader() {}
};

class SqliteFileReader : public IFileReader
{
public:
    QList<Data> readFile(QString) override;
};

class JsonFileReader : public IFileReader
{
public:
    QList<Data> readFile(QString) override;
};

#endif // FILEREADER_H
