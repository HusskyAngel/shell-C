#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include "aux.h"

#define MAX 100

Array process;

int lastElement(char ** arr){
    int count=0;
    while(1){
        if(arr[count]==NULL)
            return count;
        count++;
    }
}

char ** returnArr(char ** arr){

    char **cadena  = arr; 
    cadena[lastElement(arr)-1]= NULL;
    
    return cadena;    
}




int main(int argc, char* argv[]) {
  char **vector_cadenas;
  char cadena[MAX];

  while (1) {
      pid_t pid;
      printf("> ");
      leer_de_teclado(MAX, cadena);
      vector_cadenas = de_cadena_a_vector(cadena);
      if (strcmp("salir",vector_cadenas[0]) == 0) break;
      int arethere=0;
      if( strcmp("&",vector_cadenas[lastElement(vector_cadenas)-1])==0 ){
          arethere=1;
      }
      pid = fork();
      assert(pid >= 0);
      if( strcmp("&",vector_cadenas[lastElement(vector_cadenas)-1])==0  && pid==0){
          //printf("Proceso: %d", getpid());
          execvp(vector_cadenas[0], returnArr(vector_cadenas));
          
      } else if (pid == 0) {
             execvp(vector_cadenas[0], vector_cadenas);
       
      }else if (arethere == 1 && pid>0){
          insertArray(&process, pid); 
          continue;   
        
      }
      else {
            if (strcmp("tareas",vector_cadenas[0])==0){
            int num_process=process.used;
            
             for (int x=0; x< num_process; x++){
               printf("%d\n”",process.array[x]);
                }
            }else if(strcmp("detener",vector_cadenas[0])==0){
               
               execvp(vector_cadenas, returnArr(vector_cadenas));
            }
          wait(NULL);
      }
  }
  printf("Gracias por usar mi dummy shell ;-)\n");

  return 0;
}
