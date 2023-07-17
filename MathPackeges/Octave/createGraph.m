axis([-5 35 -20 20])
arr = [];
arrX = [];
radius = 1;

hold on

quantity_of_rings = 8
for x_0 = 0:1.3:1.3*8
  x = -1000;
  y = -1000;
  arrX = [arrX x_0];
  arr = [arr plot(x,y)];
endfor

count = 0;
x_delta = 0.1;
for step = 0:1:10000
  for count = 1:1:quantity_of_rings
    x_centre = arrX(count) + x_delta;
    arrX(count) = x_centre;
    y_centre = sin(x_centre);
    alpha = 0:0.01:2*pi;
    x = radius*cos(alpha) + x_centre;
    y = radius*sin(alpha) + y_centre;
    set(arr(count), 'XData',x,'YData',y);
    drawnow
  endfor
endfor
hold off

