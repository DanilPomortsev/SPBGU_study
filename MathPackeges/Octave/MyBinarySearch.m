function retval = MyBinarySearch (a, b, f)
  a_copy = a;
  b_copy = b;
  if(f(a_copy)*f(b_copy) > 0)
    retval = false;
    return
  endif
  count_itr = 0;
  middle = a_copy + (b_copy - a_copy) / 2;
  while(f(a_copy)*f(b_copy) < 0)

    past_middle = middle;
    middle = a_copy + (b_copy - a_copy) / 2;

    if((abs(past_middle - middle) < 0.000001) && (count_itr > 0)&&(count_itr > 100))
      break;
    endif
    count_itr += 1;

    if(f(middle) * f(a_copy) < 0)
      b_copy = middle;
    else
      a_copy = middle;
    endif
    past_middle = middle;

  retval = middle;
  endwhile
endfunction
