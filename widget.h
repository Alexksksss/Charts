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
#include <QLabel>
#include <QHeaderView>
#include <QPdfWriter>
#include "filereader.h"
#include "chart.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private slots:
    void openFolder(); // слот открытия папки (для кнопки открыть)
    void OpenFile(const QItemSelection &selected, const QItemSelection &deselected);//слот выбора файла
    void changeChartType();//круговая-столбчатая
    void colorChange();//чб<->цвет
    void print();//слот печати (для кнопки печать)
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    QString directoryPath;//путь до директории
    QString filePath;//путь до директории + выбранный файл
    std::unique_ptr<QFileSystemModel> fileModel;//файловая модель
    std::unique_ptr<QTreeView> treeView; // файлы в виде дерева
    std::unique_ptr<QChartView> chartView;//вид графика
    std::unique_ptr<QPushButton> printButton;//кнопка печать
    std::unique_ptr<QPushButton> openButton;//кнопка открыть
    std::unique_ptr<QCheckBox> checkBox;//чекбокс чб
    std::unique_ptr<QLabel> labelType;//текст (Тип диаграммы)
    std::unique_ptr<QComboBox> comboBoxType;//выпадающий список вида графика
    std::unique_ptr<QVBoxLayout> allLayout;//самый большой
    std::unique_ptr<QHBoxLayout> wrapperLayout;//левый + правый
    std::unique_ptr<QVBoxLayout> leftLayout;//где файлы в виде дерева
    std::unique_ptr<QVBoxLayout> rightLayout;//где график
    std::unique_ptr<QHBoxLayout> chartWidgetLayout;//график
    std::unique_ptr<QHBoxLayout> topLayout;//кнопки, чекбокс, комбобокс, текст
    std::unique_ptr<QSplitter> fileSplitter;//левый сплиттер
    std::unique_ptr<QSplitter> chartSplitter;//правый сплиттер
    bool isShown = false;//есть ли сейчас график в виджете

    void drawChart();//функция рисовки

    std::unique_ptr<Ui::Widget> ui;//сам интерфейс

};

#endif // WIDGET_H
