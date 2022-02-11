clear;clc;
fs = 44100;
tiledlayout(4,2)
magnitudes = zeros(8,9);

  

freq = [0 125 250 500 1000 2000 4000 8000 44100];
normFreq=freq/fs;

materials = ["Rough concrete", "Wood lining, 12 mm", "Wood, 16 mm thick", "Glass, single pane, 3 mm", "Pile carpet, 6 mm","Studio curtains, 6 mm from wall","Fabric covered panel, 6 pcf rockwool core","Fibre absorber, mineral fibre"];

% rough concrete
magnitudes(1,:) = [0 0.02 0.02 0.03 0.03 0.04 0.05 0.05 1];

% wood lining 
magnitudes(2,:) = [0 0.27 0.23 0.22 0.15 0.10 0.07 0.06 1];

% wood 1.6 cm
magnitudes(3,:) = [0 0.18 0.12 0.10 0.09 0.08 0.07 0.07 1];

% glass single pane
magnitudes(4,:) = [0 0.08 0.04 0.03 0.03 0.02 0.02 0.02 1];

% pile carpet
magnitudes(5,:) = [0 0.03 0.09 0.20 0.54 0.70 0.72 0.72  1];

% studio curtains
magnitudes(6,:) = [0 0.36 0.26 0.51 0.45 0.62 0.76 0.76 1];

% fabric panel
magnitudes(7,:) = [0 0.21 0.66 1.0 1.0 0.97 0.98 0.98  1];

% fibre absorber
magnitudes(8,:) = [0 0.20 0.56 0.82 0.87 0.70 0.53 0.53 1];



%{
% smooth unpainted concrete
magnitudes(2,:) = [0 0.01 0.01 0.02 0.02 0.02 0.05 0.05 1];

% Smooth brickwork, 10 mm deep pointing, pit sand mortar
magnitudes(3,:) = [0 0.08 0.09 0.12 0.16 0.22 0.24 0.24 1];

% glass single pane
magnitudes(4,:) = [0 0.08 0.04 0.03 0.03 0.02 0.02 0.02 1];

% wood 1.6 cm
magnitudes(5,:) = [0 0.18 0.12 0.10 0.09 0.08 0.07 0.07 1];

% wooden lining 
magnitudes(6,:) = [0 0.27 0.23 0.22 0.15 0.10 0.07 0.06 1];

% cotton carpet
magnitudes(7,:) = [0 0.07 0.31 0.49 0.81 0.66 0.54 0.48 1];

% hairy carpet 
magnitudes(8,:) = [0 0.11 0.14 0.37 0.43 0.27 0.25 0.25 1];
%}
magnitudes = 1-magnitudes;

a = zeros(length(materials),4);
b = zeros(length(materials),4);

for filter = 1:size(magnitudes,1)
[b(filter,:),a(filter,:)]=yulewalk(3,normFreq,magnitudes(filter,:));

nexttile
[h,w] = freqz(b(filter,:),a(filter,:),128);
plot(w/pi,20*log10(abs(h)))
ax = gca;
ax.YLim = [-50 0];
xlabel('Normalized Frequency (\times\pi rad/sample)')
ylabel('Magnitude (dB)')
title(materials(filter))
grid
 end
 
 ba = [b,a];

allOneString1 = regexprep(num2str(ba(1,:)),'\s+',',')
allOneString2 = regexprep(num2str(ba(2,:)),'\s+',',')
allOneString3 = regexprep(num2str(ba(3,:)),'\s+',',')
allOneString4 = regexprep(num2str(ba(4,:)),'\s+',',')
allOneString5 = regexprep(num2str(ba(5,:)),'\s+',',')
allOneString6 = regexprep(num2str(ba(6,:)),'\s+',',')
allOneString7 = regexprep(num2str(ba(7,:)),'\s+',',')
allOneString8 = regexprep(num2str(ba(8,:)),'\s+',',')
