clear
% suradnice x,y,z piatich skupin bodov
load CTGdata

% vstupne a vystupne data na trenovanie neuronovej siete
datainnet=NDATA';
dataoutnet=full(ind2vec(typ_ochorenia'));

% vytvorenie struktury siete
% pocet_neuronov=[10];
pocet_neuronov = [30];
% pocet_neuronov = [20 10];
pocet_behov = 5;

% polia na ukladanie uspesnosti pre vsetky behy (bod 10)
train_accuracies = zeros(1, pocet_behov);
test_accuracies = zeros(1, pocet_behov);
all_accuracies = zeros(1, pocet_behov);

% premenne pre zapamatanie najlepsieho behu
best_acc = 0;
best_net = [];
best_tr = [];
best_test_targets = [];
best_test_outputs = [];
best_train_acc = 0;
best_test_acc = 0;
best_all_acc = 0;

for i = 1:pocet_behov
    net = patternnet(pocet_neuronov);

    % rozdelenie dat
    net.divideFcn='dividerand';
    net.divideParam.trainRatio=0.6;
    net.divideParam.valRatio=0.2;
    net.divideParam.testRatio=0.2;

    % nastavenie parametrov trenovania 
    net.trainParam.goal = 1e-6;       % ukoncovacia podmienka na chybu.
    net.trainParam.epochs = 150;        % maximalny pocet trenovacich epoch.
    net.trainParam.max_fail=50;         % ak sa nezlepsi 50 epoch po sebe tak koncime, aby sme zamedzili pretrenovaniu
    net.trainParam.showWindow = false;   % vypnutie trenovacieho okna nech nevyskakuje
    
    [net, tr] = train(net, datainnet, dataoutnet); % trenovanie siete

    % simulacia na VSETKYCH datach pre dany beh (aby sme ich vedeli rozdelit)
    all_outputs = sim(net, datainnet);

    % uspesnost na trenovacich data
    train_targets = dataoutnet(:, tr.trainInd);
    train_outputs = all_outputs(:, tr.trainInd);
    c_train = confusion(train_targets, train_outputs);
    train_accuracies(i) = 100 * (1 - c_train);

    % pouzitie testovacich dat ktore si siet nahodne vybrala 
    test_targets = dataoutnet(:, tr.testInd);
    test_outputs = all_outputs(:, tr.testInd);
    c_test = confusion(test_targets, test_outputs);
    test_accuracies(i) = 100 * (1 - c_test);

    % uspesnost celkovych dat 
    c_all = confusion(dataoutnet, all_outputs);
    all_accuracies(i) = 100 * (1 - c_all);
    
    % zachytenie najlepsej siete (podla testovacich dat)
    if test_accuracies(i) > best_acc
        best_acc = test_accuracies(i);
        best_net = net;
        best_tr = tr;
        best_test_targets = test_targets;
        best_test_outputs = test_outputs;
        
        best_train_acc = train_accuracies(i);
        best_test_acc = test_accuracies(i);
        best_all_acc = all_accuracies(i);
    end

end
 
% vypis
fprintf('\n=========================================\n');
fprintf('vysledky pre strukturu [%s]:\n', num2str(pocet_neuronov));
fprintf('trenovacie data - min: %.2f %%, max: %.2f %%, priemer: %.2f %%\n', min(train_accuracies), max(train_accuracies), mean(train_accuracies));
fprintf('testovacie data - min: %.2f %%, max: %.2f %%, priemer: %.2f %%\n', min(test_accuracies), max(test_accuracies), mean(test_accuracies));

% vypis najlepsej siete
fprintf('\n--- najlepsia siet z 5 behov ---\n');
fprintf('uspesnost na trenovacich datach: %.2f %%\n', best_train_acc);
fprintf('uspesnost na testovacich datach: %.2f %%\n', best_test_acc);
fprintf('uspesnost na celkovych datach: %.2f %%\n', best_all_acc);

% grafy pre najlepsiu siet
figure('name', 'priebeh ucenia (loss vs. epoch)');
plotperform(best_tr);

figure('name', 'kontingencna matica - testovacie data');
plotconfusion(best_test_targets, best_test_outputs);

% senzitivita a specificita
[~, cm] = confusion(best_test_targets, best_test_outputs);

tp = diag(cm); 
fn = sum(cm, 2) - tp; 
fp = sum(cm, 1)' - tp; 
tn = sum(cm(:)) - (tp + fp + fn); 

senzitivita = tp ./ max((tp + fn), 1); 
specificita = tn ./ max((tn + fp), 1);

fprintf('\n--- metriky pre najlepsiu siet (senzitivita a specificita) ---\n');
triedy_nazvy = {'normalny', 'podozrivy', 'patologicky'};
for k = 1:3
    fprintf('trieda %d (%s):\n', k, triedy_nazvy{k});
    fprintf('  senzitivita (recall): %.2f %%\n', senzitivita(k) * 100);
    fprintf('  specificita:          %.2f %%\n', specificita(k) * 100);
end

% otestovanie 3 vzoriek datasetu
fprintf('\n--- testovanie vybranych vzoriek (bod 11) ---\n');

% najdeme index prvej vzorky pre kazdu z 3 tried v povodnych datach
idx1 = find(typ_ochorenia == 1, 1);
idx2 = find(typ_ochorenia == 2, 1);
idx3 = find(typ_ochorenia == 3, 1);

% vyberieme tieto 3 vzorky z nasej premennej 'datainnet'
vzorky_in = datainnet(:, [idx1, idx2, idx3]);
vzorky_out_real = [1, 2, 3]; % toto su ich skutocne triedy

% pustime ich do nasej najlepsej siete
outnetsimbody = sim(best_net, vzorky_in);
triedy_predikovane = vec2ind(outnetsimbody);

disp('skutocne triedy vzoriek:');
disp(vzorky_out_real);
disp('siet predikovala (surove pravdepodobnosti):');
disp(outnetsimbody);
disp('siet ich zatriedila do tried (vysledok):');
disp(triedy_predikovane);
fprintf('=========================================\n');