//include all neccessary header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//structure of user data
typedef struct info{
    char fname[20];
    char lname[20];
    char phone[11];
    char salary[15];
    char key[40];
    char education[20];
    int state;
}INFO;

//structure for trie node  by key value
typedef struct ktrie{
    struct ktrie* child[27];
    bool end;
    INFO *data;
}KTrie;

//structure for trie node  by phone value
typedef struct ptrie{
    struct ptrie* child[11];
    bool end;
    INFO *data;
}PTrie;


//create new node for user info.
INFO* newInfo(INFO obj)
{
    INFO *node=(INFO*)malloc(sizeof(INFO));
    strcpy(node->fname,obj.fname);
    strcpy(node->lname,obj.lname);
    strcpy(node->phone,obj.phone);
    strcpy(node->salary,obj.salary);
    strcpy(node->key,obj.key);
    strcpy(node->education,obj.education);
    node->state=obj.state;
    return node;
}

//create new node for KTrie
KTrie* newNodeK()
{
    int i=0;
    KTrie* node=(KTrie*)malloc(sizeof(KTrie));
    node->end=false;
    for(i=0;i<27;i++)
        node->child[i]=NULL;
    return node;
}

//create new node for PTrie
PTrie* newNodeP()
{
    int i=0;
    PTrie* node=(PTrie*)malloc(sizeof(PTrie));
    node->end=false;
    for(i=0;i<11;i++)
        node->child[i]=NULL;
    return node;
}

//insert by key value
void insertK(KTrie* root,INFO *inf)
{
    KTrie* node=root;
    int i=0,index,flg;
    for(i=0;(inf->key[i])!='\0';i++)
    {
        index=(inf->key[i])-'a';
        if(node->child[index]==NULL)
        {
            node->child[index]=newNodeK();
        }
        node=node->child[index];
    }
    node->end=true;
    node->data=inf;
}

//insert by phone value
void insertP(PTrie* root,INFO *inf)
{
    PTrie* node=root;
    int i=0,index,flg;
    for(i=0;(inf->phone[i])!='\0';i++)
    {
        index=(inf->phone[i])-'0';
        if(node->child[index]==NULL)
        {
            node->child[index]=newNodeP();
        }
        node=node->child[index];
    }
    node->end=true;
    node->data=inf;
}

//search by key
void searchByKey(KTrie* root,char* key,char *str)
{
    int flg=0,index,i;
    KTrie* node=root;
    for(i=0;key[i]!='\0';i++)
    {
        index=key[i]-'a';
        if(node->child[index]==NULL)
        {
            flg=1;
            break;
        } 
        node=node->child[index];
    }
    if(flg==0)
    {
        if(node->end==true && node->data->state==1)
        {
            printf("\nEmployee Name: %s %s",node->data->fname,node->data->lname);
            printf("\nPhone No: %s",node->data->phone);
            printf("\nEducation: %s",node->data->education);
            printf("\nSalary: %s",node->data->salary);
            printf("Key-Name: %s",node->data->key);
            strcpy(str,node->data->phone);
            return;
        }
        else
        {
            printf("\nUser not found!");
            strcpy(str,"0000000000");
        }
    }
    else
    {
        printf("\nUser not found!");
        strcpy(str,"0000000000");
    }
    return;
}   


//Serach by phone nummber
void searchByPhone(PTrie* root,char* key)
{
    int flg=0,index,i;
    PTrie* node=root;
    for(i=0;key[i]!='\0';i++)
    {
        index=key[i]-'0';
        if(node->child[index]==NULL)
        {
            flg=1;
            break;
        } 
        node=node->child[index];
    }
    if(flg==0)
    {
        if(node->end==true && node->data->state==1)
        {
            printf("\nEmployee Name: %s %s",node->data->fname,node->data->lname);
            printf("\nPhone No: %s",node->data->phone);
            printf("\nEducation: %s",node->data->education);
            printf("\nSalary: %s",node->data->salary);
            printf("Key-Name: %s",node->data->key);
        
            return;
        }
        else
        {
            printf("\nUser not found!");
        }
    }
    else
    {
        printf("\nUser not found!");
    }
    return;
}   


//check already existing data by key     return  1-->for exits and 0-->for not exits
int checkByKey(KTrie* root,char* key)
{
    int flg=0,index,i;
    KTrie* node=root;
    for(i=0;key[i]!='\0';i++)
    {
        index=key[i]-'a';
        if(node->child[index]==NULL)
        {
            node=NULL;
            flg=1;
            break;   
        }
        node=node->child[index];
    }
    if(flg==0)
    {
        if(node->end==true && node->data->state==1)
            return 1;
        else    
            return 0;
    }
    else    
        return 0;
    return 0;
}

//check already existing data by phone no     return  1-->for exits and 0-->for not exits
int checkByPhone(PTrie* root,char* key)
{
    int flg=0,index,i;
    PTrie* node=root;
    for(i=0;key[i]!='\0';i++)
    {
        
		index=key[i]-'0';
        if(node->child[index]==NULL)//not found
        {
            node=NULL;
            flg=1;
            break;   
        }
        node=node->child[index];
    }
    if(flg==0)//found
    {
        if(node->end==true && node->data->state==1)
            return 1;
        else    
            return 0;
    }
    else    
        return 0;
    return 0;
}


//deletion of record by using key
void deleteByKey(KTrie* root, char* key)
{
    int i,index;
    KTrie* node=root;
    for(i=0;i<strlen(key);i++)
    {
        index=key[i]-'a';
        if(index<0 || index>=27)//not found 
        {
            printf("\nDATA NOT FOUND");
            return;
        }
        node=node->child[index];
    }
    if(node!=NULL)
    {
        if(node->end==true && node->data->state==1)
        {
            node->data->state=0;
            printf("\nDATA DELETED SUCESSFULLY FROM TRIE");
            return;
        }
        else{
            printf("\nDATA NOT FOUND");
            return;
        }
    }
    else{
        printf("\nDATA NOT FOUND");
            return;
    }
}

//deletion of record by using phone no.
void deleteByPhone(PTrie* root, char* key)
{
    int i,index;
    PTrie* node=root;
    for(i=0;i<strlen(key);i++)
    {
        index=key[i]-'0';
        if(index<0 || index>=11)//not found 
        {
            printf("\nDATA NOT FOUND");
            return;
        }
        node=node->child[index];
    }
    if(node!=NULL)
    {
        if(node->end==true && node->data->state==1)
        {
            node->data->state=0;
            printf("\nDATA DELETED SUCESSFULLY FROM TRIE");
            return;
        }
        else{
            printf("\nDATA NOT FOUND");
            return;
        }
    }
    else{
        printf("\nDATA NOT FOUND");
            return;
    }
}

//check weather input is valid or not
int checkValid(char* str,int flg)
{
    int i,validity=1;
    if(flg==1)  //check for string
    {
        for(i=0;str[i]!='\0';i++)
        {
            if(str[i]>=97 && str[i]<=122)
                continue;
            else
            {
                validity=0;
                break;
            }
        }
    }
    else
    {
        for(i=0;str[i]!='\0';i++)   //check for phone no
        {
            if(str[i]>=48 && str[i]<=57)
                continue;
            else
            {
                validity=0;
                break;
            }
        }
        if(i!=10 && flg==0)//invalid no.
            validity=0;
    }
    return validity;
}

//Input data  from user
int inputData(INFO* data,KTrie* kroot,PTrie* proot)
{
    int flg=0;
    printf("\n -------------------------Enter Faculty Data-------------------------\n");
    printf("\n{Enter data in lowercase}\n");
    while(flg<3)
    {
        printf("\nEnter First Name: ");
        scanf("%s",data->fname);
        if(checkValid(data->fname,1))
            break;
        else
        {
            printf("\nINvalid Data");
            flg++;
        }
    }
    if(flg==3)
    {
        printf("\nSorry try again :)");
        return 0;
    }
    //------------------------------
    flg=0;
    while(flg<3)
    {
        printf("\nEnter Last Name: ");
        scanf("%s",data->lname);
        if(checkValid(data->lname,1))
            break;
        else
        {
            printf("\nInvalid Data");
            flg++;
        }
    }
    if(flg==3)
    {   
        printf("\nSorry try again :)");
        return 0;
    }
    //------------------------------
    flg=0;
    while(flg<3)
    {
        printf("\nEnter Key(must be unique) {only lowercase alphabets}: ");
        scanf("%s",data->key);
        if(checkValid(data->key,1))
        {
            if(checkByKey(kroot,data->key))
            {
                printf("\nKey Already Exits---Reenter the key");
                flg++;
            }
            else
                break;    
        }    
        else
        {
            printf("\nInvalid Data");
            flg++;
        }
    }
    if(flg==3)
    {
        printf("\nSorry try again :)");
        return 0;
    }
    //-------------------------------
    flg=0;
    while(flg<3)
    {
        printf("\nEnter Phone number: ");
        scanf("%s",data->phone);
        if(checkValid(data->phone,0))
        {
            if(checkByPhone(proot,data->phone))
            {
                printf("\nPhone Already Exits---Renter the Phone no.");
                flg++;
            }
            else
                break;    
        }    
        else
        {
            printf("\nInvalid Data");
            flg++;
        }
    }
    if(flg==3)
    {
        printf("\nSorry try again :)");
        return 0;
    }
    //----------------

    printf("\nEnter Education: ");
    scanf("%s",data->education);
   
    //-------------------
    flg=0;
    while(flg<3)
    {
        printf("\nEnter Salary: ");
        scanf("%s",data->salary);
        if(checkValid(data->salary,2))
            break;
        else
        {
            printf("\nInvalid Data");
            flg++;
        }
    }
    if(flg==3)
    {   
        printf("\nSorry try again :)");
        return 0;
    }

    return 1;
}
//modification in file
void modification_in_file(FILE *file,INFO obj,KTrie* kroot,PTrie* proot)
{
    int pos;
    KTrie* knode;
    PTrie* pnode;
    INFO obj1;
    INFO* ptr;
    rewind(file);
    while(1)
    {
        pos=ftell(file);
        fscanf(file,"%s %s %s %s %s %s %d",&obj1.fname,&obj1.lname,&obj1.key,&obj1.phone,&obj1.salary,&obj1.education,&obj1.state);
        if(feof(file))
            break;
        if(strcmp(obj.key,obj1.key)==0)
            break;
    }
    if(feof(file))
    {
        printf("\nData not found\n");
        return;
    }
    printf("\n\t\t\tEnter Modified data\t\t\t\n");
    printf("________________________________________________________________________________________");
    deleteByKey(kroot,obj.key);
    deleteByPhone(proot,obj.phone);
    if(!inputData(&obj1,kroot,proot))
        return;
    obj1.state=1;
    ptr=newInfo(obj1);
    fseek(file,pos,SEEK_SET);
    fprintf(file,"\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",obj1.fname,obj1.lname,obj1.key,obj1.phone,obj1.education,obj1.salary,obj1.state);
    insertK(kroot,ptr);
    insertP(proot,ptr);
    return;
}

//adding data to file
void add_in_file(FILE* file,INFO obj)
{
    fseek(file,0,SEEK_END);
    fprintf(file,"\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",obj.fname,obj.lname,obj.key,obj.phone,obj.salary,obj.education,obj.state);
}

//delete data from file
void delete_from_file(FILE *file,INFO obj)
{
    int pos;
    INFO obj1;
    rewind(file);
    while(1)
    {
        pos=ftell(file);
        fscanf(file,"%s %s %s %s %s %s %d",&obj1.fname,&obj1.lname,&obj1.key,&obj1.phone,&obj1.salary,&obj1.education,&obj1.state);
        if(feof(file))
            break;
        if(strcmp(obj.key,obj1.key)==0)
            break;
    }
    fseek(file,pos,SEEK_SET);
    obj1.state=0;
    fprintf(file,"\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",obj1.fname,obj1.lname,obj1.key,obj1.phone,obj1.salary,obj1.education,obj1.state);
}


void displayAll(FILE *file)
{
    INFO obj1;
    rewind(file);
    system("cls");
    printf("\n___________________________________________________________________________________________\n");
    printf("\n        First-Name                Surname           Phone No.                  Education               Salary\n");
    printf("\n___________________________________________________________________________________________\n");

    while(1)
    {
        fscanf(file,"%s %s %s %s %s %s %d",&obj1.fname,&obj1.lname,&obj1.key,&obj1.phone,&obj1.salary,&obj1.education,&obj1.state);
        if(feof(file))
            break;
        if(obj1.state==1)
        {
            printf("  %15s\t%15s  \t%15s  \t%15s  \t%15s\n",obj1.fname,obj1.lname,obj1.phone,obj1.education,obj1.salary);
        }
    }
    printf("\n\n\n\n");
}
