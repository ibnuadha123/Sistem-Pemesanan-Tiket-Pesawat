#include "ticket.h"
#include <iomanip>

using namespace std;

// Data tiket digunakan bersama oleh modul searching, booking, dan graph.
vector<Ticket> tickets;

void initTickets() {
    // Menghindari data terduplikasi jika fungsi dipanggil lebih dari sekali.
    tickets.clear();

    // Data simulasi tiket pesawat dan kereta.
    tickets.push_back({1, "Pesawat", "Medan", "Jakarta", 1250000, "07:30"});
    tickets.push_back({2, "Pesawat", "Medan", "Surabaya", 1450000, "09:15"});
    tickets.push_back({3, "Pesawat", "Jakarta", "Bali", 1100000, "06:45"});
    tickets.push_back({4, "Pesawat", "Medan", "Bali", 1750000, "13:20"});
    tickets.push_back({5, "Kereta", "Jakarta", "Bandung", 150000, "08:00"});
    tickets.push_back({6, "Kereta", "Bandung", "Yogyakarta", 280000, "10:30"});
    tickets.push_back({7, "Kereta", "Jakarta", "Surabaya", 450000, "15:10"});
    tickets.push_back({8, "Pesawat", "Surabaya", "Makassar", 1350000, "11:00"});
    tickets.push_back({9, "Pesawat", "Bali", "Lombok", 650000, "05:50"});
    tickets.push_back({10, "Kereta", "Yogyakarta", "Jakarta", 320000, "16:25"});
}

void displayTicket(const Ticket& ticket) {
    cout << left
         << setw(5)  << ticket.id
         << setw(12) << ticket.transport
         << setw(16) << ticket.origin
         << setw(16) << ticket.destination
         << right << setw(15) << ticket.price
         << "   " << left << setw(10) << ticket.departure
         << '\n';
}

void displayTickets() {
    if (tickets.empty()) {
        cout << "\nBelum ada data tiket yang tersedia.\n";
        return;
    }

    cout << "\n============================== DAFTAR TIKET ==============================\n";
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "Transport"
         << setw(16) << "Asal"
         << setw(16) << "Tujuan"
         << right << setw(15) << "Harga (Rp)"
         << "   " << left << setw(10) << "Berangkat"
         << '\n';
    cout << string(78, '-') << '\n';

    for (const Ticket& ticket : tickets) {
        displayTicket(ticket);
    }

    cout << string(78, '-') << '\n';
}

void sortByPrice() {
    // Selection Sort: pilih harga terkecil dari bagian yang belum terurut.
    for (size_t i = 0; i < tickets.size(); i++) {
        size_t minIndex = i;

        for (size_t j = i + 1; j < tickets.size(); j++) {
            if (tickets[j].price < tickets[minIndex].price) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Ticket temp = tickets[i];
            tickets[i] = tickets[minIndex];
            tickets[minIndex] = temp;
        }
    }

    cout << "\nTiket berhasil diurutkan berdasarkan harga termurah.\n";
}

void sortByDeparture() {
    // Selection Sort: format HH:MM dua digit dapat dibandingkan secara leksikografis.
    for (size_t i = 0; i < tickets.size(); i++) {
        size_t earliestIndex = i;

        for (size_t j = i + 1; j < tickets.size(); j++) {
            if (tickets[j].departure < tickets[earliestIndex].departure) {
                earliestIndex = j;
            }
        }

        if (earliestIndex != i) {
            Ticket temp = tickets[i];
            tickets[i] = tickets[earliestIndex];
            tickets[earliestIndex] = temp;
        }
    }

    cout << "\nTiket berhasil diurutkan berdasarkan waktu keberangkatan paling awal.\n";
}
