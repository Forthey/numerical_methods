#pragma once
using Function = double (&)(double);

/// \class Интеграл от заданной функции
class IntegralCalculator {
    // Ссылка на функцию
    Function f;
    // Порядок метода (=4)
    static int const methodOrder;
    // Знаменатель в правиле Рунге (=7)
    static double const rungeRuleDenominator;

    /// \brief Функция проверяет правило Рунге для двух значений интеграла и нужной точности
    /// \param I_2n значение интеграла при 2N разбиений
    /// \param I_n значение интеграла при N разбиений
    /// \param epsilon нужная точность
    /// \return Выполняется ли правило Рунге (true/false)
    static bool checkRungeRule(double I_2n, double I_n, double epsilon);
public:
    /// \class Результат вычислений интеграла
    class Result {
    public:
        // Значение интеграла
        double value;
        // Число итераций, которое понадобилось для вычисления значения
        long iterCnt;
        // Длина отрезка разбиения
        double h;
    };

    /// \brief Конструктор класса
    /// \param f подинтегральная функция
    explicit IntegralCalculator(Function f);

    /// \brief функция считает значение интеграла на заданном отрезке с заданной точностью
    /// \param a левая граница отрезка
    /// \param b правая граница отрезка
    /// \param epsilon требуемая точность
    /// \return Значение интеграла
    Result calculate(double a, double b, double epsilon);
};
