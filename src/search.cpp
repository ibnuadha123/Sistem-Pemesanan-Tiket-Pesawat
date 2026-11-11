#include "search.h"
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;

static string trim(const string& text) {
    size_t start = 0;
    while (start < text.size() && isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }

    size_t end = text.size();
    while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) {
        end--;
    }

    return text.substr(start, end - start);
}

static string toLowerCase(string text) {
    for (size_t i = 0; i < text.size(); i++) {
        text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
    }
    return text;
}

static bool sameText(const string& a, const string& b) {
    return toLowerCase(trim(a)) == toLowerCase(trim(b));
}

static bool readCity(const string& prompt, string& city) {
    cout << prompt;
    if (!getline(cin >> ws, city)) {
        cin.clear();
        return false;
    }

    city = trim(city);
    if (city.empty()) {
        cout << "Nama kota tidak boleh kosong.\n";
        return false;
    }

    return true;
}

static void printHeader(const string& title) {
    cout << "\n" << title << "\n";
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "Transport"
         << setw(16) << "Asal"
         << setw(16) << "Tujuan"
         << right << setw(15) << "Harga (Rp)"
         << "   " << left << setw(10) << "Berangkat"
         << '\n';
    cout << string(78, '-') << '\n';
}

static void showResults(const vector<Ticket>& results, const string& title,
                        const string& notFoundMessage) {
    if (results.empty()) {
        cout << "\n" << notFoundMessage << "\n";
        return;
    }

    printHeader(title);
    for (size_t i = 0; i < results.size(); i++) {
        displayTicket(results[i]);
    }
    cout << string(78, '-') << '\n';
    cout << "Ditemukan " << results.size() << " tiket.\n";
}

void searchByOrigin() {
    string origin;
    if (!readCity("Masukkan kota asal: ", origin)) {
        return;
    }

    vector<Ticket> results;
    for (size_t i = 0; i < tickets.size(); i++) {
        if (sameText(tickets[i].origin, origin)) {
            results.push_back(tickets[i]);
        }
    }

    showResults(results,
                "========== HASIL PENCARIAN KOTA ASAL: " + origin + " ==========",
                "Tidak ada tiket dengan kota asal \"" + origin + "\".");
}

void searchByDestination() {
    string destination;
    if (!readCity("Masukkan kota tujuan: ", destination)) {
        return;
    }

    vector<Ticket> results;
    for (size_t i = 0; i < tickets.size(); i++) {
        if (sameText(tickets[i].destination, destination)) {
            results.push_back(tickets[i]);
        }
    }

    showResults(results,
                "========== HASIL PENCARIAN KOTA TUJUAN: " + destination + " ==========",
                "Tidak ada tiket dengan kota tujuan \"" + destination + "\".");
}

void searchByRoute() {
    string origin, destination;
    if (!readCity("Masukkan kota asal: ", origin)) {
        return;
    }
    if (!readCity("Masukkan kota tujuan: ", destination)) {
        return;
    }

    vector<Ticket> results;
    for (size_t i = 0; i < tickets.size(); i++) {
        // Kombinasi rute: asal DAN tujuan harus cocok.
        if (sameText(tickets[i].origin, origin) &&
            sameText(tickets[i].destination, destination)) {
            results.push_back(tickets[i]);
        }
    }

    showResults(results,
                "========== HASIL PENCARIAN RUTE: " + origin + " -> " + destination + " ==========",
                "Tidak ada tiket untuk rute " + origin + " -> " + destination + ".");
}