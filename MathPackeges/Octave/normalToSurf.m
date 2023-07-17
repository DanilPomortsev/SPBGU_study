function retval = normalToSurf(x_0, y_0, Z_handle, X, Y)
  h = 0.0000001;
  derivZ = 1;

  x_0 += h;
  valDevrivXPast = Z_handle(x_0,y_0);
  x_0 -= h;
  valDevrivXCurr = Z_handle(x_0,y_0);
  derivX = (valDevrivXPast - valDevrivXCurr)/h;

  y_0 += h;
  valDevrivYPast = Z_handle(x_0,y_0);
  y_0 -= h;
  valDevrivYCurr = Z_handle(x_0,y_0);
  derivY = (valDevrivYPast - valDevrivYCurr)/h;

  norm = sqrt(derivZ^2 + derivX^2 + derivY^2);
  derivX /= norm;
  derivY /= norm;
  derivZ /= norm;

  t = -3:0.01:0;
  x_norm = x_0 + derivX*t;
  y_norm = y_0 + derivY*t;
  z_norm = Z_handle(x_0,y_0) + derivZ*t;
  Z = Z_handle(X, Y);

  hold on
  surf(X,Y,Z);
  axis equal;
  plot3(x_norm,y_norm,z_norm, 'linewidth', 3);

  xlabel('x');
  ylabel('y');
  zlabel('z');
  grid on;
endfunction
