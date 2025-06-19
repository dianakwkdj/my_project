#include "authregform.h"
#include "ui_authregform.h"
#include "networkclient.h"
#include <QJsonObject>
#include <QInputDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QRandomGenerator>

AuthRegForm::AuthRegForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AuthRegForm)
{
    ui->setupUi(this);

    // Скрываем элементы регистрации по умолчанию
    ui->lineEditMail->setVisible(false);
    ui->lineEditPasswordCheck->setVisible(false);
    ui->pushButtonReg->setVisible(false);

    ui->labelMail->setVisible(false);
    ui->labelPasswordCheck->setVisible(false);

    ui->pushButtonForgotPassword->setVisible(true);
    ui->pushButtonChange->setText("Зарегистрироваться");
}

AuthRegForm::~AuthRegForm()
{
    delete ui;
}

// Авторизация
void AuthRegForm::on_pushButtonAuth_clicked()
{
    QString login = ui->lineEditLogin->text().trimmed();
    QString password = ui->lineEditPassword->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
        return;
    }

    QJsonObject obj;
    obj["action"] = "login";
    obj["login"] = login;
    obj["password"] = password;

    NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString &text) {
        QJsonObject response = QJsonDocument::fromJson(text.toUtf8()).object();
        if (response["status"] == "success") {

            // 🔍 Проверяем статус администратора
            QJsonObject checkAdmin;
            checkAdmin["action"] = "check_admin_status";
            checkAdmin["login_or_email"] = login;

            NetworkClient::instance().sendJsonRequest(checkAdmin, [=](bool ok, const QString& adminText) {
                if (!ok) return;

                QJsonObject adminResp = QJsonDocument::fromJson(adminText.toUtf8()).object();

                if (adminResp["status"] == "success" && adminResp["is_admin"].toBool()) {
                    QMessageBox::information(this, "Успешно", "Вы вошли как администратор.");
                    emit admin_ok(login); // 🔁 сигнал для открытия админки
                } else {
                    QMessageBox::information(this, "Успешно", "Вход выполнен.");
                    emit auth_ok(login); // обычный пользователь
                }

                this->accept();
            });

        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        }
    });







}

// Показать форму регистрации
void AuthRegForm::on_pushButtonChange_clicked()
{
    ui->lineEditMail->setVisible(true);
    ui->lineEditPasswordCheck->setVisible(true);
    ui->pushButtonReg->setVisible(true);

    ui->labelMail->setVisible(true);
    ui->labelPasswordCheck->setVisible(true);

    ui->pushButtonAuth->setVisible(false);
    ui->pushButtonForgotPassword->setVisible(true);
    ui->pushButtonChange->setVisible(false);
}

// Регистрация — пошаговая логика
void AuthRegForm::on_pushButtonReg_clicked()
{
    QString login = ui->lineEditLogin->text().trimmed();
    QString email = ui->lineEditMail->text().trimmed();
    QString password = ui->lineEditPassword->text();
    QString passwordRepeat = ui->lineEditPasswordCheck->text();

    if (login.isEmpty() || email.isEmpty() || password.isEmpty() || passwordRepeat.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    if (password != passwordRepeat) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    QJsonObject obj;
    obj["action"] = "register_check_login";
    obj["login"] = login;

    NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString &text) {
        if (!success) return;
        QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
        if (resp["status"] != "ok") {
            QMessageBox::warning(this, "Ошибка", resp["message"].toString());
            return;
        }

        QJsonObject obj2;
        obj2["action"] = "register_check_email";
        obj2["email"] = email;

        NetworkClient::instance().sendJsonRequest(obj2, [=](bool success, const QString &text) {
            if (!success) return;
            QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
            if (resp["status"] != "ok") {
                QMessageBox::warning(this, "Ошибка", resp["message"].toString());
                return;
            }

            QJsonObject obj3;
            obj3["action"] = "register_check_password";
            obj3["password"] = password;

            NetworkClient::instance().sendJsonRequest(obj3, [=](bool success, const QString &text) {
                if (!success) return;
                QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                if (resp["status"] != "ok") {
                    QMessageBox::warning(this, "Ошибка", resp["message"].toString());
                    return;
                }

                QJsonObject obj4;
                obj4["action"] = "email_confirm_request";
                obj4["email"] = email;
                obj4["login"] = login;

                NetworkClient::instance().sendJsonRequest(obj4, [=](bool success, const QString &text) {
                    if (!success) return;
                    QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                    if (resp["status"] != "success") {
                        QMessageBox::warning(this, "Ошибка", resp["message"].toString());
                        return;
                    }

                    QString code = QInputDialog::getText(this, "Подтверждение", "Введите код из письма:");
                    if (code.isEmpty()) {
                        QMessageBox::warning(this, "Ошибка", "Код не введён.");
                        return;
                    }

                    QJsonObject obj5;
                    obj5["action"] = "email_confirm_validate";
                    obj5["email"] = email;
                    obj5["login"] = login;
                    obj5["password"] = password;
                    obj5["code"] = code;

                    NetworkClient::instance().sendJsonRequest(obj5, [=](bool success, const QString &text) {
                        if (!success) return;
                        QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                        if (resp["status"] == "success") {
                            QMessageBox::information(this, "Успешно", "Регистрация завершена.");
                            clear();
                            change_type_to_reg(false); // переключаем интерфейс обратно на авторизацию

                            ui->pushButtonAuth->setVisible(true);
                            ui->pushButtonChange->setVisible(true);
                            ui->lineEditPassword->setFocus();
                        } else {
                            QMessageBox::warning(this, "Ошибка", resp["message"].toString());
                        }
                    });
                });
            });
        });
    });
}

void AuthRegForm::handleJsonResponse(const QJsonObject& response)
{
    QString action = response.value("action").toString();
    QString status = response.value("status").toString();

    if (action == "register_check_login") {
        if (status == "ok") {
            QJsonObject obj;
            obj["action"] = "register_check_email";
            obj["email"] = ui->lineEditMail->text().trimmed();
            NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString& text) {
                if (!success) return;
                QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                handleJsonResponse(resp);
            });
        } else {
            ui->labelHelp->setText(response.value("message").toString());
        }
        return;
    }

    if (action == "register_check_email") {
        if (status == "ok") {
            QJsonObject obj;
            obj["action"] = "register_check_password";
            obj["password"] = ui->lineEditPassword->text();
            NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString& text) {
                if (!success) return;
                QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                handleJsonResponse(resp);
            });
        } else {
            ui->labelHelp->setText(response.value("message").toString());
        }
        return;
    }

    if (action == "register_check_password") {
        if (status == "ok") {
            QJsonObject obj;
            obj["action"] = "email_confirm_request";
            obj["email"] = ui->lineEditMail->text().trimmed();
            obj["login"] = ui->lineEditLogin->text().trimmed();
            NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString& text) {
                if (!success) return;
                QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                handleJsonResponse(resp);
            });
        } else {
            ui->labelHelp->setText(response.value("message").toString());
        }
        return;
    }

    if (action == "email_confirm_request") {
        if (status == "success") {
            ui->labelHelp->setText("Введите код, отправленный на почту.");
            QString code = QInputDialog::getText(this, "Подтверждение", "Введите код из письма:");

            if (code.isEmpty()) {
                ui->labelHelp->setText("Код не введён. Регистрация отменена.");
                return;
            }

            QJsonObject obj;
            obj["action"] = "email_confirm_validate";
            obj["login"] = ui->lineEditLogin->text().trimmed();
            obj["email"] = ui->lineEditMail->text().trimmed();
            obj["password"] = ui->lineEditPassword->text();
            obj["code"] = code;

            NetworkClient::instance().sendJsonRequest(obj, [=](bool success, const QString& text) {
                if (!success) return;
                QJsonObject resp = QJsonDocument::fromJson(text.toUtf8()).object();
                handleJsonResponse(resp);
            });
        } else {
            ui->labelHelp->setText(response.value("message").toString());
        }
        return;
    }

    if (action == "email_confirm_validate") {
        if (status == "success") {
            QMessageBox::information(this, "Готово", "Регистрация завершена!");
            this->close();
        } else {
            ui->labelHelp->setText(response.value("message").toString());
        }
        return;
    }
}


void AuthRegForm::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    ui->lineEditLogin->setFocus();
}


void AuthRegForm::change_type_to_reg(bool is_reg)
{
    ui->labelPasswordCheck->setVisible(is_reg);
    ui->labelMail->setVisible(is_reg);
    ui->lineEditPasswordCheck->setVisible(is_reg);
    ui->lineEditMail->setVisible(is_reg);
    ui->pushButtonReg->setVisible(is_reg);
    ui->pushButtonAuth->setVisible(!is_reg);
    ui->pushButtonChange->setText(is_reg ? "Авторизоваться" : "Зарегистрироваться");
}



void AuthRegForm::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        if (ui->lineEditLogin->hasFocus()) ui->lineEditPassword->setFocus();
        else if (ui->lineEditPassword->hasFocus()) ui->lineEditPasswordCheck->setFocus();
        else if (ui->lineEditPasswordCheck->hasFocus()) ui->lineEditMail->setFocus();
        else if (ui->lineEditMail->hasFocus()) ui->pushButtonReg->click();
    } else {
        QDialog::keyPressEvent(event);
    }
}

void AuthRegForm::on_pushButtonForgotPassword_clicked() {
    emit recovery_ok();
}

QString AuthRegForm::generateRecoveryCode() {
    QString code;
    for (int i = 0; i < 6; ++i)
        code.append(QString::number(QRandomGenerator::global()->bounded(10)));
    return code;
}

bool AuthRegForm::sendRecoveryCode(const QString& email, const QString& code) {
    qDebug() << "Отправка кода на почту: " << email;
    qDebug() << "Код: " << code;
    return true;
}

void AuthRegForm::clear() {
    ui->lineEditPassword->clear();
    ui->lineEditPasswordCheck->clear();
    ui->lineEditMail->clear();
}



void AuthRegForm::onCodeConfirmed(const QString& email, const QString& login, const QString& password)
{
    ui->pushButtonReg->setEnabled(true);
    ui->pushButtonReg->setText("Регистрация");

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    NetworkClient::instance().registerUser(
        login, password, email,
        [this, login](bool success, const QString& message) {
            QApplication::restoreOverrideCursor();
            if (success) {
                QMessageBox::information(this, "Успех", "Регистрация завершена. Теперь вы вошли в систему.");
                emit auth_ok(login);
                this->close();
            } else {
                QMessageBox::critical(this, "Ошибка", message);
            }
        });
}
