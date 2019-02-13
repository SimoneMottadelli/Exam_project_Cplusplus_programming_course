#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QPieSeries;
class QPieSlice;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_regionComboBox_currentTextChanged();

private:
    Ui::MainWindow *ui;
    QChart *chartMen;
    QChart *chartWomen;
    QStringList dataset;
    long numberOfMen;
    long numberOfWomen;

    void readFile();
    void init();
    void initRegionComboBox();
    void refreshTable();
    void initPieCharts();
    void updatePieCharts();
};

#endif // MAINWINDOW_H
