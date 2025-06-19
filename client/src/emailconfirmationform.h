#ifndef EMAILCONFIRMATIONFORM_H
#define EMAILCONFIRMATIONFORM_H

#include <QDialog>

namespace Ui {
class EmailConfirmationForm;
}

class EmailConfirmationForm : public QDialog
{
    Q_OBJECT

public:
    explicit EmailConfirmationForm(QWidget *parent = nullptr);
    ~EmailConfirmationForm();
    void setUserData(const QString& email, const QString& sentCode, const QString& login, const QString& password);


signals:
    // Сигнал успешного подтверждения кода, передаем email, пароль и логин для дальнейшей регистрации
    void codeConfirmed(const QString& email, const QString& login, const QString& password);


private slots:
    // Слот обработки кнопки "Проверить"
    void on_pushButtonVerify_clicked();

private:
    Ui::EmailConfirmationForm *ui;

    QString m_email;    // Почта пользователя
    QString m_sentCode; // Отправленный код подтверждения

    // Для хранения логина и пароля, которые будут переданы из AuthRegForm
    QString m_login;
    QString m_password;
};

#endif // EMAILCONFIRMATIONFORM_H
