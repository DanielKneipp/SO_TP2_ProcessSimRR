/*
 * Process.cpp
 *
 *  Created on: 10/05/2014
 *      Author: daniel
 */

#include "Process.h"

Process::Process(
		const unsigned id, const unsigned serviceTime, const unsigned arrivalTime) :
		 id(id), serviceTime(serviceTime), serviceTime_remaining(serviceTime),
		 arrivalTime(arrivalTime), finishTime(0), state(READY) {}
	/*this->id = id;
	this->serviceTime = serviceTime;
	this->arrivalTime = arrivalTime;
	this->serviceTime_remaining = this->serviceTime;
}*/

bool Process::update_serviceTime_remaining(unsigned _time) {
	this->serviceTime_remaining -= _time;
	if (this->serviceTime_remaining == 0)
		return false;
	else
		return true;
}

void Process::set_state(const states newState) {
	this->state = newState;
}

states Process::get_state() {
	return this->state;
}

unsigned Process::get_serviceTime () {
	return this->serviceTime;
}

unsigned Process::get_arrivalTime () {
	return this->arrivalTime;
}

unsigned Process::get_finishTime () {
	return this->finishTime;
}

void Process::set_finishTime (unsigned time) {
	this->finishTime = time;
}

unsigned Process::get_serviceTime_remaining () {
	return this->serviceTime_remaining;
}

Process::~Process() {
}

