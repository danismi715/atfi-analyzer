#include "mvp/model/model.h"
#include <QDateTime>
#include <QElapsedTimer>

Model::Model(QObject *parent) : QObject(parent)
{
    _accessFileMux = new QMutex();
    _file = new QFile();
}

Model::~Model()
{
    delete _accessFileMux;
    if (!_file->isOpen()) {
        _file->close();
        delete _file;
    }
}

void Model::setResourceFile(const QString path)
{
    _resourceFilePath = path;
}

const QString Model::getResourceFile()
{
    return _resourceFilePath;
}

bool Model::openResourceFile()
{
    _file->setFileName(_resourceFilePath);

    if (!_file->open(QIODevice::ReadOnly)) {
        return false;
    }

    return true;
}

void Model::extractResourceFromFile(ChannelColumn column)
{
    if (!_file->isOpen()) {
        openResourceFile();
    }

    if (_resourceFilePath.isEmpty()) {
        qDebug() << "The path to resource file was not found";
        return;
    }

    _x.clear();
    _y.clear();

    QStringList columnResource;
    QString line;

    while (!_file->atEnd()) {
        _accessFileMux->lock();
        line = _file->readLine();
        _accessFileMux->unlock();

        columnResource = line.split('\t');

        double timeinsec = columnResource[HTIME_COLUMN].toInt() * 3600
                         + columnResource[MTIME_COLUMN].toInt() * 60
                         + columnResource[STIME_COLUMN].toFloat();

        int day = QDate::fromString(columnResource[DATE_COLUMN], "yyyy.MM.dd").day();

        timeinsec += day * 86400;

        _x.append(timeinsec);
        _y.append(columnResource[column].toFloat());
    }

    if (_file->isOpen()) {
        _file->close();
    }
}

QVector<double> Model::getY()
{
    return _y;
}

QVector<double> Model::getY(int begin, int len)
{
    if (!(begin <= _y.size()) && !(len <= _y.size()) && !((begin + len) <= _y.size())) {
        qDebug() << "Out of range";
        return QVector<double>{};
    }

    return _y.mid(begin, len);
}


QVector<double> Model::getX()
{
    return _x;
}

QVector<double> Model::getX(int begin, int len)
{
    if (!(begin <= _x.size()) && !(len <= _x.size()) && !((begin + len) <= _x.size())) {
        qDebug() << "Out of range";
        return QVector<double>{};
    }

    return _x.mid(begin, len);
}

int Model::getSize()
{
    return _y.size();
}

float Model::getSignalPeriod()
{
    return (_x[1] - _x[0]);
}

int Model::getProgressReadFile()
{
    _accessFileMux->lock();
    int prog = ((long double)_file->pos() / (long double)_file->size()) * 100; // convert to percent
    _accessFileMux->unlock();

    return prog;
}

