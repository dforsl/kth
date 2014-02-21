% Test data classes
%   classA: centered around (1.0,0.5)
%   classB: centered around (-1.0,0.0)
sd = 0.5; % standard deviation
classA(1,:) = [randn(1,50) .* 0.2 - 1.0, ...
randn(1,50) .* 0.2 + 1.0];
classA(2,:) = randn(1,100) .* 0.2 + 0.3;
classB(1,:) = randn(1,100) .* 0.3 + 0.0;
classB(2,:) = randn(1,100) .* 0.3 - 0.1;

% Merge into one pattern
patterns = [classA, classB];

% Create values row vector
targets(1,1:100) = ones(1,100);
targets(1,101:200) = ones(1,100) .* -1.0;

% Permute into random order
permute = randperm(200);
patterns = patterns(:, permute);
targets = targets(:, permute);

plot(patterns(1, find(targets>0)), ...
    patterns(2, find(targets>0)), '*',...
    patterns(1, find(targets<0)), ...
    patterns(2, find(targets<0)), '+');