#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "networkclient.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

void AdminPanel::setLogin(const QString& login) {
    m_adminLogin = login;
    refreshUserList(); // обновим таблицу при установке логина
}
AdminPanel::AdminPanel(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    setupTable();
    setupConnections();
    onRefreshClicked(); // автообновление при открытии
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::setupTable()
{
    ui->tableUsers->setColumnCount(6);
    QStringList headers = {"ID", "Логин", "Email", "Админ", "Заблокирован", "Дата"};
    ui->tableUsers->setHorizontalHeaderLabels(headers);
    ui->tableUsers->horizontalHeader()->setStretchLastSection(true);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AdminPanel::setupConnections()
{
    connect(ui->btnRefresh, &QPushButton::clicked, this, &AdminPanel::onRefreshClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &AdminPanel::onDeleteClicked);
    connect(ui->btnMakeAdmin, &QPushButton::clicked, this, &AdminPanel::onMakeAdminClicked);
    connect(ui->btnRemoveAdmin, &QPushButton::clicked, this, &AdminPanel::onRemoveAdminClicked);
    connect(ui->btnResetPassword, &QPushButton::clicked, this, &AdminPanel::onResetPasswordClicked);
}

void AdminPanel::onRefreshClicked()
{
    QJsonObject request;
    request["action"] = "admin_get_users";
    request["login_or_email"] = "admin"; // текущий админ

    NetworkClient::instance().sendJsonRequest(request, [this](bool success, const QString& result) {
        if (!success) {
            QMessageBox::critical(this, "Ошибка", result);
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject obj = doc.object();
        QJsonArray users = obj.value("users").toArray();

        ui->tableUsers->setRowCount(users.size());
        for (int i = 0; i < users.size(); ++i) {
            QJsonObject user = users[i].toObject();
            ui->tableUsers->setItem(i, 0, new QTableWidgetItem(QString::number(user["id"].toInt())));
            ui->tableUsers->setItem(i, 1, new QTableWidgetItem(user["login"].toString()));
            ui->tableUsers->setItem(i, 2, new QTableWidgetItem(user["email"].toString()));
            ui->tableUsers->setItem(i, 3, new QTableWidgetItem(user["is_admin"].toBool() ? "Да" : "Нет"));
            ui->tableUsers->setItem(i, 4, new QTableWidgetItem(user["is_blocked"].toBool() ? "Да" : "Нет"));
            ui->tableUsers->setItem(i, 5, new QTableWidgetItem(user["created_at"].toString()));
        }
    });
}

void AdminPanel::onDeleteClicked()
{
    int row = ui->tableUsers->currentRow();
    if (row < 0) return;

    QString login = ui->tableUsers->item(row, 1)->text();

    QJsonObject request;
    request["action"] = "admin_delete_user";
    request["login_or_email"] = login;

    NetworkClient::instance().sendJsonRequest(request, [this, login](bool success, const QString& result) {
        if (success) {
            QMessageBox::information(this, "Успех", QString("Пользователь '%1' удалён").arg(login));
            onRefreshClicked();
        } else {
            QMessageBox::critical(this, "Ошибка", result);
        }
    });
}

void AdminPanel::onMakeAdminClicked()
{
    int row = ui->tableUsers->currentRow();
    if (row < 0) return;

    QString login = ui->tableUsers->item(row, 1)->text();

    QJsonObject request;
    request["action"] = "admin_grant_admin";
    request["login_or_email"] = login;

    NetworkClient::instance().sendJsonRequest(request, [this, login](bool success, const QString& result) {
        if (success) {
            QMessageBox::information(this, "Успех", QString("'%1' назначен администратором").arg(login));
            onRefreshClicked();
        } else {
            QMessageBox::critical(this, "Ошибка", result);
        }
    });
}

void AdminPanel::onRemoveAdminClicked()
{
    int row = ui->tableUsers->currentRow();
    if (row < 0) return;

    QString login = ui->tableUsers->item(row, 1)->text();

    QJsonObject request;
    request["action"] = "admin_revoke_admin";
    request["login_or_email"] = login;

    NetworkClient::instance().sendJsonRequest(request, [this, login](bool success, const QString& result) {
        if (success) {
            QMessageBox::information(this, "Успех", QString("Права администратора сняты с '%1'").arg(login));
            onRefreshClicked();
        } else {
            QMessageBox::critical(this, "Ошибка", result);
        }
    });
}

void AdminPanel::onResetPasswordClicked()
{
    int row = ui->tableUsers->currentRow();
    if (row < 0) return;

    QString login = ui->tableUsers->item(row, 1)->text();

    QJsonObject request;
    request["action"] = "admin_reset_password";
    request["login_or_email"] = login;

    NetworkClient::instance().sendJsonRequest(request, [this, login](bool success, const QString& result) {
        if (success) {
            QMessageBox::information(this, "Сброс пароля", QString("Пароль для '%1' сброшен. Проверьте email пользователя.").arg(login));
        } else {
            QMessageBox::critical(this, "Ошибка", result);
        }
    });
}

void AdminPanel::refreshUserList()
{
    if (m_adminLogin.isEmpty()) return;

    ui->tableUsers->clearContents();
    ui->tableUsers->setRowCount(0);

    NetworkClient::instance().adminGetUsers(m_adminLogin,
                                            [this](bool success, const QJsonArray& users, const QString& errorMsg) {
                                                if (!success) {
                                                    QMessageBox::warning(this, "Ошибка", "Не удалось получить список пользователей:\n" + errorMsg);
                                                    return;
                                                }

                                                ui->tableUsers->setRowCount(users.size());

                                                for (int i = 0; i < users.size(); ++i) {
                                                    QJsonObject user = users[i].toObject();
                                                    ui->tableUsers->setItem(i, 0, new QTableWidgetItem(QString::number(user["id"].toInt())));
                                                    ui->tableUsers->setItem(i, 1, new QTableWidgetItem(user["login"].toString()));
                                                    ui->tableUsers->setItem(i, 2, new QTableWidgetItem(user["email"].toString()));
                                                    ui->tableUsers->setItem(i, 3, new QTableWidgetItem(user["is_admin"].toBool() ? "Да" : "Нет"));
                                                    ui->tableUsers->setItem(i, 4, new QTableWidgetItem(user["is_blocked"].toBool() ? "Да" : "Нет"));
                                                    ui->tableUsers->setItem(i, 5, new QTableWidgetItem(user["created_at"].toString()));
                                                }

                                                ui->tableUsers->resizeColumnsToContents();
                                            });
}
void AdminPanel::setAdminLogin(const QString &login)
{
    m_adminLogin = login;
    refreshUserList();
}
