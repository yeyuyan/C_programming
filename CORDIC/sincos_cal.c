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
            printf("a=%lf",a);
            sincosQ0(a,c,s);
            *c = *c * (-1);
            break;
        case 2:
            a -= PI;
            printf("a=%lf",a);
            sincosQ0(a,s,c);
            *s = *s * (-1);
            *c = *c * (-1);
            break;
        case 3:
            a -= 3*PID2;
            printf("a=%lf",a);
            sincosQ0(a,c,s);
            *s = *s * (-1);
            break;
    }
}

int main(){
    double a;
    printf("\nQuel est la valeur de votre angle ?\n");
    scanf("%lf", &a);
    double s = 0;
    double c = 0;

    sincos(a,&s,&c);
    printf("sinus fonction = %.16lf et cosinus fonction = %.16lf\n", s,c);
    printf("sinus réel = %.16lf et cosinus reel = %.16lf\n", sin(a),cos(a));
    printf("ecart sinus = %.16lf et ecart cosinus = %.16lf\n", sin(a)-s,cos(a)-c);
    return 0;
}
