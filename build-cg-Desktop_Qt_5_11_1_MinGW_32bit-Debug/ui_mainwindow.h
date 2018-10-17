/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "bitmap.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *camera_left;
    QPushButton *camera_right;
    QPushButton *camera_bottom;
    QPushButton *camera_top;
    QPushButton *camera_move_left;
    QPushButton *camera_move_right;
    QPushButton *camera_move_up;
    QPushButton *camera_move_down;
    QPushButton *cam_scale_less;
    QPushButton *cam_scale_higher;
    Bitmap *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(833, 702);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(670, 80, 121, 121));
        QFont font;
        font.setPointSize(20);
        pushButton->setFont(font);
        camera_left = new QPushButton(centralWidget);
        camera_left->setObjectName(QStringLiteral("camera_left"));
        camera_left->setGeometry(QRect(660, 270, 51, 41));
        camera_right = new QPushButton(centralWidget);
        camera_right->setObjectName(QStringLiteral("camera_right"));
        camera_right->setGeometry(QRect(760, 270, 51, 41));
        camera_bottom = new QPushButton(centralWidget);
        camera_bottom->setObjectName(QStringLiteral("camera_bottom"));
        camera_bottom->setGeometry(QRect(710, 310, 51, 41));
        camera_top = new QPushButton(centralWidget);
        camera_top->setObjectName(QStringLiteral("camera_top"));
        camera_top->setGeometry(QRect(710, 230, 51, 41));
        camera_move_left = new QPushButton(centralWidget);
        camera_move_left->setObjectName(QStringLiteral("camera_move_left"));
        camera_move_left->setGeometry(QRect(660, 410, 51, 41));
        camera_move_right = new QPushButton(centralWidget);
        camera_move_right->setObjectName(QStringLiteral("camera_move_right"));
        camera_move_right->setGeometry(QRect(760, 410, 51, 41));
        camera_move_up = new QPushButton(centralWidget);
        camera_move_up->setObjectName(QStringLiteral("camera_move_up"));
        camera_move_up->setGeometry(QRect(710, 370, 51, 41));
        camera_move_down = new QPushButton(centralWidget);
        camera_move_down->setObjectName(QStringLiteral("camera_move_down"));
        camera_move_down->setGeometry(QRect(710, 450, 51, 41));
        cam_scale_less = new QPushButton(centralWidget);
        cam_scale_less->setObjectName(QStringLiteral("cam_scale_less"));
        cam_scale_less->setGeometry(QRect(640, 510, 41, 31));
        cam_scale_higher = new QPushButton(centralWidget);
        cam_scale_higher->setObjectName(QStringLiteral("cam_scale_higher"));
        cam_scale_higher->setGeometry(QRect(700, 510, 41, 31));
        widget = new Bitmap(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 600, 600));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\221\320\230\320\237", nullptr));
        camera_left->setText(QApplication::translate("MainWindow", "cam r_ll", nullptr));
        camera_right->setText(QApplication::translate("MainWindow", "cam r_r", nullptr));
        camera_bottom->setText(QApplication::translate("MainWindow", "cam r_b", nullptr));
        camera_top->setText(QApplication::translate("MainWindow", "cam r_t", nullptr));
        camera_move_left->setText(QApplication::translate("MainWindow", "m left", nullptr));
        camera_move_right->setText(QApplication::translate("MainWindow", "m right", nullptr));
        camera_move_up->setText(QApplication::translate("MainWindow", "m up", nullptr));
        camera_move_down->setText(QApplication::translate("MainWindow", "m down", nullptr));
        cam_scale_less->setText(QApplication::translate("MainWindow", "-", nullptr));
        cam_scale_higher->setText(QApplication::translate("MainWindow", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
