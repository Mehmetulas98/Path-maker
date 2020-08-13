#include <dir.h>
#include <process.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <libgen.h>
///////////////////////////////////////////////////////////////////////////////////////////////////

void go(char* gidilicek)
{
change_dir(gidilicek);
return;
}

bool dir_control(const char *path){
    for(int i = 0 ; i < strlen(path) ; i++){
        if(!(isalpha(path[i])) && !(isdigit(path[i])) && !(path[i]=='*')  &&  !(path[i]=='_')  && !(path[i]=='/') ){
            return false;
        }
    }
    if(path[0]=='/' || path[strlen(path)-1]=='/' ){
        printf("/ burada olamaz \n");
        return false;
    }
    if(path[0]!='*'){
        for(int i=0;i<strlen(path);i++){
            if(path[i]=='*'){
                printf(" Hata var - üst dizine sadece baslangicda cikilabilir   ");
                return false;
            }
        }
    }
    else{
            printf("Hata yok  ");
        return true;
    }
}

bool isDirectoryExists(const char *path)
{
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode) && dir_control(path)==true)
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
int MAXSIZE = 8;
int stack_2[8];
int top_2 = -1;

int isempty_2() {
   if(top_2 == -1)
      return 1;
   else
      return 0;
}

int isfull_2() {
   if(top_2 == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek_2() {
   return stack_2[top_2];
}

int pop_2() {
   int data;
   if(!isempty_2()) {
      data = stack_2[top_2];
      top_2 = top_2 - 1;
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int push_2(int data) {
   if(!isfull_2()) {
      top_2 = top_2 + 1;
      stack_2[top_2] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}

////////////////////////////////////////////////////////////////////////////////////////

bool com_cont_1(char ch){

    if(ch == '<' ){
        return true;
    }
    return false;
}

bool com_cont_2(char ch){
    if(  ch == '>'){
        return true;
    }
    return false;
}

bool if_control(char* str){
    if(!strcmp(str, "if") ){
        return true;
    }
    else
        return false;
}

bool ifnot_control(char* str){
    if(!strcmp(str, "ifnot") ){
        return true;
    }
    else
        return false;
}

bool make_control(char* str){
    if(!strcmp(str, "make") ){
        return true;
    }
    else
        return false;
}

bool go_control(char* str){
    if(!strcmp(str, "go") ){
        return true;
    }
    else
        return false;
}

bool if_varlik(char* str){
    if( 1 )
        return true;
    else
        return false;
}

////////////////////////////////////////////////////////////////////////////////////////

bool if_acilis(char ch){
    if(ch=='{')
        return true;
    return false;
}

bool if_kapanma(char ch){
    if(ch=='}')
        return true;
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' )
        return (true);
    return (false);
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' ||
        ch == '=')
        return (true);
    return (false);
}

bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

bool isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "ifnot") ||
        !strcmp(str, "make") || !strcmp(str, "go")  )
        return (true);
    return (false);
}

char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void parse(char* str)
{
    blocks_controller(str);
    bool curly_cracket_acma=true;
    bool curly_cracket_kapama;
    int left = 0, right = 0;
    int len = strlen(str);
    int kontrol_open_index;
    int kontrol_close_index;
    bool kontrol=true;
    bool anlik_islem_go=false;
    bool anlik_islem_make=false;
    bool anlik_islem_if=false;
    bool anlik_islem_ifnot=false;

    // while döngüsü ile kodun içinde gezilir ve islem yapilir
    while (right <= len && left <= right) {
        char cwd[100];
        // bulunulan dizin
        getcwd(cwd,sizeof(cwd));
        // ciktilari daha anlamli yorumlamak icin degisken tutulur
        int make_sayac=0;

        if (isDelimiter(str[right]) == false)
            right++;
        if (isDelimiter(str[right]) == true && left != right|| (right == len && left != right))
        {
            char* subStr = subString(str, left, right - 1);
            // İF - İFNOT - MAKE - GO icin kontrol kismi
            if (isKeyword(subStr) == true)
            {
                if(if_control(subStr)==true)
                {
                    printf("if in baslangici\n");
                    anlik_islem_if=true;
                }
                else if(make_control(subStr)==true)
                {
                    printf("make baslangici\n");
                    anlik_islem_make=true;
                }
                else if(go_control(subStr)==true)
                {
                    printf("go baslangici\n");
                    anlik_islem_go=true;
                }

                 else if(ifnot_control(subStr)==true)
                {
                    printf("ifnot baslangici\n");
                    anlik_islem_ifnot=true;
                }
            }

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false)
                printf(" \n" );

            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
                left = right;
        }

        else if (isDelimiter(str[right]) == true && left == right)
            {
            if (isOperator(str[right]) == true)
                printf(" \n" );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
                if(com_cont_1(str[right])== true){
                    // Kosul acilisi ve gerekli kontrollerin yapilmasi
                    kontrol_open_index=right;
                    printf("KOSUL ACILDI \n");
                    kontrol=false;
                    printf( "KOSUL ACILIS INDISI %d \n",  right);
                }
                if(com_cont_2(str[right])== true){
                    // Kosul kapanisi ve gerekli kontrollerin yapilmasi
                    kontrol_close_index=right;
                    printf("KOSUL  KAPANDI \n");
                    kontrol=true;
                    printf( "KOSUL KAPANIS INDISI %d \n",  right);
                    // Kosulun icindeki kismin substring ile alinmasi
                    char* islenecek_dizin=subString(str,kontrol_open_index+1,kontrol_close_index-1);
                    printf("%s  KOSULUN ICINDEKI METIN \n", islenecek_dizin);
                    printf(" \n" );
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Burasi make ıf ilgili islemleri gerceklesitirir
                    if(anlik_islem_if==true)
                    {
                        printf("'%s'  if  ici   klasor \n", islenecek_dizin);
                        // yildiz olmadigi kosulda buraya giriyor
                        if(isDirectoryExists(islenecek_dizin)==true &&  dir_control(islenecek_dizin)==true)
                            {
                            char *token = strtok(islenecek_dizin, "/");
                            printf("%s \n",token);
                            if(!strcmp(token,"*"))
                            {
                                chdir("..");
                                 printf("kotnrol 1");
                                token = strtok(NULL, "/");
                            }
                            else
                            {
                                chdir(token);
                                token = strtok(NULL, "/");
                            }
                            while (token != NULL)
                            {
                                printf("%s\n", token);
                                go(token);
                                token = strtok(NULL, "/");
                                make_sayac++;
                            }
                            go(cwd);
                            printf(" \n" );
                            anlik_islem_if=false;
                            }
                            // yildiz oldugu kosulda buraya giriyor

                            else if(islenecek_dizin[0]=='*' && dir_control(islenecek_dizin)==true)
                            {
                                char *token = strtok(islenecek_dizin, "/");
                                printf("%s \n",token);
                                if(!strcmp(token,"*"))
                                {

                                    chdir("..");
                                    token = strtok(NULL, "/");
                                }
                                else
                                {

                                    change_dir(token);
                                    token = strtok(NULL, "/");
                                }
                                 while (token != NULL)
                                {
                                    if(!strcmp(token,"*"))
                                    {
                                    chdir("..");
                                    token = strtok(NULL, "/");
                                    }
                                    else
                                    {
                                    change_dir(token);
                                    token = strtok(NULL, "/");
                                    }
                                    printf("%s\n", token);
                                    make_sayac++;
                                }
                                anlik_islem_if=false;
                                printf("haloooo");
                                change_dir(cwd);
                            }
                            else
                            {
                            printf("Bu yol daha once olusturulmus\n");
                            printf(" \n" );
                            anlik_islem_if=false;
                             while(str[right]!=';' && str[right]!= '{')
                            {
                                right++;
                            }
                            if(str[right]=='{')
                            {
                                push_2(1);
                                right++;
                                while(isempty_2()!=1)
                                {
                                    if(str[right]=='{')
                                    {
                                        push_2(1);
                                        printf("Kontrol 1 {");
                                    }
                                    else if(str[right]=='}')
                                    {
                                        pop_2();
                                        printf("Kontrol 1 }");
                                    }
                                    right++;
                                }
                            }
                            }
                    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Burasi make ıfnot ilgili islemleri gerceklesitirir
                    if(anlik_islem_ifnot==true)
                        {
                        printf("'%s'  ifnot  ici   klasor \n", islenecek_dizin);
                        // yildiz olmadigi kosulda buraya giriyor
                        if(!isDirectoryExists(islenecek_dizin)==true &&  !dir_control(islenecek_dizin)==true)
                            {
                            char *token = strtok(islenecek_dizin, "/");
                            printf("%s \n",token);

                            if(!strcmp(token,"*"))
                            {
                                chdir("..");
                                 printf("kontrol 1");
                                token = strtok(NULL, "/");
                            }
                            else
                            {
                                chdir(token);
                                token = strtok(NULL, "/");
                            }
                            while (token != NULL)
                            {
                                printf("%s\n", token);
                                go(token);
                                token = strtok(NULL, "/");
                                make_sayac++;
                            }
                            go(cwd);
                            printf(" \n" );
                            anlik_islem_ifnot=false;
                            }

                            // yildiz oldugu kosulda buraya giriyor
                            else if(islenecek_dizin[0]=='*' && dir_control(islenecek_dizin)==true)
                            {
                                char *token = strtok(islenecek_dizin, "/");
                                printf("%s \n",token);

                                if(!strcmp(token,"*"))
                                {
                                    chdir("..");
                                    token = strtok(NULL, "/");
                                }
                                else
                                {
                                    change_dir(token);
                                    token = strtok(NULL, "/");
                                }

                                 while (token != NULL)
                                {
                                    if(!strcmp(token,"*"))
                                    {
                                    chdir("..");
                                    token = strtok(NULL, "/");

                                    }
                                    else
                                    {
                                    change_dir(token);
                                    token = strtok(NULL, "/");
                                    }
                                    printf("%s\n", token);
                                    make_sayac++;
                                }
                                anlik_islem_ifnot=false;
                                printf("haloooo");
                                change_dir(cwd);
                            }

                            else
                            {
                            printf("Bu yol daha once olusturulmus\n");
                            printf(" \n" );
                            anlik_islem_ifnot=false;

                             while(str[right]!=';' && str[right]!= '{')
                            {
                                right++;
                            }
                            if(str[right]=='{')
                            {
                                push_2(1);
                                right++;
                                while(isempty_2()!=1)
                                {
                                    if(str[right]=='{')
                                    {
                                        push_2(1);
                                        printf("Kontrol 1 {");
                                    }
                                    else if(str[right]=='}')
                                    {
                                        pop_2();
                                        printf("Kontrol 1 }");
                                    }
                                    right++;
                                }
                            }
                            }
                        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Burasi make ile ilgili islemleri gerceklesitirir
                     else if(anlik_islem_make==true )
                     {
                            if(isDirectoryExists(islenecek_dizin)==false)
                            {
                             printf("'%s'  Make ile Yaratilacak klasor \n", islenecek_dizin);
                             printf("Bu yol bos klasor yaratiliyor\n");
                            char *token = strtok(islenecek_dizin, "/");
                            printf("%s \n",token);

                            if(!strcmp(token,"*")){
                                chdir("..");
                                 printf("kotnrol 1");
                                token = strtok(NULL, "/");
                            }
                            else
                            {
                                create_dir(token);
                                chdir(token);
                                token = strtok(NULL, "/");
                            }
                            while (token != NULL)
                            {
                                printf("%s\n", token);
                                create_dir(token);
                                go(token);
                                token = strtok(NULL, "/");
                                make_sayac++;
                            }
                            go(cwd);
                            printf(" \n" );
                            anlik_islem_make=false;
                            }
                          else
                            {
                            printf("Bu yol daha once olusturulmus\n");
                            printf(" \n" );
                            anlik_islem_make=false;
                            }
                     }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Burasi go ile ilgili islemleri gerceklesitirir
                    else if(anlik_islem_go==true)
                        {
                            int sayac=0;
                            char *token = strtok(islenecek_dizin, "/");
                            printf("%s   %d\n",token,sayac);
                            if(!strcmp(token,"*"))
                            {
                                chdir("..");
                                token = strtok(NULL, "/");
                            }
                            else
                            {
                                chdir(token);
                                token = strtok(NULL, "/");
                            }
                            while (token != NULL)
                            {
                                sayac++;
                                printf("%s     %d\n", token,sayac);
                                if(!strcmp(token,"*"))
                                {
                                    chdir("..");
                                    printf("%s     %d\n", token,sayac);
                                    token = strtok(NULL, "/");
                                }
                                else
                                {
                                     go(token);
                                token = strtok(NULL, "/");
                                make_sayac++;
                                }
                            }
                            if(isDirectoryExists(islenecek_dizin)==true
                                && dir_control(islenecek_dizin)==true  )
                            {
                            char *token_2 = strtok(islenecek_dizin, "/");
                            printf("%s Token\n", token_2);
                            if(strcmp(token_2, '*'))
                            {
                                //
                            }
                            else
                            {
                                change_dir(token_2);
                            }
                            while (token_2 != NULL)
                            {
                                printf("%s Token\n", token_2);
                                token_2 = strtok(NULL, "/");
                                make_sayac++;
                                change_dir(token_2);
                            }
                            printf("Bu yol gecerli ve gidiliyor\n");
                            printf(" \n" );
                            anlik_islem_go=false;
                            }
                            else
                            {
                            printf("Bu yolda bir sey yok \n");
                            printf(" \n" );
                            anlik_islem_go=false;
                            }
                    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                }
            right++;
            left = right;
            }
    }
    // < > ' larin  kontrol edildigi yer
    if(kontrol==false){
        printf("hata var \n");
    }
    else
        printf("hata yok\n");
    return;
}
///////////////////////////////////////////////////////////////////////////////////
void create_dir(char* dir_name){
    int check;
    char* dirname = dir_name;
    check = mkdir(dirname);
    if (!check)
        printf("Klasor olusturuldu\n");
    else {
        printf(" Klasor olusturulamadı\n");
        exit(1);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int top=-1;
int stack[100];
void push(char a)
{
	stack[top] = a;
	top++;
}
void pop()
{
	if (top == -1)
	{
	    printf("\n");
		printf("Parantezlerde sikinti var\n");
		exit(0);
	}
	else
	{
		top--;
	}
}
void find_top()
{
	if (top == -1)
		printf("\nBu ifade gecerli\n");
	else
		printf("\nBu ifade gecersiz\n");
}
void blocks_controller(char* a){
    int i;
	for (i = 0; a[i] != '\0';i++)
	{
		if (a[i] == '{')
		{
			push(a[i]);
		}
		else if (a[i] == '}')
		{
			pop();
		}
	}
	find_top();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void change_dir(char* dir_name){
 chdir(dir_name);
}
void parcala(char girdi[])
{
    printf("%c",girdi[1]);
    char * token = strtok(girdi, "/");
    while( token != NULL )
    {
      printf( " %s\n", token );
      token = strtok(NULL, "/");
    }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* getData(char* fileName){
	FILE* file = fopen(fileName,"r");
	char* buffer = malloc(100);
	buffer = calloc(buffer,100);
	int counter = 0;
	while(!feof(file))
    {
		buffer[counter] = getc(file);
		counter++;
	}
	fclose(file);
	return buffer;
}

 int main()
{
    // current directory program sonu bastirmak icin kullanilan char array
    char s[100];

    ////////////////////////////////////////////////////////////////////////////////////////

    // dosyanin okundugu yer

    char *str=getData("x.pmk.txt");

    ////////////////////////////////////////////////////////////////////////////////////////

    //parse baslamadan onceki directory durumunu veren komut
    printf("%s\n", getcwd(s, 100));


    // parse ile birlikte okunan dosyadaki veriler islenir
    parse(str);

    //parse basladiktan sonra directory durumunu veren komut
    printf("%s\n", getcwd(s, 100));

    return 0;
}
