#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

extern double rint();

int main(int argc,char *argv[])
{
  char buf[4096];
  double* x;
  double* y;
  double* z;
  double bx,by,bz;
  int n;
  double ri,rr;
  int pbc=0;
  
  if(argc<2){
    fprintf(stderr,"usage: %s radius [radius]\n",argv[0]);
    exit(1);
  }
  ri = 0.0;
  if ( argc == 3 ){
  ri = atof(argv[1]);
  rr = atof(argv[2]);
  }
  else{
  rr = atof(argv[1]);
  }
  rr*=rr;
  ri*=ri;
  
  while(NULL!=fgets(buf,sizeof(buf),stdin)){
    if(strncmp(buf,"@BOX3",5)==0){
      fgets(buf,sizeof(buf),stdin);
      sscanf(buf,"%lf %lf %lf\n",&bx,&by,&bz);
      pbc++;
    }
    if(strncmp(buf,"@AR3A",5)==0||strncmp(buf,"@NX4A",5)==0||strncmp(buf,"@NX3A",5)==0){
      int i;
      fgets(buf,sizeof(buf),stdin);
      sscanf(buf,"%d",&n);
      printf("@NGPH\n%d\n",n);
      x = malloc( sizeof( double ) * n );
      y = malloc( sizeof( double ) * n );
      z = malloc( sizeof( double ) * n );
      for(i=0;i<n;i++){
	int j;
	fgets(buf,sizeof(buf),stdin);
	sscanf(buf,"%lf %lf %lf\n",&x[i],&y[i],&z[i]);
	for(j=0;j<i;j++){
	  double dx,dy,dz;
	  dx = x[i]-x[j];
	  dy = y[i]-y[j];
	  dz = z[i]-z[j];
	  if(pbc){
	    dx -= rint(dx/bx)*bx;
	    dy -= rint(dy/by)*by;
	    dz -= rint(dz/bz)*bz;
	  }
	  double dd;
	  dd = dx*dx+dy*dy+dz*dz;
	  if(ri<dd && dd<rr){
	    printf("%d %d\n",i,j);
	  }
	}
      }
      printf("-1 -1\n");
    }
  }
}
