// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "networkclient.h"
#include "adminpanel.h"
#include <QKeyEvent>
#include "solution.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , uravCount(2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    // Скрываем поля для дополнительных уравнений (по умолчанию 2)
    ui->labelUrav3->setVisible(false);
    ui->labelUrav4->setVisible(false);
    ui->labelUrav5->setVisible(false);
    ui->lineEditUrav3->setVisible(false);
    ui->lineEditUrav4->setVisible(false);
    ui->lineEditUrav5->setVisible(false);

    setFocusToFirstEmptyField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFocusToFirstEmptyField()
{
    if (ui->lineEditUrav1->text().isEmpty()) ui->lineEditUrav1->setFocus();
    else if (ui->lineEditUrav2->text().isEmpty()) ui->lineEditUrav2->setFocus();
    else if (uravCount >= 3 && ui->lineEditUrav3->text().isEmpty()) ui->lineEditUrav3->setFocus();
    else if (uravCount >= 4 && ui->lineEditUrav4->text().isEmpty()) ui->lineEditUrav4->setFocus();
    else if (uravCount >= 5 && ui->lineEditUrav5->text().isEmpty()) ui->lineEditUrav5->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QList<QLineEdit*> fields = {
            ui->lineEditUrav1,
            ui->lineEditUrav2,
            ui->lineEditUrav3,
            ui->lineEditUrav4,
            ui->lineEditUrav5
        };
        for (int i = 0; i < fields.size(); ++i) {
            if (fields[i]->hasFocus()) {
                for (int j = i + 1; j < fields.size(); ++j) {
                    if (fields[j]->isVisible()) {
                        fields[j]->setFocus();
                        return;
                    }
                }
                QMessageBox::information(this, "Добавление уравнения", "Нажмите \"Добавить уравнение\".");
                return;
            }
        }
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::slot_show(const QString &login)
{
    // После входа проверяем права администратора
    QJsonObject req;
    req["action"] = "check_admin_status";
    req["login_or_email"] = login;

    NetworkClient::instance().sendJsonRequest(req, [this, login](bool success, const QString &resp) {
        if (!success) {
            QMessageBox::warning(this, "Ошибка", "Не удалось проверить статус администратора.");
            this->show();
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(resp.toUtf8());
        QJsonObject obj = doc.object();

        if (obj["status"].toString() == "success" && obj["is_admin"].toBool()) {
            // Показываем админ-панель
            this->hide();
            AdminPanel *panel = new AdminPanel(this);
            panel->setAttribute(Qt::WA_DeleteOnClose);
            panel->setAdminLogin(login);
            connect(panel, &QDialog::finished, this, &MainWindow::show);
            panel->show();
        } else {
            this->show();
        }
    });
}

void MainWindow::on_pushButtonAddUrav_clicked()
{
    if (uravCount >= 5) {
        QMessageBox::warning(this, "Максимум", "Нельзя добавить более 5 уравнений.");
        return;
    }
    QLineEdit* edits[] = { ui->lineEditUrav1, ui->lineEditUrav2, ui->lineEditUrav3, ui->lineEditUrav4, ui->lineEditUrav5 };
    for (int i = 0; i < uravCount; ++i) {
        if (edits[i]->text().trimmed().isEmpty()) {
            edits[i]->setFocus();
            QMessageBox::warning(this, "Пустое поле", "Заполните предыдущее уравнение.");
            return;
        }
    }
    switch (uravCount) {
    case 2: ui->labelUrav3->setVisible(true); ui->lineEditUrav3->setVisible(true); ui->lineEditUrav3->setFocus(); break;
    case 3: ui->labelUrav4->setVisible(true); ui->lineEditUrav4->setVisible(true); ui->lineEditUrav4->setFocus(); break;
    case 4: ui->labelUrav5->setVisible(true); ui->lineEditUrav5->setVisible(true); ui->lineEditUrav5->setFocus(); break;
    }
    uravCount++;
}

void MainWindow::on_pushButtonDelUrav_2_clicked()
{
    if (uravCount <= 2) {
        QMessageBox::warning(this, "Минимум", "Должно быть минимум 2 уравнения.");
        return;
    }
    QLineEdit* edits[] = { ui->lineEditUrav1, ui->lineEditUrav2, ui->lineEditUrav3, ui->lineEditUrav4, ui->lineEditUrav5 };
    QLabel* labels[] = { ui->labelUrav1, ui->labelUrav2, ui->labelUrav3, ui->labelUrav4, ui->labelUrav5 };
    int last = uravCount - 1;
    if (!edits[last]->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Поле заполнено", "Нельзя удалить заполненное поле.");
        return;
    }
    edits[last]->clear(); edits[last]->setVisible(false);
    labels[last]->setVisible(false);
    uravCount--;
    setFocusToFirstEmptyField();
}

void MainWindow::on_pushButtonSolveUrav_clicked()
{
    QJsonObject req;
    req["action"] = "solve";
    QJsonArray arr;
    arr.append(ui->lineEditUrav1->text());
    arr.append(ui->lineEditUrav2->text());
    if (uravCount >= 3) arr.append(ui->lineEditUrav3->text());
    if (uravCount >= 4) arr.append(ui->lineEditUrav4->text());
    if (uravCount >= 5) arr.append(ui->lineEditUrav5->text());
    req["equations"] = arr;

    NetworkClient::instance().sendSolutionRequest(req, [this](bool ok, const QString &resp) {
        if (!ok) {
            QMessageBox::critical(this, "Ошибка", resp.isEmpty() ? "Сетевая ошибка." : resp);
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(resp.toUtf8());
        QJsonObject obj = doc.object();
        if (obj["status"] == "success") displaySolution(obj);
        else QMessageBox::critical(this, "Ошибка", obj["message"].toString());
    });
}

void MainWindow::displaySolution(const QJsonObject &response)
{
    QString sol;
    if (response.contains("steps")) {
        for (auto v : response["steps"].toArray()) sol += v.toString() + "\n";
    }
    if (!solutionWindow) solutionWindow = new Solution(this);
    solutionWindow->setSolutionText(sol);
    solutionWindow->show();
}
