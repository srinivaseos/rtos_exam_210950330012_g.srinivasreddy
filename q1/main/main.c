
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/queue.h>

QueueHandle_t queue;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;
TaskHandle_t xHandle_3;
TaskHandle_t xHandle_4;
TaskHandle_t xHandle_5;

void Task1(void *pvparameters)
{
    while(1)
    {
        printf("Task1 RUNNING\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void Task2(void *pvparameters)
{
    while(1)
    {
        printf("Task2 RUNNING\n");
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}

void Task3(void *pvparameters)
{
    while(1)
    {
        printf("Task3 RUNNING\n");
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
}
void Task4(void *pvparameters)
{
    int sending_data=0;
    while(1)
    {
        sending_data++;
        printf("Task4  RUNNING:%d\n",sending_data);
        xQueueSend(queue,&sending_data,portMAX_DELAY);
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void Task5(void *pvparameters)
{
    while(1)
    {
         int rece_data=0;
        xQueueReceive(queue,&rece_data,portMAX_DELAY);
        printf("RECEIVED DATA :%d\n",rece_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void app_main()
{
    queue=xQueueCreate(4,sizeof(int));
    BaseType_t result;
    result=xTaskCreate(Task1, "Task1",2048,NULL,5,&xHandle_1);
    if(result==pdPASS)
    {
        printf("Task1 created\n");
    }
    result=xTaskCreate(Task2,"Task2",2048,NULL,6,&xHandle_2);
    if(result==pdPASS)
    {
        printf("Task2 created\n");
    }
    result=xTaskCreate(Task3,"Task3",2048,NULL,7,&xHandle_3);
    if(result==pdPASS)
    {
        printf("Task3 created\n");
    }
    result=xTaskCreate(Task4, "Task4",2048,NULL,8,&xHandle_4);
    if(result==pdPASS)
    {
        printf("Task4 created\n");
    }
    result=xTaskCreate(Task5, "Task5",2048,NULL,9,&xHandle_5);
    if(result==pdPASS)
    {
        printf("Task5 created\n");
    }
}
