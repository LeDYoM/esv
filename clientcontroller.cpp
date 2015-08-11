#include "clientcontroller.h"
#include "boardmodel.h"
#include <QDebug>
#include <QTime>

ClientController::ClientController(QObject *parent)
    : QObject{parent}
{
    QTime time = QTime::currentTime();
    qsrand((uint)(time.elapsed() + time.msecsSinceStartOfDay()));
}

ClientController::~ClientController()
{

}

void ClientController::getNewStartBoard(BoardModel * const toFill)
{
    auto area = toFill->area();
    int dens = area * densiness();
    qDebug() << "Area int:" << area;
    qDebug() << "Densiness int:" << dens;
    auto fill = 0;

    for (auto x=0;x<toFill->size().width();++x)
    {
        for (auto y=0;y<toFill->size().height();++y)
        {
            auto r = randomInt(area);
            int fElement = r<dens?1:0;
            toFill->setFutureElement(QPoint(x,y),fElement);
            if (fElement)
            {
                fill++;
            }
        }
    }

    qDebug() << "Occupied:" << fill;
    qDebug() << "Proportion:"<<(float)(fill/(float)area);
}

void ClientController::getNewStep(BoardModel * const toFill)
{
    for (auto x=0;x<toFill->size().width();++x)
    {
        for (auto y=0;y<toFill->size().height();++y)
        {
            QPoint point(x,y);
            if (toFill->elementIsOccupied(point))
            {
                if (toFill->countNeighbours(point) <= lowp())
                {
                    toFill->freeFutureElement(point);
                }
                else if (toFill->countNeighbours(point) >= highp())
                {
                    toFill->freeFutureElement(point);
                }
                else
                {
                    toFill->forwardFutureElement(point);
                }
            }
            else
            {
                if (toFill->countNeighbours(point) == createp())
                {
                    toFill->occupyFutureElement(point);
                }
                else
                {
                    toFill->forwardFutureElement(point);
                }
            }
        }
    }
}

int ClientController::randomInt(const int max) const
{
    int max_{max};
    int acc = (qrand()%max_);

    if (max_>RAND_MAX)
    {
        int temp = acc;
        max_ -= RAND_MAX;

        while (max_>RAND_MAX)
        {
            acc += temp;
            max_-=RAND_MAX;
        }

        acc += qrand()%max_;
    }

    return acc;
}
/*
int ClientController::randomInt(int max) const
{
    int randomValue = qrand();

    if (randomValue>rmax)
    {
        rmax = randomValue;
        qDebug() << "RMax:"<<rmax;
    }

    return randomValue%max;
}
*/
