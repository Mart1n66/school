% =========================================================
% Zadanie 7 - MLP cast 
% Rozpoznavanie rukou pisanych cislic MNIST pomocou MLP
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

fprintf('=== MNIST dataset ===\n');
fprintf('Train obrazky: %s\n', mat2str(size(train_images)));
fprintf('Test  obrazky: %s\n', mat2str(size(test_images)));

% Normalizacia [0,1] a reshape na [28x28x1xN]
trainX = single(train_images) / 255;
testX  = single(test_images)  / 255;
trainX = reshape(trainX, 28, 28, 1, []);
testX  = reshape(testX,  28, 28, 1, []);

% Kategoricke labely
trainY = categorical(train_labels);
testY  = categorical(test_labels);

% Validacna mnozina – 10 % z trenovacich dat
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
%  2. DEFINICIA ARCHITEKTUR MLP
%     MLP1: 1 skryta vrstva, 256 neuronov
%     MLP2: 2 skryte vrstvy, 512 + 256 neuronov
%  -------------------------------------------------------
layers_MLP1 = [
    imageInputLayer([28 28 1], 'Normalization','none')
    flattenLayer
    fullyConnectedLayer(256)
    reluLayer
    fullyConnectedLayer(10)
    softmaxLayer
    classificationLayer
];

layers_MLP2 = [
    imageInputLayer([28 28 1], 'Normalization','none')
    flattenLayer
    fullyConnectedLayer(512)
    reluLayer
    fullyConnectedLayer(256)
    reluLayer
    fullyConnectedLayer(10)
    softmaxLayer
    classificationLayer
];

%% -------------------------------------------------------
%  3. HYPERPARAMETRE TRENOVANIA (rovnake pre obe struktury)
%  -------------------------------------------------------
EPOCHS     = 20;
BATCH_SIZE = 64;
LEARN_RATE = 0.001;
N_RUNS     = 5;

itersPerEpoch = ceil(numel(trainIdx) / BATCH_SIZE);

opts = trainingOptions('adam', ...
    'MaxEpochs',           EPOCHS, ...
    'MiniBatchSize',        BATCH_SIZE, ...
    'InitialLearnRate',     LEARN_RATE, ...
    'ValidationData',       {Xva, Yva}, ...
    'ValidationFrequency',  itersPerEpoch, ...  % raz za epochu
    'Shuffle',             'every-epoch', ...
    'Verbose',              false, ...
    'Plots',               'none');

%% -------------------------------------------------------
%  4. TRENOVANIE – 5 BEHOV PRE KAZDU STRUKTURU
%  -------------------------------------------------------
archs = {layers_MLP1, layers_MLP2};
names = {'MLP1', 'MLP2'};
R     = struct();

for m = 1:2
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
            R.(names{m}).bestRunID = r; % Oznacime si, ktory beh to bol
        end
    end

    fprintf('  -> Najlepsi model pre %s bol beh %d s test. uspesnostou %.2f%%\n', ...
            names{m}, R.(names{m}).bestRunID, best_test_acc);
end

%% -------------------------------------------------------
%  5. VYPIS TABULIEK DO COMMAND WINDOW
%  -------------------------------------------------------
fprintf('\n\n');
fprintf('=== Tab.1: Porovnavane struktury MLP ===\n');
fprintf('%-6s %-14s %-20s %-8s %-6s %-6s\n', ...
        'Model','Skryte vrstvy','Neurony','Epochy','LR','Batch');
fprintf('%-6s %-14d %-20s %-8d %-6.4f %-6d\n','MLP1',1,'256',EPOCHS,LEARN_RATE,BATCH_SIZE);
fprintf('%-6s %-14d %-20s %-8d %-6.4f %-6d\n','MLP2',2,'512, 256',EPOCHS,LEARN_RATE,BATCH_SIZE);

for m = 1:2
    nm = names{m};
    fprintf('\n=== Tab.%d: Vysledky 5 behov – %s ===\n', m+1, nm);
    fprintf('%-5s %-14s %-12s %-15s %-12s\n', ...
            'Beh','Train loss','Val loss','Train acc [%]','Test acc [%]');
    for r = 1:N_RUNS
        fprintf('%-5d %-14.4f %-12.4f %-15.2f %-12.2f\n', r, ...
                R.(nm).trainLoss(r), R.(nm).valLoss(r), ...
                R.(nm).trainAcc(r),  R.(nm).testAcc(r));
    end
end

fprintf('\n=== Tab.4: Suhrn MLP ===\n');
fprintf('%-6s %-14s %-14s %-16s %-14s\n', ...
        'Model','Min test[%]','Max test[%]','Priem test[%]','Priem val loss');
for m = 1:2
    nm = names{m};
    fprintf('%-6s %-14.2f %-14.2f %-16.2f %-14.4f\n', nm, ...
            min(R.(nm).testAcc), max(R.(nm).testAcc), ...
            mean(R.(nm).testAcc), mean(R.(nm).valLoss));
end

%% -------------------------------------------------------
%  6. GRAFY – Loss a Accuracy vs Epocha 
%     Zobrazuje sa najlepsi beh
%  -------------------------------------------------------
for m = 1:2
    nm   = names{m};
    info = R.(nm).info;

    nTr      = length(info.TrainingLoss);
    epochsTr = (1:nTr) / itersPerEpoch;

    % Validacne hodnoty su zaznamenane raz za epochu
    vl = info.ValidationLoss;
    va = info.ValidationAccuracy;
    epochsVL = linspace(1/itersPerEpoch, EPOCHS, sum(~isnan(vl)));
    vl = vl(~isnan(vl));
    va = va(~isnan(va));

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

    sgtitle([nm ' – Najlepsi beh'], 'FontSize', 12);
end

%% -------------------------------------------------------
%  7. KONTINGENCNA MATICA 
%  -------------------------------------------------------
for m = 1:2
    nm = names{m};
    figure('Name', [nm ' - Kontingencna matica'], 'NumberTitle','off');
    confusionchart(Yte, R.(nm).predTest, ...
        'Title', [nm ' - Kontingencna matica (testovacie data)'], ...
        'RowSummary','row-normalized', ...
        'ColumnSummary','column-normalized');
end

%% -------------------------------------------------------
%  8. CPU vs GPU – meranie pre MLP2 
%  -------------------------------------------------------
fprintf('\n=== Tab.13 (cast MLP): CPU vs GPU – MLP2 ===\n');

opts_cpu = trainingOptions('adam', ...
    'MaxEpochs', EPOCHS, 'MiniBatchSize', BATCH_SIZE, ...
    'InitialLearnRate', LEARN_RATE, ...
    'ValidationFrequency', 9999, ...
    'ExecutionEnvironment','cpu', ...
    'Verbose',false, 'Plots','none');

rng(1);
t = tic;
trainNetwork(Xtr, Ytr, layers_MLP2, opts_cpu);
cpu_mlp2 = toc(t);
fprintf('MLP2 CPU: %.1f s\n', cpu_mlp2);

if canUseGPU
    opts_gpu = trainingOptions('adam', ...
        'MaxEpochs', EPOCHS, 'MiniBatchSize', BATCH_SIZE, ...
        'InitialLearnRate', LEARN_RATE, ...
        'ValidationFrequency', 9999, ...
        'ExecutionEnvironment','gpu', ...
        'Verbose',false, 'Plots','none');
    rng(1);
    t = tic;
    trainNetwork(Xtr, Ytr, layers_MLP2, opts_gpu);
    gpu_mlp2 = toc(t);
    fprintf('MLP2 GPU: %.1f s  (zrychlenie: %.1fx)\n', gpu_mlp2, cpu_mlp2/gpu_mlp2);
else
    gpu_mlp2 = NaN;
    fprintf('GPU nie je dostupna.\n');
end

%% -------------------------------------------------------
%  9. VIZUALIZACIA VZORIEK – najlepsia MLP 
%     Pre MLP1 aj MLP2: 1 vzorka z kazdej triedy 0..9
%  -------------------------------------------------------
for m = 1:2
    nm  = names{m};
    net = R.(nm).net;
    figure('Name', [nm ' - Vzorky 0-9'], 'NumberTitle','off');

    for digit = 0:9
        idx_d     = find(test_labels == digit, 1);
        img       = Xte(:,:,:, idx_d);
        predClass = classify(net, img);
        scores    = predict(net, img);

        subplot(2, 5, digit + 1);
        imshow(squeeze(img), [0 1]);
        title(sprintf('Skut.: %d\nPred.: %s\nSkore: %.3f', ...
                       digit, char(predClass), max(scores)), ...
              'FontSize', 8);
    end
    sgtitle([nm ' – Testovanie: 1 vzorka z kazdej triedy (0–9)']);
end

fprintf('\n=== MLP cast dokoncena ===\n');
fprintf('Skontroluj ci MLP2 dosiahol priem. test acc >= 97%%\n');
for m = 1:2
    fprintf('  %s: priem. test acc = %.2f%%\n', names{m}, mean(R.(names{m}).testAcc));
end
