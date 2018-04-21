#include<stdio.h>
#include<string.h>

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
    char *mot[10];
    char txt[100];
    int nb;
    int i;
    for (;gets(txt)!=NULL;)
    {
        decouper(txt,10,&nb,mot);
        for(i=0;i<nb;++i) printf("%s\n",mot[i]);
    }
    return 0;
}
