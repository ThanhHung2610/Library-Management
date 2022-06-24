#pragma once

#include "BOOK.h"
#include "READER.h"
#include "RECEIPT.h"

void getCurDay(Date& d);

void overdueReader(ReceiptList Re, ReadList RL);

int borBookNum(BookList BL);

void genderNum(ReadList RL);

int ReaderNum(ReadList RL);

void genreNum(BookList BL);

int bookNum(BookList BL);

void chucNang6(BookList BL, ReceiptList Re, ReadList RL, int& log, User& U);


