f1 = figure;
% polynom hpm
e = [0.1 0.01 0.001 0.0001 1e-05 1e-06 1e-07 1e-08 1e-09 1e-10];
iter = [4 8 11 14 18 21 24 28 31 34];
plot(iter, e, "red");
hold on
% polynom fpi
iter = [77 126 176 227 277 327 377 427 477 527];
plot(iter, e, "blue");
% polynom fzero
%fzero(2 * x^4 + 8 * x^3 + 8 * x^2 - 1);
hold off

f2 = figure;
% complex hpm
iter = [5 8 11 15 18 21 25 28 31 35];
plot(iter, e, "green");
hold on
% complex fpi
iter = [0 1 2 4 5 6 8 9 10 12];
plot(iter, e, "black");
%fzero(2 * atan(x) - x - 3);
hold off