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


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private slots:
    void openFolder(); // слот открытия
    void OpenFile(const QItemSelection &selected, const QItemSelection &deselected);
    //void changeChartType();

   // void colorChange();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    QString directoryPath;

    QString filePath;

    QFileSystemModel* fileModel;
    QTreeView* treeView; // файлы в виде дерева

    //QChartView* chartView;

    QPushButton* printButton;
    QPushButton* openButton;

    QCheckBox* checkBox;

    QLabel* labelType;

    QComboBox* comboBoxType;

    QVBoxLayout* allLayout;
    QHBoxLayout* wrapperLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QHBoxLayout* chartWidgetLayout;
    QHBoxLayout* topLayout;

    QSplitter* fileSplitter;
    QSplitter* chartSplitter;

    bool isShown = false;

    void drawChart();

    std::unique_ptr<Ui::Widget> ui;

};

#endif // WIDGET_H
