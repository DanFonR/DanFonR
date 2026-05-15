function [Y1, Y2] = saturacao_min_max(X)
    Xhsv = rgb2hsv(X);
    Y1 = Y2 = Xhsv;
    Y1(:,:,2) = 0;
    Y2(:,:,2) = 1;
    Y1 = hsv2rgb(Y1);
    Y2 = hsv2rgb(Y2);
endfunction

function Y = inversao_tonalidade(X)
    Y = rgb2hsv(X);
    Y(:,:, 1) = mod(Y(:,:,1) + 0.5, 1);
    Y = hsv2rgb(Y);
endfunction

function main()
    X = imread('./Desktop/images.jpeg');
    [Ys, YS] = saturacao_min_max(X);
    Y_T = inversao_tonalidade(X);

    figure;

    subplot(2,2,1);
    imshow(X);
    title('Imagem Original');

    subplot(2,2,2);
    imshow(Y_T);
    title('Inversão de Tonalidade');

    subplot(2,2,3);
    imshow(Ys);
    title('Saturação Mínima');

    subplot(2,2,4);
    imshow(YS);
    title('Saturação Máxima');
endfunction