#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

//no. of thread is two.
#define number_of_threads 2        //no. of thread is two.
#define number_of_blocks 1         //1 block is defined
#define size_of_block 1024

long init_times[number_of_threads]; //no. of threads in initial time
long end_times[number_of_threads];  //no. of threads in end times

void compute_throughput()           //compute drive throuhput
{
    int i;
    double time_second;
    long least_begin_time=init_times[0];    //least_times is oth initial time
    long greatest_finish_time=end_times[number_of_threads-1];   //greatest_finish_time of last finish time
    
    for(i=0;i<number_of_threads;i++)     //to calculate initial and finish time
    {
        if(least_begin_time>init_times[i])
            least_begin_time=init_times[i];      //to optimize time
        if(greatest_finish_time<end_times[i])
            greatest_finish_time=end_times[i];      //to optimize time
    }
    time_second=((double)((greatest_finish_time)-(least_begin_time))/1000000.0);    //time_in_seconds
    printf("\nTime consumed:%lf",time_second );
    printf("\nThroughput im mbps::%lf MB/sec\n", (number_of_blocks/(time_second*1024*1024)*size_of_block)); //convert byte to mb
}

void *drive_sequence_write(void *threadid)
{
    printf("sequence write");
    struct timeval init,stop;
    FILE *file1;
    int i;
    long t_id=(long)threadid;  //t_id=threadID
    char buffer[size_of_block+1];
    memset(buffer,'****',size_of_block);  //copies * to buffer
    /* Open file for both reading and writing */
    char file_pointer[5];
    sprintf(file_pointer, "%ld", t_id); //for identification of pointer
    file1 = fopen(file_pointer, "w+");  //for write operation
    /* Write data to the file */
    gettimeofday(&init,NULL);  //to get initial time
    init_times[t_id]=init.tv_sec*1000000 + init.tv_usec;
    for(i=0;i <((number_of_blocks/size_of_block)/number_of_threads);i++)
    {
        fwrite(buffer, size_of_block, 1, file1);
    }
    gettimeofday(&stop,NULL);   //to get end time
    end_times[t_id]=stop.tv_sec*1000000 + stop.tv_usec;
    fclose(file1);  //file closing
    return 0;
}

void *drive_random_write(void *threadid)
{
    printf("Randomly write");
    long t_id=(long)threadid;
    struct timeval init,stop;
    FILE *file1;
    int i;
    char buffer[size_of_block+1];
    memset(buffer,'*',size_of_block);   //addset * to buffer
    char buffer1[size_of_block+1];
    memset(buffer,'!',size_of_block);   //addset ! to buffer
    /* Open file for both reading and writing */
    char file_pointer[5];
    sprintf(file_pointer, "%ld", t_id); //indication to file pointer
    file1 = fopen(file_pointer, "w+");     //write operation
    /* Write data to the file */
    for(i=0;i < ((number_of_blocks/size_of_block)/number_of_threads)+10;i++)
    {
        fwrite(buffer, size_of_block, 1, file1);
    }
    gettimeofday(&init,NULL);
    init_times[t_id]=init.tv_sec*1000000 + init.tv_usec;
    for(i=0;i < ((number_of_blocks/size_of_block)/number_of_threads);i++){
        fseek(file1, random()%((number_of_blocks/size_of_block)/number_of_threads),SEEK_SET); //to specify indication
        fwrite(buffer1, size_of_block,1, file1);
    }
    gettimeofday(&stop,NULL);
    end_times[t_id]=stop.tv_sec*1000000 + stop.tv_usec;
    fclose(file1);
    return 0;
}

void *drive_sequence_read(void *threadid)
{
    printf("sequence read");
    struct timeval init,stop;
    long t_id=(long)threadid;
    FILE *file1;
    int i;
    char buffer[size_of_block+1];
    memset(buffer,'*',size_of_block);
    /* Open file for both reading and writing */
    char file_pointer[5];
    sprintf(file_pointer, "%ld", t_id); //indication
    file1 = fopen(file_pointer, "w+");  //to write file
    /* Write data to the file */
    for(i=0;i < ((number_of_blocks/size_of_block)/number_of_threads)+10;i++)
        fwrite(buffer, size_of_block, 1, file1);
    fseek(file1,SEEK_SET,0);
    gettimeofday(&init,NULL);
    init_times[t_id]=init.tv_sec*1000000 + init.tv_usec;
    for(i=0;i < ((number_of_blocks/size_of_block)/number_of_threads);i++){
        fread(buffer, size_of_block, 1, file1);
    }
    gettimeofday(&stop,NULL);
    end_times[t_id]=stop.tv_sec*1000000 + stop.tv_usec;
    fclose(file1);
    return 0;
}

//Randomly read

void *drive_random_read(void *threadid)
{
    printf("Randomly read");
    struct timeval init,stop;
    long t_id=(long)threadid;
    FILE *file1;
    int i;
    char buffer[size_of_block+1];
    memset(buffer,'*',size_of_block);
    /* Open file for both reading and writing */
    char file_pointer[5];
    sprintf(file_pointer, "%ld", t_id);
    file1 = fopen(file_pointer, "w+");
    /* Write data to the file */
    for(i=0;i < (((number_of_blocks/size_of_block)/number_of_threads)+10);i++)
        fwrite(buffer, size_of_block, 1, file1);
    fseek(file1,SEEK_SET,0);
    gettimeofday(&init,NULL);
    init_times[t_id]=init.tv_sec*1000000 + init.tv_usec;
    for(i=0;i < ((number_of_blocks/size_of_block)/number_of_threads);i++)
    {
        fseek(file1, random() % ((number_of_blocks/size_of_block)/number_of_threads), SEEK_SET);
        fread(buffer, size_of_block, 1, file1);
    }
    gettimeofday(&stop,NULL);
    end_times[t_id]=stop.tv_sec*1000000 + stop.tv_usec;
    fclose(file1);
    return 0;
}

int main()
{
    pthread_t threads[number_of_threads];
    int hp, option;;
    long init,end;
    long t;
    printf("This is drive benchmark Program");
    printf("\nMake Your choice first:");
    printf("\n1.sequential write	\n2.random write	\n3.sequential read  \n4.random read  \n5.exit");
    printf("\nEnter your Choice no.:");
    printf("\n");
    scanf("%d",&option);
   	switch(option)
    {
            
        case 1:             //sequential write Method
            for(t=0;t<number_of_threads;t++)
            {
                printf("In main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, drive_sequence_write, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_threads;t++)
                pthread_join(threads[t],NULL);
            break;
        
       
        case 2:         //random write
            for(t=0;t<number_of_threads;t++)
            {
                printf("In main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, drive_random_write, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_threads;t++)
                pthread_join(threads[t],NULL);
            break;
            
        case 3:         //sequential Read
            for(t=0;t<number_of_threads;t++)
            {
                printf("In main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, drive_sequence_read, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_threads;t++)
                pthread_join(threads[t],NULL);
            break;
            
        case 4:// random Read
            for(t=0;t<number_of_threads;t++)
            {
                printf("In main: creating thread %ld\n", t);
                hp = pthread_create(&threads[t], NULL, drive_random_read, (void *)t);
                if (hp)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", hp);
                    exit(-1);
                }
            }
            for(t=0;t<number_of_threads;t++)
                pthread_join(threads[t],NULL);
            break;
            
        case 5: //Make EXIT
            exit(-1);
            
        default:
            printf("please enter a valid option");
            break;     
    }	
    
    /* Last thing that main() should do */
    compute_throughput ();
    pthread_exit(NULL);
}
