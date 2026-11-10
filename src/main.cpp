#include <iostream>
#include "ticket.h"
#include "search.h"
#include "validation.h"
#include "booking.h"
#include "graph.h"

using namespace std;

int main() {
    initTickets();

    int choice;

    do {
        cout << "\n========== SISTEM PEMESANAN TIKET ==========\n";
        cout << "1. Tampilkan semua tiket\n";
        cout << "2. Cari tiket berdasarkan kota asal\n";
        cout << "3. Cari tiket berdasarkan kota tujuan\n";
        cout << "4. Cari tiket berdasarkan rute\n";
        cout << "5. Urutkan tiket berdasarkan harga\n";
        cout << "6. Urutkan tiket berdasarkan waktu keberangkatan\n";
        cout << "7. Cari rute dengan biaya minimum (Graph)\n";
        cout << "8. Pesan tiket\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus berupa angka.\n";
            continue;
        }

        if (!isValidMenuChoice(choice, 0, 8)) {
            cout << "Pilihan menu tidak tersedia.\n";
            continue;
        }

        switch (choice) {
            case 1: displayTickets(); break;
            case 2: searchByOrigin(); break;
            case 3: searchByDestination(); break;
            case 4: searchByRoute(); break;
            case 5: sortByPrice(); displayTickets(); break;
            case 6: sortByDeparture(); displayTickets(); break;
            case 7: findShortestPath(); break;
            case 8: bookTicket(); break;
            case 0: cout << "Terima kasih telah menggunakan program.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
