#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int tempo;
    int pid;
    int burst;
    int prioridade;
    int espera;
    int andamento;
} Processo;


void removerProcesso(Processo* processos[], int index, int tamanho){
    for (int i = index; i < tamanho - 1; i++){
        processos[i] = processos[i + 1];
    }
}

Processo* criarProcesso(int pid, int tempo, int burst, int prioridade){
    Processo* processo = (Processo*)malloc(sizeof(Processo));
    processo->tempo = tempo;
    processo->pid = pid;
    processo->burst = burst;
    processo->prioridade = prioridade;
    processo->espera = 0;
    processo->andamento = 0;
    return processo;
}

int main(){

    Processo* listaProcessos[100];
    Processo* processosCorrendo[100];
    Processo* processosConcluidos[100];
    int listaProcessosTamanho = 0;
    int processosCorrendoTamanho = 0;
    int processosConcluidosTamanho = 0;

    int tempo = 0;
    int executando = 0;
    Processo* processoAtual;


    //pega informacoes do arquivo e passa para o array como um  ponteiro de um struct Processo
    FILE *arq;
    arq = fopen("listaprocessos.txt","r");
    char linha[100];

    int num1,num2,num3,num4;

    while(fgets(linha,100,arq)){
        sscanf(linha, "%d %d %d %d",&num1,&num2,&num3,&num4);
        listaProcessos[listaProcessosTamanho++] = criarProcesso(num1,num2,num3,num4);
    }
    fclose(arq);

    //escalonador preemptivo por prioridade
    while (listaProcessosTamanho != 0 || processosCorrendoTamanho != 0){
        for (int i = 0; i < listaProcessosTamanho; i++){
            if (listaProcessos[i]->tempo == tempo) {
                printf("Processo PID %d adicionado na fila de execucao no tempo %d\n", listaProcessos[i]->pid, tempo);
                processosCorrendo[processosCorrendoTamanho++] = listaProcessos[i];
                removerProcesso(listaProcessos, i, listaProcessosTamanho--);
                i--;
            }
        }

        if (processosCorrendoTamanho > 0) {
            if (executando == 0) {
                processoAtual = processosCorrendo[0];
                executando = 1;
                for (int i = 1; i < processosCorrendoTamanho; i++){
                    if (processosCorrendo[i]->prioridade < processoAtual->prioridade){
                        processoAtual = processosCorrendo[i];
                    }
                }
                printf("Nenhum processo anterior em andamento, processo PID %d foi definido como prioridade\n", processoAtual->pid);
            }
            for (int i = 0; i < processosCorrendoTamanho; i++){
                if (processosCorrendo[i]->prioridade < processoAtual->prioridade){
                    printf("Processo de PID %d foi substituido, burst = %d, tempo restante = %d\n", processoAtual->pid, processoAtual->burst, processoAtual->burst-processoAtual->andamento);
                    processoAtual = processosCorrendo[i];
                    printf("Processo de PID %d iniciado pois possui maior prioridade, burst = %d, prioridade = %d\n", processoAtual->pid, processoAtual->burst, processoAtual->prioridade);
                }
            }
            for (int i = 0; i < processosCorrendoTamanho; i++){
                if (processosCorrendo[i]->pid == processoAtual->pid){
                    processosCorrendo[i]->andamento++;
                    printf("Processo com PID %d executado no tempo %d, tempo restante = %d\n", processosCorrendo[i]->pid, tempo, processosCorrendo[i]->burst - processosCorrendo[i]->andamento);
                    if (processosCorrendo[i]->burst == processosCorrendo[i]->andamento){
                        printf("Processo de PID %d foi concluido no tempo %d\n", processosCorrendo[i]->pid, tempo);
                        processosConcluidos[processosConcluidosTamanho++] = processosCorrendo[i];
                        removerProcesso(processosCorrendo, i, processosCorrendoTamanho--);
                        executando = 0;
                        i--;
                    }
                }
                else{
                    processosCorrendo[i]->espera++;
                }
            }
        }
        else {
            printf("Nenhum processo na fila de execucao no tempo %d\n", tempo);
        }
        tempo++;
    }

    printf("Execucao de todos os processos concluida no tempo %d\n", tempo);
    int tempomedio = 0;
    for (int i = 0; i < processosConcluidosTamanho; i++) {
        tempomedio += processosConcluidos[i]->espera;
        printf("PID: %d   Tempo de espera = %d\n", processosConcluidos[i]->pid, processosConcluidos[i]->espera);
    }
    printf("Tempo medio de espera: %f\n", (float)tempomedio/processosConcluidosTamanho);

    for (int i = 0; i < processosConcluidosTamanho; i++) {
        free(processosConcluidos[i]);
    }

    return 0;
}
