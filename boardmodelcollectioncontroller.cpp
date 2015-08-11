#include "boardmodelcollectioncontroller.h"
#include "clientcontroller.h"
#include <QDebug>

BoardModelCollectionController::BoardModelCollectionController(QObject *parent)
    : QObject(parent), current{nullptr},newBoardOptions{nullptr},activeBoard{-1}, clientController{new ClientController(this)}
{
}

BoardModelCollectionController::~BoardModelCollectionController()
{
    if (current)
    {
        current->deleteLater();
        current = nullptr;
    }
}

void BoardModelCollectionController::onBoardLoaded(const BoardData *bData,const NewBoardOptions *nbo)
{
    qDebug() << Q_FUNC_INFO;
    resetController(nbo);
    getNewBoardModel();
    overrideCurrentBoardData(bData);
    registerLastBoardModel();
}

void BoardModelCollectionController::registerLastBoardModel()
{
    qDebug() << Q_FUNC_INFO;
    Q_ASSERT(current);
    data.push_back(current);
    current = nullptr;
    activeBoard = getLastBoardIndex();
    Q_EMIT activeBoardModelChanged(getActiveBoard());
    Q_EMIT collectionBoundsChanged(getLastBoardIndex());
    Q_EMIT activeBoardIndexChanged(activeBoard);
}

void BoardModelCollectionController::newStartBoard()
{
    qDebug() << Q_FUNC_INFO;
    BoardModel *temp = getNewBoardModel();
    clientController->getNewStartBoard(temp);
    temp->makeFutureCurrent();
    registerLastBoardModel();
}

void BoardModelCollectionController::generateNewStep()
{
    qDebug() << Q_FUNC_INFO;
    BoardModel *bModel = getActiveBoard();
    Q_UNUSED(bModel);
    BoardModel *temp = getNewBoardModel();
    clientController->getNewStep(bModel);
    bModel->makeFutureCurrent(temp);
    registerLastBoardModel();
}

const BoardModel *BoardModelCollectionController::getActiveBoard() const
{
    return getBoardAt(activeBoard);
}

BoardModel *BoardModelCollectionController::getActiveBoard()
{
    return getBoardAt(activeBoard);
}

void BoardModelCollectionController::resetController(const NewBoardOptions *nbo)
{
    this->reset(nbo);
}

void BoardModelCollectionController::nextStep()
{
    qDebug() << Q_FUNC_INFO;
    if (isEmpty())
    {
        newStartBoard();
    }
    else
    {
        Q_ASSERT(activeBoard>-1);
        if (getLastBoardIndex()==activeBoard)
        {
            generateNewStep();
        }
        else
        {
            ++activeBoard;
            Q_EMIT activeBoardModelChanged(getBoardAt(activeBoard));
            Q_EMIT activeBoardIndexChanged(activeBoard);
        }
    }
}

void BoardModelCollectionController::previousStep()
{
    if (activeBoard>0)
    {
        --activeBoard;
        Q_EMIT activeBoardModelChanged(getBoardAt(activeBoard));
        Q_EMIT activeBoardIndexChanged(activeBoard);
    }
}

void BoardModelCollectionController::externalSetStep(int nValue)
{
    qDebug() << Q_FUNC_INFO << ": nValue: "<< nValue << ", activeBoard: "<<activeBoard;
    Q_ASSERT(nValue>-1);
    Q_ASSERT(nValue<data.size());
    if (activeBoard != nValue)
    {
        activeBoard = nValue;
        Q_EMIT activeBoardModelChanged(getBoardAt(activeBoard));
//        Q_EMIT activeBoardIndexChanged(activeBoard);
    }
}

BoardModel *BoardModelCollectionController::getNewBoardModel()
{
    qDebug() << Q_FUNC_INFO;
    Q_ASSERT(!current);
    current = new BoardModel(newBoardOptions);
    return current;
}


int BoardModelCollectionController::getLastBoardIndex() const
{
    return data.size()-1;
}

bool BoardModelCollectionController::isEmpty() const
{
    return data.isEmpty();
}

const BoardModel *BoardModelCollectionController::getBoardAt(int index) const
{
    Q_ASSERT(index>-1);
    Q_ASSERT(index<data.size());

    return data[index];
}

BoardModel *BoardModelCollectionController::getBoardAt(int index)
{
    Q_ASSERT(index>-1);
    Q_ASSERT(index<data.size());

    return data[index];
}

void BoardModelCollectionController::overrideCurrentBoardData(const BoardData *bData)
{
    Q_ASSERT(current);
    current->setBoardData(*bData);
}

void BoardModelCollectionController::reset(const NewBoardOptions *nbo)
{
    if (current)
    {
        current->deleteLater();
        current = nullptr;
    }
    data.clear();
    setBoardOptions(nbo);
}

void BoardModelCollectionController::setBoardOptions(const NewBoardOptions *nbo)
{
    Q_ASSERT(data.size()<1);
    newBoardOptions = nbo;
}
