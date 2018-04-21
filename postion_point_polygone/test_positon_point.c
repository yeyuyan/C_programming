#include <math.h>
#include <stdio.h>

int SaisiePolygone(double pts[100][3])
{
    int nbpts;
    
    printf("\nNombre de points du polygone ? ");
    scanf("%i", &nbpts);
    int i = 0 ;
    while( i < nbpts)
    {
        printf("\n Point No %d >", i);
        scanf("%lf%lf%lf" , &pts[i][0], & pts[i][1], & pts[i][2]);
        i = i + 1 ;
    }
    pts[nbpts][0] = pts[0][0] ;
    pts[nbpts][1] = pts[0][1] ;
    pts[nbpts][2] = pts[0][2] ;
    nbpts = nbpts + 1 ;
    
    return nbpts;
        
}


int main()
{
    double pts[100][3] , q[3], /* q = coordonnées du point à tester */
        v1[3], v2[3], som , pvec[3] , y , x ; 
    int i,k, nbpts ;
    
    nbpts = SaisiePolygone(pts);
    
    printf("\n Point a tester >" );
    scanf("%lf%lf%lf", &q[0], &q[1], &q[2] );
    
    i=0 ;
    som = 0.0;
    while( i < nbpts-1 )
    {
        
        k = 0 ;
        while ( k < 3 )
        {
            v1[k] = pts[i][k] - q[k];
            v2[k] = pts[i + 1][k] - q[k];
            k = k + 1 ;
        }
        
        pvec[0] = v1[1] * v2[2] - v1[2] * v2[1];
        pvec[1] = -(v1[0] * v2[2] - v1[2] * v2[0]);
        pvec[2] = v1[0] * v2[1] - v1[1] * v2[0];
        
        k = 0 ;
        y = x = 0.0 ;
        while ( k < 3 )
        {
            y = y + pvec[k] * pvec[k] ; /* y est le carré des normes du pvect de v1 et v2 */
            x = x + v1[k] * v2[k] ; /* x est le produit scalaire de v1 et v2 */
            k = k + 1 ;
        }
        
        som = som + atan2(sqrt(y), x) ;
        i = i + 1 ;
    }
    if( fabs(som-6.283185307179586) < 1.0E-10) 
        printf("Point interieur\n"); /*  si abs[som-2*pi] < 0 */
    else
        printf("Point exterieur\n");  
    
    return 0;
}
