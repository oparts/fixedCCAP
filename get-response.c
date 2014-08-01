#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 2202

struct test{
        long long req_time;
        long long res_time;
        int response;
};

struct test tr[N];
long long start;
long long end;
int interval;
long long time1;
long long time2;

int req_num;
int res_num;
unsigned long sum_response_time;
unsigned long avg_response_time;
unsigned long max_response_time;

main(){
int i;
for (i=0; i<N; i++)
{
        tr[i].req_time=0;
        tr[i].res_time=0;
        tr[i].response=0;
}

FILE *fp;
fp = fopen("newoutput.txt","r");
if (fp == NULL)
        return -1;
for (i=0; i<N&&!feof(fp); i++)
        fscanf(fp,"%lld %lld %d", &tr[i].req_time, &tr[i].res_time, &tr[i].response);
fclose(fp);

//for (i = 0; i <N; i++)
//        printf("%lld %lld %d\n", tr[i].req_time, tr[i].res_time, tr[i].response);

interval=200;
start=tr[0].req_time-interval;
end=tr[N-1].res_time;

time1=start;
time2=time1+interval;

req_num=0;
res_num=0;
sum_response_time=0;
avg_response_time=0;
max_response_time=0;

	for (time1 = start; time1 <= end; time1 = time1+interval)
	{
		time2=time1+interval;
                req_num=0;
                res_num=0;
                sum_response_time=0;
                avg_response_time=0;
		max_response_time=0;

	for (i = 0; i<N;i++)
	{
		if (time1 <= tr[i].req_time && tr[i].req_time < time2)
			req_num++;
		if (time1 <= tr[i].res_time && tr[i].res_time < time2)
		{
			res_num++;
			sum_response_time=sum_response_time + tr[i].response;
			avg_response_time=sum_response_time/res_num;
			if (tr[i].response > max_response_time)
				max_response_time = tr[i].response;
			//printf("%lld %d %d %lu\n", time1, req_num, res_num, avg_response_time);
		}
		if (tr[i].res_time >= time2 && i==N-1)
		{
			//time1 = time2;
			//time2 = time2 + interval;
			printf("%lld %d %d %lu %lu\n", time1, req_num, res_num, avg_response_time, max_response_time);
			break;
		}
		if (time1>end && i==N-1)
			break;
	}
	}


}
