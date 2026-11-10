# Sistem Pemesanan Tiket Pesawat / Kereta

Kerangka awal proyek tugas kelompok Sorting, Searching, dan Graph menggunakan C++11.

## Anggota dan file kerja

| Anggota | File yang dikerjakan | Tanggung jawab |
| Ezer | `src/ticket.cpp` | Data tiket, tampilkan tiket, Selection Sort harga dan waktu |
| Dinda | `src/search.cpp` | Searching asal, tujuan, dan kombinasi rute |
| Nopal | `src/validation.cpp` | Validasi ID tiket, jumlah penumpang, dan pilihan menu |
| Udin | `src/booking.cpp` | Pemesanan tiket dan perhitungan total |
| Ibnu | `src/graph.cpp`, `src/main.cpp` | Graph, Dijkstra, dan integrasi menu akhir |

## Aturan penting

1. Semua fungsi dan nama variabel antarmodul mengikuti deklarasi yang sudah ada di file `.h`.
2. Setiap anggota hanya mengubah file `.cpp` yang menjadi tanggung jawabnya, kecuali ada kesepakatan bersama.
3. Jangan menghapus atau mengganti nama fungsi di header tanpa koordinasi.
4. Fungsi pada kerangka masih berupa placeholder. Ganti isi fungsi yang ditandai `TODO`.
5. Data kota dan biaya Graph adalah data simulasi, bukan harga aktual.

## Compile

Jalankan dari folder utama proyek:

```bash
g++ -std=c++11 src/main.cpp src/ticket.cpp src/search.cpp src/validation.cpp src/booking.cpp src/graph.cpp -o tiket.exe
```

Windows PowerShell:

```powershell
.\tiket.exe
```

## Alur Git yang disarankan

Pemilik repository push kerangka ke `main` terlebih dahulu. Setelah itu setiap anggota:

```bash
git clone URL_REPOSITORY
cd NAMA_FOLDER_REPOSITORY
git checkout -b nama-anggota/nama-modul
```

Setelah selesai mengerjakan:

```bash
git add src/nama_file.cpp
git commit -m "feat: implement nama-modul"
git push -u origin nama-anggota/nama-modul
```

Lalu buat Pull Request ke `main`. Anggota lain tidak perlu mengedit file yang sama. Sebelum mulai atau melanjutkan setelah ada merge:

```bash
git checkout nama-anggota/nama-modul
git fetch origin
git merge origin/main
```

Jika kelompok memilih cara paling sederhana tanpa branch, lakukan push satu per satu dan pastikan anggota berikutnya `git pull --rebase origin main` sebelum push.
