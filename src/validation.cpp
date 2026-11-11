#include "validation.h"

using namespace std;

// Validasi ID tiket berdasarkan daftar tiket yang tersedia.
bool isValidTicketID(const vector<Ticket>& ticketList, int id) {
    if (id <= 0) {
        return false;
    }

    for (size_t i = 0; i < ticketList.size(); i++) {
        if (ticketList[i].id == id) {
            return true;
        }
    }

    return false;
}

// Validasi jumlah penumpang.
// Minimal 1 orang dan maksimal 10 orang.
bool isValidPassengerCount(int passengerCount) {
    return passengerCount >= 1 && passengerCount <= 10;
}

// Validasi pilihan menu berdasarkan batas minimum dan maksimum.
bool isValidMenuChoice(int choice, int minChoice, int maxChoice) {
    if (minChoice > maxChoice) {
        return false;
    }

    return choice >= minChoice && choice <= maxChoice;
}
