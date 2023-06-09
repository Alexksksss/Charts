#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSplitter>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openFolder();//слот открытия

private:
    std::unique_ptr<Ui::Widget> ui;
    std::unique_ptr<QTreeView> treeView;//Файлы в виде дерева
    std::unique_ptr<QFileSystemModel> fileModel;//Модель для представления файлов
};

#endif // WIDGET_H
