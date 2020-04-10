#include <stdio.h>
#include <stdlib.h>
#define number 21
typedef struct net_weight
{
    int vexs[number]; //顶点信息的数组
    int edge[number][number]; //边信息的数组
    int numV; //顶点数
    int numE;//边数
}AdjMatrix;
int g[21][21]={0},p[21][21],c[21][21]={0},end[20]={0},s[21][21]={0};
void create(AdjMatrix &a)//构建交通图的函数
{
    int i,j;
    a.numV=20;
    a.numE=31;
    for(i=1;i<=20;i++)
    {
        a.vexs[i]=i;
    }
    for(i=1;i<=20;i++)
    {
        for(j=1;j<=20;j++)
        {
            a.edge[i][j]=10000;
        }
    }
    a.edge[4][5]=a.edge[19][20]=a.edge[12][17]=a.edge[13][18]=1;
    a.edge[2][7]=a.edge[11][12]=a.edge[12][13]=a.edge[16][17]=a.edge[17][18]=a.edge[10][15]=2;
    a.edge[7][8]=a.edge[4][9]=a.edge[5][10]=a.edge[9][10]=3;
    a.edge[8][13]=a.edge[13][14]=a.edge[8][9]=a.edge[18][19]=4;
    a.edge[2][3]=a.edge[11][16]=5;
    a.edge[1][2]=a.edge[6][7]=a.edge[14][15]=6;
    a.edge[3][4]=a.edge[3][8]=a.edge[6][11]=a.edge[7][12]=a.edge[15][20]=a.edge[9][14]=7;
    a.edge[1][6]=a.edge[14][19]=8;
    for(i=1;i<=20;i++)
    {
        for(j=1;j<=20;j++)
        {
            a.edge[j][i]=a.edge[i][j];
        }
    }
}
void create_road_net()//输出公交车网函数
{
    printf("     带有权值的模拟交通图如下:                   公交线路如下：\n");
    printf("      6       5       7       1                1路   途径：1,6,11,16\n");
    printf(" 1·-----2·-----3·-----4·-----5·           2路   途径：2,7,12,17\n");
    printf("  8|      2|      7|      3|      3|           3路   途径：3,8,13,18\n");
    printf("   |  6    |  3    |  4    |  3    |           4路   途径：4,9,14,19\n");
    printf(" 6·-----7·-----8·-----9·----10·           5路   途径：5,10,15,20\n");
    printf("  7|      7|      4|      7|      2|           6路   途径：16,17,18,19,20\n");
    printf("   |  2    |  2    |  4    |  6    |           7路   途径：11,12,13,14,15\n");
    printf("11·----12·----13·----14·----15·           8路   途径：6,7,8,9,10\n");
    printf("  5|      1|      1|      8|      7|           9路   途径：1,2,3,4,5\n");
    printf("   |  2    |  2    |  4    |  1    |             地铁线路如下：\n");
    printf("16·----17·----18·----19·----20·           1号线 途径：1,6,7,8,9,10,15,20\n");
    printf("请输入两个数（在1~20之间，包括1和20）          2号线 途径：5,4,9,14,13,12,11,16\n");
}
void create_bus_net()//构建公交车网函数
{
    int i,j;
    c[1][2]=c[2][3]=c[3][4]=c[4][5]=9;
    c[6][7]=c[7][8]=c[8][9]=c[9][10]=8;
    c[11][12]=c[12][13]=c[13][14]=c[14][15]=7;
    c[16][17]=c[17][18]=c[18][19]=c[19][20]=6;
    c[5][10]=c[10][15]=c[15][20]=5;
    c[4][9]=c[9][14]=c[14][19]=4;
    c[3][8]=c[8][13]=c[13][18]=3;
    c[2][7]=c[7][12]=c[12][17]=2;
    c[1][6]=c[6][11]=c[11][16]=1;
    for(i=1;i<=20;i++)
    {
        for(j=1;j<=20;j++)
        {
            c[j][i]=c[i][j];
        }
    }
}
void create_subway_net()//构建地铁网函数
{
    int i,j;
    s[1][6]=s[6][7]=s[7][8]=s[8][9]=s[9][10]=s[10][15]=s[15][20]=101;
    s[4][5]=s[4][9]=s[9][14]=s[11][16]=s[11][12]=s[12][13]=s[13][14]=102;
    for(i=1;i<=20;i++)
    {
        for(j=1;j<=20;j++)
        {
            s[j][i]=s[i][j];
        }
    }
}
void getfast(AdjMatrix &a,int n,int dis[],int m)//迪杰特斯拉算法
{
    int v,i,z,w,final[21],min;
    for(v=1;v<=a.numV;v++)
    {
        final[v]=0;
        dis[v]=a.edge[n][v];
        for(w=1;w<=a.numV;w++)
        {
            p[v][w]=0;
        }
        if(dis[v]<10000)
        {
            p[v][n]=1;
            p[v][v]=1;
            g[v][1]=n;
            g[v][2]=v;
        }
    }
    dis[n]=0;
    final[n]=1;
    for(i=1;i<=a.numV;i++)
    {
        if(i==n) continue;
        min=10000;
        for(w=1;w<=a.numV;w++)
        {
            if(!final[w]&&(dis[w]<min))
            {
                v=w;
                min=dis[w];
            }
        }
        final[v]=1;
        for(w=1;w<=a.numV;w++)
        {
            if(! final[w]&&((min+a.edge[v][w])<dis[w]))
            {
                dis[w]=min+a.edge[v][w];
                for(z=1;z<=a.numV;z++)
                {
                    p[w][z]=p[v][z];
                }
                p[w][w]=1;
                for(z=1;z<=a.numV;z++) g[w][z]=g[v][z];
                for(z=1;;z++)
                {
                    if(g[w][z]==0)
                    {
                        g[w][z]=w;
                        break;
                    }
                }
            }
        }
    }
    printf("从%d到%d所需时间最短的路径为:",n,m);
    for(i=1;;i++)
    {
        if(g[m][i]!=0)
        {
            if(i==1) printf("地点");
            printf("%d",g[m][i]);
        }
        if(g[m][i+1]!=0) printf("-->地点");
        else break;
}
//以下为输出最短时间路径换乘表
    printf("\n换乘表如下:\n");
    int pre,t;
    for(i=1;;i++)
    {
        if(g[m][i+1]==0) break;
        v=g[m][i];
        z=g[m][i+1];
        t=0;
        if(i==1)
            {
                if(s[v][z]!=0)
                {
                printf("在地点%d乘坐地铁%d号线",v,s[v][z]-100);
                pre=s[v][z];
                }
                else
                {
                printf("在地点%d乘坐%d路公交车",v,c[v][z]);
                pre=c[v][z];
                }
            }
        else if(pre!=s[v][z])
        {
            if(s[v][z]!=0)
            {
                printf("\n");
                printf("在地点%d换乘地铁%d号线",v,s[v][z]-100);
                pre=s[v][z];
                t=1;
            }
        }
        if(t==0&&pre!=c[v][z]&&pre!=s[v][z])
        {
            printf("\n");
            printf("在地点%d换乘%d路公交车",v,c[v][z]);
            pre=c[v][z];
        }
    }
}
void getstraight(AdjMatrix &a,int n,int m)//计算最少换乘次数路径
{
    printf("从%d到%d换乘次数最少的路径为:",n,m);
    int i,j,k=0,t,z,g,end1[21]={0};
    if(n<m)
    {
        t=n;
        n=m;
        m=t;
        k=1;
    }
    if(n>m)
    {
        if((n-m)<=5)
        {
            for(i=n,t=0;i>=m;i--) if(i%5==0) t=1;
            if(t==0)  for(z=n,g=1;z>=m;z--,g++) end[g]=z;
            else
            {
                if(n%5==0) for(i=n,g=1;i>=m;i--,g++) end[g]=i;
                else if((n-m)==5)
                {
                    end[1]=n;
                    end[2]=m;
                }
                else
                {
                    end[1]=n;
                    end[2]=n-5;
                    if((n-5)<m)   for(z=(n-4),g=3;z<=m;g++,z++) end[g]=z;
                    else   for(z=(n-6),g=3;z>=m;g++,z--) end[g]=z;
                }
            }
        }
        else
        {
            for(z=n,g=1,t=0;;g++,z=z-5)
            {
                if((z>m&&(z-m)<5)||((z-m)==0))
                {
                    end[g]=z;
                    g++;
                    break;
                }
                else if((z-m)<0)
                {
                    t=1;
                    break;
                }
                end[g]=z;
            }
            if(t==1) z=z+5;
            n=z;
            if(z!=m)
            {
                for(i=n,t=0;i>=m;i--) if(i%5==0) t=1;
            if(t==0) for(z=n-1;z>=m;z--,g++) end[g]=z;
            else
            {
                if(n%5==0) for(i=n-1;i>=m;i--,g++) end[g]=i;
                else if((n-m)!=5)
                {
                    end[g]=n-5;
                    g++;
                    if((n-5)<m) for(z=(n-4);z<=m;g++,z++) end[g]=z;
                    else for(z=(n-6);z>=m;g++,z--) end[g]=z;
                }
            }
            }
        }
    }
    if(k==0)
    {
        for(i=1;;i++)
        {
            if(end[i]!=0)
            printf("地点%d",end[i]);
            else break;
            if(end[i+1]!=0) printf("-->");
        }
    }
    else
    {
        for(k=1;;k++)
        {
            if(end[k+1]==0)
            {
                z=k;
                break;
            }
        }
        t=z;
        for(i=z;;i--)
        {
            if(end[i]!=0)
            printf("地点%d",end[i]);
            else break;
            if(end[i-1]!=0) printf("-->");
        }
    }
    for(i=z,j=1;i>=1;i--,j++)  end1[j]=end[i];
for(i=1;end[i]!=0;i++)   end[i]=end1[i];
//以下为输出最少换乘路径换乘表
    printf("\n换乘表如下:\n");
    int pre,v;
    for(i=1;;i++)
    {
        if(end[i+1]==0) break;
        v=end[i];
        z=end[i+1];
        if(i==1)
            {
                printf("在地点%d乘坐%d路公交车",v,c[v][z]);
                pre=c[v][z];
            }
        else if(pre!=c[v][z])
        {
            printf("\n");
            printf("在地点%d换乘%d路公交车",v,c[v][z]);
            pre=c[v][z];
        }
    }
}


int main()
{
    int  n,m;
    int dis[20];
    create_road_net();
    create_subway_net();
    scanf("%d%d",&n,&m);
    AdjMatrix a;
    create(a);
    create_bus_net();
    getfast(a,n,dis,m);
    printf("\n");
    getstraight(a,n,m);
    return 0;
}
