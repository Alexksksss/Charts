#include "fileReader.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

QList<Data> SqliteFileReader::readFile(QString filePath)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE"); //создаем соединение по умолчанию с драйвером "QSQLITE"
    // устанавливаем связь
    dbase.setDatabaseName(filePath);
    QList<Data> data;

    if (dbase.open()) {
        // делаем запрос
        QSqlQuery query ("SELECT * FROM " + dbase.tables().takeFirst());
        int i = 0; // счетчик данных
        while (query.next() && i < 5) { // пока не кончатся данные с запроса

            i++;
            // задаем стркутуру
            Data temp{query.value(0).toString(), query.value(1).toDouble()};
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

QList<Data> JsonFileReader::readFile(QString filePath)
{
    QString val;
    QFile file;
    file.setFileName(filePath);
    QList<Data> data;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Ошибка", "Ошибка в чтении файла: " );
        return QList<Data>();  // Возвращаем пустой список при ошибке чтения файла
    }

    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = doc.object();

    QStringList keys (jsonObject.keys());
    int i = 0;
    QListIterator<QString> iterator(keys);
    while (iterator.hasNext() && i < 5) {
        QString key = iterator.next();
        double value = jsonObject.value(key).toDouble();
        Data string{key, value};
        data.push_back(string);
        i++;
    }
    if (!data.isEmpty()) {
        QMessageBox::information(nullptr, "Успешное чтение файла", "Файл прочитан: " + data[0].key);
    } else {
        QMessageBox::information(nullptr, "Ошибка", "Список данных пуст");
    }

    return data;
}
