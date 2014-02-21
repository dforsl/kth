function [ errors, W, V, OOut] = twoLayerGen(patterns, targets, epochs, n, alpha, nrNodes, x, y)
    % Dimensions
    [insize, ndata] = size(patterns);
    [outsize, ndata] = size(targets);

    % Set variables
    k = 25;
    permute = randperm(ndata);
    [~, inv_perm] = sort(permute);
    patterns = patterns(:, permute);
    targets = targets(:, permute);
    
    sub_patterns = patterns(:,[1:1:k]);
    sub_targets = targets(:,[1:1:k]);
    X = [sub_patterns; ones(1,k)];
    T = sub_targets;
    
    % Initial weights
    W = randn(nrNodes, insize + 1) .* 2/sqrt(insize) - 1/sqrt(insize);
    V = randn(outsize, nrNodes + 1) .* 2/sqrt(insize) - 1/sqrt(insize);
       
    % Init errors vector
    errors = zeros(1,epochs);
    % Init deltas
    deltaW = 0;
    deltaV = 0;
    
    % Loop through the epochs
    for epoch = 1:epochs
        % Forward pass
        [HOut, OOut] = forwardPass(X, W, V, k);

        % Backward pass
        [deltaO, deltaH] = backwardPass(T, nrNodes, HOut, OOut, V);
        
        % Weight update
        deltaW = (deltaW .* alpha) - (deltaH * X') .* (1-alpha);
        deltaV = (deltaV .* alpha) - (deltaO * HOut') .* (1-alpha);
        W = W + deltaW .* n;
        V = V + deltaV .* n;
    
        % Second forward pass
        [~, OOut] = forwardPass([patterns; ones(1, ndata)], W, V, ndata);
        
        zz = reshape(OOut(:, inv_perm), 11, 11);
        mesh(x,y,zz);
        axis([-5 5 -5 5 -0.7 0.7]);
        drawnow;
    end
end

