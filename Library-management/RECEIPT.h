#pragma once
#include "BOOK.h"
#include "READER.h"

bool checkAvaiBook(Book B);

void borrowBook(ReadList RL, BookList& BL, ReceiptList& ReL);

void initMatrix(char ISBN[20][9]);

void writeReceipt(FILE* fw, Receipt B);

void writeReList(FILE* fw, ReceiptList RL);

void readReceipt(FILE* fr, Receipt& Re);

void removeReceipt(Receipt& B);

bool checkEmptyReList(ReceiptList L);

ReceiptNode* FindReData(ReceiptList L, char data[]);

void RemoveReHead(ReceiptList& L);

void RemoveReTail(ReceiptList& L);

void RemoveReNode(ReceiptList& L, char ID[]);

void removeListReceipt(ReceiptList& L);

ReceiptNode* AddTailReceipt(ReceiptList& N, Receipt b);

void readListReceipt(FILE* fr, ReceiptList& ListReceipt);

void outputBorReceipt(Receipt B);

bool IsEmptyFile(FILE* f);

int DayNum(int d, int m, int y);

int DiffDays(int d1, int m1, int y1, int d2, int m2, int y2);

double fineMoney(BookList& BL, ReceiptList& Re, ReceiptNode*& p, char ID[], int a);

void outputRetReceipt(BookList& BL, ReceiptList& Re, char ID[], int a);

bool IsBorBook(Receipt B, char* ISBN);

bool checkBorReader(ReceiptList Re, char* ID);
