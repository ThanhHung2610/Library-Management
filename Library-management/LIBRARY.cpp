#include "LIBRARY.h"

void StaticToDynamic(char*& Dyn, char Sta[])
{
	Dyn = new char[strlen(Sta) + 1];		//Delete khi dang xuat
	strcpy(Dyn, Sta);
}

void ChangeValueDynamic(char*& oldstr, char*& newstr) //s1 is old string, s2 is new string
{
	char* temp = oldstr;
	oldstr = newstr;
	if (temp != NULL)
	{
		delete temp;
		temp = NULL;
	}
}
//cap nhat thong tin cua user, book, reader
void updateInfoObject(char*& oldValue, char newValue[])
{
	char* newstr = NULL;
	StaticToDynamic(newstr, newValue);
	ChangeValueDynamic(oldValue, newstr);
}

bool IsLeapYear(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
		return true;
	else return false;
}

//kiem tra ngay hop le
bool IsValidDay(int d, int m, int y)
{
	switch (m)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return d > 31 ? false : true;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return d > 30 ? false : true;
		break;
	case 2:
		if (IsLeapYear(y))
			return d > 29 ? false : true;
		else
			return d > 28 ? false : true;
		break;
	default: return false;
		break;
	}
}

bool IsvalidName(char name[])
{
	int i = 1;
	char x;
	if (name[0] > 'Z' || name[0] < 'A') return false;
	while (name[i + 1] != '\0')
	{
		if (name[i] == ' ' && (name[i + 1] > 'Z' || name[i + 1] < 'A'))
			return false;
		i++;
	}
	return true;
}

void readUser(FILE* fr, User& A)
{
	char temp[MAX_CHAR];

	fscanf(fr, "%[^,],", temp);
	decrypt(temp);
	StaticToDynamic(A.username, temp);

	fscanf(fr, "%[^,],", temp);
	decrypt(temp);
	StaticToDynamic(A.password, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(A.name, temp);

	fscanf(fr, "%d/%d/%d,", &A.birthday.day, &A.birthday.month, &A.birthday.year);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(A.idCard, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(A.address, temp);

	fscanf(fr, "%[^,],", temp);
	StaticToDynamic(A.gender, temp);

	fscanf(fr, "%d,%d\n", &A.status, &A.classify);
}

void maskPass(char password[])		//Pass = ****
{
	int i;
	char temp;

	for (i = 0; i < MAX_CHAR - 1; i++)
	{
		temp = _getch();
		if (temp == '\r')
			break;
		if (temp == '\b')
		{
			cout << "\b \b";
			i = i - 2;
		}
		else {
			password[i] = temp;
			printf("*");
		}
	}
	password[i] = '\0';
	printf("\n");
}

int login(FILE* fr, User& A)		//0 = sai username hoac password, 1 = bi block, 2 = dang nhap thanh cong
{
	char username[MAX_CHAR], password[MAX_CHAR];

	//username
	printf("Dang nhap:\nTen dang nhap: ");
	scanf("%s", username);

	//password
	printf("Mat khau: ");
	maskPass(password);

	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readUser(fr, A);
		if (A.username != NULL && strcmp(username, A.username) == 0)
		{
			if (strcmp(password, A.password) == 0)
			{
				if (A.status == 0)
					return 1;
				return 2;
			}
		}
	}
	return 0;
}

void deleteUser(User& A)
{
	delete[] A.username;
	A.username = NULL;
	delete[] A.password;
	A.password = NULL;
	delete[] A.name;
	A.name = NULL;
	delete[] A.idCard;
	A.idCard = NULL;
	delete[] A.address;
	A.address = NULL;
	delete[] A.gender;
	A.gender = NULL;
}

void logout(User& A, int& login)
{
	deleteUser(A);
	login = 0;
}

int outputUser(FILE* fr, User A, char username[])
{
	int a = A.status, b = A.classify;
	int len = strlen(A.password);

	system("cls");
	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readUser(fr, A);
		if (strcmp(username, A.username) == 0)
		{
			printf("Thong tin nguoi dung:\n");
			printf("1. Ten dang nhap: %s\n", A.username);
			printf("2. Mat khau     : ");
			for (int i = 0; i < len; i++)
			{
				printf("*");
			}
			printf("\n");
			printf("3. Ho ten	: %s\n", A.name);
			printf("4. Ngay sinh	: %d/%d/%d\n", A.birthday.day, A.birthday.month, A.birthday.year);
			printf("5. CMND		: %s\n", A.idCard);
			printf("6. Dia chi	: %s\n", A.address);
			printf("7. Gioi tinh	: %s\n", A.gender);
		}
	}
	return 7;
}

void copyFile(FILE* fr, FILE* fw)
{
	int count;
	char buf[BUFF_MAX];
	if (!fr || !fw)
		return;
	do
	{
		count = fread(&buf, sizeof(char), BUFF_MAX, fr);
		fwrite(&buf, sizeof(char), count, fw);
	} while (count == BUFF_MAX);
}

void writeUser(FILE* fw, User A)
{
	encrypt(A.username);
	encrypt(A.password);
	fprintf(fw, "%s,%s,%s,", A.username, A.password, A.name);
	fprintf(fw, "%d/%d/%d,", A.birthday.day, A.birthday.month, A.birthday.year);
	fprintf(fw, "%s,%s,%s,%d,%d\n", A.idCard, A.address, A.gender, A.status, A.classify);
}

void changePassword(FILE* fw, User& A)
{
	char temp[MAX_CHAR];
	printf("Nhap mat khau moi: ");
	maskPass(temp);
	updateInfoObject(A.password, temp);
	writeUser(fw, A);
}

void changeName(FILE* fw, User& A)
{
	char temp[MAX_CHAR];
	printf("Nhap ho ten moi: ");
	cin.ignore();
	gets_s(temp);
	while (!IsvalidName(temp))
	{
		printf("Khong hop le. Vui long nhap lai: \n");
		cin.ignore();
		gets_s(temp);
	}
	updateInfoObject(A.name, temp);
	writeUser(fw, A);
}

void changeBirthday(FILE* fw, User& A)
{
	printf("Nhap ngay sinh moi (ngay/thang/nam): ");
	scanf("%d/%d/%d", &A.birthday.day, &A.birthday.month, &A.birthday.year);
	while (!IsValidDay(A.birthday.day, A.birthday.month, A.birthday.year))
	{
		printf("Ngay khong hop le, vui long nhap lai: ");
		scanf("%d/%d/%d", &A.birthday.day, &A.birthday.month, &A.birthday.year);
	}
	writeUser(fw, A);
}

void changeIdCard(FILE* fw, User& A)
{
	char temp[MAX_CHAR];
	printf("Nhap CMND moi: ");
	scanf("%s", temp);
	updateInfoObject(A.idCard, temp);
	writeUser(fw, A);
}

void changeAddress(FILE* fw, User& A)
{
	char temp[MAX_CHAR];
	printf("Nhap dia chi moi: ");
	cin.ignore();
	gets_s(temp);
	while (strcmp(temp, "\0") == 0 || strchr(temp, ','))
	{
		printf("Khong hop le, vui long nhap lai: ");
		//cin.ignore();
		gets_s(temp);
	}
	updateInfoObject(A.address, temp);
	writeUser(fw, A);
}

void changeGender(FILE* fw, User& A)
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
			printf("khong hop le.");
		}
	} while (x > 3 || x < 1);
	updateInfoObject(A.gender, temp);
	writeUser(fw, A);
}

void changeUser(FILE* fr, char username[], User& A, int x)
{
	if (x <= 0 || x > 7)
		return;

	FILE* fw = fopen("copy.csv", "w");
	if (!fw)
		return;

	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readUser(fr, A);
		if (strcmp(username, A.username) == 0)
		{
			switch (x)
			{
			case 1:
				printf("Username khong the doi duoc.\n");
				break;
			case 2:
				changePassword(fw, A);
				printf("Doi mat khau thanh cong!\n");
				break;
			case 3:
				changeName(fw, A);
				printf("Doi ho ten thanh cong!\n");
				break;
			case 4:
				changeBirthday(fw, A);
				printf("Doi ngay sinh thanh cong!\n");
				break;
			case 5:
				changeIdCard(fw, A);
				printf("Doi CMND thanh cong!\n");
				break;
			case 6:
				changeAddress(fw, A);
				printf("Doi dia chi thanh cong!\n");
				break;
			case 7:
				changeGender(fw, A);
				printf("Doi gioi tinh thanh cong!\n");
				break;
			default:
				break;
			}
		}
		else writeUser(fw, A);
	}
	//Chep du lieu moi tu "copy" sang "user"
	freopen("user.csv", "wb", fr);
	freopen("copy.csv", "rb", fw);
	copyFile(fw, fr);
	fclose(fw);
	freopen("user.csv", "rt", fr);
	//Xoa file copy sau khi lam xong
	remove("copy.csv");
}

void menuChangeUser(FILE* fr, char username[], User& A)
{
	int x;
	do
	{
		system("cls");
		outputUser(fr, A, username);
		printf("Nhap so tuong ung de thay doi thong tin.\n");
		printf("Hoac nhap bat ky so nao khac de quay lai.\n");
		printf("Moi ban nhap so: ");
		scanf("%d", &x);
		changeUser(fr, username, A, x);
	} while (x >= 1 && x <= 7);
}

void classUser(User& A) //decentralize user - phan quyen nguoi dung
{
	do {
		printf("Chon chuc vu:\n0.Quan li thu vien\n1.Chuyen vien thu vien\n");
		scanf("%d", &A.classify);
	} while (A.classify != 1 && A.classify != 0);
}

bool IsAvaiUser(FILE* fr, char username[])
{
	User A;
	fseek(fr, 0, SEEK_SET);
	while (!feof(fr))
	{
		readUser(fr, A);
		if (A.username != NULL && strcmp(username, A.username) == 0)
		{
			deleteUser(A);
			return true;
		}
		//deleteUser(A);
	}
	deleteUser(A);
	return false;
}

void CreUser(FILE* fw)
{
	system("cls");
	printf("============================== TAO NGUOI DUNG ==============================\n");
	User A;
	char temp[MAX_CHAR];
	//cap nhat username va password
	printf("Nhap ten dang nhap: ");
	scanf("%s", temp);
	while (IsAvaiUser(fw, temp))
	{
		printf("Ten dang nhap da co san, vui long nhap lai: ");
		scanf("%s", temp);
	}
	A.username = NULL;
	A.password = NULL;
	updateInfoObject(A.username, temp);
	printf("Nhap mat khau: ");
	maskPass(temp);
	updateInfoObject(A.password, temp);

	classUser(A); //phan quyen nguoi dung

	encrypt(A.username);
	encrypt(A.password);

	freopen("user.csv", "a", fw);
	fprintf(fw, "%s,%s,0,1/1/1,", A.username, A.password);
	fprintf(fw, "0,0,0,%d,%d\n", 1, A.classify);
	freopen("user.csv", "rt", fw);

	delete[]A.username;
	delete[]A.password;
	printf("Tao nguoi dung thanh cong!\n");
}


void chucNang1Admin(FILE* fuser, User& U, int& log)
{
	int run1, tf1 = 1;
	do
	{
		system("cls");
		printf("=================================== CAI DAT CHUNG - NGUOI DUNG ===================================\n");
		printf("1.Cap nhat thong tin ca nhan va bao mat\n");
		printf("2.Tao nguoi dung\n");
		printf("3.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
		case 1:
			menuChangeUser(fuser, U.username, U);
			system("pause");
			break;
		case 2:
			CreUser(fuser);
			system("pause");
			break;
		case 3:
			tf1 = 0;
			break;
		default:
			break;
		}
	} while (tf1);
}


void chucNang1ManagernLibrarian(FILE* fuser, User& U, int& log)
{
	int run1, tf1 = 1;
	do
	{
		system("cls");
		printf("=================================== CAI DAT CHUNG - NGUOI DUNG ===================================\n");
		printf("1.Cap nhat thong tin ca nhan va bao mat\n");
		printf("2.Quay lai\n");
		printf("Chon: ");
		scanf("%d", &run1);
		switch (run1)
		{
		case 1:
			menuChangeUser(fuser, U.username, U);
			system("pause");
			break;
		case 2:
			tf1 = 0;
			break;
		default:
			break;
		}
	} while (tf1);
}

void encrypt(char string[])
{
	int len = strlen(string);
	int num;
	for (int i = 0; i < len; i++)
	{
		num = (int)string[i];
		num += 10;
		string[i] = (char)num;
	}
}

void decrypt(char string[])
{
	int len = strlen(string);
	int num;
	for (int i = 0; i < len; i++)
	{
		num = (int)string[i];
		num -= 10;
		string[i] = (char)num;
	}
}