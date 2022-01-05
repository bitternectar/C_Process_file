/*
* lab07.cpp - ������� ���� �������.
* Copyright (C) 2021 ����������� �.�. <mistertonyragrel@gmail.com>
*
* ������ ��������� ������ ������ �������� � ��������� �����.
* ���� ��������� �������� 03.01.2021
* ��������� �������� �� �������� GNU
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define mAUTHOR "[3] - �� ������"
#define AUTHOR "����������� ������ ����������"
#define PROCESS_FILE "[2] - ���������� ����"
#define CREATE_FILE "[1] - ������� ���� example.txt"
#define EXIT "[0] - �����"
#define DESCRIPTION "��������� ��� ��������� ���������� �����."
#define BUFFER_SIZE 5
#define STR_SIZE 101


void showMenu();
void processFile();
void createExampleFile();
void showFileContents(FILE*);

int main(void){
    setlocale(LC_ALL, "RUS");

    int choose; // ���������� ��� �������� ������ ������������

    printf("%s\n",DESCRIPTION);
    showMenu(); // ������� ����

    while(scanf("%d", &choose)==1 && choose != 0){
        switch(choose){
            case 1:
                createExampleFile();
                showMenu();
                break;
            case 2:
                processFile(); // ������������ ���������� ����� � ��������� ���������� � ����� ����
                showMenu();
                break;
            case 3:
                printf("\n%s\n\n", AUTHOR);
                showMenu(); // ������� ����
                break;
            default:
                printf("\n����� ������� ���. ����������, ������� ������� �� ������:\n\n");
                showMenu(); // ������� ����
        }
    }
    return 0;
}

void showMenu(){
    // ������� ����
    printf("\n%s\n",CREATE_FILE);
    printf("%s\n",PROCESS_FILE);
    printf("%s\n",mAUTHOR);
    printf("%s\n\n",EXIT);
    printf("��� �����: ");
}

/*
    ������� ������������ ����� �����, �������� �������� ������ ������������,
    ����� ��� ������� ����� ������� ��������
    �� ������� ����� � ������� ��������
*/
void processFile(){

    printf("\n������� ����� ��� ������� ����� ������� "
           "�������� �� ����� ��������  ��������.\n\n");

    const char *fileName; // ���������� ��� �������� ������ ������ � ��������� �����
    FILE *fr, *fw;

    printf("\n������� �������� �����, ������� ���������� ����������: ");

    scanf("%s", fileName); // ������������ ������ �������� �����
    getchar(); // ������� ������ �������� ������

    fr = fopen(fileName, "r"); //��������� ���� ��� ������
    fw = fopen("result.txt", "w"); // ��������� ���� ��� ������

    //-------- �������������� ������� ���� ������� �������� --------

    if(fr){
        while(!feof(fr)){ // ��������������� � ���������� ������� �� ����� fileName � result.txt
            char ch;
            if(fscanf(fr, "%c", &ch)!= EOF){
                if(ch>='�' && ch<='�') ch = toupper(ch); // ��������������� ������� ����� �� ������� �������� � �������
                fprintf(fw, "%c", ch);
            }
        }
        fclose(fw);
        fclose(fr);

        //-------- ������� � ������� ���������� ����� result.txt --------

        printf("\n\n������ ���� result.txt.\n���������� result.txt:\n\n");
        fw = fopen("result.txt", "r"); // ��������� ���� � ����������� ��� ������
        if(fw) showFileContents(fw);   // ������� ���������� �����
        fclose(fw);

    }else{
        printf("�� ������� ������� ���� %s\n\n", fileName);
        fclose(fr);
        fclose(fw);
    }
}

/*
    ������� ������� ����-�������
*/
void createExampleFile(){

    //-------- ������ ����� ��� ����������� �����-������� --------

    char buffer[BUFFER_SIZE][STR_SIZE] = {
        "��������, test������, ��������!\n",
        "���� � �����test �����:\n",
        "���� ���������� � ������ ������,\n",
        "���� ����� ��� �test ���������� ����\n",
        "���� ������ ��� ����test����� ����������,\n"
    };

    //-------- ������� ���������� ������� � ���� --------

    FILE *fw = fopen("example.txt","w"); // ������� ���� ��� ������
    if(fw){
        for(int i=0; i<BUFFER_SIZE; i++) fprintf(fw, "%s", buffer[i]);
        fclose(fw); // ��������� ����

       //-------- ������� ��������� � ������� --------

        fw = fopen("example.txt", "rb"); // ��������� ��������� ���� ��� ������
        if(fw){
           printf("\n���������� ����� example.txt:\n\n");
           showFileContents(fw);
        }
        fclose(fw); // ��������� ����

    }else{
        printf("\n�� ������� ������� ���� example.txt\n");
        fclose(fw);
    }
}
/*
    ������� ��������� ������ � �����
    � ������� �� � �������
*/
void showFileContents(FILE *filePtr){
    while(!feof(filePtr)){ // ������� ��� ������� �� ����� � ����������� ����� ������
        char string[STR_SIZE];
        if(fgets(string, STR_SIZE, filePtr)!=NULL)
            printf("%s", string);
    }
    putchar('\n'); // ��������� � ����������� ����� ������ ������ �������� ������
    rewind(filePtr); // ���������� ��������� � ������ �����
}



