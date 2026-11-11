#include "booking.h"
#include "validation.h"

// UDIN: gunakan tickets dari ticket.h dan fungsi validasi dari validation.h.

void bookTicket() {
    int id;
    int passengers;

    displayTickets();

    // 1. Minta ID tiket dan pastikan ID valid.
    cout << "\nMasukkan ID tiket: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "ID tiket harus berupa angka.\n";
        return;
    }

    if (!isValidTicketID(tickets, id)) {
        cout << "ID tiket tidak ditemukan.\n";
        return;
    }

    // 2. Minta jumlah penumpang dan pastikan jumlahnya valid.
    cout << "Masukkan jumlah penumpang: ";
    if (!(cin >> passengers)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Jumlah penumpang harus berupa angka.\n";
        return;
    }

    if (!isValidPassengerCount(passengers)) {
        cout << "Jumlah penumpang tidak valid.\n";
        return;
    }

    // Cari tiket berdasarkan ID (urutan vector bisa berubah setelah sorting).
    const Ticket* selected = nullptr;
    for (size_t i = 0; i < tickets.size(); i++) {
        if (tickets[i].id == id) {
            selected = &tickets[i];
            break;
        }
    }

    // 3. Hitung total = harga tiket * jumlah penumpang.
    long long total = static_cast<long long>(selected->price) * passengers;

    // 4. Tampilkan ringkasan/bukti pemesanan.
    cout << "\n========== BUKTI PEMESANAN ==========\n";
    cout << "ID Tiket        : " << selected->id << '\n';
    cout << "Transportasi    : " << selected->transport << '\n';
    cout << "Rute            : " << selected->origin << " - " << selected->destination << '\n';
    cout << "Berangkat       : " << selected->departure << '\n';
    cout << "Harga/penumpang : Rp " << selected->price << '\n';
    cout << "Jumlah penumpang: " << passengers << '\n';
    cout << "Total bayar     : Rp " << total << '\n';
    cout << "=====================================\n";
}
