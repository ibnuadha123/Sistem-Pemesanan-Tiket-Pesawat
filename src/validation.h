#ifndef VALIDATION_H
#define VALIDATION_H

#include "ticket.h"

bool isValidTicketID(const vector<Ticket>& ticketList, int id);
bool isValidPassengerCount(int passengerCount);
bool isValidMenuChoice(int choice, int minChoice, int maxChoice);

#endif
