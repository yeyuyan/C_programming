#include <stdio.h>
/*
void afficheCase(int code)
{
    printf(" '%c' %d ",code,code);
    return ;
}
*/
void afficheCaseV2(int code)
{
    if (code<' '|| code>126)
        printf("|         ");
    else printf("| '%c' %3d ",code,code);
}

/*
void afficheLigne(int code1,int nbcol)
{
    while(nbcol!=0)
    {
        afficheCase(code1);
        nbcol--;
        code1++;
    }
    return ;
}
*/

int nbLigne(int code1,int code2,int nbcol)
{
    int nb=code2-code1+1;
    int nbligne=nb/nbcol;
 /*si on fait le test:
    if(nb%nbcol!=0)
        nbligne+=1;*/
    nbligne+=(nb%nbcol!=0);/*pas de test*/
    return nbligne;
}

void afficheLigneV2(int code1, int nbcol,int nbligne)
{
    while(nbcol!=0)
    {
        afficheCaseV2(code1);
        code1+=nbligne;
        nbcol--;
    }
    return ;
}

void afficheTrait(int nbcol)
{
    while(nbcol!=0)
    {
        printf("+---------");
        nbcol--;
    }
    printf("+\n");
}

int main()
{
    int code1,code2;
    int nbcol,nbligne,cpt=0;
    scanf("%3d%3d%d",&code1,&code2,&nbcol);
    nbligne=nbLigne(code1,code2,nbcol);
    printf("code1=%d,code2=%d,nbcol=%d,nbligne=%d\n",code1,code2,nbcol,nbligne);

    afficheTrait(nbcol);
    while (cpt<=nbligne)
    {
        afficheLigneV2(code1,nbcol,nbligne);
        printf("|\n");
        afficheTrait(nbcol);
        code1++;
        cpt++;
    }
    return;
}
