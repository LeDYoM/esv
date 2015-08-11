#include "newboardoptionsdialog.h"
#include "newboardoptions.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QCheckBox>

NewBoardOptionsDialog::NewBoardOptionsDialog(const NewBoardOptions * const nbo, QWidget *parent) :
    QDialog(parent,
            //Qt::CustomizeWindowHint
            Qt::Dialog | Qt::WindowTitleHint
            )
{
    Q_ASSERT(nbo);

    setModal(true);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *horizontal1 = new QHBoxLayout;
    QHBoxLayout *horizontal2 = new QHBoxLayout;
    QVBoxLayout *boardWidthGroup = new QVBoxLayout;
    QVBoxLayout *boardHeightGroup = new QVBoxLayout;
    QHBoxLayout *boardWidthMiniGroup = new QHBoxLayout;
    QHBoxLayout *boardHeightMiniGroup = new QHBoxLayout;
    //QHBoxLayout *buttonsLayout = new QHBoxLayout;

    QLabel *label1 = new QLabel(tr("New board size:"));
    QLabel *label2 = new QLabel(tr("Width:"));
    QLabel *label3 = new QLabel(tr("Height:"));

    sliderWidth = new QSlider(Qt::Horizontal,this);
    sliderHeight = new QSlider(Qt::Horizontal,this);
    boardWidthSpinBox = new QSpinBox(this);
    boardHeightSpinBox = new QSpinBox(this);

    loopCheck = new QCheckBox(tr("Loop board"),this);

    boardWidthMiniGroup->addWidget(sliderWidth);
    boardWidthMiniGroup->addWidget(boardWidthSpinBox);
    boardHeightMiniGroup->addWidget(sliderHeight);
    boardHeightMiniGroup->addWidget(boardHeightSpinBox);

    boardWidthGroup->addWidget(label2);
    boardWidthGroup->addLayout(boardWidthMiniGroup);

    boardHeightGroup->addWidget(label3);
    boardHeightGroup->addLayout(boardHeightMiniGroup);

    horizontal1->addWidget(label1);
    horizontal1->addLayout(boardWidthGroup);
    horizontal1->addLayout(boardHeightGroup);

    horizontal2->addWidget(loopCheck);

    mainLayout->addLayout(horizontal1);
    mainLayout->addLayout(horizontal2);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    layout()->setSizeConstraint( QLayout::SetFixedSize );

    sliderWidth->setMinimum(3);
    sliderWidth->setMaximum(1024);

    sliderHeight->setMinimum(3);
    sliderHeight->setMaximum(1024);

    boardWidthSpinBox->setMinimum(3);
    boardWidthSpinBox->setMaximum(1024);

    boardHeightSpinBox->setMinimum(3);
    boardHeightSpinBox->setMaximum(1024);

    QObject::connect(sliderWidth,&QSlider::valueChanged,[&](int value)
    {
        if (boardWidthSpinBox->value() != value)
        {
            boardWidthSpinBox->setValue(value);
        }
    });

    QObject::connect(sliderHeight,&QSlider::valueChanged,[&](int value)
    {
        if (boardHeightSpinBox->value() != value)
        {
            boardHeightSpinBox->setValue(value);
        }
    });

    QObject::connect(boardWidthSpinBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[&](int value)
    {
        if (sliderWidth->value() != value)
        {
            sliderWidth->setValue(value);
        }
    });

    QObject::connect(boardHeightSpinBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[&](int value)
    {
        if (sliderHeight->value() != value)
        {
            sliderHeight->setValue(value);
        }
    });

    sliderWidth->setValue(nbo->newBoardWidth());
    sliderHeight->setValue(nbo->newBoardHeight());
    loopCheck->setChecked(nbo->loopBoard());

}

void NewBoardOptionsDialog::updateNewBoardOptions(NewBoardOptions * const nbo)
{
    nbo->setNewBoardWidth(sliderWidth->value());
    nbo->setNewBoardHeight(sliderHeight->value());
    nbo->setLoopBoard(loopCheck->isChecked());
}

