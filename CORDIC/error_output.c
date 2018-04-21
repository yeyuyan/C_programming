#include <math.h>
#include <stdio.h>
#include "table.h"

/*fonction qui calcule le cosinus et sinus dans le premier quadrant */
void sincosQ0(double a, double *s, double *c)
{
    double y = 0;
    double x = Kn[25];
    int d = 0;
    double xtemp=0;
    int i;

    for(i=0;i<56;i++)
    {
        if(a<0) d=-1;
        if(a>=0) d=1;
        xtemp = x;
        x = x -(d*y*pow(2,-i));
        y = y +(d*xtemp*pow(2,-i));
        a = a -(d*at[i]);
    }
    *c = x;
    *s = y;
}


/*fonction qui réduit l'angle modulo 2pi */
double reduction(double a)
{
    for(;a<=0;a += DEUXPI);
    for(;a>=DEUXPI;a -= DEUXPI);
    return a;
}

/*fonction qui retourne le numéro du quadrant dans lequel se trouve l'angle a*/
int quadrant(double a)
{
    a=reduction(a);
    if(a>=0 && a<PID2)return 0;
    else if(a>=PID2 && a<PI)return 1;
    else if(a>=PI && a<3*PID2)return 2;
    else if(a>=3*PID2 && a<DEUXPI)return 3;
    return 4;
}

/*fonction qui calcule sin et cos d'un angle quel que soit l'angle*/
void sincos(double a, double *s, double *c)
{
    int q;
    a=reduction(a);
    q=quadrant(a);
    switch (q)
    {
        case 0:
            sincosQ0(a,s,c);
            break;
        case 1:
            a -= PID2;
            sincosQ0(a,c,s);
            *c = *c * (-1);
            break;
        case 2:
            a -= PI;
            sincosQ0(a,s,c);
            *s = *s * (-1);
            *c = *c * (-1);
            break;
        case 3:
            a -= 3*PID2;
            sincosQ0(a,c,s);
            *s = *s * (-1);
            break;
    }
}


int main(){
    double i;
    double ecart;
    double s = 0;
    double c = 0;
    FILE*f=fopen("ecart-sinus.txt","w");
    fprintf(f,"angle:    ecart:\n");
    for(i=0;i<=360;i+=0.5)
    {
        sincos(i*PI/180,&s,&c);
        ecart = fabs(s - sin(i*PI/180));
        fprintf(f,"%6.1f   %.16f\n",i,ecart);
    }

    fclose(f);
    return 0;
}
