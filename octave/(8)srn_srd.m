function [i, j] = srn2srd(x, y, L, C)
  i = round(1 - (y - 1)*(L - 1)/2);
  j = round(1 + (x + 1)*(C - 1)/2);
endfunction

function [x, y] = srd2srn(i, j, L, C)
  x = 2*(j-1)/(C-1) - 1;
  y = 2*(L-i)/(L-1) - 1;
endfunction

function X = elipse(L, C)
  X = zeros(L, C);
  N = ceil(2*pi*max(L, C));
  t = linspace(0,1,N);
  x = cos(2*pi*t);
  y = sin(2*pi*t);
  [i, j] = srn2srd(x, y, L, C);
  X(sub2ind(size(X), i, j)) = 1;
endfunction
