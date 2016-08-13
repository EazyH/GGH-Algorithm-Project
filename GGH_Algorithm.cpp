#include <iostream>
#include <time.h>
#include <cmath>
#include <windows.h>
#include <string.h>
#include <math.h>
using namespace std;

 long double *DodanieWektorow( long double* wektor1,  long double* wektor2, int wymiar){

	long double *wynik = new long double[wymiar];

	for (int i = 0; i < wymiar; i++){

		wynik[i] = wektor1[i] + wektor2[i];
	
	}

	return wynik;

}

 long double **TranspozycjaMacierzy(long double **Macierz, int wymiar) {

	long double **Transponowanie = new  long double *[wymiar];

	for (int i = 0; i < wymiar; i++) *(Transponowanie + i) = new  long double[wymiar];

	for (int i = 0; i < wymiar; i++) {

		for (int j = 0; j < wymiar; j++) {

			Transponowanie[j][i] = Macierz[i][j];

		}

	}

	return Transponowanie;

}

 long double **MnozenieMacierzy(long double **A,  long double **B, int wierszeA, int kolumnyA, int kolumnyB) {

	long double **C = new  long double *[wierszeA];
	long double suma = 0;

	for (int i = 0; i < wierszeA; i++) *(C + i) = new  long double[kolumnyB];

	for (int i = 0; i < wierszeA; i++) {

		for (int j = 0; j < kolumnyB; j++) {

			for (int k = 0; k < kolumnyA; k++) {

				suma += A[i][k] * B[k][j];

			}

			C[i][j] = suma;
			suma = 0;

		}

	}

	return C;

}

 long double **Zaokraglenie(long double **baza, int wymiar) {

	for (int i = 0; i < wymiar; i++) { 

		for (int j = 0; j < wymiar; j++) {

			baza[i][j] = round(baza[i][j]);

		}

	}

	return baza;

}

 long double **ZaokraglenieBabay(long double **babay, int kolumny) {

	for (int j = 0; j < kolumny; j++) babay[j][0] = round(babay[j][0]);

	return babay;

}

 long double WyznacznikKraty( long double **krata, int wymiar){

	long double **MacierzPomocnicza = new  long double *[wymiar]; 

	for (int i = 0; i < wymiar; i++) { 

		*(MacierzPomocnicza + i) = new  long double[wymiar];

		for (int j = 0; j < wymiar; j++) {

			MacierzPomocnicza[i][j] = krata[i][j];

		}

	}
	
	int  wiersz, znacznik = 1;
	long double temp, wyznacznik = 1.0;

	for (int i = 0; i < wymiar; i++){

		if (MacierzPomocnicza[i][i] == 0){

			znacznik = 0;
			for (int j = i + 1; j < wymiar; j++){

				if (MacierzPomocnicza[j][i] != 0){

					wiersz = j;

					for (int k = i; k < wymiar; k++){

						temp = MacierzPomocnicza[i][k];                
						MacierzPomocnicza[i][k] = MacierzPomocnicza[wiersz][k];
						MacierzPomocnicza[wiersz][k] = temp;

					}

					wyznacznik = -wyznacznik;
					j = wymiar;
					znacznik = 1;

				}

			}

		}

		if (!znacznik) return 0;

		for (int j = i + 1; j < wymiar; j++){

			temp = MacierzPomocnicza[j][i] / MacierzPomocnicza[i][i];

			for (int k = i; k < wymiar; k++){

				MacierzPomocnicza[j][k] -= temp*MacierzPomocnicza[i][k];  

			}

		}

		wyznacznik *= MacierzPomocnicza[i][i];

	}

	return wyznacznik;

}

 long double SkalarWektorow( long double* wektor1,  long double* wektor2, int wymiar){

	long double wynik = 0;

	for (int i = 0; i < wymiar; i++) wynik += wektor1[i] * wektor2[i];

	return wynik;

}

 long double MnozenieWektorow(long double* wektor1,  long double* wektor2, int wymiar) {

	long double wynik = 0;

	for (int i = 0; i < wymiar; i++) wynik += wektor1[i] * wektor2[i];

	return wynik;

}

void WypiszMacierz(long double **macierz, int wiersze, int kolumny) {

	for (int i = 0; i < wiersze; i++) {

		for (int j = 0; j < kolumny; j++) {

			cout.width(5);
			cout << macierz[i][j] << " ";

		}

		cout << "\n";

	}

}

 long double WspolczynnikHadamarda(long double **C, int wymiar) {

	long double wyznacznik = 1.0;

	wyznacznik = abs(WyznacznikKraty(C, wymiar));

	long double iloczyn_norm = 1;

	for (int i = 0; i < wymiar; i++) iloczyn_norm *= sqrt(SkalarWektorow(C[i], C[i], wymiar));

	wyznacznik = wyznacznik / iloczyn_norm;
	wyznacznik = pow(wyznacznik, 1.0 / wymiar);

	return wyznacznik;

}

 long double **Ortogonalizacja(long double **tablicaWektorow, int wymiar) {

	long double **tablicaWektorowGwiazdka = new  long double *[wymiar]; 

	for (int i = 0; i < wymiar; i++) *(tablicaWektorowGwiazdka + i) = new  long double[wymiar];

	for (int i = 0; i < wymiar; i++) tablicaWektorowGwiazdka[0][i] = tablicaWektorow[0][i]; 

	long double* temp1 = new  long double[wymiar];
	long double* temp2 = new  long double[wymiar];

	for (int i = 1; i < wymiar; i++) {

		for (int q = 0; q < wymiar; q++) {

			tablicaWektorowGwiazdka[i][q] = tablicaWektorow[i][q];
			temp1[q] = 0;
			temp2[q] = 0;

		}

		for (int j = 0; j < i; j++) {

			 long double licznik = MnozenieWektorow(tablicaWektorow[i], tablicaWektorowGwiazdka[j], wymiar);
			 long double mianownik = MnozenieWektorow(tablicaWektorowGwiazdka[j], tablicaWektorowGwiazdka[j], wymiar);
			 long double skalar = licznik / mianownik;

			for (int l = 0; l < wymiar; l++) temp1[l] = tablicaWektorowGwiazdka[j][l] * skalar;

			for (int k = 0; k < wymiar; k++) temp2[k] += temp1[k];

		}

		for (int x = 0; x < wymiar; x++) tablicaWektorowGwiazdka[i][x] = tablicaWektorowGwiazdka[i][x] - temp2[x];

	}

	return tablicaWektorowGwiazdka;

}

 long double *ZaszyfrujWiadomosc(long double **Baza,  long double *wiadomosc,  long double *r, int wymiar) {

	long double **Szyfrogram = TranspozycjaMacierzy(Baza, wymiar);

	long double **WektorSzyfrogram = new  long double *[1];

	*WektorSzyfrogram = new  long double[wymiar];

	long double temp;
	
	for (int i = 0; i < wymiar; i++) { 
		
		temp = wiadomosc[i];

		WektorSzyfrogram[0][i] = temp; 
	
	}

	Szyfrogram = MnozenieMacierzy(WektorSzyfrogram, Szyfrogram, 1, wymiar, wymiar);

	long double *WektorWynikowy = new  long double[wymiar];

	for (int i = 0; i < wymiar; i++) {

		temp = Szyfrogram[0][i];
		WektorWynikowy[i] = temp;

	}

	WektorWynikowy = DodanieWektorow(WektorWynikowy, r, wymiar);

	cout << "\nBob wysyla wiadomosc: M * C^T + R: ";

	for (int i = 0; i < wymiar; i++) cout << WektorWynikowy[i] << " ";

	return WektorWynikowy;

}

 long double** KofaktoryDopelnienia(long double ** A, int n){

	long double ** C = new  long double *[n];

	for (int i = 0; i < n; ++i) C[i] = new  long double[n];

	long double ** M = new  long double *[n - 1];

	int i;

	for (i = 0; i < n - 1; ++i) M[i] = new  long double[n - 1];

	int j, i1, j1, ii, jj;

	for (j = 0; j < n; ++j){

		for (i = 0; i < n; ++i){

			i1 = 0;

			for (ii = 0; ii < n; ++ii){

				if (ii == i) continue;

				j1 = 0;

				for (jj = 0; jj < n; ++jj){

					if (jj == j) continue;

					M[i1][j1] = A[ii][jj];

					j1++;

				}

				i1++;

			}

			 long double detM = WyznacznikKraty(M, n - 1);

			if ((i + j) % 2 == 0) C[i][j] = detM;
			else C[i][j] = -detM;

		}

	}

	return C;

}

 long double **OdwrotnoscMacierzy( long double ** A, int n){

	long double ** B = new  long double *[n];
	
	for (int i = 0; i < n; ++i) B[i] = new  long double[n];

	long double c = WyznacznikKraty(A, n);

	long double ** C = new  long double *[n];
	
	for (int i = 0; i < n; ++i) C[i] = new  long double[n];

	C = KofaktoryDopelnienia(A, n);

	B = TranspozycjaMacierzy(C, n);

	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) B[i][j] /= c;
	
	return B;

}

 long double **Babay( long double **DobraBaza,  long double *szyfrogram, int wymiar) {

	DobraBaza =  OdwrotnoscMacierzy(DobraBaza, wymiar);

	long double **szyfrogramtrans = new  long double *[wymiar];

	for (int i = 0; i < wymiar; i++) *(szyfrogramtrans + i) = new  long double[1];

	long double temp;

	for (int i = 0; i < wymiar; i++) {
			
		temp = szyfrogram[i];

		szyfrogramtrans[i][0] = temp;

	}

	DobraBaza = MnozenieMacierzy(DobraBaza, szyfrogramtrans, wymiar, wymiar, 1);
	DobraBaza = ZaokraglenieBabay(DobraBaza, wymiar);
	
	return DobraBaza;

}

int main() {

	srand(time(NULL));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

	int wymiar, wspolczynnik;
	long double WspHadamard, detL;

	cout << "Podaj wymiar bazy: ";
	cin >> wymiar;

	long double **Baza = new  long double *[wymiar]; 

	for (int i = 0; i < wymiar; i++) *(Baza + i) = new  long double[wymiar];

	do {

		for (int i = 0; i < wymiar; i++) { 

			for (int j = 0; j < wymiar; j++) {

				wspolczynnik = (rand() % 30) + 1;
				Baza[i][j] = wspolczynnik;

			}

		}

		Baza = Ortogonalizacja(Baza, wymiar); 
		Baza = Zaokraglenie(Baza, wymiar);    
		detL = WyznacznikKraty(Baza, wymiar);
		WspHadamard = WspolczynnikHadamarda(Baza, wymiar);

	} while (WspHadamard <= 0.75 || detL == 0);

	cout << "\nAlicja generuje dobra baze: " << endl;
	WypiszMacierz(Baza, wymiar, wymiar);

	cout << "\nWspolczynnik Hadamarda: " << WspHadamard << endl;
	
	long double **DobraBaza = new  long double *[wymiar];

	for (int i = 0; i < wymiar; i++) {

		*(DobraBaza + i) = new  long double[wymiar];

		for (int j = 0; j < wymiar; j++) {

			DobraBaza[i][j] = Baza[i][j];

		}

	}

	long double **DobraBaza2 = new  long double *[wymiar];

	for (int i = 0; i < wymiar; i++) {

		*(DobraBaza2 + i) = new  long double[wymiar];

		for (int j = 0; j < wymiar; j++) {

			DobraBaza2[i][j] = Baza[i][j];

		}

	}

	long double **MacierzUnimodularna = new  long double *[wymiar]; 

	for (int i = 0; i < wymiar; i++) *(MacierzUnimodularna + i) = new  long double[wymiar];

	do {

		for (int i = 0; i < wymiar; i++) { 

			for (int j = 0; j < wymiar; j++) {

				if (j == i) MacierzUnimodularna[i][j] = 1;
				else MacierzUnimodularna[i][j] = 0;
				
			}

		}

		int x, y;
		wspolczynnik = (rand() % 20) + 1;

		do {

			x = rand() % wymiar;
			y = rand() % wymiar;

		} while (x == y);

		MacierzUnimodularna[x][y] = wspolczynnik;

		Baza = MnozenieMacierzy(Baza, MacierzUnimodularna, wymiar, wymiar, wymiar);
		WspHadamard = WspolczynnikHadamarda(Baza, wymiar);

	} while (WspHadamard >= 0.1);

	cout << "\nAlicja generuje popsuta baze: " << endl;
	WypiszMacierz(Baza, wymiar, wymiar);
	cout << "\nWspolczynnik Hadamarda: " << WspHadamard << endl;

	long double **ZlaBaza2 = new  long double *[wymiar];

	for (int i = 0; i < wymiar; i++) {

		*(ZlaBaza2 + i) = new  long double[wymiar];

		for (int j = 0; j < wymiar; j++) {

			ZlaBaza2[i][j] = Baza[i][j];

		}

	}

	long double *Wiadomosc = new  long double [wymiar];
	cout << "\nPodaj wiadomosc (WEKTOR), ktora ma wyslac Bob: ";
	for (int i = 0; i < wymiar; i++) cin >> Wiadomosc[i];

	long double *r = new  long double[wymiar];
	cout << "\nPodaj r (WEKTOR) dla Boba: ";
	for (int i = 0; i < wymiar; i++) cin >> r[i];

	long double *Szyfrogram = ZaszyfrujWiadomosc(Baza, Wiadomosc, r, wymiar);

	long double **Babay1 = Babay(DobraBaza, Szyfrogram, wymiar);

	long double** pomocnicza = new  long double*[wymiar];

	for (int i = 0; i < wymiar; i++) pomocnicza[i] = new  long double[wymiar];

	for (int i = 0; i < wymiar; i++){

		for (int j = 0; j < wymiar; j++){

			pomocnicza[j][i] = Babay1[i][0] * DobraBaza2[j][i];

		}

	 }

	 long double **wynik = new  long double*[wymiar];

	 for (int i = 0; i < wymiar; i++){

		wynik[i] = new long double[1];

		wynik[i][0] = 0;

	 }

	 for (int i = 0; i < wymiar; i++){

		for (int j = 0; j < wymiar; j++) wynik[i][0] += pomocnicza[i][j];

	 }

	 long double **temp = TranspozycjaMacierzy(ZlaBaza2, wymiar);

	 temp =  OdwrotnoscMacierzy(temp, wymiar);

	 long double **pom = new  long double *[1];

	*pom = new  long double[wymiar];

	for (int i = 0; i < wymiar; i++) {

		pom[0][i] = wynik[i][0];

	}

	long double **WYNIK = MnozenieMacierzy(pom, temp, 1, wymiar, wymiar);

	cout << "\n\nWiadomosc, ktora odczytala Alicja: ";

	WypiszMacierz(WYNIK, 1, wymiar);

	cout << "\n" << endl;

	return 0;

}

