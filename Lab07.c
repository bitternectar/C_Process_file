/*
* lab07.cpp - главный файл проекта.
* Copyright (C) 2021 Смирновский М.Е. <mistertonyragrel@gmail.com>
*
* Данная программа решает задачу создания и обработки файла.
* Дата последней редакции 03.01.2021
* Программа доступна по лицензии GNU
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define mAUTHOR "[3] - Об авторе"
#define AUTHOR "Смирновский Михаил Евгеньевич"
#define PROCESS_FILE "[2] - Обработать файл"
#define CREATE_FILE "[1] - Создать файл example.txt"
#define EXIT "[0] - Выход"
#define DESCRIPTION "Программа для обработки текстового файла."
#define BUFFER_SIZE 5
#define STR_SIZE 101


void showMenu();
void processFile();
void createExampleFile();
void showFileContents(FILE*);

int main(void){
    setlocale(LC_ALL, "RUS");

    int choose; // Переменная для хранения выбора пользователя

    printf("%s\n",DESCRIPTION);
    showMenu(); // Выводим меню

    while(scanf("%d", &choose)==1 && choose != 0){
        switch(choose){
            case 1:
                createExampleFile();
                showMenu();
                break;
            case 2:
                processFile(); // Обрабатываем содержимое файла и результат записываем в новый файл
                showMenu();
                break;
            case 3:
                printf("\n%s\n\n", AUTHOR);
                showMenu(); // Выводим меню
                break;
            default:
                printf("\nТакой команды нет. Пожалуйста, введите команду из списка:\n\n");
                showMenu(); // Выводим меню
        }
    }
    return 0;
}

void showMenu(){
    // Выводим меню
    printf("\n%s\n",CREATE_FILE);
    printf("%s\n",PROCESS_FILE);
    printf("%s\n",mAUTHOR);
    printf("%s\n\n",EXIT);
    printf("Ваш выбор: ");
}

/*
    Функция обрабатывает текст файла, название которого вводит пользователь,
    меняя все русский буквы нижнего регистра
    на русский буквы в верхнем регистре
*/
void processFile(){

    printf("\nФункция менят все русские буквы нижнего "
           "регистра на буквы верхнего  регистра.\n\n");

    const char *fileName; // Переменная для хранения адреса строки с названием файла
    FILE *fr, *fw;

    printf("\nВведите название файла, который необходимо обработать: ");

    scanf("%s", fileName); // Пользователь вводит название файла
    getchar(); // Убираем символ перевода строки

    fr = fopen(fileName, "r"); //Открываем файл для чтения
    fw = fopen("result.txt", "w"); // Открываем файл для записи

    //-------- Преобразование русских букв нижнего регистра --------

    if(fr){
        while(!feof(fr)){ // Преобразовываем и записываем символы из файла fileName в result.txt
            char ch;
            if(fscanf(fr, "%c", &ch)!= EOF){
                if(ch>='а' && ch<='я') ch = toupper(ch); // Преобразовываем русские буквы из нижнего регистра в верхний
                fprintf(fw, "%c", ch);
            }
        }
        fclose(fw);
        fclose(fr);

        //-------- Выведем в консоль содержимое файла result.txt --------

        printf("\n\nСоздан файл result.txt.\nСодержимое result.txt:\n\n");
        fw = fopen("result.txt", "r"); // Открываем файл с результатом для чтения
        if(fw) showFileContents(fw);   // Выводим содержимое файла
        fclose(fw);

    }else{
        printf("Не удалось открыть файл %s\n\n", fileName);
        fclose(fr);
        fclose(fw);
    }
}

/*
    Функция создает файл-образец
*/
void createExampleFile(){

    //-------- Массив строк для содержимого файла-образца --------

    char buffer[BUFFER_SIZE][STR_SIZE] = {
        "Отмщенье, testсударь, отмщенье!\n",
        "Паду к ногамtest твоим:\n",
        "Будь справедлив и накажи убийцу,\n",
        "Чтоб казнь его вtest позднейшие века\n",
        "Твой правый суд потоtestмству возвестила,\n"
    };

    //-------- Запишем содержимое массива в файл --------

    FILE *fw = fopen("example.txt","w"); // Создаем файл для записи
    if(fw){
        for(int i=0; i<BUFFER_SIZE; i++) fprintf(fw, "%s", buffer[i]);
        fclose(fw); // Закрываем файл

       //-------- Выведем результат в консоль --------

        fw = fopen("example.txt", "rb"); // Открываем созданный файл для чтения
        if(fw){
           printf("\nСодержимое файла example.txt:\n\n");
           showFileContents(fw);
        }
        fclose(fw); // Закрываем файд

    }else{
        printf("\nНе удалось создать файл example.txt\n");
        fclose(fw);
    }
}
/*
    Функция считывает данные с файла
    и выводит их в консоль
*/
void showFileContents(FILE *filePtr){
    while(!feof(filePtr)){ // Выводим все символы из файла в стандартный поток вывода
        char string[STR_SIZE];
        if(fgets(string, STR_SIZE, filePtr)!=NULL)
            printf("%s", string);
    }
    putchar('\n'); // Вставляем в стандартный поток вывода символ перевода строки
    rewind(filePtr); // Возвращаем указатель в начало файла
}



