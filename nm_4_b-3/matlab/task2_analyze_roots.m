% Считывание корней
fileRoot = fopen("../matrices/root.matr", "rt");
fileRoots = fopen("../matrices/roots.matrs", "rt");
x = fscanf(fileRoot, "%f", [MATRIX_SIZE 1]);
roots = fscanf(fileRoots, "%f", [MATRIX_SIZE 12]);
fclose(fileRoot);
fclose(fileRoots);

% Вычисление норм
norm1 = zeros(1, 12);
norm2 = zeros(1, 12);



diag = eye(MATRIX_SIZE);
for i = 1:MATRIX_SIZE
    diag(i, i) = 100 * i;
end

e = zeros(1, 12);
for i = 1:12
    e(i) = 10^(-i);
end 

for i = 1:(MATRIX_SIZE - 1)
    diag(i, i) = diag(i, i) / 10; 
    A = ort * diag * transpose(ort);
    b = A * x;
    norm1(i) = norm(roots(:, i) - x);
    norm2(i) = norm(A * roots(:, i) - b);

    % Проверка выполнения неравенства
    db = 2 * (0.5 - rand(MATRIX_SIZE,1)) .* b;
    condNum = norm(A) * norm(inv(A));
    norm1(i) / norm(roots(:, i));
    norm(db) * norm(b);
end

% Вывод норм на экран
loglog(e, norm1);
hold on
loglog(e, norm2);
legend("|x* - x|", "|A*x-b|");
title("Зависимость норм от точности");
xlabel("точность");
ylabel("норма");
grid on
hold off

figure
fileDet = fopen("../matrices/determinants.txt", "rt");
dets = fscanf(fileDet, "%f", [1 9]);
iter = [9 12 19 34 49 51 52 191 375];
loglog(dets, iter);

title("Зависимость числа итераций от определителя при точности 10^(-10)");
xlabel("|A|");
ylabel("N");
grid on