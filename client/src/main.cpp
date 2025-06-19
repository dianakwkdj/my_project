#include <QApplication>
#include "authregform.h"
#include "mainwindow.h"
#include "adminpanel.h" // <-- ВАЖНО

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AuthRegForm authForm;

    QObject::connect(&authForm, &AuthRegForm::auth_ok, [](const QString& login){
        MainWindow* mainWindow = new MainWindow();
        mainWindow->show();
    });

    QObject::connect(&authForm, &AuthRegForm::admin_ok, [](const QString& login){
        AdminPanel* adminWindow = new AdminPanel();
        adminWindow->show();
    });

    authForm.exec();
    return app.exec();
}
