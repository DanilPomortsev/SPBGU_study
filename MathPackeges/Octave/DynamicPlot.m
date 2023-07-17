##x = -10:0.01:10;
##k = -2;
##y = k*x.^2 - 2;
##ph = plot(x,y);
##
##axis([-10 10 -100 100]) #оси нужно фиксировать
##
##while k <= 2
##  k = k + 0.01;
##  y = k*x.^2 - 2;
##  set(ph, 'XData',x,'YData',y);
##  pause(0.05)
##  drawnow
##endwhile

clear, clc
x = 0:pi/50:4*pi;
y = x;
[X,Y] = meshgrid(x,y);
z = 3*sin(X) + cos(Y);
h = surf(z);

axis tight

shading interp
colormap(ocean)

for k = 0:pi/100:2*pi
  z = (sin(X) + cos(Y)).*sin(k);
  set(h, 'ZData',z)

  drawnow
endfor
