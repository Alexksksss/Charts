#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <memory>
#include <iostream>
#include <QMessageBox>
#include <QHeaderView>
#include <QComboBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    treeView(new QTreeView(this)),//при создании экземляра  они управляются родительским виджетом, поэтому не нужно умные указатели сипользовать
    fileModel(new QFileSystemModel(this)),
    sqliteFileReader(new SqliteFileReader()), // Добавлено инициализация объекта sqliteFileReader
    jsonFileReader(new JsonFileReader()) // Добавлено инициализация объекта json
{
    ui->setupUi(this);
    resize(800, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QWidget *topWidget = new QWidget(this);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);

    openButton = std::unique_ptr<QPushButton>(new QPushButton("Открыть", this));
    openButton->setFixedSize(100, 30);

    labelType = std::unique_ptr<QLabel>(new QLabel("Тип диаграммы", this));// Создание QLabel с текстом "Текст"

    checkBox = std::unique_ptr<QCheckBox>(new QCheckBox("ЧБ", this));

    comboBoxType = std::unique_ptr<QComboBox>(new QComboBox(this));
    comboBoxType->addItem("Круговая");
    comboBoxType->addItem("Столбчатая");

    printButton = std::unique_ptr<QPushButton>(new QPushButton("Печать", this));

    topLayout->addWidget(openButton.get());
    topLayout->addWidget(labelType.get(), Qt::AlignLeft);
    topLayout->addWidget(comboBoxType.get(), Qt::AlignLeft);
    topLayout->addWidget(checkBox.get(), Qt::AlignLeft);
    topLayout->addWidget(printButton.get());

    layout->addWidget(topWidget);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    QWidget *leftWidget = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(treeView.get());

    splitter->addWidget(leftWidget);

    QWidget *rightWidget = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    splitter->addWidget(rightWidget);

    layout->addWidget(splitter);
    fileModel->setRootPath(""); // Установка корневого пути для модели
    treeView->setModel(fileModel.get());

    // Установка размеров столбцов
    QHeaderView *header = treeView->header();
    header->setSectionResizeMode(0, QHeaderView::Interactive);
    header->resizeSection(0, 150); // (название)

    header->setSectionResizeMode(1, QHeaderView::Interactive);
    header->resizeSection(1, 70); // (размер)

    header->setSectionResizeMode(2, QHeaderView::Interactive);
    header->resizeSection(2, 70); // (тип)

    header->setSectionResizeMode(3, QHeaderView::Interactive);
    header->resizeSection(3, 50); // (дата изменения)

    connect(openButton.get(), &QPushButton::clicked, this, &Widget::openFolder);
    connect(treeView.get(), &QTreeView::clicked, this, &Widget::openFile);
    connect(printButton.get(), &QPushButton::clicked, this, &Widget::print);
}

Widget::~Widget()
{
}

void Widget::openFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Выберите папку"); // Открытие диалогового окна выбора папки
    fileModel->setRootPath(folderPath); // Установка выбранной папки в модель
    treeView->setRootIndex(fileModel->index(folderPath)); // Установка корневого индекса в представлении
}

void Widget::openFile(const QModelIndex& index)
{
    QString filePath = fileModel->fileInfo(index).absoluteFilePath();
    if (sqliteFileReader)
    {
        QList<Data> data = sqliteFileReader->readFile(filePath);
        //        std::cout << "Файл успешно прочитан: " << filePath.toStdString();
        //QMessageBox::information(this, "Успешное чтение файла sql", "Файл успешно прочитан: " + filePath);
    }
    else if (jsonFileReader)
    {
        QList<Data> data = jsonFileReader->readFile(filePath);
        if (data.isEmpty()) {
            QMessageBox::information(this, "Ошибка", "Список данных пуст");
            return;
        }

        //        std::cout << "Файл успешно прочитан: " << filePath.toStdString();
        // QMessageBox::information(this, "Успешное чтение файла json", "Файл успешно прочитан: " + filePath);
    }
}

void Widget::print()
{
    QMessageBox::information(this, "печать", "вызов печати");
}
