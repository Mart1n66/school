% =========================================================
% Zadanie 7 - CNN cast 
% Rozpoznavanie rukou pisanych cislic MNIST pomocou CNN
% =========================================================
clear; clc; close all;

%% -------------------------------------------------------
%  1. NACITANIE DAT MNIST
%  -------------------------------------------------------
mnist_path = 'C:\Users\slata\Documents\MATLAB\MNIST_MATLAB\MNIST_MATLAB';

train_images = read_idx(fullfile(mnist_path, 'train', 'images.idx3-ubyte'));
train_labels = read_idx(fullfile(mnist_path, 'train', 'labels.idx1-ubyte'));
test_images  = read_idx(fullfile(mnist_path, 'test',  'images.idx3-ubyte'));
test_labels  = read_idx(fullfile(mnist_path, 'test',  'labels.idx1-ubyte'));

trainX = single(train_images) / 255;
testX  = single(test_images)  / 255;
trainX = reshape(trainX, 28, 28, 1, []);
testX  = reshape(testX,  28, 28, 1, []);

trainY = categorical(train_labels);
testY  = categorical(test_labels);

% Validacna mnozina (10 % z trenovacich dat)
N = size(trainX, 4);
rng(42);
idx_all  = randperm(N);
nVal     = round(0.1 * N);
valIdx   = idx_all(1 : nVal);
trainIdx = idx_all(nVal+1 : end);

Xtr = trainX(:,:,:, trainIdx);   Ytr = trainY(trainIdx);
Xva = trainX(:,:,:, valIdx);     Yva = trainY(valIdx);
Xte = testX;                     Yte = testY;

fprintf('Trenovacich: %d  Validacnych: %d  Testovacich: %d\n\n', ...
        numel(trainIdx), nVal, size(Xte,4));

%% -------------------------------------------------------
%  2. DEFINICIA ARCHITEKTUR CNN 
%     CNN1: 2 konv. vrstvy (32,64 filtrov), FC 128
%     CNN2: 3 konv. vrstvy (32,64,128),    FC 128
%     CNN3: 3 konv. vrstvy (32,64,128),    FC 256
%  -------------------------------------------------------
layers_CNN1 = [
    imageInputLayer([28 28 1], 'Normalization','none')
    convolution2dLayer(3, 32, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    convolution2dLayer(3, 64, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    flattenLayer
    fullyConnectedLayer(128); reluLayer
    fullyConnectedLayer(10)
    softmaxLayer; classificationLayer
];

layers_CNN2 = [
    imageInputLayer([28 28 1], 'Normalization','none')
    convolution2dLayer(3, 32, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    convolution2dLayer(3, 64, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    convolution2dLayer(3, 128, 'Padding','same')
    batchNormalizationLayer; reluLayer
    flattenLayer
    fullyConnectedLayer(128); reluLayer
    fullyConnectedLayer(10)
    softmaxLayer; classificationLayer
];

layers_CNN3 = [
    imageInputLayer([28 28 1], 'Normalization','none')
    convolution2dLayer(3, 32, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    convolution2dLayer(3, 64, 'Padding','same')
    batchNormalizationLayer; reluLayer
    maxPooling2dLayer(2, 'Stride',2)
    convolution2dLayer(3, 128, 'Padding','same')
    batchNormalizationLayer; reluLayer
    flattenLayer
    fullyConnectedLayer(256); reluLayer
    fullyConnectedLayer(10)
    softmaxLayer; classificationLayer
];

%% -------------------------------------------------------
%  3. HYPERPARAMETRE TRENOVANIA (rovnake pre vsetky CNN)
%  -------------------------------------------------------
EPOCHS     = 15;
BATCH_SIZE = 64;
LEARN_RATE = 0.001;
N_RUNS     = 5;

itersPerEpoch = ceil(numel(trainIdx) / BATCH_SIZE);

opts = trainingOptions('adam', ...
    'MaxEpochs',           EPOCHS, ...
    'MiniBatchSize',        BATCH_SIZE, ...
    'InitialLearnRate',     LEARN_RATE, ...
    'ValidationData',       {Xva, Yva}, ...
    'ValidationFrequency',  itersPerEpoch, ...
    'Shuffle',             'every-epoch', ...
    'ExecutionEnvironment', 'auto', ...
    'Verbose',              false, ...
    'Plots',               'none');

%% -------------------------------------------------------
%  4. TRENOVANIE CNN – 5 BEHOV PRE KAZDU ARCHITEKTURU 
%  -------------------------------------------------------
archs = {layers_CNN1, layers_CNN2, layers_CNN3};
names = {'CNN1', 'CNN2', 'CNN3'};
R     = struct();

for m = 1:3
    fprintf('========== %s ==========\n', names{m});
    best_test_acc = 0;
    for r = 1:N_RUNS
        fprintf('  Beh %d/%d ... ', r, N_RUNS);
        rng(r * 100);
        [net, info] = trainNetwork(Xtr, Ytr, archs{m}, opts);

        predTr = classify(net, Xtr, 'MiniBatchSize', 512);
        predTe = classify(net, Xte, 'MiniBatchSize', 512);

        R.(names{m}).trainAcc(r) = mean(predTr == Ytr) * 100;
        R.(names{m}).testAcc(r)  = mean(predTe == Yte) * 100;
        R.(names{m}).trainLoss(r)= info.TrainingLoss(end);
        vl = info.ValidationLoss(~isnan(info.ValidationLoss));
        R.(names{m}).valLoss(r)  = vl(end);

        fprintf('Train: %.2f%%   Test: %.2f%%\n', ...
                R.(names{m}).trainAcc(r), R.(names{m}).testAcc(r));

        % ulozenie najlepsieho behu
        if R.(names{m}).testAcc(r) > best_test_acc
            best_test_acc = R.(names{m}).testAcc(r);
            
            R.(names{m}).net       = net;
            R.(names{m}).info      = info;
            R.(names{m}).predTest  = predTe;
            R.(names{m}).bestRunID = r; % TOTO NAM TAM CHYBALO!
        end
    end
end

%% -------------------------------------------------------
%  5. VYPIS TABULIEK
%  -------------------------------------------------------
fprintf('\n\n=== Tab.5: Porovnavane architektury CNN ===\n');
fprintf('%-6s %-12s %-16s %-10s %-8s %-6s\n', ...
        'Model','Conv vrstvy','Filtre','FC vrstvy','Epochy','Batch');
fprintf('%-6s %-12d %-16s %-10d %-8d %-6d\n','CNN1',2,'32, 64',    128,EPOCHS,BATCH_SIZE);
fprintf('%-6s %-12d %-16s %-10d %-8d %-6d\n','CNN2',3,'32, 64, 128',128,EPOCHS,BATCH_SIZE);
fprintf('%-6s %-12d %-16s %-10d %-8d %-6d\n','CNN3',3,'32, 64, 128',256,EPOCHS,BATCH_SIZE);

for m = 1:3
    nm = names{m};
    fprintf('\n=== Tab.%d: Vysledky 5 behov – %s ===\n', m+5, nm);
    fprintf('%-5s %-14s %-12s %-15s %-12s\n', ...
            'Beh','Train loss','Val loss','Train acc [%]','Test acc [%]');
    for r = 1:N_RUNS
        fprintf('%-5d %-14.4f %-12.4f %-15.2f %-12.2f\n', r, ...
                R.(nm).trainLoss(r), R.(nm).valLoss(r), ...
                R.(nm).trainAcc(r),  R.(nm).testAcc(r));
    end
end

fprintf('\n=== Tab.9: Suhrn CNN ===\n');
fprintf('%-6s %-14s %-14s %-16s %-14s\n', ...
        'Model','Min test[%]','Max test[%]','Priem test[%]','Priem val loss');
for m = 1:3
    nm = names{m};
    fprintf('%-6s %-14.2f %-14.2f %-16.2f %-14.4f\n', nm, ...
            min(R.(nm).testAcc), max(R.(nm).testAcc), ...
            mean(R.(nm).testAcc), mean(R.(nm).valLoss));
end

%% -------------------------------------------------------
%  6. GRAFY – Loss a Accuracy vs Epocha
%  -------------------------------------------------------
for m = 1:3
    nm   = names{m};
    info = R.(nm).info;

    nTr      = length(info.TrainingLoss);
    epochsTr = (1:nTr) / itersPerEpoch;

    val_iters = find(~isnan(info.ValidationLoss)); 
    epochsVL  = val_iters / itersPerEpoch; 
    
    vl = info.ValidationLoss(val_iters);
    va = info.ValidationAccuracy(val_iters);

    figure('Name', [nm ' - Priebeh ucenia'], 'NumberTitle','off');

    subplot(1,2,1);
    plot(epochsTr, info.TrainingLoss, 'b-', 'LineWidth',1.5); hold on;
    plot(epochsVL, vl, 'r--', 'LineWidth',1.5);
    xlabel('Epocha'); ylabel('Loss (Cross-entropy)');
    title([nm ' - Loss vs Epocha']);
    legend('Trenovacia loss','Validacna loss','Location','northeast');
    grid on; xlim([0 EPOCHS]);

    subplot(1,2,2);
    plot(epochsTr, info.TrainingAccuracy, 'b-', 'LineWidth',1.5); hold on;
    plot(epochsVL, va, 'r--', 'LineWidth',1.5);
    xlabel('Epocha'); ylabel('Uspesnost [%]');
    title([nm ' - Accuracy vs Epocha']);
    legend('Trenovacia acc','Validacna acc','Location','southeast');
    grid on; xlim([0 EPOCHS]);

    sgtitle(sprintf('%s – Najlepsi beh (Beh %d z %d)', nm, R.(nm).bestRunID, N_RUNS), 'FontSize', 12);
end

%% -------------------------------------------------------
%  7. KONTINGENCNA MATICA
%  -------------------------------------------------------
for m = 1:3
    nm = names{m};
    figure('Name', [nm ' - Kontingencna matica'], 'NumberTitle','off');
    confusionchart(Yte, R.(nm).predTest, ...
        'Title', sprintf('%s - Kontingencna matica (testovacie data, beh %d)', nm, R.(nm).bestRunID), ...
        'RowSummary','row-normalized', ...
        'ColumnSummary','column-normalized');
end

%% -------------------------------------------------------
%  8. DROPOUT ANALYZA – 3 modely, 5 behov kazdy
%     Zaklad: CNN2 architektura, early stopping (ValidationPatience=5)
%  -------------------------------------------------------
fprintf('\n\n========== DROPOUT ANALYZA ==========\n');

dropout_vals = [0.0, 0.3, 0.5];
drop_names   = {'D1_p00', 'D2_p03', 'D3_p05'};

opts_drop = trainingOptions('adam', ...
    'MaxEpochs',           30, ...
    'MiniBatchSize',        BATCH_SIZE, ...
    'InitialLearnRate',     LEARN_RATE, ...
    'ValidationData',       {Xva, Yva}, ...
    'ValidationFrequency',  itersPerEpoch, ...
    'ValidationPatience',   5, ...         % early stopping
    'Shuffle',             'every-epoch', ...
    'ExecutionEnvironment', 'auto', ...
    'Verbose',              false, ...
    'Plots',               'none');

DR = struct();

for d = 1:3
    dp = dropout_vals(d);
    dn = drop_names{d};
    fprintf('\n--- %s (dropout = %.1f) ---\n', dn, dp);

    if dp > 0
        layers_drop = [
            imageInputLayer([28 28 1], 'Normalization','none')
            convolution2dLayer(3, 32, 'Padding','same')
            batchNormalizationLayer; reluLayer
            maxPooling2dLayer(2, 'Stride',2)
            convolution2dLayer(3, 64, 'Padding','same')
            batchNormalizationLayer; reluLayer
            maxPooling2dLayer(2, 'Stride',2)
            convolution2dLayer(3, 128, 'Padding','same')
            batchNormalizationLayer; reluLayer
            flattenLayer
            dropoutLayer(dp)
            fullyConnectedLayer(128); reluLayer
            dropoutLayer(dp)
            fullyConnectedLayer(10)
            softmaxLayer; classificationLayer
        ];
    else
        layers_drop = layers_CNN2;   % bez dropoutu
    end

    for r = 1:N_RUNS
        fprintf('  Beh %d/%d ... ', r, N_RUNS);
        rng(r * 200);
        [net, info] = trainNetwork(Xtr, Ytr, layers_drop, opts_drop);

        predTr = classify(net, Xtr, 'MiniBatchSize', 512);
        predTe = classify(net, Xte, 'MiniBatchSize', 512);

        DR.(dn).trainAcc(r)  = mean(predTr == Ytr) * 100;
        DR.(dn).testAcc(r)   = mean(predTe == Yte) * 100;
        vl = info.ValidationLoss(~isnan(info.ValidationLoss));
        DR.(dn).valLoss(r)   = vl(end);
        DR.(dn).epochStop(r) = length(info.TrainingLoss) / itersPerEpoch;

        fprintf('Train: %.2f%%  Test: %.2f%%  Epochy: %.1f\n', ...
                DR.(dn).trainAcc(r), DR.(dn).testAcc(r), DR.(dn).epochStop(r));

        if r == N_RUNS
            DR.(dn).net  = net;
            DR.(dn).info = info;
        end
    end
end

% --- Suhrn dropout ---
fprintf('\n=== Tab.10: Porovnanie dropout – epocha pretrenovania ===\n');
fprintf('%-10s %-10s %-12s %-18s %-14s\n', ...
        'Model','Dropout','Pocet beh.','Priem epochStop','Priem val loss');
for d = 1:3
    dn = drop_names{d};
    fprintf('%-10s %-10.1f %-12d %-18.1f %-14.4f\n', dn, dropout_vals(d), N_RUNS, ...
            mean(DR.(dn).epochStop), mean(DR.(dn).valLoss));
end

fprintf('\n=== Tab.11: Suhrn dropout – uspesnost ===\n');
fprintf('%-10s %-12s %-17s %-15s %-14s\n', ...
        'Dropout','Pocet beh.','Priem train[%]','Priem test[%]','Priem val loss');
for d = 1:3
    dn = drop_names{d};
    fprintf('%-10.1f %-12d %-17.2f %-15.2f %-14.4f\n', dropout_vals(d), N_RUNS, ...
            mean(DR.(dn).trainAcc), mean(DR.(dn).testAcc), mean(DR.(dn).valLoss));
end

% --- Graf val loss dropout – posledny beh ---
figure('Name','Dropout - Porovnanie val loss','NumberTitle','off');
farby = {'b-','r--','g:'};
hold on;
for d = 1:3
    dn   = drop_names{d};
    info = DR.(dn).info;
    
    val_iters = find(~isnan(info.ValidationLoss)); 
    ep = val_iters / itersPerEpoch; 
    
    vl = info.ValidationLoss(val_iters);
    plot(ep, vl, farby{d}, 'LineWidth', 1.8);
end
legend('Dropout = 0.0','Dropout = 0.3','Dropout = 0.5','Location','northeast');
xlabel('Epocha'); ylabel('Validacna loss');
title('Porovnanie val loss pre rozne nastavenie dropout-u (CNN2)');
grid on;

%% -------------------------------------------------------
%  9. POROVNANIE MLP a CNN – suhrn
%  -------------------------------------------------------
fprintf('\n=== Tab.12: Suhrn MLP vs CNN ===\n');
fprintf('%-10s %-14s %-18s %-14s\n', ...
        'Pristup','Pocet modelov','Priem test acc[%]','Priem val loss');
% CNN hodnoty z tohto skriptu
cnn_priem_acc  = mean([mean(R.CNN1.testAcc), mean(R.CNN2.testAcc), mean(R.CNN3.testAcc)]);
cnn_priem_loss = mean([mean(R.CNN1.valLoss), mean(R.CNN2.valLoss), mean(R.CNN3.valLoss)]);
fprintf('%-10s %-14d %-18s %-14s\n', 'MLP','2','(doplnit z MLP)','(doplnit z MLP)');
fprintf('%-10s %-14d %-18.2f %-14.4f\n', 'CNN', 3, cnn_priem_acc, cnn_priem_loss);

%% -------------------------------------------------------
% 10. CPU vs GPU POROVNANIE – CNN2
%  -------------------------------------------------------
fprintf('\n========== CPU vs GPU – CNN2 (%d epoch) ==========\n', EPOCHS);

opts_cpu = trainingOptions('adam', ...
    'MaxEpochs', EPOCHS, 'MiniBatchSize', BATCH_SIZE, ...
    'InitialLearnRate', LEARN_RATE, ...
    'ValidationFrequency', 9999, ...
    'ExecutionEnvironment','cpu', ...
    'Verbose',false, 'Plots','none');

rng(1);
t = tic;
trainNetwork(Xtr, Ytr, layers_CNN2, opts_cpu);
cpu_cnn2 = toc(t);
fprintf('CNN2 CPU: %.1f s\n', cpu_cnn2);

if canUseGPU
    opts_gpu = trainingOptions('adam', ...
        'MaxEpochs', EPOCHS, 'MiniBatchSize', BATCH_SIZE, ...
        'InitialLearnRate', LEARN_RATE, ...
        'ValidationFrequency', 9999, ...
        'ExecutionEnvironment','gpu', ...
        'Verbose',false, 'Plots','none');
    rng(1);
    t = tic;
    trainNetwork(Xtr, Ytr, layers_CNN2, opts_gpu);
    gpu_cnn2 = toc(t);
    fprintf('CNN2 GPU: %.1f s\n', gpu_cnn2);

    fprintf('\n=== Tab.13: CPU vs GPU ===\n');
    fprintf('%-8s %-14s %-14s %-12s\n','Model','CPU cas [s]','GPU cas [s]','Zrychlenie');
    fprintf('%-8s %-14.1f %-14.1f %-10.1fx\n','CNN2',cpu_cnn2,gpu_cnn2,cpu_cnn2/gpu_cnn2);
    fprintf('(MLP2 cas doplnit z ZAD7_MLP_final.m)\n');

    % Graf
    figure('Name','CPU vs GPU - CNN2','NumberTitle','off');
    b = bar([cpu_cnn2, gpu_cnn2], 'FaceColor','flat');
    b.CData(1,:) = [0.2 0.4 0.8];
    b.CData(2,:) = [0.9 0.4 0.1];
    set(gca,'XTickLabel',{'CPU','GPU'});
    ylabel('Cas trenovania [s]');
    title(sprintf('CNN2 – CPU vs GPU  (Adam, LR=%.4f, Batch=%d, %d epoch)', ...
                  LEARN_RATE, BATCH_SIZE, EPOCHS));
    hold on;
    text(1, cpu_cnn2 + cpu_cnn2*0.02, sprintf('%.0f s', cpu_cnn2), ...
         'HorizontalAlignment','center','FontWeight','bold');
    text(2, gpu_cnn2 + cpu_cnn2*0.02, sprintf('%.0f s  (%.1fx)', gpu_cnn2, cpu_cnn2/gpu_cnn2), ...
         'HorizontalAlignment','center','FontWeight','bold');
    grid on;
else
    fprintf('GPU nie je dostupna na tomto stroji.\n');
end

%% -------------------------------------------------------
% 11. VIZUALIZACIA VZORIEK – najlepsia CNN
%  -------------------------------------------------------
best_net = R.CNN3.net;
figure('Name','CNN3 - Vzorky 0-9','NumberTitle','off');
for digit = 0:9
    idx_d     = find(test_labels == digit, 1);
    img       = Xte(:,:,:, idx_d);
    predClass = classify(best_net, img);
    scores    = predict(best_net, img);

    subplot(2, 5, digit + 1);
    imshow(squeeze(img), [0 1]);
    title(sprintf('Skut.: %d\nPred.: %s\nSkore: %.3f', ...
                   digit, char(predClass), max(scores)), ...
          'FontSize', 8);
end
sgtitle('CNN3 – Testovanie: 1 vzorka z kazdej triedy (0–9)');

fprintf('\n=== CNN cast dokoncena ===\n');
fprintf('Skontroluj ci CNN3 dosiahol priem. test acc >= 99%%\n');
for m = 1:3
    fprintf('  %s: priem. test acc = %.2f%%\n', names{m}, mean(R.(names{m}).testAcc));
end
