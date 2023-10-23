% Считывание корней
fileRoot = fopen("../matrices/root.matr", "rt");
fileRoots = fopen("../matrices/roots.matrs", "rt");
x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
roots = fscanf(fileRoots, "%f", [MATRIX_SIZE (E_MAX - E_MIN + 1)]);
fclose(fileRoot);
fclose(fileRoots);

% Вычисление норм
norm1 = zeros(1, E_MAX - E_MIN + 1);
norm2 = zeros(1, E_MAX - E_MIN + 1);
e = zeros(1, E_MAX - E_MIN + 1);
for i = E_MIN:E_MAX
    e(i) = 10^i;
end

inequalityTrue = true;

for i = E_MIN:E_MAX
    diag(1, 1) = (-1)^i * e(i);
    A = ort * diag * transpose(ort);
    b = A * x;
    norm1(i) = norm(roots(:, i) - x);
    norm2(i) = norm(A * roots(:, i) - b);

    % Проверка выполнения неравенства
    db = 2 * (0.5 - rand(MATRIX_SIZE,1)) .* b;
    condNum = norm(A) * norm(inv(A));
    if ~(norm1(i) / norm(roots(:, i)) <= condNum * norm(db) * norm(b))
        inequalityTrue = false;
    end
end

if inequalityTrue
    fprintf("Неравество выполняется!\n");
else
    fprintf("Неравенство не выполняется!\n");
end

% Вывод норм на экран
loglog(e, norm1);
hold on
grid on
loglog(e, norm2);
legend("|x* - x|", "|A*x-b|");
title("Зависимость норм от числа обусловленности");
xlabel("e");
ylabel("норма");