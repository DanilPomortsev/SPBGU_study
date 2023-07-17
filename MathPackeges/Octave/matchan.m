function matr = matchan(n,m)
  matr = false(n,m);
  matr(:. 2:2::m) = 1;
end

