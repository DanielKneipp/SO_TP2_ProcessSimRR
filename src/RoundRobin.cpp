/*
 * RoundRobin.cpp
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#include "RoundRobin.h"

struct info_exec simular_RoundRobin(const unsigned n_iter, const unsigned quantum) {
	RoundRobin RR (quantum);
	struct info_exec info;
    unsigned tempo_corrido = 0, ids = 1;
	srand ((unsigned) time (NULL)); /* Estabelecer semente baseada na hora e data atual */

	for (unsigned i = 0; i < n_iter; i++) {
		/* TODO gerar e adicionar n processos (0 <= n <= 3) */
        unsigned short n_processos = rand() % 4;
        for (unsigned j = 0; j < n_processos; j++) {
            unsigned id = ids++ /*rand() % 65536*/;
			unsigned serviceTime = (rand() % (quantum + 2000)) + 10;
			Process __processo (id, serviceTime, tempo_corrido);
			RR.adicionar_processo(__processo);
		}

		/* TODO Simular uma passada de tempo (tempo variavel) */
		RR.passar_tempo(&tempo_corrido);
	}
	info.n_processos_executados = RR.n_processos_executados();
	info.TrTx_media = RR.get_TrTx_media();
	info.tempo_corrido = tempo_corrido;
	return info;
}

RoundRobin::RoundRobin(unsigned const quantum) :
		processos(new std::vector<Process>()),
		processos_terminados(new std::vector<Process>()),
		TrTx_media(0.0), quantum(quantum) {}

RoundRobin::~RoundRobin() {
	delete processos_terminados;
	delete processos;
}

void RoundRobin::adicionar_processo(Process &processo) {
	processos->push_back(processo);
    std::cout << std::endl << "*** PROCESSO CRIADO ***";
    processo.printf_info();
}

void RoundRobin::passar_tempo(unsigned* tempo_atual) {
	/* TODO caso nao tenha processo pronto, a iteracao e cancelada */
	if (this->processos->size() == 0)
		return;

	/* TODO Pegar um processo no estado READY e processa-lo */
	Process processo (*(this->processos->begin()));
	this->processos->erase(this->processos->begin());
	unsigned cont_tempo = this->executar_processo(processo);

	/* TODO Atualiziar o tempo total de execução e o tempo restante para o        */
	/* termino da execucao do processo, caso o mesmo ja tenha terminado,          */
	/* entao ele e finalizado, ou ocorre a interrupcao do processo caso contrario */
	*tempo_atual += cont_tempo;
	if (!processo.update_serviceTime_remaining(cont_tempo))
		this->finalizar_processo(processo, *tempo_atual);
	else
		this->interromper_processo(processo);
}

float RoundRobin::get_TrTx_media() {
	return this->TrTx_media;
}

unsigned RoundRobin::n_processos_executados() {
	return processos_terminados->size();
}

void RoundRobin::atualziar_TrTx() {
	unsigned Tr = 0, Tx = 0;
	float TrTx = 0.0;

	std::vector<Process>::iterator it;
	for (it = this->processos_terminados->begin(); it != this->processos_terminados->end(); it++) {
		Tx = it->get_serviceTime();
		Tr = it->get_finishTime() - it->get_arrivalTime();
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

    std::cout << std::endl << "*** PROCESSO EM EXECUCAO ***";
    processo.printf_info();

	/* TODO Parar a execucao do programa simulando a execucao do processo */
	cont_tempo = (this->quantum < processo.get_serviceTime_remaining()) ?
			this->quantum : processo.get_serviceTime_remaining();
	usleep(cont_tempo*1000); /* Congelar a execucao do programa por 'cont_tempo' milesegundos (LINUX) */

	return cont_tempo;
}

bool RoundRobin::interromper_processo(Process &processo) {
	Process __processo(processo);
	if (__processo.get_state() != RUNNING)
		return false;

	/* TODO Alterar o estado do processo e coloca-lo no final fila de processos */
	__processo.set_state(READY);

    std::cout << std::endl << "*** PROCESSO INTERROMPIDO ***";
    __processo.printf_info();

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

    std::cout << std::endl << "*** PROCESSO FINALIZADO ***";
    __processo.printf_info();

	processos_terminados->push_back(__processo);

	/* TODO Atualizar valor de Tr/Tx */
	this->atualziar_TrTx();

	return true;
}
