#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QSlider>

class MainScene;
class BoardModel;
class DialogManager;
class ESVClient;
class ESVGraphicsView;
class NewBoardOptions;
class NewBoardOptionsDialog;
class Zoomer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainScene *getMainScene() const { return mScene; }
    ESVGraphicsView *getView() const { return view; }
    void ensureMainSceneIsVisible();

    const NewBoardOptions *selectedNewBoardOptions() const { return newBoardOptions; }

public Q_SLOTS:
    void onActiveBoardModelChanged(const BoardModel *const);
    void onCollectionBoundsChanged(int);
    void onActiveBoardIndexChanged(int);

    void showNewBoardOptionsDialog();
    void newBoardOptionsDialogFinished(int result);

    void onZoomIn();
    void onZoomOut();
    void onResetZoom();

Q_SIGNALS:
    void nextStep();
    void previousStep();
    void setStep(int);

    void saveBoard(QString);
    void saveSession(QString);
    void loadBoard(QString);
    void loadSession(QString);
    void newSession();
    void zoomIn();
    void zoomOut();
    void resetZoom();

private:
    void addMainWidgets();
    void addMenu();
    QWidget *addOptionsWidget(QWidget *parent);
    QWidget *windowSurface;
    ESVGraphicsView *view;
    MainScene *mScene;
    DialogManager *fileDialogManager;
    QSlider *boardSlider;
    NewBoardOptionsDialog *newBoardOptionsDialog;
    NewBoardOptions *newBoardOptions;
    Zoomer *zoomer;
};

#endif // MAINWINDOW_H
