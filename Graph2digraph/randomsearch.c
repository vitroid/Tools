/*
 *$B=P7k9g?t(B2$B$^$?$O(B1$B$H$$$&>r7o$N$b$H$G!"2DG=$JM-8~%0%i%U$r%i%s%@%`$K0l$D(B
 $BA*$V!#H]!#>r7o$,$"$^$9$.$k!#(B4$B7k9g$N>l9g$K$O!"=P7k9g$O(B2$B$G$J$$$H:$$k!#(B
 $BJ?@.#9G/#1#07n#2#5F|(B($BEZ(B)
 $B2DG=$J9=B$$rA*$V$@$1$G$J$/!"$h$j%(%M%k%.!<$,Dc$/$J$j$=$&$J9=B$$r%5%s(B
$B%W%k$7$?$$!#:#$N$H$3$mH=L@$7$F$$$k5,B'$O!"!V(B3$B7k9g$,O"B3$9$k>l9g$K$O!"(B
$B30FL$,NY@\$7$J$$$h$&$K$9$k!#!W!V(B180$BEY$K3+$$$?(B2$BK\$K(BH$B$r$o$j$"$F$J$$!W(B

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
    /*$B$9$Y$F$N7k9g$K0l5$$KJ}8~$rM?$(!">r7o$r$_$?$9$^$G7+$jJV$9!#(B*/
    int i,n,x,y,z,j;
    n=h->nnode;
    int am[n*n];
    i=0;
    fprintf(stderr,"...");
/*$B6vA3$K4|BT$7$FNI$$AH9g$;$,=P8=$9$k$^$G7+$jJV$9$N$GHs>o$KCY$$!#$J$s$H(B */
/*$B$+$7$m!#J?@.#9G/#1#07n#2#5F|(B($BEZ(B)*/
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
    /*$BK\Ev$O(Bam$B$r3+J|$7$F!"(Bmain$B$K$b$I$k$Y$-$@$,!"JL$K$3$3$G=*$o$C$F$b;Y>c$J$7!#(B*/
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

