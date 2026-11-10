#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Ticket {
    int id;
    string transport;
    string origin;
    string destination;
    int price;
    string departure; // Format HH:MM, contoh 07:30
};

// Data tiket digunakan bersama oleh modul lain.
extern vector<Ticket> tickets;

void initTickets();
void displayTicket(const Ticket& ticket);
void displayTickets();
void sortByPrice();
void sortByDeparture();

#endif
