#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define NPOINTS 10

#define tdimx 4
#define tdimy 4

// |     |
// |  R  |T
// |-----|
// |     |1

#define bdimx 3
#define bdimy 10

// |---|---|---|
// | x | y | z | 
// |---|---|---|
// |---|---|---|


double* applyM_p(double * buf, double * Tmatrix, int npoints);


int main()
{

double * t = new double [16];
// |----------------|
// iterate -> tdimx * it + 0/1/2/3 (tdimx-1)
double tfilling [16]={0.999987,0.0,0.0,10.0,0.0,0.999999,0.0,10.0,0.0,0.0,0.999967,10.0,0.0,0.0,0.0,1.0};
memcpy(t,&tfilling,tdimx*tdimy*sizeof(double));

for(int i=0; i<tdimx*tdimy;i++)
std::cout<< tfilling[i]<<" ";
std::cout<< std::endl;

double * pbuf = new double [NPOINTS *3];
// |------------------------------|
// iterate -> bdimx * p + 0/1/2 (bdimx-1)
memset(pbuf, NULL, bdimx*bdimy*sizeof(double));
double pbuffilling [9]={1,2,3,4,5,6,7,8,9};
memcpy(pbuf,&pbuffilling,9*sizeof(double));

for(int i=0; i<bdimx*bdimy;i++)
std::cout<< pbuf[i]<<" ";
std::cout<< std::endl;

double * rispbuf ;
//applyM_p allocates for double pointer size = III function input
rispbuf=applyM_p(pbuf,t,3);

for(int i=0; i<3*3;i++)
std::cout<< rispbuf[i]<<" ";
std::cout<< std::endl;

delete [] rispbuf;

std::cout<<std::endl;
return 0;
}



double* applyM_p(double * pbuf, double * t, int npoints)
{

 double * rispbuf = new double [npoints *3];

 double partial=0;
 for(int p=0; p<npoints; p++)
 {//cycle over points

        for(int row=0; row < tdimx-1; row++)//do not calculate the 4th row
        {
                for(int column=0; column<tdimy ; column ++)  
                {
                if(column == tdimx-1) partial += t[tdimx*row +column];
                else  
                        partial += pbuf[p* bdimx + column] * t[tdimx * row +column];
                }

               // printf("%f ",partial);
               //if( == (bdimy-1))printf("\n");
rispbuf[p*3+row]=partial;                
partial =0;
        }
 }

return rispbuf;
}



