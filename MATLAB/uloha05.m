function main()

    clear; clc; close all;
    load databody.mat
    
    % 2. Vytvorenie vstupnych a vystupnych matic pre neuronovu siet
    % (Tento krok je rovnaky ako v tvojom povodnom skripte)
    datainnet = [data1; data2; data3; data4; data5]';
    dataoutnet = [ones(1,50) zeros(1,200); zeros(1,50) ones(1,50) zeros(1,150); ...
              zeros(1,100) ones(1,50) zeros(1,100); zeros(1,150) ones(1,50) zeros(1,50); ...
              zeros(1,200) ones(1,50)];

end