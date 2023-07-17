## Copyright (C) 2023 danul
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} chess (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: danul <danul@LAPTOP-QV1HN5HI>
## Created: 2023-03-10

function retval = chess (input1, input2)
  retval = false(input1,input2);
  l = 0
  for i = 1:input1
    for j = 1:input2
      if mod(l,2) == 0
        retval(i, j) = true
      end
      l = l + 1
    end
  end
endfunction
