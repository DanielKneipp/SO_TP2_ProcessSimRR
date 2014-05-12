/*
 * RoundRobin.cpp
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#include "RoundRobin.h"

struct info_exec simular_RoundRobin(const unsigned n_iter, unsigned const quantum) {

}

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
	Process processo (this->processos->begin());
	this->processos->erase(this->processos->begin());
	unsigned cont_tempo = this->executar_processo(processo);

	/* TODO Atualiziar o tempo total de execução e o tempo restante para o         */
	/* termino da execucao do processo, caso o mesmo ja tenha terminado,          */
	/* entao ele e finalizado, ou ocorre a interrupcao do processo caso contrario */
	*tempo_atual += cont_tempo;
	if (!processo.update_serviceTime_remaining(cont_tempo))
		this->finalizar_processo(processo, *tempo_atual);
	else
		this->interromper_processo(processo);
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

unsigned RoundRobin::executar_processo(Process &processo) {
	unsigned cont_tempo = 0;

	/* TODO Mudar seu estado caso o mesmo esteja em estado READY */
	if (processo.get_state() != READY)
		return 0;
	processo.set_state(RUNNING);

	/* TODO Parar a execucao do programa simulando a execucao do processo */
	cont_tempo = (this->quantum < processo.get_serviceTime_remaining()) ? this->quantum : processo.get_serviceTime_remaining();
	usleep(cont_tempo); /* Congelar a execucao do programa por 'cont_tempo' milesegundos (LINUX) */

	return cont_tempo;
}

bool RoundRobin::interromper_processo(Process &processo) {
	Process __processo(processo);
	if (__processo.get_state != RUNNING)
		return false;

	/* TODO Alterar o estado do processo e coloca-lo no final fila de processos */
	__processo.set_state(READY);
	this->processos->push_back(__processo);

	return true;
}

bool RoundRobin::finalizar_processo(Process &processo, unsigned tempo_atual) {
	Process __processo(processo);
	if (__processo.get_state() == TERMINATED)
		return false;

	/* TODO Alterar o estado do processo para TERMINATED e coloca-lo no vector    */
	/* de processos terminados, atribuindo ao mesmo o momento em que ele terminou */
	__processo.set_state(TERMINATED);
	__processo.set_finishTime(tempo_atual);
	processos_terminados->push_back(__processo);

	return true;
}
