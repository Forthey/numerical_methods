% Константы 
MATRIX_SIZE = 10;
file = fopen("../matrices/root.matr", "wt");
for i = 1:10
    fprintf(file, "%.15f ", log(i + 1) * i / 2 * sqrt(i) * sin(i));
end

% Считывание вектора Хауса для задания ортогональной матрицы
fileHaus = fopen("../matrices/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [MATRIX_SIZE 1]);
fclose(fileHaus);

% Считывания корня
fileRoot = fopen("../matrices/root.matr", "rt");
x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
fclose(fileRoot);

% Создание ортогональной матрицы
diag = eye(MATRIX_SIZE);
ort = diag - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);

fileMatrices = fopen("../matrices/matrices.matrs", "wt");
fprintf(fileMatrices, "%i %i\n", 1, MATRIX_SIZE);

left = 2;
right = 10;
for i = 1:MATRIX_SIZE
    diag(i, i) = left + (right - left) * (i - 1) / MATRIX_SIZE;
end

fileDet = fopen("../matrices/determinants.txt", "wt");

umAll = 4;
umCur = 4;
% Уменьшение определителя матрицы через уменьшение с.ч.
for row = 1:MATRIX_SIZE
    if row ~= 1
        diag(row, row) = diag(row, row) / umCur;
    end
    A = (ort * diag * transpose(ort)) / umAll;
    b = A * x;
    det(A)
    lambda1 = diag(1, 1);
    lambdan = diag(MATRIX_SIZE, MATRIX_SIZE);
    fprintf(fileDet, "%.15f ", det(A));

    fprintf(fileMatrices, "%i ", MATRIX_SIZE);
    fprintf(fileMatrices, "%.15f %.15f ", lambda1, lambdan);
    fprintf(fileMatrices, "%.15f ", A);
    fprintf(fileMatrices, "\n");
    fprintf(fileMatrices, "%.15f ", b);
    fprintf(fileMatrices, "\n");
end
fclose(fileMatrices);