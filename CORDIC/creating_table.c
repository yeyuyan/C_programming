#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (acos(-1.0))
#endif

/*fonction qui calcule Kn ,un produit de termes pour i de 0 a la taille n*/
double calcul_Kn(int taille){
    double Kn=1/(sqrt(2));/* valeur initial quand n=0*/
    while(taille!=0){
        Kn=Kn*(1/(sqrt(1+(pow(2,-2*taille)))));
        taille--;
    }
    return Kn;
}


/*fonction qui ecrire la table de constant kn et la table de constant at*/
void table_constant(){

    FILE*f=fopen("table.h","w");/*ouvre la table.h*/
    fprintf(f,"double Kn[] =\n{\n");/*ecrire dans table.h */


    /*un boucle pour ecrire les valeurs de kn*/
    int i=0;
    while(i<26)
    {
        fprintf(f,"%.16f,\n",calcul_Kn(i));
        i++;
    }
    fprintf(f,"};\n\n");


    /*un boucle pour ecrice les atan(2^-i)*/
    double j=1;
    double at=atan(1);
    int k;
    fprintf(f,"double at[] =\n{\n");
    for(k=0;k<56;k++)
    {
        fprintf(f,"%.16f,\n",at);
        j=j/2;
        /*j=2^-i, pour i de 0 a n ,c'est ид dire la division j par 2 chaque fois*/
        at=atan(j);

    }
    fprintf(f,"};\n\n");
    fprintf(f,"#define PI %.17lf\n", M_PI);
    fprintf(f,"#define DEUXPI %.17lf\n", 2*M_PI);
    fprintf(f,"#define PID2 %.17lf\n", M_PI/2);
    fprintf(f,"#define PID4 %.17lf\n", M_PI/4);
    fclose(f);

    return;
}


int main(){
    table_constant();
    return 0;
}





