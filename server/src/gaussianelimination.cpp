#include "gaussianelimination.h"
#include <QString>

// Форматированный вывод матрицы с переменными
QString formatMatrix(const QVector<QVector<double>>& matrix, const QVector<double>& constants, const QStringList& variables) {
    QString result;
    for (int i = 0; i < matrix.size(); ++i) {
        QString row;
        for (int j = 0; j < matrix[i].size(); ++j) {
            double val = matrix[i][j];
            QString str;

            if (j == 0) {
                // Первая переменная: не добавляем знак +
                str = QString::number(val, 'f', 3);
            } else {
                // Остальные переменные: добавляем знак с пробелом
                str = (val >= 0 ? "+ " : "- ") + QString::number(std::abs(val), 'f', 3);
            }

            row += str + variables[j] + " ";
        }

        row += "= " + QString::number(constants[i], 'f', 3);
        result += row.trimmed() + "\n";
    }
    return result;
}

bool GaussianElimination::solve(QVector<QVector<double>>& matrix,
                                QVector<double>& constants,
                                QVector<double>& solution,
                                QStringList& steps,
                                QString& error,
                                const QStringList& variables)
{
    int n = matrix.size();           // количество уравнений (строк)
    int vars = matrix[0].size();     // количество переменных (столбцов)

    steps.append("Начинаем приведение системы уравнений к ступенчатому виду:");
    steps.append(formatMatrix(matrix, constants, variables));

    for (int i = 0; i < qMin(n, vars); ++i) {
        // Поиск главного элемента
        int pivotRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (qAbs(matrix[k][i]) > qAbs(matrix[pivotRow][i]))
                pivotRow = k;
        }

        // Проверка на нулевой ведущий элемент
        if (qFuzzyIsNull(matrix[pivotRow][i])) {
            continue; // не нормализуем, но дойдём до анализа позже
        }

        // Перестановка строк при необходимости
        if (pivotRow != i) {
            std::swap(matrix[i], matrix[pivotRow]);
            std::swap(constants[i], constants[pivotRow]);
            steps.append(QString("Меняем местами строки %1 и %2, чтобы элемент %3 стал ведущим.")
                             .arg(i + 1)
                             .arg(pivotRow + 1)
                             .arg(i + 1));
            steps.append(formatMatrix(matrix, constants, variables));
        }

        // Нормализация строки
        double pivot = matrix[i][i];
        if (qAbs(pivot - 1.0) > 1e-9) {
            steps.append(QString("Нормализуем строку %1 (делим на коэффициент %2):").arg(i + 1).arg(pivot, 0, 'f', 3));
            for (int j = i; j < vars; ++j)
                matrix[i][j] /= pivot;
            constants[i] /= pivot;
            steps.append(formatMatrix(matrix, constants, variables));
        }

        // Обнуление под текущей строкой
        for (int k = i + 1; k < n; ++k) {
            double factor = matrix[k][i];
            for (int j = i; j < vars; ++j)
                matrix[k][j] -= factor * matrix[i][j];
            constants[k] -= factor * constants[i];
            steps.append(QString("Вычитаем %1 × строку %2 из строки %3, чтобы обнулить элемент в столбце %4.")
                             .arg(factor, 0, 'f', 3)
                             .arg(i + 1)
                             .arg(k + 1)
                             .arg(i + 1));
            steps.append(formatMatrix(matrix, constants, variables));
        }
    }

    // Проверка на несовместность или бесконечно много решений
    int rank = 0;
    for (int i = 0; i < n; ++i) {
        bool nonZeroRow = false;
        for (int j = 0; j < vars; ++j) {
            if (!qFuzzyIsNull(matrix[i][j])) {
                nonZeroRow = true;
                break;
            }
        }

        if (!nonZeroRow && !qFuzzyIsNull(constants[i])) {
            error = "Система несовместна — нет решений.";
            return false;
        }

        if (nonZeroRow)
            ++rank;
    }

    if (rank < vars) {
        error = "Система неопределённа — бесконечно много решений.";

        return false;
    }

    steps.append("Полученная ступенчатая матрица:");
    steps.append(formatMatrix(matrix, constants, variables));
    steps.append("Начинаем обратную подстановку:");

    // === Адаптация под неквадратную систему ===
    solution.resize(vars); // теперь по количеству переменных
    for (int i = vars - 1; i >= 0; --i) {
        double sum = 0.0;

        // Найти строку, содержащую ненулевой коэффициент при переменной i
        int pivotRow = -1;
        for (int row = i; row >= 0; --row) {
            if (!qFuzzyIsNull(matrix[row][i])) {
                pivotRow = row;
                break;
            }
        }

        if (pivotRow == -1) {
            solution[i] = 0; // свободная переменная
            continue;
        }

        for (int j = i + 1; j < vars; ++j)
            sum += matrix[pivotRow][j] * solution[j];

        solution[i] = (constants[pivotRow] - sum) / matrix[pivotRow][i];

        QString step = QString("%1 = (%2 - %3) / %4 = %5")
                           .arg(variables[i])
                           .arg(constants[pivotRow], 0, 'f', 3)
                           .arg(sum, 0, 'f', 3)
                           .arg(matrix[pivotRow][i], 0, 'f', 3)
                           .arg(solution[i], 0, 'f', 3);

        step.replace("- -", "+ ");
        step.replace("+ -", "- ");

        steps.append(step);
    }

    QString answer = "Ответ: ";
    QStringList resultParts;
    for (int i = 0; i < vars; ++i)
        resultParts << QString("%1 = %2").arg(variables[i]).arg(solution[i], 0, 'f', 3);
    steps.append("\n\n" + answer + resultParts.join(", "));

    return true;
}
