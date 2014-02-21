x=[-5:1:5]';
y=x;
z=exp(-x.*x*0.1) * exp(-y.*y*0.1)' - 0.5;
%mesh (x, y, z);

ndata = 11*11;
targets = reshape (z, 1, ndata);
[xx, yy] = meshgrid (x, y);
patterns = [reshape(xx, 1, ndata); reshape(yy, 1, ndata)];

% Training
nrNodes = 3;
epochs = 1000;
alpha = 0.9;
n = 0.1;
[errors, W, V, OOut] = twoLayer(patterns, targets, epochs, n, alpha, nrNodes, x, y);

