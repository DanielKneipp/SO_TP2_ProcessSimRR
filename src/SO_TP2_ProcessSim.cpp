/*
 * SO_TP2_ProcessSim.cpp
 *
 *  Created on: 13/05/2014
 *      Author: daniel
 */

#include <iostream>
#include "RoundRobin.h"

int main(int argc, char **argv) {
	unsigned n_iter = 0;
	unsigned quantum = 0;
	struct info_exec info;

	std::cout << "Digite o numero de iteracoes desejadas: " << std::endl;
	std::cin >> n_iter;
	std::cout << "Digite o valor do quantum: " << std::endl;
	std::cin >> quantum;

	info = simular_RoundRobin(n_iter, quantum);
	std::cout << "Numero de processos executados: " << info.n_processos_executados << std::endl;
	std::cout << "Tr/Tx (tempode de Turnaround / Tempo de execucao): " << info.TrTx_media  << std::endl;
	std::cout << "Tempo total de execucao: " << info.tempo_corrido << " milesegundos" << std::endl;

	return 0;
}
