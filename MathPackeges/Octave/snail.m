function retval = snail (n)
  retval = zeros(n,n)
  direction = 0
  i = 2
  j = 0
  cur_val = 1
  while (i != n) && (j != n)
    retval(i,j) = curval
    if mod(direction,2) == 0
      if(i == 1) ||(j == n)
        direction = dirction + 1
      i = i - 1
      j = j + 1
    else
      if(i == 1) ||(j == n)
        direction = dirction + 1
      i = i - 1
      j = j + 1
    endif

    cur_val = cur_val + 1
  endwhile
endfunction
