#include "mainwindow.h"
#include "mainscene.h"
#include "boardmodel.h"
#include "dialogmanager.h"
#include "esvgraphicsview.h"
#include "newboardoptions.h"
#include "newboardoptionsdialog.h"
#include "statecolors.h"
#include "zoomer.h"

#include <QLabel>
#include <QLayout>
#include <QSlider>
#include <QKeyEvent>
#include <QMenuBar>
#include <QDebug>
#include <QStyle>
#include <QGroupBox>
#include <QPushButton>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), windowSurface{nullptr}, view{nullptr}, mScene{nullptr},
      newBoardOptionsDialog{nullptr},stateColors{nullptr},zoomer{nullptr}
{
    fileDialogManager = new DialogManager(this);
    newBoardOptions = new NewBoardOptions(this);
    stateColors = new StateColors(this);
    zoomer = new Zoomer({0.01,0.02,0.05,0.1,0.15,0.25,0.33,0.5,0.75,0.85,
                        1,1.15,1.25,1.33,1.5,1.75,1.85,2,2.5,3,4,5},10,this);
    addStateColors();
    addMenu();
    addMainWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::ensureMainSceneIsVisible()
{
    Q_ASSERT(windowSurface);
    windowSurface->setVisible(true);
}

void MainWindow::addMainWidgets()
{
    Q_ASSERT(!windowSurface);

    windowSurface = new QWidget(this);

    QHBoxLayout *mainWindowLayer = new QHBoxLayout();
    QVBoxLayout *boardLeftLayer = new QVBoxLayout();
    QHBoxLayout *topBoardLayer = new QHBoxLayout();
    QVBoxLayout *boardRightLayer = new QVBoxLayout();
    QLabel *boardLabel = new QLabel("Board:");
    boardSlider = new QSlider();
    boardSlider->setOrientation(Qt::Orientation::Horizontal);
    topBoardLayer->addWidget(boardLabel);
    topBoardLayer->addWidget(boardSlider);

    boardLeftLayer->addLayout(topBoardLayer);

    view = new ESVGraphicsView(this);

    mScene = new MainScene(QRect(0, 0, 300, 300), this);
    view->setScene(mScene);
    boardLeftLayer->addWidget(view);

    boardRightLayer->addWidget(addOptionsWidget(this));

    mainWindowLayer->addLayout(boardLeftLayer);
    mainWindowLayer->addLayout(boardRightLayer);

    windowSurface->setLayout(mainWindowLayer);
    setCentralWidget(windowSurface);
    windowSurface->setVisible(false);

    // Internal connections
    QObject::connect(boardSlider,&QSlider::valueChanged,this,&MainWindow::setStep);
}

QWidget *MainWindow::addOptionsWidget(QWidget *parent)
{
    QGroupBox *runtimeOptionsBox = new QGroupBox(tr("Runtime options"),parent);
    QVBoxLayout *runtimeOptionsLayout = new QVBoxLayout();
    QHBoxLayout *zoomLayout = new QHBoxLayout();
    QLabel *zoomTextLabel = new QLabel(tr("Zoom:"));
    QSpinBox *zoomSpin = new QSpinBox(parent);
    zoomSpin->setSuffix(" %");
    zoomSpin->setSingleStep(10);
    zoomSpin->setMaximum(500);
    zoomSpin->setValue(100);
    QObject::connect(zoomSpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[&](int value)
    {
        zoomer->externSetValue((float)value/100.0f);
        view->setZoom(QVector2D(zoomer->getCurrentZoomValue(),zoomer->getCurrentZoomValue()));
    });

    zoomLayout->addWidget(zoomTextLabel);
    zoomLayout->addWidget(zoomSpin);
    runtimeOptionsLayout->addLayout(zoomLayout);

    runtimeOptionsBox->setLayout(runtimeOptionsLayout);
    return runtimeOptionsBox;
}

void MainWindow::addMenu()
{
    auto newAction = new QAction(tr("&New session"), this);
    //newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Start a new session"));
    connect(newAction, SIGNAL(triggered()), this, SIGNAL(newSession()));

    auto loadBoardAction = new QAction(tr("&Load board"), this);
//    loadBoardAction->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
//    loadBoardAction->setIcon(QIcon::fromTheme("application-exit"));
//    loadBoardAction->setShortcut(QKeySequence::Open);
    loadBoardAction->setStatusTip(tr("Load a new board and start a new session"));
    connect(loadBoardAction, &QAction::triggered, [&]()
    {
        bool result = fileDialogManager->showOpenBoard();
        if (result)
        {
            Q_EMIT loadBoard(fileDialogManager->getBoardFileName());
        }
    });

    auto loadSessionAction = new QAction(tr("&Load session"), this);
    loadSessionAction->setShortcut(QKeySequence::Open);
    loadSessionAction->setStatusTip(tr("Load a session"));
/*
    connect(loadBoardAction, &QAction::triggered, [&]()
    {
        bool result = fileDialogManager->showOpenBoard();
        if (result)
        {
            Q_EMIT loadBoard(fileDialogManager->getBoardFileName());
        }
    });
    */

    auto saveBoardAction = new QAction(tr("&Save board"), this);
    saveBoardAction->setShortcut(QKeySequence::Save);
    saveBoardAction->setStatusTip(tr("Save the current selected board"));
    connect(saveBoardAction, &QAction::triggered, [&]()
    {
        bool result = fileDialogManager->showSaveBoard();
        if (result)
        {
            Q_EMIT saveBoard(fileDialogManager->getBoardFileName());
        }
    });

    auto saveSessionAction = new QAction(tr("Save session"), this);
//    saveSessionAction.setShortcut(QKeySequence::SaveAs);
    saveSessionAction->setStatusTip(tr("Save the current session"));

    auto exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    /////////////////////////////////////////////////////////////////////
    auto goPreviousAction = new QAction(tr("Back"), this);
    goPreviousAction->setStatusTip(tr("Go one step back"));
    goPreviousAction->setShortcut(tr("A"));
    connect(goPreviousAction, SIGNAL(triggered()), this, SIGNAL(previousStep()));

    auto goNextAction = new QAction(tr("Next"), this);
    goNextAction->setStatusTip(tr("Go one step forward"));
    goNextAction->setShortcut(tr("D"));
    connect(goNextAction, SIGNAL(triggered()), this, SIGNAL(nextStep()));


    auto zoomInAction = new QAction(tr("Zoom in"), this);
    zoomInAction->setStatusTip(tr("Increment zoom in the center"));
    zoomInAction->setShortcut(tr("+"));
    connect(zoomInAction, SIGNAL(triggered()), this, SIGNAL(zoomIn()));

    auto zoomOutAction = new QAction(tr("Zoom out"), this);
    zoomOutAction->setStatusTip(tr("Decrement zoom in the center"));
    zoomOutAction->setShortcut(tr("-"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SIGNAL(zoomOut()));

    auto resetZoomAction = new QAction(tr("Reset zoom"), this);
    resetZoomAction->setStatusTip(tr("Resets zoom to normal state"));
    resetZoomAction->setShortcut(tr("*"));
    connect(resetZoomAction, SIGNAL(triggered()), this, SIGNAL(resetZoom()));

    /////////////////////////////////////////////////////////////////////

    auto viewNewBoardOptions = new QAction("New board options", this);
    viewNewBoardOptions->setStatusTip(tr("Toggle view of new board options"));
    connect(viewNewBoardOptions, &QAction::triggered, this, &MainWindow::showNewBoardOptionsDialog);
    //    viewNewBoardOptions->setCheckable(true);


    /////////////////////////////////////////////////////////////////////
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(newAction);
    fileMenu->addAction(loadBoardAction);
    fileMenu->addAction(loadSessionAction);
    fileMenu->addAction(saveBoardAction);
    fileMenu->addAction(saveSessionAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    auto editMenu = menuBar()->addMenu(tr("&Edit"));

    editMenu->addAction(goPreviousAction);
    editMenu->addAction(goNextAction);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);
    editMenu->addAction(resetZoomAction);

    auto options = menuBar()->addMenu(tr("&Options"));
    options->addAction(viewNewBoardOptions);

//    viewMenu->addAction

    // Internal connections
    QObject::connect(this,SIGNAL(zoomIn()),this,SLOT(onZoomIn()));
    QObject::connect(this,SIGNAL(zoomOut()),this,SLOT(onZoomOut()));
    QObject::connect(this,SIGNAL(resetZoom()),this,SLOT(onResetZoom()));
}

void MainWindow::addStateColors()
{
    stateColors->setColor(QColor(255,0,0),1);
}

void MainWindow::onActiveBoardModelChanged(const BoardModel * const bModel)
{
    mScene->doBoardViewUpdate(bModel);
}

void MainWindow::onCollectionBoundsChanged(int size)
{
    Q_ASSERT(size>-1);
    Q_ASSERT(boardSlider);

    boardSlider->setMinimum(0);
    boardSlider->setMaximum(size);

    if (!boardSlider->isVisible())
        boardSlider->setVisible(true);

    qDebug() << "esvMainWindow: boardSlider: min:"<<boardSlider->minimum()
             << " max: "<<boardSlider->maximum()<<" value: "<<boardSlider->value();

}

void MainWindow::onActiveBoardIndexChanged(int nValue)
{
    Q_ASSERT(boardSlider);
    Q_ASSERT(nValue>=boardSlider->minimum());
    Q_ASSERT(nValue<=boardSlider->maximum());
    boardSlider->setValue(nValue);
}

void MainWindow::showNewBoardOptionsDialog()
{
    Q_ASSERT(!newBoardOptionsDialog);
    Q_ASSERT(newBoardOptions);
    newBoardOptionsDialog = new NewBoardOptionsDialog(newBoardOptions,this);
    newBoardOptionsDialog->show();
    //QObject::connect(newBoardOptionsDialog,&QDialog::finished,this,MainWindow::newBoardOptionsDialogFinished);
}

void MainWindow::newBoardOptionsDialogFinished(int result)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "result: "<<result;
    Q_ASSERT(newBoardOptionsDialog);
    Q_ASSERT(newBoardOptions);
    if (result==QDialog::DialogCode::Accepted)
    {
        newBoardOptionsDialog->updateNewBoardOptions(newBoardOptions);
    }

    qDebug() << "BoardOptions:";
    qDebug() << "\tSize: " << newBoardOptions->newBoardSize();
    qDebug() << "Loop board: " << newBoardOptions->loopBoard();


    newBoardOptionsDialog->deleteLater();
    newBoardOptionsDialog = nullptr;
}

void MainWindow::onZoomIn()
{
    zoomer->zoomIn();
    view->setZoom(QVector2D(zoomer->getCurrentZoomValue(),zoomer->getCurrentZoomValue()));
}

void MainWindow::onZoomOut()
{
    zoomer->zoomOut();
    view->setZoom(QVector2D(zoomer->getCurrentZoomValue(),zoomer->getCurrentZoomValue()));
}

void MainWindow::onResetZoom()
{
    view->setZoom(QVector2D(1.0f,1.0f));
}
