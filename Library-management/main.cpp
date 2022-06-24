#include "LIBRARY.h"
#include "READER.h"
#include "BOOK.h"
#include "RECEIPT.h"
#include "STATISTIC.h"

void main(int argc, char** argv)
{
	User U;
	ReceiptList Re;
	ReadList RL;
	BookList BL;
	FILE* fuser = fopen("user.csv", "rt");
	FILE* freader = fopen("reader.csv", "rt");
	readListReader(freader, RL);
	FILE* fbook = fopen("book.csv", "rt");
	readListBook(fbook, BL);
	FILE* freceipt = fopen("receipt.csv", "rt");
	readListReceipt(freceipt, Re);

	int x, run, log;
	bool tf = true;
	do {
		system("cls");
		printf("=================================== THU VIEN TRUONG DAI HOC KHOA HOC TU NHIEN TP.HCM ===================================\n");
		printf("1.Dang nhap\n0.Thoat chuong trinh.\n");
		printf("Chon: ");
		scanf("%d", &x);
		switch (x)
		{
		case 1:
			log = login(fuser, U);
			if (log == 0) {
				printf("Ten dang nhap hoac mat khau khong dung!\n");
				system("pause");
				break;
			}
			else if (log == 1)
			{
				printf("Tai khoan cua ban da bi khoa, lien he quan ly hoac chuyen vien de duoc ho tro!\n");
				system("pause");
				break;
			}
			else {
				if (U.classify == 9)
				{
					do {
						system("cls");
						printf("=============================== MENU ===============================\n");
						printf("1.Cai dat chung - nguoi dung\n");
						printf("2.Quan li doc gia\n");
						printf("3.Quan li sach\n");
						printf("4.Lap phieu muon sach\n");
						printf("5.Lap phieu tra sach\n");
						printf("6.Cac thong ke co ban\n");
						printf("0.Dang xuat.\n");
						printf("Chon: ");
						scanf("%d", &run);
						switch (run)
						{
						case 1:
							chucNang1Admin(fuser, U, log);
							break;
						case 2:
							//ghi ReadList vao file sau ham nay
							chucNang2AdminnManager(RL, U, log);
							break;
						case 3:
							//ghi BookList vao file sau ham nay
							chucNang3AdminnManager(BL, U, log);
							break;
						case 4:
							borrowBook(RL, BL, Re);
							break;
						case 5:
							char temp[MAX_CHAR];
							int a;
							printf("Nhap ma doc gia (ID): ");
							scanf("%s", temp);
							printf("Doc gia co lam mat sach khong?\n0.Khong		1.Co\n");
							printf("Chon: ");
							scanf("%d", &a);
							outputRetReceipt(BL, Re, temp, a);
							break;
						case 6:
							chucNang6(BL, Re, RL, log, U);
							break;
						case 0:
							log = false;
							break;
						default:
							break;
						}
						system("pause");
					} while (log);
				}
				else if (U.classify == 0)
				{
					//ham chuc nang cua quan li
					do {
						system("cls");
						printf("=============================== MENU ===============================\n");
						printf("1.Cai dat chung - nguoi dung\n");
						printf("2.Quan li doc gia\n");
						printf("3.Quan li sach\n");
						printf("4.Lap phieu muon sach\n");
						printf("5.Lap phieu tra sach\n");
						printf("6.Cac thong ke co ban\n");
						printf("0.Dang xuat.\n");
						printf("Chon: ");
						scanf("%d", &run);
						switch (run)
						{
						case 1:
							chucNang1ManagernLibrarian(fuser, U, log);
							break;
						case 2:
							//ghi ReadList vao file sau ham nay
							chucNang2AdminnManager(RL, U, log);
							break;
						case 3:
							//ghi BookList vao file sau ham nay
							chucNang3AdminnManager(BL, U, log);
							break;
						case 4:
							borrowBook(RL, BL, Re);
							break;
						case 5:
							char temp[MAX_CHAR];
							int a;
							printf("Nhap ID: ");
							scanf("%s", temp);
							printf("Doc gia co lam mat sach khong?\n0.Khong		1.Co\n");
							printf("Chon: ");
							scanf("%d", &a);
							outputRetReceipt(BL, Re, temp, a);
							break;
						case 6:
							chucNang6(BL, Re, RL, log, U);
							break;
						case 0:
							log = false;
							break;
						default:
							break;
						}
						system("pause");
					} while (log);
				}
				else if (U.classify == 1)
				{
					//ham chuc nang chuyen vien
					do {
						system("cls");
						printf("=============================== MENU ===============================\n");
						printf("1.Cai dat chung - nguoi dung\n");
						printf("2.Quan li doc gia\n");
						printf("3.Tim kiem sach\n");
						printf("4.Lap phieu muon sach\n");
						printf("5.Lap phieu tra sach\n");
						printf("0.Dang xuat.\n");
						printf("Chon: ");
						scanf("%d", &run);
						switch (run)
						{
						case 1:
							chucNang1ManagernLibrarian(fuser, U, log);
							break;
						case 2:
							//ghi ReadList vao file sau ham nay
							chucNang2Librarian(RL, U, log);
							break;
						case 3:
							//ghi BookList vao file sau ham nay
							chucNang3Librarian(BL, U, log);
							break;
						case 4:
							borrowBook(RL, BL, Re);
							break;
						case 5:
							char temp[MAX_CHAR];
							int a;
							printf("Nhap ID: ");
							scanf("%s", temp);
							printf("Doc gia co lam mat sach khong?\n0.Khong		1.Co\n");
							printf("Chon: ");
							scanf("%d", &a);
							outputRetReceipt(BL, Re, temp, a);
							break;
						case 0:
							log = false;
							break;
						default:
							break;
						}
						system("pause");
					} while (log);
				}
				//Luu nhung thay doi vao file
				freopen("book.csv", "wt", fbook);
				freopen("reader.csv", "wt", freader);
				freopen("receipt.csv", "wt", freceipt);

				writeBList(fbook, BL);
				writeRList(freader, RL);
				writeReList(freceipt, Re);

				freopen("book.csv", "rt", fbook);
				freopen("reader.csv", "rt", freader);
				freopen("receipt.csv", "rt", freceipt);
				break;
			}
		case 0:
			tf = false;
			printf("Chao tam biet va hen gap lai!");
			break;
		default: break;
		}
	} while (tf);


	removeListBook(BL);
	removeListReader(RL);
	removeListReceipt(Re);
	fclose(freceipt);
	fclose(fbook);
	fclose(freader);
}
