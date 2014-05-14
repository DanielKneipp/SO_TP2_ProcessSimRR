/*
 * RoundRobin.h
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#ifndef ROUNDROBIN_H_
#define ROUNDROBIN_H_

#include <vector>
#include <time.h>     /* srand() */
#include <unistd.h>   /* usleep (LINUX) */
#include <stdlib.h>   /* rand() */
#include "Process.h"

struct info_exec {
	unsigned n_processos_executados;
	float TrTx_media;
	unsigned tempo_corrido;
};

/*
 * BRIEF:
 *     Simula a execucao de um escalonador do tipo Round Robin, gerando de
 *     0 a 3 processos por iteracao com tempo de execucao variando de 10 a (quantum + 2000)
 *
 * PARAM:
 *     n_iter - const unsigned - numero que iteraceos que serao executadas,
 *                               neste cso, esse valor equivale a numero de vezes
 *                               que havera uma troca de um processo que esta
 *                               sendo executado por outro.
 *
 * RETURN:
 *     struct info_exec - Estrutura contendo numero de processos executados e
 *                       Tr/Tx medio.
 */
struct info_exec simular_RoundRobin(const unsigned n_iter, const unsigned quantum);

class RoundRobin {
private:
	std::vector<Process>* processos;
	std::vector<Process>* processos_terminados;
	float TrTx_media;
	unsigned const quantum;

	/*
	 * BRIEF:
	 *     Finaliza um processo, alterando seu estado para TERMINATED,
	 *     o colocando no vector de processos terminados e atuliza
	 *     a variavel TrTx_media com o novo valor.
	 *
	 * PARAM:
	 *     processo    - Process  - Processo que sera terminado
	 * PARAM:
	 *     tempo_atual - unsigned - momento da iteracao atual
	 *
	 * RETURN:
	 *     false - Caso o estado atual do processo ja seja TERMINATED
	 *             (e nada mais e feito)
	 *     true  - Caso contrario
	 */
	bool finalizar_processo(Process &processo, unsigned tempo_atual);

	/*
	 * BRIEF:
	 *     Interrompe a execucao do processo passado como parametro,
	 *     alterando o estado dele de RUNNING para READY,ja que o mesmo
	 *     retorna para a fila de processos prontos instataneamete.
	 *
	 * PARAM:
	 *     processo - Process - Processo que sera interrompido
	 *
	 * RETURN:
	 *     false - Caso o estado atual do processo não seja RUNNING
	 *             (e nada mais e feito)
	 *     true  - Caso contrario
	 */
	bool interromper_processo(Process &processo);

	/*
	 * BRIEF:
	 *     Simula a execucao do processo, tirando o processo da fila
	 *     de processos prontos, alterando seu estado de READY para RUNING e
	 *     interrompendo a simulacao por  um intervalo de tempo (0 < t <= quantum).
	 *     Caso o mesmo tenha terminado sua execucao dentro do quantum, o mesmo
	 *     e finalizado, caso contrario ele e interrompido.
	 *
	 *
	 * PARAM:
	 *     processo - Process - Processo a ser executado.
	 *
	 * RETURN:
	 *     0             - unsigned - Caso o processo nao esteja no estado READY.
	 *     tempo_corrido - unsigned - Caso contrario, se retorna o tempo que se
	 *                                passou do inicio ao fim da execucao do processo
	 *                                (0 < t <= quantum).
	 */
	unsigned executar_processo(Process &processo);

	/*
	 * BRIEF:
	 *     Atualzia o valor de TrTx (Tempo de Turnaround / Tempo de execucao)
	 *     utilizando o vector de processos terminados
	 */
	void atualziar_TrTx();

public:
	RoundRobin(unsigned const quantum);

	virtual ~RoundRobin();

	/*
	 * BRIEF:
	 *     Adiciona um novo processo a fila de execucao
	 *
	 * PARAM:
	 *     processo - Process - Novo processo a ser adicionado
	 */
	void adicionar_processo(Process &processo);

	/*
	 * BRIEF:
	 *     Funcao que simula a passada de um intervalo de tempo (0 <= t <= quantum),
	 *     executando algum processo e finalizando-o caso memso tenha terminado.
	 *
	 * PARAM:
	 *     tempo_atual - unsigned* - ponteiro paramomento da iteracao atual. Deve ser
	 *                               maior que o tempo passado em um iteracao
	 *                               anterior
	 */
	void passar_tempo(unsigned* tempo_atual);

	/*
	 * BRIEF:
	 *     Retorna o numero de processos já executadas na simulacao.
	 *
	 * RETURN:
	 *     unsigned - Numero de processos em estado TERMINATED
	 */
	unsigned n_processos_executados();

	/*
	 * BRIEF:
	 *     Retorna o valor da media de Tr/Tx (tempo de Turnaround / Tempo de execucao)
	 *     de todos os processos executados.
	 *
	 * RETURN:
	 *     float - >edia dos Tr/Tx de todos os processos.
	 */
	float get_TrTx_media();
};

#endif /* ROUNDROBIN_H_ */
