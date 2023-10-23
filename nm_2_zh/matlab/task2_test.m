% Считывания корня
TEST_SIZE = 4;
fileRoot = fopen("../matrices/test_root.matr", "rt");
x = fscanf(fileRoot, "%f", [TEST_SIZE 1]);
fclose(fileRoot);

A = [-1 2 -3 4; -4 3 -2 -1; 5 -9 7 1; 4 5 -2 0];
for i = 1:TEST_SIZE
    for j = 1:i
        A(j, i) = A(i, j);
    end
end
b = A * x;
testFile = fopen("../matrices/test_matrices.matrs", "wt");
fprintf(testFile, "%i %i\n", 1, 1);
fprintf(testFile, "%i ", TEST_SIZE);
fprintf(testFile, "%.15f\n", norm(A) * norm(inv(A)));
fprintf(testFile, "%.15f ", A);
fprintf(testFile, "\n");
fprintf(testFile, "%.15f ", b);
fprintf(testFile, "\n");
fclose(testFile);