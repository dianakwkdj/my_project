#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QDialog>
#include <QMessageBox>
#include "passwordrecoveryform.h"
#include "emailconfirmationform.h"
namespace Ui {
class AuthRegForm;
}

class AuthRegForm : public QDialog
{
    Q_OBJECT

public:
    explicit AuthRegForm(QWidget *parent = nullptr);
    ~AuthRegForm();


private slots:
    void on_pushButtonChange_clicked();
    void on_pushButtonAuth_clicked();
    void on_pushButtonReg_clicked();
    void on_pushButtonForgotPassword_clicked();
    void onCodeConfirmed(const QString& email, const QString& login, const QString& password);
public slots:
    void handleJsonResponse(const QJsonObject& response);


protected:
    void keyPressEvent(QKeyEvent *event) override;  // Переопределение keyPressEvent
    void showEvent(QShowEvent* event) override; // Добавляем объявление showEvent

signals:
    void auth_ok(QString);
    void recovery_ok();
    void admin_ok(QString);


private:
    Ui::AuthRegForm *ui;
    void change_type_to_reg(bool);
    void clear();
    int authAttempts;
    QString generateRecoveryCode();
    bool sendRecoveryCode(const QString& email, const QString& code);
    EmailConfirmationForm *emailConfirmForm = nullptr;
};

#endif // AUTHREGFORM_H
