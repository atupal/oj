
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INF 2147483647

const int maxn = 101;

int n;
double min;
double r[maxn];

void swap(int i, int j) {
    double t = r[i]; r[i] = r[j]; r[j] = t;
}

void calc() {
    double x[n];
    double mr = 0;
    x[0] = r[0];
    for (int i = 1; i < n; ++ i) {
        double t;
        for (int j = i - 1; j >= 0; -- j) {
            t = 2 * sqrt(r[i] * r[j]);
            x[i] = x[j] + t;
            int flag = 0;
            for (int k = j - 1; k >= 0; -- k) {
                t = 2 * sqrt(r[i] * r[k]);
                if (x[i] - x[k] < t) {
                    flag = 1;
                    break;
                }
            }
            if (x[i] < r[i]) {x[i] = r[i];}
            if (flag) continue;
            else break;
        }
    }
    for (int i = 0; i < n; ++ i) if (x[i] + r[i] > mr) {
        mr = x[i] + r[i];
    }
    min = mr < min ? mr : min;
}

void arr(int cur) {
    if (cur == n) {
        calc();
        return;
        for (int i = 0; i < n; ++ i) {
            printf("%f ", r[i]);
        }
        printf("\n");
    }
    else for (int i = cur; i < n; ++ i) if(r[i] != r[cur] || i == cur){
        swap(cur, i);
        arr(cur + 1);
        swap(cur, i);
    }
}

int main() {
    int tn;
    scanf("%d", &tn);
    while (tn--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) scanf("%lf", &r[i]);
        min = INF;
        arr(0);
        printf("%.3lf\n", min);
    }

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define len 10
double radius[len],r[len],x[len],min;
int n;
int cmp(const void *a,const void *b){
    return *(double *)a>*(double *)b?1:-1;
}
double dis(int past,int now){                           //计算圆心横坐标
    return x[past]+2*sqrt(r[past]*r[now]);               //(R+r)^2-(R-r)^2=d^2
}
void dfs(int cur,double num){
    int i,j,c1,c2;
    double max,length;
    if(cur==n){
        if(min>num)
            min=num;
        return ;
    }
    for(i=0;i<n;i++)
        if(!i||radius[i]!=radius[i-1]){          //枚举符合条件的全排列
            c1=c2=0;
            for(j=0;j<n;j++)
                if(radius[i]==radius[j])
                    c1++;
            for(j=0;j<cur;j++)
                if(radius[i]==r[j])
                    c2++;
            if(c1>c2){                           //控制元素的添加
                r[cur]=radius[i];
                if(cur){                              //如果已经有元素,那么对先前的元素逐个判断
                    for(j=0,max=0.;j<cur;j++){
                        length=dis(j,cur);
                        if(max<length)
                            max=length;
                    }
                    if(r[cur]>max){                  //如果为真则表明第cur个圆的一部分已经落在x负半轴，为了从0开始计算全部圆心坐标向右平移
                        for(j=0;j<cur;j++)
                            x[j]+=r[cur]-max;
                        x[cur]=r[cur];
                    }
                    else
                        x[cur]=max;
                }
                else
                    x[cur]=r[cur];
                if(num<x[cur]+r[cur])                  //选取大的进行递归
                    dfs(cur+1,x[cur]+r[cur]);
                else
                    dfs(cur+1,num);
            }
        }
}
int main(void){
    int ncase,i;
    scanf("%d",&ncase);
    while(ncase--){
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%lf",&radius[i]);
        //deal
        min=100000000.;
        qsort(radius,n,sizeof(radius[0]),cmp);
        dfs(0,0.);
        printf("%.3lf\n",min);
    }
    return 0;
}
*/
