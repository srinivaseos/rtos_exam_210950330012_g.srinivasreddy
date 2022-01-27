#include <stdio.h>
#include <freertos/task.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

TaskHandle_t task_handle1;
TaskHandle_t task_handle2;
TaskHandle_t task_handle3;
QueueHandle_t queue_handle1;

void task1(void *pv)
{
    //int sendingdata =0;
    while(1)
    {
        //sending data++;
        printf("hello this is task 1/n");
        vTaskDelay(1000 /portTICK_PERIOD_MS);
    }
}
void task2(void *pv)
{
    while(1)
    {
        printf("hello this is task 2/n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
void task3(void *pv)
{
    while(1)
    {
        printf("hello this is task 3/n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
void sending_queue(void *pv)
{
    int sendingdata = 0;
    while(1)
    {
        sendingdata++;
        printf("sending data is %d\n",sendingdata);
        xQueueSend(queue_handle1,&sending_queue,portMAX_DELAY);
    }
}
void receiving_queue(void *pv)
{
    int receiving_queue =0;
    while(1)
    {
        xQueueReceive(queue_handle1,&receiving_queue,portMAX_DELAY);
        printf("receiving data is %d\n",receiving_queue);
    }
}
void app_main()
{
    queue_handle1 = xQueueCreate(10,sizeof(int));
    xTaskCreate(task1,"hello",2048,NULL,5,&task_handle1);
    xTaskCreate(task2,"hello",2048,NULL,6,&task_handle2);
    xTaskCreate(task3,"hello",2048,NULL,7,&task_handle3);
    xTaskCreate(sending_queue,"hello",NULL,8,NULL);
    xTaskCreate(receiving_queue,"hello",NULL,9,NULL);
}

