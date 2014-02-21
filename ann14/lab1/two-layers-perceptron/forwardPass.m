function [ HOut, OOut ] = forwardPass(X, W, V, ndata)
    HIn = W*X;
    HOut = [2 ./ (1+exp(-HIn)) - 1; ones(1,ndata)];
    OIn = V*HOut;
    OOut = 2 ./ (1+exp(-OIn)) - 1;
end

