/********************************************************************************
** Form generated from reading UI file 'solution.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLUTION_H
#define UI_SOLUTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Solution
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowserSolution;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Solution)
    {
        if (Solution->objectName().isEmpty())
            Solution->setObjectName("Solution");
        Solution->resize(800, 600);
        Solution->setStyleSheet(QString::fromUtf8("background-color: rgb(226, 228, 255);"));
        centralwidget = new QWidget(Solution);
        centralwidget->setObjectName("centralwidget");
        textBrowserSolution = new QTextBrowser(centralwidget);
        textBrowserSolution->setObjectName("textBrowserSolution");
        textBrowserSolution->setGeometry(QRect(100, 80, 601, 421));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(10);
        textBrowserSolution->setFont(font);
        textBrowserSolution->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 10, 401, 51));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(2, 2, 2);\n"
"background-color: rgb(255, 255, 255);"));
        Solution->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Solution);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        Solution->setMenuBar(menubar);
        statusbar = new QStatusBar(Solution);
        statusbar->setObjectName("statusbar");
        Solution->setStatusBar(statusbar);

        retranslateUi(Solution);

        QMetaObject::connectSlotsByName(Solution);
    } // setupUi

    void retranslateUi(QMainWindow *Solution)
    {
        Solution->setWindowTitle(QCoreApplication::translate("Solution", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271", nullptr));
        label->setText(QCoreApplication::translate("Solution", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271:</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Solution: public Ui_Solution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLUTION_H
