#include "statistics.h"
#include <QVBoxLayout>
#include <QPushButton>

Statistics::Statistics(QWidget *parent)
    : QDialog(parent)
    , m_textEdit(new QPlainTextEdit(this))
{
    setWindowTitle("Статистика");
    resize(400, 300);

    m_textEdit->setReadOnly(true);
    m_textEdit->setPlaceholderText("Здесь будет отображена статистика...");

    // Кнопка закрыть
    auto *closeBtn = new QPushButton("Закрыть", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    // Лэйаут
    auto *lay = new QVBoxLayout(this);
    lay->addWidget(m_textEdit, /*stretch=*/1);
    lay->addWidget(closeBtn, /*stretch=*/0);
    setLayout(lay);
}

void Statistics::setStatText(const QString &text)
{
    m_textEdit->setPlainText(text);
}
