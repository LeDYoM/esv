#ifndef ZOOMER_H
#define ZOOMER_H

#include <QObject>
#include <QVector2D>
#include <QPoint>
#include <QVector>
#include <QPair>

class Zoomer : public QObject
{
    Q_OBJECT
public:
    explicit Zoomer(const QVector<float> &iData,int initIndex,QObject *parent = 0);
    ~Zoomer();

    int addStep(const float stepData);
    float getCurrentZoomValue() const;

    void changedProcessed();

public Q_SLOTS:
    void zoomIn();
    void zoomOut();
    void externSetValue(float value);

private:
    int getNearestIndex(float value, bool upwards);

    QVector<float> zoomData;
    int _index;
    float valueSet;
};

#endif // ZOOMER_H
