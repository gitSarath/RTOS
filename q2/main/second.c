#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/timers.h"
#include"freertos/task.h"

TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TimerHandle_t timer;
static int taskcore = 1;

void timer_callback(TimerHandle_t timer)
{
    printf("the timer is activated!!!\n");
}
void first(void *data)
{
    printf("first task\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(task1);
}
void second(void *data)
{
    printf("second task\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    vTaskDelete(task2);
}
void third(void *data)
{
    printf("third task\n");
    timer=xTimerCreate("oneshot",pdMS_TO_TICKS(10000),pdFALSE,NULL,timer_callback);
    xTimerStart(timer,0);
    vTaskDelay(pdMS_TO_TICKS(10000));
    vTaskDelete(task3);

}
void app_main()
{
    xTaskCreatePinnedToCore(first,"first",2048,NULL,5,&task1,taskcore);
    xTaskCreatePinnedToCore(second,"second",2048,NULL,6,&task2,taskcore);
    xTaskCreatePinnedToCore(third,"third",2048,NULL,7,&task3,taskcore);
}
