clear;
close all;

trajectoire1 = csvread('../trajectoires/courbe1.csv');
trajectoire2 = csvread('../trajectoires/courbe2.csv');
trajectoire3 = csvread('../trajectoires/courbe3.csv');

X = {trajectoire1(:, 1) trajectoire2(:, 1) trajectoire3(:, 1)};
Z = {trajectoire1(:, 3) trajectoire2(:, 3) trajectoire3(:, 3)};

[nTrajectoire, pTrajectoire] = size(X);

targets = [0 0; -3000 0; 0 1000; 3500 0; 1700 -1000; -1500 -1000; 0 -1000; 0 0];
[nTargets, pTargets] = size(targets);
labels = cellstr( num2str([1:8]') );  %' # labels correspond to their order

figure;
hold on
for i = 1:nTargets
  circle(targets(i, 1), targets(i, 2), 400)
end
text(targets(:,1), targets(:,2), labels, 'VerticalAlignment','middle', 'HorizontalAlignment','center')

% plot(X{:, 1}, Z{:, 1}, 'b')
plot(X{:, 2}, Z{:, 2}, 'r')
% plot(X{:, 3}, Z{:, 3}, 'k')

xlabel('X')
ylabel('Z')
set(gca,'ydir','reverse')
axis([-4000 4000 -2000 2000])
