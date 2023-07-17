function retval = ShereCreate (x_0, y_0, radius, arr)
  x = -100:0.1:100;
  y = sqrt((x. - x_0).^2 - radius^2)  + y_0;
  arr = [arr plot(x,y)
endfunction
