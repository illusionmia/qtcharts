/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "tablewidget.h"
#include "customtablemodel.h"
#include <QGridLayout>
#include <QTableView>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QVXYModelMapper>
#include <QGroupedBarSeries>
#include <QBarSet>
#include <QVBarModelMapper>
#include <QHeaderView>

QTCOMMERCIALCHART_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    //! [1]
    CustomTableModel *model = new CustomTableModel;
    //! [1]

    //! [2]
    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    //! [2]

    //! [3]
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // series 1
    //! [4]
    QGroupedBarSeries *series = new QGroupedBarSeries;

    int first = 3;
    int count = 5;
    QVBarModelMapper *mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(1);
    mapper->setLastBarSetColumn(4);
    mapper->setFirst(3);
    mapper->setCount(count);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
    //! [4]

    QStringList categories;
    categories << "June" << "July" << "August" << "September" << "October" << "November";

    chart->axisX()->categories()->insert(categories);

    //! [5]
    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    QList<QBarSet*> barsets = series->barSets();
    for (int i = 0; i < barsets.count(); i++) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        model->addMapping(seriesColorHex, QRect(1 + i, first, 1, barsets.at(i)->count()));
    }
    //! [5]

    //! [8]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    //! [8]

    //! [9]
    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [9]
}
