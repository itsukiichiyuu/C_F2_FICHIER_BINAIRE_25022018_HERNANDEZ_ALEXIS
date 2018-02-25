#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

typedef struct Ddn{

    int j,m,a;

}Ddn;

typedef struct Cid{

    int NumeroCarte;
    char* Nom;
    char* Prenom;
    char Sexe;
    char* Ville;
    Ddn Naissance;

}Cid;

int main()
{
    long lSize=0;
    FILE* pFile = NULL; //descripteur de fichier
    Cid* pCid=malloc(sizeof(Cid));

    //----------INITIALISATION de pCid----------

    pCid->Nom=malloc(sizeof(char*)*MAX);
    pCid->Prenom=malloc(sizeof(char*)*MAX);
    pCid->Ville=malloc(sizeof(char*)*MAX);
    pCid->Naissance.j=22;
    pCid->Naissance.m=11;
    pCid->Naissance.a=1989;
    strcpy(pCid->Nom,"HERNANDEZ");
    strcpy(pCid->Prenom,"Alexis");
    pCid->NumeroCarte=1234567;
    pCid->Sexe='H';
    strcpy(pCid->Ville,"LINGOLSHEIM");

    //-------------------------FIN INITIALISATION DE pCid--------------------------


    //--------------------ECRITURE DANS LE FICHIER (FONCTIONNE)--------------------

    pFile = fopen("fichier_binaire.bin","ab");
    fwrite(pCid, sizeof(Cid),sizeof(pCid),pFile);
    fclose(pFile);

    //------------------------FIN ECRITURE DANS LE FICHIER-------------------------

    //strcpy(pCid->Nom,"personne");
    //TEST pour voir si le fichier est bien fread et pas pCid qui se réécrit simplement avec d'anciennes valeurs


    pFile = fopen ( "fichier_binaire.bin" , "rb");

    fseek(pFile,0,SEEK_END);    //on va a la fin du fichier
    lSize=ftell(pFile);         //on garde la taille du fichier
    rewind(pFile);              //on retourne au début du fichier


    //------------------LECTURE DU FICHIER (NE MARCHE QU'UNE FOIS)-----------------

    fread(pCid,1,lSize,pFile);  //ici le soucis est que le fichier ne change que la premiere valeur (le prenom) après
                                //2 jours de recherche et d'innombrables essais je n'ai pas trouvé de solution viable
                                //il y a bien quelques solutions mais pas avec un pointeur et la serialisation semble
                                //impossible avec un type structuré...

    printf("id:%d, Nom:%s, Prenom:%s, Sexe:%c, Ville:%s, DDN %d/%d/%d.",
           pCid->NumeroCarte,pCid->Nom,pCid->Prenom,pCid->Sexe,pCid->Ville,
           pCid->Naissance.j,pCid->Naissance.m,pCid->Naissance.a);
           //ici j'ai également essayé avec un "buffer" qui prend les données et les écrit mais cela ne fonctionnait pas...

    fclose (pFile);

    //----------------------------FIN LECTURE DU FICHIER----------------------------

    return 0;
}
