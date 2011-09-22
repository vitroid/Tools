/*
 *出結合数2または1という条件のもとで、可能な有向グラフをランダムに一つ
 選ぶ。否。条件があますぎる。4結合の場合には、出結合は2でないと困る。
 平成９年１０月２５日(土)
 可能な構造を選ぶだけでなく、よりエネルギーが低くなりそうな構造をサン
プルしたい。今のところ判明している規則は、「3結合が連続する場合には、
外凸が隣接しないようにする。」「180度に開いた2本にHをわりあてない」

2010-7-12
Defective configurations are generated........
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double drand48();

typedef struct 
{
    int npair,nnode;
    int *pair0,*pair1;
    int *nout;
    int *nneib;
}
hbset;

hbset *hbset_constructor(int n)
{
    hbset *h;
    h=malloc(sizeof(hbset));
    h->nnode=n;
    h->pair0=calloc(n*n,sizeof(int));
    h->pair1=calloc(n*n,sizeof(int));
    h->nout=calloc(n,sizeof(int));
    h->nneib=calloc(n,sizeof(int));
    h->npair=0;
    return h;
}

void hbset_done(hbset *h)
{
    free(h->pair0);
    free(h->pair1);
    free(h->nout);
    free(h->nneib);
    free(h);
}

void randomset(hbset *h)
{
    /*すべての結合に一気に方向を与え、条件をみたすまで繰り返す。*/
    int i,n,x,y,z,j;
    n=h->nnode;
    int am[n*n];
    i=0;
    fprintf(stderr,"...");
/*偶然に期待して良い組合せが出現するまで繰り返すので非常に遅い。なんと */
/*かしろ。平成９年１０月２５日(土)*/
/*
    while(i!=n)
      {
	  for(i=0;i<n;i++)
	    {
		h->nout[i]=0;
	    }
	  for(i=0;i<h->npair;i++)
	    {
		x=h->pair0[i];
		y=h->pair1[i];
		if(x>y)
		  {
		      z=x;
		      x=y;
		      y=z;
		  }
		if(drand48()>0.5)
		  {
		      h->pair0[i]=x;
		      h->pair1[i]=y;
		      h->nout[x]++;
		  }
		else
		  {
		      h->pair0[i]=y;
		      h->pair1[i]=x;
		      h->nout[y]++;
		  }
	    }
	  for(i=0;i<n;i++)
	    {
		if((h->nneib[i]>=4)&&(h->nout[i]!=2))
		  break;
		if((h->nout[i]!=1)&&(h->nout[i]!=2))
		  break;
	    }
      }*/
    /*make a random initial configuration*/
    for(i=0;i<n;i++)
      {
          h->nout[i]=0;
      }
    for(i=0;i<h->npair;i++)
      {
          x=h->pair0[i];
          y=h->pair1[i];
          if(x>y)
            {
                z=x;
                x=y;
                y=z;
            }
          if(drand48()>0.5)
            {
                h->pair0[i]=x;
                h->pair1[i]=y;
                h->nout[x]++;
            }
          else
            {
                h->pair0[i]=y;
                h->pair1[i]=x;
                h->nout[y]++;
            }
      }
    for(j=0;j<h->npair*h->npair;j++)
      {
          int flip=0;
          i=drand48()*h->npair;
          /*adjust number of out HB so as to be in the restriction*/
          /*x,pair0 is the outgoing side*/
          x=h->pair0[i];
          y=h->pair1[i];
/*          if(h->nneib[x]==4)*/
            {
                /*out should be 2*/
                if(h->nout[x]>2)
                  flip++;
            }
          if(h->nneib[y]>=4)
            {
                /*out should be 2*/
                if(h->nout[y]<2)
                  flip++;
            }
          else
            {
                if(h->nout[y]<1)
                  flip++;
            }
          if(flip)
            {
                fprintf(stderr,"%d,",j);
                h->pair0[i]=y;
                h->pair1[i]=x;
                h->nout[x]--;
                h->nout[y]++;
            }
      }                
    fprintf(stderr,"Found.\n%d\n",n*n*sizeof(int));
/*    am=calloc(n*n,sizeof(int));*/
    
/*    am=malloc(sizeof(int)*n*n);*/

    for(i=0;i<n*n;i++)
      am[i]=0;
    
    for(i=0;i<h->npair;i++)
      {
	  x=h->pair0[i];
	  y=h->pair1[i];
	  am[x*n+y]=1;
      }
    printf("@NGPH\n%d\n",n);
    for(i=0;i<n;i++){
        int j;
        for(j=0;j<n;j++)   {
            if ( am[i*n+j] ) {
                printf( "%d %d\n", i,j );
            }
        }
    }
    printf("-1 -1\n");
    
    exit(0);
    /*本当はamを開放して、mainにもどるべきだが、別にここで終わっても支障なし。*/
}


int main(int argc,char *argv[])
{
    int n,i,seed;
    char buf[1024];
    
    if(argc!=2)    {
        fprintf(stderr,"usage: %s randomseed < @GRPH\n",argv[0]);
        exit(1);
    }
    
    srand48(seed=atoi(argv[1]));
    fprintf(stderr,"(%d)",seed);
    
    while(NULL!=fgets(buf,sizeof(buf),stdin)){
        if(0==strncmp(buf,"@GRPH",5)) {
            hbset *h;
            int k;
            fgets(buf,sizeof(buf),stdin);
            h=hbset_constructor(n=atoi(buf));
            k=0;
            for(i=0;i<n;i++){
                int j;
                fgets(buf,sizeof(buf),stdin);
                for(j=i+1;j<n;j++){
                    if(buf[j]=='1'){
                        h->pair0[k]=i;
                        h->pair1[k]=j;
                        h->nneib[i]++;
                        h->nneib[j]++;
                        k++;
                    }
                }
            }
            h->npair=k;
            randomset(h);
            hbset_done(h);
        }				
        if(0==strncmp(buf,"@NGPH",5)) {
            hbset *h;
            int k;
            fgets(buf,sizeof(buf),stdin);
            h=hbset_constructor(n=atoi(buf));
            k=0;
            {
                int j;
                int hb[n][n];
                memset( hb, 0, sizeof(int)*n*n );
                while( NULL != fgets( buf, sizeof(buf), stdin ) ){
                    
                    sscanf( buf, "%d %d", &i, &j );
                    if ( i < 0 )
                        break;
                    if ( hb[i][j] == 0 ){
                        hb[i][j] = 1;
                        hb[j][i] = 1;
                        
                        h->pair0[k]=i;
                        h->pair1[k]=j;
                        h->nneib[i]++;
                        h->nneib[j]++;
                        k++;
                    }
                }
            }
            h->npair=k;
            randomset(h);
            hbset_done(h);
        }				
    }
}

