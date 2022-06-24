#include "RECEIPT.h"

bool checkAvaiBook(Book B)
{
	if (B.BorAmount == B.amount)
		return false;
	return true;
}

void borrowBook(ReadList RL, BookList& BL, ReceiptList& ReL)
{
	Receipt B;
	char temp[MAX_CHAR];
	initMatrix(B.ISBN);
	system("cls");
	printf("===================================== NHAP PHIEU MUON SACH =====================================\n");
	printf("Nhap ma doc gia: ");
	scanf("%s", temp);
	StaticToDynamic(B.ID, temp);
	while (!FindRData(RL, B.ID, 3)) {
		printf("Ma doc gia khong ton tai!\n");
		printf("Nhap lai ma doc gia: ");
		scanf("%s", B.ID);
	}
	if (checkBorReader(ReL, B.ID))
	{
		printf("Doc gia nay dang muon sach roi! Hay tra sach truoc roi muon tiep.\n");
		return;
	}

	printf("Nhap ngay muon (ngay/thang/nam): ");
	scanf("%d/%d/%d", &B.borrow.day, &B.borrow.month, &B.borrow.year);
	while (!IsValidDay(B.borrow.day, B.borrow.month, B.borrow.year))
	{
		printf("Ngay khong hop le, vui long nhap lai: ");
		scanf("%d/%d/%d", &B.borrow.day, &B.borrow.month, &B.borrow.year);
	}

	printf("Nhap ngay tra du kien (ngay/thang/nam): ");
	scanf("%d/%d/%d", &B.expReturn.day, &B.expReturn.month, &B.expReturn.year);
	int diff = DiffDays(B.borrow.day, B.borrow.month, B.borrow.year, B.expReturn.day, B.expReturn.month, B.expReturn.year);
	while (!IsValidDay(B.expReturn.day, B.expReturn.month, B.expReturn.year) || diff > 7 || diff < 0)
	{
		printf("Khong hop le (Chi duoc muon toi da 7 ngay), vui long nhap lai: ");
		scanf("%d/%d/%d", &B.expReturn.day, &B.expReturn.month, &B.expReturn.year);
		diff = DiffDays(B.borrow.day, B.borrow.month, B.borrow.year, B.expReturn.day, B.expReturn.month, B.expReturn.year);
	}
	int x, i = 0;
	printf("Nhap danh sach ISBN (nhap \"done\" de ket thuc viec nhap)\n");
	do {
		scanf("%s", temp);
		x = _stricmp(temp, "done");
		if (x == 0) break;

		BookNode* b = FindBData(BL, temp, 2);
		if (b && b->data.BorAmount < b->data.amount)
		{
			for (int j = 0; j < 9; j++)
			{
				B.ISBN[i][j] = temp[j];
			}
			i++;
			b->data.BorAmount++;
		}
		else
		{
			printf("Khong co cuon sach nay!\n");
			printf("Nhap lai: ");
		}
	} while (x);

	AddTailReceipt(ReL, B);
	outputBorReceipt(B);
}
void initMatrix(char ISBN[20][9])
{
	for (int i = 0; i < 20; i++)
	{
		ISBN[i][0] = '0';
		ISBN[i][1] = '\0';
	}
}

void writeReceipt(FILE* fw, Receipt B)
{
	fprintf(fw, "%s,", B.ID);
	fprintf(fw, "%d/%d/%d,", B.borrow.day, B.borrow.month, B.borrow.year);
	fprintf(fw, "%d/%d/%d,", B.expReturn.day, B.expReturn.month, B.expReturn.year);
	int i = 0;
	while (B.ISBN[i + 1][1] != '\0')
	{
		fprintf(fw, "%s,", B.ISBN[i]);
		i++;
	}
	fprintf(fw, "%s\n", B.ISBN[i]);
}

void writeReList(FILE* fw, ReceiptList RL)
{
	freopen("receipt.csv", "wt", fw);
	for (ReceiptNode* p = RL.head; p; p = p->next)
	{
		writeReceipt(fw, p->data);
	}
}

void readReceipt(FILE* fr, Receipt& Re)
{
	initMatrix(Re.ISBN);
	char temp[MAX_CHAR], c;
	int i = 0;
	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(Re.ID, temp);

	fscanf(fr, "%d/%d/%d,", &Re.borrow.day, &Re.borrow.month, &Re.borrow.year);

	fscanf(fr, "%d/%d/%d,", &Re.expReturn.day, &Re.expReturn.month, &Re.expReturn.year);
	do {
		for (int k = 0; k < MAX_ISBN; k++)
		{
			temp[k] = fgetc(fr);
		}
		temp[MAX_ISBN] = '\0';
		for (int j = 0; j < MAX_ISBN + 1; j++)
		{
			Re.ISBN[i][j] = temp[j];
		}
		i++;
		c = fgetc(fr);
	} while (c != '\n' && c != EOF);
	fscanf(fr, "\n");
}


void removeReceipt(Receipt& B)
{
	delete[] B.ID;
	B.ID = NULL;
}

bool checkEmptyReList(ReceiptList L)
{
	return !L.head;
}
ReceiptNode* FindReData(ReceiptList L, char data[])
{
	for (ReceiptNode* p = L.head; p; p = p->next)
	{
		if (strcmp(p->data.ID, data) == 0)
			return p;
	}
	return NULL;
}
void RemoveReHead(ReceiptList& L)
{
	if (checkEmptyReList(L)) return;
	ReceiptNode* temp = L.head;
	removeReceipt(temp->data);
	L.head = temp->next;
	if (L.head != NULL) L.head->prev = NULL;
	delete temp;
}
void RemoveReTail(ReceiptList& L)
{
	if (checkEmptyReList(L)) return;
	ReceiptNode* temp = L.tail;
	removeReceipt(temp->data);
	L.tail = temp->prev;
	if (L.tail)
		L.tail->next = NULL;
	else
	{
		L.head = NULL;
	}
	delete temp;
	temp = NULL;
}
void RemoveReNode(ReceiptList& L, char ID[])
{
	ReceiptNode* temp = FindReData(L, ID);
	if (!temp) return;
	if (temp == L.tail)
		RemoveReTail(L);
	else if (temp == L.head)
		RemoveReHead(L);
	else {
		ReceiptNode* p1 = temp->prev;
		ReceiptNode* p2 = temp->next;
		removeReceipt(temp->data);
		p1->next = p2;
		p2->prev = p1;
		delete temp;
	}
}
void removeListReceipt(ReceiptList& L)
{
	if (!checkEmptyReList(L))
		RemoveReHead(L);
}
ReceiptNode* AddTailReceipt(ReceiptList& N, Receipt b)
{
	ReceiptNode* temp = new ReceiptNode;

	temp->data = b;
	temp->next = NULL;
	if (checkEmptyReList(N))
	{
		temp->prev = NULL;
		N.head = temp;
		N.tail = temp;
	}
	else
	{
		temp->prev = N.tail;
		N.tail->next = temp;
		N.tail = temp;
	}
	return temp;
}
void readListReceipt(FILE* fr, ReceiptList& ListReceipt)
{
	Receipt B;
	B.ID = NULL;
	ListReceipt.head = NULL;
	ListReceipt.tail = NULL;
	if (!IsEmptyFile(fr))
	{
		fseek(fr, 0, SEEK_SET);
		while (!feof(fr))
		{
			readReceipt(fr, B);
			AddTailReceipt(ListReceipt, B);
		}
	}
}

void outputBorReceipt(Receipt B)
{
	system("cls");
	printf("================================= PHIEU MUON SACH =================================\n");
	printf("||	Ma doc gia: %s							||\n", B.ID);
	printf("||	Ngay muon: %d/%d/%d							||\n", B.borrow.day, B.borrow.month, B.borrow.year);
	printf("||	Ngay tra du kien: %d/%d/%d						||\n", B.expReturn.day, B.expReturn.month, B.expReturn.year);
	printf("||	Danh sach ISBN cua cac sach duoc muon:					||\n");
	int i = 0;
	while (B.ISBN[i][1] != '\0')
	{
		printf("||	%s								||\n", B.ISBN[i]);
		i++;
	}
	printf("==================================================================================\n");
}

int DayNum(int d, int m, int y)   //so ngay ke tu dau nam den ngay d/m/y
{
	int s = d;
	for (int i = 0; i < m; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == MAX_ISBN || i == 10)
		{
			s = s + 31;
		}
		else if (i == 4 || i == 6 || i == 9 || i == 11)
		{
			s = s + 30;
		}
		else if (i == 2)
		{
			IsLeapYear(y) ? s = s + 29 : s = s + 28;
		}
	}
	return s;
}

int DiffDays(int d1, int m1, int y1, int d2, int m2, int y2)
{
	int s, s1, s2, s3 = 0;
	if (y1 == y2)
	{
		s = DayNum(d2, m2, y2) - DayNum(d1, m1, y1);
		return s;
	}
	else if (y2 > y1)
	{
		IsLeapYear(y1) ? s1 = 366 - DayNum(d1, m1, y1) : s1 = 365 - DayNum(d1, m1, y1);
		s2 = DayNum(d2, m2, y2);
		for (int i = y1 + 1; i < y2; i++)
		{
			IsLeapYear(i) ? s3 = s3 + 366 : s3 = s3 + 365;
		}
		s = s1 + s2 + s3;
		return s;
	}
	else return -400;  //return -400 neu y1 > y2
}

double fineMoney(BookList& BL, ReceiptList& Re, ReceiptNode*& p, char ID[], int a) //a=0 khong bi mat sach, a=1 bi mat sach
{
	double sum = 0;
	char temp[MAX_CHAR];
	printf("Nhap ngay tra thuc te (ngay/thang/nam): ");
	scanf("%d/%d/%d", &p->data.actReturn.day, &p->data.actReturn.month, &p->data.actReturn.year);
	int dif = DiffDays(p->data.borrow.day, p->data.borrow.month, p->data.borrow.year, p->data.actReturn.day, p->data.actReturn.month, p->data.actReturn.year);
	while (!IsValidDay(p->data.actReturn.day, p->data.actReturn.month, p->data.actReturn.year) || dif < 0)
	{
		printf("Khong hop le, vui long nhap lai: ");
		scanf("%d/%d/%d", &p->data.actReturn.day, &p->data.actReturn.month, &p->data.actReturn.year);
		dif = DiffDays(p->data.borrow.day, p->data.borrow.month, p->data.borrow.year, p->data.actReturn.day, p->data.actReturn.month, p->data.actReturn.year);
	}

	if (a == 1)
	{
		int x;
		printf("Nhap danh sach ISBN cua cac sach bi mat (nhap \"done\" de ket thuc viec nhap)\n");
		do {
			scanf("%s", temp);
			x = _stricmp(temp, "done");
			if (x == 0) break;

			BookNode* b = FindBData(BL, temp, 2);
			if (b && IsBorBook(p->data, temp))
			{
				sum += (b->data.price) * 2;
				changeAmount(b->data, b->data.amount--);
				b->data.BorAmount--;
			}
			else
			{
				printf("Ban khong muon cuon sach nay.\n");
				printf("Nhap lai: ");
			}
		} while (x);
	}
	return (dif > 7) ? sum += (dif - 7) * 5000 : sum;
}

//a=0 khong bi mat sach, a=1 bi mat sach
void outputRetReceipt(BookList& BL, ReceiptList& Re, char ID[], int a)
{
	ReceiptNode* p = FindReData(Re, ID);
	if (p == NULL) {
		printf("Khong co doc gia nay!\n");
		return;
	}
	double money = fineMoney(BL, Re, p, ID, a);
	system("cls");
	printf("===================================== PHIEU TRA SACH =====================================\n");
	printf("||	Ma doc gia: %s							||\n", p->data.ID);
	printf("||	Ngay muon: %d/%d/%d							||\n", p->data.borrow.day, p->data.borrow.month, p->data.borrow.year);
	printf("||	Ngay tra : %d/%d/%d							||\n", p->data.actReturn.day, p->data.actReturn.month, p->data.actReturn.year);
	printf("||	Danh sach ISBN cua cac sach duoc muon:					||\n");
	int i = 0;
	while (p->data.ISBN[i][1] != '\0')
	{

		BookNode* b = FindBData(BL, p->data.ISBN[i], 2);
		b->data.BorAmount--;
		printf("||	%s								||\n", p->data.ISBN[i]);
		i++;
	}
	printf("||	So tien phat (tre han nop hoac lam mat sach): %g nghin VND.		||\n", money / 1000);
	printf("==================================================================================\n");
	RemoveReNode(Re, ID);
}

bool IsBorBook(Receipt B, char* ISBN) //ktr sach co dung la sach da muon hay k
{
	int i = 0;
	while (B.ISBN[i][1] != '\0')
	{
		if (strcmp(B.ISBN[i], ISBN) == 0)
			return true;
		i++;
	}
	return false;
}

bool checkBorReader(ReceiptList Re, char* ID)		//true = dang muon sach, false = dang khong muon sach
{
	for (ReceiptNode* p = Re.head; p; p = p->next)
	{
		if (strcmp(p->data.ID, ID) == 0)
			return true;
	}
	return false;
}


bool IsEmptyFile(FILE* f)
{
	fseek(f, 0, SEEK_END);
	if (ftell(f) == 0)
		return true;
	return false;
}