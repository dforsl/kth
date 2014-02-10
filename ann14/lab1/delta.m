% Dimensions
[insize, ndata] = size(patterns);
[outsize, ndata] = size(targets);

% Number of epochs to run
epochs = 2000;

% Step length
n = 0.0001;

% Set variables for the delta rule
X = [patterns; ones(1,ndata)];
T = targets;

% Initial weights
W = randn(outsize, insize + 1);
disp(W);
% Loop through the epochs
for epoch = 1:epochs
    % Delta rule
    deltaW = -n*(W*X-T)*transpose(X);
    W = W + deltaW;
    
    % Draw current state
    p = W(1,1:2);
    k = -W(1, insize+1) / (p*p');
    l = sqrt(p*p');
    plot (patterns(1, find(targets>0)), ...
    patterns(2, find(targets>0)), '*', ...
    patterns(1, find(targets<0)), ...
    patterns(2, find(targets<0)), '+', ...
    [p(1), p(1)]*k + [-p(2), p(2)]/l, ...
    [p(2), p(2)]*k + [p(1), -p(1)]/l, '-');
    axis ([-2, 2, -2, 2], 'square');
    drawnow;
end