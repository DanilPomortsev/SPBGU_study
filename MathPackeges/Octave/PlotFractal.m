t = [-5:0.001:5];
a = 1/ 4;
b = 1 / 16;
m = 8;
n = 8;
x = cos(t) - a*cos(m*t) + b*sin(n*t);
y = sin(t) + a*sin(m*t) + b*cos(n*t);
s = 25;
hold on
for i = 1:s
  plot(x/i,y/i);
end
grid on
