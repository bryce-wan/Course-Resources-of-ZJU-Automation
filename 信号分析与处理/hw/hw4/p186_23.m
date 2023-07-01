clear;clc;

syms alpha beta n0 N n k

assume(N,'integer');
assume(n0,'integer');
assume(n,'integer');

h(n) = piecewise(0 <= n & n <= (N-1), alpha^n, 0);
x(n) = piecewise(n0 <= n, beta^(n-n0), 0);

y(n) = symsum(h(n-k) * x(k), k, -inf, inf);

pretty(y(n));
