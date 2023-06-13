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

    openButton = std::make_unique<QPushButton>("Открыть",this);
    printButton = std::make_unique<QPushButton>("Печать",this);
    labelType = std::make_unique<QLabel>("Тип диаграммы",this);
    checkBox = std::make_unique<QCheckBox>("ЧБ",this);
    comboBoxType = std::make_unique<QComboBox>(this);

    comboBoxType->addItem("Столбчатая");
    comboBoxType->addItem("Круговая");

    topLayout = std::make_unique<QHBoxLayout>();
    wrapperLayout = std::make_unique<QHBoxLayout>();

    topLayout->addWidget(openButton.get());
    topLayout->addWidget(labelType.get());
    topLayout->addWidget(comboBoxType.get());
    topLayout->addWidget(checkBox.get());
    topLayout->addWidget(printButton.get());

    leftLayout = std::make_unique<QVBoxLayout>();
    fileSplitter = std::make_unique<QSplitter>();
    treeView = std::make_unique<QTreeView>();
    fileModel = std::make_unique<QFileSystemModel>(this);
    treeView->setModel(fileModel.get());

    leftLayout->addWidget(treeView.get());
    fileSplitter->addWidget(treeView.get());
    leftLayout->addWidget(fileSplitter.get());

    rightLayout = std::make_unique<QVBoxLayout>();
    chartWidgetLayout = std::make_unique<QHBoxLayout>();
    chartSplitter = std::make_unique<QSplitter>();
    chartView = std::make_unique<QChartView>();

    chartWidgetLayout->addWidget(chartView.get());
    rightLayout->addLayout(chartWidgetLayout.get());
    chartSplitter->addWidget(chartView.get());
    rightLayout->addWidget(chartSplitter.get());

    wrapperLayout->addLayout(leftLayout.get());
    wrapperLayout->addLayout(rightLayout.get());

    allLayout = std::make_unique<QVBoxLayout>();
    allLayout->addLayout(topLayout.get());
    allLayout->addLayout(wrapperLayout.get());
    setLayout(allLayout.get());

    QHeaderView *header = treeView->header();
    header->setSectionResizeMode(0, QHeaderView::Interactive);
    header->resizeSection(0, 200); // (название)

    header->setSectionResizeMode(1, QHeaderView::Interactive);
    header->resizeSection(1, 70); // (размер)

    header->setSectionResizeMode(2, QHeaderView::Interactive);
    header->resizeSection(2, 70); // (тип)

    header->setSectionResizeMode(3, QHeaderView::Interactive);
    header->resizeSection(3, 50); // (дата изменения)

    connect(openButton.get(), &QPushButton::clicked, this, &Widget::openFolder);
    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::OpenFile);
    connect(comboBoxType.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::changeChartType);
    connect(checkBox.get(), &QCheckBox::toggled, this, &Widget::colorChange);
    connect(printButton.get(), &QPushButton::clicked, this, &Widget::print);
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
    else{
        QMessageBox::information(nullptr, "Ошибка", "Неподдерживаемый формат файла");
        return;
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

void Widget::print() {
    if(isShown){
        QFileDialog *fileDialog = new QFileDialog(this);

        fileDialog->setDirectory("");
        fileDialog->setAcceptMode(QFileDialog::AcceptSave);

        QStringList fileNames;
        if(fileDialog->exec())
            fileNames = fileDialog->selectedFiles();

        QPdfWriter pdfWriter(fileNames.first() + ".pdf");

        QPainter painter(&pdfWriter);

        chartView->render(&painter);
        painter.end();
    }
    else {
        QMessageBox::information(nullptr, "Ошибка", "Файл не выбран");
    }
}


Widget::~Widget()
{
}
