#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSplitter>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include "filereader.h"
#include "chart.h"
#include <QLabel>
#include <QPdfWriter>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private slots:
    void openFolder(); // слот открытия
    void OpenFile(const QItemSelection &selected, const QItemSelection &deselected);
    void changeChartType();
    void colorChange();
    void print();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    QString directoryPath;
    QString filePath;
    std::unique_ptr<QFileSystemModel> fileModel;
    std::unique_ptr<QTreeView> treeView; // файлы в виде дерева
    std::unique_ptr<QChartView> chartView;
    std::unique_ptr<QPushButton> printButton;
    std::unique_ptr<QPushButton> openButton;
    std::unique_ptr<QCheckBox> checkBox;
    std::unique_ptr<QLabel> labelType;
    std::unique_ptr<QComboBox> comboBoxType;
    std::unique_ptr<QVBoxLayout> allLayout;
    std::unique_ptr<QHBoxLayout> wrapperLayout;
    std::unique_ptr<QVBoxLayout> leftLayout;
    std::unique_ptr<QVBoxLayout> rightLayout;
    std::unique_ptr<QHBoxLayout> chartWidgetLayout;
    std::unique_ptr<QHBoxLayout> topLayout;
    std::unique_ptr<QSplitter> fileSplitter;
    std::unique_ptr<QSplitter> chartSplitter;
    bool isShown = false;

    void drawChart();

    std::unique_ptr<Ui::Widget> ui;

};

#endif // WIDGET_H
