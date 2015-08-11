#include "zoomer.h"
#include <cfloat>

Zoomer::Zoomer(const QVector<float> &iData, int initIndex, QObject *parent) : QObject(parent)
{
    zoomData=iData;
    _index=initIndex;
}

Zoomer::~Zoomer()
{

}

int Zoomer::addStep(const float stepData)
{
    zoomData.push_back(stepData);
    return zoomData.size()-1;
}

float Zoomer::getCurrentZoomValue() const
{
    return (_index>-1)?zoomData[_index]:valueSet;
}

void Zoomer::zoomIn()
{
    if (_index<(zoomData.size()-1))
    {
        _index++;
    }
    else
    {
        _index = 0;
    }
}

void Zoomer::zoomOut()
{
    if (_index>0)
    {
        _index--;
    }
    else
    {
        _index = zoomData.size()-1;
    }
}

int Zoomer::getNearestIndex(float value,bool upwards)
{
    int i=-1;

    for (i=0;i<zoomData.size();++i)
    {
        if (value<zoomData[i])
        {
            return upwards?i:i+1;
        }
    }
    return i;

}

void Zoomer::externSetValue(float value)
{
    _index = -1;
    valueSet = value;
}

