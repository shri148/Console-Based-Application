#include<stdio.h>
#include"functions.h"

void main()
{
    int num,flg;
    char opt,tem;
    char str[30],tmp[30];
    FILE *file;
    INFO data;
    INFO *ptr;
    KTrie *ptr_key=newNodeK();
    PTrie *ptr_phone=newNodeP();
    KTrie *dummy;
    PTrie *fake;
    //HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    // system("color f1");
    printf("\n======================================================================================================================\n");
    printf("\n*********************           COLLEGE DEPARTMENTAL FACULTY DETAILS MANAGEMENT SYSTEM         ***********************\n");
    printf("\n======================================================================================================================\n");
    printf("\n\tCHOOSE YOUR DEPARTMENT\n");
    init:
    printf("\n\t1.COMPUTER SCIENCE ENGINEERING\n\t2.IT ENGINEERING\n\t3.MECHANICAL ENGINEERING\n\t4.ELECTRICAL ENGINEERING\n\t5.CIVIL ENGINEERING\n  Option:");
    scanf("%c%c",&opt,&tem);
    switch(opt)
    {
    case '1':
        file=fopen("cse.txt","r+");
        if(!file)
        {
            file=fopen("cse.txt","w");
            fclose(file);
            file=fopen("cse.txt","r+");
        }
        system("cls");
    printf("\n*********************             WELCOME TO COMPUTER SCIENCE & ENGG DEPARTMENT                 ***********************\n");

        break;
    case '2':
        file=fopen("it.txt","r+");
        if(!file)
        {
            file=fopen("it.txt","w");
            fclose(file);
            file=fopen("it.txt","r+");
        }
                system("cls");
        printf("\n*********************             WELCOME TO INFORMATION TECHNOLOGY DEPARTMENT                 ***********************\n");
        break;
    case '3':
        file=fopen("mech.txt","r+");
        if(!file)
        {
            file=fopen("mech.txt","w");
            fclose(file);
            file=fopen("mech.txt","r+");
        }
                system("cls");
        printf("\n*********************                    WELCOME TO MECHANICAL ENGG DEPARTMENT                 ***********************\n");
        break;
    case '4':
        file=fopen("elect.txt","r+");
        if(!file)
        {
            file=fopen("elect.txt","w");
            fclose(file);
            file=fopen("elect.txt","r+");
        }
                system("cls");
        printf("\n*********************                    WELCOME TO ELECTRICAL ENGG DEPARTMENT                  ***********************\n");
        break;
    case '5':
        file=fopen("civil.txt","r+");
        if(!file)
        {
            file=fopen("civil.txt","w");
            fclose(file);
            file=fopen("civil.txt","r+");
        }
                system("cls");
        printf("\n*********************                     WELCOME TO CIVIL ENGG DEPARTMENT                      ***********************\n");
        break;
    default:
        printf("\nInvalid option\n");
        goto init;
        break;
    }


    while(1)
    {
        fscanf(file,"%s %s %s %s %s %s %d",&data.fname,&data.lname,&data.key,&data.phone,&data.education,&data.salary,&data.state);
        if(feof(file))
            break;
        ptr=newInfo(data);
      // printf("%s %s %s %s %d",data.firname,data.surname,data.key,data.phone,data.state);
      if(data.state==1)
     {
        insertK(ptr_key,ptr);// printf("\nInserted in N");
        insertP(ptr_phone,ptr);  // printf("\nInserted in P");
     }
    }
   // printf("\nFaculty Data Management Project\n");
    printf("\n******NOTE: All names should be in lowercase & key name should be given without space.\n");
    while(1)
    {
        fflush(stdin);
        printf("\n\tMenu\n\t1.Add data\n\t2.Modify\n\t3.Search by Key name\n\t4.Search by Phone Number\n\t5.Delete data\n\t6.Display All Data\n\t7.Exit\n  Option:");
        //scanf("%c",&opt);
        opt=getc(stdin);

        if(opt=='7')
            break;
        switch(opt)
        {
        case '1':
            system("cls");
            if(!inputData(&data,ptr_key,ptr_phone))
                break;
            data.state=1;
            ptr=newInfo(data);
            add_in_file(file,*ptr);
         //   printf("\nSuccess\n");
            insertK(ptr_key,ptr);
           //  printf("\nSuccess\n");
            insertP(ptr_phone,ptr);
           //  printf("\nSuccess\n");
           printf("\nRECORD ADDED SUCCESSFULLY!!\n");

            break;
        case '2':
            system("cls");
             printf("\nEnter Key name:");
            scanf("%s",data.key);
            if(!checkValid(data.key,1))
            {
                printf("\nInvalid data\n");
                break;
            }
            printf("\nEnter phone number:");
            scanf("%s",data.phone);
            if(!checkValid(data.phone,0))
            {
                printf("\nInvalid data\n");
                break;
            }
            data.state=1;
            ptr=newInfo(data);

            modification_in_file(file,*ptr,ptr_key,ptr_phone);
            printf("\nRECORD MODIFIED SUCCESSFULLY!!\n");
            break;
        case '3':
            system("cls");
            printf("\nEnter key name to search:");
            scanf("%s",str);
            if(!checkValid(str,1))
            {
                printf("\nInvalid Input");
                break;
            }
            searchByKey(ptr_key,str,tmp);
            break;
        case '4':
            system("cls");
            printf("\nEnter phone to search:");
            scanf("%s",str);
            if(!checkValid(str,0))
            {
                printf("\nInvalid Input");
                break;
            }
            searchByPhone(ptr_phone,str);
            break;
        case '5':
            system("cls");
            printf("\nEnter key name to delete:");
            scanf("%s",data.key);
            if(!checkValid(data.key,1))
            {
                printf("\nInvalid Input");
                break;
            }
             searchByKey(ptr_key,data.key,tmp);
             if(strcmp(tmp,"0000000000")==0)
                break;
             strcpy(data.phone,tmp);
            delete_from_file(file,data);
            deleteByKey(ptr_key,data.key);
            deleteByPhone(ptr_phone,data.phone);
            printf("\nRECORD DELETED SUCCESSFULLY!!\n");
            break;
        case '6':
            displayAll(file);
            break;
        default:
           // SetConsoleTextAttribute(hStdOut,(FOREGROUND_RED | BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED));
            printf("\nInvalid Option");
            break;
        }
    }
    fclose(file);
    return;
}
