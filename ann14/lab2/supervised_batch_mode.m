% Patterns
x = [0:0.1:2*pi]';

% Calculate function
f = square(2*x);
%f = cos(2*x);

r = zeros(1, units);
% Draw the expected results, actual results and residual values
for units = 2:rows(x)
    makerbf();
    Phi = calcPhi(x, m, var);
    w = Phi\f;
    r(1,units) = max(abs(f-Phi*w));
    
    rbfplot1(x, Phi*w, f, units);
    drawnow;
    pause(0.1);
end
%
% Units required for sin2x residual value of
%   0.1:    7
%   0.01    25
%   0.001   56
%
% square(2x)
%   0.1:
%   0.01: 
%   0.001: 
%