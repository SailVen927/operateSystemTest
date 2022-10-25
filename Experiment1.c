#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct{
    int     frt_tp;
    sem_t   sem_product;
    sem_t   sem_space;
    pthread_mutex_t mutex;
}frt_sem_mtx_def;


/*  父亲线程:盘子中为空，则随机添加水果
    frt_tp值为1-橘子，2-苹果
    对frt_tp进行资源加锁，更改后，释放锁
*/
void* fun_father(void* arg)
{
    frt_sem_mtx_def *frt = (frt_sem_mtx_def*)arg;
    int cnt = 0;
    while (1)
    {
        sem_wait(&frt->sem_space);
        sem_post(&frt->sem_product);

        sem_getvalue(&frt->sem_product, &cnt);
        pthread_mutex_lock(&frt->mutex);
        frt->frt_tp = rand()%2+1;
        pthread_mutex_unlock(&frt->mutex);
        if(frt->frt_tp==1){
printf("父亲 向盘中添加 橘子\n");
}else{
printf("父亲 向盘中添加 苹果\n");

}
        //printf("父亲 向盘中添加 苹果");
        //printf("father Thread 0x%lx put %d fruit, count:%d\n", pthread_self(), frt->frt_tp, cnt);

        sleep(1);
    }
}

/*  儿子线程：加锁访问frt_tp值
    若值是1，则对盘子中水果减一，对盘子空间加一
    重置frt_tp为0，最后释放锁
*/
void* fun_son(void* arg)
{
    frt_sem_mtx_def *frt = (frt_sem_mtx_def*)arg;

    int p_cnt = 0;
    int s_cnt = 0;
    
    while (1)
    {
        pthread_mutex_lock(&frt->mutex);
        if (frt->frt_tp == 1)
        {
            //对产品个数减一
            sem_wait(&frt->sem_product);
            //相应的空间加一
            sem_post(&frt->sem_space);
            sem_getvalue(&frt->sem_product, &p_cnt);
            sem_getvalue(&frt->sem_space, &s_cnt);
             printf("儿子 从盘中取走 橘子\n");
            //printf("Son Thread 0x%lx take %d fruit, p_cnt:%d, s_cnt:%d\n", pthread_self(),frt->frt_tp, p_cnt, s_cnt);
            frt->frt_tp = 0;
        }
        pthread_mutex_unlock(&frt->mutex);
        sleep(1);
    }
    return (void*)0;
}

/*  女儿线程：加锁访问frt_tp值
    若值是2，则对盘子中水果减一，对盘子空间加一
    重置frt_tp为0，最后释放锁
*/
void* fun_dau(void* arg)
{
    int p_cnt = 0;
    int s_cnt = 0;
    frt_sem_mtx_def *frt = (frt_sem_mtx_def*)arg;

    while (1)
    {
        pthread_mutex_lock(&frt->mutex);
        if (frt->frt_tp == 2)
        {
            //对产品个数减一
            sem_wait(&frt->sem_product);
            //相应的空间加一
            sem_post(&frt->sem_space);
            sem_getvalue(&frt->sem_product, &p_cnt);
            sem_getvalue(&frt->sem_space, &s_cnt);
            printf("女儿 从盘中取走 苹果\n");
            //printf("dau Thread 0x%lx take %d fruit, p_cnt:%d, s_cnt:%d\n", pthread_self(), frt->frt_tp, p_cnt, s_cnt);
            frt->frt_tp = 0;
        }

        pthread_mutex_unlock(&frt->mutex);
        sleep(1);

    }

    return (void*)0;
}

int main()
{
    pthread_t id1, id2, id3;
    frt_sem_mtx_def frt;
    frt.frt_tp = 0;
    // 初始化信号量
    sem_init(&frt.sem_product, 0, 0); // 初始状态水果为0
    sem_init(&frt.sem_space, 0, 1);   // 空间设置一个
    pthread_mutex_init(&frt.mutex, NULL);

    pthread_create(&id1, NULL, fun_father, (void*)&frt);
    pthread_create(&id2, NULL, fun_son, (void*)&frt);
    pthread_create(&id3, NULL, fun_dau, (void*)&frt);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);

    return 0;
}