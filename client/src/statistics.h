#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include <QPlainTextEdit>

class Statistics : public QDialog
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics() override = default;

    void setStatText(const QString &text);

private:
    QPlainTextEdit *m_textEdit;
};

#endif // STATISTICS_H
