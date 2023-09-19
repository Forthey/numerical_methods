% Зависимость итераций от точности

f1 = figure;

e = [1 2 3 4 5 6 7 8 9 10];

% polynom hpm
iter = [4 8 11 14 18 21 24 28 31 34];
plot(e, iter, "red");
hold on
% polynom fpi
iter = [1 2 6 10 14 18 22 24 28 32];
plot(e, iter, "blue");
% complex hpm
iter = [5 8 11 15 18 21 25 28 31 35];
plot(e, iter, "green");
% complex fpi
iter = [0 1 2 4 5 6 8 9 10 12];
plot(e, iter, "black");

legend('полином МПД','полином МПИ', 'транс МПД', 'транс МПИ');
title("Зависимость числа итераций от точности");
xlabel("e^-^i");
ylabel("число итераций");
hold off

% Фактическая ошибка

f2 = figure;

rootPoly = 0.3065629648763765278566431734271871535837611883492695275488983669;
rootComplex = -5.8001297200890918399;
rootsPolyHpm = [0.309688 0.306582 0.306194 0.306534 0.306561 0.306563 0.306563 0.306563 0.306563 0.306563];
rootsPolyFpi = [0.278471 0.293256 0.305297 0.306453 0.306553 0.306562 0.306563 0.306563 0.306563 0.306563];
rootsComplexHpm = [-5.78125 -5.80078 -5.80029 -5.80014 -5.80013 -5.80013 -5.80013 -5.80013 -5.80013 -5.80013];
rootsComplexFpi = [-5.91 -5.90253 -5.79942 -5.80015 -5.80023 -5.80013 -5.80013 -5.80013 -5.80013 -5.80013];

% polynom hpm
e = [1 2 3 4 5 6 7 8 9 10];
plot(e, log(abs(rootsPolyHpm - rootPoly)), "red");
hold on
% polynom fpi
plot(e, log(abs(rootsPolyFpi - rootPoly)), "blue");
% complex hpm
plot(e, log(abs(rootsComplexHpm - rootComplex)), "green");
% complex fpi
plot(e, log(abs(rootsComplexFpi - rootComplex)), "black");

legend('полином МПД','полином МПИ', 'транс МПД', 'транс МПИ');
title("Зависимость ln разности с истинным корнем от точности");
xlabel("e^-^i");
ylabel("ln(|x - x^*|)");
hold off