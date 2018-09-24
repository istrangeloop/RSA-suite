#include"utils.h"

int main(){
   
    mpz_t n, e, d, int_msg, int_cpt;
    mpz_init(e);
    mpz_init(n);
    mpz_init(d);
    mpz_init(int_msg);
    mpz_init(int_cpt);

    gmp_randstate_t rnd;
    gmp_randinit_default(rnd);
    gmp_randseed_ui(rnd, 112);
    
    char* msg;
    msg = malloc(MAX*sizeof(char));
    char sel;

    printf("--------Menu--------\n");
    printf("(G)erar novas chaves\n");
    printf("(C)riptografar\n");
    printf("(D)escriptografar\n");
    printf("--------------------\n");
    printf(">");
    sel = getc(stdin);

    switch(sel){
        case('G'):
            gera_chaves(n, e, d, rnd);
            gmp_printf("--chave pública--\n n=%Zd\ne=%Zd\n", n, e);
            gmp_printf("--chave privada--\n n=%Zd\nd=%Zd\n", n, d);
            return 0;
        case('C'):
            getchar();
            printf("Insira a mensagem\n>");
            fgets(msg, MAX, stdin);
            printf("Insira o número N da chave pública\n>");
            gmp_scanf("%Zd", n);
            printf("Insira o expoente e\n>");
            gmp_scanf("%Zd", e);
            codifica(int_msg, msg);
            criptografa(int_cpt, int_msg, n, e);
            printf("Mensagem encriptada:\n");
            gmp_printf("%Zd\n", int_cpt);
            return 0;
        case('D'):
            getchar();
            printf("Insira a mensagem\n>");
            gmp_scanf("%Zd", int_cpt);
            //fgets(msg, MAX, stdin);
            printf("Insira o número N da chave pública\n>");
            gmp_scanf("%Zd", n);
            printf("Insira o expoente d\n>");
            gmp_scanf("%Zd", d);
            //codifica(int_msg, msg);
            descriptografa(int_msg, int_cpt, n, d);
            printf("Mensagem original:\n");
            printf("%s\n", decodifica(int_msg));
            return 0;
    }
    
    return 0;
}
