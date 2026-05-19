function angulo = angulo_pendulo(theta0, g, l, t)
    angulo = theta0 * cos(sqrt(g/l) * t);
end

function reta = rasterizar(v0, v1, dimX, dimY)
    reta = zeros(dimY, dimX);
    N = max(abs(v1 - v0));
    k = 0:N;
    if N == 0
        reta(v0(2), v1(1)) = 1;
        return;
    end
    vecs = round((1 - k/N)'*v0 + (k/N)'*v1);
    reta(sub2ind(size(reta), vecs(:,1), vecs(:,2))) = 1;
end

function circulo = desenhar_circulo(centro, R, dimX, dimY)
    circulo = zeros(dimY, dimX);

    for Di = -R:R
        i = centro(1) + Di;
        L = round(sqrt(R^2 - Di^2));

        if i < 1 || i > dimY
            continue;
        end

        j = centro(2) + [-L:L];
        j = j(j >= 1 & j <= dimX);

        circulo(i, j) = 1;
    end
end

function pendulo = tracar_pendulo(pivot, theta0, g, l, tempos, dimX, dimY)
    if size(tempos, 1) ~= 1 || pivot(2) + l > dimY || any([dimX dimY] < 0) || any([dimX dimY] < abs(pivot))
        return;
    end

    pendulo = zeros(dimY, dimX, size(tempos, 2));
    thetas = angulo_pendulo(theta0, g, l, tempos);
    R = .02 * max(dimX, dimY);

    for i = 1:size(tempos, 2)
        centro = round(pivot + l*[cos(thetas(i)) sin(thetas(i))]);
        img = desenhar_circulo(centro, R, dimX, dimY);
        img = img | rasterizar(pivot, centro, dimX, dimY);
        pendulo(:,:, i) = img;
    end
end

function main(angulo_graus, comprimento, qtd_frames, criarGIFs)
    g = 10;
    theta = deg2rad(angulo_graus);
    tempos = linspace(0, 2*pi/sqrt(g/comprimento), qtd_frames);
    dimX = 1000;
    dimY = 1000;

    pivot = [1 500];
    x = tracar_pendulo(pivot, theta, g, comprimento, tempos, dimX, dimY);   

    mkdir "gif_frames";
    cd "gif_frames"
    for i = 1:qtd_frames
        imwrite(x(:,:, i), sprintf("frame%03d.png", i));
    end

    if ~criarGIFs
        cd "..";
        return;
    end

    % depende de ter o FFMPEG
    system("ffmpeg -framerate 30 -i frame%03d.png pendulum.gif");

    if ~isfile("pendulum.gif")
        cd "..";
        return;
    end

    delete "*.png";
    movefile pendulum.gif ..;
    cd "..";
    rmdir "gif_frames";
end

main(30, 100, 100, true);
