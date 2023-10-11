% Константы 
MATRIX_SIZE = 10;
E_MIN = 1;
E_MAX = 15;

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
fprintf(fileMatrices, "%i %i %i\n", MATRIX_SIZE, E_MIN, E_MAX);

e = zeros(1, E_MAX - E_MIN + 1);
for i = E_MIN:E_MAX
    e(i) = 10^i;
end

for i = E_MIN:E_MAX
    diag(1, 1) = (-1)^i * e(i);
    A = ort * diag * transpose(ort);
    b = A * x;
    fprintf(fileMatrices, "%.15f\n", norm(A) * norm(inv(A)));
    fprintf(fileMatrices, "%.15f ", A);
    fprintf(fileMatrices, "\n");
    fprintf(fileMatrices, "%.15f ", b);
    fprintf(fileMatrices, "\n");
end
fclose(fileMatrices);