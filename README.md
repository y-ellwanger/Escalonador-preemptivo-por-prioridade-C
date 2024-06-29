# escalonador-preemptivo-por-prioridade
 Simulador de um escalonador preemptivo por prioridade escrito em C.

 ## Instruções
 As informações dos processos devem ser inseridas no arquivo listaprocessos.txt na seguinte ordem: PID, TEMPO DE CHEGADA, BURST, PRIORIDADE. Sendo separadas por um espaço em branco (" "), bem como cada processo deve ser separado por uma linha em branco("\n"). A prioridade entre processos é definida de maneira decrescente. Ou seja, quanto menor o número informado como parâmetro de prioridade, maior será a prioridade do processo.
 
 ### Exemplo: 
 Para um processo com os seguintes atributos:
 PID = 1
 TEMPO DE CHEGADA = 2
 BURST = 6
 PRIORIDADE = 3
 Deve ser escrito no arquivo: "1 2 6 3".
 O próximo processo na lista deve ser separado deste por um linha em branco.