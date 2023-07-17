function arrX, arr = arrOfGraph (x_0, radius, quantity_of_rings, diffrence_between_rings, arr)
  arrX = [];
  arr = [];
  for x_curr = x_0:diffrence_between_rings:diffrence_between_rings*quantity_of_rings
    x = -1000;
    y = -1000;
    arrX = [arrX x_curr];
    arr = [arr plot(x,y)];
  endfor
endfunction
