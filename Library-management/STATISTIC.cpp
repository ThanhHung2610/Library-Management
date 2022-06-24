#include "STATISTIC.h"

void getCurDay(Date& d)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	d.year = 1900 + ltm->tm_year;
	d.month = 1 + ltm->tm_mon;
	d.day = ltm->tm_mday;
}

void overdueReader(ReceiptList Re, ReadList RL)
{
	int sum = 0;
	Date curDay;
	ReadNode* R;
	getCurDay(curDay);
	for (ReceiptNode* p = Re.head; p; p = p->next)
	{
		Receipt B = p->data;
		int diff = DiffDays(B.borrow.day, B.borrow.month, B.borrow.year, curDay.day, curDay.month, curDay.year);
		if (diff > 7)
		{
			R = FindRData(RL, B.ID, 3);
			printf("%-10s%-15s", B.ID, R->data.name);
			printf("	%d/%d/%d		%d/%d/%d\n", B.borrow.day, B.borrow.month, B.borrow.year, B.expReturn.day, B.expReturn.month, B.expReturn.year);
			sum++;
		}
	}
	printf("So doc gia tre han la: %d\n", sum);
}

int borBookNum(BookList BL)
{
	int sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		sum += B.BorAmount;
	}
	return sum;
}

void genderNum(ReadList RL)
{
	int sumB = 0, sumG = 0, sumD = 0;
	for (ReadNode* p = RL.head; p; p = p->next)
	{
		Reader B = p->data;
		if (strcmp(B.gender, "Nam") == 0)
			sumB++;
		if (strcmp(B.gender, "Nu") == 0)
			sumG++;
		if (strcmp(B.gender, "Khac") == 0)
			sumD++;
	}
	printf("Nam	: %d\n", sumB);
	printf("Nu	: %d\n", sumG);
	printf("Khac	: %d\n", sumD);
}

int ReaderNum(ReadList RL)
{
	int sum = 0;
	for (ReadNode* p = RL.head; p; p = p->next)
	{
		sum++;
	}
	return sum;
}

void genreNum(BookList BL)
{
	int sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		if (strcmp(B.genre, "Toan hoc") == 0)
			sum++;
	}
	printf("Toan hoc	: %d\n", sum);

	sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		if (strcmp(B.genre, "Vat ly") == 0)
			sum++;
	}
	printf("Vat ly		: %d\n", sum);

	sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		if (strcmp(B.genre, "Hoa hoc") == 0)
			sum++;
	}
	printf("Hoa hoc		: %d\n", sum);

	sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		if (strcmp(B.genre, "Sinh hoc") == 0)
			sum++;
	}
	printf("Sinh hoc	: %d\n", sum);

	sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		if (strcmp(B.genre, "Tai lieu khac") == 0)
			sum++;
	}
	printf("Tai lieu khac	: %d\n", sum);
}

int bookNum(BookList BL)
{
	int sum = 0;
	for (BookNode* p = BL.head; p; p = p->next)
	{
		Book B = p->data;
		sum += B.amount;
	}
	return sum;
}


void chucNang6(BookList BL, ReceiptList Re, ReadList RL, int& log, User& U) //danh sach doc gia tre han chua xong
{
	int run1 = -1, tf1 = 1;
	char temp[MAX_CHAR];
	do {
		system("cls");
		printf("=================================== THONG KE CO BAN ===================================\n");
		printf("1.Thong ke so luong sach trong thu vien.\n");
		printf("2.Thong ke so luong sach theo the loai.\n");
		printf("3.Thong ke so luong doc gia.\n");
		printf("4.Thong ke so luong doc gia theo gioi tinh.\n");
		printf("5.Thong ke so luong sach dang duoc muon.\n");
		printf("6.Thong ke danh sach bi tre han.\n");
		printf("7.Quay lai.\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
			system("cls");
		case 1:
			printf("So luong sach trong thu vien la: %d\n", bookNum(BL));
			break;
		case 2:
			printf("So luong sach theo the loai: \n");
			genreNum(BL);
			break;
		case 3:
			printf("So luong doc gia la: %d\n", ReaderNum(RL));
			break;
		case 4:
			printf("So luong doc gia theo gioi tinh: \n");
			genderNum(RL);
			break;
		case 5:
			printf("So luong sach dang duoc muon: %d\n", borBookNum(BL));
			break;
		case 6:
			printf("Danh sach cac doc gia bi tre han: \n");
			overdueReader(Re, RL);
			break;
		case 7:
			tf1 = 0;
			break;
		default: break;
		}
		system("pause");
	} while (tf1);

}