#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QList>
#include <QMap>

//собственная структура
struct Data {
public:
    QString key;
    double value;
};
//абстрактный класс
class IFileReader
{
public:
    virtual QList<Data> readFile(const QString) = 0;
    virtual ~IFileReader() {}
};
//наследники, конкретные классы, переропределяющие виртуальные методы
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
