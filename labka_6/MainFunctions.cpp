#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
void SearchByName(Item* arr, int n) {
    int index[N] = { -1 };
    char s[N] = "\0";
    int count = 0;
    printf("Введіть назву:\n");
    scanf("%s", &s);
    printf("Знайдено за критерієм такі записи:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(s, arr[i].name) == 0) {
            count++;
            printf("%d запис: \n\tНайменування: %s\n\tКод: %d \n\tКількість: %d\n\tДата: %s\n", i + 1, arr[i].name, arr[i].code, arr[i].number, arr[i].data);
        }
    }
    printf("Всього знайдено %d записів", count);

}
void SearchByData(Item* arr, int n) {
    char s[N] = "\0";
    int count = 0;
    printf("Введіть дату^\n");
    scanf("%s", &s);
    printf("Знайдено за критерієм такі записи:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(s, arr[i].name) == 0) {
            count++;
            printf("%d запис: \n\tНайменування: %s\n\tКод: %d \n\tКількість: %d\n\tДата: %s\n", i + 1, arr[i].name, arr[i].code, arr[i].number, arr[i].data);
        }
    }
    printf("Всього знайдено %d записів", count);
}
void SearchByCode(Item* arr, int n) {
    int icode = 0;
    int count = 0;
    printf("Введіть код:\n");
    scanf("%d", &icode);
    printf("Знайдено за критерієм такі записи:\n");
    for (int i = 0; i < n; i++) {
        if (icode == arr[i].code)count++;
    }
    printf("Всього знайдено %d записів", count);
}

//
void GenerateSumItems(Item* ItemsArr, RefItem* refArr, SumItem* sumitem, int refn, int n, int* SumN) {
    int m = 0;
    for (int i = 0; i < refn; i++) {
        SumItem newSum;
        newSum.sumNumber = 0;
        newSum.sumValue = 0.0;
        newSum.code = refArr[i].code;
        for (int j = 0; j < n; j++) {
            //memset(newSum.name, 0, strlen(newSum.name));

            if (ItemsArr[j].code == refArr[i].code) {
                strcpy(newSum.name, ItemsArr[j].name);
                newSum.sumNumber += ItemsArr[j].number;
                m++;
            }
        }
        newSum.sumValue = newSum.sumNumber * refArr[i].value;
        sumitem[*SumN].code = newSum.code;
        strcpy(sumitem[*SumN].name, newSum.name);
        sumitem[*SumN].sumNumber = newSum.sumNumber;
        sumitem[*SumN].sumValue = newSum.sumValue;
        *SumN = *SumN + 1;
        m = 0;
    }
}

//Поміняти місцями SumItem
void Swap(SumItem destination, SumItem source) {
    SumItem buffer;
    buffer.code = destination.code;
    buffer.sumNumber = destination.sumNumber;
    buffer.sumValue = destination.sumValue;
    strcpy(buffer.name, destination.name);
    //
    destination.code = source.code;
    destination.sumNumber = source.sumNumber;
    destination.sumValue = source.sumValue;
    strcpy(destination.name, source.name);
    //
    source.code = destination.code;
    source.sumNumber = destination.sumNumber;
    source.sumValue = destination.sumValue;
    strcpy(source.name, destination.name);
}
//Відсортувати заг. товарів
void SortSumItems(SumItem* arr, int n) {
    for (int startIndex = 0; startIndex < n - 1; ++startIndex)
    {
        int smallestIndex = startIndex;
        for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex)
        {
            if (arr[currentIndex].sumValue < arr[smallestIndex].sumValue)
                smallestIndex = currentIndex;
        }
        Swap(arr[startIndex], arr[smallestIndex]);
    }
}
//вивести загю товарів
void PrintSumItems(Item* ItemsArr, RefItem* refArr, SumItem* sumitem, int refn, int n, int* SumN) {
    GenerateSumItems(ItemsArr, refArr, sumitem, refn, n, SumN);
    SortSumItems(sumitem, *SumN);
    printf("Загальні відомості:\n");
    for (int i = 0; i < *SumN; i++) {
        printf("-------------------\n");
        printf("\tНазва: %s\n", sumitem[i].name);
        printf("\tКод: %d\n", sumitem[i].code);
        printf("\tЗагальна кількість: %d\n", sumitem[i].sumNumber);
        printf("\tЗагальна ціна: %f\n", sumitem[i].sumValue);
    }
}
