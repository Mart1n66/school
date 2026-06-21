function main()
    addpath('genetic');
    pop_size = 250;
    max_gen = 800;
    num_runs = 5;
    Amps = 100000 * ones(1,5); 

    space = [zeros(1, 5); 2800000 * ones(1, 5)]; 
    
    penalty_types = {'mrtva', 'stupnovita', 'umerna'};
    
    best_history_all = zeros(3, max_gen);

    for p_idx = 1:length(penalty_types)
        typ_pokuty = penalty_types{p_idx};
        figure('Name', sprintf('Pokuta: %s', typ_pokuty));
        hold on;

        best_run_fitness = inf; % premenne na zaznamenanie najlepsieho behu v ramci jednej pokuty
        best_run_x = [];
        best_run_vynos = 0;
        best_run_violations = [];

        for run = 1:num_runs
            % 1. generovanie pociatocnej populacie
            Pop = genrpop(pop_size, space);

            history = zeros(1, max_gen);

            for gen = 1:max_gen
                
                % a) ohodnotenie populacie
                FitnV = zeros(pop_size, 1);
                for i = 1:pop_size
                    % zavolame tvoju fitness funkciu pre kazdeho jedinca
                    FitnV(i) = eval_invest(Pop(i,:), typ_pokuty);
                end
                
                % zaznam najlepsieho fitness v aktualnej generacii
                [min_fit, min_idx] = min(FitnV);
                history(gen) = min_fit;
                
                % b) GA Operatory - Selekcia, Krizenie, Mutacia
                % Elitizmus: Ulozime si najlepsieho jedinca, aby sa nestratil
                % Neskor ho vlozime spat do novej populacie
                best_guy = Pop(min_idx, :); 

                % 1. Selekcia
                % seltourn vyberie jedincov pre dalsiu generaciu na zaklade turnaja
                WorkPop = seltourn(Pop, FitnV, pop_size); 
                
                % 2. Krizenie
                % crossov vykona krizenie. '2' je typ krizenia (2-bodové)
                % a '0' nahodny vyber dvojic
                WorkPop = crossov(WorkPop, 2, 0); 
                
                % 3. Mutacia
                % mutx zmutuje jedincov v hraniciach definovanych 'space'
                % Pravdepodobnost mutacie nastavime napr. na 0.1
                WorkPop = mutx(WorkPop, 0.1, space);
                WorkPop = muta(WorkPop, 0.075, Amps, space);
                
                % zlozenie novej populacie: Nova populacia nahradza staru
                Pop = WorkPop;
                
                % vratenie elity: Nahradime nahodneho (napr. prveho) jedinca tym najlepsim zo starej gen
                Pop(1, :) = best_guy;
            end
            
            % 3. Vykreslenie krivky do grafu s popiskom do legendy 
            % Format: "Beh X (finalna fitness)"
            legend_str = sprintf('Beh %d (%.2f)', run, history(end));
            plot(history, 'DisplayName', legend_str);
            
            % 4. Ulozenie udajov najlepsieho behu pre dany typ pokuty
            % Explicitne najdeme najlepsieho jedinca z finalnej populacie
            FitnV_final = zeros(pop_size, 1);
            for i = 1:pop_size
                FitnV_final(i) = eval_invest(Pop(i,:), typ_pokuty);
            end
            [final_best_fit, final_best_idx] = min(FitnV_final);
            final_best_x = Pop(final_best_idx, :);
            
            if final_best_fit < best_run_fitness
                best_run_fitness = final_best_fit;
                best_history_all(p_idx, :) = history;
                [~, vynos, violations] = eval_invest(final_best_x, typ_pokuty);
                best_run_x = final_best_x;
                best_run_vynos = vynos;
                best_run_violations = violations;
            end
        end

        % dokoncenie grafu pre aktualnu pokutu
        title(sprintf('Konvergencia - %s pokuta', typ_pokuty));
        xlabel('Generácia');
        ylabel('Fitness');
        legend('show', 'Location', 'best');
        hold off;
        
        % Vypis najlepsieho vysledku do konzoly
        fprintf('--- NAJLEPSÍ BEH PRE: %s POKUTU ---\n', typ_pokuty);
        fprintf('Alokácia x1 az x5: [%s]\n', num2str(best_run_x, '%.2f '));
        fprintf('Finálna Fitness: %.2f\n', best_run_fitness);
        fprintf('Hodnota výnosu: %.2f\n', best_run_vynos);
        fprintf('Porušenia ohraničení g1-g4 (0 = splnené): [%s]\n\n', num2str(best_run_violations, '%.2f '));

    end

    % 5. Finalny porovnavaci graf najlepsich behov
    figure('Name', 'Porovnanie najlepších behov');
    hold on;
    plot(best_history_all(1, :), 'LineWidth', 1.5, 'DisplayName', 'Mŕtva');
    plot(best_history_all(2, :), 'LineWidth', 1.5, 'DisplayName', 'Stupňovitá');
    plot(best_history_all(3, :), 'LineWidth', 1.5, 'DisplayName', 'Úmerná');
    title('Porovnanie metód pokutovania (najlepšie behy)');
    xlabel('Generácia');
    ylabel('Fitness');
    legend('show', 'Location', 'best');
    hold off;

end

function [fitness, vynos, violations] = eval_invest(x, typ_pokuty)
    % x = vektor riesenia [x1, x2, x3, x4, x5]
    % typ_pokuty = string: 'mrtva', 'stupnovita', alebo 'umerna'

    % 1. Vypočet realneho vynosu (to, čo chceme v realite maximalizovat)
    vynos = 0.04*x(1) + 0.07*x(2) + 0.11*x(3) + 0.06*x(4) + 0.05*x(5);
    
    % Prechod na minimalizacnu ulohu pre GA (cim vyssi vynos, tym mensie fitness)
    base_fitness = -vynos;

    % 2. Vypocet ohraniceni (upravene do tvaru g(x) <= 0)
    sum_x = sum(x);
    g = zeros(1, 4);
    
    g(1) = sum_x - 10000000;                % 1) celkova investicia max 10 000 000
    g(2) = x(1) + x(2) - 2500000;           % 2) akcie max 2 500 000
    g(3) = x(5) - x(4);                     % 3) statne dlh. >= uspory (upravene na x5 - x4 <= 0)
    g(4) = x(3) + x(4) - 0.5 * sum_x;       % 4) dlhopisy <= 50% z celkovej investicie

    % 5) Nezapornost x(i) >= 0 nepocitame cez pokutu, ale vyriesime ju 
    % priamo pri generovani populacie a mutaciach (cez Lower Bound = 0)

    % Zistime o kolko boli ohranicenia porusene (zaporne hodnoty ignorujeme, to su splnene)
    porusenia = max(0, g); 
    pocet_poruseni = sum(porusenia > 0);
    violations = porusenia; % Vraciame pre kontrolu vysledku na konci skriptu

    % 3. Zapracovanie pokuty
    pokuta = 0;
    
    if pocet_poruseni > 0
        switch typ_pokuty
            case 'mrtva'
                % MRTVA POKUTA: Obrovská fixná hodnota bez ohľadu na počet porušení.
                % Takze fitness bude okolo -1 000 000. 
                % Pokuta 1e8 s prehladom "zabije" jedinca.
                pokuta = 1e6; % ale to uz by nebola mrtva pokuta ale umerna lebo by mal informaciu o poruseniach 
                
            case 'stupnovita'
                % STUPŇOVITÁ POKUTA: Fixná suma za KAŽDÉ jedno porušené pravidlo.
                fixna_za_kus = 2e6; 
                pokuta = pocet_poruseni * fixna_za_kus;
                
            case 'umerna'
                % UMERNA POKUTA: Suma realnych hodnot prekroceni vynasobena vahou.
                vaha = 100; 
                pokuta = sum(porusenia) * vaha;
                
        end
    end

    % 4. Finalna hodnota fitness, ktoru Toolbox uvidi a bude minimalizovat
    fitness = base_fitness + pokuta;
end