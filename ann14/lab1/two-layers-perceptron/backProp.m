% Dimensions
[insize, ndata] = size(patterns);
[outsize, ndata] = size(targets);

% Number of epochs to run
epochs = 200;
x = 1:epochs;

% Number of hidden layers
nrLayers = 200;

% Step length
n = 0.001;

% Alpha
alpha = 0.9;

% Run two layers perceptron
errors1 = twoLayer(patterns, targets, nrLayers, epochs, 0.01, alpha);

% Run two layers perceptron
errors2 = twoLayer(patterns, targets, nrLayers, epochs, 0.001, alpha);

% Run two layers perceptron
errors3 = twoLayer(patterns, targets, nrLayers, epochs, 0.0001, alpha);

% Plot the results
plot(x, errors1, '-', x, errors2, '-', x, errors3, '-');
axis ([0, epochs, 0, 200], 'square');
legend('n = 0.01', 'n = 0.001', 'n = 0.0001');