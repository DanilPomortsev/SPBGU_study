x = -10:0.1:10;
##f = @(x) 1 + (1 + sin(x) - cos(x)).^ 2 - (sin(x.*2) - cos(x.*2) - 0.2).^2;
f = @(x) x.^3 - 1;
y = f(x);
hold on
plot(x,y);
vec_x = [];
vec_y = [];

##for curr_x = -5:0.3:5
##  x_solve = fzero(f, curr_x);
##  if((abs(f(x_solve)) < 0.00001) && (x_solve > -5) && (x_solve < 5))
##    vec_x = [vec_x x_solve]
##  endif
##endfor
##plot(vec_x, vec_y, 'r.', 'MarkerSize', 20)

##for curr_x = -5:0.5:5
##  x_solve = MyBinarySearch(curr_x, curr_x+0.5, f);
##  if((abs(f(x_solve)) < 0.00001) && (x_solve > -5) && (x_solve < 5))
##    vec_x = [vec_x x_solve]
##  endif
##endfor

for curr_x = -5:0.01:5;
  x_solve = MyNewtonMethod(f, curr_x, 0.000001);
  if((abs(f(x_solve)) < 0.000001) && (x_solve > -5) && (x_solve < 5))
    vec_x = [vec_x x_solve];
  endif
endfor

vec_x = uniquetol(vec_x, 0.000001);
vec_y = zeros(size(vec_x));
plot(vec_x, vec_y, 'r.', 'MarkerSize', 20);
