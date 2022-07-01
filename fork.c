#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>

// funcao que recebe os argumentos passados e
// quebra o codigo caso a entrada seja invalida
void checkaArg(int argc, char *argv[])
{
  if(argc == 1) {
    printf("\n[!!!] Voce nao enviou nenhum argumento [!!!]\n");
    exit(-2); 
  }
  for(int i=1;i<argc;i++) {
    if(*argv[i] < 48 || *argv[i] > 57) {
      printf("\n[!!!] Argumentos inconsistentes [!!!]\n");
      exit(-3);
    }
  }
}

// recebe o tempo do inicio e o pid do pai de todos
// gera um clock para o fim e verifica se o pid recebido e o mesmo atual
// caso seja, printa o tempo de execucao
void tempo(double inicio, pid_t pid)
{
  clock_t fim;
  fim = clock();
  if(pid == getpid()) printf("Tempo de execucao: %f\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
}

int main (int argc, char *argv[]) {
  pid_t proc, mainproc;
  int estado;
  clock_t inicio;

  checkaArg(argc, argv); // checka os argumentos
  mainproc = getpid(); // pega o pid do pai de todos
  inicio = clock(); // inicia tempo

  for(int i=1;i<argc;i++) { // for com tam = quantidade argumentos
    for(int j=0;j<atoi(argv[i]);j++) { // gera os filhos(folhas da arvore)
      proc = fork();
      if(proc == 0) { // 0 eh filho
        break;
      } else if (proc < 0) {
        printf("[!!!] Falhou em dar fork [!!!] \n");
        exit(-1);
      }
    }
    if (proc > 0) { // > 0 eh pai
      wait(&estado);
      break;
    }
  }
  printf("-> Sou o processo PID: %d | Meu pai tem o PID: %d | terminei! <- \n",getpid(), getppid());

  tempo(inicio, mainproc);
  return 0;
}
