/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <myview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Pixels;
    QAction *actionDownload_Pixels;
    QAction *actionReset_Pixels;
    QAction *actionSet_Board_Size;
    QAction *actionCalculate_Probability;
    QAction *actionChoose_Layer;
    QAction *actionAdd_Layer;
    QAction *actionDelete_Layer;
    QAction *actionParse_Image;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *addPixelButton;
    QRadioButton *removePixelButton;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_4;
    QSlider *verticalSlider;
    QGridLayout *gridLayout_2;
    QPushButton *up20Button;
    QPushButton *upButton;
    QPushButton *left20Button;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *right20Button;
    QPushButton *downButton;
    QPushButton *down20Button;
    QPushButton *topleft_Button;
    QPushButton *bottomleft_Button;
    QPushButton *topright_Button;
    QPushButton *bottomright_Button;
    QSlider *horizontalSlider;
    QSpacerItem *verticalSpacer_3;
    QPushButton *fullSizeButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *picturePreviewLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *currentLayerLabel;
    QSpacerItem *horizontalSpacer;
    MyView *MyViewWidget;
    QMenuBar *menuBar;
    QMenu *menumenu;
    QMenu *menuAlgorithm;
    QMenu *menuBoard;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1098, 837);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/media-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionSave_Pixels = new QAction(MainWindow);
        actionSave_Pixels->setObjectName(QString::fromUtf8("actionSave_Pixels"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Pixels->setIcon(icon1);
        actionDownload_Pixels = new QAction(MainWindow);
        actionDownload_Pixels->setObjectName(QString::fromUtf8("actionDownload_Pixels"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload_Pixels->setIcon(icon2);
        actionReset_Pixels = new QAction(MainWindow);
        actionReset_Pixels->setObjectName(QString::fromUtf8("actionReset_Pixels"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset_Pixels->setIcon(icon3);
        actionSet_Board_Size = new QAction(MainWindow);
        actionSet_Board_Size->setObjectName(QString::fromUtf8("actionSet_Board_Size"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/th-small-outline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Board_Size->setIcon(icon4);
        actionCalculate_Probability = new QAction(MainWindow);
        actionCalculate_Probability->setObjectName(QString::fromUtf8("actionCalculate_Probability"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalculate_Probability->setIcon(icon5);
        actionChoose_Layer = new QAction(MainWindow);
        actionChoose_Layer->setObjectName(QString::fromUtf8("actionChoose_Layer"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("icons/waves.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionChoose_Layer->setIcon(icon6);
        actionAdd_Layer = new QAction(MainWindow);
        actionAdd_Layer->setObjectName(QString::fromUtf8("actionAdd_Layer"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/document-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_Layer->setIcon(icon7);
        actionDelete_Layer = new QAction(MainWindow);
        actionDelete_Layer->setObjectName(QString::fromUtf8("actionDelete_Layer"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("icons/document-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_Layer->setIcon(icon8);
        actionParse_Image = new QAction(MainWindow);
        actionParse_Image->setObjectName(QString::fromUtf8("actionParse_Image"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionParse_Image->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addPixelButton = new QRadioButton(centralWidget);
        addPixelButton->setObjectName(QString::fromUtf8("addPixelButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addPixelButton->sizePolicy().hasHeightForWidth());
        addPixelButton->setSizePolicy(sizePolicy1);
        addPixelButton->setChecked(true);

        verticalLayout->addWidget(addPixelButton);

        removePixelButton = new QRadioButton(centralWidget);
        removePixelButton->setObjectName(QString::fromUtf8("removePixelButton"));
        sizePolicy1.setHeightForWidth(removePixelButton->sizePolicy().hasHeightForWidth());
        removePixelButton->setSizePolicy(sizePolicy1);
        removePixelButton->setChecked(false);

        verticalLayout->addWidget(removePixelButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalSlider->sizePolicy().hasHeightForWidth());
        verticalSlider->setSizePolicy(sizePolicy2);
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(20);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(true);

        gridLayout_4->addWidget(verticalSlider, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        up20Button = new QPushButton(centralWidget);
        up20Button->setObjectName(QString::fromUtf8("up20Button"));
        up20Button->setMinimumSize(QSize(50, 50));
        up20Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(up20Button, 0, 2, 1, 1);

        upButton = new QPushButton(centralWidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setMinimumSize(QSize(50, 50));
        upButton->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(upButton, 1, 2, 1, 1);

        left20Button = new QPushButton(centralWidget);
        left20Button->setObjectName(QString::fromUtf8("left20Button"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(left20Button->sizePolicy().hasHeightForWidth());
        left20Button->setSizePolicy(sizePolicy3);
        left20Button->setMinimumSize(QSize(50, 50));
        left20Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(left20Button, 2, 0, 1, 1);

        leftButton = new QPushButton(centralWidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        sizePolicy3.setHeightForWidth(leftButton->sizePolicy().hasHeightForWidth());
        leftButton->setSizePolicy(sizePolicy3);
        leftButton->setMinimumSize(QSize(50, 50));
        leftButton->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(leftButton, 2, 1, 1, 1);

        rightButton = new QPushButton(centralWidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        sizePolicy3.setHeightForWidth(rightButton->sizePolicy().hasHeightForWidth());
        rightButton->setSizePolicy(sizePolicy3);
        rightButton->setMinimumSize(QSize(50, 50));
        rightButton->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(rightButton, 2, 3, 1, 1);

        right20Button = new QPushButton(centralWidget);
        right20Button->setObjectName(QString::fromUtf8("right20Button"));
        sizePolicy3.setHeightForWidth(right20Button->sizePolicy().hasHeightForWidth());
        right20Button->setSizePolicy(sizePolicy3);
        right20Button->setMinimumSize(QSize(50, 50));
        right20Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(right20Button, 2, 4, 1, 1);

        downButton = new QPushButton(centralWidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setMinimumSize(QSize(50, 50));
        downButton->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(downButton, 3, 2, 1, 1);

        down20Button = new QPushButton(centralWidget);
        down20Button->setObjectName(QString::fromUtf8("down20Button"));
        down20Button->setMinimumSize(QSize(50, 50));
        down20Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(down20Button, 4, 2, 1, 1);

        topleft_Button = new QPushButton(centralWidget);
        topleft_Button->setObjectName(QString::fromUtf8("topleft_Button"));
        topleft_Button->setMinimumSize(QSize(50, 50));
        topleft_Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(topleft_Button, 0, 0, 1, 1);

        bottomleft_Button = new QPushButton(centralWidget);
        bottomleft_Button->setObjectName(QString::fromUtf8("bottomleft_Button"));
        bottomleft_Button->setMinimumSize(QSize(50, 50));
        bottomleft_Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(bottomleft_Button, 4, 0, 1, 1);

        topright_Button = new QPushButton(centralWidget);
        topright_Button->setObjectName(QString::fromUtf8("topright_Button"));
        topright_Button->setMinimumSize(QSize(50, 50));
        topright_Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(topright_Button, 0, 4, 1, 1);

        bottomright_Button = new QPushButton(centralWidget);
        bottomright_Button->setObjectName(QString::fromUtf8("bottomright_Button"));
        bottomright_Button->setMinimumSize(QSize(50, 50));
        bottomright_Button->setMaximumSize(QSize(50, 50));

        gridLayout_2->addWidget(bottomright_Button, 4, 4, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setSizeIncrement(QSize(700, 700));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(horizontalSlider, 1, 0, 1, 2);


        verticalLayout->addLayout(gridLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        fullSizeButton = new QPushButton(centralWidget);
        fullSizeButton->setObjectName(QString::fromUtf8("fullSizeButton"));

        verticalLayout->addWidget(fullSizeButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        picturePreviewLabel = new QLabel(centralWidget);
        picturePreviewLabel->setObjectName(QString::fromUtf8("picturePreviewLabel"));
        sizePolicy3.setHeightForWidth(picturePreviewLabel->sizePolicy().hasHeightForWidth());
        picturePreviewLabel->setSizePolicy(sizePolicy3);
        picturePreviewLabel->setMinimumSize(QSize(300, 200));
        picturePreviewLabel->setMaximumSize(QSize(300, 200));
        picturePreviewLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(picturePreviewLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        currentLayerLabel = new QLabel(centralWidget);
        currentLayerLabel->setObjectName(QString::fromUtf8("currentLayerLabel"));
        currentLayerLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(currentLayerLabel);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        MyViewWidget = new MyView(centralWidget);
        MyViewWidget->setObjectName(QString::fromUtf8("myViewWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(100);
        sizePolicy4.setVerticalStretch(100);
        sizePolicy4.setHeightForWidth(MyViewWidget->sizePolicy().hasHeightForWidth());
        MyViewWidget->setSizePolicy(sizePolicy4);
        MyViewWidget->setMinimumSize(QSize(700, 700));
        MyViewWidget->setMaximumSize(QSize(100500, 100500));
        MyViewWidget->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_2->addWidget(MyViewWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1098, 28));
        menumenu = new QMenu(menuBar);
        menumenu->setObjectName(QString::fromUtf8("menumenu"));
        menuAlgorithm = new QMenu(menuBar);
        menuAlgorithm->setObjectName(QString::fromUtf8("menuAlgorithm"));
        menuBoard = new QMenu(menuBar);
        menuBoard->setObjectName(QString::fromUtf8("menuBoard"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menumenu->menuAction());
        menuBar->addAction(menuBoard->menuAction());
        menuBar->addAction(menuAlgorithm->menuAction());
        menuAlgorithm->addAction(actionCalculate_Probability);
        menuAlgorithm->addAction(actionParse_Image);
        menuBoard->addAction(actionSave_Pixels);
        menuBoard->addAction(actionDownload_Pixels);
        menuBoard->addAction(actionReset_Pixels);
        menuBoard->addAction(actionSet_Board_Size);
        menuBoard->addAction(actionChoose_Layer);
        menuBoard->addAction(actionAdd_Layer);
        menuBoard->addAction(actionDelete_Layer);
        mainToolBar->addAction(actionSave_Pixels);
        mainToolBar->addAction(actionDownload_Pixels);
        mainToolBar->addAction(actionReset_Pixels);
        mainToolBar->addAction(actionSet_Board_Size);
        mainToolBar->addAction(actionChoose_Layer);
        mainToolBar->addAction(actionAdd_Layer);
        mainToolBar->addAction(actionDelete_Layer);
        mainToolBar->addSeparator();
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCalculate_Probability);
        mainToolBar->addAction(actionParse_Image);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Medvedev AI Chess", nullptr));
        actionSave_Pixels->setText(QCoreApplication::translate("MainWindow", "Save Pixels", nullptr));
        actionDownload_Pixels->setText(QCoreApplication::translate("MainWindow", "Download Pixels", nullptr));
        actionReset_Pixels->setText(QCoreApplication::translate("MainWindow", "Reset Pixels", nullptr));
        actionSet_Board_Size->setText(QCoreApplication::translate("MainWindow", "Set Boards Size", nullptr));
        actionCalculate_Probability->setText(QCoreApplication::translate("MainWindow", "Calculate Probability", nullptr));
        actionChoose_Layer->setText(QCoreApplication::translate("MainWindow", "Choose Layer", nullptr));
        actionAdd_Layer->setText(QCoreApplication::translate("MainWindow", "Add Layer", nullptr));
        actionDelete_Layer->setText(QCoreApplication::translate("MainWindow", "Delete Layer", nullptr));
        actionParse_Image->setText(QCoreApplication::translate("MainWindow", "Parse Image", nullptr));
        addPixelButton->setText(QCoreApplication::translate("MainWindow", "Add Pixel", nullptr));
        removePixelButton->setText(QCoreApplication::translate("MainWindow", "Remove Pixel", nullptr));
        up20Button->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        upButton->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        left20Button->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        leftButton->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        rightButton->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        right20Button->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        downButton->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        down20Button->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        topleft_Button->setText(QCoreApplication::translate("MainWindow", "TL", nullptr));
        bottomleft_Button->setText(QCoreApplication::translate("MainWindow", "BL", nullptr));
        topright_Button->setText(QCoreApplication::translate("MainWindow", "TR", nullptr));
        bottomright_Button->setText(QCoreApplication::translate("MainWindow", "BR", nullptr));
        fullSizeButton->setText(QCoreApplication::translate("MainWindow", "Show Full Size", nullptr));
        picturePreviewLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Current Layer:", nullptr));
        currentLayerLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        menumenu->setTitle(QString());
        menuAlgorithm->setTitle(QCoreApplication::translate("MainWindow", "Algorithm", nullptr));
        menuBoard->setTitle(QCoreApplication::translate("MainWindow", "Boards", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
