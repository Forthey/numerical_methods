% ...
fileHaus = fopen("../matrix/haus_vector.matr", "rt");
hausVector = fscanf(fileHaus, "%f", [10 1]);
ort = eye(10) - 2 * hausVector * transpose(hausVector) / (norm(hausVector)^2);
ort * transpose(ort)