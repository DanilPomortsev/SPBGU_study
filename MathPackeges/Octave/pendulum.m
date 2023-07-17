function retval = pendulum (length, theta0, dt, time)
  g = 9.81;
  hold on;
  axis([0 2.5*length 0 2.5*length]);
  start = true;
  theta = theta0;
  omega = 0;

  hline = line([length, length+length*sin(theta)], [length, length-length*cos(theta)]);
  hball = scatter(length + length*sin(theta), -length*cos(theta), 'filled');
  set(hline, 'LineWidth', 2);
  set(hball, 'SizeData', 50);

  for curr_time = 0:dt:time
    alpha = -g/length*sin(theta);
    omega = omega + alpha*dt;
    theta = theta + omega*dt;

    set(hline, 'XData', [1.5*length, 1.5*length + length*sin(theta)]);
    set(hline, 'YData', [1.5*length, 1.5*length - length*cos(theta)]);
    set(hball, 'XData', 1.5*length + length*sin(theta));
    set(hball, 'YData', 1.5*length - length*cos(theta));
    set(hball, 'MarkerFaceColor', 'r');

    drawnow
  endfor
endfunction
