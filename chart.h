#ifndef CHART_H
#define CHART_H
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <filereader.h>
using namespace QtCharts;

class IChart {
    QChart* chart = new QChart();
public:
    QChart* getChart() {return chart;}
    virtual void drawChart(QList<Data>, bool) = 0;
    virtual ~IChart() = default;
};

class BarChart: public IChart {
public:
    void drawChart(QList<Data>, bool);
    ~BarChart() = default;
};

class PieChart: public IChart {
public:
    void drawChart(QList<Data>, bool);
    ~PieChart() = default;
};

#endif // CHART_H

