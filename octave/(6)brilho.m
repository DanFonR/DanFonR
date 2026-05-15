function mais_brilho = aumenta_brilho(X)
    mais_brilho = log2(1 + X);
endfunction

function menos_brilho = diminui_brilho(X)
    menos_brilho = 2.^X - 1;
endfunction

function log_repetido = repetir_log(X)
    log_repetido = X;
    contador = 0;

    while mean(log_repetido, 'all') < 0.5
        log_repetido = aumenta_brilho(log_repetido);
        contador += 1;
    endwhile

    fprintf('iteracoes de log: %d\n', contador);
endfunction

function exp_repetido = repetir_exp(X)
    exp_repetido = X;
    contador = 0;

    while mean(exp_repetido, 'all') > 0.5
        exp_repetido = diminui_brilho(exp_repetido);
        contador += 1;
    endwhile

    fprintf('iteracoes de exp: %d\n', contador);
endfunction

function normalizada = intervalo(X)
    if all(0 <= X & X <= 1)
        normalizada = X;
    else
        normalizada = double(X)/255;
    end
endfunction

function main()
    sub1 = intervalo(imread('img_sub1.png'));
    sub2 = intervalo(imread('img_sub2.png'));
    super1 = intervalo(imread('img_super1.png'));
    super2 = intervalo(imread('img_super2.png'));

    figure(1);
    sub1 = aumenta_brilho(sub1);
    imshow(sub1);
    figure(2);
    super1 = diminui_brilho(super1);
    imshow(super1);

    figure(3);
    sub2 = repetir_log(sub2);
    imshow(sub2);
    figure(4);
    super2 = repetir_exp(super2);
    imshow(super2);
endfunction
