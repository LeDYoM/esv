#ifndef MVCONTROLLER_H
#define MVCONTROLLER_H

#include <QApplication>
#include "mainwindow.h"
#include "filemanager.h"

class BoardModelCollectionController;
class NewBoardOptions;

class MVController : public QApplication
{
	Q_OBJECT

public:
    MVController(int &argc, char **argv, int applicationFlags = ApplicationFlags);
    virtual ~MVController();

    void newSession();

Q_SIGNALS:
    void boardLoaded(const BoardData *boardData);
    void sessionLoaded();

private:
	void connectAll();

    MainWindow window;
    FileManager fileManager;
    const NewBoardOptions *currentNewBoardOptions;
    BoardModelCollectionController *bmCollectionController;
};

#endif // MVCONTROLLER_H
