#pragma once
#include "LIBRARY.h"

void readBook(FILE* fr, Book& B);

void writeBook(FILE* fw, Book B);

void writeBList(FILE* fw, BookList L);

void removeBook(Book& B);

bool checkEmptyBookList(BookList L);

BookNode* FindBData(BookList L, char data[], int a);

void RemoveBHead(BookList& L);

void RemoveBTail(BookList& L);

int RemoveBNode(BookList& L, char ISBN[]);

void removeListBook(BookList& L);

BookNode* AddTailBook(BookList& N, Book b);

void readListBook(FILE* fr, BookList& ListBook);

void changeISBN(Book& B);

void changeBname(Book& B);

void changeAuthor(Book& B);

void changePublisher(Book& B);

void changeByear(Book& B);

void changeGenre(Book& B);

void changePrice(Book& B);

void changeAmount(Book& B, int amount);

void AddBook(BookList& ListBook);

int outputBook(Book B);

void changeBook(Book& B, int x);

void menuChangeBook(BookList& L, char ISBN[]);

void FindnPrintBook(BookList L, char data[], int n);

void outputBList(BookList B);

void chucNang3AdminnManager(BookList& BL, User& U, int& log);

void chucNang3Librarian(BookList& BL, User& U, int& log);
