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

fileZero = fopen("../matrices/zero_matrices.matrs", "wt");
fprintf(fileZero, "%i %i\n", 1, 2);

diag(1, 1) = 10;
A = ort * diag * transpose(ort);
for j = 1:MATRIX_SIZE
    A(2, j) = A(3, j);
    A(j, 2) = A(j, 2);
end
A
b = A * x;
fprintf(fileZero, "%i ", MATRIX_SIZE);
% Так как norm(A) * norm(inv(A)) неопределен (обратная матрица к
% матрице с нулевым определителем не определена), будем записывать
% просто ноль
fprintf(fileZero, "%.15f\n", 0);
fprintf(fileZero, "%.15f ", A);
fprintf(fileZero, "\n");
fprintf(fileZero, "%.15f ", b);
fprintf(fileZero, "\n");

B = 10 * A;
b = A * x;

fprintf(fileZero, "%i ", MATRIX_SIZE);
fprintf(fileZero, "%.15f\n", 0);
fprintf(fileZero, "%.15f ", B);
fprintf(fileZero, "\n");
fprintf(fileZero, "%.15f ", b);
fprintf(fileZero, "\n");
fclose(fileZero);

fileRoots = fopen("../matrices/zero_roots.matrs", "rt");
roots = fscanf(fileRoots, "%f", [MATRIX_SIZE 2]);
fclose(fileRoots);
factOshibka1 = norm(roots(:, 1) - x)
nevyazka1 = norm(A * roots(:, 1) - b)
factOshibka2 = norm(roots(:, 2) - x)
nevyazka2 = norm(A * roots(:, 2) - b)