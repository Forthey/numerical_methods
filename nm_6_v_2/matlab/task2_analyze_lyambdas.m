% Считывание корней
fileRoot = fopen("../matrices/lyambda.matr", "rt");
fileRoots = fopen("../matrices/lyambda.txt", "rt");
lyambda = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
lyambdas = fscanf(fileRoots, "%f", [1 COUNT]);
fclose(fileRoot);
fclose(fileRoots);

e = zeros(1, COUNT);
accuracy = zeros(1, COUNT);

for i = 1:COUNT 
    e(i) = 10^(E_MIN - i + 1);
    accuracy(i) = abs(lyambda(1) - lyambdas(i));
end

% Вывод норм на экран
loglog(e, accuracy);
title("Зависимость разности с истинным с.ч. от точности");
xlabel("точность");
ylabel("|l - l*|");
grid on

figure
iter = [229 363 499 634 769 904 1039];
semilogx(e, iter);
title("Зависимость числа итераций от точности");
xlabel("точность");
ylabel("N");
grid on