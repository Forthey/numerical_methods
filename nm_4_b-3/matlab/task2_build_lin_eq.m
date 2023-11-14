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
fprintf(fileMatrices, "%i %i\n", 1, 9);

left = 25;
right = 40;
for i = 1:MATRIX_SIZE
    diag(i, i) = left + (right - left) * (i - 1) / MATRIX_SIZE;
end

fileDet = fopen("../matrices/determinants.txt", "wt");

for i = 1:(MATRIX_SIZE - 1)
    A = ort * diag * transpose(ort);
    b = A * x;
    for j = 1:(i - 1)
        A(j, j) = A(j, j) / 10;
    end
    fprintf(fileDet, "%.15f ", det(A));

    fprintf(fileMatrices, "%i ", MATRIX_SIZE);
    fprintf(fileMatrices, "%.15f %.15f ", diag(1, 1), diag(MATRIX_SIZE, MATRIX_SIZE));
    fprintf(fileMatrices, "%.15f ", A);
    fprintf(fileMatrices, "\n");
    fprintf(fileMatrices, "%.15f ", b);
    fprintf(fileMatrices, "\n");
end
fclose(fileMatrices);