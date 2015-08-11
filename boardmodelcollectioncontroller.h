#ifndef BOARDMODELCOLLECTIONCONTROLLER_H
#define BOARDMODELCOLLECTIONCONTROLLER_H

#include <QObject>
#include "boardmodel.h"

class ClientController;
class BoardData;
class NewBoardOptions;

class BoardModelCollectionController : public QObject
{
    Q_OBJECT
public:
    explicit BoardModelCollectionController(QObject *parent = 0);
    virtual ~BoardModelCollectionController();

    BoardModel *getNewBoardModel();
    void registerLastBoardModel();
    int getLastBoardIndex() const;
    bool isEmpty() const;
    const BoardModel *getBoardAt(int index) const;
    BoardModel *getBoardAt(int index);
    void overrideCurrentBoardData(const BoardData *bData);

    void onBoardLoaded(const BoardData *bData, const NewBoardOptions *nbo);

    void previousStep();
    void nextStep();

    const BoardModel *getActiveBoard() const;
    BoardModel *getActiveBoard();

    void setActiveBoardIndex(int nValue);

    const ClientController *getClientController() const { return clientController; }
    ClientController *getClientController() { return clientController; }
    void resetController(const NewBoardOptions *nbo);

    void generateNewStep();
Q_SIGNALS:
    void collectionBoundsChanged(int newSize);
    void activeBoardIndexChanged(int nIndex);
    void activeBoardModelChanged(const BoardModel *const);
    void boardSizeChanged(const QSize newSize);

public Q_SLOTS:
    void externalSetStep(int);

private:
    void reset(const NewBoardOptions *nbo);

    inline const NewBoardOptions *getCurrentNewBoardOptions() const { return newBoardOptions; }
    QVector<BoardModel*> data;
    BoardModel *current;

    const NewBoardOptions *newBoardOptions;
    void setBoardOptions(const NewBoardOptions *nbo);

private:
    void newStartBoard();
    int activeBoard;
    ClientController *clientController;

};

#endif // BOARDMODELCOLLECTIONCONTROLLER_H
