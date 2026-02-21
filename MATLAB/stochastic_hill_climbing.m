function main()

    x_range = -1000:1:1000;
    y_values = testfn3c(x_range');

    plot(x_range, y_values);
    xlabel('X Range');
    ylabel('Y Values');
    title('Graf Schwefelovej funkcie');
    grid on;
    hold on;
    x_min = -1000;
    x_max = 1000;
    d = 4.0;
    max_krokov = 2000;

    best_global_y = 5000;
    best_global_x = 0;
    pocet_pokusov = 30;

    for pokus = 1:pocet_pokusov
        x_curr = rand * (x_max - x_min) + x_min;
        y_curr = testfn3c(x_curr);
        lepsie = true;
        krok_iter = 0;

        while lepsie && (krok_iter < max_krokov)
            krok_iter = krok_iter + 1;

            x_left = max(x_curr - d, x_min);
            x_right = min(x_curr + d, x_max);
            
            y_left = testfn3c(x_left);
            y_right = testfn3c(x_right);
            if y_left < y_curr || y_right < y_curr
                if y_left < y_right
                    x_curr = x_left;
                    y_curr = y_left;
                else
                    x_curr = x_right;
                    y_curr = y_right;
                end
            else
                lepsie = false;
            end
            plot(x_curr, y_curr, '.', Color= 'red');
       
            if y_curr < best_global_y
                best_global_y = y_curr;
                best_global_x = x_curr;
            end
        end
        
    end
    disp(best_global_x);
    disp(best_global_y);
    plot(best_global_x, best_global_y, '.',  'MarkerSize', 20, Color= 'green');
end

% nova schwefelova funckia z dodaneho suboru
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
