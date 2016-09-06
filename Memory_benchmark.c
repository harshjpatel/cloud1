//
//  main.c
//  memory_banchmark
//
//  Created by Harsh on 2/7/16.
//  Copyright © 2016 Harsh. All rights reserved.
//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<pthread.h>

#define number_of_thread 2                //value of threads
#define number_of_blocks 10485760          //1 mega_byte block size defined for memory operation(1024*1024=10485760 byte)

int number;
long init_time[number_of_thread];
long end_time[number_of_thread];

//sequential Access for 1 byte
void* sequential_byte(void *);          //Sequential Method for 1 Byte

//sequential Access for 1024 byte
void* sequential_kilo_byte(void *);     //sequential Method for 1 KB.

//sequential Access for 10485760 byte
void* sequential_mega_byte(void *);     //Sequential Method for 1 MB.

//Random Access for 1 byte
void* rand_byte(void *);                //Random Method for 1 Byte.

//Random Access for 1024 byte
void* rand_kilo_byte(void *);           //Random Method for 1 KB.

//Random Access for 10485760 byte
void* rand_mega_byte(void *);           //Random Method for 1 MB.

//calculate Time and throughput
void calculateTime(int number_of_bytes)
{
    double time_second,time_computed;
    long init,end,i;
    init=init_time[0];                //Time for initially
    end=end_time[0];                  //Time for endtime
    for(i=0;i<number_of_thread;i++)
    {
        if(init_time[i]<init)
            init=init_time[i];
        if(end_time[i]>end)
            end=end_time[i];
    }
    time_second=(double)(end-init)/1000.0;    //convert to milisecond
    
    printf("The time taken by %d threads for %d bytes is %lf miliseconds \n",number_of_thread,number_of_bytes,time_second);
    printf("Throughput for %d bytes block size by %d threads is %lf mega_byte/sec\n ",number_of_bytes,number_of_thread,(double)(number_of_blocks)/(time_second*1024*1024)); //Convert to mega_byte
    double throughput = ((double)(number_of_blocks)/(time_second*1024*1024));  //Throughput value derived
    double latency = ((double)(1/throughput));                              //Latency value defined
    printf("Throuhput is: %lf mega_byte/sec\n",throughput);
    printf("Latency is: %lf milisecond\n\n",latency*1000);
}



void main()
{
    double time;
    printf("\nMake your number! Choose any1 from three\n");
    printf("\n1.sequentialuential Access in 1 byte");
    printf("\nsequentialuential Access in 1 Kilobyte");
    printf("\nsequentialuential Access in 1 Megabyte");  //sequential Access
    printf("\n@@@@@@");
    printf("\n2.Random access in 1 byte");
    printf("\nRandom Access in 1 Kilobyte");
    printf("\nRandom Access in 1 Megabyte   \n7.Exit");//Random Access
    printf("\n\nMake your number\n");
    scanf("%d",&number);                                                       //Make your number
    pthread_t threads[number_of_thread];
    int hp;
    long t;
    switch(number)
    {
            
    case 1://for Seuential Access for 1 byte
            
            for(t=0;t<number_of_thread;t++)
            {
                printf("\nIn main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, sequential_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_thread;t++)
            {
                pthread_join(threads[t],NULL);
            }
            calculateTime(1);
                        //calculate for 1 byte.
            
    
            //for Seuential Access for 1 Kilobyte
    
            for(t=0;t<number_of_thread;t++)
            {
                printf("\nIn main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, sequential_kilo_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
        
            for(t=0;t<number_of_thread;t++)
            {
                pthread_join(threads[t],NULL);
            }
            calculateTime(1024);
             //calculate for 1024 byte = 1 KiloBytes
            
   
            //for Seuential Access for 1 Megabyte
            
            for(t=0;t<number_of_thread;t++)
            {
                printf("\nIn main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, sequential_mega_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            
            for(t=0;t<number_of_thread;t++)
            {
                pthread_join(threads[t],NULL);
            }
            calculateTime(1048576);  //1024*1024        //Calculate for 1024*1024 byte = 1 MegaByte
         
            
    
        case 2: //for Random Access for 1 byte
            
            for(t=0;t<number_of_thread;t++)
            {
                printf("\nIn main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, rand_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_thread;t++)
            {
                pthread_join(threads[t],NULL);
            }
            calculateTime(1);
                  //Calculate for 1 Byte
            
          
            //for Random Access for 1 Kilobyte
            
            for(t=0;t<number_of_thread;t++)
            {
                printf("\bIn main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, rand_kilo_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_thread;t++)
            {
                pthread_join(threads[t],NULL);
            }
            
            calculateTime(1024);
            //calaculate for 1024 byte = 1 KB
            
            //for Random Access for 1 Megabyte
            
            for(t=0;t<number_of_thread;t++)
            {
                printf("In main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, rand_mega_byte, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_thread;t++){
                pthread_join(threads[t],NULL);
            }
            
            calculateTime(1048576);         //calculate for 1 mega_byte block size byte
            break;
            
        default : exit(0);
                  break;
            
            
    }
}

void *sequential_byte(void* p)
{
    
    struct timeval init,stop;
    long long i;
    long tid=(long)p;
    int j;
    char *array1, *array2, *temp;
    array1 = (char *)malloc((number_of_blocks/number_of_thread));
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
    memset(array2,'a',number_of_blocks/number_of_thread);
    gettimeofday(&init,NULL);
    
    for(i=0;i<(number_of_blocks/number_of_thread);i++)
    {
        memcpy(array1+(i),array2+(i),1);                //Read and Write Operation
    }
    gettimeofday(&stop,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);
    free(array1);
    return 0;
}

void* sequential_kilo_byte(void* p)
{
    struct timeval init,stop;
    long long i;
    long tid=(long)p;
    int j;
    char *array1, *array2, *temp;
    array1 = (char *)malloc(number_of_blocks/number_of_thread);
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
    memset(array2,'a',number_of_blocks/number_of_thread);          //Read and Write peration
    gettimeofday(&init,NULL);
    for(i=0;i<(number_of_blocks/(1024*number_of_thread));i++)
    {
        memcpy(array1+(i*1024),array2+(i*1024),1024);
    }
    gettimeofday(&stop,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);
    free(array1);
    return 0;
}

void* sequential_mega_byte(void* p)
{
    struct timeval init,stop;
    long long i;
    long tid=(long)p;
    int j;
    char *array1, *array2, *temp1;
    array1 = (char *)malloc(number_of_blocks/number_of_thread);
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
    memset(array2,'a',number_of_blocks/number_of_thread);          //Read and Write Operation
    gettimeofday(&init,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    for(i=0;i<(number_of_blocks/(1024*1024*number_of_thread));i++)
    {
        memcpy(array1+(i*1024*1024),array2+(i*1024*1024),1048576);
    }
    gettimeofday(&stop,NULL);
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);
    free(array1);
    return 0;
}

void* rand_byte(void* p)
{
    struct timeval init,stop;
    long long i,k;
    long tid=(long)p;
    char *array1, *array2, *temp;
    long long M=0,N=(number_of_blocks/number_of_thread);
    array1 = (char *)malloc(number_of_blocks/number_of_thread);
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
    memset(array2,'a',number_of_blocks/number_of_thread);         //Read and Write Operation
    gettimeofday(&init,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    for(i=0;i<(number_of_blocks/number_of_thread);i++)
    {
        //k=rand()%1048576;
        srand((unsigned)time(NULL));
        k = M+rand() / (RAND_MAX/(N-M+1)+1);
        memcpy(array1+k,array2+k,1);
    }
    
    gettimeofday(&stop,NULL);
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);
    free(array1);
    return 0;
    
}

void* rand_kilo_byte(void* p)
{
    struct timeval init,stop;
    long long i,k;
    long tid=(long)p;
    long long M=0,N=(number_of_blocks/(1024*number_of_thread));
    char *array1, *array2, *temp;
    array1 = (char *)malloc(number_of_blocks/number_of_thread);
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
    memset(array2,'a',number_of_blocks/number_of_thread);             //Read and Write Operation
    gettimeofday(&init,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    for(i=0;i<(number_of_blocks/(1024*number_of_thread));i++)
    {
        //k=rand()%20479;
        srand((unsigned)time(NULL));
        k = M+rand() / (RAND_MAX/(N-M+1)+1);
        memcpy(array1+(k),array2+(k*1024),1024);
    }
    gettimeofday(&stop,NULL);
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);
    free(array1);
    return 0;
}


void* rand_mega_byte(void* p)
{
    struct timeval init,stop;
    long long i,k;
    long tid=(long)p;
    long long M=0,N=number_of_blocks/(1024*1024*number_of_thread);
    char *array1, *array2, *temp1;
    array1 = (char *)malloc(number_of_blocks/number_of_thread);
    array2 = (char *)malloc(number_of_blocks/number_of_thread);
   	memset(array2,'a',(number_of_blocks/number_of_thread));            //Read and write operation
    gettimeofday(&init,NULL);
    init_time[tid]=(init.tv_sec*1000000)+init.tv_usec;
    for(i=0;i<(number_of_blocks/(1024*1024*number_of_thread));i++)
    {
        //k=rand()%19;
        srand((unsigned)time(NULL));
        k = M+rand() / (RAND_MAX/(N-M+1)+1);                               //Randomly generate block
        memcpy(array1+(k),array2+(k*1048576),1048576);
    }
    
    gettimeofday(&stop,NULL);
    end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
    free(array2);       //free size of array
    free(array1);
    return 0;
}