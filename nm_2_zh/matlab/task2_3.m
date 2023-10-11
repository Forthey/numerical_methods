% Файл для записи матриц гилберта
HILBERT_MIN = 3;
HILBERT_MAX = 10;
hilbertFile = fopen("../matrices/hilbert_matrices.matrs", "wt");

% Считывания корня
fileRoot = fopen("../matrices/root.matr", "rt");
x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
fclose(fileRoot);

fprintf(hilbertFile, "%i %i\n", HILBERT_MIN, HILBERT_MAX);
for size = HILBERT_MIN:HILBERT_MAX
    hilbertMatrix = zeros(size, size);
    for i = 1:size
        for j = 1:size
            hilbertMatrix(i, j) = 1 / (i + j - 1);
        end
    end
    
    b = hilbertMatrix * x(1:size);
    fprintf(hilbertFile, "%i ", size);
    fprintf(hilbertFile, "%.15f\n", norm(hilbertMatrix) * norm(inv(hilbertMatrix)));
    fprintf(hilbertFile, "%.15f ", hilbertMatrix);
    fprintf(hilbertFile, "\n");
    fprintf(hilbertFile, "%.15f ", b);
    fprintf(hilbertFile, "\n");
end
fclose(hilbertFile);