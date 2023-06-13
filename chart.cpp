#include "chart.h"

void BarChart::drawChart(QList<Data> data, bool isGray) {
    // диаграмма
    QChart* chart = getChart();

    chart->setTitle("BarChart");

    QBarSeries *series = new QBarSeries(chart);
    // количество данных
    int length = data.count();
    for (int i = 0; i < length; i++) {
        QBarSet* barSet = new QBarSet(data.at(i).key);
        * barSet << data.at(i).value;
        if (isGray)
        {
            int gray = (rand() % 255);
            barSet->setBrush(QColor(gray, gray, gray));
        }
        else
             barSet->setBrush(QColor(rand() % 255, rand() % 255, rand() % 255));
        series->append(barSet);
    }
    chart->removeAllSeries();

    chart->addSeries(series);
    chart->createDefaultAxes();// Создает оси для диаграммы на основе ряда, который уже был добавлен в диаграмму.
}

void PieChart::drawChart(QList<Data> list, bool isGrey) {
    // диаграмма
    QChart* chart = getChart();
    // заголовок
    chart->setTitle("PieChart");
    QPieSeries * pieSeries = new QPieSeries(chart);
    // количество данных
    int length = list.count();
    if (length > 10)
        length = 10;
    for (int i = 0; i < length; i++) {
        QPieSlice* slice = pieSeries->append(list.at(i).key, list.at(i).value);
        if (isGrey)
        {
            int gray = (rand() % 255);
            slice->setBrush(QColor(gray, gray, gray));
        }
        else
            slice->setBrush(QColor(rand() % 255, rand() % 255, rand() % 255));
    }
    chart->removeAllSeries();
    chart->addSeries(pieSeries);
}
