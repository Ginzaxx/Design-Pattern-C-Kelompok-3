# Technical Design Document
## Blind Progression & Skip Reward System

### 1. Arsitektur Utama
Sistem ini menggunakan dua *Design Pattern* utama:
*   **State Pattern:** Mengatur progresi level (Small Blind -> Big Blind -> Boss Blind -> Next Ante).
*   **Command Pattern:** Mengatur pemberian *reward* (hadiah) yang dieksekusi secara tertunda ketika pemain melakukan SKIP pada Blind.

---

### 2. Blind System (State Pattern)
Sistem ini memisahkan setiap fase permainan ke dalam *class* state (status) yang terpisah.

*   **Interface `BlindState`:** Menentukan standar fungsi (seperti target skor, uang hadiah, ke state mana selanjutnya, dan *reward* saat di-skip).
*   **Alur Progresi:** 
    `SmallBlindState` ➔ `BigBlindState` ➔ `BossBlindState` ➔ *(Naik Ante)* ➔ `SmallBlindState`.

---

### 3. Skip Reward System (Command Pattern)
Saat pemain memilih SKIP, *reward* tidak langsung diberikan. *Reward* tersebut dibungkus menjadi sebuah objek perintah (Command) untuk dieksekusi nanti.

*   **Interface `RewardCommand`:** Menyimpan logika efek *reward* dan timing kapan *reward* tersebut aktif.
*   **Contoh Implementasi:** 
    *   `BonusHandCommand`: Menambah +1 kesempatan main.
    *   `FreePlayingCardCommand`: Memberikan kartu bermain gratis.
*   **Sistem Eksekusi:** *Command* yang dibuat saat SKIP akan masuk antrean, lalu baru dieksekusi saat permainan mencapai titik tertentu (misalnya awal *Blind* berikutnya atau awal *Ante* baru).

---

### 4. Runtime State (`SessionState`)
Objek utama yang menyimpan seluruh data berjalannya game (*current ante*, *total score*, jumlah *plays/discards*, *state* saat ini, dan antrean *reward* yang tertunda).

**Alur Permainan:**
1. **Mulai Blind:** Target skor dan hadiah ditentukan.
2. **Aksi Pemain:**
   * **PLAY:** Bermain normal untuk mencapai target.
   * **SKIP:** Generate `RewardCommand` ➔ Simpan Command di antrean ➔ Pindah ke Blind berikutnya.
3. **Eksekusi Tertunda:** Sistem akan mengeksekusi `RewardCommand` dari antrean hanya saat syarat *timing*-nya tercapai.

---

### 5. Aturan Teknis Tambahan
* Menggunakan **Smart Pointers** (`std::unique_ptr` / `std::shared_ptr`) untuk manajemen memori objek *State* dan *Command*.
* Menghindari penggunaan if-else/switch case yang panjang dalam mengatur alur game.
