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
	string bienso, taixe, loai;
	int stt;
	static int i;
public:
	Xe(string loai = "Xe", string bienso = "", string taixe = "")
		: bienso(bienso), taixe(taixe), loai(loai) {
		i++;
		stt = i;
	}
	virtual void nhap() {
		cout << "Nhap bien so xe: "; getline(cin, bienso);
		cout << "Nhap ten tai xe: "; getline(cin, taixe);
	}
	virtual void xuat() {
		cout << stt << ": " << loai << " - ";
		cout << "Bien so: " << bienso << ", Tai xe: " << taixe;
	}
	virtual void ghifile(ofstream& of) {
		of << bienso << "," << taixe << ",";
	}
	virtual ~Xe() {
		i--;
	}

	string get_loai() {
		return loai;
	}
	string get_bienso() { return bienso; }
	int get_stt() { return stt; }
	static int get_i() { return i; }
	static void set_i(int new_i) { i = new_i; }
	void set_stt(int new_stt) { stt = new_stt; }
	void set_bienso(string newbienso) { bienso = newbienso; }
	void set_taixe(string newtaixe) { taixe = newtaixe; }
};
int Xe::i = 0;

class Bus : public Xe {
	int soghe;
	string diemdon, diemden;
public:

	Bus(string bienso = "", string taixe = "", string diemdon = "", string diemden = "", int soghe = 0)
		: Xe("Bus", bienso, taixe), diemdon(diemdon), diemden(diemden), soghe(soghe) {
	}
	void nhap() override {
		Xe::nhap();
		cout << "Nhap diem don : "; getline(cin, diemdon);
		cout << "Nhap diem den : "; getline(cin, diemden);
		cout << "Nhap so ghe: "; cin >> soghe; cin.ignore();
	}
	void xuat() override {

		Xe::xuat();
		cout << ", Diem don: " << diemdon << ", Diem den: " << diemden << ", So ghe: " << soghe;
	}
	void ghifile(ofstream& of) override {
		of << "Bus,";
		Xe::ghifile(of);
		of << diemdon << "," << diemden << "," << soghe << endl;
	}
	~Bus() {}
	void set_soghe(int newsoghe) { soghe = newsoghe; }
	void set_diemdon(string newdiemdon) { diemdon = newdiemdon; }
	void set_diemden(string newdiemden) { diemden = newdiemden; }
};

class Taxi : public Xe {
	string tenxe;
public:
	Taxi(string bienso = "", string taixe = "", string tenxe = "")
		: Xe("Taxi", bienso, taixe), tenxe(tenxe) {
	}
	void nhap() override {
		Xe::nhap();
		cout << "Nhap ten xe: "; getline(cin, tenxe);
	}
	void xuat() override {

		Xe::xuat();
		cout << ", Ten xe: " << tenxe;
	}
	void ghifile(ofstream& of) override {
		of << "Taxi,";
		Xe::ghifile(of);
		of << tenxe << endl;
	}
	~Taxi() {}
	void set_tenxe(string newtenxe) { tenxe = newtenxe; }
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
		cout << "Dang tai...";
		for (int i = 0; i < 10; i++) {
			cout << "."; cout.flush();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		cout << "\nDa luu vao file QuanLyXe.txt\n";
		this_thread::sleep_for(chrono::seconds(2));
		system("cls");
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
			string bienso, taixe, diemdon, diemden, soghe_str, tenxe;
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
				getline(ss, tenxe, ',');
				phtien.push_back(new Taxi(bienso, taixe, tenxe));
			}
		}
		file.close();
		cout << "Da doc file thanh cong!\n";
		xuattatca();
	}
	void timkiem_bienso(string bien) {

		bool kt = false;
		for (Xe* v : phtien) {
			if (v->get_bienso() == bien) {
				v->xuat();
				cout << endl;
				kt = true;
			}
		}
		if (!kt) cout << "Khong tim thay phuong tien voi bien so tren.\n";
	}
	void xoatheostt(int stt_xoa) {
		bool kt = false;
		for (auto it = phtien.begin(); it != phtien.end(); ++it) {
			if ((*it)->get_stt() == stt_xoa) {
				delete* it;
				phtien.erase(it);
				kt = true;
				cout << "Da xoa phuong tien co STT " << stt_xoa << " thanh cong!\n\n";
				capnhatSTT();
				break;
			}
		}
		if (!kt) {
			cout << "Khong tim thay xe voi STT:  '" << stt_xoa << "'!\n\n";
		}

	}
	void xoabienso(const string& bien) {
		bool kt = false;
		for (auto it = phtien.begin(); it != phtien.end(); ++it) {
			if ((*it)->get_bienso() == bien) {
				delete* it;
				it = phtien.erase(it);
				kt = true;
				cout << "Da xoa xe co bien so '" << bien << "' thanh cong!\n\n";
				cout << endl;
				capnhatSTT();
				break;
			}
		}

		if (!kt) {
			cout << "Khong tim thay xe voi bien so: '" << bien << "'!\n\n";
		}

	}
	void capnhatSTT() {
		for (size_t i = 0; i < phtien.size(); i++) {
			phtien[i]->set_stt(i + 1);
		}
		Xe::set_i(phtien.size());
	}
	void suaThongTin() {
		system("cls");
		if (phtien.empty()) {
			cout << "Danh sach phuong tien rong!\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		int stt_sua;
		Xe* xe_sua = nullptr;

		cout << "Thong tin hien tai:\n";
		xuattatca();

		cout << "Chon STT can sua thong tin: ";
		cin >> stt_sua;
		cin.ignore();
		for (Xe* x : phtien) {
			if (x->get_stt() == stt_sua) {
				xe_sua = x;
				break;
			}
		}
		if (xe_sua == nullptr) {
			cout << "Khong tim thay phuong tien voi STT " << stt_sua << "!\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}

		system("cls");

		xe_sua->xuat();
		cout << endl;
		int luachonSua;
		cout << "Chon thong tin can sua:\n";
		cout << "1. Bien so\n2. Ten tai xe\n";
		if (xe_sua->get_loai() == "Bus") {
			cout << "3. Diem don\n4. Diem den\n5. So ghe\n";
		}
		else if (xe_sua->get_loai() == "Taxi") {
			cout << "3. Ten xe\n";
		}
		cout << "Chon: ";
		cin >> luachonSua;
		cin.ignore();
		switch (luachonSua) {
		case 1: {
			string newbienSo;
			cout << "Nhap bien so moi: ";
			getline(cin, newbienSo);
			xe_sua->set_bienso(newbienSo);
			cout << "Da cap nhat bien so!\n";
			break;
		}
		case 2: {
			string newtaiXe;
			cout << "Nhap ten tai xe moi: ";
			getline(cin, newtaiXe);
			xe_sua->set_taixe(newtaiXe);
			cout << "Da cap nhat ten tai xe!\n";
			break;
		}
		case 3: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				string newDiemDon;
				cout << "Nhap diem don moi: ";
				getline(cin, newDiemDon);
				cout << "Da cap nhat diem don!\n";
			}
			else if (xe_sua->get_loai() == "Taxi") {
				Taxi* taxi = dynamic_cast<Taxi*>(xe_sua);
				string newtenxe;
				cout << "Nhap ten xe moi: ";
				getline(cin, newtenxe);
				taxi->set_tenxe(newtenxe);
				cout << "Da cap nhat ten xe!\n";
			}
			break;
		}
		case 4: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				string newdiemden;
				cout << "Nhap diem den moi: ";
				getline(cin, newdiemden);
				bus->set_diemden(newdiemden);
				cout << "Da cap nhat diem den!\n";
			}
			break;
		}
		case 5: {
			if (xe_sua->get_loai() == "Bus") {
				Bus* bus = dynamic_cast<Bus*>(xe_sua);
				int newsoghe;
				cout << "Nhap so ghe moi: ";
				cin >> newsoghe;
				cin.ignore();
				bus->set_soghe(newsoghe);
				cout << "Da cap nhat so ghe!\n";
			}
			break;
		}
		default:
			cout << "Lua chon khong hop le!\n";
		}
	}
};



int main() {
	Benxe quanly;
	int choice;
	do {
		cout << "===== Quan ly ben xe Da Nang =====\n";
		cout << "1. Them phuong tien\n";
		cout << "2.Hien thi tat ca\n";
		cout << "3.Luu vao file\n";
		cout << "4.Doc tu file\n";
		cout << "5.Tim kiem phuong tien\n";
		cout << "6.Xoa phuong tien\n";
		cout << "7.Sua thong tin phuong tien\n";
		cout << "0.Thoat\n";
		cout << "Chon: ";
		cin >> choice; cin.ignore();
		switch (choice) {
		case 1: quanly.thempt(); break;
		case 2: quanly.xuattatca(); break;
		case 3: quanly.luufile(); break;
		case 4:quanly.docfile(); break;
		case 5: {
			string bien;
			cout << "Nhap bien so can tim: ";
			getline(cin, bien);
			quanly.timkiem_bienso(bien); break;
		}
		case 6: {
			int tmp_xoa;
			cout << "1. Xoa theo so thu tu ( In danh sach )\n2. Xoa theo bien so\nChon: ";
			cin >> tmp_xoa; cin.ignore();
			if (tmp_xoa == 1) {
				quanly.xuattatca();
				cout << endl;
				int stt_xoa;
				cout << "Nhap stt can xoa: "; cin >> stt_xoa;
				quanly.xoatheostt(stt_xoa);
			}
			else if (tmp_xoa == 2) {
				string bien;
				cout << "Nhap bien so can xoa: ";
				getline(cin, bien);
				quanly.xoabienso(bien);
				cout << endl;
			}
			else break;
			break;
		}
		case 7: quanly.suaThongTin(); break;
		}
	} while (choice != 0);
	return 0;
}
