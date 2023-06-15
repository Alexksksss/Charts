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
protected:
    QChart* chart;
public:
    IChart();

    QChart* getChart();

    void drawChart(QList<Data> data, bool isGray, int limit);

    virtual ~IChart() = default;

    virtual void createChartTitle() = 0;
    virtual void createChartSeries(QList<Data> data, bool isGray, int limit) = 0;
    virtual void customizeChart() = 0;
    virtual void removeSeries() = 0;
};

class BarChart : public IChart {
public:
    void createChartTitle() override;
    void createChartSeries(QList<Data> data, bool isGray, int limit) override;
    void customizeChart() override;
    void removeSeries() override;

    ~BarChart() = default;
};

class PieChart : public IChart {
public:
    void createChartTitle() override;
    void createChartSeries(QList<Data> data, bool isGray, int limit) override;
    void customizeChart() override;
    void removeSeries() override;

    ~PieChart() = default;
};

#endif // CHART_H
