#include "fileReader.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

QList<QMap<QString, QString>> SqliteFileReader::readFile(const QString& filePath)
{
    QList<QMap<QString, QString>> data;

    // Чтение файла с расширением .sqlite

    return data;
}

QList<QMap<QString, QString>> CsvFileReader::readFile(const QString& filePath)
{
    QList<QMap<QString, QString>> data;

    // Чтение файла с расширением .csv

    return data;
}
