% Константы 
MATRIX_SIZE = 10;
E_MIN = 1;
E_MAX = 15;

%file = fopen("../matrices/root.matr", "wt");
%for i = 1:10
%    fprintf(file, "%.15f ", log(i + 1) * i / 2 * sqrt(i));
%end

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
for i = E_MIN:E_MAX
    diag(1, 1) = 10^i;
    A = ort * diag * transpose(ort);
    b = A * x;
    [c, p] = chol(A);
    if (p ~= 0) 
        "Какая-то матрица не положительно определенная..."
        break;
    end
    fprintf(fileMatrices, "%.15f\n", norm(A) * norm(inv(A)));
    fprintf(fileMatrices, "%.15f ", A);
    fprintf(fileMatrices, "\n");
    fprintf(fileMatrices, "%.15f ", b);
    fprintf(fileMatrices, "\n");
end
fclose(fileMatrices);