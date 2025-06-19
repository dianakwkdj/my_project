// ✅ emailconfirmationform.cpp — с отправкой кода на сервер

#include "emailconfirmationform.h"
#include "ui_emailconfirmationform.h"
#include "networkclient.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

EmailConfirmationForm::EmailConfirmationForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmailConfirmationForm)
{
    ui->setupUi(this);
    ui->labelInfo->setText("");
}

EmailConfirmationForm::~EmailConfirmationForm() {
    delete ui;
}

void EmailConfirmationForm::setUserData(const QString& email, const QString& /*sentCode*/, const QString& login, const QString& password) {
    m_email = email;
    m_login = login;
    m_password = password;
    ui->labelInfo->setText(QString("Подтвердите вашу учетную запись. Код отправлен на %1").arg(email));
}

void EmailConfirmationForm::on_pushButtonVerify_clicked() {
    QString enteredCode = ui->lineEditCode->text().trimmed();

    if (enteredCode.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите код подтверждения.");
        return;
    }

    QJsonObject request;
    request["action"] = "email_confirm_validate";
    request["email"] = m_email;
    request["code"] = enteredCode;

    NetworkClient::instance().sendJsonRequest(request, [=](bool success, const QString& result) {
        if (!success) {
            QMessageBox::critical(this, "Ошибка", "Сетевая ошибка при проверке кода.");
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject resp = doc.object();

        if (resp["status"] == "success") {
            QMessageBox::information(this, "Успех", "Код подтверждён. Регистрация продолжается.");
            emit codeConfirmed(m_email, m_login, m_password);
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", resp["message"].toString());
        }
    });
}
