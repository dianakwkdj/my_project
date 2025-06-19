/********************************************************************************
** Form generated from reading UI file 'emailconfirmationform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAILCONFIRMATIONFORM_H
#define UI_EMAILCONFIRMATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EmailConfirmationForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelInfo;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEditCode;
    QPushButton *pushButtonVerify;

    void setupUi(QDialog *EmailConfirmationForm)
    {
        if (EmailConfirmationForm->objectName().isEmpty())
            EmailConfirmationForm->setObjectName("EmailConfirmationForm");
        EmailConfirmationForm->resize(361, 137);
        verticalLayout_2 = new QVBoxLayout(EmailConfirmationForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        labelInfo = new QLabel(EmailConfirmationForm);
        labelInfo->setObjectName("labelInfo");

        verticalLayout->addWidget(labelInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(EmailConfirmationForm);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lineEditCode = new QLineEdit(EmailConfirmationForm);
        lineEditCode->setObjectName("lineEditCode");

        horizontalLayout->addWidget(lineEditCode);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        pushButtonVerify = new QPushButton(EmailConfirmationForm);
        pushButtonVerify->setObjectName("pushButtonVerify");

        verticalLayout_2->addWidget(pushButtonVerify);


        retranslateUi(EmailConfirmationForm);

        QMetaObject::connectSlotsByName(EmailConfirmationForm);
    } // setupUi

    void retranslateUi(QDialog *EmailConfirmationForm)
    {
        EmailConfirmationForm->setWindowTitle(QCoreApplication::translate("EmailConfirmationForm", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\320\265", nullptr));
        labelInfo->setText(QCoreApplication::translate("EmailConfirmationForm", "                    \320\232\320\276\320\264 \320\276\321\202\320\277\321\200\320\260\320\262\320\273\320\265\320\275 \320\275\320\260 \320\262\320\260\321\210\321\203 \320\277\320\276\321\207\321\202\321\203.\n"
"    \320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\265\320\263\320\276 \320\264\320\273\321\217 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\321\217 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270.", nullptr));
        label_2->setText(QCoreApplication::translate("EmailConfirmationForm", "\320\237\320\276\320\273\320\265 \320\264\320\273\321\217 \320\262\320\262\320\276\320\264\320\260 \320\272\320\276\320\264\320\260", nullptr));
        pushButtonVerify->setText(QCoreApplication::translate("EmailConfirmationForm", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmailConfirmationForm: public Ui_EmailConfirmationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAILCONFIRMATIONFORM_H
