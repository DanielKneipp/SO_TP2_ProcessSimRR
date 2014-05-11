/*
 * Process.h
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#ifndef PROCESS_H_
#define PROCESS_H_

enum states {
	READY,
	RUNNING,
	TERMINATED
};

class Process {
private:
	const unsigned id;
	const unsigned serviceTime;
	unsigned serviceTime_remaining;
	const unsigned arrivalTime;
	unsigned finishTime;
	states state;

public:
	Process(
			const unsigned id, const unsigned serviceTime,
			const unsigned arrivalTime, );

	virtual ~Process();

	/*
	 * BRIEF:
	 *     Atualiza o tempo restante para fim da execucao do processo
	 *     em um intervalo de tempo.
	 *
	 * RETURN:
	 *     false - Caso o processo tenha finalizado sua execucao
	 *     true  - Caso contrario.
	 */
	bool update_serviceTime_remaining ();

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
	 *     states - estado do processo.
	 */
	states get_state ();

	/*
	 * BRIEF:
	 *     Atribui a finishTime o tempo em que o processo foi finalizado.
	 *
	 * PARAM:
	 *     time - unsigned - Tempo do termino do processo.
	 */
	void set_finishTime (unsigned time);
};

#endif /* PROCESS_H_ */