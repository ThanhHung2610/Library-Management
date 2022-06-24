#include "BOOK.h"

void readBook(FILE* fr, Book& B)
{
	char temp[MAX_CHAR];

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(B.ISBN, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(B.name, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(B.author, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(B.publisher, temp);

	fscanf(fr, "%d,", &B.year);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(B.genre, temp);

	fscanf(fr, "%u,", &B.price);

	fscanf(fr, "%d,", &B.amount);

	fscanf(fr, "%d\n", &B.BorAmount);
}

void writeBook(FILE* fw, Book B)
{
	fprintf(fw, "%s,%s,%s,%s,", B.ISBN, B.name, B.author, B.publisher);
	fprintf(fw, "%d,", B.year);
	fprintf(fw, "%s,", B.genre);
	fprintf(fw, "%u,", B.price);
	fprintf(fw, "%d,", B.amount);
	fprintf(fw, "%d\n", B.BorAmount);
}

void writeBList(FILE* fw, BookList L)
{
	for (BookNode* p = L.head; p; p = p->next)
	{
		writeBook(fw, p->data);
	}
}

void removeBook(Book& B)
{
	delete[]B.ISBN;
	B.ISBN = NULL;
	delete[]B.name;
	B.name = NULL;
	delete[]B.author;
	B.author = NULL;
	delete[]B.publisher;
	B.publisher = NULL;
	delete[]B.genre;
	B.genre = NULL;
}

bool checkEmptyBookList(BookList L)
{
	return !L.head;
}

BookNode* FindBData(BookList L, char data[], int a)// a=1 tim theo ten, a=2 tim theo ISBN
{
	switch (a) {
	case 1:
		for (BookNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.name, data) == 0)
				return p;
		}
		return NULL;
		break;
	case 2:
		for (BookNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.ISBN, data) == 0)
				return p;
		}
		return NULL;
		break;
	default:
		return NULL;
	}
}

void RemoveBHead(BookList& L)
{
	if (checkEmptyBookList(L)) return;
	BookNode* temp = L.head;
	removeBook(temp->data);
	L.head = temp->next;
	L.head->prev = NULL;
	delete temp;
}

void RemoveBTail(BookList& L)
{
	if (checkEmptyBookList(L)) return;
	BookNode* temp = L.tail;
	removeBook(temp->data);
	L.tail = temp->prev;
	L.tail->next = NULL;
	delete temp;
}

//tra ve 0 neu khong co sach, tra ve 1 neu xoa thanh cong
int RemoveBNode(BookList& L, char ISBN[]) //de  trong menu
{
	BookNode* temp = FindBData(L, ISBN, 2);
	if (!temp) return 0;
	if (temp == L.tail)
		RemoveBTail(L);
	else if (temp == L.head)
		RemoveBHead(L);
	else {
		BookNode* p1 = temp->prev;
		BookNode* p2 = temp->next;
		removeBook(temp->data);
		p1->next = p2;
		p2->prev = p1;
		delete temp;
	}
	return 1;
}

void removeListBook(BookList& L)
{
	if (!checkEmptyBookList(L))
		RemoveBHead(L);
}

BookNode* AddTailBook(BookList& N, Book b)
{
	BookNode* temp = new BookNode;
	temp->data = b;
	temp->next = NULL;
	if (checkEmptyBookList(N))
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

void readListBook(FILE* fr, BookList& ListBook)
{
	Book B;
	ListBook.head = NULL;
	ListBook.tail = NULL;
	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readBook(fr, B);
		AddTailBook(ListBook, B);
	}
}

void changeISBN(Book& B)
{
	char temp[MAX_CHAR];
	printf("Nhap ISBN: ");
	scanf("%s", temp);
	updateInfoObject(B.ISBN, temp);
}

void changeBname(Book& B)
{
	char temp[MAX_CHAR];
	printf("Nhap ten sach: ");
	cin.ignore();
	gets_s(temp);
	updateInfoObject(B.name, temp);
}

void changeAuthor(Book& B)
{
	char temp[MAX_CHAR];
	printf("Nhap tac gia: ");

	gets_s(temp);
	while (!IsvalidName(temp))
	{
		printf("Khong hop le. Vui long nhap lai: \n");
		gets_s(temp);
	}
	updateInfoObject(B.author, temp);
}

void changePublisher(Book& B)
{
	char temp[MAX_CHAR];
	printf("Nhap nha xuat ban: ");
	gets_s(temp);
	updateInfoObject(B.publisher, temp);
}

void changeByear(Book& B)
{
	printf("Nhap nam xuat ban: ");
	scanf("%d", &B.year);
	while (B.year < 0)
	{
		printf("Nam khong hop le. Vui long nhap lai: ");
		scanf("%d", &B.year);
	}
}

void changeGenre(Book& B)
{
	char temp[MAX_CHAR];
	printf("Nhap the loai: ");
	cin.ignore();
	gets_s(temp);
	updateInfoObject(B.genre, temp);
}

void changePrice(Book& B)
{
	printf("Nhap gia sach: ");
	scanf("%u", &B.price);
	while (B.price < 0)
	{
		printf("Gia khong hop le. Vui long nhap lai: ");
		scanf("%u", &B.price);
	}
}

void changeAmount(Book& B, int amount)
{
	B.amount = amount;
}

void AddBook(BookList& ListBook)
{
	Book B;
	B.ISBN = NULL;
	B.name = NULL;
	B.author = NULL;
	B.publisher = NULL;
	B.genre = NULL;
	char temp[MAX_CHAR];

	changeISBN(B);
	changeBname(B);
	changeAuthor(B);
	changePublisher(B);
	changeByear(B);
	changeGenre(B);
	changePrice(B);
	int amo;
	printf("Nhap so quyen sach: ");
	scanf("%d", &amo);
	while (amo < 0)
	{
		printf("So luong khong hop le. Vui long nhap lai: ");
		scanf("%d", &amo);
	}
	changeAmount(B, amo);
	B.BorAmount = 0;

	AddTailBook(ListBook, B);
}

int outputBook(Book B)
{
	printf("Thong tin sach:\n");
	printf("1. ISBN		: %s\n", B.ISBN);
	printf("2. Ten sach	: %s\n", B.name);
	printf("3. Tac gia	: %s\n", B.author);
	printf("4. Nha xuat ban	: %s\n", B.publisher);
	printf("5. Nam xuat ban	: %d\n", B.year);
	printf("6. The loai	: %s\n", B.genre);
	printf("7. Gia sach	: %u\n", B.price);
	printf("8. So quyen sach: %d\n", B.amount);
	printf("9. So sach dang duoc muon: %d\n\n", B.BorAmount);
	return 9;
}

void changeBook(Book& B, int x)
{
	switch (x)
	{
	case 1:
		printf("ISBN khong the doi duoc.\n");
		break;
	case 2:
		changeBname(B);
		printf("Doi ho ten thanh cong!\n");
		break;
	case 3:
		cin.ignore();
		changeAuthor(B);
		printf("Doi tac gia thanh cong!\n");
		break;
	case 4:
		cin.ignore();
		changePublisher(B);
		printf("Doi nha xuat ban thanh cong!\n");
		break;
	case 5:
		changeByear(B);
		printf("Doi nam xuat ban thanh cong!\n");
		break;
	case 6:
		changeGenre(B);
		printf("Doi the loai thanh cong!\n");
		break;
	case 7:
		changePrice(B);
		printf("Doi gia sach thanh cong!\n");
		break;
	case 8:
		int amo;
		printf("Nhap so quyen sach: ");
		scanf("%d", &amo);
		while (amo < 0)
		{
			printf("So luong khong hop le. Vui long nhap lai: ");
			scanf("%d", &amo);
		}
		changeAmount(B, amo);
		printf("Doi so quyen sach thanh cong!\n");
		break;
	case 9:
		printf("Khong the doi duoc.\n");
		break;
	default:
		return;
	}
}

void menuChangeBook(BookList& L, char ISBN[])
{
	int x;
	BookNode* p = FindBData(L, ISBN, 2);
	if (p == NULL)
	{
		printf("Khong tim thay sach nay.\n");
		return;
	}
	do
	{
		system("cls");
		outputBook(p->data);
		printf("Nhap so tuong ung de thay doi thong tin.\n");
		printf("Hoac nhap bat ky so nao khac de quay lai.\n");
		printf("Moi ban nhap so: ");
		scanf("%d", &x);
		changeBook(p->data, x);
		system("pause");
	} while (x >= 1 && x <= 9);
}

void FindnPrintBook(BookList L, char data[], int n) //n=1 tim theo ten sach, n=2 tim theo ISBN
{
	int x = 0;
	switch (n) {
	case 1:
		for (BookNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.name, data) == 0)
				x = outputBook(p->data);
		}
		if (x == 0) printf("Khong tim thay sach!\n");
		break;
	case 2:
		for (BookNode* p = L.head; p; p = p->next)
		{
			if (strcmp(p->data.ISBN, data) == 0)
				x = outputBook(p->data);
		}
		if (x == 0) printf("Khong tim thay sach!\n");
		break;
	default:
		break;
	}
}

void outputBList(BookList B)
{
	printf("ISBN  		Ten sach\n");
	for (BookNode* p = B.head; p; p = p->next)
	{
		printf("%s	%s\n", p->data.ISBN, p->data.name);
	}
}

void chucNang3AdminnManager(BookList& BL, User& U, int& log)
{
	int run1 = -1, tf1 = 1, a = -1;
	char temp[MAX_CHAR];
	do {
		system("cls");
		printf("=================================== QUAN LY SACH ===================================\n");
		printf("1.Xem danh sach cac sach\n");
		printf("2.Them sach\n");
		printf("3.Chinh sua thong tin sach\n");
		printf("4.Xoa thong tin sach\n");
		printf("5.Tim kiem sach theo ISBN\n");
		printf("6.Tim kiem sach theo ten\n");
		printf("7.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
		case 1:
			system("cls");
			printf("============================== DANH SACH CAC SACH ==============================\n");
			outputBList(BL);
			break;
		case 2:
			system("cls");
			printf("============================== THEM SACH ==============================\n");
			AddBook(BL);
			printf("Them sach thanh cong!\n");
			break;
		case 3:
			char temp[MAX_CHAR];
			printf("Nhap ISBN cua sach can chinh sua thong tin: ");
			cin.ignore();
			scanf("%s", temp);
			menuChangeBook(BL, temp);
			break;
		case 4:
			system("cls");
			printf("============================== XOA THONG TIN SACH ==============================\n");
			printf("Nhap ISBN cua sach can xoa thong tin: ");
			cin.ignore();
			scanf("%s", temp);
			a = RemoveBNode(BL, temp);
			if (a == 1) printf("Xoa thanh cong!\n");
			else printf("Khong co cuon sach nay!\n");
			break;
		case 5:
			system("cls");
			printf("============================== TIM KIEM SACH THEO ISBN ==============================\n");
			printf("Nhap ISBN cua sach can tim: ");
			cin.ignore();
			scanf("%s", temp);
			FindnPrintBook(BL, temp, 2);
			break;
		case 6:
			system("cls");
			printf("============================== TIM KIEM SACH THEO TEN ==============================\n");
			printf("Nhap ten cua sach can tim: ");
			cin.ignore();
			gets_s(temp);
			FindnPrintBook(BL, temp, 1);
			break;
		case 7:
			tf1 = 0;
			break;
		default: break;
		}
		system("pause");
	} while (tf1);
}


void chucNang3Librarian(BookList& BL, User& U, int& log)
{
	int run1 = -1, tf1 = 1, a = -1;
	char temp[MAX_CHAR];
	do {
		system("cls");
		printf("=================================== TIM KIEM SACH ===================================\n");
		printf("1.Tim kiem sach theo ISBN\n");
		printf("2.Tim kiem sach theo ten\n");
		printf("3.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
		case 1:
			system("cls");
			printf("============================== TIM KIEM SACH THEO ISBN ==============================\n");
			printf("Nhap ISBN cua sach can tim: ");
			cin.ignore();
			scanf("%s", temp);
			FindnPrintBook(BL, temp, 2);
			break;
		case 2:
			system("cls");
			printf("============================== TIM KIEM SACH THEO TEN ==============================\n");
			printf("Nhap ten cua sach can tim: ");
			cin.ignore();
			gets_s(temp);
			FindnPrintBook(BL, temp, 2);
			break;
		case 3:
			tf1 = 0;
			break;
		default: break;
		}
		system("pause");
	} while (tf1);
}
