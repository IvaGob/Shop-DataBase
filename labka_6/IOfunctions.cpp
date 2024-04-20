#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void ReadReferenceFile(RefItem* arr, char* refFileName, int* i) {
    FILE* file = fopen(refFileName, "r");
    if (file != NULL) {
        SkipHeader(file);
        char c = '\0';
        RefItem refArr[MAXITEMS];
        RefItem newRef;
        c = fgetc(file);
        while (c != EOF) {
            if (*i > MAXITEMS)break;
            char valueS[N] = { '\0' };
            int j = 0;
            while (c != ',') {
                valueS[j++] = c;
                c = fgetc(file);
            }
            c = fgetc(file);
            newRef.code = atoi(valueS);
            /*newRef.code[j] = '\0';*/
            memset(valueS, 0, strlen(valueS));
            c = fgetc(file);
            //fscanf(file, "%d", &newRef.code);

            j = 0;
            while (c != '\n') {

                valueS[j++] = c;
                c = fgetc(file);
                if (c == EOF)break;
            }
            newRef.value = atof(valueS);
            //fscanf(file, "%f", &newRef.value);
            arr[*i].code = newRef.code;
            arr[*i].value = newRef.value;
            *i = *i + 1;
            c = fgetc(file);


        }
    }
    else {
        printf("Помилка відкриття файлу бази");
    }
}
//Записати запис у певний файл
void WriteRecord(Item newItem, FILE* file) {
    //Записати назву
    fputs(newItem.name, file);
    fputs(" ", file);
    //записати код
    char s[N] = "\0";
    sprintf(s, "%d", newItem.code);
    fputs(s, file);
    fputs(" ", file);
    //записати кількість
    memset(s, 0, strlen(s));
    sprintf(s, "%d", newItem.number);
    fputs(s, file);
    fputs(" ", file);
    //записати дату
    fputs(newItem.data, file);
    fputs("\n", file);
}
//звірити код запису з кодами в базі
bool CheckReferenceCodes(RefItem* Refarr, int code) {
    int i = 0;

    while (i < MAXITEMS) {
        if (code == Refarr[i++].code)return true;
    }

    return false;
}

//Прочитати файл записів
void ReadRecordsFile(Item* arr, RefItem* ref, char* recFileName, int* i) {
    FILE* file = fopen(recFileName, "r");
    if (file != NULL) {
        *i = 0;
        Item newItem;
        char c = '\0';
        c = fgetc(file);
        while (c != EOF) {
            if (*i > MAXITEMS)break;
            int j = 0;
            while (c != ' ') {
                if (c == EOF)break;
                newItem.name[j++] = c;
                c = fgetc(file);
            }
            newItem.name[j] = '\0';
            j = 0;
            char valueS[N] = "\0";
            c = fgetc(file);
            while (c != ' ') {
                if (c == EOF)break;
                valueS[j++] = c;
                c = fgetc(file);
            }

            newItem.code = atoi(valueS);
            if (CheckReferenceCodes(ref, newItem.code)) {
                memset(valueS, 0, strlen(valueS));
                j = 0;
                c = fgetc(file);
                while (c != ' ') {
                    valueS[j++] = c;
                    c = fgetc(file);
                }
                newItem.number = atoi(valueS);
                if (newItem.number > 0) {
                    j = 0;
                    c = fgetc(file);
                    while (c != '\n') {
                        if (c == EOF)break;
                        newItem.data[j++] = c;
                        c = fgetc(file);
                    }
                    newItem.data[j] = '\0';
                    arr[*i].code = newItem.code;
                    strcpy(arr[*i].name, newItem.name);
                    arr[*i].number = newItem.number;
                    strcpy(arr[*i].data, newItem.data);
                    *i = *i + 1;
                    c = fgetc(file);
                }
                else {
                    printf("Помилка у записі %d, кількість товару повинна бути більше 0!\n", i + 1);
                }

            }
            else {
                printf("Помилка у записі %d, код товару не збігається з базою!\n", i + 1);
            }

        }
    }
    else {
        printf("Помилка відкриття файлу записів");
    }

}

//Додати новий запис
void AddRecord(char* recFileName, RefItem* ref, Item* itemArr, int* i) {

    if (*i < MAXITEMS) {
        Item newItem;
        printf("Введіть код товару:\n");
        scanf("%d", &newItem.code);
        if (CheckReferenceCodes(ref, newItem.code)) {
            //
            printf("Введіть назву товару:\n");
            scanf("%s", &newItem.name);
            //
            printf("Введіть кількість товару:\n");
            int num = 0;
            scanf("%d", &num);
            if (num > 0) {
                newItem.number = num;
                printf("Введіть дату надходження товару(ДД.ММ.РР):\n");
                scanf("%s", &newItem.data);
                //
                itemArr[*i].code = newItem.code;
                strcpy(itemArr[*i].name, newItem.name);
                itemArr[*i].number = newItem.number;
                strcpy(itemArr[*i].data, newItem.data);
                //
                FILE* file = fopen(recFileName, "a");
                WriteRecord(newItem, file);
                *i = *i + 1;
            }
            else {
                printf("Кількість товару не може бути менше 0");
            }

        }
        else {
            printf("Такий код в базі не існує!");
        }

    }
    else {
        printf("Ви досягли ліміту кількості предметів");
    }
}

//
void PrintRecords(Item* arr, int n) {
    printf("Всі записи в файлі з записами:\n");
    for (int i = 0; i < n; i++) {
        printf("%d запис: \n\tНайменування: %s\n\tКод: %d \n\tКількість: %d\n\tДата: %s\n", i + 1, arr[i].name, arr[i].code, arr[i].number, arr[i].data);
    }
}

//
void DeleteRecord(char* recFileName, Item* itemArr, RefItem* refItems, int* n, int i) {
    FILE* file = fopen(recFileName, "w");
    for (int j = 0; j < *n; j++) {
        if (j != i - 1) {
            WriteRecord(itemArr[j], file);
        }
        else {
            printf("%d!!!!!!", i - 1);
        }
    }
    ReadRecordsFile(itemArr, refItems, recFileName, n);
}