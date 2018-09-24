#ifndef _UTILS_H
#define _UTILS_H
#define MAX 1024
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

//questão 1
void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b);

//questão 2
int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n);

//questão 3
void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n);

//quetão 4
int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q);

//questão 5
int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd);

//questão 6
void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd);

//questão 7
void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd);

//questão 8
void codifica(mpz_t r, const char *str);

//questão 9
char *decodifica(const mpz_t n);

//questão 10
void criptografa(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e);

//questão 11
void descriptografa(mpz_t M, const mpz_t C,const  mpz_t n,const  mpz_t d);

#endif
