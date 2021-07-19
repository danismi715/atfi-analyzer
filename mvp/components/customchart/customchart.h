#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include "qcustomplot.h"

class CustomChart : public QCustomPlot
{
public:
    CustomChart(QWidget *parent);
    CustomChart(QWidget *parent, QString &&str, QString &&ylabel, QString &&xlabel);
};

#endif // CUSTOMCHART_H
