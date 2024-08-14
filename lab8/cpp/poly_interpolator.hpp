#pragma once
#include <utility>
#include <fstream>
#include <format>

#include "poly.hpp"

using Grid = std::vector<long double>;
using GridFunc = std::vector<long double>;

// Класс для представления табличной функции
class TabularFunc {
public:
    Grid grid;
    GridFunc gridFunc;

    void addPoint(long double const x, long double const y) {
        grid.push_back(x);
        gridFunc.push_back(y);
    }
};


// Основной класс, ищущий коэффициенты полинома по заданной табличной функции
class PolyInterpolator {
    // Табличная функция
    TabularFunc tabFunc;
    // Путь к директории с файлами .tf .cf
    const std::string dataDirPath = "../data";
    // На случай, если в сетке будет 0
    const long double zeroReplacer = 0.000000000001;

    /**
     * \brief Функция, считающая корневой полином заданной табличной функции
     * \return Корневой полином
     */
    Poly findRootPoly();
    /**
    * \brief Функция, строящая полином по заданной табличной функции в форме Лагранжа
    * \return Интерполяционный полином
    */
    Poly findPolyLagrange();
    /**
    * \brief Функция, cчитающая w'(xk) (делитель в форме Лагранжа)
    * \return Делитель
    */
    long double findDenomFor(size_t index);
public:
    /**
    * \brief Функция, cчитающая w'(xk) (делитель в форме Лагранжа)
     * \param postfix Уникальный постфикс файла in, содержащий в себе id функции и № параграфа
    * \return Делитель
    */
    explicit PolyInterpolator(std::string const &postfix);
};
