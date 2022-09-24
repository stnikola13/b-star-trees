#include "BStarTree.h"
#include <iostream>
#include <fstream>
using namespace std;

int loadFromSTD(string& key) { // Funkcija za unos jednog para reci sa standardnog ulaza.
	cout << "Unesite rec: ";
	string word;
	cin >> word;
	if (word == "X") return 0;
	else {
		key = word;
		return 1;
	}
}

int loadFromFile(string fileName, string* keys, int& noOfWords) { // Funkcija za citanje liste parova reci iz datoteke.
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Greska u radu sa datotekom!" << endl;
		return 0;
	}
	int count = 0;
	string word;
	while (getline(file, word)) {
		keys[count] = word;
		count++;
	}
	noOfWords = count;
	file.close();
	return 1;
}

int main() {

	BStarTree tree;
	string keys[100], fileName = "", key = "", word = "";
	int i = 0, n = 0, noOfWords = 0, j = 0, red = 0, added = 0, removed = 0, less = 0;
	bool cycle = true, isActive = false;

	while (cycle) {
		cout << endl << "- - - - - - - - - - Meni - - - - - - - - - -" << endl << "1. Formiranje stabla" << endl << "2. Pretraga kljuca" << endl <<
			"3. Umetanje kljuca" << endl << "4. Brisanje kljuca" << endl << "5. Ispis stabla" << endl <<
			"6. Broj kljuceva manji od datog" << endl << "7. Kraj programa" << endl << endl << "Unesite redni broj zeljene opcije: ";
		cin >> n;
		if (n <= 0 || n > 7) {
			cout << "Pogresno uneta opcija. Molimo pokusajte ponovo!" << endl;
			continue;
		}

		switch (n) {
		case 1:
			if (isActive) {
				cout << "Stablo je vec prethodno kreirano! Izaberite drugu opciju." << endl;
				continue;
			}
			else {
				while (true) {
					cout << "Unesite red stabla: ";
					cin >> red;
					if (red < 3 || red > 10) cout << "Red stabla mora biti izmedju 3 i 10!" << endl;
					else {
						isActive = true;
						break;
					}
				}
			}
			int m;
			cout << "1. Standardni ulaz" << endl << "2. Datoteka" << endl << "Unesite opciju izvora podataka: ";
			cin >> m;
			if (m <= 0 || m > 2) {
				cout << "Pogresno uneta opcija. Molimo pokusajte ponovo!" << endl;
				continue;
			}
			switch (m) {
			case 1:
				cout << "Unosite reci u zasebnim redovima. Za prekid unosa, unesite X." << endl;
				for (i = 0; i < 100; i++) {
					j = loadFromSTD(keys[i]);
					if (!j) break;
				}
				noOfWords = i;
				cout << "Unos uspesan." << endl;
				break;
			case 2:
				cout << "Unesite ime datoteke: ";
				cin >> fileName;
				j = loadFromFile(fileName, keys, noOfWords);
				if (j) cout << "Unos uspesan." << endl;
				break;
			}
			for (int k = 0; k < noOfWords; k++) tree.addKey(keys[k], red);
			break;

		case 2:
			if (!isActive) {
				cout << "Stablo nije incijalizovano!" << endl;
				continue;
			}
			else {
				cout << "Unesite kljuc za pretragu: ";
				cin >> key;
				if (key.length() < 1) {
					cout << "Neispravno uneta rec!" << endl;
					continue;
				}
				else {
					bool found = tree.search(key);
					if (found) cout << "Kljuc " << key << " je pronadjen!" << endl;
					else cout << "Kljuc " << key << " nije pronadjen!" << endl;
				}
			}
			break;

		case 3:
			if (!isActive) {
				cout << "Stablo nije incijalizovano!" << endl;
				continue;
			}
			cout << "Unesite kljuc koji zelite da dodate u stablo: ";
			cin >> key;
			if (key.length() < 1) {
				cout << "Neispravan unos reci." << endl;
				continue;
			}
			added = tree.addKey(key, red);
			if (added) cout << "Kljuc " << key << " uspesno umetnut u stablo!" << endl;
			else cout << "Kljuc " << key << " vec postoji u stablu!" << endl;
			break;

		case 4:
			if (!isActive) {
				cout << "Stablo nije incijalizovano!" << endl;
				continue;
			}
			cout << "Unesite kljuc koji zelite da obrisete iz stabla: ";
			cin >> key;
			if (key.length() < 1) {
				cout << "Neispravan unos kljuca." << endl;
				continue;
			}
			removed = tree.removeKey(key, red);
			if (removed) cout << "Kljuc " << key << " uspesno obrisan iz stabla!" << endl;
			else cout << "Kljuc " << key << " ne postoji u stablu!" << endl;
			break;

		case 5:
			if (!isActive) {
				cout << "Stablo nije incijalizovano!" << endl;
				continue;
			}
			//tree.print();
			cout << endl << endl << tree;
			break;

		case 6:
			if (!isActive) {
				cout << "Stablo nije incijalizovano!" << endl;
				continue;
			}
			cout << "Unesite kljuc za koji zelite da se pronadje broj reci koje su leksikografski manji od njega: ";
			cin >> key;
			if (key.length() < 1) {
				cout << "Neispravan unos kljuca." << endl;
				continue;
			}
			less = tree.findLesserKeys(key);
			cout << "Broj reci u stablu koje su leksikografski manje od unete je " << less << "." << endl;
			break;

		case 7:
			cout << "Zdravo!" << endl;
			cycle = false;
			break;
		}
	}

	return 0;
}