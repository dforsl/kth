function [ errors, W, V, OOut] = twoLayer(patterns, targets, epochs, n, alpha, nrNodes)
    % Dimensions
    [insize, ndata] = size(patterns);
    [outsize, ndata] = size(targets);

    % Set variables for the delta rule
    X = [patterns; ones(1,ndata)];
    T = targets;

    % Initial weights
    W = randn(nrNodes, insize + 1) .* 2/sqrt(insize) - 1/sqrt(insize);
    V = randn(outsize, nrNodes + 1) .* 2/sqrt(insize) - 1/sqrt(insize);
       
    % Init errors vector
    errors = zeros(1,epochs);
    % Init deltas
    deltaW = 0;
    deltaV = 0;
    currErrs = 1;
    % Loop through the epochs
    %while currErrs > 0
    for epoch = 1:epochs
        % Forward pass
        [HOut, OOut] = forwardPass(X, W, V, ndata);

        % Backward pass
        [deltaO, deltaH] = backwardPass(T, nrNodes, HOut, OOut, V);
        
        % Weight update
        deltaW = (deltaW .* alpha) - (deltaH * X') .* (1-alpha);
        deltaV = (deltaV .* alpha) - (deltaO * HOut') .* (1-alpha);
        W = W + deltaW .* n;
        V = V + deltaV .* n;

        % Calculate errors in this epoch
        errors(epoch) = sum(sum(abs(sign(OOut) - T)./2));
        currErrs = sum(sum(abs(sign(OOut) - T)./2));
        disp(sign(OOut));
        disp(currErrs);
    end
end

