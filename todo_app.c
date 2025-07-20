#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define RESET   15
#define BLUE    9
#define GREEN   10
#define RED     12
#define YELLOW  14
#define MAGNETA 13

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

typedef struct Node{
    char task[100];
    int completed;
    int count;
    struct Node* next;
} Node;

//view all tasks
void viewTasks(Node** head, int taskCount);

//add task
void addTask(Node** head, int *taskCount);

//delete task
void deleteTask(Node** head, int *taskCount);

//mark task as done
void markTaskCompleted(Node **head);
//Number the tasks
void adjustCount(Node** head);

void screenTop();

int main(){

    Node* head = NULL;
    int taskCount = 0;
    int taskNumber = 0;
    int choice;
    system("cls");
    do{
        screenTop();
        scanf(" %d", &choice);
        //perform different functions based on user's choice
        
        switch(choice){
            case 1:
                system("cls");
                setColor(GREEN);
                viewTasks(&head, taskCount);
                setColor(RESET);
                system("pause");
                break;
            case 2:
                system("cls");
                setColor(GREEN);
                addTask(&head, &taskCount);
                system("pause");
                break;
            case 3:
                system("cls");
                setColor(RED);
                deleteTask(&head, &taskCount);
                setColor(RESET);
                system("pause");
                break;
            case 4:
                system("cls");
                setColor(YELLOW);
                markTaskCompleted(&head);
                setColor(RESET);
                system("pause");
                break;
            case 5:
                system("cls");
                setColor(BLUE);
                printf("Bye! Hope to see you again.");
                setColor(RESET);
                break;
        }
    }while(choice != 5);
    free(head);
    return 0;
}

//display the application's starting interface
void screenTop(){
    setColor(BLUE);
    printf("************************************\n");
    printf("********* TODO LIST APP ************\n");
    printf("************************************\n");
    setColor(MAGNETA);
    printf("What would you like to do: \n");
    printf("1. View all tasks\n");
    printf("2. Add a new task\n");
    printf("3. Delete a task\n");
    printf("4. mark task as done\n");
    printf("5. Exit application\n");
    printf("Enter: ");
    setColor(RESET);
};

//view all tasks

void viewTasks(Node** head, int taskCount){
    Node* temp = *head;
    printf("\n\n******* TODO LIST *******\n");
    if(*head == NULL){
        setColor(RED);
        printf("No tasks added!\n");
        setColor(GREEN);
    }
    printf("TOTAL TASKS: %d task\n", taskCount);
    while(temp != NULL){
        printf("--------------------------\n");
        
        printf("%d.\n Task: %s\n IsDone: %s\n", temp->count, temp->task, temp->completed == 1 ? "Completed" : "Not Completed");
        printf("--------------------------\n");
        temp = temp->next;
        
        
    }
    printf("*************************\n");
    
}

//add a new task
void addTask(Node** head, int *taskCount){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->completed = 0;
    int count = 0;
    printf("Enter new Task: ");
    fflush(stdin);
    fgets(newNode->task, sizeof(newNode->task), stdin);
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        adjustCount(head);
        setColor(GREEN);
        printf("Task succesfully added!\n");
        (*taskCount)++;
        setColor(RESET);
        return;
    }
    Node* temp = *head;

    while(temp->next != NULL){
        temp = temp->next;
    }
    
    temp->next = newNode;
    
    (*taskCount)++;
    adjustCount(head);
    setColor(GREEN);
    printf("Task succesfully added!\n");
    setColor(RESET);
}



//delete a task
void deleteTask(Node** head, int *taskCount){
    if(*head == NULL){
    setColor(RED);
    printf("The node list is empty\n");
    setColor(RESET);
    return;
    }
    Node* temp = *head;
    Node* prev = NULL;
    int position;
    printf("Enter the task number for the task you want to delete: ");
    scanf(" %d", &position);
    if(temp != NULL && temp->count == position){
    *head = temp->next;
    free(temp);
    adjustCount(head);
    printf("Task succesfully deleted!\n");
    (*taskCount)--;
    return;
    }
    while(temp != NULL && temp->count != position){
    prev = temp;
    temp = temp->next;
    }
    if(temp == NULL) return;
    prev->next = temp->next;
    free(temp);
    (*taskCount)--;
    adjustCount(head);
    setColor(GREEN);
    printf("Task succesfully deleted!\n");
    setColor(RESET);
    
}

//mark task as completed
void markTaskCompleted(Node **head){
    Node* temp = *head;
    int position;
    printf("Enter task number to mark as completed: ");
    scanf("%d", &position);
    getchar();

    if(*head == NULL){
        setColor(RED);
        printf("List is empty\n");
        setColor(RESET);
    }
    if(temp != NULL && temp->count == position){
        temp->completed = 1;
        setColor(GREEN);
        printf("Task succesfully marked as done!\n");
        setColor(RESET);
        return;
    }
    while(temp != NULL && temp->count != position){
        temp = temp->next;
    }
    if(temp == NULL) return;
    temp->completed = 1;
    setColor(GREEN);
    printf("Task succesfully marked as done!\n");
    setColor(RESET);
}

//Number the tasks
void adjustCount(Node** head){
    Node* temp = *head;
    int i = 1;

    while (temp != NULL) {
        temp->count = i;
        i++;
        temp = temp->next;
    }
}