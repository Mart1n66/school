function main()
    addpath('genetic');

    n = 100; % pocet premennych 
    popsize = 500; % velkost populacie
    maxgen = 10000; % max pocet gen (teda aj cyklov foru)
    mut_rate = 0.05; % pravdepodobnost mutacie
    elite_count = 6; % kolko najlepsich jedincov prezije bez zmeny (elitarizmus)
    Space = [-1000 * ones(1, n); 
              1000 * ones(1, n)];
    
    Oldpop = genrpop(popsize, Space);

    best_history = zeros(1, maxgen);

    for gen = 1:maxgen

        Fvpop = testfn3c(Oldpop); % funckne hodnoty
        best_history(gen) = min(Fvpop); % vyber minima

        [Elite, EliteFit] = selbest(Oldpop, Fvpop, ones(1, elite_count)); % vyberieme x najlepsie kopie najlepsieho jedinca selekcia 

        Selected = seltourn(Oldpop, Fvpop, popsize - elite_count); % selekcia zvysku populacie turnajom
        
        Crossed = crossov(Selected, 2, 0); % krizenie (viacbodove)

        Mutated = mutx(Crossed, mut_rate, Space); % mutacia mutx-globalna, muta-lokalna    

        Oldpop = [Elite; Mutated];

        if mod(gen, 20) == 0
            fprintf('Generácia %d: Best Fitness = %.4f\n', gen, best_history(gen));
        end

    end
    plot(best_history);
    title('Priebeh');
    grid on;
    hold on;

    Fvpop = testfn3c(Oldpop);
    [final_best_fit, idx] = min(Fvpop); % Najde hodnotu a index najlepsieho jedinca
    best_X = Oldpop(idx, :);            % zapise suradnice x1 az x100

    disp(final_best_fit);
    disp(best_X); % Vypis
    
end

function[Fit]=testfn3c(Pop)

    x0=30;  
    y0=100; 

    [lpop,lstring]=size(Pop);
    Fit=zeros(1,lpop);

    for i=1:lpop
        x=Pop(i,:);
        Fit(i)=0;	
        for j=1:lstring
            Fit(i)=Fit(i)-(x(j)-x0)*sin(sqrt(abs((x(j)-x0))))+y0;
        end   
    end
end