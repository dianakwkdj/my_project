#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();
    void setLogin(const QString& login);
    void setAdminLogin(const QString &login);

private slots:
    void onRefreshClicked();
    void onDeleteClicked();
    void onMakeAdminClicked();
    void onRemoveAdminClicked();
    void onResetPasswordClicked();
    void refreshUserList();
private:
    Ui::AdminPanel *ui;
    QString m_adminLogin;
    void setupTable();
    void setupConnections();
};

#endif // ADMINPANEL_H
