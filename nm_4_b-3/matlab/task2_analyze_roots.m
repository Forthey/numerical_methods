% Считывание корней
fileRoot = fopen("../matrices/root.matr", "rt");
fileRoots = fopen("../matrices/roots.matrs", "rt");
x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
roots = fscanf(fileRoots, "%f", [MATRIX_SIZE 12]);
fclose(fileRoot);
fclose(fileRoots);

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);

% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);

% Вычисление норм
norm1 = zeros(1, 12);
norm2 = zeros(1, 12);



diag = eye(MATRIX_SIZE);
left = 15;
right = 20;
for i = 1:MATRIX_SIZE
    diag(i, i) = left + (right - left) * (i - 1) / MATRIX_SIZE;
end

for i = 1:12
    A = ort * diag * transpose(ort);
    A(1, 1) = A(1, 1) / 10;
    b = A * x;
    norm1(i) = norm(roots(:, i) - x);
    norm2(i) = norm(A * roots(:, i) - b);
end

% Вывод норм на экран
loglog(e, norm1);
hold on
loglog(e, norm2);
legend("|x* - x|", "|A*x-b|");
title("Зависимость норм от точности");
xlabel("точность");
ylabel("норма");
grid on
hold off

figure
fileDet = fopen("../matrices/determinants.txt", "rt");
dets = fscanf(fileDet, "%f", [1 9]);
iter = [14 3646 2284 1698 1521 1648 1713 5876 6609];
semilogx(dets, iter);

title("Зависимость числа итераций от определителя при точности 10^-^1^0");
xlabel("|A|");
ylabel("N");
grid on