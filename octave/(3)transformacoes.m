function plota_triangulo(v1, v2, v3, fignum)
    figure(fignum);
    plot([v1(1), v2(1), v3(1), v1(1)], [v1(2), v2(2), v3(2), v1(2)]);
    axis([-1 1 -1 1]);
    grid on;
endfunction

function vm = centro(v1, v2, v3)
    vm = (v1 + v2 + v3) / 3;
endfunction

function vy = escala(v, fator)
    M = eye(2) * fator;
    vy = v * M;
endfunction

function vy = transf_em_torno(v, vm, func, param)
    vy = func((v - vm), param) + vm;
endfunction

function vy = rotacao(v, graus)
    M = [cosd(graus) sind(graus); -sind(graus) cosd(graus)];
    vy = v * M;
endfunction

function main()
    v1 = [.1 .2]; v2 = [.3 .2]; v3 = [ .2 .4];
    vm = centro(v1, v2, v3);
    graus = 40;
    fator = 1/2;

    % r = rotacao, r0 = rotacao + ponto medio
    v1r = rotacao(v1, graus); v2r = rotacao(v2, graus); v3r = rotacao(v3, graus);
    v1r0 = rotacao(v1 - vm, graus) + vm;
    v2r0 = rotacao(v2 - vm, graus) + vm;
    v3r0 = rotacao(v3 - vm, graus) + vm;

    % e = escala, e0 = escala + ponto medio
    v1e = escala(v1, fator); v2e = escala(v2, fator); v3e = escala(v3, fator);
    v1e0 = escala(v1 - vm, fator) + vm;
    v2e0 = escala(v2 - vm, fator) + vm;
    v3e0 = escala(v3 - vm, fator) + vm;

    plota_triangulo(v1, v2, v3, 1);
    plota_triangulo(v1r, v2r, v3r, 2);
    plota_triangulo(v1r0, v2r0, v3r0, 3);
    plota_triangulo(v1e, v2e, v3e, 4);
    plota_triangulo(v1e0, v2e0, v3e0, 5);
endfunction
