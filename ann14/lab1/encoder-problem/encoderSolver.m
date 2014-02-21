patterns = eye(8) * 2 - 1;
targets = patterns;

% Number of epochs to run
epochs = 4000;
x = 1:epochs;

% Number of hidden layers
nrNodes = 3;

% Step length
n = 0.01;

% Alpha
alpha = 0.9;

% Dimensions
[insize, ndata] = size(patterns);
[outsize, ndata] = size(targets);
    
[err, W, V] = twoLayer(patterns, targets, epochs, n, alpha, nrNodes);
disp(sign(W));
% Plot the results
plot(x, err, '-');
axis ([0, epochs, 0, 200], 'square');