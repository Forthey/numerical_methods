#pragma once
#include <vector>
#include <string>
#include <pretty_stl.hpp>

/// \class точка
class Point {
public:
    double x, y;

    explicit Point(double x, double y) : x(x), y(y) {}
};

/// \class Квадратичный полином
class QuadPoly {
public:
    /// Коэффициенты полинома
    double a = 0, b = 0, c = 0;
    /// Отрезок, на котором действует полином
    double x0 = 0, x1 = 0;

    QuadPoly() = default;
    QuadPoly(double a, double b, double c, double x0, double x1) : a(a), b(b), c(c), x0(x0), x1(x1) {}
};


#define str(a) std::to_string(a)
/// \brief Функция преобразует полином в одну строку
/// \param quadPoly полином
/// \return Полином как строка
std::string quadPolyToStr(QuadPoly const& quadPoly);

/// \brief Функция преобразует точку в одну строку
/// \param point точка
/// \return Точка как строка
std::string pointToStr(Point const& point);

// Класс, строящий квадратичный сплайн и вычисляющий его значения в нужных точках
class QuadraticSpline {
    std::vector<Point> tabFunc;

    /// \brief Функция считает значние сплайна в заданной точке
    /// \param spline сплайн
    /// \param x заданная точка
    /// \return Значение сплайна в заданной точке
    static double splineY(std::vector<QuadPoly> const& spline, double x);

    /// \brief Функция считает значние полинома в заданной точке
    /// \param quadPoly полином
    /// \param x заданная точка
    /// \return Значение полинома в заданной точке
    static double quadPolyY(QuadPoly const& quadPoly, double x);

    /// \brief Функция считает значние производной полинома в заданной точке
    /// \param a коэффициент при x^2
    /// \param b коэффициент при x
    /// \return Значение производной полинома в заданной точке
    static double derFromCoefs(double a, double b, double x);

    /// \brief Функция считает коэффициенты квадратичного полинома в заданном диапазоне
    /// \param \a коэффициент при x^2
    /// \param x1, x0 диапазон
    /// \param y1, y0 значения в данных x1, x0
    /// \param d0 производная в x0
    /// \return Коэффициенты полинома в заданном диапазоне
    static QuadPoly evalLocalCoefficients(double x1, double x0, double y0, double y1, double d0);

    /// \brief Функция считает коэффициенты квадратичного полинома по трём точкам
    /// \param \a коэффициент при x^2
    /// \param x2, x1, x0 значения по x
    /// \param y2, y1, y0 значения в данных x2, x1, x0
    /// \return Коэффициенты полинома
    static QuadPoly evalFirstCoefficients(double x2, double x1, double x0, double y2, double y1, double y0);
public:
    /// \brief Функция возвращает искомую табличную функцию
    /// \return Табличная функция как массив точек
    std::vector<Point> const & getPoints();

    /// \brief Функция добавляет точку в массив искомых точек
    /// \param x,y - координаты точки
    void addPointToTabFunc(double x, double y);

    /// \brief Основная функция программы - считает по добавленным искомым точкам коэффициенты полиномов сплайна
    /// \return Сплайн как массив коэффицциентов квадратичных полиномов
    std::vector<QuadPoly> evaluateCoefficients();

    /// \brief Функция считает для переданного сплайна значения в конкретных внутренних точках
    /// \param pointsCnt число точек, в которых надо посчитать значения
    /// \return Массив точек сплайна размером в pointsCnt
    static std::vector<Point> getSplineValues(std::vector<QuadPoly> const& spline, long pointsCnt);
};
