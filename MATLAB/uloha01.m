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
    d = 1.0;
    max_krokov = 2000;
    x_curr = rand * (x_max - x_min) + x_min;
    y_curr = testfn3c(x_curr);
    plot(x_curr, y_curr, '.', Color= 'blue');
    krok_iter = 0;
    nasiel_lepsie = true;

    while nasiel_lepsie && (krok_iter < max_krokov)
        krok_iter = krok_iter + 1;
       
        x_left = x_curr - d;
        x_right = x_curr + d;
        
        x_left = max(x_left, x_min);
        x_right = min(x_right, x_max);
        
        y_left = testfn3c(x_left);
        y_right = testfn3c(x_right);
        
        if y_left < y_curr && y_left < y_right
            x_curr = x_left;
            y_curr = y_left;
            plot(x_curr, y_curr, 'g.', 'MarkerSize', 10);
            
        elseif y_right < y_curr && y_right <= y_left
            x_curr = x_right;
            y_curr = y_right;
            plot(x_curr, y_curr, 'g.', 'MarkerSize', 10);
            
        else
            nasiel_lepsie = false;
        end
     
        if mod(krok_iter, 2) == 0; pause(0.01); end
    end
    plot(x_curr, y_curr, 'g.', 'MarkerSize', 10, color= 'red');
    
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