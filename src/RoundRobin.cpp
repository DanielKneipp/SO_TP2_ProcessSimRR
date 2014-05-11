/*
 * RoundRobin.cpp
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#include "RoundRobin.h"

RoundRobin::RoundRobin(unsigned const quantum) :
		TrTx_media(0.0), processos(new std::vector<Process>()),
		processos_terminados(new std::vector<Process>()), quantum(quantum) {}

RoundRobin::~RoundRobin() {
	delete [] processos;
	delete [] processos_terminados;
}

void RoundRobin::adicionar_processo(Process &processo) {
	processos->push_back(processo);
}

void RoundRobin::passar_tempo(unsigned* tempo_atual) {
	/* TODO Pegar um processo no estado READY e processa-lo */

	/* TODO Interromper o processo caso o mesmo passe o quantum      */
	/* ou finaliza-lo caso o processamento tenha terminado.           */
	/* Caso for finaliza-lo, e preciso atualizar o tempo atual antes */
	/* para passar para o metodo que finaliza o processo             */

	/* TODO Atualziar a variavel tempo_atual somando o valor do quantum nela         */
	/* caso o processo tenha usado todo_ o tempo determinado pelo quantum ou somente */
	/* o tempo utilizado ate o mesmo ter sido finalizado                             */
}

unsigned RoundRobin::n_processos_executados() {
	return processos_terminados->size();
}

void RoundRobin::atualziar_TrTx() {
	unsigned Tr = 0, Tx = 0;
	unsigned float TrTx = 0.0;

	std::vector<Process>::iterator it;
	for (it = this->processos_terminados->begin(); it != this->processos_terminados->end(); it++) {
		Tx = it->serviceTime;
		Tr = it->finishTime - it->arrivalTime;
		TrTx += Tr/Tx;
	}
	this->TrTx_media = TrTx / this->processos_terminados->size();
}

bool RoundRobin::interromper_processo(Process &processo) {
	if (processo.get_state != RUNNING)
		return false;

	/* TODO Alterar o estado do processo e coloca-lo no final fila de processos */
	processo.set_state(READY);
	this->processos->push_back(processo);

	return true;
}

bool RoundRobin::finalizar_processo(Process &processo, unsigned tempo_atual) {
	if (processo.get_state() == TERMINATED)
		return false;

	/* TODO Alterar o estado do processo para TERMINATED e coloca-lo no vector    */
	/* de processos terminados, atribuindo ao mesmo o momento em que ele terminou */
	processo.set_state(TERMINATED);
	processo.set_finishTime(tempo_atual);
	processos_terminados->push_back(processo);

	return true;
}
