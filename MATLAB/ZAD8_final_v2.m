% =========================================================
% Zadanie 8 - FINALNY SKRIPT
% Porovnanie CNN od nuly (from scratch) a transfer learningom (TL)
% Dataset: Food101
% M1: VGG16  |  M2: ResNet18  |  M3: MobileNetV2
% =========================================================
% clear; clc; close all;

%% -------------------------------------------------------
%  1. NACITANIE DATASETU FOOD101 (oficialny kod z UMINT-UNS_data)
%  -------------------------------------------------------
rootDir     = fullfile(pwd, "data2");
archiveFile = fullfile(rootDir, "food-101.tar.gz");
datasetDir  = fullfile(rootDir, "food-101");

if ~isfolder(rootDir), mkdir(rootDir); end

if isfolder(datasetDir)
    disp("Food-101 uz existuje, download sa preskakuje.");
elseif isfile(archiveFile)
    disp("Nasiel sa archiv Food-101, rozbalujem...");
    untar(archiveFile, rootDir);
else
    disp("Food-101 sa nenasiel, stahujem dataset (~5 GB)...");
    url = "https://data.vision.ee.ethz.ch/cvl/food-101.tar.gz";
    websave(archiveFile, url);
    untar(archiveFile, rootDir);
end

% Nacitanie podla oficialneho rozdelenia (train.txt / test.txt)
imagesDir = fullfile(datasetDir, "images");
metaDir   = fullfile(datasetDir, "meta");
trainList = readlines(fullfile(metaDir, "train.txt"));
testList  = readlines(fullfile(metaDir, "test.txt"));
trainList = trainList(strlength(trainList) > 0);
testList  = testList(strlength(testList) > 0);

trainFiles  = fullfile(imagesDir, cellstr(trainList + ".jpg"));
testFiles   = fullfile(imagesDir, cellstr(testList  + ".jpg"));
trainLabels = categorical(extractBefore(trainList, "/"));
testLabels  = categorical(extractBefore(testList,  "/"));

imdsTrain_all = imageDatastore(trainFiles, "Labels", trainLabels);
imdsTest_all  = imageDatastore(testFiles,  "Labels", testLabels);

% Filtrovanie na 10 vybranych tried
keepClasses = ["apple_pie","caesar_salad","clam_chowder","edamame", ...
               "french_fries","hamburger","hot_dog","ice_cream","sushi","waffles"];

idxTrain = ismember(string(imdsTrain_all.Labels), keepClasses);
idxTest  = ismember(string(imdsTest_all.Labels),  keepClasses);

imdsTrain10 = subset(imdsTrain_all, find(idxTrain));
imdsTest10  = subset(imdsTest_all,  find(idxTest));

imdsTrain10.Labels = removecats(imdsTrain10.Labels);
imdsTest10.Labels  = removecats(imdsTest10.Labels);

classes    = categories(imdsTrain10.Labels);
numClasses = numel(classes);

fprintf('=== Zadanie 8: Food101 – 10 tried ===\n');
fprintf('Triedy: %s\n', strjoin(classes, ', '));
fprintf('Train: %d   Test: %d\n', numel(imdsTrain10.Files), numel(imdsTest10.Files));

% Validacna mnozina z trenovacich dat (15 % z kazde triedy)
rng(42);
[imdsTrain_f, imdsVal_f] = splitEachLabel(imdsTrain10, 0.85, 'randomized');
fprintf('Po rozdeleni -> Train: %d  Val: %d  Test: %d\n\n', ...
        numel(imdsTrain_f.Files), numel(imdsVal_f.Files), numel(imdsTest10.Files));

%% -------------------------------------------------------
%  2. HYPERPARAMETRE (rovnake pre vsetky modely)
%  -------------------------------------------------------
EPOCHS     = 15;
BATCH_SIZE = 32;
LEARN_RATE = 0.0001;
N_RUNS     = 3;
IMG_SIZE   = [224 224];

fprintf('Hyperparametre: Epochy=%d, Batch=%d, LR=%.5f\n\n', ...
        EPOCHS, BATCH_SIZE, LEARN_RATE);

% Augmentacia 
augmenter = imageDataAugmenter( ...
    'RandXReflection',  true, ...
    'RandRotation',     [-15 15], ...
    'RandXTranslation', [-20 20], ...
    'RandYTranslation', [-20 20], ...
    'RandXScale',       [0.8 1.2], ...
    'RandYScale',       [0.8 1.2]);

% Resize datastory (bez augmentacie)
imds_tr_r  = augmentedImageDatastore(IMG_SIZE, imdsTrain_f, 'ColorPreprocessing','gray2rgb');
imds_va_r  = augmentedImageDatastore(IMG_SIZE, imdsVal_f,   'ColorPreprocessing','gray2rgb');
imds_te_r  = augmentedImageDatastore(IMG_SIZE, imdsTest10,  'ColorPreprocessing','gray2rgb');

% Resize s augmentaciou
imds_tr_aug = augmentedImageDatastore(IMG_SIZE, imdsTrain_f, ...
    'DataAugmentation', augmenter, 'ColorPreprocessing','gray2rgb');

itersPerEpoch = ceil(numel(imdsTrain_f.Files) / BATCH_SIZE);

%% -------------------------------------------------------
%  3. TRENOVANIE – 3 BEHY x (scratch + TL) x 3 modely
%  -------------------------------------------------------
model_names = {'VGG16', 'ResNet18', 'MobileNetV2'};
arch_ids    = {'vgg16', 'resnet18', 'mobilenetv2'};
modes       = {'scratch', 'tl'};
R           = struct();

for m = 1:3
    arch  = arch_ids{m};
    mname = model_names{m};

    for md = 1:2
        mode  = modes{md};
        field = sprintf('M%d_%s', m, mode);

        fprintf('\n========== M%d (%s) – %s ==========\n', m, mname, upper(mode));

        for r = 1:N_RUNS
            fprintf('  Beh %d/%d ... ', r, N_RUNS);
            rng(r * 77);

            lgraph = build_network(arch, mode, numClasses);

            opts = trainingOptions('adam', ...
                'MaxEpochs',           EPOCHS, ...
                'MiniBatchSize',       BATCH_SIZE, ...
                'InitialLearnRate',    LEARN_RATE, ...
                'ValidationData',      imds_va_r, ...
                'ValidationFrequency', itersPerEpoch, ...
                'Shuffle',            'every-epoch', ...
                'ExecutionEnvironment','auto', ...
                'Verbose',             false, ...
                'Plots',              'none');

            [net, info] = trainNetwork(imds_tr_r, lgraph, opts);

            predTr = classify(net, imds_tr_r, 'MiniBatchSize', 64);
            predVa = classify(net, imds_va_r, 'MiniBatchSize', 64);
            predTe = classify(net, imds_te_r, 'MiniBatchSize', 64);

            R.(field).trainAcc(r) = mean(predTr == imdsTrain_f.Labels) * 100;
            R.(field).valAcc(r)   = mean(predVa == imdsVal_f.Labels)   * 100;
            R.(field).testAcc(r)  = mean(predTe == imdsTest10.Labels)  * 100;
            R.(field).trainLoss(r)= info.TrainingLoss(end);

            vl = info.ValidationLoss(~isnan(info.ValidationLoss));
            R.(field).valLoss(r)  = vl(end);
            R.(field).testLoss(r) = compute_loss(net, imds_te_r, imdsTest10.Labels, numClasses);

            fprintf('Train: %.1f%%  Val: %.1f%%  Test: %.1f%%\n', ...
                    R.(field).trainAcc(r), R.(field).valAcc(r), R.(field).testAcc(r));

            if r == N_RUNS
                R.(field).net      = net;
                R.(field).info     = info;
                R.(field).predTest = predTe;
            end
        end
    end
end

%% -------------------------------------------------------
%  4. VYPIS TABULIEK
%  -------------------------------------------------------
fprintf('\n\n');
fprintf('=== Tab.1: Modely a hyperparametre ===\n');
fprintf('%-6s %-14s %-8s %-10s %-6s\n','Model','Architektura','Epochy','LR','Batch');
for m = 1:3
    fprintf('%-6s %-14s %-8d %-10.5f %-6d\n', ...
            sprintf('M%d',m), model_names{m}, EPOCHS, LEARN_RATE, BATCH_SIZE);
end

tab_num = 1;
for m = 1:3
    for md = 1:2
        tab_num = tab_num + 1;
        mode  = modes{md};
        field = sprintf('M%d_%s', m, mode);
        fprintf('\n=== Tab.%d: M%d (%s) – %s – Vysledky 3 behov ===\n', ...
                tab_num, m, model_names{m}, upper(mode));
        fprintf('%-5s %-12s %-12s %-10s %-10s %-12s %-12s\n', ...
                'Beh','Train loss','Train [%]','Val loss','Val [%]','Test loss','Test [%]');
        for r = 1:N_RUNS
            fprintf('%-5d %-12.4f %-12.2f %-10.4f %-10.2f %-12.4f %-12.2f\n', r, ...
                    R.(field).trainLoss(r), R.(field).trainAcc(r), ...
                    R.(field).valLoss(r),   R.(field).valAcc(r), ...
                    R.(field).testLoss(r),  R.(field).testAcc(r));
        end
    end

    % Suhrn scratch vs TL pre model m
    tab_num = tab_num + 1;
    fs = sprintf('M%d_scratch', m);
    ft = sprintf('M%d_tl',      m);
    fprintf('\n=== Tab.%d: Suhrn scratch vs TL – M%d (%s) ===\n', tab_num, m, model_names{m});
    fprintf('%-10s %-14s %-14s %-12s %-12s %-14s %-14s\n', ...
            'Rezim','Pr.trainLoss','Pr.train[%]','Pr.valLoss','Pr.val[%]','Pr.testLoss','Pr.test[%]');
    for fld = {fs, ft}
        f   = fld{1};
        rz  = strsplit(f,'_'); rz = upper(rz{end});
        fprintf('%-10s %-14.4f %-14.2f %-12.4f %-12.2f %-14.4f %-14.2f\n', rz, ...
                mean(R.(f).trainLoss), mean(R.(f).trainAcc), ...
                mean(R.(f).valLoss),   mean(R.(f).valAcc), ...
                mean(R.(f).testLoss),  mean(R.(f).testAcc));
    end
end

% Tab suhrn scratch vs TL pre vsetky modely
fprintf('\n=== Tab.5: Suhrn vsetkych modelov – FROM SCRATCH ===\n');
fprintf('%-6s %-14s %-16s %-18s %-14s\n','Model','Archit.','Pr.test loss','Pr.test acc [%]','Splnenie 90%');
for m = 1:3
    f = sprintf('M%d_scratch', m);
    ok = 'nie'; if mean(R.(f).testAcc) >= 90, ok = 'ANO'; end
    fprintf('%-6s %-14s %-16.4f %-18.2f %-14s\n', ...
            sprintf('M%d',m), model_names{m}, mean(R.(f).testLoss), mean(R.(f).testAcc), ok);
end

fprintf('\n=== Tab.6: Suhrn vsetkych modelov – TRANSFER LEARNING ===\n');
fprintf('%-6s %-14s %-16s %-18s %-14s\n','Model','Archit.','Pr.test loss','Pr.test acc [%]','Splnenie 93%');
for m = 1:3
    f = sprintf('M%d_tl', m);
    ok = 'nie'; if mean(R.(f).testAcc) >= 93, ok = 'ANO'; end
    fprintf('%-6s %-14s %-16.4f %-18.2f %-14s\n', ...
            sprintf('M%d',m), model_names{m}, mean(R.(f).testLoss), mean(R.(f).testAcc), ok);
end

%% -------------------------------------------------------
%  5. GRAFY – Loss a Accuracy vs Epocha
%  -------------------------------------------------------
for m = 1:3
    mname = model_names{m};
    figure('Name', sprintf('M%d (%s) – Priebeh ucenia', m, mname), 'NumberTitle','off');

    for md = 1:2
        mode  = modes{md};
        field = sprintf('M%d_%s', m, mode);
        info  = R.(field).info;

        [trL, trA] = epoch_avgs(info, itersPerEpoch);
        vl = info.ValidationLoss(~isnan(info.ValidationLoss));
        va = info.ValidationAccuracy(~isnan(info.ValidationAccuracy));
        ep_vl = linspace(1, EPOCHS, length(vl));
        ep_tr = 1:length(trL);

        subplot(2, 2, (md-1)*2 + 1);
        plot(ep_tr, trL, 'b-', 'LineWidth',1.5); hold on;
        plot(ep_vl, vl,  'r--','LineWidth',1.5);
        xlabel('Epocha'); ylabel('Loss');
        title(sprintf('M%d %s – Loss vs Epocha', m, upper(mode)));
        legend('Train loss','Val loss','Location','northeast'); grid on;

        subplot(2, 2, (md-1)*2 + 2);
        plot(ep_tr, trA, 'b-', 'LineWidth',1.5); hold on;
        plot(ep_vl, va,  'r--','LineWidth',1.5);
        xlabel('Epocha'); ylabel('Uspesnost [%]');
        title(sprintf('M%d %s – Accuracy vs Epocha', m, upper(mode)));
        legend('Train acc','Val acc','Location','southeast'); grid on;
    end
    sgtitle(sprintf('M%d (%s) – Scratch vs TL (beh 3)', m, mname), 'FontSize',12);
end

%% -------------------------------------------------------
%  6. AUGMENTACIA – najlepsi TL model
%  -------------------------------------------------------
fprintf('\n\n========== AUGMENTACIA ==========\n');

best_acc = 0; best_m = 1;
for m = 1:3
    f = sprintf('M%d_tl', m);
    if mean(R.(f).testAcc) > best_acc
        best_acc = mean(R.(f).testAcc);
        best_m   = m;
    end
end
fprintf('Najlepsi model: M%d (%s), priem. TL test acc = %.2f%%\n', ...
        best_m, model_names{best_m}, best_acc);

AUG = struct();
for r = 1:N_RUNS
    fprintf('  Beh %d/%d (s augmentaciou) ... ', r, N_RUNS);
    rng(r * 333);

    lgraph = build_network(arch_ids{best_m}, 'tl', numClasses);

    opts_aug = trainingOptions('adam', ...
        'MaxEpochs',           EPOCHS, ...
        'MiniBatchSize',       BATCH_SIZE, ...
        'InitialLearnRate',    LEARN_RATE, ...
        'ValidationData',      imds_va_r, ...
        'ValidationFrequency', itersPerEpoch, ...
        'Shuffle',            'every-epoch', ...
        'ExecutionEnvironment','auto', ...
        'Verbose',             false, ...
        'Plots',              'none');

    [net, info] = trainNetwork(imds_tr_aug, lgraph, opts_aug);

    predVa = classify(net, imds_va_r, 'MiniBatchSize', 64);
    predTe = classify(net, imds_te_r, 'MiniBatchSize', 64);

    vl = info.ValidationLoss(~isnan(info.ValidationLoss));
    AUG.valAcc(r)   = mean(predVa == imdsVal_f.Labels)  * 100;
    AUG.testAcc(r)  = mean(predTe == imdsTest10.Labels) * 100;
    AUG.valLoss(r)  = vl(end);
    AUG.testLoss(r) = compute_loss(net, imds_te_r, imdsTest10.Labels, numClasses);

    fprintf('Val: %.1f%%  Test: %.1f%%\n', AUG.valAcc(r), AUG.testAcc(r));

    if r == N_RUNS
        AUG.net      = net;
        AUG.info     = info;
        AUG.predTest = predTe;
    end
end

% Tab.7
fprintf('\n=== Tab.7: Vysledky 3 behov s augmentaciou – M%d (%s) ===\n', best_m, model_names{best_m});
fprintf('%-5s %-12s %-12s %-12s %-12s\n','Beh','Val loss','Val acc[%]','Test loss','Test acc[%]');
for r = 1:N_RUNS
    fprintf('%-5d %-12.4f %-12.2f %-12.4f %-12.2f\n', r, ...
            AUG.valLoss(r), AUG.valAcc(r), AUG.testLoss(r), AUG.testAcc(r));
end

% Tab.8
ft_best = sprintf('M%d_tl', best_m);
fprintf('\n=== Tab.8: Porovnanie bez a s augmentaciou – M%d (%s) ===\n', best_m, model_names{best_m});
fprintf('%-22s %-12s %-12s %-12s %-12s\n','Varianta','Val loss','Val acc[%]','Test loss','Test acc[%]');
fprintf('%-22s %-12.4f %-12.2f %-12.4f %-12.2f\n', 'Bez augmentacie', ...
        mean(R.(ft_best).valLoss), mean(R.(ft_best).valAcc), ...
        mean(R.(ft_best).testLoss), mean(R.(ft_best).testAcc));
fprintf('%-22s %-12.4f %-12.2f %-12.4f %-12.2f\n', 'S augmentaciou', ...
        mean(AUG.valLoss), mean(AUG.valAcc), mean(AUG.testLoss), mean(AUG.testAcc));

% Graf bez vs s augmentaciou
figure('Name','Augmentacia – porovnanie','NumberTitle','off');
info_no  = R.(ft_best).info;
info_aug = AUG.info;
vl_no  = info_no.ValidationLoss(~isnan(info_no.ValidationLoss));
vl_aug = info_aug.ValidationLoss(~isnan(info_aug.ValidationLoss));
va_no  = info_no.ValidationAccuracy(~isnan(info_no.ValidationAccuracy));
va_aug = info_aug.ValidationAccuracy(~isnan(info_aug.ValidationAccuracy));

subplot(1,2,1);
plot(linspace(1,EPOCHS,length(vl_no)),  vl_no,  'b-',  'LineWidth',1.8); hold on;
plot(linspace(1,EPOCHS,length(vl_aug)), vl_aug, 'r--', 'LineWidth',1.8);
legend('Bez augmentacie','S augmentaciou'); xlabel('Epocha'); ylabel('Val loss');
title(sprintf('M%d (%s) – Val loss', best_m, model_names{best_m})); grid on;

subplot(1,2,2);
plot(linspace(1,EPOCHS,length(va_no)),  va_no,  'b-',  'LineWidth',1.8); hold on;
plot(linspace(1,EPOCHS,length(va_aug)), va_aug, 'r--', 'LineWidth',1.8);
legend('Bez augmentacie','S augmentaciou'); xlabel('Epocha'); ylabel('Uspesnost [%]');
title(sprintf('M%d (%s) – Val accuracy', best_m, model_names{best_m})); grid on;
sgtitle(sprintf('Vplyv augmentacie – M%d (%s)', best_m, model_names{best_m}));

%% -------------------------------------------------------
%  7. VIZUALIZACIA PREDIKCII (6 nahodnych vzoriek)
%     Pre kazdy model, oba rezimy + augmentovany najlepsi
%  -------------------------------------------------------
all_files  = imdsTest10.Files;
all_labels = imdsTest10.Labels;

for m = 1:3
    for md = 1:2
        mode  = modes{md};
        field = sprintf('M%d_%s', m, mode);
        net   = R.(field).net;

        figure('Name', sprintf('M%d %s – Predikcie', m, upper(mode)), 'NumberTitle','off');
        rng(42 + m*10 + md);
        idx_show = randperm(numel(all_files), 6);

        for k = 1:6
            img   = imread(all_files{idx_show(k)});
            img_r = imresize(img, IMG_SIZE);
            if size(img_r,3)==1, img_r = repmat(img_r,[1 1 3]); end

            pred   = classify(net, img_r);
            scores = predict(net, img_r);
            true_c = all_labels(idx_show(k));

            subplot(2, 3, k);
            imshow(img_r);
            clr = 'green'; if pred ~= true_c, clr = 'red'; end
            title(sprintf('Skut: %s\nPred: %s\n%.0f%%', ...
                           char(true_c), char(pred), max(scores)*100), ...
                  'Color', clr, 'FontSize', 7);
        end
        sgtitle(sprintf('M%d (%s) – %s: Predikcie', m, model_names{m}, upper(mode)), 'FontSize',9);
    end
end

% Augmentovany najlepsi model
figure('Name', sprintf('M%d TL+aug – Predikcie', best_m), 'NumberTitle','off');
rng(55);
idx_show = randperm(numel(all_files), 6);
for k = 1:6
    img   = imread(all_files{idx_show(k)});
    img_r = imresize(img, IMG_SIZE);
    if size(img_r,3)==1, img_r = repmat(img_r,[1 1 3]); end
    pred   = classify(AUG.net, img_r);
    scores = predict(AUG.net, img_r);
    true_c = all_labels(idx_show(k));
    subplot(2,3,k); imshow(img_r);
    clr = 'green'; if pred ~= true_c, clr = 'red'; end
    title(sprintf('Skut: %s\nPred: %s\n%.0f%%', char(true_c), char(pred), max(scores)*100), ...
          'Color', clr, 'FontSize', 7);
end
sgtitle(sprintf('M%d (%s) – TL s augmentaciou: Predikcie', best_m, model_names{best_m}));

fprintf('\n=== Zadanie 8 dokoncene ===\n');

%% -------------------------------------------------------
%  LOKALNE FUNKCIE
%  -------------------------------------------------------
function lgraph = build_network(arch, mode, num_classes)
    is_tl = strcmp(mode, 'tl');
    lrf   = 10*is_tl + 1*(~is_tl);

    % 1. Načítanie – s váhami alebo bez
    if is_tl
        switch arch
            case 'vgg16',       net = vgg16;
            case 'resnet18',    net = resnet18;
            case 'mobilenetv2', net = mobilenetv2;
        end
    else
        switch arch
            case 'vgg16',       net = vgg16('Weights','none');
            case 'resnet18',    net = resnet18('Weights','none');
            case 'mobilenetv2', net = mobilenetv2('Weights','none');
        end
    end
    
    if isa(net, 'nnet.cnn.LayerGraph')
        lgraph = net;
    else
        lgraph = layerGraph(net);
    end

    % 2. Zmrazenie extrakčnej časti pri TL
    if is_tl
        layers = lgraph.Layers;
        for i = 1:numel(layers)
            if isprop(layers(i), 'WeightLearnRateFactor')
                frozenLayer = layers(i);
                frozenLayer.WeightLearnRateFactor = 0;
                frozenLayer.BiasLearnRateFactor   = 0;
                lgraph = replaceLayer(lgraph, frozenLayer.Name, frozenLayer);
            end
        end
    end 

    % 3. Nahradenie klasifikačnej časti
    new_fc  = fullyConnectedLayer(num_classes, 'Name', 'fc_out', ...
                'WeightLearnRateFactor', lrf, 'BiasLearnRateFactor', lrf);
    new_sm  = softmaxLayer('Name', 'softmax_out');
    new_out = classificationLayer('Name', 'classif_out');

    switch arch
        case 'vgg16'
            lgraph = replaceLayer(lgraph, 'fc8',    new_fc);
            lgraph = replaceLayer(lgraph, 'prob',   new_sm);
            lgraph = replaceLayer(lgraph, 'output', new_out);
        case 'resnet18'
            lgraph = replaceLayer(lgraph, 'fc1000', new_fc);
            lgraph = replaceLayer(lgraph, 'prob',   new_sm);
            lgraph = replaceLayer(lgraph, 'ClassificationLayer_predictions', new_out);
        case 'mobilenetv2'
            layers = lgraph.Layers;
            n = numel(layers);
            lgraph = replaceLayer(lgraph, layers(n-2).Name, new_fc);
            lgraph = replaceLayer(lgraph, layers(n-1).Name, new_sm);
            lgraph = replaceLayer(lgraph, layers(n).Name,   new_out);
    end
end

function loss = compute_loss(net, imds_r, true_labels, num_classes)
    scores   = predict(net, imds_r, 'MiniBatchSize', 64);
    true_idx = grp2idx(true_labels);
    row_idx  = (1:size(scores,1))';
    probs    = max(scores(sub2ind(size(scores), row_idx, true_idx)), 1e-7);
    loss     = -mean(log(probs));
end

function [loss_ep, acc_ep] = epoch_avgs(info, iters)
    n        = floor(length(info.TrainingLoss) / iters);
    loss_ep  = zeros(1,n);
    acc_ep   = zeros(1,n);
    for e = 1:n
        idx       = (e-1)*iters+1 : e*iters;
        loss_ep(e)= mean(info.TrainingLoss(idx));
        acc_ep(e) = mean(info.TrainingAccuracy(idx));
    end
end