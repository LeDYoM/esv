#include "boardmodel.h"
#include "newboardoptions.h"

BoardModel::BoardModel(const NewBoardOptions *nbo, QObject *parent)
    : QObject{parent},boardData{nbo->newBoardSize()},futureBoardData{nullptr}
{
}

BoardModel::BoardModel(const BoardModel &other)
    : QObject(other.parent()),boardData{other.boardData}, futureBoardData{other.futureBoardData}
{
}

BoardModel &BoardModel::operator=(const BoardModel &other)
{
    boardData.data = other.boardData.data;
    boardData.size = other.boardData.size;
    boardData.setLoopBoard(other.boardData.loopBoard());
    return *this;
}

BoardModel::~BoardModel()
{
}

bool BoardModel::operator==(const BoardModel &other) const
{
    if (boardData.size == other.boardData.size)
    {
        for (int x=0;x<boardData.size.width();++x)
        {
            for (int y=0;y<boardData.size.height();++y)
            {
                QPoint p(x,y);
                if (getElement(p)!=other.getElement(p))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

 QSize BoardModel::size() const
{
    return boardData.size;
}

qint32 BoardModel::getElement(const QPoint &point)
{
    return boardData[point.x()][point.y()];
}

void BoardModel::setFutureElement(const QPoint &point, qint32 fElement)
{
    qint32 current = getElement(point);
    if (current != fElement)
    {
        if (!futureBoardData)
        {
            futureBoardData = new BoardData(boardData.size);
        }

        futureBoardData->data[point.x()][point.y()] = fElement;
    }
}

int BoardModel::countNeighbours(const QPoint &point) const
{
    int nn{0};
    for (int x=point.x()-1;x<=point.x()+1;++x)
    {
        for (int y=point.y()-1;y<=point.y()+1;++y)
        {
            if (x != point.x() || y != point.y())
            {
                QPoint point_ = toModelOptions(QPoint(x,y));
                if (elementIsOccupied(point_))
                {
                    ++nn;
                }
            }
        }
    }

    return nn;
}

bool BoardModel::elementIsEmpty(const QPoint &point) const
{
    return getElement(point) == 0;
}

bool BoardModel::elementIsOccupied(const QPoint &point) const
{
    return !elementIsEmpty(point);
}

void BoardModel::occupyFutureElement(const QPoint &point)
{
    setFutureElement(point,1);
}

void BoardModel::freeFutureElement(const QPoint &point)
{
    setFutureElement(point,0);
}

void BoardModel::forwardFutureElement(const QPoint &point)
{
    setFutureElement(point,getElement(point));
}

qint32 BoardModel::getElement(const QPoint &point) const
{
    return boardData.data[point.x()][point.y()];
}

void BoardModel::setElement(const QPoint &point, const qint32 nElement)
{
    boardData.data[point.x()][point.y()] = nElement;
}

void BoardModel::setBoardData(const BoardData &data_)
{
    boardData.size = data_.size;
    boardData.data = data_.data;
}

void BoardModel::makeFutureCurrent(BoardModel * const bmOut)
{
    if (futureBoardData)
    {
        BoardModel *bmOut_=bmOut;
        if (!bmOut_)
        {
            bmOut_=this;
        }
        bmOut_->setBoardData(*futureBoardData);
        delete futureBoardData;
        futureBoardData = nullptr;
    }
}


QPoint BoardModel::toModelOptions(const QPoint &point) const
{
    if (!boardData.loopBoard())
        return point;

    QPoint point_(point);

    while (point_.x() < 0)
    {
        point_.setX(point_.x()+boardData.size.width());
    }

    while (point_.x() >= boardData.size.width())
    {
        point_.setX(point_.x()-boardData.size.width());
    }
    while (point_.y() < 0)
    {
        point_.setY(point.y()+boardData.size.height());
    }

    while (point_.y() >= boardData.size.height())
    {
        point_.setY(point_.y()-boardData.size.height());
    }

    return point_;
}
