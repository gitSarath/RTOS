#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/timers.h"
#include"freertos/task.h"
#include"freertos/queue.h"

TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;
TaskHandle_t task5;
QueueHandle_t que;
static int taskcore = 1;

void firsttask(void *data)
{
    printf("the first task\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(task1);
}
void secondtask(void *data)
{
    printf("the second task\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    vTaskDelete(task2);
}
void thirdtask(void *data)
{
    printf("the tird task\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    vTaskDelete(task3);
}
void fourthtask(void *data)
{
    int send=10;
    printf("data from forth task\n");
    while(1)
    {
        send++;
    xQueueSend(que,&send,pdMS_TO_TICKS(5000));
    }
    vTaskDelete(task4);
}
void fifthtask(void *data)
{
    int rec_buff=0;
    printf("data recieved in fifth task\n");
    while(1)
    {
    xQueueReceive(que,&rec_buff,pdMS_TO_TICKS(5000));
    printf("the data recieved is %d\n",rec_buff);
    }
    vTaskDelete(task5);
}

void app_main()
{
    que=xQueueCreate(5,50);
    xTaskCreatePinnedToCore(firsttask,"task1",2048,NULL,5,&task1,taskcore);
    xTaskCreatePinnedToCore(secondtask,"task2",2048,NULL,6,&task2,taskcore);
    xTaskCreatePinnedToCore(thirdtask,"task3",2048,NULL,7,&task3,taskcore);
    xTaskCreatePinnedToCore(fourthtask,"task4",2048,NULL,8,&task4,taskcore);
    xTaskCreatePinnedToCore(fifthtask,"task5",2048,NULL,9,&task5,taskcore);
}
