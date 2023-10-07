fileRoot = fopen("../matrices/root.matr", "rt");
fileRoots = fopen("../matrices/roots.matrs", "rt");

x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
roots = fscanf(fileRoots, "%f", [MATRIX_SIZE (E_MAX - E_MIN + 1)]);

fclose(fileRoot);
fclose(fileRoots);

norm1 = zeros(1, E_MAX - E_MIN + 1);
norm2 = zeros(1, E_MAX - E_MIN + 1);

e = zeros(1, E_MAX - E_MIN + 1);
for i = E_MIN:E_MAX
    e(i) = 10^i;
end

for i = E_MIN:E_MAX
    diag(1, 1) = e(i);
    A = ort * diag * transpose(ort);
    b = A * x;
    norm(A * roots(i) - b)
    norm1(i) = norm(roots(i) - x);
    norm2(i) = norm(A * roots(i) - b);
end


loglog(e, norm1);
grid on
figure
loglog(e, norm2);
grid on