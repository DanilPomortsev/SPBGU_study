function retval = MyNewtonMethod (f, x_0_material, x_0_complex, eps)
  t = 0.0000001;
  curr_x = x_0;
  while(abs(f(curr_x + x_0_complex*i)) > eps)
      diff = (f(curr_x + t) - f(curr_x)) / t;
      curr_x -= f(curr_x)/diff;
  endwhile
 retval = curr_x;
endfunction
