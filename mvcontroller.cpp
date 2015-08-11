#include "mvcontroller.h"
#include "mainscene.h"
#include "boardmodel.h"
#include "boardmodelcollectioncontroller.h"
#include "clientcontroller.h"
#include "newboardoptions.h"
#include "mainwindow.h"
#include "esvgraphicsview.h"
#include <QGraphicsScene>
#include <QDebug>

MVController::MVController(int &argc, char **argv, int applicationFlags)
    : QApplication(argc,argv,applicationFlags),
      currentNewBoardOptions{nullptr}, bmCollectionController{nullptr}
{
    window.show();

    bmCollectionController = new BoardModelCollectionController(this);
    connectAll();

    newSession();
}

MVController::~MVController()
{
}

void MVController::connectAll()
{
    QObject::connect(&window, &MainWindow::nextStep, bmCollectionController, &BoardModelCollectionController::nextStep);
    QObject::connect(&window, &MainWindow::previousStep, bmCollectionController, &BoardModelCollectionController::previousStep);
    QObject::connect(&window, &MainWindow::setStep, bmCollectionController,&BoardModelCollectionController::externalSetStep);

    QObject::connect(bmCollectionController, &BoardModelCollectionController::collectionBoundsChanged,&window,&MainWindow::onCollectionBoundsChanged);
    QObject::connect(bmCollectionController, &BoardModelCollectionController::activeBoardModelChanged,&window,&MainWindow::onActiveBoardModelChanged);
    QObject::connect(bmCollectionController, &BoardModelCollectionController::activeBoardIndexChanged,&window,&MainWindow::onActiveBoardIndexChanged);

    QObject::connect(&window, &MainWindow::newSession,[&]()
    {
        newSession();
    });

    QObject::connect(&window, &MainWindow::loadBoard,[&](QString fName)
    {
        BoardData bData = fileManager.loadBoard(fName);

        bmCollectionController->onBoardLoaded(&bData,nullptr);
    });

    connect(&window, &MainWindow::saveBoard,[&](QString fName)
    {
        fileManager.saveBoard(fName,
                              FileManager::BoardFormatType::BinaryNative,
                              bmCollectionController->getActiveBoard());
    });
}

void MVController::newSession()
{
    currentNewBoardOptions = window.selectedNewBoardOptions();
    window.ensureMainSceneIsVisible();
    window.getMainScene()->resetCache();

    bmCollectionController->resetController(currentNewBoardOptions);
    bmCollectionController->nextStep();

    window.getView()->adjustToWindowZoom();

}
