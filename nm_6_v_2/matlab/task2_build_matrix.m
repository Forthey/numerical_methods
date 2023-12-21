% Константы 
MATRIX_SIZE = 10;
E_MIN = -1;
E_MAX = -10;
COUNT = E_MIN - E_MAX + 1;

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);

% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);

% Создание диагональной матрицы и записывание собственных чисел в файл
file = fopen("../matrices/lyambda.matr", "wt");
for i = 1:MATRIX_SIZE
    if i == 1
        diag(i, i) = sqrt(abs(sin(i)));
    else
        diag(i, i) = 3 * sin(i) + 9;
    end
    fprintf(file, "%.15f ", diag(i, i));
end

fileMatrices = fopen("../matrices/matrices.matrs", "wt");
fprintf(fileMatrices, "%i %i\n", E_MIN, E_MAX);

A = ort * diag * transpose(ort);

[V,D] = eig(A);
vector = V(:, 1);
fprintf(fileMatrices, "%i ", MATRIX_SIZE);
fprintf(fileMatrices, "%.15f ", A);
fprintf(fileMatrices, "\n");

fclose(fileMatrices);