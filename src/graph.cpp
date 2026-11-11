#include "graph.h"
#include "ticket.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

// Menghapus spasi di awal/akhir dan mengubah nama kota menjadi huruf kecil.
static string normalizeCity(const string& city) {
    size_t start = 0;
    while (start < city.size() && isspace(static_cast<unsigned char>(city[start]))) {
        start++;
    }

    size_t end = city.size();
    while (end > start && isspace(static_cast<unsigned char>(city[end - 1]))) {
        end--;
    }

    string result = city.substr(start, end - start);
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = static_cast<char>(tolower(static_cast<unsigned char>(result[i])));
    }

    return result;
}

// Mengambil semua kota unik dari data tiket.
static vector<string> getCities() {
    vector<string> cities;

    for (size_t i = 0; i < tickets.size(); i++) {
        string routeCities[2] = {tickets[i].origin, tickets[i].destination};

        for (int j = 0; j < 2; j++) {
            if (normalizeCity(routeCities[j]).empty()) {
                continue;
            }

            bool found = false;
            for (size_t k = 0; k < cities.size(); k++) {
                if (normalizeCity(cities[k]) == normalizeCity(routeCities[j])) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cities.push_back(routeCities[j]);
            }
        }
    }

    return cities;
}

// Mencari indeks kota di dalam daftar kota.
static int getCityIndex(const vector<string>& cities, const string& city) {
    string target = normalizeCity(city);

    for (size_t i = 0; i < cities.size(); i++) {
        if (normalizeCity(cities[i]) == target) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// Mengubah angka menjadi format Rupiah, contoh 1250000 menjadi Rp 1.250.000.
static string formatRupiah(long long amount) {
    string number = to_string(amount);

    for (int position = static_cast<int>(number.length()) - 3;
         position > 0; position -= 3) {
        number.insert(static_cast<size_t>(position), ".");
    }

    return "Rp " + number;
}

// Meminta input nama kota dari pengguna.
static bool readCity(const string& prompt, string& city) {
    cout << prompt;

    if (!getline(cin >> ws, city)) {
        cin.clear();
        cout << "Input kota tidak berhasil dibaca.\n";
        return false;
    }

    if (normalizeCity(city).empty()) {
        cout << "Nama kota tidak boleh kosong.\n";
        return false;
    }

    return true;
}

int findCityIndex(const string& city) {
    vector<string> cities = getCities();
    return getCityIndex(cities, city);
}

void findShortestPath() {
    if (tickets.empty()) {
        cout << "\nBelum ada data tiket untuk membentuk Graph.\n";
        return;
    }

    vector<string> cities = getCities();
    int cityCount = static_cast<int>(cities.size());

    if (cityCount == 0) {
        cout << "\nBelum ada data kota yang tersedia.\n";
        return;
    }

    cout << "\n========== DAFTAR KOTA ==========" << '\n';
    for (int i = 0; i < cityCount; i++) {
        cout << i + 1 << ". " << cities[i] << '\n';
    }

    string origin, destination;

    if (!readCity("\nMasukkan kota asal: ", origin)) {
        return;
    }

    if (!readCity("Masukkan kota tujuan: ", destination)) {
        return;
    }

    int source = findCityIndex(origin);
    int target = findCityIndex(destination);

    if (source == -1) {
        cout << "Kota asal tidak ditemukan dalam data tiket.\n";
        return;
    }

    if (target == -1) {
        cout << "Kota tujuan tidak ditemukan dalam data tiket.\n";
        return;
    }

    // Membuat adjacency matrix. INF berarti tidak ada rute langsung.
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<vector<long long> > graph(
        cityCount, vector<long long>(cityCount, INF)
    );

    for (int i = 0; i < cityCount; i++) {
        graph[i][i] = 0;
    }

    // Setiap tiket menjadi edge berarah dari kota asal ke kota tujuan.
    // Jika ada beberapa tiket untuk rute yang sama, gunakan harga termurah.
    for (size_t i = 0; i < tickets.size(); i++) {
        if (tickets[i].price < 0) {
            continue;
        }

        int from = getCityIndex(cities, tickets[i].origin);
        int to = getCityIndex(cities, tickets[i].destination);

        if (from != -1 && to != -1 && from != to) {
            if (tickets[i].price < graph[from][to]) {
                graph[from][to] = tickets[i].price;
            }
        }
    }

    // Inisialisasi algoritma Dijkstra.
    vector<long long> distance(cityCount, INF);
    vector<bool> visited(cityCount, false);
    vector<int> previous(cityCount, -1);

    distance[source] = 0;

    // Dijkstra menggunakan adjacency matrix.
    for (int count = 0; count < cityCount; count++) {
        int current = -1;

        // Pilih kota yang belum dikunjungi dengan biaya sementara terkecil.
        for (int i = 0; i < cityCount; i++) {
            if (!visited[i] && distance[i] != INF) {
                if (current == -1 || distance[i] < distance[current]) {
                    current = i;
                }
            }
        }

        // Tidak ada kota lain yang dapat dijangkau.
        if (current == -1) {
            break;
        }

        visited[current] = true;

        // Perbarui biaya menuju seluruh kota tetangga.
        for (int next = 0; next < cityCount; next++) {
            if (!visited[next] && graph[current][next] != INF) {
                long long newDistance = distance[current] + graph[current][next];

                if (newDistance < distance[next]) {
                    distance[next] = newDistance;
                    previous[next] = current;
                }
            }
        }
    }

    if (distance[target] == INF) {
        cout << "\nTidak ditemukan rute dari " << cities[source]
             << " menuju " << cities[target] << ".\n";
        return;
    }

    // Menyusun kembali jalur dari kota tujuan ke kota asal.
    vector<int> path;
    int current = target;

    while (current != -1) {
        path.push_back(current);

        if (current == source) {
            break;
        }

        current = previous[current];
    }

    if (path.empty() || path.back() != source) {
        cout << "Rute tidak dapat ditampilkan.\n";
        return;
    }

    reverse(path.begin(), path.end());

    // Menampilkan hasil rute dan rincian biaya setiap perjalanan.
    cout << "\n========== RUTE DENGAN BIAYA MINIMUM ==========\n";
    cout << "Kota asal   : " << cities[source] << '\n';
    cout << "Kota tujuan : " << cities[target] << '\n';
    cout << "Rute        : ";

    for (size_t i = 0; i < path.size(); i++) {
        cout << cities[path[i]];
        if (i + 1 < path.size()) {
            cout << " -> ";
        }
    }
    cout << '\n';

    if (path.size() == 1) {
        cout << "Anda sudah berada di kota tujuan.\n";
    } else {
        cout << "\nRincian biaya perjalanan:\n";
        for (size_t i = 0; i + 1 < path.size(); i++) {
            int from = path[i];
            int to = path[i + 1];

            cout << cities[from] << " -> " << cities[to]
                 << " : " << formatRupiah(graph[from][to]) << '\n';
        }
    }

    cout << "\nTotal biaya minimum: " << formatRupiah(distance[target]) << '\n';
    cout << "===============================================\n";
}