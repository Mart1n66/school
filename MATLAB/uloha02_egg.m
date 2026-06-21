function main()
    addpath('genetic');

    n = 10; % pocet premennych 
    popsize = 700; % velkost populacie
    maxgen = 5000; % max pocet gen (teda aj cyklov foru)
    mut_rate = 0.05; % pravdepodobnost mutacie 
    elite_count = 4; % kolko najlepsich jedincov prezije bez zmeny (elitarizmus)
    Space = [-512 * ones(1, n); 
              512 * ones(1, n)];
    
    Oldpop = genrpop(popsize, Space);
    
    best_history = zeros(1, maxgen);
    
    for gen = 1:maxgen

        Fvpop = eggholder(Oldpop); % funckne hodnoty
        best_history(gen) = min(Fvpop); % vyber minima

        [Elite, EliteFit] = selbest(Oldpop, Fvpop, [1 1 1 1]); % vyberieme 4 najlepsie kopie najlepsieho jedinca selekcia 

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

    Fvpop = eggholder(Oldpop);
    [final_best_fit, idx] = min(Fvpop); % Najde hodnotu a index najlepsieho jedinca
    best_X = Oldpop(idx, :);            % zapise suradnice x1 az x10

    disp(final_best_fit);
    disp(best_X); % vypis

end

function[Fit]=eggholder(Pop)


[lpop,lstring]=size(Pop);

for i=1:lpop
  G=Pop(i,:);
  Fit(i)=0;
  for j=1:(lstring-1)
    Fit(i)=Fit(i)-G(j)*sin(sqrt(abs(G(j)-(G(j+1)+47))))-(G(j+1)+47)*sin(sqrt(abs(G(j+1)+47+G(j)/2)));
  end;  
end;
end