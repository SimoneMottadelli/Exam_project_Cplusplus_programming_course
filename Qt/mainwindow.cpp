#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::init() {
    readFile();
    initPieCharts();
    initRegionComboBox();
    refreshTable();
    updatePieCharts();
}


void MainWindow::readFile() {
    dataset.clear();
    QFile file("data.txt");
    file.open(QIODevice::ReadOnly);
    if (file.isOpen()) {
        QTextStream textStream(&file);
        QString row;
        while (!textStream.atEnd()) {
            row = textStream.readLine();
            if (row != "<END>")
                dataset.append(row);
        }
        file.close();
    }
}


void MainWindow::initRegionComboBox() {
    ui->regionComboBox->clear();
    QString regionName, previousRegionName = "";
    for (int i = 0; i < dataset.size(); ++i) {
        regionName = dataset.at(i).split(" ").at(0);
        if (regionName != previousRegionName) {
            ui->regionComboBox->addItem(regionName);
            previousRegionName = regionName;
        }
    }
}


void MainWindow::refreshTable() {
    // clear old total number of men and women
    numberOfMen = 0;
    numberOfWomen = 0;

    // clear table
    for (int i = 0; i < dataset.size(); ++i)
        ui->tableWidget->removeRow(0);

    ui->tableWidget->removeRow(0); // clear total number of men and women

    // insert new rows
    QString regionName = ui->regionComboBox->currentText();
    int rowIndex = 0;
    for (int i = 0; i < dataset.size(); ++i) {
        QStringList row = dataset.at(i).split(" ");
        if (row.first() == regionName) {
            row.removeFirst(); // region name is not necessary
            ui->tableWidget->insertRow(rowIndex);
            for (int j = 0; j < row.size(); ++j)
                ui->tableWidget->setItem(rowIndex, j, new QTableWidgetItem(row.at(j)));
            ++rowIndex;

            //update total number of men and women
            numberOfMen += row.at(1).toInt();
            numberOfWomen += row.at(2).toInt();
        }
    }

    // add total number of men and women
    ui->tableWidget->insertRow(rowIndex);
    ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem("TOTALE"));
    ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(numberOfMen)));
    ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(numberOfWomen)));
}


void MainWindow::initPieCharts() {
    chartMen = new QChart();
    chartMen->setTitle("Maschi");
    chartMen->legend()->setAlignment(Qt::AlignLeft);
    chartWomen = new QChart();
    chartWomen->setTitle("Femmine");
    chartWomen->legend()->setAlignment(Qt::AlignLeft);
    ui->rightMainLayout->addWidget(new QChartView(chartMen));
    ui->rightMainLayout->addWidget(new QChartView(chartWomen));
}


void MainWindow::updatePieCharts() {
    // clear charts
    chartMen->removeAllSeries();
    chartWomen->removeAllSeries();

    // add series to pie charts
    QPieSeries *seriesMen = new QPieSeries();
    QPieSeries *seriesWomen = new QPieSeries();

    for (int i = 0; i < dataset.size(); ++i) {
        QStringList row = dataset.at(i).split(" ");
        if (row.first() == ui->regionComboBox->currentText()) {
            double percentageMen = row.at(2).toDouble() * 100 / numberOfMen;
            double percentageWomen = row.at(3).toDouble() * 100 / numberOfWomen;
            QString label = "[" + row.at(1)  + "] " + QString::number(percentageMen, 'f', 2) + "%";
            QPieSlice *sliceMan = new QPieSlice(label, percentageMen);
            label = "[" + row.at(1)  + "] " + QString::number(percentageWomen, 'f', 2) + "%";
            QPieSlice *sliceWoman = new QPieSlice(label, percentageWomen);
            seriesMen->append(sliceMan);
            seriesWomen->append(sliceWoman);
        }
    }
    chartMen->addSeries(seriesMen);
    chartWomen->addSeries(seriesWomen);
}


void MainWindow::on_regionComboBox_currentTextChanged() {
    refreshTable();
    updatePieCharts();
}
