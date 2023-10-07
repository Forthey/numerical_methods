% Константы 
MATRIX_SIZE = 10;
E_MIN = 0;
E_MAX = 14;

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);

% Считывания корня
fileRoot = fopen("../matrices/root.matr");
rootVector = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
fclose(fileRoot);

% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);


fileMatrices = fopen("../matrices/matrices.matrs", "wt");
fprintf(fileMatrices, "%i %i %i ", MATRIX_SIZE, E_MIN, E_MAX);
for i = E_MIN:E_MAX
    diag(1, 1) = 10^i;
    matr = ort * diag * transpose(ort);
    [c, p] = chol(matr);
    if (p ~= 0) 
        "Какая-то матрица не положительно определенная..."
        break;
    end
    fprintf(fileMatrices, "%f ", norm(matr) * norm(inv(matr)));
    fprintf(fileMatrices, "%f ", matr);
    fprintf(fileMatrices, "%f ", matr * rootVector);
end
fclose(fileMatrices);