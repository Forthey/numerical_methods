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
e = zeros(1, 12);

left
right
umAll
diag = eye(MATRIX_SIZE);
for i = 1:MATRIX_SIZE
    diag(i, i) = left + (right - left) * (i - 1) / MATRIX_SIZE;
end

A = (ort * diag * transpose(ort)) / umAll;
b = A * x;

for i = 1:12
    e(i) = 10^(-i + 1);
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
dets = fscanf(fileDet, "%f", [1 MATRIX_SIZE]);
iter = [230 650 644 642 643 644 658 669 670 260];
semilogx(dets, iter);

title("Зависимость числа итераций от определителя при точности 10^-^1^0");
xlabel("|A|");
ylabel("N");
grid on

figure
iter2 = [15 37 61 85 109 133 157 181 205 230 254 278];
loglog(e, iter2);
grid on