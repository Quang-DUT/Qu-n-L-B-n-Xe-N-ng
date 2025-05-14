#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
class Xe {
private:
	string bienso, taixe;
public:
	Xe(string bienso = "", string taixe = "", string tuyenduong = "")
		:bienso(bienso), taixe(taixe){
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
		:Xe(bienso, taixe), soghe(soghe),tuyenduong(tuyenduong) {
	}
	void nhap() {
		Xe::nhap();
		cout << "Nhap tuyen duong ( Tu - Den ): "; getline(cin, tuyenduong);
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
int main()
{
	Taxi a;
	a.nhap();
	ofstream f1("QuanLyXe.txt");
	if (!f1.is_open()) {
		cout << "Khong the tao/mo file!";
		return 1;
	}
	a.ghifile(f1);
	f1.close();
	khachhang b;
	ofstream f2("QuanLyKH.txt");
	b.nhap();
	b.ghifile(f2);
	f2.close();
	return 0;
}
