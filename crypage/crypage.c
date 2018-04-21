/*TD crypage*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*fct qui crypte txt avec cle
et retourne la taille de txt(sans considerer 0 a la fin)*/
long crypter(char txt[],char cle[])
{
    int t=0,c=0;
    while(txt[t]!=0)
    {
        txt[t]=txt[t]^cle[c];
        t++;
        c++;
        if (cle[c]==0) c=0;
    }
    txt[t]=cle[c];/*crypter 0 a la fin de txt*/
    return t;
}


long decrypter(char txt[],char cle[])
{
    int t=0,c=0;
    while(txt[t]!=cle[c])
    {
        txt[t]=txt[t]^cle[c];
        t++;
        c++;
        if (cle[c]==0) c=0;
    }
    txt[t]=0;/*decrypter l'element a la fin de txt*/
    return t;
}

long cryperficher(char in[],char out[],char cle[])
/*in et out noms de fichiers*/
{
    int crypt=0,c=0;char car=0;
    /*crypt compteur; c indice de cle; car caratere a crypter*/
    FILE *pIn,*pOut;
    pIn=fopen(in,"r");
    if(pIn==0)
    {
        printf("error!\n");
        return -1;
    }/*erreur entree*/
    pOut=fopen(out,"w");
    if (pOut==0)
    {
        fclose(pIn);
        return -2;/*erreur sortie*/
    }
    while(fscanf(pIn,"%c",&car)==1)
    {
        fprintf(pOut,"%c",car^cle[c]);
        c++;
        crypt++;
        if (cle[c]==0)c=0;
    }
    fclose(pIn);
    fclose(pOut);
    return crypt;
}


/*decoupage*/
char *sauterBlanc(char *s)
{
    for(;(*s==' ')||(*s=='\t');) ++s;
    return s;
}
char *sauterNonBlanc(char *s)
{
    for(;(*s!=' ')&&(*s!='\t')&&(*s!=0);) ++s;
    return s;
}

void decouper(char *txt, int nbmax, int *nb, char *mot[])
{
    for(*nb=0,txt=sauterBlanc(txt);(*txt!=0)&&(*nb<nbmax);txt=sauterBlanc(txt))
    {
        mot[*nb]=txt;
        (*nb)++;
        txt=sauterNonBlanc(txt);
        if (*txt!=0)
        {
            *txt=0;
            txt++;
        }
    }
}

int main()
{
    long res;
    char *mot[10];
    char txt[100];
    int nb;
    gets(txt);/*la commande: crypt in.txt out.txt 123*/
    decouper(txt,10,&nb,mot);
    printf("%d\n",nb);

    if (nb!=4)
    {
        printf("usage:crypt fiche_entree fiche_sortie cle\n");
        exit(-3);
    }
    res=cryperficher(mot[1],mot[2],mot[3]);/*nom du ficher d'entree:in;ficher sortie:out;cle*/
    if (res==-1) printf ("Impossible d'ouvrir %s\n",mot[1]);
    else if (res==-2) printf("Impossible d'ouvrir %s\n",mot[2]);
    else printf("crypage reussi:%ld octets\n",res);

    return res<0?0:res;/*0 pour l'erreur et res(positif) pour nb d'octet reussi */
}
