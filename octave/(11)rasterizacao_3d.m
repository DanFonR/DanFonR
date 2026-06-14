function Y = parallel_project(X)
    gama = .25;

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

    % correcao gama
    Y = Y.^gama;
end

function reta = rasterizar(v0, v1, dims)
    reta = zeros(dims);
    N = max(abs(v1 - v0));
    k = 0:N;

    vecs = round((1 - k/N)'*v0 + (k/N)'*v1);
    reta(sub2ind(size(reta), vecs(:,1), vecs(:,2), vecs(:,3))) = 1;
end

function triangulo = triangulo3d(A, B, C, dims)
    triangulo = rasterizar(A, B, dims);
    triangulo = max(triangulo, rasterizar(B, C, dims));
    triangulo = max(triangulo, rasterizar(A, C, dims));
end

function main()
    dims = [1000 1000 100];

    for i=1:3
        A = [randi(1000, 1, 2) [randi(100)]];
        B = [randi(1000, 1, 2) [randi(100)]];
        C = [randi(1000, 1, 2) [randi(100)]];

        AB = rasterizar(A, B, dims);
        AB_proj = parallel_project(AB);

        tri = triangulo3d(A, B, C, dims);
        tri_proj = parallel_project(tri);

        imwrite(AB_proj, sprintf('test_line-%02d.png', i));
        imwrite(tri_proj, sprintf('test_tri-%02d.png', i));
    end
end

main();
