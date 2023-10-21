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

e = zeros(1, E_MAX - E_MIN + 1);
for i = E_MIN:E_MAX
    e(i) = 10^i;
end

fileZero = fopen("../matrices/zero_matrices.matrs", "wt");
fprintf(fileZero, "%i %i\n", E_MIN, E_MAX);
for i = E_MIN:E_MAX
    diag(1, 1) = 0;
    A = diag;
    b = A * x;
    fprintf(fileZero, "%i ", MATRIX_SIZE);
    fprintf(fileZero, "%.15f\n", norm(A) * norm(inv(A)));
    fprintf(fileZero, "%.15f ", A);
    fprintf(fileZero, "\n");
    fprintf(fileZero, "%.15f ", b);
    fprintf(fileZero, "\n");
end
fclose(fileZero);