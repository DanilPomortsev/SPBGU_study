function retval = ShereCreate (x_0, y_0, radius, arr)
  axis tight;
  alpha = 0:0.1:2*pi;
  x = radius*cos(alpha) + x_0;
  y = radius*sin(alpha) + y_0;
  arr = [arr plot(x,y)];
  hold on
endfunction
