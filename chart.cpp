#include "chart.h"

IChart::IChart() {
    chart = new QChart();
}

QChart* IChart::getChart() {
    return chart;
}

void IChart::drawChart(QList<Data> data, bool isGray, int limit) {
    createChartTitle();
    createChartSeries(data, isGray, limit);
    customizeChart();
}

void BarChart::createChartTitle() {
    chart->setTitle("BarChart");
}

void BarChart::createChartSeries(QList<Data> data, bool isGray, int limit) {
    int length = data.count();
    if (length > limit)
        length = limit;
    if(length==0)
        return;
    QBarSeries* series = new QBarSeries(chart);

    for (int i = 0; i< length; i++) {
        QBarSet* barSet = new QBarSet(data.at(i).key);
        *barSet << data.at(i).value;

        if (isGray) {
            int gray = (rand() % 255);
            barSet->setBrush(QColor(gray, gray, gray));
        } else
            barSet->setBrush(QColor(rand() % 255, rand() % 255, rand() % 255));

        series->append(barSet);
    }
    removeSeries();
    chart->addSeries(series);
}

void BarChart::customizeChart() {
    chart->createDefaultAxes();// Создает оси для диаграммы на основе ряда, который уже был добавлен в диаграмму.
}

void BarChart::removeSeries(){
    chart->removeAllSeries();
}

void PieChart::createChartTitle() {
    chart->setTitle("PieChart");
}


void PieChart::createChartSeries(QList<Data> data, bool isGray, int limit) {
    QPieSeries* pieSeries = new QPieSeries(chart);

    int length = data.count();
    if (length > limit)
        length = limit;
    if(length == 0)
        return;

    for (int i = 0; i < length; i++) {
        const Data& item = data.at(i);

        QPieSlice* slice = pieSeries->append(item.key, item.value);

        if (isGray) {
            int gray = (rand() % 255);
            slice->setBrush(QColor(gray, gray, gray));
        } else
            slice->setBrush(QColor(rand() % 255, rand() % 255, rand() % 255));
    }

    removeSeries();
    chart->addSeries(pieSeries);
}

void PieChart::customizeChart() {
    //не нужно
}

void PieChart::removeSeries(){
    chart->removeAllSeries();
}
