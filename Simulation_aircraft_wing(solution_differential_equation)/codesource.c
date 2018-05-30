/*The program realise simulations of vibration for an aircraft wing who recieves flux
  The program read the data of system from a file by typing "simu "+ filename in the terminal 
  when running the program 
  
  It use the method of Runge-Kutta to find the solution of differential equations*/



#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979312

typedef struct dataSim
{
    double m ; /* masse de l'aile */
    double ro ; /* masse volumique */
    double S ; /* surface de l'aile */
    double alpha0 ; /* angle d'incidence initial de l'aile */
    double k ; /* raideur ressort équivalent */
    double u0 ; /* flux d'air */
    double du ; /* flux d'air */
    int tvent ; /* déterminer le type de vent 0: flux sinusoïdal    1 : flux indiciel*/
} dataSim ;

typedef double (*derivee)(double z, double v, double t, void *params);


/* fonction qui permet de convertir un angle en degré en radian */
double deg2Rad(double angle)
{
    angle = angle*PI/180;
    return angle;
}




/* fonction qui initialise la simulation */
void initialisation(FILE* f, dataSim *Sim0)
{
    
    fscanf(f,"m=%lf\n",&(*Sim0).m);
    fscanf(f,"ro=%lf\n",&(*Sim0).ro);
    fscanf(f,"S=%lf\n",&(*Sim0).S);
    fscanf(f,"alpha0=%lf\n",&(*Sim0).alpha0);
    fscanf(f,"k=%lf\n",&(*Sim0).k);
    fscanf(f,"u0=%lf\n",&(*Sim0).u0);
    fscanf(f,"du=%lf\n",&(*Sim0).du);
    fscanf(f,"tvent=%d",&(*Sim0).tvent);
    

 /*   
    (*Sim0).m = 3;
    (*Sim0).ro = 1.22;
    (*Sim0).S = 0.3;
    (*Sim0).alpha0 = 10;
    (*Sim0).k = 980;
    (*Sim0).u0 = 7.5;
    (*Sim0).du = 1.5;
    (*Sim0).tvent = 0;

    */
}


/* fonction qui modélise la vitesse du vent */
double vent(double t, dataSim *params)
{
    double vitesse;
    double w0 = sqrt((*params).k/(*params).m);
    double w = 0.5*w0 ;
    
    switch ((*params).tvent)
    {
        case 0: /* flux sinusoïdal */
            if(t<=0) vitesse = 0;
            else vitesse = (*params).u0 + (*params).du * sin(w*t);            
            break;
        case 1: /* flux indiciel */
            if(t<1 || t>=4) vitesse=0;
            else vitesse=(*params).du;
            break;
    }
    return vitesse;
}


/* fonction qui calcule la portance Cz avec pour entrée un angle en RADIAN */
double coeffPortance(double angle)
{
    double Cz;
    if(angle >= deg2Rad(-18) && angle <= deg2Rad(18)) Cz = 2*PI*angle;
    else Cz = 0;
    return Cz;    
}



/* fonction qui calcule la dérivée de la fonction (1) du 1.2 */
double f(double z, double v, double t, void *params)
{
    double derivee = v;
    return derivee;
}


/* fonction qui calcule la dérivée de la fonction (2) du 1.2 */
double g(double z, double v, double t, void *params)
{
    double derivee;
    dataSim *Simu = (dataSim*) params; /* cast ou transtypage */
    double u = vent(t,params);
    double Cz = (*Simu).alpha0;
    if (u!=0) Cz -= atan(v/u);
    derivee = Cz*(((*Simu).ro*(*Simu).S)/(2*(*Simu).m))*u*sqrt((u*u)+(v*v)) - (*Simu).k/(*Simu).m * z;  
    return derivee;
}


/* fonction qui calcule les valeurs  des variables z et v à l'instant t + dt */
void rk4(double *z, double *v, double *t, double dt, derivee f, derivee g, void *params)
{
    double kz1,kv1,kz2,kv2,kz3,kv3,kz4,kv4;
    
    kz1 = f(*z,*v,*t,params) * dt;
    kv1 = g(*z,*v,*t,params) * dt;
    kz2 = f(*z+kz1/2,*v+kv1/2,*t+dt/2,params) * dt;
    kv2 = g(*z+kz1/2,*v+kv1/2,*t+dt/2,params) * dt;
    kz3 = f(*z+kz2/2,*v+kv2/2,*t+dt/2,params) * dt;
    kv3 = g(*z+kz2/2,*v+kv2/2,*t+dt/2,params) * dt;
    kz4 = f(*z+kz3,*v+kv3,*t+dt,params) * dt;
    kv4 = g(*z+kz3,*v+kv3,*t+dt,params) * dt;
    *z +=  (kz1 + 2*kz2 + 2*kz3 + kz4) / 6.0 ;
    *v +=  (kv1 + 2*kv2 + 2*kv3 + kv4) / 6.0;

    
}




/* fonction qui va résoudre le problème et écrire les résultats dans un fichier */
void resolution(FILE* file)
{
    dataSim Sim0;
    initialisation(file,&Sim0);
    printf("m = %lf\nro = %lf\nS = %lf\nalpha0 = %lf\nk = %lf\nu0 = %lf\ndu = %lf\ntype vent = %d\n", Sim0.m, Sim0.ro, Sim0.S, Sim0.alpha0, Sim0.k, Sim0.u0, Sim0.du, Sim0.tvent);
    double t,z=0,v=0,dt=0.00695;
    FILE* fileRes=fopen("Res_freq_0.5w0.txt","w");
    for(t=0;t<=6;t+=dt)
    {
        fprintf(fileRes,"%.7f ",t+dt);
        rk4(&z,&v,&t,dt,&f,&g,&Sim0);
        fprintf(fileRes,"%.9f\n",z);       
    }
    fclose(fileRes);
    
}


int main(int argc, char *argv[])
{
    char fileAdress[100];
    scanf("simu %s",fileAdress);
    FILE* file=fopen(fileAdress,"r");
    if(file!=NULL)
        resolution(file);
    else 
        printf("La fichier ne peut pas etre ouvert");
    fclose(file);
    return 0;
}
