#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include<algorithm>
#include <vector>
#include <map>
#include <stack>
#define INVALID 1;
using namespace std;

class Durata
{
protected:
	int ore;
	int minute;

public:
	Durata()
	{
		this->minute = 0;
		this->ore = 0;
	}
	Durata(int ore, int minute)
	{
		this->minute = minute;
		this->ore = ore;
	}

	Durata& operator=(const Durata& a)
	{
		if (this != &a)
		{
			this->minute = a.minute;
			this->ore = a.ore;
		}
		return *this;
	}
	Durata(const Durata& a)
	{
		this->minute = a.minute;
		this->ore = a.ore;
	}

	friend ostream& operator<<(ostream& o, const Durata& a)
	{
		o << "Durata: " << a.ore << " ore si  " << a.minute << " minute" << endl;
		return o;
	}
	friend ofstream& operator<<(ofstream& o, const Durata& a)
	{
		o << a.ore << endl << a.minute << endl;
		return o;
	}

	friend istream& operator>>(istream& in, Durata& a)
	{
		cout << "Durata filmului(ore si minute) " << endl;
		cout << "Numarul de ore al filmului este:" << endl;
		in >> a.ore;
		cout << "Numarul de minute al filmului este:" << endl;
		in >> a.minute;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Durata& a)
	{
		in >> a.ore;
		in >> a.minute;
		return in;
	}

	bool setOre(Durata durata)
	{
		if (durata.ore >= 0)
		{
			this->ore = durata.ore;
			return true;
		}
		else return false;
	}
	bool setMinute(Durata durata)
	{
		if (durata.minute >= 0)
		{
			this->minute = durata.minute;
			return true;
		}
		else return false;
	}
	int MinuteTotale()
	{
		int minuteTotale = this->ore * 60 + this->minute;
		return minuteTotale;
	}
	bool operator==(const Durata& a)
	{
		if (ore == a.ore && minute == a.minute)
			return true;
		else return false;

	}
};

class Distributie
{
protected:
	int NrActori;
	string* actori;


public:
	Distributie()
	{
		NrActori = 1;
		actori = new string[NrActori];
		for (int i = 0;i < NrActori;i++)
		{
			actori[i] = "ACTOR";
		}

	}

	Distributie(int NrActori, string* actori)
	{
		this->NrActori = NrActori;
		this->actori = new string[NrActori];
		for (int i = 0;i < NrActori;i++)
		{
			this->actori[i] = actori[i];
		}
	}

	Distributie(const Distributie& a)
	{
		this->NrActori = a.NrActori;
		this->actori = new string[a.NrActori];
		for (int i = 0;i < a.NrActori;i++)
		{
			this->actori[i] = a.actori[i];
		}
	}
	~Distributie()
	{
		delete[] actori;
	}
	Distributie& operator=(const Distributie& a)
	{
		if (this != &a)
		{
			this->NrActori = a.NrActori;
			delete[] actori;
			this->actori = new string[a.NrActori];
			for (int i = 0;i < a.NrActori;i++)
			{
				this->actori[i] = a.actori[i];
			}
		}
		return*this;
	}
	friend ostream& operator<<(ostream& o, const Distributie& a)
	{
		o << "Actori: ";
		for (int i = 0;i < a.NrActori;i++)
		{
			o << a.actori[i];
			if (i != a.NrActori - 1)
			{
				o << ", ";
			}
		}
		return o;
	}
	friend ofstream& operator<<(ofstream& o, const Distributie& a)
	{
		o << a.NrActori << endl;
		for (int i = 0;i < a.NrActori;i++)
		{

			o << a.actori[i];
			if (i != a.NrActori - 1)
			{
				o << ",";
			}
			else o << ";";
		}
		return o;
	}
	friend istream& operator>>(istream& in, Distributie& a)
	{
		cout << "Numarul de actori ai filmului este:" << endl;
		in >> a.NrActori;
		delete[] a.actori;
		a.actori = new string[a.NrActori];
		in.ignore();
		for (int i = 0;i < a.NrActori;i++)
		{

			cout << "Actorul " << i + 1 << " este: " << endl;
			getline(in, a.actori[i]);
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Distributie& a)
	{

		in >> a.NrActori;
		delete[] a.actori;
		a.actori = new string[a.NrActori];
		in.ignore();
		for (int i = 0;i < a.NrActori;i++)
		{
			if (i < a.NrActori - 1)
				getline(in, a.actori[i], ',');
			else
				getline(in, a.actori[i], ';');
		}
		return in;
	}
	bool ScriereBinara(ofstream& f)
	{
		f.write((char*)&NrActori, sizeof(NrActori));
		size_t n;
		for (int i = 0;i < NrActori;i++)
		{
			n = actori[i].size();
			f.write((char*)&n, sizeof(n));
			f.write(actori[i].data(), n);
		}
		if (f.good())
		{
			return true;
		}
		else
			return false;
	}

	bool CitireBinara(ifstream& f)
	{
		f.read((char*)&NrActori, sizeof(NrActori));
		delete[]actori;
		size_t n;
		actori = new string[NrActori];
		for (int i = 0;i < NrActori;i++)
		{
			f.read((char*)&n, sizeof(n));
			actori[i].resize(n);
			f.read(&actori[i][0], n);
		}
		if (f.good())
		{
			return true;
		}
		else
			return false;
	}
	bool setNrActori(Distributie distributie)
	{
		if (distributie.NrActori > 0)
		{
			this->NrActori = distributie.NrActori;
			return true;
		}
		else return false;
	}
	bool setActori(Distributie distributie)
	{
		if (distributie.actori != NULL)
		{
			if (this->actori != NULL)
				delete[]actori;
			this->actori = new string[distributie.NrActori];
			for (int i = 0;i < distributie.NrActori;i++)
				this->actori[i] = distributie.actori[i];
			return true;
		}
		else return false;
	}
	string operator[](int index)
	{
		if (index >= 0 && index < this->NrActori)
			return actori[index];
		else throw INVALID;
	}
	bool operator==(const Distributie& a)
	{
		if (NrActori == a.NrActori)
		{
			for (int i = 0;i < NrActori;i++)
				if (!(actori[i] == a.actori[i]))
					return false;
			return true;
		}
		else return false;
	}
};

class Film
{
protected:
	int id;
	char* denumire;
	string gen;
	long int buget;
	Durata durata;
	string producator;
	Distributie distributie;
	string regizor;
	int anAparitie;

public:
	//constructor fara parametri, acesta va oferi valori default
	Film()
	{
		this->id = 0;
		this->denumire = new char[strlen("DENUMIRE") + 1];
		strcpy(this->denumire, "DENUMIRE");
		this->gen = "GEN";
		this->buget = 0;
		this->producator = "PRODUCATOR";
		this->anAparitie = 0;
		this->regizor = "REGIZOR";
	}

	Film(int id, const char* denumire, string gen, long int buget, Durata durata, string producator, Distributie distributie, string regizor, int anAparitie)
	{
		this->id = id;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->gen = gen;
		this->buget = buget;
		this->producator = producator;
		this->anAparitie = anAparitie;
		this->regizor = regizor;
		this->durata = durata;
		this->distributie = distributie;
	}
	~Film()
	{
		delete[] denumire;
	}

	Film(const Film& a)
	{
		this->id = a.id;
		this->denumire = new char[strlen(a.denumire) + 1];
		strcpy(this->denumire, a.denumire);
		this->gen = a.gen;
		this->buget = a.buget;
		this->producator = a.producator;
		this->anAparitie = a.anAparitie;
		this->regizor = a.regizor;
		this->durata = a.durata;
		this->distributie = a.distributie;
	}
	Film& operator=(const Film& a)
	{
		if (this != &a)
		{
			this->id = a.id;
			delete[] denumire;
			this->denumire = new char[strlen(a.denumire) + 1];
			strcpy(this->denumire, a.denumire);
			this->gen = a.gen;
			this->buget = a.buget;
			this->producator = a.producator;
			this->anAparitie = a.anAparitie;
			this->regizor = a.regizor;
			this->durata = a.durata;
			this->distributie = a.distributie;
		}
		return*this;

	}

	//Getters
	int getId()
	{
		return id;
	}
	const char* getDenumire()
	{
		return denumire;
	}
	string getGen()
	{
		return gen;
	}
	long int getBuget()
	{
		return buget;
	}
	string getProducator()
	{
		return producator;
	}
	int getAnAparitie()
	{
		return anAparitie;
	}
	string getRegizor()
	{
		return regizor;
	}
	Durata getDurata()
	{
		return durata;
	}
	Distributie getDistributie()
	{
		return distributie;
	}

	//Setters
	void setId(int id)
	{
		if (id > 0)
			this->id = id;
		else cout << "Valoare ID invalida!" << endl;
	}
	void setDenumire(const char* denumire)
	{
		if (strlen(denumire) > 2)
		{
			if (this->denumire != NULL)
			{
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else throw exception("Denumirea introdusa este prea scurta!");
	}
	void setGen(string gen)
	{
		if (gen.size() >= 2)
			this->gen = gen;
		else cout << "Genul introdus este invalid" << endl;
	}
	void setAnAparitie(int anAparitie)
	{
		if (anAparitie > 1900 && anAparitie <= 2023)
			this->anAparitie = anAparitie;
		else cout << "Anul introdus este invalid!" << endl;
	}
	void setRegizor(string regizor)
	{
		if (regizor.size() > 2)
			this->regizor = regizor;
		else cout << "Numele de regizor introdus este invalid" << endl;
	}
	void setProducator(string producator)
	{
		if (producator.size() > 2)
			this->producator = producator;
		else cout << "Numele producatorului introdus este invalid" << endl;
	}
	void setBuget(long int buget)
	{
		if (buget > 1000)
			this->buget = buget;
		else cout << "Bugetul  introdus este prea mic!" << endl;
	}
	void setDurata(Durata durata)
	{
		if (!this->durata.setOre(durata))
			cout << "Numarul de ore introdus este invalid!" << endl;
		if (!this->durata.setMinute(durata))
			cout << "Numarul de ore introdus este invalid!" << endl;
	}
	void setDistributie(Distributie distributie)
	{
		if (this->distributie.setNrActori(distributie))
		{
			if (!this->distributie.setActori(distributie))
				cout << "Numele actorilor introdusi sunt invalide!" << endl;
		}
		else	cout << "Numarul de actori introdus este invalid!" << endl;

	}

	void marimeBuget()
	{
		if (this->buget <= 50000000)
			cout << "Bugetul filmului " << getDenumire() << " a fost mic." << endl;
		else if (this->buget > 50000000 && this->buget <= 100000000)
			cout << "Bugetul filmului " << getDenumire() << " a fost mediu." << endl;
		else if (this->buget > 100000000)
			cout << "Bugetul filmului " << getDenumire() << " a fost mare." << endl;
	}
	void aAparutPrimul(Film& a)
	{
		if (this->anAparitie == a.anAparitie)
			cout << "Filmul " << this->getDenumire() << " si filmul " << a.getDenumire() << " au aparut in acelasi an." << endl;
		else if (this->anAparitie < a.anAparitie)
			cout << "Filmul " << this->getDenumire() << " a aparut inaintea filmului  " << a.getDenumire() << endl;
		else
			cout << "Filmul " << this->getDenumire() << " a aparut mai tarziu decat filmul  " << a.getDenumire() << endl;
	}
	int MinuteTotale()
	{
		return this->durata.MinuteTotale();
	}
	virtual void timpPanaLaPremiere() {};//forteaza clasa derivata sa suprascrie aceasta metoda

	bool operator>(Film& a)
	{
		if (this->MinuteTotale() > a.MinuteTotale())
			return true;
		else return false;
	}
	bool operator==(const Film& a)
	{
		if (id==a.id && strcmp(denumire,a.denumire) == 0 && gen==a.gen && anAparitie==a.anAparitie && regizor==a.regizor && producator==a.producator && buget==a.buget && durata==a.durata && distributie==a.distributie)
			return true;
		else return false;
	}
	bool operator<(Film& a)
	{
		if (!(*this > a) && !(this->MinuteTotale() == a.MinuteTotale()))
			return true;
		else return false;
	}
	int operator-(Film& a)
	{
		return this->durata.MinuteTotale() - a.durata.MinuteTotale();
	}
	string operator[](int index)
	{
		return this->distributie[index];
	}
	int operator+(Film& a)
	{
		int rez = this->buget + a.buget;
		return rez;
	}
	int operator+(int x)
	{
		int rez = buget + x;
		return rez;
	}
	friend int operator+(int x, Film& a)
	{
		return a + x;
	}

	operator float() const {
		return this->buget / 1'000'000.0f;
	}
	operator string() const
	{
		string str;
		// numaram cate cifre are bugetul
		if (this->buget != 0) {
			int numarCifre = 0;
			for (int i = this->buget; i > 0; i /= 10)
			{
				numarCifre++;
			}
			// convertim cifrele una cate una in string si le adaugam la stringul ce va fi returnat
			for (int i = numarCifre - 1; i >= 0; i--) {
				str += to_string((this->buget / static_cast<int>(pow(10, i))) % 10);
				if (i % 3 == 0 && i != 0) {
					str += ' ';  // adaugam un spatiu dupa fiecare a treia cifra
				}
			}
		}
		else str = to_string(this->buget);
		return str;
	}

	friend ostream& operator<<(ostream& o, const Film& a);
	friend istream& operator>>(istream& in, Film& a);
	friend ofstream& operator<<(ofstream& o, const Film& a);
	friend ifstream& operator>>(ifstream& in, Film& a);

	virtual bool ScriereBinara(ofstream& f)
	{
		size_t n = strlen(denumire);
		f.write((char*)&n, sizeof(n));
		f.write(denumire, n + 1);             //denumire

		f.write((char*)&id, sizeof(id));//id
		f.write((char*)&anAparitie, sizeof(anAparitie));//an
		n = gen.size();
		f.write((char*)&n, sizeof(n));
		f.write(gen.data(), n);                   //gen
		n = regizor.size();
		f.write((char*)&n, sizeof(n));
		f.write(regizor.data(), n);          //regizor
		n = producator.size();
		f.write((char*)&n, sizeof(n));
		f.write(producator.data(), n);    //producator
		f.write((char*)&buget, sizeof(buget));              //buget
		f.write((char*)&durata, sizeof(Durata));          //durata                       
		if (f.good() && distributie.ScriereBinara(f))     //distributie    
		{
			return true;
		}
		else return false;
	}

	virtual bool CitireBinara(ifstream& f)
	{
		size_t n;
		f.read((char*)&n, sizeof(n));
		delete[] denumire;
		denumire = new char[n + 1];
		f.read(denumire, n + 1);
		//denumire[n] = '\0';

		f.read((char*)&id, sizeof(id));

		f.read((char*)&anAparitie, sizeof(anAparitie));
		f.read((char*)&n, sizeof(n));
		gen.resize(n);
		f.read(&gen[0], n);
		f.read((char*)&n, sizeof(n));
		regizor.resize(n);
		f.read(&regizor[0], n);
		f.read((char*)&n, sizeof(n));
		producator.resize(n);
		f.read(&producator[0], n);
		f.read((char*)&buget, sizeof(buget));
		f.read((char*)&durata, sizeof(Durata));

		if (f.good() && distributie.CitireBinara(f))
		{
			return true;
		}
		else return false;
	}
};

ostream& operator<<(ostream& o, const Film& a)
{
	o << endl << "Denumire film :" << "\033[7m" << a.denumire << "\033[0m" << endl;
	o << "Id: " << a.id << endl;
	o << "Anul aparitiei: " << a.anAparitie << endl;
	o << "Gen: " << a.gen << endl;
	o << "Regizor: " << a.regizor << endl;
	o << "Producator: " << a.producator << endl;
	o << "Buget: " << string(a) << " EUR" << endl;
	o << a.durata;
	o << a.distributie << endl;
	return o;
}
istream& operator>>(istream& in, Film& a)
{
	cout << endl << "ID-ul filmului este: " << endl;
	in >> a.id;
	cout << "Denumirea filmului este: " << endl;
	in.ignore();
	delete[] a.denumire;
	char buffer[50];
	in.getline(buffer, 50);
	a.denumire = new char[strlen(buffer) + 1];
	strcpy(a.denumire, buffer);
	cout << "Anul de aparitie al filmului este: " << endl;
	in >> a.anAparitie;
	cout << "Genul fimului este: " << endl;
	in.ignore();
	getline(in, a.gen);
	cout << "Numele regizorului este: " << endl;
	getline(in, a.regizor);
	cout << "Producatorul este:" << endl;
	getline(in, a.producator);
	cout << "Bugetul filmului este(suma in euro):" << endl;
	in >> a.buget;
	in >> a.durata;
	in >> a.distributie;
	return in;
}
ofstream& operator<<(ofstream& o, const Film& a)
{
	o << a.denumire << endl;
	o << a.id << endl;
	o << a.anAparitie << endl;
	o << a.gen << endl;
	o << a.regizor << endl;
	o << a.producator << endl;
	o << a.buget << endl;
	o << a.durata;
	o << a.distributie << endl;
	return o;
}
ifstream& operator>>(ifstream& in, Film& a)
{
	delete[] a.denumire;
	char buffer[50];
	in.get(buffer, 50);
	a.denumire = new char[strlen(buffer) + 1];
	strcpy(a.denumire, buffer);
	in >> a.id;
	in >> a.anAparitie;
	in.ignore();
	getline(in, a.gen);
	getline(in, a.regizor);
	getline(in, a.producator);
	in >> a.buget;
	in >> a.durata;
	in >> a.distributie;
	return in;
}

template <typename T>
class ColectieFilme {
private:
	string numeColectie;
	T* filme;
	int nrFilme;

public:
	// constructor fara parametri
	ColectieFilme() : numeColectie(" "), filme(nullptr), nrFilme(0) {}

	// constructor cu toti parametrii
	ColectieFilme(string den ,int dim, T* filme)
	{
		this->numeColectie = den;
		this->nrFilme = dim;
		this->filme = new T[dim];
		for (int i = 0; i < nrFilme; i++)
		{
			this->filme[i] = filme[i];
		}
	}

	// constructor de copiere
	ColectieFilme(const ColectieFilme& colectie)
	{
		numeColectie = colectie.numeColectie;
		filme = new T[colectie.nrFilme];
		nrFilme = colectie.nrFilme;
		for (int i = 0; i < nrFilme; i++) {
			filme[i] = colectie.filme[i];
		}
	}

	// destructor
	~ColectieFilme()
	{
		if (filme != nullptr)
			delete[] filme;
	}

	// operator de atribuire
	ColectieFilme& operator=(const ColectieFilme& colectie) {
		if (this != &colectie) {
			if (filme != nullptr)
				delete[] filme;
			filme = new T[colectie.nrFilme];
			numeColectie = colectie.numeColectie;
			nrFilme = colectie.nrFilme;
			for (int i = 0; i < nrFilme; i++) {
				filme[i] = colectie.filme[i];
			}
		}
		return *this;
	}

	//operator de citire a obiectului de tip ColectieFilme
	friend istream& operator>>(istream& in, ColectieFilme& colectie) {
		cout <<endl<< "Numele colectiei este:" << endl;
		getline(in, colectie.numeColectie);
		cout << "Numarul de filme din colectie este:" << endl;
		in >> colectie.nrFilme;
		if (colectie.filme != nullptr)
			delete[] colectie.filme;
		colectie.filme = new T[colectie.nrFilme];
		for (int i = 0; i < colectie.nrFilme; i++)
		{
			if (colectie.nrFilme != 1)
			{
				cout << "Filmul " << i + 1 << " este:";
			}
			else cout << "Filmul este: ";
			in >> colectie.filme[i];
		}
		return in;
	}

	// operator de iesire a obiectului de tip ColectieFilme
	friend ostream& operator<<(ostream& out, const ColectieFilme& colectie) {
		out <<endl<< "Colectia "<<colectie.numeColectie <<" are in componenta ";
		if (colectie.nrFilme == 1)
			out << "un film.";
		else
			out << colectie.nrFilme << " filme.";
		for (int i = 0; i < colectie.nrFilme; i++)
		{
			if (colectie.nrFilme != 1)
			{
				out << endl << "Filmul " << i + 1 << " este:";
			}
			out << colectie.filme[i];
		}
		return out;
	}

	//operatorul de indexare
	T& operator[](int index)
	{
		if (index >= 0 && index < this->nrFilme)
			return filme[index];
		else throw INVALID;
	}


	//Metoda de sortare elemente dupa anul de aparitie in ordine crescatoare prin selectie
	void sortareCronologica()
	{
		for (int i = 0; i < nrFilme; i++)
		{
			int pozMin = i;
			for (int j = i + 1; j < nrFilme; j++)
			{
				if (filme[j].getAnAparitie() < filme[pozMin].getAnAparitie())
				{
					pozMin = j;
				}
			}
			swap(filme[i], filme[pozMin]);
		}
	}

	//Metoda de sortare elemente dupa id in ordine crescatoare folosind functia sort
	void sortareID()
	{
		sort(filme, filme + nrFilme, [](T& f1, T& f2) {return f1.getId() < f2.getId(); }  );

	}
	
	//Operatorul + care adauga un obiect in colectie
	ColectieFilme& operator+(const T& film) {
		ColectieFilme<T>temp ("temp", nrFilme + 1, new T[nrFilme + 1]);
		for (int i = 0; i < nrFilme; i++) {
			temp[i] = filme[i];
		}
		temp[nrFilme] = film;
		*this = temp;
		return *this;
	}
	//Operatorul + care adauga x obiecte neinitializate la finalul colectiei
	 ColectieFilme& operator+(int x) 
	{
		ColectieFilme<T>temp("temp", nrFilme + x, new T[nrFilme + x]);
		for (int i = 0; i < nrFilme; i++) {
			temp[i] = filme[i];
		}
		*this=temp;
		return *this;
	}
	//Operatorul - care sterge ultimele x obiecte din colectie
	ColectieFilme& operator-(int x)
	{
		if (x < nrFilme)
		{
			ColectieFilme<T>temp("temp", nrFilme - x, new T[nrFilme - x]);
			for (int i = 0; i < nrFilme-x; i++) {
				temp[i] = filme[i];
			}
			*this = temp;
		}
		else
		{
			ColectieFilme<T>temp;
			*this = temp;
		}
		return *this;
	}
	//Operatorul - care sterge un anumit obiect din colectie
	ColectieFilme& operator-(const T& film)
	{
		int poz = -1;
		for (int i = 0; i < nrFilme; i++) {
			if (filme[i] == film)
				poz = i;
		}
		if (poz != -1)
		{
			ColectieFilme<T>temp("temp", nrFilme - 1, new T[nrFilme - 1]);
			for (int i = 0; i < nrFilme; i++)
			{
				if(i!=poz)
					temp[i] = filme[i];
			}
			*this = temp;
		}
		return *this;
	}
	int durataTotalaColectie()
	{
		int rez=0;
		for (int i = 0;i < nrFilme;i++)
			rez += filme[i].MinuteTotale();
		return rez;
	}
	
	void celMaiMareBuget()
	{
		int index=0;
		int rez = 0;
		for(int i=0;i<nrFilme;i++)
			if (filme[i].getBuget() > rez)
			{
				rez = filme[i].getBuget();
				index = i;
			}
		string str = string(filme[index]);
		cout << "Cel mai mare buget din colectia " << this->numeColectie << "este de " << str << " EUR si apartine filmului " << filme[index].getDenumire() << "." << endl;
	}
};

// Clasa FilmPremiat derivata din clasa Film si clasa suport Data
/*
class Data
{
private:
	int zi, luna, an;

public:
	// Constructor fara parametrii
	Data()
	{
		zi = 1;
		luna = 1;
		an = 1900;
	}

	// Constructor cu toti parametrii
	Data(int zi, int luna, int an)
	{
		this->zi = zi;
		this->luna = luna;
		this->an = an;
	}

	// Constructor de copiere
	Data(const Data& a)
	{
		this->zi = a.zi;
		this->luna = a.luna;
		this->an = a.an;
	}

	// Operator de atribuire
	Data& operator=(const Data& a)
	{
		if (this != &a)
		{
			this->zi = a.zi;
			this->luna = a.luna;
			this->an = a.an;
		}
		return *this;
	}

	// Supraincarcarea operatorului >> pentru citire
	friend istream& operator>>(istream& in, Data& a)
	{
		cout << "Zi: " << endl;
		in >> a.zi;
		cout << "Luna: " << endl;
		in >> a.luna;
		cout << "An: " << endl;
		in >> a.an;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Data& a)
	{
		in >> a.zi;
		in >> a.luna;
		in >> a.an;
		return in;
	}

	// Supraincarcarea operatorului << pentru afisare
	friend ostream& operator<<(ostream& out, const Data& a)
	{
		out << a.zi << "/" << a.luna << "/" << a.an << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& o, const Data& a)
	{
		o << a.zi << endl << a.luna << endl << a.an << endl;
		return o;
	}
	void setDataPremiere(Data data, int x)
	{
		if (data.zi > 0 && data.zi < 32)
			this->zi = data.zi;
		else cout << "Ziua introdusa este invalida!" << endl;
		if (data.luna > 0 && data.luna < 13)
			this->luna = data.luna;
		else cout << "Luna introdusa este invalida!" << endl;
		if (data.an >= x && data.an < 2024)
			this->an = data.an;
		else cout << "Anul introdus este invalid!" << endl;
	}
	int getZi()
	{
		return zi;
	}
	int getLuna()
	{
		return luna;
	}
	int getAn()
	{
		return an;
	}
};
class FilmPremiat : public Film
{
protected:
	string premiu;
	Data dataPremiere;
public:
	// constructor fara parametri
	FilmPremiat() : Film()
	{
		premiu = "PREMIU";
	}

	// constructor cu parametri
	FilmPremiat(int id, const char* denumire, string gen, long int buget, Durata durata, string producator, Distributie distributie, string regizor, int anAparitie, string premiu, Data dataPremiere)
		: Film(id, denumire, gen, buget, durata, producator, distributie, regizor, anAparitie)
	{
		this->premiu = premiu;
		this->dataPremiere = dataPremiere;
	}

	// destructor
	~FilmPremiat() {}

	// constructor de copiere
	FilmPremiat(const FilmPremiat& fp) : Film(fp)
	{
		this->premiu = fp.premiu;
		this->dataPremiere = fp.dataPremiere;
	}

	// operator de atribuire
	FilmPremiat& operator=(const FilmPremiat& fp)
	{
		if (this != &fp)
		{
			Film::operator=(fp);
			this->premiu = fp.premiu;
			this->dataPremiere = fp.dataPremiere;
		}
		return *this;
	}

	// getter pentru premiu
	string getPremiu()
	{
		return premiu;
	}
	//getter pentru dataPremiere
	Data getDataPremiere()
	{
		return dataPremiere;
	}
	//setter pentru dataPremiere
	void setDataPremiere(Data data)
	{
		int x = this->getAnAparitie();
		this->dataPremiere.setDataPremiere(data, x);
	}

	void timpPanaLaPremiere()
	{
		if (this->anAparitie == this->dataPremiere.getAn())
			cout << endl << "Filmul " << this->getDenumire() << " a fost premiat in acelasi an in care a fost lansat." << endl;
		else {
			cout << endl << "Filmul " << this->getDenumire() << " a fost premiat ";
			if (this->dataPremiere.getAn() - this->anAparitie == 1)
				cout << "la un an dupa lansare." << endl;
			else
				cout << "dupa " << this->dataPremiere.getAn() - this->anAparitie << " ani de la lansare" << endl;
		}
	}
	// setter pentru premiu
	void setPremiu(string premiu)
	{
		this->premiu = premiu;
	}
	friend ostream& operator<<(ostream& o, const FilmPremiat& a)
	{
		o << (Film)a;
		o << "Premiu castigat: " << a.premiu << endl;
		o << "Data acordarii premiului:" << a.dataPremiere;
		return o;
	}
	friend istream& operator>>(istream& in, FilmPremiat& a)
	{
		in >> (Film&)a;
		cout << "Premiul castigat este: " << endl;
		getline(in, a.premiu);
		cout << "Data acordarii premiului(DD/MM/YYYY)" << endl;
		in >> a.dataPremiere;
		return in;
	}
	friend ofstream& operator<<(ofstream& o, const FilmPremiat& a)
	{
		o << (Film)a;
		o << a.premiu << endl;
		o << a.dataPremiere;
		return o;
	}
	friend ifstream& operator>>(ifstream& in, FilmPremiat& a)
	{
		in >> (Film&)a;
		in.ignore();
		getline(in, a.premiu);
		in >> a.dataPremiere;
		return in;
	}
	bool ScriereBinara(ofstream& f)
	{
		size_t n = strlen(denumire);
		f.write((char*)&n, sizeof(n));
		f.write(denumire, n + 1);             //denumire

		f.write((char*)&id, sizeof(id));     //id
		f.write((char*)&anAparitie, sizeof(anAparitie));//an
		n = gen.size();
		f.write((char*)&n, sizeof(n));
		f.write(gen.data(), n);                   //gen
		n = regizor.size();
		f.write((char*)&n, sizeof(n));
		f.write(regizor.data(), n);          //regizor
		n = producator.size();
		f.write((char*)&n, sizeof(n));
		f.write(producator.data(), n);    //producator
		f.write((char*)&buget, sizeof(buget));              //buget
		f.write((char*)&durata, sizeof(Durata));        //durata    
		n = premiu.size();
		f.write((char*)&n, sizeof(n));
		f.write(premiu.data(), n);                       //premiu
		f.write((char*)&dataPremiere, sizeof(Data));
		if (f.good() && distributie.ScriereBinara(f))     //distributie    
		{
			return true;
		}
		else return false;
	}
	bool CitireBinara(ifstream& f)
	{
		size_t n;
		f.read((char*)&n, sizeof(n));
		delete[] denumire;
		denumire = new char[n + 1];
		f.read(denumire, n + 1);
		//denumire[n] = '\0';

		f.read((char*)&id, sizeof(id));

		f.read((char*)&anAparitie, sizeof(anAparitie));
		f.read((char*)&n, sizeof(n));
		gen.resize(n);
		f.read(&gen[0], n);
		f.read((char*)&n, sizeof(n));
		regizor.resize(n);
		f.read(&regizor[0], n);
		f.read((char*)&n, sizeof(n));
		producator.resize(n);
		f.read(&producator[0], n);
		f.read((char*)&buget, sizeof(buget));
		f.read((char*)&durata, sizeof(Durata));
		f.read((char*)&n, sizeof(n));
		premiu.resize(n);
		f.read(&premiu[0], n);
		f.read((char*)&dataPremiere, sizeof(Data));
		if (f.good() && distributie.CitireBinara(f))
		{
			return true;
		}
		else return false;
	}
};*/

int main()
{
	//Testare metode din clasa principala Film
	Film film1;
	Film film2(2, "Titanic", "Drama", 200'000'000, Durata(3, 15), "20th Century Fox, Paramount Pictures,Lightstorm Entertainment", Distributie(11, new string[11]{ "Leonardo DiCaprio","Kate Winslet","Billy Zane","Kathy Bates","Frances Fisher","Victor Garber","Bernard Hill","Jonathan Hyde","Danny Nucci","David Warner","Bill Paxton" }), "James Cameron", 1997);
	Film film3;
	Film film4;
	cout << film2;
	//cin >> film4;
	cout << film4;

	//Testare setteri
	film1.setId(20);
	try {
		film1.setDenumire("Inception");
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	film1.setAnAparitie(2010);
	film1.setBuget(160'000'000);
	film1.setGen("SF");
	film1.setProducator("Warner Bros. Pictures");
	film1.setRegizor("Christopher Nolan");
	film1.setDurata(Durata(2, 28));
	film1.setDistributie(Distributie(9, new string[9]{ "Leonardo DiCaprio","Ken Watanabe","Joseph Gordon-Levitt","Ellen Page","Marion Cotillard","Tom Hardy","Cillian Murphy","Tom Berenger","Michael Caine" }));
	try {
		film1.setDenumire("X");
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << film1;


	film1.marimeBuget();
	film1.aAparutPrimul(film2);
	if (film2 > film1) {
		cout << "Filmul " << film2.getDenumire() << " este mai lung decat filmul " << film1.getDenumire() << " cu " << film2 - film1 << " minute." << endl;
	}
	if (film1 < film2) {
		cout << "Filmul " << film1.getDenumire() << " este mai scurt decat filmul " << film2.getDenumire() << " cu " << film2 - film1 << " minute." << endl;
	}
	film3.setDurata(Durata(2, 28));
	try {
		film3.setDenumire("Avatar");
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	if (film1 == film3 || film1.MinuteTotale() == film3.MinuteTotale()) {
		cout << "Filmul " << film1.getDenumire() << " are aceeasi lungime cu filmul " << film3.getDenumire() << "." << endl;
	}
	cout << "Filmul " << film1.getDenumire() << " are " << film1.MinuteTotale() << " minute." << endl;
	film3.setBuget(500'000);
	cout << "Bugetul filmului " << film3.getDenumire() << " exprimat in milioane euro este de " << float(film3) << " mil EUR." << endl;
	cout << "Bugetul filmului " << film3.getDenumire() << " este de " << string(film3) << " EUR." << endl;
	try {
		cout << "Primul actor este " << film2[0] << "." << endl;
	}
	catch (int x)
	{
		if (x == 1)
			cout << "Numarul introdus se afla in afara limitelor indexului!" << endl;
	}
	try {
		cout << film2[11] << endl;
	}
	catch (int x)
	{
		if (x == 1)
			cout << "Numarul introdus se afla in afara limitelor indexului!" << endl;
	}
	cout << "Bugetul total al filmelor " << film1.getDenumire() << ", " << film2.getDenumire() << " si " << film3.getDenumire() << " este de " << film1 + film2 + film3 << " EUR." << endl;
	cout << "Bugetul total al filmelor " << film1.getDenumire() << ", " << film2.getDenumire() << " si " << film3.getDenumire() << " este de " << float(film1) + float(film2) + float(film3) << " mil EUR." << endl;
	cout << "Bugetul filmului " << film1.getDenumire() << " inainte de marire: " << float(film1) << " mil EUR." << endl;
	1'000'000 + film1;
	film1 + 1'000'000;
	cout << "Bugetul filmului " << film1.getDenumire() << " dupa marire: " << float(film1) << " mil EUR." << endl;
	cout << film2.getId() << endl << film2.getDenumire() << endl << film2.getGen() << endl << film2.getAnAparitie() << endl << film2.getBuget() << endl << film2.getProducator() << endl << film2.getRegizor() << endl << film2.getDurata() << film2.getDistributie() << endl;

	//Scriere in fisier text
	ofstream file("Filme.txt");
	file << film2;
	file.close();

	//Citire din fisier text
	ifstream file1("Filme.txt");
	file1 >> film3;
	file1.close();
	cout << film3;

	//Scriere biara in fisier 
	ofstream fis("Filme.dat", ios::binary | ios::out);
	if (fis.is_open())
	{
		if (film2.ScriereBinara(fis))
		{
			cout << endl << "Scrierea a avut succes!" << endl;
		}
		else
		{
			cout << endl << "Scrierea nu a reusit!" << endl;
		}
		fis.close();
	}
	else cout << endl << "Fisierul nu a putut fi deschis!" << endl;

	//Citire binara din fisier
	ifstream fis1("Filme.dat", ios::binary | ios::in);
	if (fis1.is_open())
	{
		if (film3.CitireBinara(fis1))
		{
			cout << endl << "Citirea a avut succes!" << endl;
		}
		else
		{
			cout << endl << "Citirea nu a reusit!" << endl;
		}
		fis1.close();
	}
	else cout << endl << "Fisierul nu a putut fi deschis!" << endl;
	cout << film3;

	//Testare metode din clasa de tip lista obiecte cu date de tip Film
	ColectieFilme<Film>a;
	//cin >> a;
	cout << a;
	try {
		cout << a[5];
	}
	catch (int x)
	{
		if (x == 1)
			cout << endl << "Numarul introdus se afla in afara limitelor indexului!" << endl;
	}

	Film f(15, "Parasite", "Black comedy thriller", 15'500'000, Durata(2, 12), "CJ Entertainment", Distributie(6, new string[6]{ "Song Kang-ho","Lee Sun-kyun","Cho Yeo-jeong","Choi Woo-shik","Park So-dam","Jang Hye-jin" }), "Bong Joon-ho", 2019);
	Film f1(16, "The Lord of the Rings:The Fellowship of the Ring", "Epic fantasy adventure", 93'000'000, Durata(2, 58), "New Line Cinema, WingNut Films", Distributie(8, new string[8]{ "Elijah Wood","Ian McKellen","Liv Tyler","Viggo Mortensen","Sean Astin","Cate Blanchett","John Rhys-Davies","Billy Boyd" }), "Peter Jackson", 2001);
	ColectieFilme<Film>colectie("Filme populare", 3, new Film[3]);
	colectie[0] = f;
	colectie[1] = film2;
	colectie[2] = f1;
	colectie.sortareCronologica();
	cout << colectie;
	colectie.sortareID();
	cout << colectie;
	colectie + film4;
	cout << colectie;
	colectie + 2;
	cout << colectie;
	colectie - 2;
	cout << colectie;
	colectie - film4;
	cout << colectie;
	cout << "Durata totala a filmelor din colectie este de " << (int)colectie.durataTotalaColectie() / 60 << " h si " << colectie.durataTotalaColectie() % 60 << " minute." << endl;
	colectie.celMaiMareBuget();

	//Testare lista de obiecte cu date de tip int
	ColectieFilme<int>d;
	//cin >> d;
	cout << d;
	//d[0] = 15;
	cout << d;

	//Testare lista de obiecte cu date de tip string
	ColectieFilme<string>s;
	cin >> s;
	cout << s;
	s[0] = "proiect";
	cout << s;

	//codul in care clasa derivata si toate metodele acesteia sunt testate
	/*
	FilmPremiat filmP1;
	FilmPremiat filmP(2, "Titanic", "Drama", 200'000'000, Durata(3, 15), "20th Century Fox, Paramount Pictures,Lightstorm Entertainment", Distributie(11, new string[11]{ "Leonardo DiCaprio","Kate Winslet","Billy Zane","Kathy Bates","Frances Fisher","Victor Garber","Bernard Hill","Jonathan Hyde","Danny Nucci","David Warner","Bill Paxton" }), "James Cameron", 1997, "Oscar", Data(15, 06, 1998));
	cin >> filmP1;
	FilmPremiat filmP2;
	FilmPremiat filmP3;
	cout << filmP;
	cout << filmP1;
	filmP2.setId(5);
	try {
		filmP2.setDenumire("Dune");
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	filmP2.setAnAparitie(2021);
	filmP2.setBuget(165'000'000);
	filmP2.setGen("SF");
	filmP2.setProducator("Warner Bros. Pictures");
	filmP2.setRegizor("Denis Villeneuve");
	filmP2.setDurata(Durata(2, 36));
	filmP2.setDistributie(Distributie(8, new string[8]{ "Timothée Chalamet","Rebecca Ferguson","Oscar Isaac","Josh Brolin","Stellan Skarsgård","Dave Bautista","Stephen McKinley Henderson","Zendaya" }));
	filmP2.setPremiu("Oscar");
	filmP2.setDataPremiere(Data(16, 05, 2021));
	cout << endl << filmP2.getId() << endl << filmP2.getDenumire() << endl << filmP2.getGen() << endl << filmP2.getAnAparitie() << endl << filmP2.getBuget() << endl << filmP2.getProducator() << endl << filmP2.getRegizor() << endl << filmP2.getDurata() << filmP2.getDistributie() << endl << filmP2.getPremiu() << endl << filmP2.getDataPremiere();
	filmP.marimeBuget();
	filmP.aAparutPrimul(filmP2);
	if (filmP > filmP2) {
		cout << "Filmul " << filmP.getDenumire() << " este mai lung decat filmul " << filmP2.getDenumire() << " cu " << filmP - filmP2 << " minute." << endl;
	}
	if (filmP2 < filmP) {
		cout << "Filmul " << filmP2.getDenumire() << " este mai scurt decat filmul " << filmP.getDenumire() << " cu " << filmP - filmP2 << " minute." << endl;
	}
	cout << "Filmul " << filmP.getDenumire() << " are " << filmP.MinuteTotale() << " minute." << endl;
	cout << "Bugetul filmului " << filmP.getDenumire() << " exprimat in milioane euro este de " << float(filmP) << " mil EUR." << endl;
	cout << "Bugetul filmului " << filmP.getDenumire() << " este de " << string(filmP) << " EUR." << endl;
	try {
		cout << "Primul actor este " << filmP[0] << "." << endl;
	}
	catch (int x)
	{
		if (x == 1)
			cout << "Numarul introdus se afla in afara limitelor indexului!" << endl;
	}
	try {
		cout << filmP[11] << endl;
	}
	catch (int x)
	{
		if (x == 1)
			cout << "Numarul introdus se afla in afara limitelor indexului!" << endl;
	}
	cout << "Bugetul total al filmelor " << filmP.getDenumire() << ", " << filmP1.getDenumire() << " si " << filmP2.getDenumire() << " este de " << filmP + filmP2 + filmP1 << " EUR." << endl;
	cout << "Bugetul total al filmelor " << filmP.getDenumire() << ", " << filmP1.getDenumire() << " si " << filmP2.getDenumire() << " este de " << (float(filmP) + float(filmP1)) + float(filmP2) << " mil EUR." << endl;
	cout << "Bugetul filmului " << filmP.getDenumire() << " inainte de marire: " << float(filmP) << " mil EUR." << endl;
	1'000'000 + filmP;
	filmP + 1'000'000;
	cout << "Bugetul filmului " << filmP.getDenumire() << " dupa marire: " << float(filmP) << " mil EUR." << endl;
	filmP.timpPanaLaPremiere();

	ofstream out("FilmePremiate.txt");
	out << filmP;
	out.close();

	ifstream in("FilmePremiate.txt");
	in >> filmP1;
	in.close();
	cout << filmP1;
	Film* f = &filmP2;      //Evidentiere virtualizare
	f->timpPanaLaPremiere();
	ofstream out1("FilmePremiate.dat", ios::binary | ios::out);
	if (out1.is_open())
	{
		if (f->ScriereBinara(out1))
		{
			cout << endl << "Scrierea a avut succes!" << endl;
		}
		else
		{
			cout << endl << "Scrierea nu a reusit!" << endl;
		}
		out1.close();
	}
	else cout << endl << "Fisierul nu a putut fi deschis!" << endl;

	f = &filmP3;
	ifstream in1("FilmePremiate.dat", ios::binary | ios::in);
	if (in1.is_open())
	{
		if (f->CitireBinara(in1))
		{
			cout << endl << "Citirea a avut succes!" << endl;
		}
		else
		{
			cout << endl << "Citirea nu a reusit!" << endl;
		}
		in1.close();
	}
	else cout << endl << "Fisierul nu a putut fi deschis!" << endl;
	cout << filmP3;*/

//Testare  containere din biblioteca STL
	vector<Film> vector_filme;
	vector_filme.push_back(colectie[0]);
	vector_filme.push_back(colectie[1]);
	vector_filme.push_back(colectie[2]);
	vector_filme.push_back(film4);
	vector_filme.push_back(film1);
	vector_filme.pop_back();
	for (int i = 0;i < vector_filme.size();i++)
		cout << vector_filme[i] << endl;

	map<string, Film> map_filme;
	map_filme["Primul"] = colectie[0];
	map_filme["Al doilea"] = colectie[1];
	map_filme["Al treilea"] = colectie[2];
	map_filme["Al patrulea"] = film4;
	map_filme["Al cincilea"] = film1;
	cout << map_filme["Al treilea"];


	stack<Film> stack_filme;
	stack_filme.push(colectie[0]);
	stack_filme.push(colectie[2]);
	stack_filme.push(colectie[1]);
	stack_filme.push(film1);
	stack_filme.push(film4);

	while (!stack_filme.empty()) {
		cout << stack_filme.top() << endl;
		stack_filme.pop();
	}
	return 0;
}

