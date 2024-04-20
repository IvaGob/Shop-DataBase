#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "header.h"

RefItem refItems[MAXITEMS];
Item items[MAXITEMS];
SumItem Sumitems[MAXITEMS];
int refItemN = 0;
int itemN = 0;
int SumItemN = 0;

void SkipHeader(FILE* file) {
    char a = '\0';
    while (a != '\n') {
        if (a == EOF)break;
        a = fgetc(file);
    }
}


//C:\\Laba\\Reference.itemref
//C:\\Laba\\Base.item
int main()
{
    system("chcp 1251");

    extern RefItem refItems[MAXITEMS];
    extern Item items[MAXITEMS];
    extern SumItem Sumitems[MAXITEMS];
    extern int refItemN;
    extern int itemN;
    extern int SumItemN;
    //Ввід назви файлу бази
    static char refFileName[N] = { '\0' };
    printf("Введіть ім'я бази: \n");
    fgets(refFileName, sizeof(refFileName) / sizeof(char), stdin);
    refFileName[strcspn(refFileName, "\r\n")] = 0;

    //Ввід файлу з записами
    char recFileName[N] = { '\0' };
    printf("Введіть ім'я файлу з записами: \n");
    fgets(recFileName, sizeof(recFileName) / sizeof(char), stdin);
    recFileName[strcspn(recFileName, "\r\n")] = 0;
    //


    ReadReferenceFile(refItems, refFileName, &refItemN);
    ReadRecordsFile(items, refItems, recFileName, &itemN);

    int choice = 0;
    do {
        fflush(stdin);
        printf("\nMenu:\n");
        printf("1. Додати новий запис\n");
        printf("2. Роздрукувати всі дані\n");
        printf("3. Пошук товарів\n");
        printf("4. Видалити запис\n");
        printf("5. Вивести Узагальнення товарів\n");
        printf("6. Завершити роботу\n");
        printf("Оберіть дію:\n");
        scanf("%d", &choice);
        int i = 0;
        switch (choice) {
        case 1:
            //
            AddRecord(recFileName, refItems, items, &itemN);
            break;
        case 2:
            //
            PrintRecords(items, itemN);
            break;
        case 3:
            //
            printf("1. Шукати по назві\n2. Шукати по даті\n3. Шукати по коду\n4. Повернутись в меню\n");
            scanf("%d", &i);
            switch (i) {
            case 1:
                SearchByName(items, itemN);
                break;
            case 2:
                SearchByData(items, itemN);
                break;
            case 3:
                SearchByCode(items, itemN);
                break;
            case 4:
                break;
            default:
                break;
            }
            break;
        case 4:
            printf("Введіть номер запису який ви хочете видалити:\n");

            scanf("%d", &i);
            DeleteRecord(recFileName, items, refItems, &itemN, i);
            break;
        case 5:
            PrintSumItems(items, refItems, Sumitems, refItemN, itemN, &SumItemN);
            break;
        case 6:
            printf("Завершення роботи\n");
            break;
        default:
            printf("\nНаправильний вибір. Спробуйте ще раз\n");
            fflush(stdin);
        }
    } while (choice != 6);

    return 0;
}