function main()
   addpath('genetic');
   B = [0, 0; 17, 100; 51, 15; 70, 62; 42, 25; 32, 17; 51, 64; 39, 45; 68, 89; 20, 19; 12, 87; 80, 37; 35, 82; 2, 15; 38, 95; 33, 50; 85, 52; 97, 27; 99, 10; 37, 67; 20, 82; 49, 0; 62, 14; 7, 60; 0, 0];
  
   pop_size = 300;       
   chrom_length = 23;    
   max_gen = 900;        
   pocet_behov = 10;     
   
   % matice na ukladanie
   konecne_vysledky = zeros(pocet_behov, 1);
   najlepsie_trasy = zeros(pocet_behov, chrom_length); 
   historia_fitness = zeros(pocet_behov, max_gen);
   
   for beh = 1:pocet_behov
       populacia = zeros(pop_size, chrom_length);
       for i = 1:pop_size
           populacia(i, :) = randperm(chrom_length) + 1;
       end
        
       historia_behu = zeros(1, max_gen); % zaznam pre jeden beh
       
       for gen = 1:max_gen
            
           fit = zeros(pop_size, 1);
           for i = 1:pop_size
               fit(i) = tsp_fitness(populacia(i, :), B);
           end
            
           [naj_fit, naj_idx] = min(fit);
           najlepsi_jedinec = populacia(naj_idx, :);
           
           historia_behu(gen) = naj_fit; % ulozime si fitness aktualnej generacie
           
           rodicia = selsus(populacia, fit, pop_size); % vybera jedincov populacie na zaklade ich fitness cez ruletu 
           
           deti = invord(rodicia, 0.8); % invertuje poradie useku trasy 
          
           deti(1, :) = najlepsi_jedinec;
           
           populacia = deti;
       end
        
       konecne_vysledky(beh) = naj_fit; 
       najlepsie_trasy(beh, :) = najlepsi_jedinec; % ulozime si vitaznu trasu
       historia_fitness(beh, :) = historia_behu;   % ulozime si priebeh generacii
       
       disp(['Beh ', num2str(beh), ' skoncil s trasou: ', num2str(konecne_vysledky(beh))]);
   end
   
   uspesne_behy = sum(konecne_vysledky <= 480);
   disp('---------------------------------------------------');   
   disp(['Pocet uspesnych behov: ', num2str(uspesne_behy), ' z 10']);

   % graf 1 body v rovine

   [absolutne_naj_fit, naj_beh_idx] = min(konecne_vysledky);
   naj_genom = najlepsie_trasy(naj_beh_idx, :); % Vyberieme vitazne poradie
   
   % spojime to do jednej trasy (Start v bode 1 -> Genom -> Ciel v bode 1)
   kompletna_trasa = [1, naj_genom, 1]; 
   body_trasy = B(kompletna_trasa, :); % Zoradene suradnice
 
   figure('Name', 'Najkratsia spojnica 25 bodov v rovine');
   % parameter '-o' zabezpeci, ze body su spojene ciarou
   plot(body_trasy(:,1), body_trasy(:,2), '-o', 'LineWidth', 1.5, 'MarkerFaceColor', 'r', 'Color', 'b');
   hold on;
   plot(B(1,1), B(1,2), 'gs', 'MarkerSize', 10, 'MarkerFaceColor', 'g'); % zeleny Start/Ciel
   
   % pridame cisla bodov pre lepsiu orientaciu
   for i = 1:size(B, 1)-1
       text(B(i, 1)+1.5, B(i, 2)+1.5, num2str(i), 'FontSize', 8, 'FontWeight', 'bold');
   end
   
   title(['Najlepsia najdena trasa (Vzdialenost: ', num2str(absolutne_naj_fit), ')']);
   xlabel('X'); ylabel('Y');
   grid on; hold off;

   % graf 2 konvergencia

   figure('Name', 'Priebeh fitness v zavislosti od generacii');
   hold on;
   for beh = 1:pocet_behov
       behy = plot(1:max_gen, historia_fitness(beh, :), 'Color', [0.7 0.7 0.7]); % sive ciary (vsetky behy)
   end
   % priemerna krivka konvergencie (modra)
   farba_priemer = plot(1:max_gen, mean(historia_fitness), 'b', 'LineWidth', 2);
   % najlepsi beh (cervena)
   farba_najlepsi = plot(1:max_gen, historia_fitness(naj_beh_idx, :), 'r', 'LineWidth', 1.5);
   
   title('Konvergencia GA (10 behov)');
   xlabel('Generacia'); ylabel('Fitness (Dlzka trasy)');
   legend([behy, farba_priemer, farba_najlepsi],'Behy GA', 'Priemerna krivka', 'Najlepsi beh');
   grid on; hold off;

   disp('===================================================');
   disp(['ABSOLUTNE NAJKRATSIA TRASA: ', num2str(absolutne_naj_fit)]);
   disp('Najlepsi genom (poradie prejazdu bodov 2 az 24):');
   disp(naj_genom);

end

function f = tsp_fitness(chromozom, B)
    trasa = [1, chromozom, 1];
    f = 0;
    for i = 1:(length(trasa)-1)
        p1 = B(trasa(i), :);
        p2 = B(trasa(i+1), :);
        f = f + sqrt(sum((p1 - p2).^2)); 
    end
end