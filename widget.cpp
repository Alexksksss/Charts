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
    resize(1000, 600);

    openButton = new QPushButton("Открыть");
    printButton = new QPushButton("Печать");
    labelType = new QLabel("Тип диаграммы");
    checkBox = new QCheckBox("ЧБ");
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
    treeView->setModel(fileModel);

    leftLayout->addWidget(treeView);
    fileSplitter->addWidget(treeView);
    leftLayout->addWidget(fileSplitter);


    rightLayout = new QVBoxLayout();
    chartWidgetLayout = new QHBoxLayout();
    chartSplitter = new QSplitter();
    chartView = new QChartView();

    chartWidgetLayout->addWidget(chartView);
    rightLayout->addLayout(chartWidgetLayout);
    chartSplitter->addWidget(chartView);
    rightLayout->addWidget(chartSplitter);

    wrapperLayout->addLayout(leftLayout);
    wrapperLayout->addLayout(rightLayout);


    allLayout = new QVBoxLayout();
    allLayout->addLayout(topLayout);
    allLayout->addLayout(wrapperLayout);
    setLayout(allLayout);

    QHeaderView *header = treeView->header();
    header->setSectionResizeMode(0, QHeaderView::Interactive);
    header->resizeSection(0, 200); // (название)

    header->setSectionResizeMode(1, QHeaderView::Interactive);
    header->resizeSection(1, 70); // (размер)

    header->setSectionResizeMode(2, QHeaderView::Interactive);
    header->resizeSection(2, 70); // (тип)

    header->setSectionResizeMode(3, QHeaderView::Interactive);
    header->resizeSection(3, 50); // (дата изменения)

    connect(openButton, &QPushButton::clicked, this, &Widget::openFolder);
    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::OpenFile);
    connect(comboBoxType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::changeChartType);
    connect(checkBox, &QCheckBox::toggled, this, &Widget::colorChange);
}

void Widget::openFolder()
{
    QFileDialog dialogWindow(this);
    QString initialPath = "D:/Qt/testFor3";
    dialogWindow.setDirectory(initialPath);
    dialogWindow.setFileMode(QFileDialog::Directory);

    if (dialogWindow.exec())
    {
        directoryPath = dialogWindow.selectedFiles().first();
        fileModel->setRootPath(directoryPath);
        treeView->setRootIndex(fileModel->index(directoryPath));
    }
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
    if (comboBoxType->currentText() == "Круговая") {
        iocContainer.RegisterInstance<IChart, PieChart>();
        isShown = true;
    }
    else if (comboBoxType->currentText() == "Столбчатая") {
        iocContainer.RegisterInstance<IChart, BarChart>();
        isShown = true;
    }
    // рисуем график
    if (isShown) {
        drawChart();
    }
}
void Widget::changeChartType()
{
    if (comboBoxType->currentText() == "Круговая")
        iocContainer.RegisterInstance<IChart, PieChart>();
    else if (comboBoxType->currentText() == "Столбчатая")
        iocContainer.RegisterInstance<IChart, BarChart>();
    if (isShown)
        drawChart();
}

void Widget::colorChange()
{
    if (isShown)
        drawChart();
}

void Widget::drawChart()
{
    auto chart = iocContainer.GetObject<IChart>();
    auto dataStructure = iocContainer.GetObject<IFileReader>();

    QList<Data> items = dataStructure->readFile(filePath);
    chart->drawChart(items, checkBox->isChecked());

    chartView->setChart(chart->getChart());
}

Widget::~Widget()
{
    delete openButton;
    delete printButton;
    delete checkBox;
    delete comboBoxType;
    delete chartView;
    delete chartSplitter;
    delete chartWidgetLayout;
    delete rightLayout;
    delete treeView;
    delete fileSplitter;
    delete leftLayout;
    delete fileModel;
    delete topLayout;
    delete wrapperLayout;
    delete allLayout;
}
