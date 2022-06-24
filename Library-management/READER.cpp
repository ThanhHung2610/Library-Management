#include "READER.h"

void readReader(FILE* fr, Reader& R)
{
	char temp[MAX_CHAR];

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.ID, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.name, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.idCard, temp);

	fscanf(fr, "%d/%d/%d,", &R.birthday.day, &R.birthday.month, &R.birthday.year);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.gender, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.email, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(R.address, temp);

	fscanf(fr, "%d/%d/%d,", &R.creDate.day, &R.creDate.month, &R.creDate.year);

	fscanf(fr, "%d/%d/%d\n", &R.expDate.day, &R.expDate.month, &R.expDate.year);
}
void writeReader(FILE* fw, Reader R)
{
	fprintf(fw, "%s,%s,%s,", R.ID, R.name, R.idCard);
	fprintf(fw, "%d/%d/%d,", R.birthday.day, R.birthday.month, R.birthday.year);
	fprintf(fw, "%s,%s,%s,", R.gender, R.email, R.address);
	fprintf(fw, "%d/%d/%d,", R.creDate.day, R.creDate.month, R.creDate.year);
	fprintf(fw, "%d/%d/%d\n", R.expDate.day, R.expDate.month, R.expDate.year);
}
void writeRList(FILE* fw, ReadList L)
{
	for (ReadNode* p = L.head; p; p = p->next)
	{
		writeReader(fw, p->data);
	}
}
void removeReader(Reader& R)
{
	delete[]R.ID;
	R.ID = NULL;
	delete[]R.name;
	R.name = NULL;
	delete[]R.idCard;
	R.idCard = NULL;
	delete[]R.gender;
	R.gender = NULL;
	delete[]R.email;
	R.email = NULL;
	delete[]R.address;
	R.address = NULL;
}
void removeListReader(ReadList& L)
{
	if (!checkEmptyReadList(L))
		RemoveRHead(L);
}

bool checkEmptyReadList(ReadList L)
{
	return !L.head;
}

ReadNode* AddTailReader(ReadList& N, Reader r)
{
	ReadNode* temp = new ReadNode;
	temp->data = r;
	temp->next = NULL;
	if (checkEmptyReadList(N))
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
	return N.tail;
}
// a=1 tim theo ten, a=2 tim theo CMND, a=3 tim theo ID
ReadNode* FindRData(ReadList L, char data[], int a)
{
	switch (a) {
	case 1:
		for (ReadNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.name, data) == 0)
				return p;
		}
		return NULL;
		break;
	case 2:
		for (ReadNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.idCard, data) == 0)
				return p;
		}
		return NULL;
		break;
	case 3:
		for (ReadNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.ID, data) == 0)
				return p;
		}
		return NULL;
		break;
	default: return NULL;
	}
}

void RemoveRHead(ReadList& l)
{
	if (checkEmptyReadList(l)) return;
	ReadNode* temp = l.head;
	removeReader(temp->data);
	l.head = temp->next;
	l.head->prev = NULL;
	delete temp;
}
void RemoveRTail(ReadList& l)
{
	if (checkEmptyReadList(l)) return;
	ReadNode* temp = l.tail;
	removeReader(temp->data);
	l.tail = temp->prev;
	l.tail->next = NULL;
	delete temp;
}

//tra ve 0 neu khong co doc gia, tra ve 1 neu xoa thanh cong
int RemoveRNode(ReadList& L, char ID[]) //de  trong menu
{
	ReadNode* temp = FindRData(L, ID, 3);
	if (!temp) return 0;
	if (temp == L.tail)
		RemoveRTail(L);
	else if (temp == L.head)
		RemoveRHead(L);
	else {
		ReadNode* p1 = temp->prev;
		ReadNode* p2 = temp->next;
		removeReader(temp->data);
		p1->next = p2;
		p2->prev = p1;
		delete temp;
	}
	return 1;
}


void readListReader(FILE* fr, ReadList& ListReader)
{
	Reader R;
	ListReader.head = NULL;
	ListReader.tail = NULL;
	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readReader(fr, R);
		AddTailReader(ListReader, R);
	}
}

void changeRid(Reader& R)
{
	char temp[MAX_CHAR];
	printf("Nhap ID: ");
	scanf("%s", temp);
	updateInfoObject(R.ID, temp);
}
void changeRname(Reader& R)
{
	char temp[MAX_CHAR];
	printf("Nhap ho ten: ");
	cin.ignore();
	gets_s(temp);
	while (!IsvalidName(temp))
	{
		printf("Khong hop le. Vui long nhap lai: \n");
		gets_s(temp);
	}
	updateInfoObject(R.name, temp);
}
void changeRIdcard(Reader& R)
{
	char temp[MAX_CHAR];
	printf("Nhap CMND: ");
	scanf("%s", temp);
	updateInfoObject(R.idCard, temp);
}
void changeRbirthday(Reader& R)
{
	printf("Nhap ngay sinh (ngay/thang/nam): ");
	scanf("%d/%d/%d", &R.birthday.day, &R.birthday.month, &R.birthday.year);
	while (!IsValidDay(R.birthday.day, R.birthday.month, R.birthday.year))
	{
		printf("Ngay khong hop le, vui long nhap lai: ");
		scanf("%d/%d/%d", &R.birthday.day, &R.birthday.month, &R.birthday.year);
	}
}
void changeRgender(Reader& R)
{
	int x;
	char temp[MAX_CHAR];
	do {
		printf("Chon gioi tinh:\n1.Nam\n2.Nu\n3.Khac\n");
		scanf("%d", &x);
		if (x == 1) strcpy(temp, "Nam");
		else if (x == 2) strcpy(temp, "Nu");
		else if (x == 3) strcpy(temp, "Khac");
		else
		{
			printf("Khong hop le.");
		}
	} while (x > 3 || x < 1);
	updateInfoObject(R.gender, temp);
}
void changeRemail(Reader& R) {
	char temp[MAX_CHAR];
	printf("Nhap Email: ");
	scanf("%s", temp);
	updateInfoObject(R.email, temp);
}
void changeRaddress(Reader& R)
{
	char temp[MAX_CHAR];
	printf("Nhap dia chi: ");
	cin.ignore();
	gets_s(temp);
	while (strchr(temp, ','))
	{
		printf("Khong hop le, vui long nhap lai: ");
		gets_s(temp);
	}
	updateInfoObject(R.address, temp);
}
void addRcreDate(Reader& R)
{
	printf("Nhap ngay lap the (ngay/thang/nam): ");
	scanf("%d/%d/%d", &R.creDate.day, &R.creDate.month, &R.creDate.year);
	while (!IsValidDay(R.creDate.day, R.creDate.month, R.creDate.year))
	{
		printf("Ngay khong hop le, vui long nhap lai: ");
		scanf("%d/%d/%d", &R.creDate.day, &R.creDate.month, &R.creDate.year);
	}
}
void addRexpDate(Reader& R)
{
	R.expDate.day = R.creDate.day;
	R.expDate.month = R.creDate.month;
	R.expDate.year = R.creDate.year + 4;
}

void AddReader(ReadList& ListReader)
{
	Reader R;
	R.ID = NULL;
	R.name = NULL;
	R.address = NULL;
	R.email = NULL;
	R.gender = NULL;
	R.idCard = NULL;
	char temp[MAX_CHAR];

	changeRid(R);
	changeRname(R);
	changeRIdcard(R);
	changeRbirthday(R);
	changeRgender(R);
	changeRemail(R);
	changeRaddress(R);
	addRcreDate(R);
	addRexpDate(R);

	AddTailReader(ListReader, R);
}

void outputRList(ReadList R)
{
	printf("ID  		Ho ten\n");
	for (ReadNode* p = R.head; p; p = p->next)
	{
		printf("%s	%s\n", p->data.ID, p->data.name);
	}
}

int outputReader(Reader R)
{
	printf("Thong tin doc gia:\n");
	printf("1. ID		: %s\n", R.ID);
	printf("2. Ho ten	: %s\n", R.name);
	printf("3. CMND		: %s\n", R.idCard);
	printf("4. Ngay sinh	: %d/%d/%d\n", R.birthday.day, R.birthday.month, R.birthday.year);
	printf("5. Gioi tinh	: %s\n", R.gender);
	printf("6. Email	: %s\n", R.email);
	printf("7. Dia chi	: %s\n", R.address);
	printf("8. Ngay tao the	: %d/%d/%d\n", R.creDate.day, R.creDate.month, R.creDate.year);
	printf("9. Ngay het han	: %d/%d/%d\n\n", R.expDate.day, R.expDate.month, R.expDate.year);
	return 9;
}


void changeReader(Reader& R, int x)
{
	switch (x)
	{
	case 1:
		printf("ID khong the doi duoc.\n");
		break;
	case 2:
		changeRname(R);
		printf("Doi ho ten thanh cong!\n");
		break;
	case 3:
		changeRIdcard(R);
		printf("Doi CMND thanh cong!\n");
		break;
	case 4:
		changeRbirthday(R);
		printf("Doi ngay sinh thanh cong!\n");
		break;
	case 5:
		changeRgender(R);
		printf("Doi gioi tinh thanh cong!\n");
		break;
	case 6:
		changeRemail(R);
		printf("Doi email thanh cong!\n");
		break;
	case 7:
		changeRaddress(R);
		printf("Doi dia chi thanh cong!\n");
		break;
	case 8:
		printf("Khong the doi.\n");
		break;
	case 9:
		printf("Khong the doi.\n");
		break;
	default:
		return;
	}
}
void menuChangeReader(ReadList& L, char ID[])
{
	int x;
	ReadNode* p = FindRData(L, ID, 3);
	if (p == NULL)
	{
		printf("Khong co doc gia nay.\n");
		return;
	}
	do
	{
		system("cls");
		printf("============================== CHINH SUA THONG TIN DOC GIA ==============================\n");
		outputReader(p->data);
		printf("Nhap so tuong ung de thay doi thong tin.\n");
		printf("Hoac nhap bat ky so nao khac de quay lai.\n");
		printf("Moi ban nhap so: ");
		scanf("%d", &x);
		changeReader(p->data, x);
		system("pause");
	} while (x >= 1 && x <= 9);
}


//chuc nang 5 va chuc nang 6: tim va xuat thong tin doc gia theo CMND va ho ten
//n=1 tim theo ho ten, n=2 tim theo CMND
void FindnPrintReader(ReadList L, char data[], int n)
{
	int x = 0;
	switch (n) {
	case 1:
		for (ReadNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.name, data) == 0)
				x = outputReader(p->data);
		}
		if (x == 0) printf("Khong tim thay doc gia!\n");
		break;
	case 2:
		for (ReadNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.idCard, data) == 0)
				x = outputReader(p->data);
		}
		if (x == 0) printf("Khong tim thay doc gia!\n");
		break;
	default: break;
	}
}


void chucNang2AdminnManager(ReadList& RL, User& U, int& log)
{
	int run1, tf1 = 1, a = -1;
	char temp[MAX_CHAR];
	do
	{
		system("cls");
		printf("=================================== QUAN LY DOC GIA ===================================\n");
		printf("1.Xem danh sach doc gia trong thu vien\n");
		printf("2.Them doc gia\n");
		printf("3.Chinh sua thong tin doc gia\n");
		printf("4.Xoa thong tin doc gia\n");
		printf("5.Tim kiem doc gia theo CMND\n");
		printf("6.Tim kiem doc gia theo ho ten\n");
		printf("7.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
		case 1:
			system("cls");
			printf("================================== DANH SACH DOC GIA ==================================\n");
			outputRList(RL);
			printf("========================================================================================\n");
			break;
		case 2:
			system("cls");
			printf("=================================== THEM DOC GIA ===================================\n");
			AddReader(RL);
			printf("Them doc gia thanh cong!\n");
			break;
		case 3:
			system("cls");
			printf("============================== CHINH SUA THONG TIN DOC GIA ==============================\n");
			printf("Nhap ma doc gia (ID) cua doc gia can chinh sua: ");
			scanf("%s", temp);
			menuChangeReader(RL, temp);
			break;
		case 4:
			system("cls");
			printf("============================== XOA THONG TIN DOC GIA ==============================\n");
			printf("Nhap ma doc gia (ID) cua doc gia can xoa: ");
			scanf("%s", temp);
			a = RemoveRNode(RL, temp);
			if (a == 1) printf("Xoa thanh cong!\n");
			else printf("Khong co doc gia nay!\n");
			break;
		case 5:
			system("cls");
			printf("============================== TIM KIEM DOC GIA THEO CMND ==============================\n");
			printf("Nhap CMND cua doc gia can tim: ");
			scanf("%s", temp);
			FindnPrintReader(RL, temp, 2);
			break;
		case 6:
			system("cls");
			printf("============================== TIM KIEM DOC GIA THEO TEN ==============================\n");
			printf("Nhap ho ten cua doc gia can tim: ");
			cin.ignore();
			gets_s(temp);
			while (!IsvalidName(temp))
			{
				printf("Khong hop le. Vui long nhap lai: \n");
				gets_s(temp);
			}
			FindnPrintReader(RL, temp, 1);
			break;
		case 7:
			tf1 = 0;
			break;
		default:
			break;
		}
		system("pause");
	} while (tf1);
}


void chucNang2Librarian(ReadList& RL, User& U, int& log)
{
	int run1, tf1 = 1, a = -1;
	char temp[MAX_CHAR];
	do
	{
		system("cls");
		printf("=================================== QUAN LY DOC GIA ===================================\n");
		printf("1.Xem danh sach doc gia trong thu vien\n");
		printf("2.Them doc gia\n");
		printf("3.Chinh sua thong tin doc gia\n");
		printf("4.Tim kiem doc gia theo CMND\n");
		printf("5.Tim kiem doc gia theo ho ten\n");
		printf("6.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
			system("cls");
		case 1:
			printf("================================== DANH SACH DOC GIA ==================================\n");
			outputRList(RL);
			printf("========================================================================================\n");
			break;
		case 2:
			printf("=================================== THEM DOC GIA ===================================\n");
			AddReader(RL);
			printf("Them doc gia thanh cong!\n");
			break;
		case 3:
			printf("============================== CHINH SUA THONG TIN DOC GIA ==============================\n");
			printf("Nhap ma doc gia (ID) cua doc gia can chinh sua: ");
			scanf("%s", temp);
			menuChangeReader(RL, temp);
			break;
		case 4:
			printf("============================== TIM KIEM DOC GIA THEO CMND ==============================\n");
			printf("Nhap CMND cua doc gia can tim: ");
			scanf("%s", temp);
			FindnPrintReader(RL, temp, 2);
			break;
		case 5:
			printf("============================== TIM KIEM DOC GIA THEO TEN ==============================\n");
			printf("Nhap ho ten cua doc gia can tim: ");
			cin.ignore();
			gets_s(temp);
			while (!IsvalidName(temp))
			{
				printf("Khong hop le. Vui long nhap lai: \n");
				gets_s(temp);
			}
			FindnPrintReader(RL, temp, 1);
			break;
		case 6:
			tf1 = 0;
			break;
		default:
			break;
		}
		system("pause");
	} while (tf1);
}
