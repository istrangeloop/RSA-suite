#include <gmp.h>
#include "utils.h"

//questão 1
void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
    //a > b
    mpz_t x1, y1, res;
    mpz_init(x1);
    mpz_init(y1);
    mpz_init(res);
    mpz_t mod; 
    mpz_init(mod);
    mpz_t div; 
    mpz_init(div);
    if(mpz_cmp_ui(a, 0) == 0){
        mpz_set(g, b);
        mpz_set_ui(x, 0);
        mpz_set_ui(y, 1);
        return;
    }
    mpz_mod(mod, b, a);
    mpz_div(div, b, a);
    mdc_estendido(g,x1,y1,mod, a);
    mpz_mul(res, div, x1);
    mpz_sub(x, y1, res);
    mpz_set(y, x1);
}

//questão 2
int inverso_modular(mpz_t r, const mpz_t n, const mpz_t a){
    mpz_t g, y;
    mpz_init(g);
    mpz_init(y);
    
    mdc_estendido(g, r, y, a, n); 
    if(mpz_cmp_ui(g, 1) != 0)
        return 0;
    return 1;
}

//questão 3

void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n){
    mpz_t power, modn, e2, rr;
    mpz_init(power); mpz_init(modn); mpz_init(e2); mpz_init(rr);
    mpz_div_ui(e2, e, 2);
    if(mpz_cmp_ui(e, 2) == 0){
        mpz_mul(power, b, b);
        mpz_mod(r, power, n);
    }
    else if (mpz_cmp_ui(e, 1) == 0){
        mpz_mod(r, b, n);
    }
    else if (mpz_even_p(e) == 1){
        exp_binaria(r, b, e2, n);
        mpz_mul(power, r, r);
        mpz_mod(r, power, n);
    }
    else if (mpz_even_p(e) == 0){
        exp_binaria(r, b, e2, n);
        mpz_mul(power, r, r);
        mpz_mod(r, power, n);
        mpz_mul(rr, r, b);
        mpz_mod(r, rr, n);
    }
}

//questão 4
int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q){
    unsigned int x;
    mpz_t exp, m;
    mpz_init(exp); mpz_init(m);
    mpz_set(exp, q);
    for(x = 0; x < t; x++){
        exp_binaria(m, a, exp, n);
        if(x == 0 && mpz_cmp_ui(m, 1) == 0)
            return 1;
        else if(mpz_cmp(n1, m) == 0)
            return 1;
        mpz_mul_ui(exp, exp, 2);
    }
    return 0;
}

//questão 5
int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd){
    unsigned int i, t = 0, log = 0, result;
    mpz_t a, n1, rest; 
    mpz_t q;
    mpz_init(a); mpz_init(n1);
    mpz_init(q); mpz_init(rest);
    mpz_sub_ui(n1, n, 1);
    mpz_set(q, n1);
    do{
        t ++;
        log ++;
        mpz_div_ui(q, q, 2);
    }while(mpz_even_p(q));
    mpz_set(rest, q);
    while(mpz_cmp_ui(rest, 1) > 0){
        mpz_div_ui(rest, rest, 2);
        log++;
    }

    for (i = 0; i < iter; i++){
        mpz_urandomb(a, rnd, log);
        result = talvez_primo(a, n, n1, t, q);
        if(result == 0)
            return 0;
    }
    return 1;
}

//questão 6
void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd){
    mpz_urandomb(r, rnd, b);    
    while(mpz_even_p(r) || provavelmente_primo(r, 20, rnd) == 0)
        mpz_urandomb(r, rnd, b);
}

//questão 7
void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd){
    mpz_t p, q, phi, aux;
    mpz_init(p); mpz_init(q); mpz_init(phi); mpz_init(aux);
    primo_aleatorio(p, 2048, rnd);
    primo_aleatorio(q, 2048, rnd);
    mpz_mul(n, p, q);
    mpz_sub_ui(phi, p, 1);
    mpz_sub_ui(aux, q, 1);
    mpz_mul(phi, phi, aux);
    mpz_set_ui(e, 65537);
    while(inverso_modular(d, phi, e) != 1)
        mpz_add_ui(e, e, 1);
    if(mpz_cmp_ui(d, 0) < 0)
        gera_chaves(n, e, d, rnd);
}

//questão 8
void codifica(mpz_t r, const char *str){
    int i = 0;
    mpz_t ch, partial, pos;
    mpz_init(ch); mpz_init(partial); mpz_init(pos);
    mpz_set_ui(pos, 1);
    mpz_set_ui(r, 0);
    while(str[i] != '\0'){
        mpz_set_ui(ch, str[i]);
        mpz_mul(partial, ch, pos);
        mpz_add(r, r, partial);
        mpz_mul_ui(pos, pos, 256);
        i++;
    }
}

//questão 9
char *decodifica(const mpz_t n){
    char* mensagem;
    int i = 0, int_ch;
    mpz_t partial, pos;
    mpz_init(partial); mpz_init(pos);
    mpz_set_ui(pos, 1);
    mensagem = malloc(MAX * sizeof(char));
    do{
        mpz_div(partial, n, pos);
        mpz_mod_ui(partial, partial, 256);
        int_ch = mpz_get_ui(partial);
        mensagem[i] = (char) int_ch;
        mpz_mul_ui(pos, pos, 256);
        i++;
    }while(int_ch != 0);
    return mensagem;
}

//questão 10
void criptografa(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e){
    exp_binaria(C, M, e, n);
}

//questão 11
void descriptografa(mpz_t M, const mpz_t C, const  mpz_t n, const  mpz_t d){
    exp_binaria(M, C, d, n);
}
