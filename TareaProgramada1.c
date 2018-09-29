//
//  TareaProgramada1.c
//  
//
//

#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>



main(int argc, char* argv[]) {
    
    int         my_rank;       /* rank del proceso     */
    int         p;             /* n?mero de procesos   */
    //int         source;        /* rank de quien env?a  */
    //int         dest;          /* rank del receptor     */
    //int         tag = 0;       /* etiqueta para mensajes */
    //char        message[100];  /* almacenamiemto del mensaje  */
    int         m;      /* almacenamiemto del n?mero  */
    int *matriz;                /* matriz la cual se debe repartir entre los procesos  */
    int *matrizB;                /* matriz la cual se debe repartir entre los procesos  */
    int *vector;                /* vector donde se reciben las filas asignadas de la matriz A  */
    int columns;
    int a,b,c,d;        /*aleatorios*/
    
    void Genera_vector( int    v[], int    m);
    void Imprime_vector( int    v[], int size, int columns);
    
    srand(time(0));
    //MPI_Status  status;        /* return status para receptor  */
    
    /* Inicializa MPI */
    MPI_Init(&argc, &argv);
    
    /* Qui?n soy  */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    /* Cu?ntos somos */
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    if(my_rank == 0){
        printf("Ingrese un numero\n");
        scanf("%d", &m);
        printf("El numero ingresado es: %d\n", m);
        columns = m;
        m = m*m;
        matriz = (int*)malloc(sizeof(int)*m);    /*se pide memoria para matriz*/
        matrizB = (int*)malloc(sizeof(int)*9*columns);    /*se pide memoria para matrizB*/
        
        if(matriz != NULL && matrizB){
            Genera_vector(matriz, m);    /*llena la matriz con numeros aleatorios*/
            a = (int)rand()/(int)(((unsigned)RAND_MAX + 1) / columns);
            printf("El numero a es: %d\n", a);
            
            b = (int)rand()/(int)(((unsigned)RAND_MAX + 1) / columns);
            printf("El numero b es: %d\n", b);
            
            c = (int)rand()/(int)(((unsigned)RAND_MAX + 1) / columns);
            printf("El numero c es: %d\n", c);
            
            d = (int)rand()/(int)(((unsigned)RAND_MAX + 1) / columns);
            printf("El numero d es: %d\n", d);
            Imprime_vector(matriz, m, columns);
        } else{
            exit(1);
        }
    }
    
    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&d, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Bcast(&columns, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    vector = (int*)malloc(sizeof(int)*columns*columns/p);
    
    MPI_Scatter(matriz, columns*columns/p, MPI_INT, vector, columns*columns/p, MPI_INT, 0, MPI_COMM_WORLD );
    
    int i;
    for( i = 0; i < columns*columns/p; i++){
        printf("Proc: %d vector [%d] = %d\n", my_rank, i, vector[i]);
    }
    
    if(my_rank != 0){
        printf("Soy el proceso: %d, a = %d, b = %d, c = %d, d = %d, m = %d\n", my_rank,a,b,c,d, columns);
    }
    
    
    if(my_rank == 0){
        free(matriz);
        free(matrizB);
    }
    free(vector);
    /* Termina de usarse MPI */
    MPI_Finalize();
} /* main */

void Genera_vector(
                   int    v[]        /* out */,
                   int    m          /* in  */)
{
    int    i;
    for (i = 0; i < m; i++){
        v[i]= (int)rand()/(int)(((unsigned)RAND_MAX + 1) / 6);
    }
    
}  /* Genera_vector */

void Imprime_vector(int    v[] /* in */,int    m /* size  */, int columns /*columns*/)
{
    int    i;
    int j = 0;
    for (i = 0; i < m; i++){
        printf("%d,", v[i]);
        j = j + 1;
        if(j == columns){
            j = 0;
            printf("\n");
        }
    }
    
    }  /* Genera_vector */
