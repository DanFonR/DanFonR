function borrado = borrar(img, N)
    kernel = ones(N)/N^2;
    borrado = conv2(img, kernel, 'same');
endfunction

function main()
    X1 = double(imread('img1.jpg'))/255;
    X2 = double(imread('img2.jpg'))/255;
    X3 = double(imread('img3.jpg'))/255;

    figure(1);
    imshow(X1);
    figure(2);
    imshow(X2);
    figure(3);
    imshow(X3);

    N_menor = 7;
    N_maior = 20;

    X1b = borrar(X1, N_menor);
    X3b = borrar(X3, N_maior);
    
    figure(4);
    imshow(X1b);
    figure(5);
    imshow(X3b);

    juncao = max(max(X1b, X2), X3b);

    figure(6);
    imshow(juncao);
endfunction
