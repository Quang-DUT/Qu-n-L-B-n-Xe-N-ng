#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

class Xe {
private:
	string bienso, taixe;
public:
	Xe(string bienso = "", string taixe = "") : bienso(bienso), taixe(taixe) {}
	virtual void nhap() {
		cout << "Nhap bien so xe: "; getline(cin, bienso);
		cout << "Nhap ten tai xe: "; getline(cin, taixe);
	}
	virtual void xuat() {
		cout << "Bien so: " << bienso << ", Tai xe: " << taixe;
	}
	virtual void ghifile(ofstream& of) {
		of << bienso << "," << taixe << ",";
	}
	virtual ~Xe() {}
};

class Bus : public Xe {
	int soghe;
	string diemdon, diemden;
public:
	Bus(string bienso = "", string taixe = "", string diemdon = "", string diemden = "", int soghe = 0)
		: Xe(bienso, taixe), diemdon(diemdon), diemden(diemden), soghe(soghe) {
	}
	void nhap() override {
		Xe::nhap();
		cout << "Nhap diem don : "; getline(cin, diemdon);
		cout << "Nhap diem den : "; getline(cin, diemden);
		cout << "Nhap so ghe: "; cin >> soghe; cin.ignore();
	}
	void xuat() override {
		cout << "Phuong tien: Bus";
		Xe::xuat();
		cout << ", Diem don: " << diemdon << ", Diem den: " << diemden << ", So ghe: " << soghe;
	}
	void ghifile(ofstream& of) override {
		of << "Bus,";
		Xe::ghifile(of);
		of << diemdon << "," << diemden << "," << soghe << endl;
	}
};

class Taxi : public Xe {
	double km;
public:
	Taxi(string bienso = "", string taixe = "", double km = 0)
		: Xe(bienso, taixe), km(km) {
	}
	void nhap() override {
		Xe::nhap();
		cout << "Nhap so km: "; cin >> km; cin.ignore();
	}
	void xuat() override {
		cout << "Phuong tien: Taxi, ";
		Xe::xuat();
		cout << ", So km: " << km;
	}
	void ghifile(ofstream& of) override {
		of << "Taxi,";
		Xe::ghifile(of);
		of << km << endl;
	}
};

class Benxe {
	vector<Xe*> phtien;
public:
	~Benxe() {
		for (Xe* x : phtien) delete x;
	}
	void thempt() {
		int choice;
		cout << "1. Bus\n2. Taxi\nLua chon: "; cin >> choice; cin.ignore();
		Xe* v = nullptr;
		if (choice == 1) v = new Bus();
		else if (choice == 2) v = new Taxi();
		else return;
		v->nhap();
		phtien.push_back(v);
		cout << "Them thanh cong.";
		this_thread::sleep_for(chrono::seconds(2));
		system("cls");
	}
	void xuattatca() {
		for (Xe* v : phtien) {
			v->xuat();
			cout << endl << "--------------------\n";
		}
	}
	void luufile() {
		int tmp;
		cout << "Ban co muon ghi de len file!\n0. Khong\n1. Co\nChon: ";
		cin >> tmp;
		ofstream f;
		if (tmp == 0) {
			f.open("QuanLyXe.txt", ios::app);
			if (!f) {
				cout << "Khong mo duoc file de ghi!\n";
				return;
			}

		}
		if (tmp == 1) {
			f.open("QuanLyXe.txt", ios::trunc);
			if (!f) {
				cout << "Khong mo duoc file de ghi!\n";
				return;
			}

		}
		for (Xe* v : phtien) v->ghifile(f);
		f.close();
	}
	void docfile() {
		for (Xe* x : phtien) delete x;
		phtien.clear();
		ifstream file("QuanLyXe.txt");
		if (!file) {
			cout << "Khong mo duoc file!\n";
			return;
		}
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string loai;
			getline(ss, loai, ',');
			string bienso, taixe, diemdon, diemden, soghe_str, km_str;
			if (loai == "Bus") {
				getline(ss, bienso, ',');
				getline(ss, taixe, ',');
				getline(ss, diemdon, ',');
				getline(ss, diemden, ',');
				getline(ss, soghe_str, ',');
				int soghe = stoi(soghe_str);
				phtien.push_back(new Bus(bienso, taixe, diemdon, diemden, soghe));
			}
			else if (loai == "Taxi") {
				getline(ss, bienso, ',');
				getline(ss, taixe, ',');
				getline(ss, km_str, ',');
				double km = stod(km_str);
				phtien.push_back(new Taxi(bienso, taixe, km));
			}
		}
		file.close();
		cout << "Da doc file thanh cong!\n";
		xuattatca();
	}
};

int main() {
	Benxe quanly;
	int choice;
	do {
		cout << "===== Quan ly ben xe Da Nang =====\n";
		cout << "1. Them phuong tien\n2. Hien thi tat ca\n3. Luu vao file\n4. Doc tu file\n0. Thoat\nChon: ";
		cin >> choice; cin.ignore();
		switch (choice) {
		case 1: quanly.thempt(); break;
		case 2: quanly.xuattatca(); break;
		case 3:
			quanly.luufile();
			cout << "Dang tai...";
			for (int i = 0; i < 10; i++) {
				cout << "."; cout.flush();
				this_thread::sleep_for(chrono::milliseconds(100));
			}
			cout << "\nDa luu vao file QuanLyXe.txt\n";
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			break;
		case 4:
			quanly.docfile();
			break;
		}
	} while (choice != 0);

	return 0;
}
