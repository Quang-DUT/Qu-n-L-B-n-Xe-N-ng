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
	Xe(string bienso = "", string taixe = "", string tuyenduong = "")
		:bienso(bienso), taixe(taixe) {
	}
	virtual void nhap() {
		cout << "Nhap bien so xe: "; getline(cin, bienso);
		cout << "Nhap ten tai xe: "; getline(cin, taixe);

	}
	virtual void xuat() {
		cout << "Bien so: " << bienso << ", Tai xe: " << taixe;

	};

	virtual void ghifile(ofstream& of) {
		of << bienso << ", " << taixe << ", ";
	}
};
class Bus :public Xe {
	int soghe;
	string  tuyenduong;
public:
	Bus(string bienso = "", string taixe = "", string tuyenduong = "", int soghe = 0)
		:Xe(bienso, taixe), soghe(soghe), tuyenduong(tuyenduong) {
	}
	void nhap() {
		Xe::nhap();
		cout << "Nhap tuyen duong ( diemdon - diemden ): "; getline(cin, tuyenduong);
		cout << "Nhap so ghe: "; cin >> soghe; cin.ignore();

	}
	void xuat() {
		Xe::xuat();
		cout << "So ghe: " << soghe << endl;
	}
	void ghifile(ofstream& of) {
		of << "Bus, ";
		Xe::ghifile(of);
		of << ", " << soghe << endl;
	}
};
class Taxi :public Xe {
	double km;
public:
	Taxi(string bienso = "", string taixe = "", double km = 0)
		:Xe(bienso, taixe), km(km) {
	}
	void nhap() {
		Xe::nhap();
		cout << "Nhap so km: "; cin >> km; cin.ignore();
	}
	void xuat() {
		Xe::xuat();
		cout << "So km: " << km << endl;
	}
	void ghifile(ofstream& of) {
		of << "Taxi, ";
		Xe::ghifile(of);
		of << ", " << km << endl;
	}
};
class khachhang {
	string tenkh;
	int sdt;
public:
	void nhap() {
		cout << "Nhap ho ten khach hang: "; getline(cin, tenkh);
		cout << "Nhap so dien thoai khach hang: "; cin >> sdt; cin.ignore();
	}
	void xuat() {
		cout << "Ho ten: " << tenkh << endl;
		cout << "Dien thoai: " << sdt << endl;
	}
	void ghifile(ofstream& of) {
		of << tenkh << "," << sdt;
	}
};
class Benxe {
	vector<Xe*> phtien;
public:
	~Benxe() {
		for (Xe* x : phtien)
			delete x;
	}
	void thempt() {
		int choice;
		cout << "1.Bus\n2.Taxi\nLua chon: "; cin >> choice; cin.ignore();
		Xe* v;
		if (choice == 1)
			v = new Bus();
		else if (choice == 2)
			v = new Taxi();
		else return;
		v->nhap();
		phtien.push_back(v);
	}
	void xuattatca() {
		for (Xe* v : phtien) {
			v->xuat();
			cout << "--------------------\n";
		}
	}
	void luufile() {
		ofstream f("QuanLyXe.txt");
		for (Xe* v : phtien) {
			v->ghifile(f);
			f.close();
		}
	}

};
int main()
{
	Benxe quanly;
	int choice;
	do {
		cout << "===== Quan ly ben xe Da Nang =====\n";
		cout << "1. Them phuong tien\n2. Hien thi tat ca\n3. Luu vao file\n0. Thoat\nChon: ";
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case 1: quanly.thempt(); break;
		case 2: quanly.xuattatca(); break;
		case 3: {
			quanly.luufile();
			cout << "Dang tai...";
			for (int i = 0; i < 10; i++) {
				cout << ".";
				cout.flush();
				this_thread::sleep_for(chrono::milliseconds(100));
			}
			cout << "\nDa luu vao file QuanLyXe.txt\n";
			break;
		}
		}
	} while (choice != 0);

	return 0;
}
