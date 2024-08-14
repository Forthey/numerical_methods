#pragma once
using Function = double (&)(double);

/// \class Интеграл от заданной функции
class IntegralCalculator {
    Function func;
    /// Порядок метода (=4)
    static int const methodOrder;
    /// Знаменатель в правиле Рунге (=7)
    static double const rungeRuleDenominator;

    /// \brief Класс-Функция с счетчиком внутри
    /// \param x аргумент
    /// \param reset сбрасывать ли счетчик
    /// \return значение функции в точке x
    class FuncWithCallCnt {
        Function f;
        int callCnt = 0;
    public:
        explicit FuncWithCallCnt(Function f) : f(f) {}

        [[nodiscard]] double operator()(double x) {
            callCnt++;
            return f(x);
        }

        [[nodiscard]] int getCallCnt() const { return callCnt; }
    };

    /// \brief Функция конвертирует t из [-1; 1] в [a; b]
    /// \param t значение из [0; 1]
    /// \param a, b границы отрезка [a; b]
    /// \return преобразованное значение
    inline static double convert_t_to_ab(double const t, double const a, double const b) {
        return (a + b) / 2.0 + (b - a) / 2.0 * t;
    }

    /// \brief Функция проверяет правило Рунге для двух значений интеграла и нужной точности
    /// \param I_2n значение интеграла при 2N разбиений
    /// \param I_n значение интеграла при N разбиений
    /// \param epsilon нужная точность
    /// \return Выполняется ли правило Рунге (true/false)
    static bool checkRungeRule(double I_2n, double I_n, double epsilon);

    /// \brief Функция вычисляет интеграл методом Гаусса на отрезке для n узлов
    /// \param a, b границы отрезка
    /// \param n число узлов (2, 3, 4)
    /// \param f функция
    /// \return значение интеграла
    static double calculateGaussOnSubsection(double a, double b, int n, FuncWithCallCnt &f);

    /// \brief функция считает значение интеграла на заданном подотрезке с заданной точностью
    /// \param a левая граница отрезка
    /// \param b правая граница отрезка
    /// \param epsilon требуемая точность
    /// \return Значение интеграла
    static double calculateGaussRec(double a, double b, double epsilon, FuncWithCallCnt &f);
public:
    /// \class Результат вычислений интеграла
    class Result {
    public:
        /// Значение интеграла
        double value;
        /// Число итераций, которое понадобилось для вычисления значения
        long callCnt;
    };

    /// \brief Конструктор класса
    /// \param f подинтегральная функция
    explicit IntegralCalculator(Function f);

    /// \brief функция считает значение интеграла на заданном отрезке с заданной точностью методом 3/8
    /// \param a левая граница отрезка
    /// \param b правая граница отрезка
    /// \param epsilon требуемая точность
    /// \return Значение интеграла
    Result calculateThreeEight(double a, double b, double epsilon);

    /// \brief функция считает значение интеграла на заданном отрезке с заданной точностью
    /// \param a левая граница отрезка
    /// \param b правая граница отрезка
    /// \param epsilon требуемая точность
    /// \return Значение интеграла
    Result calculateGauss(double a, double b, double epsilon);
};
