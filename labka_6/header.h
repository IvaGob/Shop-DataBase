#ifndef HEADERF_H
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#define HEADERF_H
#define MAXITEMS 100
#define N 100

typedef struct {
    int code;
    double value;
}RefItem;

typedef struct {
    int code;
    char name[N];
    int number;
    char data[N];
}Item;

typedef struct {
    int code;
    char name[N];
    int sumNumber;
    double sumValue;
}SumItem;

void SkipHeader(FILE* file);
void ReadReferenceFile(RefItem* arr, char* refFileName, int* i);
//void WriteRecord(Item newItem, FILE* file);
void AddRecord(char* recFileName, RefItem* ref, Item* itemArr, int* i);
void PrintRecords(Item* arr, int n);
void DeleteRecord(char* recFileName, Item* itemArr, RefItem* refItems, int* n, int i);
void ReadRecordsFile(Item* arr, RefItem* ref, char* recFileName, int* i);
bool CheckReferenceCodes(RefItem* Refarr, int code);
void SearchByName(Item* arr, int n);
void SearchByData(Item* arr, int n);
void SearchByCode(Item* arr, int n);
void GenerateSumItems(Item* ItemsArr, RefItem* refArr, SumItem* sumitem, int refn, int n, int* SumN);
void Swap(SumItem destination, SumItem source);
void SortSumItems(SumItem* arr, int n);
void PrintSumItems(Item* ItemsArr, RefItem* refArr, SumItem* sumitem, int refn, int n, int* SumN);

#endif // ך³םוצü פאיכא headerf.h
