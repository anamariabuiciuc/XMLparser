#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct student
{
    int grupa;
    char nume[20];
    char initiala;
    char prenume[20];
    char finantare[6];
};

void afisare_catalog_studenti( struct student *data, int n)
{
    int i;
    for( i=1; i<=n; i++ )       ///aici afisez ca sa vad daca a introdus numele
    {
        printf( "%d\n", data[i].grupa );
        printf( "%s\n", data[i].nume );
        printf( "%c\n", data[i].initiala );
        printf( "%s\n", data[i].prenume );
        printf( "%s\n", data[i].finantare );
        printf( "\n\n" );
    }
}

void adauga_date_student_nou(struct student *data, int n)
{ int nr,i;

  FILE *fisierxml = fopen( "catalog.xml", "a+" );
  //int grupa;
  char initiala[2];
  printf("Introduceti numarul de studenti pe care doriti sa ii adaugati: ");
  scanf("%d", &nr);
  data = (struct student *)realloc(data, (n+nr)* sizeof(struct student));
       for (i=n+1; i<=n+nr; i++)
           {    //    data = (struct student *)realloc(data, (n+i)* sizeof(struct student)); //hai ca afiseaza asa daca lasi realloc-ul din main
                    fprintf(fisierxml," <STUDENT>\n");

                    printf("\nAdaugati grupa studentului:\n");
                    fprintf(fisierxml,"   <GRUPA>");
                    scanf("%d", &data[i].grupa);
                    fprintf(fisierxml,"%d",data[i].grupa);
                    fprintf(fisierxml,"</GRUPA>\n");

                    printf("Adaugati numele studentului:\n");
                    fprintf(fisierxml,"   <NUME>");
                    scanf("%s", data[i].nume);
                    fprintf(fisierxml,"%s", data[i].nume);
                    fprintf(fisierxml,"</NUME>\n");

                    printf("Adaugati initiala tatalui studentului:");
                    fprintf(fisierxml,"   <INITIALA>");
                    scanf("%s", initiala);
                    fprintf(fisierxml, "%s", initiala);
                    fprintf(fisierxml,"</INITIALA>\n");

                    printf("Adaugati prenumele studentului:\n");
                    fprintf(fisierxml,"   <PRENUME>");
                    scanf("%s", data[i].prenume);
                    fprintf(fisierxml,"%s", data[i].prenume);
                    fprintf(fisierxml,"</PRENUME>\n");

                    printf("Adaugati modul de finantare:");
                    fprintf(fisierxml,"   <FINANTARE>");
                    scanf("%s",data[i].finantare);
                    fprintf(fisierxml, "%s" ,data[i].finantare);
                    fprintf(fisierxml,"</FINANTARE>\n");


                    fprintf(fisierxml,"</STUDENT>\n");

               }

                fprintf(fisierxml, "</CATALOG>");

}

void Control_Panel( struct student *data, int n )
{
    FILE *fisierxml =  fopen( "catalog.xml", "a+" );
    int exit;
    char parametru;
    exit = 0;
    while( !exit )
    {
        printf(" Apasati tasta A pentru afisarea datelor studentilor.\n");
        printf(" Apasati tasta I pentru introducerea de noi date.\n");
        printf(" Apasati tasta X pentru a iesi.\n");
        printf(" Introduceti alegerea dumneavoastra -> ");

        scanf( "%c", &parametru );
        if( parametru == 'A' )

            afisare_catalog_studenti( data, n );
        else
        if( parametru == 'I' )
        {  // fseek(fisierxml,-10,SEEK_END);

            adauga_date_student_nou(data, n);


        }

        else
        if( parametru == 'X' )
            exit = 1;
        else
        if( !strchr( "AIX", parametru ) )
            printf("tasta neacceptata\n\n");


    }
}

int main()
{
    FILE *fisierxml = fopen( "catalog.xml", "a+" );
    FILE *out = fopen( "out.txt", "w" );
    FILE *fout = fopen( "fisier.txt", "w" );
    int n,i,flag_nume,flag_prenume,flag_grupa,flag_initiala,flag_finantare, exit;
    char *line, *tok, parametru;
    struct student *data;
    n = 1;

    data = (struct student*)malloc( 10*sizeof(struct student));  ///posibil greseala
    line = (char*)malloc( 256 * sizeof(char));

    flag_nume = flag_prenume = flag_finantare = flag_grupa = flag_initiala = 0;

    while( !feof(fisierxml) )
    {
        fgets (line, 256, fisierxml);         ///citesc linie cu linie
        tok = strtok( line, "<> ");     ///tai linia pt a cauta mai usor
        while (tok != NULL)
        {
            if( strcmp( tok, "STUDENT" ) == 0 )
            {
                n++;
               // data = (struct student *)realloc(data, n* sizeof(struct student));
            }

            ///NUME
            if( strcmp( tok, "NUME" ) == 0 && flag_nume == 0 )
                flag_nume = 1;
            if( flag_nume == 1 && strcmp( tok, "NUME") != 0 )
            {
                strcpy( data[n-1].nume, "" );
                strcat( data[n-1].nume, tok );
                flag_nume = 0;
            }

            ///GRUPA
            if( strcmp( tok, "GRUPA" ) == 0 && flag_grupa == 0 )
                flag_grupa = 1;
            if( flag_grupa == 1 && strcmp( tok, "GRUPA") != 0 )
            {
                data[n-1].grupa = atoi( tok );
                flag_grupa = 0;
            }

            ///PRENUME
            if( strcmp( tok, "PRENUME" ) == 0 && flag_prenume == 0 )
                flag_prenume = 1;
            if( flag_prenume == 1 && strcmp( tok, "PRENUME") != 0 )
            {
                strcpy( data[n-1].prenume, "" );
                strcat( data[n-1].prenume, tok );
                flag_prenume = 0;
            }

            ///INITIALA
            if( strcmp( tok, "INITIALA" ) == 0 && flag_initiala == 0 )
                flag_initiala = 1;
            if( flag_initiala == 1 && strcmp( tok, "INITIALA") != 0 )
            {
                data[n-1].initiala = tok[0];
                flag_initiala = 0;
            }

            ///FINANTARE
            if( strcmp( tok, "FINANTARE" ) == 0 && flag_finantare == 0 )
                flag_finantare = 1;
            if( flag_finantare == 1 && strcmp( tok, "FINANTARE") != 0 )
            {
                strcpy( data[n-1].finantare, "" );
                strcat( data[n-1].finantare, tok );
                flag_finantare = 0;
            }

            tok  = strtok(NULL, "<> ");
        }


    }
    n--;
    afisare_catalog_studenti(data,n);
    Control_Panel(data,n);
    return 0;

}

/*void Control_Panel( struct student *data, int n )
{
    exit = 0;
    while( !exit )
    {
        printf(" Apasati tasta A pentru afisarea datelor studentilor.\n");
        printf(" Apasati tasta I pentru introducerea de noi date.\n");
        printf(" Apasati tasta X pentru a iesi.\n");
        printf(" Introduceti alegerea dumneavoastra ->");

        scanf( "%c", &parametru );
        if( parametru == 'A' )
            afisare_catalog_studenti( data, n );
        else
        if( parametru == 'I' )
            printf("inca nu am rezolvat si asta=))" );
        else
        if( parametru == 'X' )
            exit = 1;
        else
        if( !strchr( "AIX", parametru ) )
            printf("tasta neacceptata\n\n");
    }
}
*/
