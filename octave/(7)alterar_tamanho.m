function w = tri_mask(fact)
    w = (-abs([1:2*fact - 1] - fact) + fact) / fact;
endfunction

function Y = scale_img(X, h_rat, w_rat)
    [w_exp_fact, w_com_fact] = rat(w_rat);
    [h_exp_fact, h_com_fact] = rat(h_rat);
    [img_h, img_w] = size(X);

    w_exp_mask = tri_mask(w_exp_fact);
    w_com_mask = tri_mask(w_com_fact);
    w_com_mask = w_com_mask / sum(w_com_mask);
    h_exp_mask = tri_mask(h_exp_fact);
    h_com_mask = tri_mask(h_com_fact);
    h_com_mask = h_com_mask / sum(h_com_mask);

    % combinacao das mascaras de expansao e compressao
    w_mask = conv(w_exp_mask, w_com_mask);
    h_mask = conv(h_exp_mask, h_com_mask)'; % transposta para aplicar a cada coluna

    % expansoes de largura (h) e comprimento (w)
    Y = zeros(img_h + (img_h - 1)*(h_exp_fact - 1), img_w + (img_w - 1)*(w_exp_fact - 1));
    Y(1:h_exp_fact:end, 1:w_exp_fact:end) = X;
    [Y_h, Y_w] = size(Y);

    Y = conv2(Y, w_mask, 'same');
    Y = conv2(Y, h_mask, 'same');

    % compressao para tamanho alvo
    Y = Y(1:h_com_fact:end, 1:w_com_fact:end);
endfunction

function main()
    X = phantom();
    width_ratio = randi(10) + (randi(6) - 1) / 10;
    height_ratio = randi(10) + (randi(6) - 1) / 10;

    tic;
    Y = scale_img(X, height_ratio, width_ratio);
    scale_time = toc;

    subplot(1, 2, 1)
    imshow(X);

    subplot(1, 2, 2)
    imshow(Y);

    fprintf('%fs para gerar imagem ' ...
          + '(fator de largura %.1f, fator de comprimento %.1f)\n', ...
          scale_time, width_ratio, height_ratio ...
    );
endfunction
