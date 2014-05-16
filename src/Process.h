/*
 * Process.h
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#include <iostream>

#ifndef PROCESS_H_
#define PROCESS_H_

enum states {
	READY,
	RUNNING,
	TERMINATED
};

class Process {
private:
	unsigned id;
	unsigned serviceTime;
	unsigned serviceTime_remaining;
	unsigned arrivalTime;
	unsigned finishTime;
	states state;

public:
	Process(
			const unsigned id, const unsigned serviceTime,
			const unsigned arrivalTime);

	virtual ~Process();

	/*
	 * BRIEF:
	 *     Atualiza o tempo restante para fim da execucao do processo
	 *     subtraindo-o em um intervalo de tempo passado como parametro.
	 *
	 * PARAM:
	 *     unsigned - _time - Valor que sera subtraido do tempo restante atual
	 *
	 * RETURN:
	 *     false - Caso o processo tenha finalizado sua execucao
	 *     true  - Caso contrario.
	 */
	bool update_serviceTime_remaining (unsigned _time);

	/*
	 * BRIEF:
	 *     Modifica o estado do processo para o estado especificado no
	 *     parametro newSate.
	 *
	 * PARAM:
	 *     newState - states - Valor do novo estado, devendo estar entre os
	 *                         valores enumerados no enum states.
	 */
	void set_state (const states newState);

	/*
	 * BRIEF:
	 *     Retorna o estado atual do processo baseado no enum states definido.
	 *
	 * RETURN:
	 *     states - Estado do processo.
	 */
	states get_state ();

	/*
	 * BRIEF:
	 *     Retorna o tempo necessario par o processo terminar sua execucao.
	 *
	 * RETURN:
	 *     unsigned - Tempo de execucao total.
	 */
	unsigned get_serviceTime ();

	/*
	 * BRIEF:
	 *     Retorna o instante de tempo que o processo entrou no estado READY pela
	 *     primeira vez.
	 *
	 * RETURN:
	 *     unsigned - Instante de tempo da chegada do processo ao processador.
	 */
	unsigned get_arrivalTime ();

	/*
	 * BRIEF:
	 *     Retorna o instante de tempo em que o processo terminou sua execucao.
	 *     Caso o mesmo nao tenha terminado, e retornado 0.
	 *
	 * RETURN:
	 *     unsigned - Instante de tempo do termino da execucao do processo.
	 */
	unsigned get_finishTime ();

	/*
	 * BRIEF:
	 *     Atribui a finishTime o tempo em que o processo foi finalizado.
	 *
	 * PARAM:
	 *     time - unsigned - Tempo do termino do processo.
	 */
	void set_finishTime (unsigned time);

	/*
	 * BRIEF:
	 *     Retorna o tempo de execucao necessario para finalizar o processo.
	 *
	 * RETURN:
	 *     unsigned - tempo restante para terminar o processo.
	 */
	unsigned get_serviceTime_remaining ();

    /*
     * BRIEF:
     *     Imprimi na saida padrao, as informacoes do processo.
     */
    virtual void printf_info();
};

#endif /* PROCESS_H_ */
