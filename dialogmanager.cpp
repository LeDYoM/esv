#include "dialogmanager.h"

#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>

DialogManager::DialogManager(QWidget *parent)
    : QObject(parent),currentBoardFileName{""},currentSessionFileName{""},
      parentWidget{parent}
{
}

DialogManager::~DialogManager()
{

}

bool DialogManager::showOpenBoard()
{
    QString fn = QFileDialog::getOpenFileName(parentWidget, tr("Open Board File..."),
        QString(),getFileDialogFileSelection());

    return setCurrentBoardFileName(fn);
}

bool DialogManager::showOpenSession()
{
    return false;
}

bool DialogManager::showSaveBoard()
{
    QString fn = QFileDialog::getSaveFileName(parentWidget, tr("Save Board File..."),
        QString(), getFileDialogFileSelection());

    return setCurrentBoardFileName(fn);
}

bool DialogManager::showSaveSession()
{
    return false;
}

const QString DialogManager::getFileDialogFileSelection() const
{
    return tr("ESV Board Files (*.ebf);;All Files (*)");
}

bool DialogManager::setCurrentBoardFileName(const QString fn)
{
    if (!fn.isEmpty())
        currentBoardFileName = fn;
    return !fn.isEmpty();
}

bool DialogManager::setCurrentSessionFileName(const QString fn)
{
    if (!fn.isEmpty())
        currentSessionFileName = fn;
    return !fn.isEmpty();
}
