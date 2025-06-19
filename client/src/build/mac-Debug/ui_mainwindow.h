/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonSolveUrav;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *textBrowser_2;
    QSpacerItem *verticalSpacer;
    QLabel *labelVvod;
    QFormLayout *formLayout;
    QLabel *labelUrav1;
    QLineEdit *lineEditUrav1;
    QLabel *labelUrav2;
    QLineEdit *lineEditUrav2;
    QLabel *labelUrav3;
    QLineEdit *lineEditUrav3;
    QLabel *labelUrav4;
    QLineEdit *lineEditUrav4;
    QLabel *labelUrav5;
    QLineEdit *lineEditUrav5;
    QPushButton *pushButtonDelUrav_2;
    QPushButton *pushButtonAddUrav;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 598);
        MainWindow->setStyleSheet(QString::fromUtf8("color: rgb(31, 3, 54);\n"
"background-color: rgb(212, 229, 255);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButtonSolveUrav = new QPushButton(centralwidget);
        pushButtonSolveUrav->setObjectName("pushButtonSolveUrav");
        pushButtonSolveUrav->setGeometry(QRect(320, 510, 301, 61));
        pushButtonSolveUrav->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(60, 10, 801, 448));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setMaximumSize(QSize(16777215, 85));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(textBrowser);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        textBrowser_2 = new QTextBrowser(verticalLayoutWidget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(226, 242, 255);"));

        verticalLayout->addWidget(textBrowser_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        labelVvod = new QLabel(verticalLayoutWidget);
        labelVvod->setObjectName("labelVvod");
        labelVvod->setStyleSheet(QString::fromUtf8("background-color: rgb(196, 209, 255);"));

        verticalLayout->addWidget(labelVvod);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelUrav1 = new QLabel(verticalLayoutWidget);
        labelUrav1->setObjectName("labelUrav1");
        labelUrav1->setStyleSheet(QString::fromUtf8(""));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelUrav1);

        lineEditUrav1 = new QLineEdit(verticalLayoutWidget);
        lineEditUrav1->setObjectName("lineEditUrav1");
        lineEditUrav1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditUrav1);

        labelUrav2 = new QLabel(verticalLayoutWidget);
        labelUrav2->setObjectName("labelUrav2");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelUrav2);

        lineEditUrav2 = new QLineEdit(verticalLayoutWidget);
        lineEditUrav2->setObjectName("lineEditUrav2");
        lineEditUrav2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditUrav2);

        labelUrav3 = new QLabel(verticalLayoutWidget);
        labelUrav3->setObjectName("labelUrav3");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelUrav3);

        lineEditUrav3 = new QLineEdit(verticalLayoutWidget);
        lineEditUrav3->setObjectName("lineEditUrav3");
        lineEditUrav3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditUrav3);

        labelUrav4 = new QLabel(verticalLayoutWidget);
        labelUrav4->setObjectName("labelUrav4");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelUrav4);

        lineEditUrav4 = new QLineEdit(verticalLayoutWidget);
        lineEditUrav4->setObjectName("lineEditUrav4");
        lineEditUrav4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditUrav4);

        labelUrav5 = new QLabel(verticalLayoutWidget);
        labelUrav5->setObjectName("labelUrav5");
        labelUrav5->setStyleSheet(QString::fromUtf8(""));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelUrav5);

        lineEditUrav5 = new QLineEdit(verticalLayoutWidget);
        lineEditUrav5->setObjectName("lineEditUrav5");
        lineEditUrav5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditUrav5);


        verticalLayout->addLayout(formLayout);

        pushButtonDelUrav_2 = new QPushButton(centralwidget);
        pushButtonDelUrav_2->setObjectName("pushButtonDelUrav_2");
        pushButtonDelUrav_2->setGeometry(QRect(60, 460, 341, 29));
        pushButtonDelUrav_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButtonAddUrav = new QPushButton(centralwidget);
        pushButtonAddUrav->setObjectName("pushButtonAddUrav");
        pushButtonAddUrav->setGeometry(QRect(490, 460, 371, 29));
        pushButtonAddUrav->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        pushButtonSolveUrav->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\270\321\202\321\214  \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271!", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-style:italic; color:#120b5d;\">\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213 \320\273\320\270\320\275\320\265\320\271\320\275\321\213\321\205 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271 \320\277\320\265\321\200\320\262\320\276\320\263\320\276 \320\277\320"
                        "\276\321\200\321\217\320\264\320\272\320\260 \320\274\320\265\321\202\320\276\320\264\320\276\320\274 \320\223\320\260\321\203\321\201c\320\260.</span></p></body></html>", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<h2 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\342\234\205 </span><span style=\" font-size:10pt; font-weight:700; font-style:italic; text-decoration: underline;\">\320\237\320\276\320\264\320\264\320\265\321\200\320\266\320\270\320\262\320\260\320\265\320\274\321\213\320\265 \321\201\320\270\320\274\320\262\320\276\320\273\321\213 \320\270 \321\204\320\276\321\200\320\274\320"
                        "\260\321\202 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271</span></h2>\n"
"<h3 style=\" margin-top:14px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\360\237\223\214 \320\234\320\276\320\266\320\275\320\276 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214:</span></h3>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\360\237\224\244 <span style=\" font-weight:700;\">\320\233\320\260\321\202\320\270\320\275\321\201\320\272\320\270\320\265 \320\261\321\203\320\272\320\262\321\213</span> \320\264\320\273\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\321\205"
                        "<br />(\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: <span style=\" font-family:'Courier New';\">x</span>, <span style=\" font-family:'Courier New';\">y</span>, <span style=\" font-family:'Courier New';\">a</span>, <span style=\" font-family:'Courier New';\">b1</span>, <span style=\" font-family:'Courier New';\">z2</span>)</li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\360\237\224\242 <span style=\" font-weight:700;\">\320\247\320\270\321\201\320\273\320\260</span>, \320\262\320\272\320\273\321\216\321\207\320\260\321\217 \320\264\320\265\321\201\321\217\321\202\320\270\321\207\320\275\321\213\320\265<br />(\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: <span style=\" font-family:'Courier New';\">2</span>, <span style=\" font-family:'Courier New';\">3.5</span>, <span style=\" font-family:'Courier New';\">-0.25</span>)</li>\n"
"<li style=\" f"
                        "ont-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\236\225\342\236\226 <span style=\" font-weight:700;\">\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270:</span> <span style=\" font-family:'Courier New';\">+</span>, <span style=\" font-family:'Courier New';\">-</span>, <span style=\" font-family:'Courier New';\">=</span></li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\220\243 <span style=\" font-weight:700;\">\320\237\321\200\320\276\320\261\320\265\320\273\321\213</span><br />(\320\270\320\263\320\275\320\276\321\200\320\270\321\200\321\203\321\216\321\202\321\201\321\217 \320\277\321\200\320\270 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\265)</li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margi"
                        "n-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\360\237\223\220 \320\244\320\276\321\200\320\274\320\260\321\202 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\321\217:</span></p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\232\320\260\320\266\320\264\320\276\320\265 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \320\264\320\276\320\273\320\266\320\275\320\276 \320\261\321\213\321\202\321\214 <span style=\" font-weight:700;\">\320\273\320\270\320\275\320\265\320\271\320\275\321\213\320\274</span>.</li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\">\360\237\224\215 <span style=\" font-weight:700;\">\320\237\321\200\320\270\320\274\320\265\321\200 \320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276\320\263\320\276 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\321\217:</span></li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">2x + 3y = 5</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\342\232\240\357\270\217 \320\235\320\265 \320\277\320\276\320\264\320\264\320\265\321\200\320\266\320\270\320\262\320\260\320\265\321\202\321\201\321\217:</span></p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" font-size:10"
                        "pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\243\320\274\320\275\320\276\320\266\320\265\320\275\320\270\320\265 \321\201 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 <span style=\" font-family:'Courier New';\">*</span> (\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: <span style=\" font-family:'Courier New';\">2*x</span>)</li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\241\320\272\320\276\320\261\320\272\320\270 <span style=\" font-family:'Courier New';\">( )</span></li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\241\321\202\320\265\320\277\320\265\320\275\320\270"
                        " <span style=\" font-family:'Courier New';\">^</span></li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\224\320\265\320\273\320\265\320\275\320\270\320\265 <span style=\" font-family:'Courier New';\">/</span></li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\240\321\203\321\201\321\201\320\272\320\270\320\265 \320\261\321\203\320\272\320\262\321\213 (\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: <span style=\" font-family:'Courier New';\">\320\260</span>, <span style=\" font-family:'Courier New';\">\320\261</span>, <span style=\" font-family:'Courier New';\">\321\205</span>)</li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-r"
                        "ight:0px; -qt-block-indent:0; text-indent:0px;\">\342\235\214 \320\241\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\321\213\320\265 \321\201\320\270\320\274\320\262\320\276\320\273\321\213 <span style=\" font-family:'Courier New';\">@</span>, <span style=\" font-family:'Courier New';\">#</span>, <span style=\" font-family:'Courier New';\">!</span>, \320\270 \321\202.\320\277.</li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\360\237\247\240 \320\222\320\260\320\266\320\275\320\276 \320\277\320\276\320\274\320\275\320\270\321\202\321\214:</span></p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\242"
                        "\320\276\320\273\321\214\320\272\320\276 <span style=\" font-weight:700;\">\320\276\320\264\320\270\320\275 \320\267\320\275\320\260\320\272 </span><span style=\" font-family:'Courier New'; font-weight:700;\">=</span> \320\262 \320\272\320\260\320\266\320\264\320\276\320\274 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\270.</li>\n"
"<li style=\" font-size:10pt; font-style:italic;\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271 \320\274\320\276\320\266\320\265\321\202 \321\201\320\276\320\264\320\265\321\200\320\266\320\260\321\202\321\214 <span style=\" font-weight:700;\">\320\273\320\260\321\202\320\270\320\275\321\201\320\272\320\270\320\265 \320\261\321\203\320\272\320\262\321\213 \320\270 \321\206\320\270\321\204\321\200\321\213</span>:<br />\342\234\205 <span style=\" font-family:'Courier New';\">a1</span"
                        ">, <span style=\" font-family:'Courier New';\">b2</span>, <span style=\" font-family:'Courier New';\">x</span><br />\342\235\214 <span style=\" font-family:'Courier New';\">\320\260</span> (\321\200\321\203\321\201\321\201\320\272\320\260\321\217 &quot;\320\260&quot;), <span style=\" font-family:'Courier New';\">x@</span>, <span style=\" font-family:'Courier New';\">x^2</span></li></ul></body></html>", nullptr));
        labelVvod->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271 (\320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276 \320\274\320\260\320\272\321\201\320\270\320\274\321\203\320\274 5 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\320\265):", nullptr));
        labelUrav1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\320\243\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \342\204\2261:</span></p></body></html>", nullptr));
        labelUrav2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\320\243\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \342\204\2262:</span></p></body></html>", nullptr));
        labelUrav3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\320\243\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \342\204\2263:</span></p></body></html>", nullptr));
        labelUrav4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\320\243\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \342\204\2264:</span></p></body></html>", nullptr));
        labelUrav5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\320\243\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265 \342\204\2265:</span></p></body></html>", nullptr));
        pushButtonDelUrav_2->setText(QCoreApplication::translate("MainWindow", "-\320\243\320\261\321\200\320\260\321\202\321\214 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265", nullptr));
        pushButtonAddUrav->setText(QCoreApplication::translate("MainWindow", "+\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
