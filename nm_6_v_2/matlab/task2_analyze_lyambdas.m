% Считывание чисел и векторов
fileRoot = fopen("../matrices/lyambda.matr", "rt");
fileRoots = fopen("../matrices/lyambda.txt", "rt");
fileRoots2 = fopen("../matrices/lyambdas_not_normed", "rt");
fileVectors = fopen("../matrices/vectors.matrs", "rt");
lyambda = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
lyambdas = fscanf(fileRoots, "%f", [1 COUNT]);
notNormedLyambdas = fscanf(fileRoots2, "%f", [1 COUNT]);
vectors = fscanf(fileVectors, "%f", [MATRIX_SIZE COUNT]);
fclose(fileRoot);
fclose(fileRoots);
fclose(fileRoots2);

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);
% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);
% Создание диагональной матрицы и записывание собственных чисел в файл
for i = 1:MATRIX_SIZE
    if i == 1
        diag(i, i) = sqrt(abs(sin(i)));
    else
        diag(i, i) = 3 * sin(i) + 9;
    end
    fprintf(file, "%.15f ", diag(i, i));
end

A = ort * diag * transpose(ort);

e = zeros(1, COUNT);
accuracyNum = zeros(1, COUNT);
accuracyNum2 = zeros(1, COUNT);
normVec = zeros(1, COUNT);
normNev = zeros(1, COUNT);

for i = 1:COUNT 
    e(i) = 10^(E_MIN - i + 1);
    accuracyNum(i) = abs(lyambda(1) - lyambdas(i));
    accuracyNum2(i) = abs(lyambda(1) - notNormedLyambdas(i));
    curV = vectors(:, i);
    if curV(1) > 0
        curV = -curV;
    end
    normVec(i) = norm(curV - vector);
    normNev(i) = norm(A * curV - lyambdas(i) * curV);
end

e1 = [e(1) e(2) e(3)];
acc2 = [abs(0.298977205272969 - lyambda(1)) abs(0.294406181633526 - lyambda(1)) abs(0.292399003892378 - lyambda(1))];


% Вывод норм на экран
loglog(e, accuracyNum);
hold on
loglog(e, accuracyNum2);
loglog(e, normVec);
loglog(e, normNev);
title("Зависимость разностей с истинным с.ч. от точности");
legend("|l - l*|", "|l - l*| (без норм)", "|x - x*|", "|Ax - lx|")
xlabel("точность");
ylabel("|l - l*|");
grid on

figure
iter = [2 3 5 6 8 10 11 13 15 16];
semilogx(e, iter);
title("Зависимость числа итераций от точности");
xlabel("точность");
ylabel("N");
grid on