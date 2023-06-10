#include "fileReader.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QWidget>

QList<Data> SqliteFileReader::readFile(const QString& filePath)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE"); //создаем соединение по умолчанию с драйвером "QSQLITE"
    // устанавливаем связь
    dbase.setDatabaseName(filePath);
    QList<Data> data;

    if (dbase.open()) {
        // делаем запрос
        QSqlQuery query ("SELECT * FROM " + dbase.tables().takeFirst());
        int i = 0; // счетчик данных
        while (query.next()) { // пока не кончатся данные с запроса
            i++;
            // задаем стркутуру
            Data temp{query.value(0).toString(), query.value(1).toString()};
            // отправляем в список
            data.push_back(temp);
        }
    }
    else {
        QMessageBox::information(nullptr, "Ошибка", "Ошибка в чтении файла: " );
    }
    QMessageBox::information(nullptr, "Успешное чтение файла", "файл прочитан: " +  data[0].key);//пока для проверки пусть так будет (выводится ключ первого элемента)

    return data;
}

QList<Data> JsonFileReader::readFile(const QString& filePath)
{
    QList<Data> data;

    // Чтение файла с расширением .json

    return data;
}
