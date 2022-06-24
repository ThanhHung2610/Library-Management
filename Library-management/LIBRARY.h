#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <time.h>
#define MAX_CHAR 101
#define BUFF_MAX 4*1024
#define MAX_ISBN 8

using namespace std;

struct Date
{
	int day, month, year;
};

struct User
{
	char* username;						//Ten dang nhap
	char* password;
	char* name;							//Ho ten
	Date birthday;						//Ngay sinh
	char* idCard;
	char* address;						//Dia chi
	char* gender;
	int status;							//1 = activated, 0 = block
	int classify;						//0 = Quan ly thu vien, 1 = chuyen vien, 9 = admin
};

struct Reader
{
	char* ID;					//Ma doc gia
	char* name;
	char* idCard;
	Date birthday;
	char* gender;
	char* email;
	char* address;
	Date creDate;				//Ngay lap the
	Date expDate;				//Ngay het han (sau 48 thang)
};

struct Book
{
	char* ISBN;				//Ma sach
	char* name;				//Ten sach
	char* author;				//Tac gia
	char* publisher;			//Nha xuat ban
	int year;					//Nam xuat ban
	char* genre;				//The loai
	unsigned int price;			//Gia sach
	int amount;					//So quyen sach
	int BorAmount;					//So sach hien co
};

struct Receipt
{
	char* ID;					//Ma doc gia
	Date borrow;				//Ngay muon
	Date expReturn;				//Ngay tra du kien
	Date actReturn;				//Ngay tra thuc te
	char ISBN[20][MAX_ISBN + 1];			//Danh sach ISBN cua cac sach duoc muon
};

struct ReadNode {
	Reader data;
	ReadNode* next;
	ReadNode* prev;
};
struct ReadList {
	ReadNode* head;
	ReadNode* tail;
};

struct BookNode {
	Book data;
	BookNode* next;
	BookNode* prev;
};
struct BookList {
	BookNode* head;
	BookNode* tail;
};

struct ReceiptNode {
	Receipt data;
	ReceiptNode* next;
	ReceiptNode* prev;
};
struct ReceiptList {
	ReceiptNode* head;
	ReceiptNode* tail;
};

void StaticToDynamic(char*& Dyn, char Sta[]);
void ChangeValueDynamic(char*& oldstr, char*& newstr);
void updateInfoObject(char*& oldValue, char newValue[]);
bool IsLeapYear(int y);
bool IsValidDay(int d, int m, int y);
bool IsvalidName(char name[]);


void readUser(FILE* fr, User& A);
void maskPass(char password[]);
int login(FILE* fr, User& A);
void deleteUser(User& A);
void logout(User& A, int& login);
int outputUser(FILE* fr, User A, char username[]);
void copyFile(FILE* fr, FILE* fw);
void writeUser(FILE* fw, User A);
void changePassword(FILE* fr, User& A);
void changeName(FILE* fw, User& A);
void changeBirthday(FILE* fw, User& A);
void changeIdCard(FILE* fw, User& A);
void changeAddress(FILE* fw, User& A);
void changeGender(FILE* fw, User& A);
void changeUser(FILE* fr, char username[], User& A, int x);
void menuChangeUser(FILE* fr, char username[], User& A);

void classUser(User& A);
bool IsAvaiUser(FILE* fr, char username[]);
void CreUser(FILE* fw);

void chucNang1Admin(FILE* fuser, User& U, int& log);

void chucNang1ManagernLibrarian(FILE* fuser, User& U, int& log);

void encrypt(char string[]);

void decrypt(char string[]);
