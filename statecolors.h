#ifndef RUNTIMEOPTIONS_H
#define RUNTIMEOPTIONS_H

#include <QObject>
#include <QColor>
#include <QVector>

class StateColors : public QObject
{
    Q_OBJECT
public:
    explicit StateColors(QObject *parent = 0):QObject{parent} {}
    ~StateColors() {}
    Q_DISABLE_COPY(StateColors)

    inline QColor getColorForState(int state) const
    {
        if (ccolors.size()>state)
        {
            return ccolors[state];
        }
        return QColor(128,128,128);
    }

    void setColor(const QColor &color,int state)
    {
        while (ccolors.size()<=state)
        {
            ccolors.push_back(QColor(128,128,128));
        }
        ccolors[state]=color;
    }

    int numVisibleColors() const { return ccolors.size(); }

private:
    QVector<QColor> ccolors;
};

#endif // RUNTIMEOPTIONS_H
