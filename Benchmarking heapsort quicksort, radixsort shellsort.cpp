#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#define VALIDO 1
#define INVALIDO 0
double PCFreq = 0.0;
__int64 CounterStart = 0;
void particao(int esq, int dir, int *i, int *j, int *A){
 int pivo,tmp;
 *i=esq;
 *j=dir;
 pivo=A[(*i+*j)/2];
 do{
 while(pivo>A[*i])
 (*i)++;
 while(pivo<A[*j])
 (*j)--;
 if(*i<=*j){
 tmp=A[*i];
 A[*i]=A[*j];
 A[*j]=tmp;
 (*i)++;
 (*j)--;
 }
 }while(*i<=*j);
}
void ordena(int esq, int dir, int *A){
 int i,j;
 particao(esq,dir,&i,&j,A);
 if(esq<j)
 ordena(esq,j,A);
 if(i<dir)
 ordena(i,dir,A);
}
void quicksort(int *A , int n){
 ordena(0,n-1,A);

}
void radix(int *vetor, int n) {
 int i;
 int *b;
 int maior = vetor[0];
 int exp = 1;
 b = (int *)calloc(n, sizeof(int));
 for (i = 0; i < n; i++) {
 if (vetor[i] > maior)
 maior = vetor[i];
 }
 while (maior/exp > 0) {
 int bucket[10] = { 0 };
 for (i = 0; i < n; i++)
 bucket[(vetor[i] / exp) % 10]++;
 for (i = 1; i < 10; i++)
 bucket[i] += bucket[i - 1];
 for (i = n - 1; i >= 0; i--)
 b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
 for (i = 0; i < n; i++)
 vetor[i] = b[i];
 exp *= 10;
 }
 free(b);

}
void shell(int *vetor, int n){
 int i;
 int j , aux;
 int gap = 1;
 while(gap < n) {
 gap = 3*gap+1;
 }
 while ( gap > 1) {
 gap /= 3;
 for(i = gap; i < n ; i++) {
 aux = vetor[i];
 j = i;
 while (j >= gap && aux < vetor[j - gap]) {
 vetor[j] = vetor[j - gap];
 j = j - gap;
 }
 vetor [j] = aux;
 }
 }

}
void criaHeap(int *vet, int i, int f){
 int aux = vet[i];
 int j = i * 2 + 1;
 while (j <= f){
 if(j < f){
 if(vet[j] < vet[j + 1]){
 j = j + 1;
 }
 }
 if(aux < vet[j]){
 vet[i] = vet[j];
 i = j;
 j = 2 * i + 1;
 }else{
 j = f + 1;
 }
 }
 vet[i] = aux;
}
void heap(int *vet, int N){

 int i, aux;
 for(i=(N - 1)/2; i >= 0; i--){
 criaHeap(vet, i, N-1);
 }
 for (i = N-1; i >= 1; i--){
 aux = vet[0];
 vet [0] = vet [i];
 vet [i] = aux;
 criaHeap(vet, 0, i - 1);
 }
}
void exibe(int *vet, int N){
int l;
 printf("\n");

 for (l = 0; l < N; l++) {
 printf(" %d", vet[l]);
 }

}
int* geravetor(int N){
int i, j, status;
 int *A;

 A = (int*) malloc(sizeof(int) * N);

srand( (unsigned)time(NULL) );
 for (i = 0; i < N; ++i) {
 do {
 A[i] = rand() % N;
 status = VALIDO;
 for (j = 0; j < i; ++j)
 if (A[i] == A[j])
 status = INVALIDO;
 } while (status == INVALIDO);

 }

 return A;
}
int* geravetorNoventa(int N){
int noventa, dez;
noventa = (N*90)/100;
dez = N - noventa;
int nove = 0;
int i, j, status;
 int *A;

 A = (int*) malloc(sizeof(int) * N);
srand( (unsigned)time(NULL) );

 nove = rand() % N;
 for (i = 0; i < noventa; i++) {
 A[i] = nove;
 status = VALIDO;
 }
 srand(time(NULL));
 for (i = noventa; i < N; ++i) {
 do {
 A[i] = rand() % dez;
 status = VALIDO;
 for (j = noventa; j < i; ++j)
 if (A[i] == A[j])
 status = INVALIDO;
 } while (status == INVALIDO);

 }

 return A;
}
int main(){
 int i, n, op;
clock_t begin;
clock_t end;
double time_spent;
int noventa, dez;

 for(;;){

 printf("\n 1 - Testar entradas com vetores que possuem 90 por cento de elementos iguais e 10 por cento de elementos aleatórios nao repetidos ");
  printf("\n 2 - Testar entradas com vetores que possuem elementos aleatorios nao repetidos");

 printf(" \n\n ESCOLHA UMA OPCAO: ");
 scanf("%d", &op);

 switch (op){

 case 1 :
 {

printf(" ENTRE COM O NUMERO DE ELEMENTOS DO VETOR: ");
scanf("%d", &n);
int *vetNoventa[n];

printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ QUICKSORT ************ \n ");
noventa = (n*90)/100;
dez = n - noventa;
 printf(" \n Noventa por cento do vetor: %d", noventa);
printf(" \n Dez por cento do vetor: %d \n", dez);
//printf(" \n VETOR 90 - 10 GERADO QUICK: ");
vetNoventa[n] = NULL;
vetNoventa[n] = geravetorNoventa(n);

 exibe(vetNoventa[n], n);

 begin = clock();

 quicksort( vetNoventa[n], n);

end = clock();

 exibe(vetNoventa[n], n);

time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("\n\n Tempo VETOR 90 - 10 GERADO QUICKSORT= %f milissegundos \n",
time_spent);



printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ RADIX ************ \n");
//printf(" \n VETOR 90 - 10 GERADO RADIX: ");

vetNoventa[n] = NULL;
vetNoventa[n] = geravetorNoventa(n);


 exibe(vetNoventa[n], n);
 begin = clock();

 radix( vetNoventa[n], n);
end = clock();
 exibe(vetNoventa[n], n);

 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("\n\n Tempo VETOR 90 - 10 GERADO RADIX= %f milissegundos \n", time_spent);


printf("_________________________________________________________________________________________________________________________________________________");
 printf(" \n ************ SHELLSORT ************ \n ");

//printf(" \n VETOR 90 - 10 GERADO SHELL ");

vetNoventa[n] = 0;
 vetNoventa[n] = geravetorNoventa(n);

 exibe(vetNoventa[n], n);
 begin = clock();

 shell( vetNoventa[n], n);
end = clock();

 exibe(vetNoventa[n], n);

 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("\n\n Tempo VETOR 90 - 10 GERADO SHELLSORT= %f milissegundos \n", time_spent);


printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ HEAPSORT************ \n ");
//printf(" \n VETOR 90 - 10 GERADO HEAP: ");

vetNoventa[n] = 0;
 vetNoventa[n] = geravetorNoventa(n);

 exibe(vetNoventa[n], n);
 begin = clock();

 heap( vetNoventa[n], n);
end = clock();
 exibe(vetNoventa[n], n);

 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 
 printf("\n\n Tempo VETOR 90 - 10 GERADO HEAPSORT= %f milissegundos \n",time_spent
);

 break;

}
 case 2 :
 {
 for(;;){
printf(" ENTRE COM O NUMERO DO VETOR: ");
scanf("%d", &n);

 int *vetAleatorio[n];

printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ QUICKSORT ************ \n ");
noventa = (n*90)/100;
dez = n - noventa;
 printf(" \n Noventa por cento do vetor: %d", noventa);
printf(" \n Dez por cento do vetor: %d \n", dez);
//printf(" \n VETOR ALEATÓRIO GERADO QUICK: \n");
 
vetAleatorio[n] = NULL;
vetAleatorio[n] = geravetor(n);

 exibe(vetAleatorio[n], n);
 begin = clock();

 quicksort( vetAleatorio[n], n);
end = clock();
 exibe(vetAleatorio[n], n);

 double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


 printf("\n\n Tempo VETOR ALEATORIO QUICKSORT= %f milissegundos \n", time_spent);



printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ RADIX ************ \n");
 //printf(" \n VETOR ALEATORIO GERADO RADIX: \n ");

 vetAleatorio[n] = 0;
vetAleatorio[n] = geravetor(n);
 exibe(vetAleatorio[n], n);

 begin = clock();

radix( vetAleatorio[n], n) ;
end = clock();
 exibe(vetAleatorio[n], n);

 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("\n\n Tempo VETOR ALEATORIO RADIX = %f milissegundos \n\n", time_spent);


printf("________________________________________________________________________________________________________________________________________________");
 printf(" \n ************ SHELLSORT ************ \n ");


 exibe(vetAleatorio[n], n);
begin = clock();

 shell( vetAleatorio[n], n) ;

end = clock();
 exibe(vetAleatorio[n], n);

 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("\n\n Tempo VETOR ALEATORIO SHELLSORT = %f milissegundos \n ", time_spent);


printf("________________________________________________________________________________________________________________________________________________");
printf(" \n ************ HEAPSORT************ \n ");
//printf(" \n VETOR ALEATORIO GERADO HEAP: \n ");
vetAleatorio[n] = 0;
vetAleatorio[n] = geravetor(n);
 exibe(vetAleatorio[n], n);

begin = clock();
 
heap( vetAleatorio[n], n) ;
end = clock();

 exibe(vetAleatorio[n], n);
 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("\n\n Tempo VETOR ALEATORIO HEAP = %f milissegundos\n",time_spent);
 break;
}
}
}
}
}
