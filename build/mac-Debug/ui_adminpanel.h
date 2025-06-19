/********************************************************************************
** Form generated from reading UI file 'adminpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminPanel
{
public:
    QTableWidget *tableUsers;
    QPushButton *btnRefresh;
    QPushButton *btnDelete;
    QPushButton *btnMakeAdmin;
    QPushButton *btnRemoveAdmin;
    QPushButton *btnResetPassword;
    QPushButton *btnExportCsv;
    QPushButton *btnBlockUser;
    QPushButton *btnUnblockUser;
    QLineEdit *lineEditSearch;
    QPushButton *btnSearch;
    QCheckBox *checkaAdminsOnly;
    QCheckBox *checkBlockedOnly;

    void setupUi(QDialog *AdminPanel)
    {
        if (AdminPanel->objectName().isEmpty())
            AdminPanel->setObjectName("AdminPanel");
        AdminPanel->resize(800, 600);
        tableUsers = new QTableWidget(AdminPanel);
        if (tableUsers->columnCount() < 6)
            tableUsers->setColumnCount(6);
        tableUsers->setObjectName("tableUsers");
        tableUsers->setGeometry(QRect(10, 129, 771, 321));
        tableUsers->setColumnCount(6);
        tableUsers->horizontalHeader()->setVisible(true);
        tableUsers->horizontalHeader()->setCascadingSectionResizes(false);
        tableUsers->horizontalHeader()->setMinimumSectionSize(12);
        tableUsers->horizontalHeader()->setDefaultSectionSize(129);
        tableUsers->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        btnRefresh = new QPushButton(AdminPanel);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(10, 460, 151, 51));
        btnDelete = new QPushButton(AdminPanel);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(170, 460, 191, 51));
        btnMakeAdmin = new QPushButton(AdminPanel);
        btnMakeAdmin->setObjectName("btnMakeAdmin");
        btnMakeAdmin->setGeometry(QRect(370, 460, 201, 61));
        btnRemoveAdmin = new QPushButton(AdminPanel);
        btnRemoveAdmin->setObjectName("btnRemoveAdmin");
        btnRemoveAdmin->setGeometry(QRect(580, 460, 201, 61));
        btnResetPassword = new QPushButton(AdminPanel);
        btnResetPassword->setObjectName("btnResetPassword");
        btnResetPassword->setGeometry(QRect(60, 530, 151, 61));
        btnExportCsv = new QPushButton(AdminPanel);
        btnExportCsv->setObjectName("btnExportCsv");
        btnExportCsv->setGeometry(QRect(250, 530, 121, 61));
        btnBlockUser = new QPushButton(AdminPanel);
        btnBlockUser->setObjectName("btnBlockUser");
        btnBlockUser->setGeometry(QRect(410, 530, 141, 61));
        btnUnblockUser = new QPushButton(AdminPanel);
        btnUnblockUser->setObjectName("btnUnblockUser");
        btnUnblockUser->setGeometry(QRect(570, 530, 151, 61));
        lineEditSearch = new QLineEdit(AdminPanel);
        lineEditSearch->setObjectName("lineEditSearch");
        lineEditSearch->setGeometry(QRect(20, 50, 731, 31));
        btnSearch = new QPushButton(AdminPanel);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(20, 80, 100, 32));
        checkaAdminsOnly = new QCheckBox(AdminPanel);
        checkaAdminsOnly->setObjectName("checkaAdminsOnly");
        checkaAdminsOnly->setGeometry(QRect(140, 100, 181, 21));
        checkBlockedOnly = new QCheckBox(AdminPanel);
        checkBlockedOnly->setObjectName("checkBlockedOnly");
        checkBlockedOnly->setGeometry(QRect(320, 100, 181, 21));

        retranslateUi(AdminPanel);

        QMetaObject::connectSlotsByName(AdminPanel);
    } // setupUi

    void retranslateUi(QDialog *AdminPanel)
    {
        AdminPanel->setWindowTitle(QCoreApplication::translate("AdminPanel", "Dialog", nullptr));
        btnRefresh->setText(QCoreApplication::translate("AdminPanel", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        btnDelete->setText(QCoreApplication::translate("AdminPanel", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        btnMakeAdmin->setText(QCoreApplication::translate("AdminPanel", "\320\235\320\260\320\267\320\275\320\260\321\207\320\270\321\202\321\214 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        btnRemoveAdmin->setText(QCoreApplication::translate("AdminPanel", "\320\241\320\275\321\217\321\202\321\214 \320\277\321\200\320\260\320\262\320\260 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        btnResetPassword->setText(QCoreApplication::translate("AdminPanel", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        btnExportCsv->setText(QCoreApplication::translate("AdminPanel", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 CSV", nullptr));
        btnBlockUser->setText(QCoreApplication::translate("AdminPanel", "\320\227\320\260\320\261\320\273\320\276\320\272\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        btnUnblockUser->setText(QCoreApplication::translate("AdminPanel", "\320\240\320\260\320\267\320\261\320\273\320\276\320\272\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        btnSearch->setText(QCoreApplication::translate("AdminPanel", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        checkaAdminsOnly->setText(QCoreApplication::translate("AdminPanel", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\321\213", nullptr));
        checkBlockedOnly->setText(QCoreApplication::translate("AdminPanel", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\267\320\260\320\261\320\273\320\276\320\272\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPanel: public Ui_AdminPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
