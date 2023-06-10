#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <memory>
#include <iostream>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    treeView(new QTreeView(this)),//при создании экземляра  они управляются родительским виджетом, поэтому не нужно умные указатели сипользовать
    fileModel(new QFileSystemModel(this)),
    sqliteFileReader(new SqliteFileReader()) // Добавлено инициализация объекта sqliteFileReader
{
    ui->setupUi(this);
    resize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    QWidget *leftWidget = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    openButton = std::unique_ptr<QPushButton>(new QPushButton("Открыть", this));
    openButton->setFixedSize(100, 30);

    leftLayout->addWidget(openButton.get());
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
    connect(treeView.get(), &QTreeView::doubleClicked, this, &Widget::openFile);
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
        QList<QMap<QString, QString>> data = sqliteFileReader->readFile(filePath);
        //        std::cout << "Файл успешно прочитан: " << filePath.toStdString();
        QMessageBox::information(this, "Успешное чтение файла", "Файл успешно прочитан: " + filePath);

    }
}
