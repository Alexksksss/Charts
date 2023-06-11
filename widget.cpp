#include "widget.h"
#include "ui_widget.h"
#include "ioc.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <memory>
#include <iostream>
#include <QMessageBox>
#include <QHeaderView>
#include <QComboBox>
#include <QChartView>
#include <QtCharts/QLineSeries>
#include <QLabel>


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800, 600);

    openButton = new QPushButton("Открыть");
    printButton = new QPushButton("Печать");
    checkBox = new QCheckBox("ЧБ");
    labelType = new QLabel("Тип диаграммы");
    comboBoxType = new QComboBox();

    comboBoxType->addItem("Столбчатая");
    comboBoxType->addItem("Круговая");

    topLayout = new QHBoxLayout();
    wrapperLayout = new QHBoxLayout();

    topLayout->addWidget(openButton);
    topLayout->addWidget(labelType);
    topLayout->addWidget(comboBoxType);
    topLayout->addWidget(checkBox);
    topLayout->addWidget(printButton);


    leftLayout = new QVBoxLayout();
    fileSplitter = new QSplitter();
    treeView = new QTreeView();
    fileModel = new QFileSystemModel(this);
    QModelIndex pathIndex = fileModel->setRootPath("");
    treeView->setModel(fileModel);
    treeView->setRootIndex(pathIndex);
    fileSplitter->addWidget(treeView);
    leftLayout->addWidget(fileSplitter);


    rightLayout = new QVBoxLayout();
    chartWidgetLayout = new QHBoxLayout();
    chartSplitter = new QSplitter();

    rightLayout->addWidget(chartSplitter);
    rightLayout->addLayout(chartWidgetLayout);

    wrapperLayout->addLayout(leftLayout);
    wrapperLayout->addLayout(rightLayout);


    allLayout = new QVBoxLayout();
    allLayout->addLayout(topLayout);
    allLayout->addLayout(wrapperLayout);
    setLayout(allLayout);

    connect(openButton, &QPushButton::clicked, this, &Widget::openFolder);
    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::OpenFile);
}

void Widget::openFolder() {
    QFileDialog dialogWindow(this);
    QString initialPath = "D:/Qt/testFor3";
    dialogWindow.setDirectory(initialPath);
    dialogWindow.setFileMode(QFileDialog::Directory);

    directoryPath = dialogWindow.selectedFiles().first();

    treeView->setRootIndex(fileModel->setRootPath(directoryPath));
}

void Widget::OpenFile(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    filePath = fileModel->filePath(indexes.first());
    if (filePath.endsWith(".json")) {
        iocContainer.RegisterInstance<IFileReader, JsonFileReader>();
    }
    else if (filePath.endsWith(".sqlite")) {
        iocContainer.RegisterInstance<IFileReader, SqliteFileReader>();
    }
    // рисуем график

}


Widget::~Widget()
{
}
