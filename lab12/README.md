# Лабораторная работа 12: Решение задачи Коши для ОДУ 1 порядка методами Рунге-Кутты

## Вариант 6 (4 2)

## Метод: Р-К 3 порядка

## Функция

$$ y’=2x(x^2+y), (1, 2), y(a) = e $$
Точное решение:  
$$ y=e^{x^2}-x^2-1 $$

## Основные задания

Заданная точность достигается по правилу Рунге на каждом шаге, кроме метода Кутты-Мерсона.

### 7 баллов

1. Иллюстрация работы метода. Построить графики точного и численных решений для двух фиксированных значений шага на отрезке. Построить график ошибки на отрезке для этих решений.
2. Исследование точности метода. Заданная точность достигается по правилу Рунге на каждом шаге, кроме метода Кутты-Мерсона. Построить график изменения шага по отрезку. Построить график зависимости фактической погрешности от заданной точности.

### 8 баллов

1. Исследование сходимости метода. Построить зависимость фактической ошибки от фиксированного шага интегрирования, использовать логарифмическую шкалу по основанию 2. Оценить порядок метода.

### Дополнительное задание

Внести погрешность 1%, 2%, 3%, 4%, 5% в начальное условие. Требуется вычислить относительную ошибку для каждого значения максимального возмущения и построить график. Эксперимент выполняется 20 раз, строится график типа боксплот, по оси х среднее фактическое возмущение данных в эксперименте.