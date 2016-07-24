# Menggemaskan dan Cantik
## Author: Alham Fikri Aji


Sebentar lagi kompetisi paling bergengsi se-Indonesia akan diadakan! Apalagi kalau bukan Kompetisi Menggemaskan dan Cantik (GemasTik) Seperti biasa GemasTik tahun ini terdiri dari 2 kategori kompetisi: Kompetisi Kegemasan dan Kompetisi Kecantikan.

Setiap perwakilan universitas berhak mengirimkan tepat 1 kelompok untuk masing-masing kategori dimana setiap kelompok terdiri dari 3 orang. Selain itu setiap orang tidak boleh ikut lebih dari satu kategori. Anda sebagai seorang yang ditugaskan oleh pihak kampus untuk mengatur pembagian kelompok sedemikian rupa agar universitas anda dapat memenangkan kompetisi ini.

Ada tepat N kandidat yang dapat bertanding di GemasTik. Setiap kandidat ke-i memiliki 2 ukuran keahlian yaitu G[i] dan C[i]. G[i] menandakan seberapa menggemaskan kandidat tersebut dan C[i] menandakan seberapa cantik kandidat tersebut. Kekuatan suatu kelompok adalah total dari keahlian masing-masing anggotanya.

Kelompok pertama akan dikirim untuk mengikuti kontes Kegemasan sementara kelompok kedua akan dikirim untuk mengikuti kontes Kecantikan. Anda diminta mengatur pembagian kelompok sedemikian rupa sehingga kekuatan Kegemasan kelompok pertama ditambah kekuatan Kecantikan kelompok kedua maksimal. Dengan kata lain jika anggota kelompok pertama adalah a b c sementara anggota kelompok kedua adalah x y dan z Carilah pembagian sedemikian sehingga G[a] + G[b] + G[c] + C[x] + C[y] + C[z] maksimal.


##Format Masukan
Baris pertama adalah sebuah integer yang menyatakan N 6 <= N <= 50000
N baris berikutnya masing-masing terdiri dari sebuah string s[i] menyatakan nama dari kandidat ke-i G[i] dan C[i].
Panjang s[i] tidak lebih dari 8 karakter [a-z] 1 <= G[i]C[i] <= 1000000.
Masukan dijamin terurut sesuai nama kandidat.


##Format Keluaran
Keluaran terdiri dari tepat dua baris.
Baris pertama terdiri dari 3 string yang dipisahkan spasi yang merupakan nama-nama anggota kelompok 1 (Kategori Kegemasan)
Baris pertama terdiri dari 3 string yang dipisahkan spasi yang merupakan nama-nama anggota kelompok 2 (Kategori Kecantikan)
Jika ada lebih dari 1 cara membagi kelompok dimana total kekuatannya maksimal, keluarkan output yang terkecil secara leksikografis


##Contoh Masukan

9
abdul 3 3
afaji 7 6
alham 11 6
alice 7 12
budi 5 3
jack 3 10
kwak 10 10
kwek 2 6
kwok 5 8


##Contoh Keluaran
afaji alham budi
alice jack kwak


