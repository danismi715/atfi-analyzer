#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QPoint>
#include <QList>
#include <QMutex>

enum ChannelColumn {
    DATE_COLUMN = 0,
    HTIME_COLUMN,
    MTIME_COLUMN,
    STIME_COLUMN,
    CHANNEL_COLUMN_1,
    CHANNEL_COLUMN_2,
    CHANNEL_COLUMN_3
};

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    ~Model();
    void setResourceFile(const QString path);
    const QString getResourceFile();
    bool openResourceFile();
    void extractResourceFromFile(ChannelColumn column = CHANNEL_COLUMN_1);
    QVector<double> getY();
    QVector<double> getY(int begin, int len);
    QVector<double> getX();
    QVector<double> getX(int begin, int len);
    int getSize();
    float getSignalPeriod();
    int getProgressReadFile();
private:
    QMutex *_accessFileMux;
    QString _resourceFilePath;
    QFile *_file;
    QVector<double> _y;
    QVector<double> _x;
};

#endif // MODEL_H
