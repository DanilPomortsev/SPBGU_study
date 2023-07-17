x = -pi:0.1:pi;
y = -pi:0.1:pi;
[X,Y] = meshgrid(x,y);

h = 0.0000001;
x_0 = 0;
y_0 = -1;

z_0 = 19;

Z = 20 - X.^2 - Y.^2;

derivZ = 1;

x_0 += h;
valDevrivXPast = 20 - x_0^2 - y_0^2;
x_0 -= h;
valDevrivXCurr = 20 - x_0^2 - y_0^2;
derivX = (valDevrivXPast - valDevrivXCurr)/h;

y_0 += h;
valDevrivYPast = 20 - x_0^2 - y_0^2;
y_0 -= h;
valDevrivYCurr = 20 - x_0^2 - y_0^2;
derivY = (valDevrivYPast - valDevrivYCurr)/h;

norm = sqrt(derivZ^2 + derivX^2 + derivY^2);
derivX /= norm
derivY /= norm
derivZ /= norm

t = -3:0.01:0;
x_norm = x_0 + derivX*t;
y_norm = y_0 + derivY*t;
z_norm = z_0 + derivZ*t;

hold on
surf(X,Y,Z);
axis equal;
plot3(x_norm,y_norm,z_norm, 'linewidth', 3);

xlabel('x');
ylabel('y');
zlabel('z');
grid on;
