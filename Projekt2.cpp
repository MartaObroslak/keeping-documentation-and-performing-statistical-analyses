#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Uczen {
private:
 int id;
 string imie;
 char plec;
 vector<int> kolokwia;
 double srednia;
public:
 Uczen(int _id, const string& _imie, char _plec, const vector<int>& _kolokwia)
 : id(_id), imie(_imie), plec(_plec), kolokwia(_kolokwia) {
 obliczSrednia();
 }
 int getId() const {
 return id;
 }
 string getImie() const {
 return imie;
 }
 char getPlec() const {
 return plec;
 }
 const vector<int>& getKolokwia() const {
 return kolokwia;
 }
 double getSrednia() const {
 return srednia;
 }
 void obliczSrednia() {
 int sum = 0;
 for (int kolokwium : kolokwia) {
 sum += kolokwium;
 }
 srednia = static_cast<double>(sum) / kolokwia.size();
 }
};
class Klasa {
private:
 vector<Uczen> uczniowie;
public:
 void dodajUcznia(const Uczen& uczen) {
 uczniowie.push_back(uczen);
 }
 void usunUcznia(int id) {
 auto it = find_if(uczniowie.begin(), uczniowie.end(), [id](const Uczen& uczen) {
 return uczen.getId() == id;
 });
 if (it != uczniowie.end()) {
 uczniowie.erase(it);
 }
 }
 void aktualizujUcznia(int id, const vector<int>& kolokwia) {
 auto it = find_if(uczniowie.begin(), uczniowie.end(), [id](const Uczen& uczen) {
 return uczen.getId() == id;
 });
 if (it != uczniowie.end()) {
 it->obliczSrednia();
 }
 }
 void wyswietlWszystkichUczniow() const {
 for (const Uczen& uczen : uczniowie) {
 cout << "ID: " << uczen.getId() << ", Imie: " << uczen.getImie()
 << ", Plec: " << uczen.getPlec() << ", Srednia: " << uczen.getSrednia() << endl;
 }
 }
 double obliczSredniaUcznia(int id) const {
 auto it = find_if(uczniowie.begin(), uczniowie.end(), [id](const Uczen& uczen) {
 return uczen.getId() == id;
 });
 if (it != uczniowie.end()) {
 return it->getSrednia();
 }
 return 0.0;
 }
 void wyswietlSredniaUcznia(int id) const {
 auto it = find_if(uczniowie.begin(), uczniowie.end(), [id](const Uczen& uczen) {
 return uczen.getId() == id;
 });
 if (it != uczniowie.end()) {
 cout << "Srednia dla ucznia o ID " << id << ": " << it->getSrednia() << endl;
 }
 }
 double obliczSredniaWszystkichUczniow() const {
 double sum = 0.0;
 for (const Uczen& uczen : uczniowie) {
 sum += uczen.getSrednia();
 }
 return sum / uczniowie.size();
 }
 void wyswietlNajlepszyINajgorszyWynik() const {
 auto minMax = minmax_element(uczniowie.begin(), uczniowie.end(), [](const Uczen& uczen1, const 
Uczen& uczen2) {
 return uczen1.getSrednia() < uczen2.getSrednia();
 });
 auto itMin = minMax.first;
 auto itMax = minMax.second;
 cout << "Najlepszy wynik: " << itMax->getSrednia() << ", Uczen ID: " << itMax->getId()
 << ", Imie: " << itMax->getImie() << ", Plec: " << itMax->getPlec() << endl;
 cout << "Najgorszy wynik: " << itMin->getSrednia() << ", Uczen ID: " << itMin->getId()
 << ", Imie: " << itMin->getImie() << ", Plec: " << itMin->getPlec() << endl;
 }
};
int main() {
 Klasa klasa;
 int wybor;
 do {
 cout << "==================================================" << endl;
 cout << " MENU" << endl;
 cout << "==================================================" << endl;
 cout << "1. Dodaj wpis." << endl;
 cout << "2. Usun wpis." << endl;
 cout << "3. Aktualizuj wpis." << endl;
 cout << "4. Wyswietl wszystkie wpisy." << endl;
 cout << "5. Oblicz srednia wynikow wybranego studenta." << endl;
 cout << "6. Wyswietl srednia wynikow wybranego studenta." << endl;
 cout << "7. Oblicz i wyswietl srednia wszystkich studentow." << endl;
 cout << "8. Wyswietl najlepszy i najgorszy wynik." << endl;
 cout << "0. Wyjscie." << endl;
 cout << "Wpisz swoj wybor: ";
 cin >> wybor;
 switch (wybor) {
 case 1: {
 int id;
 string imie;
 char plec;
 vector<int> kolokwia;
 cout << "Podaj ID ucznia: ";
 cin >> id;
 cout << "Podaj imie ucznia: ";
 cin >> imie;
 cout << "Podaj plec ucznia (M - mezczyzna, K - kobieta): ";
 cin >> plec;
 cout << "Podaj wyniki kolokwiow (3 liczby oddzielone spacja): ";
 kolokwia.resize(3);
 for (int i = 0; i < 3; i++) {
 cin >> kolokwia[i];
 }
 Uczen uczen(id, imie, plec, kolokwia);
 klasa.dodajUcznia(uczen);
 cout << "Dodano ucznia." << endl;
 break;
 }
 case 2: {
 int id;
 cout << "Podaj ID ucznia do usuniecia: ";
 cin >> id;
 klasa.usunUcznia(id);
 cout << "Usunieto ucznia." << endl;
 break;
 }
 case 3: {
 int id;
 vector<int> kolokwia;
 cout << "Podaj ID ucznia do aktualizacji: ";
 cin >> id;
 cout << "Podaj nowe wyniki kolokwiow (3 liczby oddzielone spacja): ";
 kolokwia.resize(3);
 for (int i = 0; i < 3; i++) {
 cin >> kolokwia[i];
 }
 klasa.aktualizujUcznia(id, kolokwia);
 cout << "Zaktualizowano ucznia." << endl;
 break;
 }
 case 4: {
 klasa.wyswietlWszystkichUczniow();
 break;
 }
 case 5: {
 int id;
 cout << "Podaj ID ucznia, dla ktorego chcesz obliczyc srednia: ";
 cin >> id;
 double srednia = klasa.obliczSredniaUcznia(id);
 cout << "Srednia dla ucznia o ID " << id << ": " << srednia << endl;
 break;
 }
 case 6: {
 int id;
 cout << "Podaj ID ucznia, ktorego srednia chcesz wyswietlic: ";
 cin >> id;
 klasa.wyswietlSredniaUcznia(id);
 break;
 }
 case 7: {
 double sredniaWszystkich = klasa.obliczSredniaWszystkichUczniow();
 cout << "Srednia wszystkich uczniow: " << sredniaWszystkich << endl;
 break;
 }
 case 8: {
 klasa.wyswietlNajlepszyINajgorszyWynik();
 break;
 }
 case 0: {
 cout << "Koniec programu." << endl;
 break;
 }
 default: {
 cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
 break;
 }
 }
 cout << endl;
 } while (wybor != 0);
 return 0;
}

