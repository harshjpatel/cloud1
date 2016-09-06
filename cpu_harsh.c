//
//  main.c
//  cpu_new
//
//  Created by Harsh on 2/5/16.
//  Copyright © 2016 Harsh. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#define number_of_threads 4


long init_times[number_of_threads];
long end_times[number_of_threads];
long init_times_iop[number_of_threads];
long end_times_iop[number_of_threads];

void *Flops_compute(void *thread_id)
{
    long t_id;
    int i;
    float result,n1=113.5455f,n2=112.423f;
    float n3=145.345f,n4=123.238f,n5=111.447f;
    //find by aithmatic formula
    double sum1=0.1, sum2=-0.1,sum3=0.2;
    double sum4=-0.2, sum5=0.0;
    double add=0.1,sum0=0.1, sum6=-0.1, sum7=0.2;
    double sum8=-0.2;
    double sum9=0.0,sum10=0.1, sum11=0.1, sum12=0.2;
    double sum13=0.3, sum14=0.0;
    double mul1=1.0, mul2= 1.1, mul3=1.2, mul4= 1.3;
    double mul5=1.4,mul=1.1,mul0=1.0;
    double mul6= 1.1, mul7=1.2;
    double mul8= 1.3, mul9=1.4,mul10=1.1,mul11=1.2;
    double mul12=1.0;
    double mul13=1.1,mul14=1.2;
    struct timeval init,stop;
    t_id = (long)thread_id;
    gettimeofday(&init,NULL);
    init_times[t_id]=init.tv_sec*1000000 + init.tv_usec;
    
    
    for(i=0;i<10000000000/(30*number_of_threads);i++)
    {
        mul1*mul;
        mul2*mul;
        mul3*mul;
        sum1+add;
        sum2+add;
        sum3+add;
        mul4*mul;
        mul5*mul;
        mul1*mul;
        sum4+add;
        sum5+add;
        sum1+add;
        mul2*mul;
        mul3*mul;
        mul4*mul;
        sum2+add;
        sum3+add;
        sum4+add;
        mul5*mul;
        mul1*mul;
        mul2*mul;
        sum5+add;
        sum1+add;
        sum2+add;
        mul3*mul;
        mul4*mul;
        mul5*mul;
        sum3+add;
        sum4+add;
        sum5+add;
        
    }
    
    gettimeofday(&stop,NULL);
    end_times[t_id]=stop.tv_sec*1000000 + stop.tv_usec;
    
    printf("\ntime for thread %ld :: end times %ld - init times %ld ", t_id, end_times[0], init_times[0]);
    printf("\ntime for thread %ld :: end times %ld - init times %ld ", t_id, end_times[1], init_times[1]);
    printf("\ntime for thread %ld :: end times %ld - init times %ld ", t_id, end_times[2], init_times[2]);
    printf("\ntime for thread %ld :: end times %ld - init times %ld ", t_id, end_times[3], init_times[3]);
    
    if(t_id==0)
        printf("\ntime consumed:%ld microseconds",(stop.tv_sec*1000000 + stop.tv_usec) - (init.tv_sec*1000000 + init.tv_usec));
    
    if(t_id==1)
        printf("\ntime consumed:%ld microseconds",(stop.tv_sec*1000000 + stop.tv_usec) - (init.tv_sec*1000000 + init.tv_usec));
    
    if(t_id==2)
        printf("\ntime consumed:%ld microseconds",(stop.tv_sec*1000000 + stop.tv_usec) - (init.tv_sec*1000000 + init.tv_usec));
    
    if(t_id==3)
        printf("\ntime consumed:%ld microseconds",(stop.tv_sec*1000000 + stop.tv_usec) - (init.tv_sec*1000000 + init.tv_usec));
    pthread_exit(NULL);
}

void *IOPS_compute(void *thread_id)
{
    long t_id;
    int i;
    int sum1=1, sum2=-2, sum3=1, sum4=-2, sum5=1,add=0,sum0=2, sum6=1, sum7=1, sum8=-2, sum9=-1,sum10=1, sum11=1, sum12=2, sum13=-1, sum14=1;
    int mul1=1, mul2= 1, mul3=1, mul4= 1, mul5=1,mul=1,mul0=1, mul6= 1, mul7=1, mul8= 1, mul9=1,mul10=1,mul11=1,mul12=1,mul13=1,mul14=1;
    struct timeval init_iop,stop_iop;
    t_id = (long)thread_id;
    gettimeofday(&init_iop,NULL);
    init_times_iop[t_id]=init_iop.tv_sec*1000000 + init_iop.tv_usec;
    
    
    for(i=0;i<10000000000/(30*number_of_threads);i++){
        mul1*mul;
        mul2*mul;
        mul3*mul;
        sum1+add;
        sum2+add;
        sum3+add;
        mul4*mul;
        mul5*mul;
        mul1*mul;
        sum4+add;
        sum5+add;
        sum1+add;
        mul2*mul;
        mul3*mul;
        mul4*mul;
        sum2+add;
        sum3+add;
        sum4+add;
        mul5*mul;
        mul1*mul;
        mul2*mul;
        sum5+add;
        sum1+add;
        sum2+add;
        mul3*mul;
        mul4*mul;
        mul5*mul;
        sum3+add;
        sum4+add;
        sum5+add;
    }
    gettimeofday(&stop_iop,NULL);
    end_times_iop[t_id]=stop_iop.tv_sec*1000000 + stop_iop.tv_usec;
    
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[number_of_threads],threads_iops[number_of_threads];
    int rc,rc1,rc2,r_c1,r_c2,r_c3;
    long t,init,init_iop,end,end_iop,j;
    double flops_total_time,iops_total_time;
    for(t=0; t<number_of_threads; t++){
        printf("the loop will do it 600 times:");
        printf("\nIn main: creating thread %ld\n", t);
        r_c1 = pthread_create(&threads[1], NULL, Flops_compute, (void *)t);
        r_c2 = pthread_create(&threads[2], NULL, Flops_compute, (void *)t);
        r_c3 = pthread_create(&threads[4], NULL, Flops_compute, (void *)t);
    }
    //wait for all child threads to finish
    for(t=0; t<number_of_threads; t++){
        pthread_join(threads[t],NULL);
    }
    init=init_times[0];
    end=end_times[0];
    for(j=1;j<number_of_threads;j++)
    {
        if(init_times[j]< init)
            init=init_times[j];
        if(end_times[j]>end)
            end=end_times[j];
    }
    flops_total_time=((double)(end-init))/1000000.0;
    printf("\n\nTotal time taken by %d threads for FLOPS is:%ld microseconds and %lf seconds",number_of_threads,(end-init),flops_total_time);
    
    
    for(t=0; t<number_of_threads; t++){
        printf("\nIn main: creating thread %ld\n", t);
        rc = pthread_create(&threads_iops[1], NULL, IOPS_compute, (void *)t);
        rc1 = pthread_create(&threads_iops[2], NULL, IOPS_compute, (void *)t);
        rc2 = pthread_create(&threads_iops[4], NULL, IOPS_compute, (void *)t);
        
    }
    //wait for all threads to finish
    for(t=0; t<number_of_threads; t++){
        pthread_join(threads_iops[t],NULL);
    }
    //get the initing and largest time
    
    init_iop=init_times_iop[0];
    //printf("init_iop:%ld",init_iop);
    
    end_iop=end_times_iop[0];
    //printf("end_iop:%ld",end_iop);
    for(j=1;j<number_of_threads;j++)
    {
        if(init_times_iop[j]< init_iop)
            init_iop=init_times_iop[j];
        if(end_times_iop[j]>end_iop)
            end_iop=end_times_iop[j];
    }
    printf("The initing time is:%ld",init);
    printf("The initing ending time is:%ld",end);
    
    iops_total_time=((double)(end_iop-init_iop))/1000000.0;
    
    printf("\n\n Total time taken by %d threads for IOPS is:%ld microseconds and %lf seconds",number_of_threads,(end_iop-init_iop),iops_total_time);
    
    printf("\nprinting GIGA FLOPS...\n");
    printf("%lf",((double)(10000000000.0))/(flops_total_time*1000000000.0));
    printf("\n****\n");
    printf("printing GIGA IOPS\n");
    printf("%lf",((double)(10000000000.0))/(iops_total_time*1000000000.0));
    /* Last thing that main() should do */
    pthread_exit(NULL);
}