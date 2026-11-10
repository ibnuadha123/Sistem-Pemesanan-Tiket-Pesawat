#include "validation.h"

// NOPAL: kembangkan validasi ini dan tambahkan pengecekan input bila diperlukan.

bool isValidTicketID(const vector<Ticket>& ticketList, int id) {
    // Pemeriksaan dasar: ID harus ditemukan pada daftar tiket.
    for (int i = 0; i < static_cast<int>(ticketList.size()); i++) {
        if (ticketList[i].id == id) {
            return true;
        }
    }
    return false;
}

bool isValidPassengerCount(int passengerCount) {
    // TODO NOPAL: sesuaikan batas jumlah penumpang dengan kesepakatan kelompok.
    return passengerCount >= 1 && passengerCount <= 10;
}

bool isValidMenuChoice(int choice, int minChoice, int maxChoice) {
    // Pemeriksaan dasar agar menu dapat digunakan sejak kerangka dibuat.
    // TODO NOPAL: tambahkan validasi lain jika diperlukan.
    return choice >= minChoice && choice <= maxChoice;
}
