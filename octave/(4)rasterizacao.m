function reta = tracar_reta(v0, v1, dimX, dimY)
    if v0 > [dimX dimY] | v1 > [dimX dimY]
        return
    endif

    reta = zeros(dimX, dimY);

    N = max(abs(v1 - v0));
    k = 0:N;

    % transposta para converter de 1x81 para 81x1 para multiplicar por v1 (1x2)
    vecs = round((1 - k/N)'*v0 + (k/N)'*v1);
    % sub2ind para converter de reta(m, n) para reta(indice_linear)
    reta(sub2ind(size(reta), vecs(:,1), vecs(:,2))) = 1;
endfunction

function pgon = poligono(centro, raio, lados, dimX, dimY)
    if raio > min(dimX, dimY) | centro > [dimX dimY] | centro + raio > [dimX dimY]
        return
    endif

    theta = 360/lados;
    M = [cosd(theta) sind(theta); -sind(theta) cosd(theta)];
    v0 = centro + [raio 0];
    pgon = zeros(dimX, dimY);

    for i = 1:lados
        v1 = (v0 - centro)*M + centro;
        pgon |= tracar_reta(v0, v1, dimX, dimY);
        v0 = v1;
    endfor
endfunction
