function [ deltaO, deltaH ] = backwardPass(T, nrNodes, HOut, OOut, V)
    deltaO = (OOut - T) .* ((1 + OOut) .* (1 - OOut)) * 0.5;
    deltaH = (V' * deltaO) .* ((1 + HOut) .* (1 - HOut)) * 0.5;
    deltaH = deltaH(1:nrNodes, :);
end

