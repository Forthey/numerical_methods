% Считывание чисел и векторов
fileRoot = fopen("../matrices/lyambda.matr", "rt");
fileRoots = fopen("../matrices/lyambda.txt", "rt");
fileVectors = fopen("../matrices/vectors.matrs", "rt");
lyambda = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
lyambdas = fscanf(fileRoots, "%f", [1 COUNT]);
vectors = fscanf(fileVectors, "%f", [MATRIX_SIZE COUNT]);
fclose(fileRoot);
fclose(fileRoots);

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);
% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);
% Создание диагональной матрицы и записывание собственных чисел в файл
for i = 1:MATRIX_SIZE
    diag(i, i) = log(i + 1) * i / 2 * sqrt(i) * abs(sin(i));
end
A = ort * diag * transpose(ort);

e = zeros(1, COUNT);
accuracyNum = zeros(1, COUNT);
normVec = zeros(1, COUNT);
normNev = zeros(1, COUNT);

for i = 1:COUNT 
    e(i) = 10^(E_MIN - i + 1);
    accuracyNum(i) = abs(lyambda(1) - lyambdas(i));
    curV = vectors(:, i);
    if curV(1) > 0
        curV = -curV;
    end
    normVec(i) = norm(curV - vector);
    normNev(i) = norm(A * curV - lyambdas(i) * curV);
end

% Вывод норм на экран
loglog(e, accuracyNum);
hold on
loglog(e, normVec);
loglog(e, normNev);
title("Зависимость разности с истинным с.ч. от точности");
legend("|l - l*|", "|x - x*|", "|Ax - lx|")
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