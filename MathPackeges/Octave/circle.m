function retval = circle (n,r)
  retval = false(n,n)
  if mod(n,2) == 1
    centr = fix(n / 2) + 1
  else
    centr = n / 2 + 0.5
  endif
  for i = 1:n
    for j = 1:n
      in  = (i - centr)*(i-centr) + (j - centr)*(j - centr)
      disp(in)
      if((i - centr)*(i-centr) + (j - centr)*(j - centr) <= r*r)
        retval(i, j) = true;
      endif
    endfor
  endfor
endfunction
