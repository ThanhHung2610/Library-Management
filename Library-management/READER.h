#pragma once
#include "LIBRARY.h"

void readReader(FILE* fr, Reader& R);

void writeReader(FILE* fw, Reader R);

void writeRList(FILE* fw, ReadList L);

void removeReader(Reader& R);

void removeListReader(ReadList& L);

bool checkEmptyReadList(ReadList L);

ReadNode* AddTailReader(ReadList& N, Reader r);

ReadNode* FindRData(ReadList L, char data[], int a);

void RemoveRHead(ReadList& l);

void RemoveRTail(ReadList& l);

int RemoveRNode(ReadList& L, char ID[]);

void readListReader(FILE* fr, ReadList& ListReader);

void changeRid(Reader& R);

void changeRname(Reader& R);

void changeRIdcard(Reader& R);

void changeRbirthday(Reader& R);

void changeRgender(Reader& R);

void changeRemail(Reader& R);

void changeRaddress(Reader& R);

void addRcreDate(Reader& R);

void addRexpDate(Reader& R);

void AddReader(ReadList& ListReader);

void outputRList(ReadList R);

int outputReader(Reader R);

void changeReader(Reader& R, int x);

void menuChangeReader(ReadList& L, char ID[]);

void FindnPrintReader(ReadList L, char data[], int n);

void chucNang2AdminnManager(ReadList& RL, User& U, int& log);

void chucNang2Librarian(ReadList& RL, User& U, int& log);
