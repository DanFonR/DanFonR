function Y = parallel_project(X)
    % indices
    idxs = find(any(X, 1:2));
    first_idx = idxs(1);
    last_idx = idxs(end);
    pages = last_idx - (first_idx - 1);

    % atenuacao
    X = X(:,:, first_idx:last_idx) ./ reshape((1:pages).^2, 1, 1, pages);

    % selecao por maior valor (maior valor = menor distancia ate o plano)
    % (menor distancia = primeira interseccao do raio)
    Y = max(X, [], 3);

    % normalizacao
    minY = min(Y, [], 'all');
    maxY = max(Y, [], 'all');
    Y = (Y - minY)/(maxY - minY);
end

function main()
    % carregamento
    load objs3d/cubo3d.mat
    cubo3d = X;
    load objs3d/cilindro3d.mat
    cilindro3d = X;
    load objs3d/helicoide3d.mat
    helicoide3d = X;
    clear X;

    cubo2d = parallel_project(cubo3d);
    cilindro2d = parallel_project(cilindro3d);
    helicoide2d = parallel_project(helicoide3d);

    % correcao gama (imagens inicialmente muito escuras)
    imwrite(cubo2d.^.125, 'cubo.png');
    imwrite(cilindro2d.^.125, 'cilindro.png');
    imwrite(helicoide2d.^.25, 'helicoide.png');

end
