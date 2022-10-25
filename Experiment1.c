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


/*  �����߳�:������Ϊ�գ���������ˮ��
    frt_tpֵΪ1-���ӣ�2-ƻ��
    ��frt_tp������Դ���������ĺ��ͷ���
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
printf("���� ��������� ����\n");
}else{
printf("���� ��������� ƻ��\n");

}
        //printf("���� ��������� ƻ��");
        //printf("father Thread 0x%lx put %d fruit, count:%d\n", pthread_self(), frt->frt_tp, cnt);

        sleep(1);
    }
}

/*  �����̣߳���������frt_tpֵ
    ��ֵ��1�����������ˮ����һ�������ӿռ��һ
    ����frt_tpΪ0������ͷ���
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
            //�Բ�Ʒ������һ
            sem_wait(&frt->sem_product);
            //��Ӧ�Ŀռ��һ
            sem_post(&frt->sem_space);
            sem_getvalue(&frt->sem_product, &p_cnt);
            sem_getvalue(&frt->sem_space, &s_cnt);
             printf("���� ������ȡ�� ����\n");
            //printf("Son Thread 0x%lx take %d fruit, p_cnt:%d, s_cnt:%d\n", pthread_self(),frt->frt_tp, p_cnt, s_cnt);
            frt->frt_tp = 0;
        }
        pthread_mutex_unlock(&frt->mutex);
        sleep(1);
    }
    return (void*)0;
}

/*  Ů���̣߳���������frt_tpֵ
    ��ֵ��2�����������ˮ����һ�������ӿռ��һ
    ����frt_tpΪ0������ͷ���
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
            //�Բ�Ʒ������һ
            sem_wait(&frt->sem_product);
            //��Ӧ�Ŀռ��һ
            sem_post(&frt->sem_space);
            sem_getvalue(&frt->sem_product, &p_cnt);
            sem_getvalue(&frt->sem_space, &s_cnt);
            printf("Ů�� ������ȡ�� ƻ��\n");
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
    // ��ʼ���ź���
    sem_init(&frt.sem_product, 0, 0); // ��ʼ״̬ˮ��Ϊ0
    sem_init(&frt.sem_space, 0, 1);   // �ռ�����һ��
    pthread_mutex_init(&frt.mutex, NULL);

    pthread_create(&id1, NULL, fun_father, (void*)&frt);
    pthread_create(&id2, NULL, fun_son, (void*)&frt);
    pthread_create(&id3, NULL, fun_dau, (void*)&frt);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);

    return 0;
}