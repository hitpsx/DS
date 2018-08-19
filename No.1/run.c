#include <stdio.h>
#include <stdlib.h>
#include <string.h>    //strlen

#include <unistd.h>


#define TDMAX 30000
#define ANSMAX 5
#define DATLEN 12
#define N 16

//For training data
typedef struct{
    double dat[DATLEN];
    int ans;
} tdata;

//For calculating distans data
typedef struct{
    double dist;
    int ans;
} data;

int discmp(const void *a,const void *b){
    if ((((data *)a)->dist - ((data *)b)->dist)>0.0001)return 1;
    if ((((data *)a)->dist - ((data *)b)->dist)<-0.0001)return -1;
    return 0;
}


tdata td[TDMAX];//train data
tdata testD[TDMAX];

int loadtrain(){
    FILE *fp = NULL,*fpLabel = NULL;
    int i=0,z=0;
    char *line,*record;
    char buffer[1024*12];
    if ((fp = fopen("Train.csv", "at+")) != NULL)
    {
        char delims[] = ",";
        char *result = NULL;
        int j = 0,k = 0;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)
        {
            record = strtok(line, ",");
            while (record != NULL)
            {
                if (j==10)
                    break;
                if (j >= 4 && j<7){
                     td[i].dat[j-4]=atof(record);
                   
                }
                if(j>=7)
                {
                    td[i].dat[j-4]=atof(record)/2000;
                   
                }
                record = strtok(NULL, ",");
                j++;
            }
            //printf("\n");
            i++;
            j = 0;
 
        }
        fclose(fp);
        fp = NULL;
    }
    if ((fpLabel = fopen("TrainLabel2.txt", "r")) != NULL)
    {
        while (!feof(fpLabel))
        {
            fscanf(fpLabel,"%d",&td[z].ans);
            z++;
        }
        fclose(fpLabel);
        fpLabel = NULL;
    }
  
    return i;//tc is num of train data
}

int loadtest(){
    printf("dasds\n");
    FILE *fp = NULL,*fpLabel = NULL;
    int i=0,z=0;
    char *line,*record;
    char buffer[1024*12];
    if ((fp = fopen("Train1.csv", "at+")) != NULL)
    {
        char delims[] = ",";
        char *result = NULL;
        int j = 0,k = 0;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//褰撴病鏈夎鍙栧埌鏂囦欢鏈熬鏃跺惊鐜户缁?
        {
          
            record = strtok(line, ",");
            while (record != NULL)//璇诲彇姣忎竴琛岀殑鏁版嵁
            {
                if (j==10)
                    break;
                if (j >= 4 && j<7){
                    testD[i].dat[j-4]=atof(record);
                
                    //printf("%s ", record);
                }
                if(j>=7)
                {
                    testD[i].dat[j-4]=atof(record)/2000;
                }
               
                record = strtok(NULL, ",");
                j++;
            }
            //printf("\n");
            i++;
            j = 0;
 
        }
        fclose(fp);
        fp = NULL;
    }

     if ((fpLabel = fopen("G5Lable1.txt", "r")) != NULL)
    {
        while (!feof(fpLabel))
        {
            fscanf(fpLabel,"%d",&testD[z].ans);
            z++;
        }
        fclose(fpLabel);
        fpLabel = NULL;
    }

  
    return i;//tc is num of train data
}
void checkData()
{
    int k,z,j=loadtrain();
    for(k=0;k<j;k++)
    {
        for(z=0;z<6;z++)
        {
            printf("%lf ",td[k].dat[z]);
        }
        printf(" %d \n",td[k].ans );
    }
}

int main(){
    double a,b;
    double ind[DATLEN],train[DATLEN]={};
    int tc,tt;
    int k=5,c=0,i,j,p=0;
    data dat[TDMAX];
    int ret[ANSMAX];
    int maxnum,maxi,rightNumber=0;
    int endflg =0;
    double sdat[N][7],trainDat[N][7];//Sensor raw data
    int fullflg=0;
    
    //Input training data
    //x y answer
    //Like color hardness potato or tomato
    //-1 -1 -1 is end of train data
    //-9 or more is end of td
    
    tc=loadtrain();//tc is num of train data
    tt=loadtest();
    endflg=0;
    
    printf("%d\n",tt );
    
    int flg=0;
    int label;
    int all=0;
    
    //keep communicating with server
    
    //c heckData();
    while(p<tt)
    {
        
        int mode,format,checkNumber=0;
        double interval,ax,ay,az,gx,gy,gz,mx,my,mz;
       
         
        sdat[c][0]=testD[p].dat[0];
        sdat[c][1]=testD[p].dat[1];
        sdat[c][2]=testD[p].dat[2];
        sdat[c][3]=testD[p].dat[3];
        sdat[c][4]=testD[p].dat[4];
        sdat[c][5]=testD[p].dat[5];
        sdat[c][6]=testD[p].ans;
        if (c==N-1||(fullflg&&c==N/2)){
            if (c==N-1)c=-1;
            fullflg=1;
            double sums[6]={},dsums[6]={};

            for (i=0;i<N;i++){
                checkNumber+=sdat[i][6];
                for(j=0;j<6;j++){
                    sums[j]+=sdat[i][j];
                    dsums[j]+=sdat[i][j]*sdat[i][j];
                }
               
            }
            
            
            
            for(i=0;i<3;i++){
                ind[i]=sums[i]/N;
            }
            // for(i=0;i<3;i++){
            //     ind[3+i]=(dsums[i]/N)-(sums[i]/N)*(sums[i]/N);
            // }
            for(i=3;i<6;i++){
                ind[i]=sums[i]/N;
            }
            // for(i=3;i<6;i++){
            //     ind[6+i]=(dsums[i]/N)-(sums[i]/N)*(sums[i]/N);
            // }
            for(i=0;i<6;i++)
                printf("%f ",ind[i]);
            printf("\n");
            //Init
            for (i=0;i<ANSMAX;i++)ret[i]=0;
            maxnum=-1;
            maxi=-1;
            
            //calc dist
            for (i=0;i<tc/N;i++){
                dat[i].dist=0;
                memset(train,0,sizeof(double)*7);
                for(int temp=i*N;temp<i*N+N;temp++)
                {
                    train[0]+=td[temp].dat[0];
                    train[1]+=td[temp].dat[1];
                    train[2]+=td[temp].dat[2];
                    train[3]+=td[temp].dat[3];
                    train[4]+=td[temp].dat[4];
                    train[5]+=td[temp].dat[5];
                    train[6]+=td[temp].ans;
                }
                for (j=0;j<6;j++)
                    dat[i].dist+=(train[j]/N-ind[j])*(train[j]/N-ind[j]);
               
                dat[i].ans=train[6]/N;
            
            }
            
            qsort(dat,tc,sizeof(data),discmp);
            // for(int temp=0;temp<tc;temp++)
            // {
            //     printf("%lf %d\n",dat[temp].dist,dat[temp].ans );
            // }


            for (i=0;i<k;i++){
//                printf("dbg:%f\n",dat[i].dist);
                ret[dat[i].ans]++;
                if (ret[dat[i].ans]>maxnum){
                    maxnum=ret[dat[i].ans];
                    maxi=dat[i].ans;
                }
            }
            for (i=0;i<k;i++){
                printf(" %d ",ret[i]);
            }
            if(maxi==checkNumber/N)
            {
                rightNumber++;
            }
            printf("\n%d %d\n",maxi,checkNumber/N);

            all++;
            
        }
        

        p++;
        c++;
    }
    printf("%lf\n",(double)rightNumber/all);
    return 0;
}