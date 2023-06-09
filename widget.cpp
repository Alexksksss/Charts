#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <memory>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    treeView(new QTreeView(this)),
    fileModel(new QFileSystemModel(this))
{
    ui->setupUi(this);
    resize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    QWidget *leftWidget = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    QPushButton *openButton = new QPushButton("Открыть", this);
    openButton->setFixedSize(100, 30);

    connect(openButton, &QPushButton::clicked, this, &Widget::openFolder);
    leftLayout->addWidget(openButton);

    leftLayout->addWidget(treeView.get());
    splitter->addWidget(leftWidget);

    QWidget *rightWidget = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    splitter->addWidget(rightWidget);

    layout->addWidget(splitter);

    fileModel->setRootPath(""); // Установка корневого пути для модели
    treeView->setModel(fileModel.get());

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
