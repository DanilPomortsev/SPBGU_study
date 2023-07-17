axis([-5 35 -20 20])
arr = [];
arrX = [];
radius = 1;

hold on

quantity_of_rings = 5;
diffrence_between_rings = radius*1.3;
for x_0 = 0:diffrence_between_rings:diffrence_between_rings*quantity_of_rings
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
    arrX(count) = x_centre;
    arrX(count) = x_centre;
    alpha = 0:0.01:2*pi;
    x = radius*cos(alpha) + x_centre;
    y = radius*sin(alpha) + y_centre;
    set(arr(count), 'XData',x,'YData',y);
    drawnow
  endfor
endfor
hold off

