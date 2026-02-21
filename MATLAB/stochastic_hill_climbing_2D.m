function main()
    clc; clear; close all;

    x_min = -500; 
    x_max = 500;
    d = 3;
    max_krokov = 1000;
    pocet_pokusov = 150;

    best_global_y = inf;
    best_global_x = [];

    % ===== Vizualizácia funkcie =====
    [X,Y] = meshgrid(-500:20:500, -500:20:500);
    Z = testfn3c([X(:) Y(:)]);
    Z = reshape(Z, size(X));

    figure;
    surf(X,Y,Z,'EdgeColor','none');
    colormap jet;
    hold on;
    title('2D Schwefel funkcia');
    xlabel('x'); ylabel('y'); zlabel('F(x,y)');
    view(45,45);

    % ===== Hill Climbing =====
    for pokus = 1:pocet_pokusov

        x_curr = rand(1,2)*(x_max-x_min)+x_min;
        y_curr = testfn3c(x_curr);

        for krok = 1:max_krokov

            neighbors = [
                x_curr + [ d  0];
                x_curr + [-d  0];
                x_curr + [ 0  d];
                x_curr + [ 0 -d];
            ];

            neighbors = max(min(neighbors,x_max),x_min);

            y_neighbors = testfn3c(neighbors);

            [min_val, idx] = min(y_neighbors);

            if min_val < y_curr
                x_curr = neighbors(idx,:);
                y_curr = min_val;
            else
                break;
            end
        end

        if y_curr < best_global_y
            best_global_y = y_curr;
            best_global_x = x_curr;
        end
    end

    % vykreslenie minima
    plot3(best_global_x(1), best_global_x(2), best_global_y, ...
          'r.','MarkerSize',30);

    disp("Najlepšie riešenie 2D:");
    disp(best_global_x);
    disp(best_global_y);
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
