#include "customchart.h"

CustomChart::CustomChart(QWidget *parent) : CustomChart(parent, "", "", "")
{
}

CustomChart::CustomChart(QWidget *parent, QString &&str, QString &&xlabel, QString &&ylabel)
    : QCustomPlot(parent)
{
    QCPTextElement *title = new QCPTextElement(this, str);
    title->setTextColor(QColor(0xd5e8ff));

    plotLayout()->insertRow(0);
    plotLayout()->addElement(0,0, title);
    addGraph();

    xAxis->grid()->setPen(QPen(QColor(0x303662)));
    yAxis->grid()->setPen(QPen(QColor(0x303662)));

    xAxis->setBasePen(QPen(QColor(0xffffff)));
    xAxis->setTickPen(QPen(QColor(0xffffff)));
    xAxis->setSubTickPen(QPen(QColor(0xffffff)));
    xAxis->setTickLabelColor(QColor(0xffffff));

    yAxis->setBasePen(QPen(QColor(0xffffff)));
    yAxis->setTickPen(QPen(QColor(0xffffff)));
    yAxis->setSubTickPen(QPen(QColor(0xffffff)));
    yAxis->setTickLabelColor(QColor(0xffffff));

    yAxis->grid()->setPen(QPen(QColor(0x303662)));
    setBackground(QColor(0x2c325c));
    graph(0)->setPen(QPen(QColor(0xff5497)));

    xAxis->setLabel(xlabel);
    yAxis->setLabel(ylabel);

    xAxis->setLabelColor(QColor(0xd5e8ff));
    yAxis->setLabelColor(QColor(0xd5e8ff));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setBlurRadius(10);
    dropShadowEffect->setColor(QColor(0, 0, 0));
    dropShadowEffect->setXOffset(0);
    dropShadowEffect->setYOffset(0);

    setGraphicsEffect(dropShadowEffect);
}
