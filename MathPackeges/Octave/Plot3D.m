##t = 0:0.05:9*pi;
##x = 2*sin(t)
##y = 3*cos(t)
##%plot3(x,y,t, 'linewidth', 3)
##comet3(x,y,t)
##grid on
##xlabel('x')
##ylabel('y')
##zlabel('z')
clear
u = -10:0.05:10;
v = -1:0.05:1;
[U,V] = meshgrid(u,v);
X = (1 + V./2.*cos(U./2)).*cos(U);
Y = (1 + V./2.*cos(U./2)).*sin(U);
Z = V./2.*sin(U./2);
%mesh(X, Y, Z)
surf(X,Y,Z);

