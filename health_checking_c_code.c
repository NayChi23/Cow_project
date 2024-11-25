/*!
 * @file health_checking_c_code.c
 * @brief code that can give you output 1 or 0 depending on the result of the sensor
 *
 * @author [Nay Chi]
 * @version  V1.0
 * @date  2024-11-25
 * @url https://github.com/NayChi23/Cow_project
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLS 7
#define MAX_ROWS 2 //180 for the estrus and it will take 18 round to get one data which is equalivalent to 4 hours
#define MAX_FIELD_LENGTH 50
#define MAX_SIZE 3

// Define the node structure for a doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the list from the given node to the end
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
// Function to delete every node in the list
void deleteList(struct Node** head) {
    struct Node* temp = *head;
    struct Node* nextNode;

    while (temp != NULL) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    *head = NULL;
}

struct CircularQueue {
    int* arr; // Array to store queue elements
    int front, rear; // Front and rear pointers
    int capacity; // Maximum capacity of the queue
    int size; // Current number of elements in the queue
};

struct CircularQueue* createQueue(int capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->size = 0;
    return queue;
}
int isEmpty(struct CircularQueue* queue) {
    return queue->size == 0;
}

void enqueue(struct CircularQueue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size++;
    //printf("%d enqueued to queue\n", item);
}

int dequeue(struct CircularQueue* queue) {
    int item = queue->arr[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

void printQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Elements of the queue are: ");
    int i = queue->front;
    do {
        printf("%d ", queue->arr[i]);
        i = (i + 1) % queue->capacity;
    } while (i != (queue->rear + 1) % queue->capacity);
    printf("\n");
}
int indexFinding(struct CircularQueue* queue, int no){
    int i = queue->front;
    int count = 0;
    while (count <queue->size)
    {
        if(count == no)
        {
            return queue->arr[i];
            break;
        }
        i = (i + 1) % queue->capacity;
        count++;
    }
}

int Health(float,float,float,float,float,float);
int CompareData(int, int, int);

int main(){
    unsigned int numberZero =0; //only reset to 0 if the data are equal to one day
    unsigned int numberOne =0;  //Store how many 1's in the data
    unsigned int num=0;
    bool FirstTurn = 1;
    unsigned int check_First_two_day = 0;
    //unsigned long int total_one_day_count[3] = {0,0,0};
    struct CircularQueue* total_one_day_count = createQueue(MAX_SIZE);
    struct Node* result_data = NULL;

    while(1){
        //For this i would like to use cicular queue for pushing the data 240 data
        char field[MAX_ROWS][MAX_COLS][MAX_FIELD_LENGTH] = {
            {"15:34:52,0.02,0.88,-0.3,-28.39,-21.01,-29.82"},
            {"15:34:52,-0.05,-0.17,0.79,-21.53,-23.01,21.22"}
            //May be add the number later according to the data
        };
        if(num == 108 && FirstTurn  == 1)
        {
            //need condition to put it into the double linked list array
            enqueue(total_one_day_count,numberOne);
            printf("the total number one is %d\n", numberOne);
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
            check_First_two_day += 1;
            printf("Complete %d turn \n", check_First_two_day);
            printQueue(total_one_day_count);
            
            if(check_First_two_day == 3)
            {
                FirstTurn = 0;
                printf("The result of compared data is\t%d\n",CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
                insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
                printf("%d\n",indexFinding(total_one_day_count,0));
                printf("%d\n",indexFinding(total_one_day_count,1));
                printf("%d\n",indexFinding(total_one_day_count,2));
            }
            
        }        
        else if(num == 108 && FirstTurn  == 0){
            dequeue(total_one_day_count);
            printQueue(total_one_day_count);
            enqueue(total_one_day_count,numberOne);
            printQueue(total_one_day_count);
            printf("The result of compared data is\t%d\n",CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
            insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
            printf("%d\n",indexFinding(total_one_day_count,0));
            printf("%d\n",indexFinding(total_one_day_count,1));
            printf("%d\n",indexFinding(total_one_day_count,2));
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
            break;
        }
        else{
        unsigned int row = 0, col = 0, b=0;

        char tempoarray[MAX_COLS][MAX_FIELD_LENGTH];
        while(row<MAX_ROWS && field[row][0][0] != '\0'){
            col = 0; // Reset col for each row
            char* token = strtok(field[row][col], ",");
            
            while (token != NULL && col < MAX_COLS) {
                strcpy(tempoarray[col], token);
                token = strtok(NULL, ",");
                col +=1;
            }
            // Display the items in the row
            /*for (b = 0; b < col; b++) {
                printf("%s\t", tempoarray[b]);
            }
            printf("\n"); // Newline after each row
            */
            row++;
            float ax,ay,az,gx,gy,gz;
            ax = atof(tempoarray[1]);
            ay = atof(tempoarray[2]);
            az = atof(tempoarray[3]);
            gx = atof(tempoarray[4]);
            gy = atof(tempoarray[5]);
            gz = atof(tempoarray[6]);
            //printf("%.2f %.2f %.2f %.2f %.2f %.2f\n",ax,ay,az,gx,gy,gz);
            //printf("%d\n",Estreus(ax,ay,az,gx,gy,gz));
			if (Health(ax,ay,az,gx,gy,gz)==1 || Health(ax,ay,az,gx,gy,gz)==2){
				numberOne = numberOne +1;
			}
            else{
                numberZero = numberZero +1;
            }
			//printf("%d\n",Ruminating(ax,ay,az,gx,gy,gz));
            
        }
        num +=1;
        //printf("row number is %u\n",row);
        printf("the total loop number is %u\n",num);
        }
    }
    return 0;
}

int CompareData(int firstDay, int secondDay, int thirdDay) {
  /*if (firstDay > (secondDay + (0.1 * secondDay))) {  // 10% more
    if (secondDay > (thirdDay + (0.1 * thirdDay))) {
      return 1; //Warning
    } else {
      return -1; //Warning
    }
  } else {
    return 0; //OK
    //But have to ask the condition first
  }*/
 if (firstDay > (secondDay + (0.1 * secondDay))) {  // 10% more
      return 1; //Warning
    } 
else {
    return 0; //OK
    //But have to ask the condition first
  }
}
//RUMINATING and Sitting 
int Health(float Ax,float Ay,float Az,float Gx,float Gy,float Gz){
float AxXGx = Ax * Gx, AyXAz = Ay * Az, AxXGy = Ax * Gy, AxXGz = Ax * Gz, AxXAy = Ax * Ay, AxXAz = Ax * Az, AyXAx = Ay * Ax, AyXGx = Ay * Gx, AyXGy = Ay * Gy, AyXGz = Ay * Gz, AzXAx = Az * Ax, AzXAy = Az * Ay, AzXGx = Az * Gx, AzxGy = Az * Gy, AzXGz = Az * Gz, Ax_squared = Ax * Ax, Ay_squared = Ay * Ay, Az_squared = Az * Az, Gx_squared = Gx * Gx, Gy_squared = Gy * Gy, Gz_squared = Gz * Gz, GxXGz = Gx * Gz, GxXGy = Gx * Gy, GyXGz = Gy * Gz, AzXGy = Az * Gy;
	if ( Az <= 1.05) {
		if ( Gz <= 0.73) {
			if ( Ay <= -0.62) {
				if ( Gy_squared <= -0.11) {
					if ( AzXGx <= -0.03) {
						if ( AyXGz <= 0.0) {
							if ( Ax_squared <= -0.11) {
								if ( GyXGz <= -0.03) {
									if ( Az <= -0.66) {
										if ( AzXGx <= -0.18) {
											return 0;
										}
										else {
											if ( AyXGz <= -0.22) {
												return 0;
											}
											else {
												if ( AyXAz <= 0.74) {
													return 2;
												}
												else {
													if ( GyXGz <= -0.03) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( AyXGx <= -0.21) {
											if ( AxXAz <= 0.04) {
												if ( AzXGx <= -0.23) {
													return 0;
												}
												else {
													if ( AyXAz <= 0.33) {
														return 1;
													}
													else {
														if ( Ay <= -0.72) {
															return 2;
														}
														else {
															if ( AxXGz <= 0.0) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												if ( Az_squared <= -0.1) {
													if ( GxXGz <= 0.08) {
														if ( AzXGy <= 0.04) {
															if ( Gx <= 0.54) {
																if ( AzXGz <= -0.02) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGy <= 0.09) {
														if ( Ay <= -0.64) {
															if ( Gz_squared <= -0.13) {
																return 1;
															}
															else {
																if ( Ay_squared <= 0.15) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gz <= 0.19) {
												if ( AxXGy <= 0.0) {
													if ( AzXGy <= 0.11) {
														if ( AxXAz <= -0.05) {
															return 2;
														}
														else {
															if ( Ay <= -0.71) {
																return 2;
															}
															else {
																if ( Ay_squared <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( Ay_squared <= 0.12) {
														if ( AyXAz <= 0.57) {
															if ( AxXGz <= -0.02) {
																if ( Ay <= -0.63) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXAy <= 0.2) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( GxXGy <= -0.01) {
																return 1;
															}
															else {
																if ( Gz <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXAy <= -0.1) {
													return 2;
												}
												else {
													if ( AzXGz <= -0.07) {
														if ( AyXGx <= -0.17) {
															return 2;
														}
														else {
															if ( AxXGy <= -0.02) {
																return 0;
															}
															else {
																if ( AyXGz <= -0.15) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
								}
								else {
									if ( Az_squared <= -0.22) {
										if ( Gz_squared <= -0.12) {
											if ( Ay <= -0.69) {
												return 2;
											}
											else {
												if ( AxXGx <= -0.06) {
													return 2;
												}
												else {
													if ( AyXAz <= 0.04) {
														return 2;
													}
													else {
														if ( GxXGy <= 0.03) {
															return 2;
														}
														else {
															if ( Gx <= 0.53) {
																return 2;
															}
															else {
																if ( AzXGx <= -0.07) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( AxXAz <= 0.06) {
											if ( Az_squared <= -0.14) {
												if ( AxXAz <= 0.05) {
													if ( GyXGz <= 0.0) {
														if ( Gz <= 0.33) {
															if ( Gy_squared <= -0.14) {
																if ( AyXGz <= -0.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gy_squared <= -0.14) {
														if ( AyXGz <= -0.01) {
															if ( AzXGx <= -0.04) {
																if ( Gy <= 0.15) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( GxXGy <= 0.02) {
													if ( AzXGy <= -0.01) {
														if ( AxXAz <= -0.06) {
															return 2;
														}
														else {
															if ( Ay <= -0.72) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXGy <= 0.02) {
														if ( GxXGz <= 0.03) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXAz <= 0.42) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.14) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
										else {
											if ( Az_squared <= -0.18) {
												if ( AyXGx <= -0.42) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.03) {
														if ( AxXAy <= 0.31) {
															if ( Gz_squared <= -0.13) {
																if ( AxXGx <= -0.02) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= -0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXGz <= -0.14) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Gz_squared <= -0.13) {
															return 2;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Ay <= -0.67) {
													if ( AyXAz <= 0.7) {
														if ( Gx_squared <= -0.12) {
															if ( AxXGy <= 0.01) {
																if ( GyXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy <= 0.31) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Ay <= -0.77) {
																return 1;
															}
															else {
																if ( AyXAz <= 0.57) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Az <= -0.77) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AyXAz <= 0.6) {
														if ( AyXAz <= 0.34) {
															if ( GxXGy <= 0.05) {
																if ( AxXGy <= 0.0) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGz <= -0.02) {
																if ( GxXGy <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= 0.05) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AxXGx <= -0.07) {
															return 1;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( GyXGz <= -0.03) {
									if ( GxXGz <= 0.04) {
										if ( AyXAz <= 0.57) {
											if ( GxXGz <= 0.02) {
												return 0;
											}
											else {
												if ( AyXAz <= 0.21) {
													return 0;
												}
												else {
													if ( GxXGy <= -0.03) {
														return 0;
													}
													else {
														if ( GxXGy <= -0.01) {
															return 2;
														}
														else {
															if ( GxXGy <= -0.01) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											if ( GxXGz <= 0.02) {
												return 0;
											}
											else {
												if ( AxXGx <= 0.05) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( AyXAz <= 0.3) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( AyXGy <= 0.09) {
										if ( Ay <= -0.7) {
											if ( Gz <= 0.24) {
												if ( Ax_squared <= -0.04) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gz <= 0.02) {
												return 1;
											}
											else {
												if ( AzXGz <= -0.17) {
													return 0;
												}
												else {
													if ( Ax_squared <= 0.2) {
														if ( AzXGx <= -0.04) {
															if ( AzXGz <= -0.01) {
																if ( Gy_squared <= -0.15) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										return 0;
									}
								}
							}
						}
						else {
							if ( GxXGz <= -0.01) {
								if ( GxXGy <= -0.07) {
									if ( AzXGy <= 0.06) {
										if ( AyXGx <= -1.21) {
											return 0;
										}
										else {
											if ( Gz <= -1.09) {
												return 1;
											}
											else {
												if ( Az_squared <= -0.23) {
													return 1;
												}
												else {
													if ( AxXGz <= -0.13) {
														return 0;
													}
													else {
														if ( GxXGz <= -0.24) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( Az <= -0.33) {
											return 0;
										}
										else {
											if ( Ay_squared <= 0.01) {
												if ( Gz <= -0.85) {
													if ( Gz <= -1.09) {
														return 1;
													}
													else {
														if ( Gx <= 1.47) {
															return 0;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( AzXGz <= 0.06) {
										return 1;
									}
									else {
										if ( GxXGy <= -0.01) {
											if ( Gx <= 1.11) {
												if ( AyXGx <= -0.27) {
													if ( Gz_squared <= -0.12) {
														return 1;
													}
													else {
														if ( AzXGz <= 0.23) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Gz <= -0.6) {
												if ( GyXGz <= 0.0) {
													if ( AzXGy <= 0.02) {
														if ( AyXAz <= 0.22) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.34) {
																return 0;
															}
															else {
																if ( AzXGz <= 0.2) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gx <= 0.43) {
													if ( AxXGy <= -0.06) {
														return 1;
													}
													else {
														if ( Gz <= -0.57) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AzXGx <= -0.48) {
														return 0;
													}
													else {
														if ( AxXGz <= -0.01) {
															if ( AyXGx <= -0.6) {
																return 1;
															}
															else {
																if ( Ay_squared <= 0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Az_squared <= -0.11) {
									if ( AxXAz <= 0.04) {
										if ( AxXGz <= -0.01) {
											if ( Gx <= 0.5) {
												if ( Ay <= -0.68) {
													if ( AxXGz <= -0.03) {
														return 0;
													}
													else {
														if ( AzXGx <= -0.08) {
															return 1;
														}
														else {
															if ( AxXAy <= 0.03) {
																if ( AxXGz <= -0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( Ax_squared <= 0.38) {
														if ( GxXGy <= -0.01) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.02) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gx <= 0.61) {
											if ( AzXGy <= -0.11) {
												return 0;
											}
											else {
												if ( GxXGy <= 0.02) {
													if ( AyXGx <= -0.16) {
														if ( AxXGz <= -0.01) {
															if ( Ay <= -0.68) {
																if ( AxXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= -0.04) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy <= 0.1) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AxXGx <= -0.01) {
															if ( AzXGx <= -0.03) {
																if ( Gx <= 0.22) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Gx_squared <= -0.12) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXGx <= -0.18) {
														if ( Gx_squared <= -0.09) {
															if ( Gz_squared <= -0.13) {
																return 1;
															}
															else {
																if ( AxXGy <= -0.02) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AyXAz <= 0.23) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( AxXAy <= 0.28) {
										if ( Gx <= 0.55) {
											if ( AyXGy <= -0.02) {
												if ( AxXAz <= -0.07) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.02) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Az_squared <= 0.04) {
													if ( Ay <= -0.66) {
														if ( AxXGy <= -0.02) {
															return 0;
														}
														else {
															if ( Ay <= -0.7) {
																if ( AzXGz <= 0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Az <= -0.29) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Gy <= -0.27) {
															return 1;
														}
														else {
															if ( AxXGy <= 0.01) {
																if ( AzXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGz <= 0.03) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gz <= -0.19) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AxXGy <= 0.02) {
											if ( Az_squared <= -0.03) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											if ( AyXAz <= 0.73) {
												if ( AxXGz <= -0.0) {
													if ( AzXGz <= 0.02) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( AxXAy <= -0.81) {
							if ( Gz_squared <= -0.12) {
								if ( GxXGz <= 0.01) {
									if ( AzXGy <= -0.01) {
										if ( Ax <= 1.59) {
											if ( Az <= 0.5) {
												if ( AzXGx <= 0.09) {
													if ( GyXGz <= -0.01) {
														if ( Az_squared <= -0.19) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gx_squared <= -0.13) {
													return 2;
												}
												else {
													if ( Gx <= -0.37) {
														return 2;
													}
													else {
														if ( AxXGz <= 0.04) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AxXGx <= 0.08) {
												if ( AxXAz <= 0.09) {
													if ( AxXGz <= 0.09) {
														if ( Ay_squared <= -0.07) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Ay_squared <= 0.07) {
											if ( Gy <= -0.29) {
												return 0;
											}
											else {
												if ( AxXGz <= -0.14) {
													return 1;
												}
												else {
													if ( AyXGx <= 0.14) {
														if ( GxXGz <= 0.0) {
															if ( Gy_squared <= -0.14) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Az_squared <= -0.24) {
										if ( Gz <= -0.26) {
											if ( AyXGx <= 0.13) {
												return 2;
											}
											else {
												return 1;
											}
										}
										else {
											if ( GxXGz <= 0.01) {
												if ( AzXGy <= -0.01) {
													if ( AxXAy <= -1.01) {
														return 1;
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( GyXGz <= -0.03) {
													return 0;
												}
												else {
													if ( Gx <= -0.29) {
														return 2;
													}
													else {
														if ( AxXAz <= 0.11) {
															if ( Ax_squared <= 0.61) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( GyXGz <= -0.04) {
											return 0;
										}
										else {
											if ( AzXGz <= 0.09) {
												if ( AzXGy <= 0.06) {
													if ( Gx_squared <= -0.13) {
														return 2;
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( AxXGx <= 0.05) {
																if ( AzXGz <= 0.04) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
							else {
								if ( Gx <= 0.38) {
									if ( AxXAy <= -1.56) {
										return 0;
									}
									else {
										if ( AyXAz <= -0.19) {
											return 2;
										}
										else {
											if ( Gz <= -0.86) {
												return 0;
											}
											else {
												if ( AxXAy <= -1.42) {
													return 2;
												}
												else {
													if ( Gz_squared <= -0.08) {
														if ( GxXGz <= 0.02) {
															if ( Ay_squared <= 0.15) {
																if ( Gz <= 0.39) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( Az <= 0.4) {
								if ( Gx_squared <= -0.08) {
									if ( AyXGy <= 0.07) {
										if ( AyXAz <= 0.37) {
											if ( AzXGx <= 0.01) {
												if ( Ax_squared <= -0.12) {
													if ( AxXGx <= -0.0) {
														if ( Az_squared <= -0.19) {
															if ( GxXGz <= -0.0) {
																return 0;
															}
															else {
																if ( Ay_squared <= -0.04) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Gy <= 0.28) {
																if ( AyXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXGz <= -0.07) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AzXGy <= -0.07) {
															return 0;
														}
														else {
															if ( AxXGx <= 0.03) {
																if ( Gx <= 0.26) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( Gz_squared <= -0.13) {
														if ( Gy_squared <= -0.14) {
															if ( AzXGy <= -0.0) {
																if ( AxXGx <= 0.08) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( GxXGy <= 0.02) {
															if ( GxXGz <= -0.0) {
																return 0;
															}
															else {
																if ( AxXGx <= 0.02) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AzXGz <= 0.04) {
													if ( Ax <= -0.67) {
														if ( Gz <= -0.0) {
															if ( AyXAz <= 0.21) {
																if ( AzXGz <= 0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGy <= -0.03) {
																if ( Ay_squared <= -0.04) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= -0.15) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AzXGz <= -0.05) {
															if ( AxXGz <= 0.09) {
																if ( AxXAz <= 0.05) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gy <= 0.21) {
																if ( Ax_squared <= -0.14) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AzXGx <= 0.02) {
														if ( AxXGz <= -0.03) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gy_squared <= -0.15) {
															if ( AxXAy <= 0.54) {
																if ( AxXAy <= 0.14) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGx <= -0.0) {
																if ( AxXAy <= 0.04) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ax_squared <= -0.13) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AzXGy <= -0.15) {
												if ( Ax_squared <= -0.14) {
													if ( AxXGx <= -0.01) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Az <= -0.48) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AyXGz <= -0.05) {
													if ( AxXAy <= -0.03) {
														if ( Ay <= -0.64) {
															if ( AxXGx <= -0.11) {
																return 2;
															}
															else {
																if ( AzXGz <= -0.14) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGx <= 0.06) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Gx <= 0.01) {
															if ( AzXGy <= -0.08) {
																if ( AyXAz <= 0.57) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXAz <= 0.65) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= -0.01) {
																if ( Ay_squared <= 0.18) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AxXGz <= -0.03) {
														if ( Ay <= -0.66) {
															if ( AxXGy <= 0.06) {
																if ( Ax <= 0.74) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( GyXGz <= -0.04) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Ay <= -0.71) {
															if ( AyXGz <= 0.29) {
																if ( AxXGy <= 0.01) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Az <= -0.29) {
																if ( GxXGy <= 0.0) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= -0.04) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AxXGz <= 0.01) {
											if ( GxXGz <= 0.01) {
												if ( Az_squared <= -0.19) {
													if ( Gz <= 0.0) {
														if ( GyXGz <= -0.01) {
															if ( AxXAz <= 0.16) {
																if ( AyXGx <= -0.13) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( GxXGy <= 0.02) {
															if ( AxXGx <= -0.01) {
																return 2;
															}
															else {
																if ( AxXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXAz <= 0.19) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( Az <= -0.62) {
														if ( AyXGy <= 0.22) {
															if ( AzXGy <= 0.11) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXAz <= 0.44) {
															if ( AxXAy <= -0.37) {
																return 1;
															}
															else {
																if ( AxXGy <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXGy <= -0.0) {
																if ( AzXGz <= -0.04) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AzXGz <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AyXGz <= -0.02) {
													if ( AyXAz <= 0.36) {
														if ( Ay_squared <= -0.01) {
															return 2;
														}
														else {
															if ( Ay <= -0.76) {
																return 0;
															}
															else {
																if ( Gz <= 0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AzXGz <= -0.05) {
															if ( Az_squared <= 0.04) {
																if ( AxXGy <= -0.01) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gy <= -0.15) {
																if ( Ay <= -0.68) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= -0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AzXGz <= 0.07) {
														if ( AyXGz <= 0.15) {
															if ( AxXGx <= 0.0) {
																if ( AxXAy <= 0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAy <= -0.11) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Ay_squared <= 0.04) {
																return 2;
															}
															else {
																if ( AyXGz <= 0.23) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AxXAz <= 0.0) {
															if ( AzXGz <= 0.13) {
																if ( AxXGy <= -0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Ay <= -0.66) {
																if ( AyXAz <= 0.27) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
										else {
											if ( AzXGx <= 0.03) {
												if ( AxXAz <= -0.09) {
													if ( AzXGy <= 0.03) {
														return 2;
													}
													else {
														if ( AxXGz <= 0.01) {
															return 0;
														}
														else {
															if ( GxXGy <= 0.0) {
																return 2;
															}
															else {
																if ( AzXGy <= 0.06) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AxXAz <= 0.04) {
														if ( AzXGz <= -0.08) {
															return 1;
														}
														else {
															if ( Gz <= 0.16) {
																if ( AxXAz <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGz <= 0.06) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AxXAz <= -0.13) {
													if ( AzXGz <= -0.02) {
														if ( Ay <= -0.66) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGx <= 0.11) {
														if ( AyXGx <= 0.18) {
															if ( AxXGy <= 0.04) {
																if ( GxXGz <= -0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( AyXAz <= 0.45) {
										if ( Ay <= -0.68) {
											if ( AyXGz <= -0.3) {
												if ( GyXGz <= 0.0) {
													if ( AzXGz <= -0.07) {
														if ( AyXGz <= -0.43) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Ay <= -0.79) {
													return 0;
												}
												else {
													if ( Gz <= -0.81) {
														return 0;
													}
													else {
														if ( AxXGx <= -0.11) {
															if ( Gz <= 0.0) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AzXGx <= 0.13) {
																return 2;
															}
															else {
																if ( AzXGz <= 0.08) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( Gz_squared <= -0.12) {
												if ( GxXGz <= -0.01) {
													return 1;
												}
												else {
													if ( Gy <= 0.13) {
														if ( Gx <= -1.0) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														if ( Ax <= -0.22) {
															if ( GxXGy <= -0.07) {
																return 1;
															}
															else {
																if ( Ay <= -0.67) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AzXGx <= 0.23) {
																if ( AxXAz <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												if ( GxXGz <= -0.11) {
													return 2;
												}
												else {
													if ( GxXGz <= -0.03) {
														return 1;
													}
													else {
														if ( Gy <= -0.11) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( Gz <= 0.46) {
											if ( Gz_squared <= -0.06) {
												if ( AzXGx <= 0.32) {
													if ( AxXAz <= 0.09) {
														if ( Gz <= -0.08) {
															if ( AxXAz <= 0.0) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gz <= 0.41) {
														if ( AxXAz <= -0.04) {
															return 0;
														}
														else {
															if ( AxXGz <= -0.02) {
																return 0;
															}
															else {
																if ( Gx_squared <= 0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AyXGx <= 1.06) {
												if ( AyXAz <= 0.58) {
													return 2;
												}
												else {
													if ( Ay_squared <= 0.29) {
														if ( Gy_squared <= -0.14) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
							else {
								if ( GxXGy <= 0.02) {
									if ( GxXGz <= 0.01) {
										if ( Gz <= -0.08) {
											if ( AxXAy <= 0.54) {
												if ( Gz_squared <= -0.11) {
													if ( Gy_squared <= -0.15) {
														if ( AxXAy <= -0.5) {
															if ( Az_squared <= -0.26) {
																if ( Gx <= 0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gx_squared <= -0.13) {
																if ( AxXGz <= -0.03) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGx <= 0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Gy_squared <= -0.14) {
															if ( Ax_squared <= -0.09) {
																if ( AyXAz <= -0.21) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGx <= 0.03) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXAy <= -0.55) {
																if ( Gz <= -0.13) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy <= -0.17) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AxXAz <= 0.01) {
														return 1;
													}
													else {
														if ( AzXGy <= -0.02) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.04) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXGx <= -0.02) {
												if ( GxXGz <= -0.08) {
													if ( AxXAz <= 0.07) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AxXGz <= 0.01) {
														if ( Ay <= -0.67) {
															if ( Gz_squared <= -0.13) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGy <= -0.17) {
															return 0;
														}
														else {
															if ( GyXGz <= -0.01) {
																if ( Gy <= 0.23) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
											}
											else {
												if ( GxXGy <= 0.01) {
													if ( AxXGx <= 0.05) {
														if ( AxXAz <= 0.09) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gz <= 0.04) {
														if ( AzXGz <= 0.02) {
															if ( AxXGy <= 0.06) {
																if ( AzXGy <= -0.0) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AyXGz <= 0.02) {
																if ( AxXAy <= 0.14) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Gz_squared <= -0.13) {
															if ( Gy_squared <= -0.15) {
																if ( Gx_squared <= -0.13) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AyXGz <= -0.24) {
																return 0;
															}
															else {
																if ( Gx <= -0.19) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AxXAy <= -0.12) {
											if ( Gz <= -0.28) {
												if ( AyXGz <= 0.19) {
													if ( AxXGy <= 0.01) {
														if ( GxXGy <= 0.02) {
															if ( GxXGz <= 0.02) {
																if ( AyXGx <= 0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( GyXGz <= -0.01) {
														if ( AyXGy <= -0.21) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.26) {
																if ( Az_squared <= -0.26) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AyXGz <= -0.16) {
													return 0;
												}
												else {
													if ( GxXGy <= 0.01) {
														if ( AzXGy <= -0.04) {
															return 0;
														}
														else {
															if ( AzXGz <= 0.03) {
																if ( AxXGx <= 0.16) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGz <= 0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( Gz_squared <= -0.1) {
												if ( AxXGz <= 0.03) {
													if ( GxXGy <= 0.01) {
														if ( AxXGy <= 0.1) {
															if ( Ay_squared <= 0.26) {
																if ( Gx <= -0.71) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGz <= 0.16) {
															if ( AzXGx <= 0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( GxXGz <= 0.01) {
										if ( Gx <= 0.06) {
											if ( AxXAy <= -0.7) {
												return 0;
											}
											else {
												if ( AxXGx <= 0.04) {
													if ( AyXAz <= -0.28) {
														return 0;
													}
													else {
														if ( AyXAz <= 0.03) {
															if ( AyXGz <= -0.04) {
																if ( AyXGy <= 0.2) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AyXAz <= -0.12) {
												return 0;
											}
											else {
												if ( GxXGz <= -0.01) {
													return 0;
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Gx <= -0.53) {
											if ( GxXGz <= 0.12) {
												if ( AxXAz <= 0.04) {
													return 2;
												}
												else {
													if ( AyXGx <= 0.27) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AyXGz <= -0.11) {
												return 0;
											}
											else {
												if ( AxXGz <= -0.1) {
													if ( Ax_squared <= 0.15) {
														if ( Gy_squared <= -0.13) {
															if ( AzXGx <= 0.04) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXAz <= -0.16) {
														if ( AxXAy <= -0.46) {
															return 1;
														}
														else {
															if ( AxXGx <= -0.06) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AyXGy <= 0.22) {
															if ( AyXAz <= -0.02) {
																if ( Gy <= -0.24) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gz_squared <= -0.13) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Gz <= -2.05) {
						if ( AyXAz <= 0.34) {
							if ( Gx_squared <= 0.01) {
								if ( Gz <= -2.38) {
									if ( GxXGy <= 0.02) {
										return 0;
									}
									else {
										if ( AyXGz <= 1.8) {
											if ( AzXGx <= 0.13) {
												if ( AxXGx <= -0.17) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.2) {
														if ( AzXGx <= 0.1) {
															if ( AyXGx <= 0.35) {
																if ( GxXGy <= 0.07) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gz_squared <= 1.06) {
													return 1;
												}
												else {
													if ( Gz_squared <= 1.19) {
														if ( Gx_squared <= -0.07) {
															return 1;
														}
														else {
															if ( Gy <= -2.98) {
																return 1;
															}
															else {
																if ( GyXGz <= 1.73) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gy <= -2.57) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AyXAz <= 0.2) {
										if ( Ay <= -0.71) {
											return 1;
										}
										else {
											if ( AyXGz <= 1.21) {
												if ( GxXGy <= 0.09) {
													return 1;
												}
												else {
													if ( Ay <= -0.64) {
														if ( Gz_squared <= 0.39) {
															return 1;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Ax_squared <= -0.03) {
													if ( AzXGx <= 0.0) {
														if ( GyXGz <= -0.57) {
															return 1;
														}
														else {
															if ( GxXGz <= -0.22) {
																if ( Ay_squared <= 0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GyXGz <= -0.51) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								if ( AzXGy <= 0.39) {
									if ( Gx_squared <= 0.18) {
										if ( GxXGy <= 0.2) {
											return 0;
										}
										else {
											if ( AyXAz <= 0.22) {
												if ( Gx <= 1.16) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AxXAy <= 0.49) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( AxXAz <= 0.01) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( Gy <= -2.3) {
								if ( AzXGy <= 0.78) {
									if ( Ay_squared <= -0.04) {
										return 1;
									}
									else {
										return 1;
									}
								}
								else {
									if ( Ay_squared <= 4.4) {
										if ( AzXGz <= 1.61) {
											if ( AzXGy <= 0.95) {
												return 1;
											}
											else {
												if ( Gx <= 1.7) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXAz <= -0.01) {
												return 0;
											}
											else {
												if ( GxXGz <= -1.32) {
													return 1;
												}
												else {
													if ( AzXGx <= -0.45) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AzXGz <= 1.74) {
									if ( AxXAz <= 0.63) {
										if ( AyXGx <= 0.38) {
											if ( Gz_squared <= 2.31) {
												if ( AyXGz <= 1.9) {
													if ( AyXAz <= 0.41) {
														return 0;
													}
													else {
														if ( AxXGy <= 0.13) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 1;
									}
								}
								else {
									if ( Gz_squared <= 0.7) {
										return 1;
									}
									else {
										if ( AxXGx <= -1.35) {
											return 0;
										}
										else {
											if ( AxXGz <= -0.31) {
												return 2;
											}
											else {
												if ( AyXGx <= 1.82) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Ax_squared <= -0.12) {
							if ( AyXGy <= 0.54) {
								if ( AzXGy <= -0.15) {
									if ( Gx_squared <= -0.1) {
										if ( Az <= -0.4) {
											if ( AyXGz <= 0.43) {
												if ( Ax <= -0.33) {
													if ( AyXGy <= -0.91) {
														return 0;
													}
													else {
														if ( Gx_squared <= -0.13) {
															return 1;
														}
														else {
															if ( Az <= -0.77) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Ay <= -0.71) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.01) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( GyXGz <= -0.01) {
												if ( AyXGy <= -0.71) {
													return 0;
												}
												else {
													if ( Gy <= 0.79) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXGy <= 0.11) {
													if ( Gx_squared <= -0.13) {
														return 1;
													}
													else {
														if ( Gz <= -0.0) {
															return 1;
														}
														else {
															if ( Gz <= 0.02) {
																return 0;
															}
															else {
																if ( Gz_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( Gz <= 0.17) {
											if ( GxXGy <= -0.13) {
												if ( Gx_squared <= 0.3) {
													if ( Gx_squared <= 0.01) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AyXGx <= 0.31) {
													if ( Gz_squared <= 0.11) {
														if ( Gz <= -0.03) {
															if ( Gy <= 0.61) {
																return 1;
															}
															else {
																if ( AyXAz <= 0.94) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXAy <= 0.21) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AyXGy <= -0.64) {
												if ( AzXGx <= -0.25) {
													return 0;
												}
												else {
													if ( AzXGx <= -0.21) {
														return 1;
													}
													else {
														if ( Gx <= -0.7) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AyXGx <= -0.85) {
													return 2;
												}
												else {
													if ( AyXAz <= 0.28) {
														return 2;
													}
													else {
														if ( Gz_squared <= -0.07) {
															if ( GxXGy <= 0.16) {
																if ( AyXAz <= 0.35) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( Gz <= 0.61) {
										if ( AzXGx <= -0.02) {
											if ( GxXGy <= -0.18) {
												if ( Gz <= 0.06) {
													if ( Gz <= -0.87) {
														if ( AyXGz <= 0.58) {
															if ( AyXGx <= -0.88) {
																return 1;
															}
															else {
																if ( AyXGy <= 0.35) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AyXAz <= 0.66) {
													if ( Az_squared <= -0.09) {
														if ( AzXGx <= -0.23) {
															if ( Ay <= -0.68) {
																return 1;
															}
															else {
																if ( AxXAz <= 0.06) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( GxXGz <= -0.1) {
																if ( AyXGz <= 0.5) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGz <= 0.25) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AxXAz <= 0.02) {
															return 2;
														}
														else {
															if ( Gx_squared <= -0.07) {
																if ( Gz <= -0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( GxXGy <= -0.01) {
														if ( AxXGy <= 0.01) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AyXAz <= -0.1) {
												if ( Gy_squared <= 0.07) {
													if ( Gz_squared <= -0.12) {
														if ( GxXGy <= 0.01) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGz <= -0.21) {
															return 2;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gz <= -0.51) {
													if ( GyXGz <= -0.33) {
														return 1;
													}
													else {
														if ( AxXGx <= -0.05) {
															return 2;
														}
														else {
															if ( AzXGy <= 0.13) {
																if ( AzXGx <= 0.08) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( Ay_squared <= 0.29) {
														if ( Az_squared <= 0.09) {
															if ( Az <= -0.26) {
																if ( AxXAy <= 0.11) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= -0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Az_squared <= 0.18) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AzXGz <= 0.03) {
															if ( AyXAz <= 0.2) {
																return 2;
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( GxXGy <= -0.08) {
											if ( Gy_squared <= -0.04) {
												if ( AzXGz <= -0.1) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								if ( Az <= 0.07) {
									if ( Gx_squared <= -0.12) {
										if ( AxXGz <= 0.01) {
											if ( Gy <= -1.33) {
												return 0;
											}
											else {
												if ( AxXGx <= 0.01) {
													if ( AzXGy <= 0.37) {
														if ( AzXGx <= 0.07) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXGy <= 1.11) {
											if ( GxXGz <= -0.0) {
												if ( AzXGy <= 0.29) {
													return 1;
												}
												else {
													if ( Az <= -0.73) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AzXGz <= 0.35) {
													if ( AzXGy <= 0.22) {
														return 0;
													}
													else {
														if ( AxXAz <= 0.06) {
															if ( Az_squared <= 0.07) {
																if ( Gx <= -0.64) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gz_squared <= -0.12) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AzXGx <= -0.77) {
												return 1;
											}
											else {
												if ( AzXGz <= -0.05) {
													return 0;
												}
												else {
													if ( AxXGz <= -0.07) {
														return 0;
													}
													else {
														if ( Ay_squared <= 0.01) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AyXGz <= -0.0) {
										if ( AzXGy <= 0.03) {
											return 2;
										}
										else {
											if ( AxXGz <= -0.01) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gx_squared <= 0.03) {
											if ( GyXGz <= 0.0) {
												return 0;
											}
											else {
												if ( AxXGx <= -0.0) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
							}
						}
						else {
							if ( AyXGz <= 0.15) {
								if ( AxXAy <= -0.69) {
									if ( Ay_squared <= 0.15) {
										if ( AyXGy <= 0.71) {
											if ( GyXGz <= -0.1) {
												if ( GxXGz <= -0.01) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												if ( AxXAz <= -0.17) {
													if ( AxXGz <= 0.04) {
														if ( AyXGy <= 0.3) {
															if ( Gx_squared <= -0.1) {
																if ( AyXAz <= 0.38) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGz <= -0.04) {
															if ( Gy <= 1.58) {
																if ( AxXAz <= -0.26) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Ax <= 2.05) {
														if ( Gy <= 0.58) {
															if ( AxXGy <= -0.3) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGy <= 0.46) {
																if ( AxXAy <= -0.81) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( Gx_squared <= 0.06) {
												if ( AzXGx <= 0.01) {
													if ( AzXGy <= 0.1) {
														return 1;
													}
													else {
														if ( AxXAz <= -0.23) {
															if ( AyXGy <= 1.07) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Az_squared <= -0.18) {
																if ( AxXGy <= -0.61) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( GxXGy <= -0.01) {
											if ( Gz <= 0.53) {
												if ( Gz <= 0.28) {
													if ( GxXGy <= -0.07) {
														if ( AyXGy <= 1.15) {
															if ( AzXGz <= -0.04) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AxXGz <= 0.06) {
												return 0;
											}
											else {
												if ( Ax <= 1.65) {
													if ( Ay_squared <= 0.73) {
														if ( AyXAz <= 0.36) {
															return 2;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
								else {
									if ( AzXGy <= -0.08) {
										if ( Gy_squared <= 0.16) {
											if ( AxXGz <= 0.01) {
												if ( AzXGx <= 0.61) {
													if ( GxXGy <= -0.22) {
														return 0;
													}
													else {
														if ( AzXGx <= 0.09) {
															if ( AzXGx <= 0.06) {
																if ( Gz_squared <= -0.13) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXAz <= 0.65) {
																if ( AxXAz <= -0.11) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXGz <= -0.4) {
													return 2;
												}
												else {
													if ( Ay <= -0.67) {
														if ( AzXGx <= 0.3) {
															if ( AzXGy <= -0.15) {
																if ( AyXGz <= -0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AxXGz <= 0.16) {
															if ( GxXGy <= -0.14) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.65) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											if ( AzXGy <= -0.6) {
												if ( Gy <= 1.97) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gx_squared <= -0.11) {
													return 0;
												}
												else {
													if ( Gx_squared <= -0.06) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( AyXGy <= 1.13) {
											if ( AzXGz <= -0.13) {
												if ( GxXGy <= -0.01) {
													return 0;
												}
												else {
													if ( AyXGz <= -0.4) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( GxXGz <= 0.01) {
													if ( AxXGz <= 0.13) {
														if ( AxXGx <= 0.07) {
															if ( Gy_squared <= -0.09) {
																if ( AxXAz <= -0.12) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ax <= 0.63) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Gy <= -1.29) {
																return 2;
															}
															else {
																if ( GxXGy <= -0.17) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AyXGx <= -0.54) {
														if ( AyXGx <= -0.62) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGx <= -0.24) {
															return 2;
														}
														else {
															if ( Az_squared <= 0.09) {
																if ( AyXGx <= -0.35) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
										else {
											if ( Gx_squared <= -0.12) {
												return 2;
											}
											else {
												if ( Ay_squared <= 0.04) {
													return 0;
												}
												else {
													if ( AxXGz <= -0.01) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Gy <= -0.66) {
									if ( AyXAz <= 1.04) {
										if ( AzXGy <= 0.69) {
											if ( AyXGz <= 0.64) {
												if ( GxXGy <= -0.9) {
													return 0;
												}
												else {
													if ( AzXGx <= -0.03) {
														if ( AzXGy <= 0.1) {
															return 0;
														}
														else {
															if ( AyXAz <= 0.11) {
																return 0;
															}
															else {
																if ( AxXGy <= -0.56) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Gx <= -0.63) {
															return 0;
														}
														else {
															if ( AzXGz <= 0.16) {
																if ( AxXGy <= -0.31) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
											}
											else {
												if ( AxXGy <= 0.33) {
													if ( AyXGx <= 0.52) {
														if ( Az_squared <= -0.26) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.7) {
																return 0;
															}
															else {
																if ( Gz_squared <= 0.08) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AzXGy <= 0.73) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gx_squared <= -0.01) {
											return 0;
										}
										else {
											if ( Ay <= -0.8) {
												return 0;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Ay <= -0.64) {
										if ( AzXGz <= 0.27) {
											if ( Gz <= -1.77) {
												return 1;
											}
											else {
												if ( AxXAz <= 0.27) {
													if ( AyXGx <= 0.05) {
														if ( Ax_squared <= -0.09) {
															if ( GxXGy <= -0.04) {
																return 1;
															}
															else {
																if ( AxXAz <= -0.07) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXGx <= -0.16) {
																if ( AxXAz <= -0.21) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXGz <= -0.26) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( GxXGy <= 0.05) {
															if ( AzXGz <= 0.01) {
																return 2;
															}
															else {
																if ( AxXGz <= 0.06) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXGz <= -0.16) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AxXGz <= 0.79) {
												if ( GyXGz <= -0.25) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( GxXGz <= -0.12) {
											return 1;
										}
										else {
											if ( AzXGz <= 0.09) {
												if ( AzXGy <= -0.02) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gx_squared <= -0.11) {
													if ( Az <= -0.44) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else {
				if ( Gz_squared <= -0.1) {
					if ( Az_squared <= -0.09) {
						if ( Ay <= 1.34) {
							if ( AxXAy <= -0.77) {
								if ( Gx_squared <= -0.13) {
									if ( AxXAy <= -1.54) {
										if ( Az_squared <= -0.19) {
											if ( Ay <= -0.32) {
												if ( AxXGz <= 0.08) {
													return 1;
												}
												else {
													if ( AxXAz <= -0.39) {
														return 2;
													}
													else {
														if ( AxXGz <= 0.27) {
															if ( GxXGy <= 0.01) {
																return 2;
															}
															else {
																if ( AxXGz <= 0.25) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Ax <= 4.03) {
											if ( Gz_squared <= -0.13) {
												if ( AxXAz <= -0.53) {
													if ( Az <= -0.08) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AxXAz <= -0.22) {
														return 1;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAz <= -0.23) {
													if ( AxXGz <= 0.12) {
														if ( Ax <= 2.78) {
															if ( GyXGz <= -0.02) {
																if ( Ax <= 1.76) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Ay <= -0.57) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXGy <= 0.06) {
														if ( AyXGy <= -0.09) {
															if ( AyXGy <= -0.3) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXGz <= 0.02) {
																if ( AxXAy <= -1.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGy <= 0.41) {
															if ( Gz <= 0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( Az <= 0.47) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AyXGx <= 0.05) {
										if ( AxXGx <= -0.15) {
											return 1;
										}
										else {
											if ( Gz_squared <= -0.12) {
												if ( AxXAz <= -0.05) {
													if ( AxXAz <= -0.5) {
														if ( GxXGz <= -0.01) {
															return 2;
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( AxXAy <= -0.95) {
																if ( AyXGx <= -0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXGy <= 0.22) {
																if ( GxXGz <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AxXAy <= -1.08) {
														if ( Gy_squared <= -0.14) {
															if ( AxXGx <= 0.15) {
																return 2;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gy_squared <= -0.15) {
															return 2;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AxXAz <= -0.54) {
													return 2;
												}
												else {
													if ( Ay <= -0.51) {
														if ( GyXGz <= -0.01) {
															if ( GyXGz <= -0.04) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gy_squared <= -0.12) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( GxXGz <= 0.01) {
											if ( GxXGy <= -0.03) {
												if ( AxXAz <= -0.44) {
													return 0;
												}
												else {
													if ( AzXGx <= 0.04) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AxXAz <= -0.29) {
													if ( GxXGy <= 0.01) {
														if ( AxXAy <= -1.39) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AzXGz <= 0.02) {
														if ( AzXGx <= 0.05) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( Gy_squared <= -0.15) {
												if ( AxXAz <= -0.23) {
													return 1;
												}
												else {
													return 2;
												}
											}
											else {
												if ( AzXGy <= -0.01) {
													if ( AzXGy <= -0.09) {
														return 0;
													}
													else {
														if ( Ax_squared <= 0.91) {
															if ( GyXGz <= -0.03) {
																return 2;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
							else {
								if ( Ay <= -0.57) {
									if ( Az_squared <= -0.23) {
										if ( AzXGx <= -0.02) {
											return 0;
										}
										else {
											if ( Gy_squared <= -0.09) {
												if ( AzXGz <= -0.0) {
													return 0;
												}
												else {
													if ( AxXAy <= 0.08) {
														if ( GxXGz <= -0.01) {
															return 0;
														}
														else {
															if ( AxXAz <= -0.04) {
																return 0;
															}
															else {
																if ( AzXGx <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AxXGx <= -0.01) {
															return 2;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( Ay_squared <= -0.19) {
													return 0;
												}
												else {
													if ( Ax_squared <= 0.09) {
														if ( AxXAy <= 0.05) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( AzXGx <= 0.17) {
											if ( GyXGz <= -0.01) {
												if ( AzXGx <= -0.11) {
													if ( Gx <= 0.98) {
														if ( AxXGx <= 0.16) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXAz <= -0.2) {
														if ( Gx_squared <= -0.11) {
															if ( Gx <= -0.18) {
																return 1;
															}
															else {
																if ( Gx <= 0.25) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Ax_squared <= -0.13) {
															if ( AzXGx <= 0.14) {
																if ( AyXAz <= 0.32) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXGx <= -0.03) {
																if ( AzXGy <= -0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAy <= -0.68) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGx <= -0.07) {
													if ( AyXGz <= 0.23) {
														if ( AxXGy <= 0.04) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gy_squared <= -0.09) {
														if ( GxXGz <= 0.03) {
															if ( AyXGy <= -0.21) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.35) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGx <= -0.0) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( Gy_squared <= -0.11) {
												if ( GxXGz <= -0.02) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.32) {
														return 1;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AxXAy <= 0.2) {
										if ( AyXAz <= -0.56) {
											return 2;
										}
										else {
											if ( Az_squared <= -0.22) {
												if ( Gy_squared <= -0.0) {
													if ( Ay <= -0.49) {
														if ( GxXGz <= -0.0) {
															return 0;
														}
														else {
															if ( Gy <= 0.42) {
																if ( Az_squared <= -0.26) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AxXAz <= 0.1) {
															if ( AzXGz <= -0.0) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( Gx <= -0.65) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AxXAz <= 0.02) {
													if ( AzXGy <= -0.38) {
														return 2;
													}
													else {
														if ( GxXGy <= 0.04) {
															if ( AzXGy <= -0.14) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.13) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXGx <= -0.18) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXGz <= -0.11) {
														return 1;
													}
													else {
														if ( AxXAz <= 0.03) {
															return 1;
														}
														else {
															if ( GyXGz <= -0.02) {
																return 0;
															}
															else {
																if ( AxXAz <= 0.09) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Ay <= -0.2) {
											if ( AxXGx <= 0.02) {
												if ( AxXGy <= -0.13) {
													return 2;
												}
												else {
													if ( AxXAz <= 0.08) {
														return 0;
													}
													else {
														if ( GyXGz <= -0.04) {
															return 0;
														}
														else {
															if ( Gx_squared <= -0.13) {
																return 0;
															}
															else {
																if ( Ay_squared <= -0.35) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Ay_squared <= -0.46) {
												if ( AyXAz <= -0.39) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
						else {
							if ( Gy_squared <= -0.03) {
								if ( GxXGy <= 0.01) {
									if ( AxXGy <= -0.03) {
										if ( Ax <= -0.1) {
											if ( Az_squared <= -0.17) {
												if ( Ay_squared <= -0.14) {
													return 1;
												}
												else {
													if ( GxXGy <= -0.03) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Ay_squared <= 0.04) {
												if ( AzXGy <= 0.02) {
													if ( AxXAy <= 0.57) {
														return 1;
													}
													else {
														if ( AyXAz <= -0.03) {
															if ( AzXGy <= 0.0) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AxXAy <= 0.88) {
														if ( AzXGy <= 0.09) {
															if ( AyXAz <= -0.61) {
																if ( AyXGy <= -0.22) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAz <= 0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GyXGz <= 0.01) {
													if ( Az <= -0.04) {
														return 0;
													}
													else {
														if ( AyXAz <= -0.35) {
															if ( AxXAz <= -0.06) {
																return 1;
															}
															else {
																if ( AzXGy <= 0.09) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( Gy_squared <= -0.13) {
											if ( AyXAz <= -0.22) {
												if ( Ay_squared <= 0.07) {
													if ( Ay <= 1.51) {
														if ( Ax_squared <= -0.12) {
															if ( AzXGx <= -0.01) {
																if ( Gz_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXAz <= 0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXGz <= -0.11) {
																return 0;
															}
															else {
																if ( AzXGx <= -0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( Gz <= 0.02) {
																if ( AxXGz <= -0.0) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy_squared <= -0.14) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gz <= -0.18) {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXGx <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AzXGx <= -0.02) {
														if ( GyXGz <= -0.02) {
															if ( AxXAz <= -0.02) {
																return 0;
															}
															else {
																if ( AxXGy <= 0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Az <= 0.14) {
															if ( Ax_squared <= -0.15) {
																return 1;
															}
															else {
																if ( AyXGx <= -0.26) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gz_squared <= -0.13) {
																if ( AzXGx <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGy <= -0.02) {
													if ( Ay <= 1.52) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( GxXGy <= -0.0) {
														return 0;
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( Gx <= 0.15) {
																if ( AxXGy <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGx <= 0.01) {
																if ( AyXAz <= -0.21) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( AyXGx <= 0.09) {
												if ( AyXGy <= -0.32) {
													if ( AzXGz <= -0.04) {
														return 0;
													}
													else {
														if ( Az <= -0.0) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.01) {
																if ( AxXGy <= 0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( GyXGz <= -0.03) {
														if ( AzXGz <= -0.04) {
															return 1;
														}
														else {
															if ( Ay <= 1.55) {
																if ( Ay_squared <= -0.01) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( GxXGy <= -0.09) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.07) {
																if ( AxXGy <= 0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= -0.15) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.06) {
													if ( GxXGy <= -0.05) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXGx <= -0.1) {
														return 0;
													}
													else {
														if ( AyXAz <= -0.12) {
															if ( AxXGz <= -0.0) {
																if ( AyXGy <= -0.22) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AxXAy <= 0.54) {
										if ( Gy_squared <= -0.11) {
											if ( Az <= -0.15) {
												if ( Ax_squared <= -0.15) {
													if ( Gz <= -0.14) {
														if ( GxXGz <= 0.01) {
															if ( AzXGy <= -0.08) {
																return 1;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( Gz <= 0.12) {
																return 2;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGx <= 0.21) {
																if ( Gy_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXGx <= 0.22) {
														if ( Gz_squared <= -0.12) {
															if ( AzXGz <= -0.03) {
																if ( AxXGx <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GyXGz <= -0.03) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GyXGz <= -0.02) {
													if ( AxXAz <= 0.08) {
														if ( AyXGz <= 0.22) {
															if ( AzXGz <= 0.02) {
																if ( Gz <= -0.07) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXAz <= 0.02) {
																if ( GyXGz <= -0.05) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAz <= 0.07) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Gz <= -0.02) {
															if ( AzXGy <= 0.0) {
																if ( AxXGx <= 0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GxXGy <= 0.01) {
																if ( AzXGz <= -0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXAy <= -0.15) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AzXGz <= -0.0) {
														if ( Gy_squared <= -0.13) {
															if ( AyXGx <= 0.2) {
																if ( AyXGy <= 0.1) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGx <= -0.08) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXGx <= 0.28) {
																if ( AxXAz <= 0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXGx <= -0.4) {
															return 0;
														}
														else {
															if ( Az <= -0.04) {
																if ( GxXGz <= 0.01) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( Gz <= 0.02) {
												if ( AzXGx <= -0.04) {
													if ( Gz_squared <= -0.13) {
														if ( Az <= 0.07) {
															if ( AxXGz <= -0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AzXGx <= -0.05) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXGy <= 0.34) {
														if ( AyXGx <= -0.25) {
															if ( AyXGy <= -0.38) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXAz <= -0.7) {
																return 0;
															}
															else {
																if ( AxXAy <= 0.23) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AxXGz <= -0.02) {
															if ( Gx_squared <= -0.13) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXAz <= -0.43) {
																return 1;
															}
															else {
																if ( Gx <= 0.51) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gx_squared <= -0.04) {
													if ( AxXAz <= 0.02) {
														if ( AxXGy <= -0.09) {
															return 1;
														}
														else {
															if ( AzXGx <= 0.06) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( GyXGz <= -0.07) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.06) {
																return 1;
															}
															else {
																if ( AyXGy <= -0.41) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( AxXGy <= -0.09) {
											if ( AxXGz <= 0.11) {
												if ( Gz <= -0.49) {
													return 0;
												}
												else {
													if ( GxXGy <= 0.02) {
														return 0;
													}
													else {
														if ( Gx <= -0.76) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.18) {
																if ( Az <= 0.11) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXAz <= -0.53) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gx <= -0.08) {
												if ( AxXGz <= -0.03) {
													if ( Gx <= -0.71) {
														return 0;
													}
													else {
														if ( AzXGy <= 0.02) {
															if ( Gx <= -0.33) {
																return 1;
															}
															else {
																if ( AyXGz <= -0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AyXAz <= -0.37) {
														if ( AxXGy <= -0.03) {
															if ( AxXGy <= -0.09) {
																return 1;
															}
															else {
																if ( AyXGx <= -0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GxXGz <= -0.01) {
																return 1;
															}
															else {
																if ( Gz <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Gx <= -0.2) {
															if ( AxXAy <= 0.74) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( GyXGz <= -0.03) {
													if ( Ax <= 1.08) {
														if ( Gy <= -0.14) {
															return 0;
														}
														else {
															if ( GyXGz <= -0.06) {
																return 0;
															}
															else {
																if ( Gx <= 1.27) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( GxXGz <= 0.07) {
														if ( Gy <= -0.03) {
															if ( AyXAz <= -0.65) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGy <= -0.15) {
																if ( AyXAz <= -0.61) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy <= 0.38) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Gx_squared <= -0.1) {
									if ( Gz <= 0.16) {
										if ( AxXAz <= 0.0) {
											if ( AzXGy <= -0.2) {
												return 0;
											}
											else {
												if ( Gz <= -0.01) {
													return 0;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Gy <= 1.07) {
												if ( Gy <= -1.08) {
													return 0;
												}
												else {
													if ( AyXGz <= -0.04) {
														return 0;
													}
													else {
														if ( GxXGz <= -0.0) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.0) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AzXGy <= 0.08) {
											return 0;
										}
										else {
											if ( Gx <= -0.31) {
												if ( AxXAz <= 0.01) {
													return 0;
												}
												else {
													if ( Gy <= -1.08) {
														return 2;
													}
													else {
														if ( Gy <= -0.97) {
															if ( AzXGy <= 0.21) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( GyXGz <= 0.08) {
										if ( Az_squared <= -0.17) {
											if ( AxXGy <= 0.29) {
												if ( AxXGx <= 0.04) {
													if ( AzXGx <= 0.22) {
														if ( GxXGy <= 0.15) {
															return 1;
														}
														else {
															if ( AyXGx <= 0.53) {
																if ( AyXAz <= -0.54) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Ay_squared <= 0.32) {
														if ( AxXGy <= 0.23) {
															if ( AxXGx <= 0.07) {
																return 1;
															}
															else {
																if ( Gy <= 1.27) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Ay <= 1.45) {
												return 0;
											}
											else {
												if ( GxXGy <= 0.77) {
													if ( Gy_squared <= 0.05) {
														if ( AxXGy <= -0.15) {
															return 1;
														}
														else {
															if ( Az_squared <= -0.12) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXAz <= -0.67) {
															if ( AyXAz <= -0.7) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Gx <= 1.63) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
							}
						}
					}
					else {
						if ( AxXAz <= 0.04) {
							if ( AxXAy <= 0.27) {
								if ( AyXGz <= 0.04) {
									if ( Gx <= 0.05) {
										if ( Ax <= 1.88) {
											if ( Ay <= -0.55) {
												if ( AyXGx <= 0.0) {
													if ( AxXGy <= -0.03) {
														return 0;
													}
													else {
														if ( Gy_squared <= -0.15) {
															if ( Gy <= 0.08) {
																return 1;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AyXAz <= 0.87) {
																if ( AxXGz <= 0.06) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.24) {
														if ( AzXGy <= -0.44) {
															return 0;
														}
														else {
															if ( AxXAz <= -0.08) {
																if ( AzXGx <= 0.1) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGx <= 0.19) {
															if ( GxXGy <= 0.01) {
																if ( AxXAy <= -0.66) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= -0.12) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Gz_squared <= -0.12) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												if ( GxXGy <= 0.01) {
													if ( AzXGy <= -0.52) {
														if ( AyXGy <= -0.32) {
															if ( AxXGx <= -0.17) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGy <= -0.2) {
															if ( AyXAz <= 1.03) {
																if ( AxXAz <= -0.75) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Az_squared <= 0.72) {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay_squared <= -0.68) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AxXGy <= -0.01) {
														if ( AyXAz <= 0.79) {
															if ( Gy <= 0.03) {
																if ( Gx <= -0.46) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXAz <= -0.65) {
																if ( AyXGx <= 0.03) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= 0.18) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Az_squared <= 0.61) {
															if ( AxXAy <= 0.26) {
																if ( AxXGx <= 0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Gx_squared <= -0.13) {
																if ( AyXAz <= 0.92) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= -0.07) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGy <= -0.05) {
												if ( Az <= -1.09) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.01) {
														if ( AxXGy <= -0.24) {
															return 0;
														}
														else {
															if ( AxXGz <= 0.15) {
																return 0;
															}
															else {
																if ( Ax <= 3.86) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AzXGx <= 0.16) {
													if ( Ax_squared <= 0.72) {
														if ( GxXGy <= 0.01) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGy <= -0.28) {
															return 0;
														}
														else {
															if ( AzXGx <= 0.06) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( GxXGy <= 0.02) {
											if ( GxXGy <= -0.26) {
												if ( GxXGz <= 0.04) {
													if ( Gy <= -1.47) {
														if ( Gx_squared <= -0.03) {
															return 1;
														}
														else {
															if ( AyXGy <= 0.92) {
																if ( AxXGx <= 0.51) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Gx_squared <= 0.01) {
															if ( Gx <= 0.87) {
																if ( Gz_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAz <= -0.07) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( Gx_squared <= 0.08) {
														if ( AyXGz <= -0.09) {
															if ( Gy <= -1.6) {
																return 1;
															}
															else {
																if ( AyXAz <= 0.89) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAz <= -0.47) {
																return 2;
															}
															else {
																if ( AyXGz <= -0.03) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Gy <= 0.03) {
													if ( Ax <= 2.44) {
														if ( Az_squared <= 1.03) {
															if ( AyXGz <= -0.03) {
																if ( Gy_squared <= -0.14) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= 0.68) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAz <= -0.57) {
														if ( Gz_squared <= -0.13) {
															if ( AzXGy <= -0.01) {
																if ( AyXGy <= -0.06) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Ax <= 2.1) {
																if ( AxXAy <= -0.56) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGz <= 0.02) {
															if ( GxXGz <= 0.01) {
																return 2;
															}
															else {
																if ( AzXGy <= -0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( AxXGz <= -0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gy <= 0.17) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AyXAz <= 0.51) {
												if ( GxXGy <= 0.11) {
													if ( AxXGy <= 0.03) {
														return 2;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gz <= 0.15) {
													if ( AxXGx <= 0.14) {
														if ( GxXGy <= 0.02) {
															if ( Ay_squared <= -0.54) {
																return 0;
															}
															else {
																if ( AxXGx <= 0.07) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AzXGy <= -0.77) {
																return 2;
															}
															else {
																if ( AxXGx <= 0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXGx <= -0.25) {
														return 1;
													}
													else {
														if ( AxXAz <= -0.16) {
															if ( AzXGy <= -0.5) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AzXGx <= -0.06) {
										if ( AxXGy <= -0.19) {
											if ( GyXGz <= 0.01) {
												if ( AyXGy <= 0.7) {
													if ( AyXGy <= 0.21) {
														if ( Ay <= -0.26) {
															if ( Ay_squared <= -0.38) {
																if ( GxXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gy_squared <= -0.12) {
															return 1;
														}
														else {
															if ( Ay <= -0.52) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( Gx <= 1.14) {
														if ( AzXGx <= -0.25) {
															if ( Gx <= 1.04) {
																if ( Gy_squared <= 0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gx <= 0.44) {
													return 0;
												}
												else {
													if ( GxXGz <= -0.02) {
														if ( AxXAz <= -0.37) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( AyXGz <= 0.12) {
												if ( Gx_squared <= -0.05) {
													if ( AxXAy <= -0.78) {
														if ( Gy_squared <= -0.15) {
															if ( AxXAz <= -0.72) {
																return 1;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXAz <= -0.73) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXAz <= -0.23) {
															if ( AxXAy <= -0.06) {
																if ( Gy_squared <= -0.15) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Az_squared <= 0.15) {
																if ( AyXGy <= 0.04) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= -0.14) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AzXGy <= 0.58) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AyXGy <= 0.1) {
													if ( AzXGy <= -0.45) {
														if ( Az_squared <= 0.66) {
															if ( Ay <= -0.51) {
																if ( Ax_squared <= -0.09) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGx <= -0.2) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy <= 0.92) {
																return 0;
															}
															else {
																if ( AxXGz <= -0.04) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Az_squared <= 0.01) {
															if ( AyXGz <= 0.23) {
																if ( AzXGy <= -0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGy <= 0.41) {
																if ( AxXGx <= 0.22) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gy_squared <= -0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AxXAy <= -0.27) {
														if ( AxXAz <= -0.69) {
															if ( AxXGx <= 0.3) {
																if ( AyXGx <= -0.14) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Ay_squared <= -0.35) {
																if ( AzXGz <= 0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay <= -0.58) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Ay <= -0.5) {
															if ( AyXAz <= 0.56) {
																return 0;
															}
															else {
																if ( Gy <= -1.28) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GyXGz <= -0.01) {
																return 1;
															}
															else {
																if ( AyXAz <= 0.92) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AxXGx <= -0.01) {
											if ( Gy_squared <= -0.13) {
												if ( AzXGy <= -0.15) {
													if ( AxXAz <= -0.13) {
														if ( AxXAy <= -0.29) {
															if ( Ay_squared <= -0.38) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( GxXGy <= 0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AzXGz <= 0.1) {
															if ( Az <= -0.91) {
																if ( Az <= -1.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AyXGx <= 0.05) {
														if ( AyXGz <= 0.11) {
															if ( Gy_squared <= -0.15) {
																return 2;
															}
															else {
																if ( AxXAz <= -0.21) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy_squared <= -0.14) {
																if ( AzXGy <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGz <= 0.12) {
															if ( GyXGz <= -0.02) {
																if ( AxXGx <= -0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXAz <= 0.48) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AzXGy <= -0.0) {
																if ( AxXAz <= -0.04) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXGz <= -0.09) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
											else {
												if ( GxXGy <= 0.05) {
													if ( AyXAz <= 0.53) {
														if ( Gx <= -0.07) {
															if ( GxXGy <= 0.03) {
																if ( AyXGy <= 0.26) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gx <= -0.17) {
															if ( AxXGy <= 0.14) {
																if ( Ay_squared <= -0.5) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy_squared <= -0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Az_squared <= 0.48) {
																if ( AyXGy <= -0.64) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AzXGy <= 0.19) {
														return 2;
													}
													else {
														if ( Ay <= -0.52) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AzXGy <= -0.4) {
												if ( AxXGy <= 0.33) {
													if ( AyXGy <= -0.66) {
														return 2;
													}
													else {
														if ( Gy_squared <= -0.02) {
															return 1;
														}
														else {
															if ( AyXGy <= -0.6) {
																return 1;
															}
															else {
																if ( AyXAz <= 0.71) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( GyXGz <= -0.07) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gy <= -0.63) {
													return 0;
												}
												else {
													if ( AyXGy <= 0.02) {
														if ( AxXGz <= -0.04) {
															if ( Ay <= -0.55) {
																if ( AyXGz <= 0.13) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGy <= 0.1) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Az_squared <= 0.61) {
																if ( AyXGz <= 0.13) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXGy <= -0.19) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Ax <= 1.25) {
															if ( AyXGz <= 0.11) {
																if ( AyXAz <= 0.78) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GyXGz <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Ay_squared <= -0.54) {
																return 0;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Gy_squared <= -0.08) {
									if ( Ax_squared <= 1.13) {
										if ( Az <= -1.78) {
											if ( AzXGz <= -0.01) {
												if ( AxXGy <= 0.13) {
													if ( GxXGy <= 0.01) {
														return 1;
													}
													else {
														if ( AzXGz <= -0.14) {
															return 1;
														}
														else {
															if ( Gx_squared <= -0.13) {
																return 1;
															}
															else {
																if ( AzXGz <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gx_squared <= -0.1) {
												if ( GxXGy <= 0.0) {
													if ( Ay <= 1.39) {
														return 0;
													}
													else {
														if ( GxXGy <= -0.04) {
															return 0;
														}
														else {
															if ( GxXGz <= 0.0) {
																if ( Gy <= 0.42) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= 0.07) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AxXAz <= -0.14) {
														if ( AxXGx <= -0.03) {
															if ( GyXGz <= -0.03) {
																if ( AyXAz <= -0.91) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXGx <= -0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GxXGy <= 0.03) {
																if ( Gz <= 0.31) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Ay_squared <= -0.01) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AxXAz <= -0.0) {
															if ( GyXGz <= -0.03) {
																if ( AzXGy <= 0.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay <= 1.39) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXGz <= 0.02) {
																if ( AxXGx <= -0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gy_squared <= -0.14) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AyXGx <= -0.57) {
													return 0;
												}
												else {
													if ( AxXAz <= -0.26) {
														if ( AzXGx <= 0.24) {
															if ( AyXGy <= 0.28) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Ay_squared <= 0.26) {
															if ( Ay <= 1.34) {
																return 0;
															}
															else {
																if ( Gx_squared <= -0.06) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( Gz <= 0.04) {
											if ( GxXGz <= 0.01) {
												return 1;
											}
											else {
												if ( Gz <= 0.04) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( AzXGy <= -0.41) {
										if ( AxXGx <= 0.11) {
											if ( Gy <= 2.89) {
												if ( AyXGy <= 0.83) {
													if ( Gy <= 1.29) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AzXGy <= -0.6) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Ay_squared <= -0.29) {
											if ( GxXGz <= 0.02) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gz_squared <= -0.13) {
												return 1;
											}
											else {
												if ( Gy_squared <= -0.02) {
													if ( AyXAz <= -1.26) {
														return 0;
													}
													else {
														if ( AzXGz <= 0.08) {
															if ( AxXAz <= -0.36) {
																return 0;
															}
															else {
																if ( AxXAy <= 0.4) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGz <= 0.17) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGx <= 0.66) {
														if ( Gz <= 0.12) {
															if ( AyXGy <= -0.62) {
																if ( GxXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( GxXGy <= 0.14) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( Ay <= -0.43) {
								if ( AzXGy <= 0.53) {
									if ( GxXGy <= 0.0) {
										if ( Gz <= -0.11) {
											if ( Ay_squared <= -0.33) {
												if ( Az_squared <= 0.09) {
													return 0;
												}
												else {
													if ( AxXGy <= -0.05) {
														return 1;
													}
													else {
														if ( AxXAz <= 0.11) {
															return 1;
														}
														else {
															if ( AyXGx <= -0.31) {
																return 1;
															}
															else {
																if ( AyXGy <= -0.15) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AxXGz <= 0.03) {
													if ( Az_squared <= 0.2) {
														if ( AzXGx <= -0.13) {
															return 0;
														}
														else {
															if ( AyXGy <= 0.27) {
																if ( AyXGx <= -0.1) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( Gx <= -0.2) {
															return 1;
														}
														else {
															if ( AxXAy <= 0.23) {
																return 1;
															}
															else {
																if ( AyXGx <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AzXGx <= 0.09) {
												if ( GxXGy <= -0.06) {
													return 0;
												}
												else {
													if ( GxXGy <= -0.04) {
														return 1;
													}
													else {
														if ( AxXAy <= 0.41) {
															if ( Ay <= -0.48) {
																if ( AzXGx <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Az <= -0.91) {
													if ( AxXGy <= -0.1) {
														if ( Gz <= 0.16) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gy_squared <= -0.09) {
															if ( Ax <= -1.12) {
																return 2;
															}
															else {
																if ( Gy_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXGz <= -0.07) {
																return 1;
															}
															else {
																if ( Gy <= 0.91) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( GxXGz <= -0.01) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( Az <= -0.8) {
											if ( AxXAy <= 0.5) {
												if ( AyXGz <= 0.04) {
													if ( Ay_squared <= -0.29) {
														if ( AyXAz <= 0.79) {
															if ( AxXGz <= -0.04) {
																return 2;
															}
															else {
																if ( Gx <= 0.0) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Gy <= 0.28) {
																if ( AyXGz <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGy <= -0.05) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( GyXGz <= -0.02) {
															if ( GxXGy <= 0.01) {
																return 1;
															}
															else {
																if ( GxXGy <= 0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( AyXAz <= 0.87) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAy <= 0.38) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.39) {
														if ( AxXAy <= 0.37) {
															if ( AxXGy <= 0.02) {
																if ( AyXAz <= 0.84) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXGx <= -0.04) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( GyXGz <= -0.04) {
															if ( Ay_squared <= -0.4) {
																if ( AyXAz <= 0.83) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGy <= -0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXGx <= -0.08) {
																if ( AxXAz <= 0.14) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= 0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gy <= 0.84) {
													if ( Gx <= 0.18) {
														if ( AyXAz <= 0.78) {
															if ( Gy_squared <= -0.15) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXAz <= 0.51) {
																if ( Gy_squared <= -0.15) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXAz <= 0.61) {
														if ( AyXAz <= 0.87) {
															if ( Gy <= 1.12) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( Gz <= -0.29) {
												if ( AyXGx <= 0.02) {
													if ( AyXGy <= -0.22) {
														if ( AyXGy <= -0.29) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gx_squared <= -0.12) {
													if ( AxXAy <= 0.27) {
														if ( Az_squared <= -0.07) {
															return 0;
														}
														else {
															if ( Gy_squared <= -0.15) {
																return 0;
															}
															else {
																if ( AxXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AzXGz <= -0.02) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Gz_squared <= -0.13) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( AxXGx <= -0.13) {
										if ( GxXGy <= -0.43) {
											return 0;
										}
										else {
											if ( GyXGz <= -0.03) {
												if ( GyXGz <= -0.07) {
													if ( AxXAz <= 0.34) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXAz <= 0.78) {
														if ( AyXGx <= -0.45) {
															return 2;
														}
														else {
															if ( Gy <= -1.37) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AyXGz <= 0.03) {
											if ( GxXGy <= -0.32) {
												if ( Gy_squared <= 0.25) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gy <= -1.38) {
													if ( Gx_squared <= -0.03) {
														return 2;
													}
													else {
														if ( AyXGz <= -0.02) {
															return 2;
														}
														else {
															if ( AyXAz <= 0.75) {
																return 2;
															}
															else {
																if ( AzXGy <= 0.84) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AxXGz <= -0.02) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gy <= -1.58) {
												return 0;
											}
											else {
												if ( AxXAy <= 0.34) {
													if ( Gy <= -1.2) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( Gy_squared <= -0.15) {
									if ( AzXGz <= 0.01) {
										if ( AyXGx <= -0.09) {
											if ( Az_squared <= 0.01) {
												if ( AxXGz <= -0.03) {
													return 2;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gx <= -0.61) {
													return 0;
												}
												else {
													if ( AxXAy <= 0.1) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Ay_squared <= -0.75) {
												if ( Ax_squared <= -0.1) {
													return 1;
												}
												else {
													if ( AyXGy <= -0.02) {
														if ( AxXGx <= -0.08) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAy <= 0.86) {
													if ( Gz <= 0.08) {
														if ( AzXGx <= -0.09) {
															if ( Ax <= -1.18) {
																return 2;
															}
															else {
																if ( Az_squared <= 0.07) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AzXGy <= -0.07) {
																return 1;
															}
															else {
																if ( Ay <= 1.54) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AyXAz <= -1.41) {
															return 2;
														}
														else {
															if ( AxXGz <= -0.07) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.05) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Az_squared <= 0.01) {
											if ( AyXGz <= -0.06) {
												if ( Gx_squared <= -0.07) {
													if ( AxXAz <= 0.11) {
														if ( Ay_squared <= 0.07) {
															if ( Gz <= -0.56) {
																return 2;
															}
															else {
																if ( AyXAz <= -0.76) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXGx <= -0.0) {
															if ( Ay_squared <= -0.04) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Ay <= 1.53) {
													if ( Ay <= 1.47) {
														if ( Ay <= 1.42) {
															return 1;
														}
														else {
															if ( Gz <= -0.24) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AyXGx <= -0.04) {
															if ( AyXAz <= -0.79) {
																if ( AxXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXAz <= 0.12) {
																if ( AxXAz <= 0.11) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gx <= 0.28) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Az_squared <= 1.03) {
												if ( Ay <= 1.25) {
													if ( Ay <= 1.2) {
														if ( Ax_squared <= 0.38) {
															if ( AxXGx <= -0.06) {
																return 1;
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Az_squared <= 0.55) {
														if ( Az_squared <= 0.06) {
															if ( Gx_squared <= -0.11) {
																if ( Ay_squared <= -0.12) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXGz <= 0.02) {
																if ( AxXGx <= 0.0) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AxXGz <= -0.01) {
															return 0;
														}
														else {
															if ( AxXGx <= -0.06) {
																return 2;
															}
															else {
																if ( AyXGz <= -0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.28) {
													return 2;
												}
												else {
													if ( GxXGz <= 0.01) {
														return 2;
													}
													else {
														if ( AxXGy <= 0.02) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AyXAz <= -0.97) {
										if ( Az <= -1.85) {
											if ( Ax <= -0.73) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											if ( Az <= -0.77) {
												if ( AzXGx <= -0.29) {
													return 0;
												}
												else {
													if ( GyXGz <= -0.01) {
														if ( AxXGz <= -0.04) {
															return 0;
														}
														else {
															if ( GxXGz <= -0.02) {
																return 0;
															}
															else {
																if ( AxXAz <= 0.42) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.05) {
													if ( Gx_squared <= -0.05) {
														if ( Ay <= 1.57) {
															if ( Az <= -0.66) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Ay_squared <= 0.5) {
																if ( AyXGy <= 0.25) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx_squared <= -0.12) {
														return 0;
													}
													else {
														if ( AzXGx <= -0.52) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( GxXGy <= 0.12) {
											if ( AzXGx <= 0.11) {
												if ( Ax <= -1.97) {
													if ( Az_squared <= 0.55) {
														return 2;
													}
													else {
														if ( AzXGx <= 0.03) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AzXGy <= 0.81) {
														if ( AzXGy <= 0.09) {
															if ( Gz <= -0.1) {
																if ( AyXGy <= 0.29) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= -0.15) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAz <= 0.72) {
																if ( AyXGz <= 0.01) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AxXGx <= -0.14) {
															return 2;
														}
														else {
															if ( Az_squared <= 0.55) {
																return 2;
															}
															else {
																if ( Gy_squared <= 0.14) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gx_squared <= -0.09) {
													if ( Ay_squared <= -0.6) {
														return 1;
													}
													else {
														if ( Gy <= -0.92) {
															return 2;
														}
														else {
															if ( Ay_squared <= 0.12) {
																if ( AyXGz <= 0.11) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( Ay <= 1.47) {
														if ( Ay <= -0.36) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( AzXGz <= 0.14) {
												if ( AyXGx <= -0.31) {
													return 0;
												}
												else {
													if ( Ay_squared <= -0.07) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( AyXGz <= -0.42) {
						if ( AxXGz <= -0.09) {
							if ( Az_squared <= -0.13) {
								if ( Gz_squared <= 0.35) {
									if ( AxXGy <= 0.2) {
										if ( AzXGy <= -0.07) {
											if ( Gx <= 1.31) {
												if ( Gz_squared <= 0.1) {
													return 2;
												}
												else {
													return 0;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( GyXGz <= -0.34) {
												return 1;
											}
											else {
												if ( Gz_squared <= 0.21) {
													if ( Gz_squared <= 0.04) {
														if ( Gz <= -1.14) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Ay_squared <= -0.12) {
															return 0;
														}
														else {
															if ( Ay <= 1.57) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( AyXGx <= 0.64) {
											if ( Gz_squared <= -0.0) {
												return 0;
											}
											else {
												if ( AzXGy <= -0.08) {
													if ( AyXGz <= -0.85) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Gx <= 1.48) {
										if ( AxXAy <= 1.16) {
											if ( GxXGy <= 0.01) {
												return 0;
											}
											else {
												if ( AyXGx <= -0.13) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AyXGy <= 0.83) {
									if ( AxXGx <= 0.13) {
										if ( AzXGz <= 0.52) {
											if ( GxXGy <= 0.0) {
												if ( Ay_squared <= -0.17) {
													return 0;
												}
												else {
													if ( AxXAz <= -0.26) {
														return 0;
													}
													else {
														if ( AxXAy <= 0.4) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AxXAz <= -0.07) {
													if ( AxXAy <= 0.55) {
														return 0;
													}
													else {
														if ( Gy_squared <= -0.1) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGx <= 0.12) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gx <= -1.01) {
												if ( AyXGx <= -5.58) {
													return 0;
												}
												else {
													if ( Gy <= -0.91) {
														if ( Gz <= -5.59) {
															return 0;
														}
														else {
															if ( Ax <= 0.97) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( Ax <= 1.65) {
															if ( Gy_squared <= -0.12) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AxXAz <= -0.04) {
													if ( AxXAz <= -0.27) {
														if ( AyXGz <= -0.97) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGy <= 0.03) {
															if ( AzXGx <= 0.27) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AzXGz <= 1.12) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( Ay <= 1.55) {
											if ( Gz_squared <= 0.08) {
												return 1;
											}
											else {
												if ( GxXGy <= 0.38) {
													if ( AyXAz <= -0.73) {
														if ( Gy <= 1.1) {
															if ( Az_squared <= 0.09) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Az <= -0.77) {
												return 0;
											}
											else {
												if ( Az <= -0.62) {
													return 0;
												}
												else {
													if ( AzXGz <= 0.69) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( Gx <= -1.63) {
										return 0;
									}
									else {
										if ( AzXGx <= -0.65) {
											return 0;
										}
										else {
											if ( AzXGy <= -1.86) {
												return 0;
											}
											else {
												if ( AxXAy <= 0.9) {
													if ( AxXAz <= -0.02) {
														if ( AzXGz <= 1.02) {
															if ( AzXGx <= -0.24) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( Ay_squared <= 0.15) {
								if ( Gy_squared <= 0.1) {
									if ( GxXGz <= -0.5) {
										if ( Az_squared <= -0.06) {
											if ( Az <= 0.29) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gz_squared <= 0.11) {
											if ( Gy_squared <= -0.07) {
												if ( AzXGz <= 0.21) {
													return 1;
												}
												else {
													if ( Gx_squared <= -0.06) {
														if ( Ax_squared <= -0.15) {
															if ( Az <= -0.29) {
																if ( Az_squared <= 0.02) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AyXGx <= 0.62) {
												if ( AyXAz <= -0.76) {
													if ( AxXAz <= 0.11) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Gx_squared <= 0.18) {
										if ( GxXGz <= 0.06) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AzXGz <= 0.44) {
									if ( Ay <= 1.65) {
										if ( AxXAy <= 0.1) {
											return 0;
										}
										else {
											if ( Gx_squared <= 0.15) {
												return 0;
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( AyXAz <= -0.89) {
											if ( AxXGz <= -0.08) {
												return 0;
											}
											else {
												if ( Gz_squared <= -0.06) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXGx <= -0.28) {
												return 1;
											}
											else {
												if ( AzXGx <= 0.16) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
									}
								}
								else {
									if ( AzXGx <= 1.12) {
										if ( GyXGz <= 0.03) {
											if ( AxXGz <= 0.29) {
												if ( Ay_squared <= 0.35) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gy <= -0.88) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
							}
						}
					}
					else {
						if ( AyXAz <= 0.67) {
							if ( Gy_squared <= -0.08) {
								if ( Ax_squared <= -0.14) {
									if ( Az <= -0.26) {
										if ( Gx_squared <= -0.09) {
											if ( AxXGz <= -0.01) {
												if ( Az_squared <= 0.02) {
													if ( Ay <= 1.34) {
														return 0;
													}
													else {
														if ( Gz <= 0.37) {
															if ( Gx_squared <= -0.11) {
																if ( GyXGz <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXAz <= 0.09) {
																return 1;
															}
															else {
																if ( Ay_squared <= 0.15) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( Ay_squared <= -0.04) {
														return 0;
													}
													else {
														if ( Az <= -0.8) {
															return 0;
														}
														else {
															if ( AxXAz <= 0.13) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.09) {
													if ( AyXAz <= -0.97) {
														return 0;
													}
													else {
														if ( AyXGz <= -0.27) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.19) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( Ay <= 1.42) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AxXGz <= -0.0) {
												if ( AyXAz <= -1.05) {
													return 0;
												}
												else {
													if ( Ay_squared <= -0.29) {
														return 0;
													}
													else {
														if ( Gx_squared <= 0.1) {
															if ( AzXGx <= 0.21) {
																if ( AyXGx <= 0.26) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( Gz_squared <= -0.04) {
													if ( Ax <= -0.67) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( AyXAz <= -0.24) {
											if ( GyXGz <= -0.05) {
												if ( Gx <= -0.26) {
													if ( AyXGx <= -0.33) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXGx <= 0.01) {
														if ( Ay_squared <= 0.18) {
															if ( AzXGz <= -0.07) {
																if ( AxXGx <= -0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXGx <= 0.13) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AzXGz <= 0.16) {
													if ( AxXGx <= 0.02) {
														if ( Gx_squared <= -0.13) {
															if ( AzXGz <= -0.04) {
																if ( Gx <= -0.07) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy <= -0.18) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXAz <= -0.4) {
																if ( AyXAz <= -0.73) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXGz <= -0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AyXGx <= -0.5) {
												if ( AyXAz <= 0.3) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGz <= -0.07) {
													if ( Ay <= -0.58) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gz_squared <= 0.55) {
														if ( AxXAz <= 0.07) {
															if ( Gy <= 0.14) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gx_squared <= -0.13) {
																if ( GyXGz <= -0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz_squared <= -0.08) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( Ay <= 1.28) {
										if ( AzXGy <= 0.13) {
											if ( Gz <= -0.76) {
												if ( Gx <= 1.06) {
													if ( Az_squared <= -0.26) {
														return 2;
													}
													else {
														if ( AxXGx <= 0.41) {
															if ( GyXGz <= 0.09) {
																if ( AxXAy <= -0.11) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Ay_squared <= -0.19) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AyXAz <= -0.37) {
													return 0;
												}
												else {
													if ( AxXAz <= -0.14) {
														if ( GyXGz <= -0.1) {
															return 1;
														}
														else {
															if ( AxXAz <= -0.87) {
																return 2;
															}
															else {
																if ( GxXGz <= 0.07) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AxXAy <= -0.05) {
															if ( AxXGx <= -0.03) {
																if ( AyXGz <= 0.3) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GyXGz <= -0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GxXGz <= -0.13) {
																return 1;
															}
															else {
																if ( AyXGz <= -0.21) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AyXGz <= -0.23) {
												if ( AyXGy <= 0.32) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( GxXGz <= -0.0) {
													if ( Gz_squared <= -0.09) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( Az_squared <= -0.11) {
											if ( GyXGz <= -0.05) {
												if ( GxXGz <= -0.0) {
													if ( GyXGz <= -0.08) {
														if ( AxXGz <= -0.15) {
															return 0;
														}
														else {
															if ( Az_squared <= -0.18) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AxXGx <= -0.06) {
															return 1;
														}
														else {
															if ( AxXGx <= -0.05) {
																return 1;
															}
															else {
																if ( Ay <= 1.48) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Ay_squared <= 0.09) {
														if ( Ax_squared <= -0.02) {
															if ( AxXGz <= 0.07) {
																if ( AyXGy <= -0.18) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXGz <= -0.16) {
													if ( AzXGy <= -0.03) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AzXGx <= 0.17) {
														if ( Ay_squared <= 0.41) {
															if ( AxXGz <= 0.17) {
																if ( AzXGx <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( Gx_squared <= -0.07) {
												if ( GxXGy <= 0.01) {
													if ( AxXAy <= 0.36) {
														return 0;
													}
													else {
														if ( AxXAz <= -0.45) {
															return 0;
														}
														else {
															if ( Ay <= 1.58) {
																if ( AzXGx <= -0.16) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( Gy_squared <= -0.11) {
														if ( Gx_squared <= -0.13) {
															return 0;
														}
														else {
															if ( AyXAz <= -0.99) {
																if ( Gz_squared <= -0.1) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXGx <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AyXGz <= -0.21) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AyXAz <= -0.85) {
													if ( AxXGy <= -0.03) {
														return 0;
													}
													else {
														if ( Gx <= 1.26) {
															if ( AyXAz <= -1.23) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
							else {
								if ( AyXGz <= 1.0) {
									if ( Gx_squared <= -0.12) {
										if ( AzXGz <= -0.01) {
											if ( Gy <= -0.77) {
												if ( Az_squared <= -0.11) {
													if ( AzXGy <= 0.24) {
														if ( Gx <= -0.14) {
															return 2;
														}
														else {
															if ( AxXAy <= -0.02) {
																return 2;
															}
															else {
																if ( AzXGz <= -0.1) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGy <= 0.39) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AyXAz <= 0.37) {
													if ( AyXAz <= -0.84) {
														return 0;
													}
													else {
														if ( Ay_squared <= -0.38) {
															return 0;
														}
														else {
															if ( GxXGy <= 0.02) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Ax_squared <= 0.35) {
												if ( Ax <= -0.22) {
													if ( GxXGy <= -0.0) {
														return 0;
													}
													else {
														if ( Ay_squared <= -0.17) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGz <= -0.24) {
														return 0;
													}
													else {
														if ( GyXGz <= 0.18) {
															if ( AxXAy <= -0.26) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Ay <= 0.91) {
											if ( AyXAz <= 0.53) {
												if ( AyXGy <= 0.61) {
													if ( AzXGx <= -0.12) {
														if ( Az_squared <= -0.16) {
															return 1;
														}
														else {
															if ( AxXGx <= 1.17) {
																if ( Ay_squared <= -0.26) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXGy <= 1.76) {
															if ( Gz <= 0.36) {
																if ( GxXGy <= 0.06) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= 0.19) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AzXGx <= 0.53) {
														if ( AxXGx <= -0.19) {
															return 0;
														}
														else {
															if ( AyXGz <= -0.29) {
																return 0;
															}
															else {
																if ( AxXGx <= -0.09) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXGz <= 0.09) {
													if ( AyXGy <= 1.18) {
														if ( AxXAy <= 0.3) {
															if ( GxXGy <= -0.14) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AxXAz <= -0.04) {
												if ( AyXGy <= -0.69) {
													if ( Az <= -0.58) {
														return 0;
													}
													else {
														if ( AzXGx <= 0.52) {
															if ( Gy <= -1.11) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Gx <= 3.32) {
														if ( Ay <= 1.55) {
															if ( AzXGx <= 0.43) {
																if ( AzXGz <= -0.27) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXAz <= -0.08) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GxXGy <= -0.03) {
													if ( GxXGy <= -0.14) {
														if ( Az_squared <= 0.09) {
															if ( Gy_squared <= -0.02) {
																return 1;
															}
															else {
																if ( AxXAy <= 0.41) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGy <= -0.66) {
															return 2;
														}
														else {
															if ( AyXAz <= -0.64) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( Ay <= 1.55) {
														if ( AxXAy <= -0.06) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.1) {
																return 0;
															}
															else {
																if ( AyXGz <= 0.49) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( GyXGz <= 0.1) {
															if ( GyXGz <= -0.11) {
																if ( Gx_squared <= -0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Ax_squared <= -0.02) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGz <= -0.46) {
										if ( Ay_squared <= -0.82) {
											return 1;
										}
										else {
											if ( AyXGz <= 2.31) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AyXGy <= 1.55) {
											if ( Gx <= 0.42) {
												if ( AyXGy <= 1.26) {
													if ( Gx <= 0.08) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AzXGy <= -0.03) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AzXGy <= 0.78) {
												if ( GyXGz <= 1.77) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
						}
						else {
							if ( GxXGy <= 0.02) {
								if ( Ay_squared <= -0.21) {
									if ( AzXGz <= 0.27) {
										if ( AxXAy <= -0.47) {
											if ( Gz_squared <= -0.08) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											if ( GxXGz <= -0.01) {
												if ( AzXGz <= 0.24) {
													if ( AxXGz <= -0.01) {
														if ( AxXAz <= 0.19) {
															return 2;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AyXGy <= -0.13) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gx_squared <= 0.05) {
													if ( AyXGx <= -0.45) {
														return 1;
													}
													else {
														if ( AxXGy <= 0.11) {
															if ( AyXAz <= 0.73) {
																return 0;
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( GxXGy <= -0.01) {
											if ( AxXAz <= 0.31) {
												if ( Ax_squared <= -0.13) {
													if ( Az <= -1.38) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXGx <= 0.37) {
														if ( AyXGx <= -0.08) {
															if ( AxXGx <= 0.08) {
																return 2;
															}
															else {
																if ( Gx_squared <= -0.11) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gx <= 0.97) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXGx <= 0.03) {
												if ( AxXGz <= 0.1) {
													if ( AzXGy <= 0.12) {
														if ( Ay_squared <= -0.42) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.14) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gx <= 0.4) {
													if ( AxXGy <= 0.01) {
														if ( AyXGz <= 0.27) {
															return 1;
														}
														else {
															if ( Ax <= 0.8) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( AyXAz <= 0.75) {
										if ( Gz <= -0.79) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										if ( AxXGz <= -0.6) {
											return 0;
										}
										else {
											if ( AzXGz <= 1.88) {
												if ( Ay_squared <= -0.14) {
													if ( Gz <= -0.7) {
														if ( GxXGy <= -0.02) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Ax <= -0.05) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Az_squared <= 0.55) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
							else {
								if ( GyXGz <= -0.09) {
									if ( AxXAz <= 0.24) {
										if ( AyXGy <= 0.27) {
											if ( AyXGz <= 0.43) {
												if ( AzXGx <= -0.31) {
													return 0;
												}
												else {
													if ( Ay_squared <= -0.68) {
														return 2;
													}
													else {
														if ( GyXGz <= -0.09) {
															if ( AxXGz <= 0.02) {
																if ( AxXAz <= 0.12) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AzXGy <= 0.42) {
												if ( GxXGz <= -0.04) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.04) {
														if ( AyXGy <= 0.32) {
															return 2;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AxXAy <= -0.64) {
															return 1;
														}
														else {
															if ( Gx <= -0.38) {
																return 1;
															}
															else {
																if ( Gz <= 0.42) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( GxXGy <= 0.18) {
											if ( Ay_squared <= -0.44) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Az <= -2.65) {
										return 1;
									}
									else {
										if ( GyXGz <= -0.07) {
											return 2;
										}
										else {
											if ( Gz_squared <= -0.09) {
												if ( GxXGy <= 0.07) {
													return 2;
												}
												else {
													return 1;
												}
											}
											else {
												if ( GxXGy <= 0.03) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.8) {
														return 0;
													}
													else {
														if ( Ay <= -0.53) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if ( AzXGz <= -0.33) {
				if ( AyXAz <= 0.06) {
					if ( Ay <= 1.41) {
						if ( Gy_squared <= 0.42) {
							if ( AzXGy <= 0.79) {
								if ( Ay_squared <= -1.15) {
									return 0;
								}
								else {
									if ( AyXGz <= 1.45) {
										if ( GyXGz <= 0.13) {
											if ( Gz_squared <= -0.01) {
												return 0;
											}
											else {
												if ( Ay <= 1.34) {
													if ( Az_squared <= -0.11) {
														return 0;
													}
													else {
														if ( AzXGz <= -0.44) {
															if ( AyXAz <= -0.74) {
																if ( Ax <= -0.1) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( GxXGz <= -0.38) {
														return 0;
													}
													else {
														if ( AxXGz <= -0.04) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( GxXGy <= 0.29) {
												if ( AxXGy <= -0.09) {
													return 0;
												}
												else {
													if ( AyXAz <= -1.04) {
														return 0;
													}
													else {
														if ( Ay_squared <= -0.35) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AxXGx <= -0.01) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( Az_squared <= 1.47) {
								if ( AzXGy <= 2.28) {
									if ( AxXAy <= 0.04) {
										return 0;
									}
									else {
										if ( AyXAz <= -0.39) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									return 0;
								}
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( AzXGz <= -0.4) {
							if ( Gx_squared <= 0.45) {
								if ( AxXGy <= 0.03) {
									if ( AzXGy <= -0.25) {
										if ( GyXGz <= 0.89) {
											if ( AxXAz <= 0.3) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXGx <= -0.21) {
											if ( Ay_squared <= -0.01) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											if ( AxXAz <= 0.21) {
												if ( Gy_squared <= -0.14) {
													return 0;
												}
												else {
													if ( AyXGx <= -0.13) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.27) {
															if ( AyXGz <= 0.88) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( Gz_squared <= 0.77) {
										if ( GxXGy <= -0.28) {
											return 0;
										}
										else {
											if ( Gx_squared <= -0.12) {
												return 0;
											}
											else {
												if ( Ax <= -0.27) {
													if ( AxXGy <= 0.17) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AxXAz <= -1.05) {
									return 0;
								}
								else {
									if ( GyXGz <= 3.03) {
										if ( AyXGy <= 2.94) {
											if ( AzXGy <= -0.24) {
												return 0;
											}
											else {
												if ( AzXGx <= 1.71) {
													if ( AzXGx <= 1.04) {
														if ( AxXAy <= 0.11) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( AxXGy <= 0.05) {
								if ( AzXGx <= 0.12) {
									if ( AxXAy <= 0.14) {
										if ( AyXGz <= 0.72) {
											return 2;
										}
										else {
											return 0;
										}
									}
									else {
										if ( GyXGz <= -0.32) {
											return 2;
										}
										else {
											if ( AyXGx <= -0.09) {
												return 1;
											}
											else {
												if ( Gx_squared <= -0.13) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
									}
								}
								else {
									return 0;
								}
							}
							else {
								return 0;
							}
						}
					}
				}
				else {
					if ( Gy <= 0.47) {
						if ( Ax_squared <= 0.02) {
							if ( AyXGz <= -0.87) {
								if ( Gx <= -1.14) {
									if ( AzXGz <= -0.39) {
										if ( AyXGz <= -0.97) {
											if ( AyXAz <= 0.44) {
												return 1;
											}
											else {
												if ( Gy <= -0.44) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( GxXGz <= 0.34) {
										if ( Ay <= -0.92) {
											return 0;
										}
										else {
											if ( AzXGy <= 0.48) {
												if ( Gz_squared <= 0.7) {
													if ( Gz <= 1.58) {
														return 0;
													}
													else {
														if ( AyXGy <= 0.11) {
															return 0;
														}
														else {
															if ( GxXGy <= -0.01) {
																return 2;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AzXGy <= 0.05) {
											return 0;
										}
										else {
											if ( AyXGy <= 0.26) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
								}
							}
							else {
								if ( Gy <= -0.94) {
									if ( Gx_squared <= -0.01) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AzXGx <= 0.04) {
										if ( Az_squared <= -0.03) {
											if ( AyXGx <= -0.34) {
												return 0;
											}
											else {
												if ( AyXGx <= 0.01) {
													if ( Gy <= -0.02) {
														if ( AyXAz <= 0.38) {
															return 0;
														}
														else {
															if ( Gz <= 1.2) {
																if ( Ay <= -0.7) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gy <= -0.49) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXAz <= 0.09) {
												if ( Gz_squared <= 0.01) {
													return 0;
												}
												else {
													if ( Ay <= -0.49) {
														if ( Az <= -0.69) {
															if ( AxXGy <= -0.03) {
																return 0;
															}
															else {
																if ( Ay_squared <= -0.26) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AzXGz <= -0.37) {
																if ( AzXGz <= -0.4) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AyXGy <= 0.01) {
													return 1;
												}
												else {
													if ( AyXGx <= -0.66) {
														return 0;
													}
													else {
														if ( AzXGz <= -0.75) {
															return 0;
														}
														else {
															if ( AxXGz <= -0.16) {
																return 2;
															}
															else {
																if ( AxXGz <= -0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXGz <= -0.4) {
											if ( Ay <= -0.8) {
												return 0;
											}
											else {
												if ( Gz <= 1.11) {
													if ( AxXGy <= 0.07) {
														if ( AyXGz <= -0.62) {
															return 2;
														}
														else {
															if ( AyXGx <= 0.99) {
																if ( Ax_squared <= -0.11) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AzXGx <= 0.49) {
														if ( AyXGy <= 0.1) {
															if ( AyXGx <= 0.38) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															if ( Az_squared <= 0.33) {
																if ( AyXGz <= -0.6) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( AxXGz <= -0.1) {
												return 2;
											}
											else {
												return 1;
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXAz <= 0.58) {
								if ( Ax_squared <= 0.61) {
									if ( AzXGz <= -0.42) {
										return 0;
									}
									else {
										return 2;
									}
								}
								else {
									return 0;
								}
							}
							else {
								if ( Az <= -0.22) {
									if ( AxXGx <= -0.05) {
										if ( Ay <= -0.68) {
											if ( Ay <= -1.97) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( Gy <= -0.1) {
											if ( AzXGy <= 0.21) {
												return 0;
											}
											else {
												if ( AzXGx <= -4.92) {
													return 0;
												}
												else {
													if ( GyXGz <= -3.42) {
														return 1;
													}
													else {
														if ( Gx_squared <= 0.16) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									return 1;
								}
							}
						}
					}
					else {
						if ( AxXGy <= -0.03) {
							if ( Ay <= -0.68) {
								if ( GxXGz <= -0.26) {
									if ( AzXGy <= -0.86) {
										if ( AxXAz <= 0.89) {
											return 0;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
								else {
									return 0;
								}
							}
							else {
								if ( AzXGy <= -0.98) {
									if ( Gx_squared <= 2.77) {
										if ( Az <= -1.38) {
											if ( AxXGx <= 0.51) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 0;
									}
								}
								else {
									if ( AzXGz <= -0.65) {
										return 0;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( Az_squared <= 0.45) {
								if ( Gy <= 0.91) {
									if ( GxXGy <= -0.06) {
										return 0;
									}
									else {
										if ( Az <= -0.69) {
											return 0;
										}
										else {
											if ( AyXGy <= -0.45) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AxXGx <= -0.28) {
										if ( GxXGz <= -0.34) {
											if ( Gx_squared <= 0.29) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AzXGx <= 0.04) {
											if ( AzXGy <= -0.31) {
												if ( AxXAz <= -0.09) {
													if ( GyXGz <= 1.0) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXGx <= 0.0) {
														return 0;
													}
													else {
														if ( AyXGx <= -0.23) {
															if ( AzXGy <= -0.75) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Ax <= -0.05) {
												if ( Gx_squared <= -0.06) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												if ( AxXGz <= 0.78) {
													if ( AxXGy <= 0.42) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( AxXGz <= 2.28) {
									if ( AzXGy <= -2.6) {
										if ( AxXAy <= -0.47) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( AxXAy <= -0.92) {
											return 0;
										}
										else {
											if ( Az <= -3.02) {
												return 1;
											}
											else {
												if ( AxXAz <= -0.87) {
													return 0;
												}
												else {
													if ( AyXGx <= 0.64) {
														if ( AxXGy <= 0.05) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									return 0;
								}
							}
						}
					}
				}
			}
			else {
				if ( GyXGz <= 0.17) {
					if ( AyXGz <= -0.6) {
						if ( Gx_squared <= -0.1) {
							if ( Ay <= -0.83) {
								if ( Ay <= -0.91) {
									return 0;
								}
								else {
									if ( Gz_squared <= 0.07) {
										return 0;
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( GxXGz <= 0.01) {
									if ( AzXGz <= -0.15) {
										if ( Ay_squared <= 0.32) {
											if ( AxXGx <= -0.07) {
												return 0;
											}
											else {
												if ( AxXGy <= -0.14) {
													return 2;
												}
												else {
													if ( AyXGz <= -0.74) {
														return 0;
													}
													else {
														if ( Ay_squared <= -0.07) {
															return 0;
														}
														else {
															if ( Ax_squared <= -0.14) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AxXGy <= -0.01) {
											if ( AyXGy <= 0.36) {
												if ( GxXGz <= -0.06) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AyXGy <= 0.1) {
										if ( Gy_squared <= -0.15) {
											if ( AxXGx <= 0.09) {
												if ( AyXAz <= 0.25) {
													if ( AyXAz <= 0.15) {
														if ( AzXGx <= -0.01) {
															return 2;
														}
														else {
															if ( AzXGx <= 0.02) {
																if ( Gz_squared <= 0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( GxXGz <= 0.09) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gy <= -0.44) {
											if ( AzXGy <= 0.07) {
												if ( Gz_squared <= 0.11) {
													if ( AzXGx <= 0.02) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AzXGx <= -0.0) {
														return 2;
													}
													else {
														if ( GxXGy <= -0.02) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( AyXGx <= -0.09) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AzXGz <= -0.25) {
												if ( GyXGz <= -0.13) {
													if ( Ay_squared <= -0.04) {
														return 0;
													}
													else {
														if ( AyXAz <= 0.32) {
															return 2;
														}
														else {
															if ( AyXGz <= -0.74) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AxXGy <= -0.08) {
														return 2;
													}
													else {
														if ( AxXGz <= 0.24) {
															if ( AxXAy <= 0.14) {
																if ( AxXGy <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( AyXAz <= 0.07) {
													if ( AxXGz <= 0.45) {
														if ( AzXGz <= -0.07) {
															if ( AyXGz <= -0.7) {
																if ( GxXGy <= -0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GxXGy <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXGz <= 0.36) {
																if ( AxXGy <= -0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AzXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Az_squared <= -0.26) {
															if ( AxXGz <= 0.56) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXAy <= -0.84) {
																return 2;
															}
															else {
																if ( AzXGz <= 0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AxXGz <= 0.2) {
														if ( Gz <= 1.16) {
															if ( GxXGy <= -0.02) {
																return 2;
															}
															else {
																if ( AxXGy <= -0.06) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAz <= 0.13) {
																if ( AyXGy <= 0.19) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AyXAz <= 0.08) {
															return 2;
														}
														else {
															if ( AzXGz <= -0.19) {
																if ( GxXGy <= -0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXGx <= -0.22) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( Ay_squared <= 0.56) {
								if ( GxXGz <= 0.23) {
									if ( GxXGz <= -0.35) {
										if ( AxXGz <= 0.18) {
											return 2;
										}
										else {
											return 0;
										}
									}
									else {
										if ( GyXGz <= 0.07) {
											if ( AyXAz <= 0.34) {
												if ( AxXGx <= -0.47) {
													return 0;
												}
												else {
													if ( AzXGz <= -0.12) {
														if ( Gx_squared <= 0.08) {
															if ( AzXGx <= 0.19) {
																if ( AxXGz <= 0.17) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGy <= 0.23) {
															if ( Gy_squared <= -0.15) {
																return 0;
															}
															else {
																if ( GxXGy <= 0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Ay_squared <= 0.41) {
													if ( AxXAy <= 0.03) {
														if ( Gy_squared <= -0.14) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( GxXGy <= -0.08) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AxXGx <= 0.37) {
										if ( Gx_squared <= -0.02) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( AxXAz <= -0.19) {
									return 0;
								}
								else {
									if ( Ax <= -0.84) {
										return 2;
									}
									else {
										if ( Az_squared <= -0.17) {
											if ( Gx_squared <= 0.24) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
						}
					}
					else {
						if ( Ay_squared <= -0.14) {
							if ( AxXAz <= 1.0) {
								if ( Ay_squared <= -0.33) {
									if ( AyXGz <= -0.38) {
										if ( GyXGz <= 0.0) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										if ( AxXGy <= 0.0) {
											if ( AyXGy <= -0.22) {
												return 0;
											}
											else {
												if ( AxXGx <= -0.01) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Ay <= 1.29) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AzXGz <= -0.13) {
										if ( GxXGy <= 0.28) {
											if ( Gy_squared <= -0.0) {
												if ( Gx <= -0.47) {
													if ( Gy_squared <= -0.11) {
														if ( Ax <= -0.61) {
															return 0;
														}
														else {
															if ( AyXAz <= 0.41) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx_squared <= 0.01) {
														if ( AxXGz <= 0.03) {
															if ( GyXGz <= 0.08) {
																if ( AyXGy <= -0.1) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXGz <= 0.61) {
																if ( AyXGy <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Az_squared <= -0.18) {
													return 2;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gy <= -0.03) {
											if ( Gx_squared <= -0.11) {
												return 2;
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
								}
							}
							else {
								return 2;
							}
						}
						else {
							if ( AyXGx <= -0.3) {
								if ( Gx <= -0.66) {
									if ( AxXAz <= 0.14) {
										if ( AyXAz <= -0.78) {
											return 0;
										}
										else {
											if ( AxXAz <= 0.09) {
												if ( AzXGx <= 0.31) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 1;
									}
								}
								else {
									if ( Gx_squared <= 0.06) {
										if ( GyXGz <= 0.05) {
											if ( AzXGy <= -0.07) {
												return 2;
											}
											else {
												if ( AxXGz <= 0.27) {
													if ( AyXGx <= -0.33) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( Gx <= 0.19) {
									if ( AyXGy <= -0.42) {
										if ( AzXGz <= -0.21) {
											if ( AxXGy <= -0.28) {
												return 2;
											}
											else {
												if ( AyXAz <= -0.74) {
													if ( AxXGy <= 0.04) {
														if ( AyXAz <= -0.8) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gy_squared <= 0.18) {
														if ( AxXGy <= 0.19) {
															if ( Gz <= 0.86) {
																return 2;
															}
															else {
																if ( Az <= 0.03) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AyXGx <= 0.11) {
												if ( AxXAz <= 0.1) {
													if ( AyXGz <= 0.65) {
														if ( AxXGz <= 0.12) {
															if ( GxXGz <= -0.03) {
																if ( AzXGz <= -0.07) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXGz <= 0.57) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAy <= 0.61) {
																if ( Gz_squared <= -0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Gy <= -1.29) {
															return 2;
														}
														else {
															if ( AyXAz <= -0.54) {
																return 2;
															}
															else {
																if ( AxXGx <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AzXGy <= 0.06) {
														return 2;
													}
													else {
														if ( AzXGy <= 0.21) {
															if ( AxXGy <= 0.23) {
																if ( GyXGz <= -0.21) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXAz <= -0.38) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Ay <= -0.71) {
													return 0;
												}
												else {
													if ( AxXGz <= 0.11) {
														if ( AxXAy <= 0.14) {
															if ( GxXGy <= -0.16) {
																return 2;
															}
															else {
																if ( AyXAz <= 0.2) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( AyXGz <= -0.4) {
											if ( AzXGx <= 0.14) {
												if ( GyXGz <= -0.04) {
													if ( GxXGy <= 0.03) {
														if ( Az_squared <= -0.2) {
															if ( Gy_squared <= -0.07) {
																if ( AxXGy <= -0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGy <= -0.14) {
																return 1;
															}
															else {
																if ( AzXGx <= 0.04) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AyXGx <= 0.43) {
															if ( Ax_squared <= 0.15) {
																if ( AyXGz <= -0.53) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGz <= 0.12) {
																return 2;
															}
															else {
																if ( Ay_squared <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( GxXGy <= -0.02) {
														if ( AxXGz <= 0.35) {
															if ( Ay <= -0.71) {
																if ( AyXAz <= -0.14) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GxXGy <= -0.06) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AxXGz <= 0.21) {
															if ( AyXGz <= -0.56) {
																return 2;
															}
															else {
																if ( AxXAz <= 0.03) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXAy <= -0.77) {
																if ( AyXAz <= 0.01) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXAz <= -0.21) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.01) {
													if ( AxXGx <= -0.32) {
														if ( Ay <= -0.76) {
															return 0;
														}
														else {
															if ( AzXGz <= -0.11) {
																if ( AyXGz <= -0.5) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Gz <= 0.78) {
															if ( AxXGx <= -0.18) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( Gz <= 0.93) {
																if ( AxXAz <= -0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAz <= -0.06) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( GyXGz <= -0.16) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.02) {
															if ( Gy_squared <= -0.13) {
																if ( AyXGz <= -0.43) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXGy <= 0.16) {
																if ( AxXGy <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGy <= 0.04) {
												if ( AxXAz <= 0.06) {
													if ( AyXAz <= -0.75) {
														return 0;
													}
													else {
														if ( AzXGx <= 0.04) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Az <= -0.37) {
														return 1;
													}
													else {
														if ( Gx <= 0.08) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AyXGx <= -0.13) {
										if ( Gy_squared <= -0.07) {
											if ( AzXGx <= -0.02) {
												if ( AzXGx <= -0.05) {
													return 2;
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gy_squared <= -0.01) {
											if ( AyXGy <= -0.02) {
												if ( Ax_squared <= -0.11) {
													if ( AxXAy <= 0.04) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( GyXGz <= 0.1) {
													if ( AzXGz <= -0.22) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Gy_squared <= 0.29) {
												if ( AzXGx <= -0.07) {
													return 1;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Ay <= 0.99) {
						if ( Gy_squared <= 0.13) {
							if ( AxXAy <= -0.15) {
								if ( AxXGx <= 0.28) {
									if ( AxXAz <= -0.21) {
										return 1;
									}
									else {
										if ( AzXGz <= -0.22) {
											return 0;
										}
										else {
											if ( AxXGy <= 0.64) {
												if ( Gy_squared <= -0.07) {
													return 0;
												}
												else {
													if ( GxXGy <= -0.31) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									return 1;
								}
							}
							else {
								if ( AyXGx <= -0.15) {
									return 0;
								}
								else {
									if ( Gz <= 1.09) {
										return 2;
									}
									else {
										if ( AyXGx <= 0.19) {
											return 2;
										}
										else {
											return 1;
										}
									}
								}
							}
						}
						else {
							if ( AzXGy <= -0.68) {
								return 1;
							}
							else {
								if ( AxXGx <= -0.71) {
									return 0;
								}
								else {
									if ( Gz_squared <= 1.91) {
										if ( AxXGz <= 1.01) {
											if ( AxXGx <= 0.52) {
												if ( Gy <= 2.79) {
													if ( AzXGy <= -0.54) {
														return 1;
													}
													else {
														if ( AyXAz <= 0.31) {
															if ( AyXGy <= -1.23) {
																if ( AyXGy <= -1.31) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= -1.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
					else {
						if ( AyXGx <= -0.63) {
							return 0;
						}
						else {
							if ( Ay_squared <= -0.12) {
								if ( AzXGy <= -0.25) {
									return 0;
								}
								else {
									return 0;
								}
							}
							else {
								if ( AzXGx <= -0.16) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		if ( Ay <= -0.01) {
			if ( Gy_squared <= 0.02) {
				if ( Gz <= -0.25) {
					if ( Gx <= 0.01) {
						if ( AxXAy <= 0.5) {
							if ( AyXGy <= -0.03) {
								if ( AxXGz <= -0.08) {
									if ( AyXGy <= -0.16) {
										if ( Ax_squared <= 0.44) {
											if ( AyXAz <= -0.55) {
												if ( AxXGz <= -0.12) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Ax <= 0.8) {
											return 2;
										}
										else {
											if ( AxXGx <= -0.04) {
												if ( AzXGx <= -0.01) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( AyXGx <= 0.08) {
										if ( Gy_squared <= -0.15) {
											if ( AyXAz <= -0.54) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											if ( AyXGz <= 0.12) {
												return 0;
											}
											else {
												if ( Ay_squared <= -0.01) {
													if ( Ax <= -0.73) {
														return 2;
													}
													else {
														if ( AxXAz <= 0.04) {
															return 0;
														}
														else {
															if ( Gy_squared <= -0.14) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( Gx_squared <= -0.13) {
														return 1;
													}
													else {
														if ( AxXGy <= -0.0) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
									else {
										if ( GxXGz <= 0.03) {
											if ( GxXGy <= -0.05) {
												return 2;
											}
											else {
												if ( AyXGy <= -0.09) {
													if ( Gy_squared <= -0.14) {
														return 2;
													}
													else {
														if ( Gy_squared <= -0.13) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AzXGz <= -0.02) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( Az <= 2.5) {
												if ( AzXGx <= -0.06) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( Gz <= -0.39) {
									if ( GyXGz <= 0.03) {
										if ( AzXGx <= 0.01) {
											if ( AxXAy <= -0.41) {
												if ( AzXGy <= -0.03) {
													if ( Gz <= -0.43) {
														if ( AxXAz <= 0.19) {
															return 2;
														}
														else {
															if ( GxXGy <= 0.02) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Az <= 1.23) {
													return 2;
												}
												else {
													if ( AyXAz <= -0.64) {
														if ( GxXGy <= 0.04) {
															if ( AzXGz <= -0.05) {
																if ( AxXGy <= -0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXGx <= 0.02) {
															if ( Gx <= -0.34) {
																return 2;
															}
															else {
																if ( AzXGx <= 0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AzXGy <= -0.02) {
												if ( AzXGz <= -0.01) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
								else {
									if ( AxXGz <= -0.09) {
										if ( AzXGx <= -0.07) {
											return 1;
										}
										else {
											if ( GyXGz <= -0.02) {
												if ( AyXGx <= 0.01) {
													return 2;
												}
												else {
													if ( AxXGx <= -0.15) {
														return 2;
													}
													else {
														if ( AxXAz <= 0.82) {
															if ( AyXGx <= 0.12) {
																if ( AxXAz <= 0.29) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( AyXGy <= 0.09) {
													return 2;
												}
												else {
													if ( Gy <= -0.24) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( AxXAy <= -0.05) {
											if ( AxXAy <= -0.32) {
												if ( AzXGx <= -0.01) {
													if ( AyXAz <= -0.85) {
														return 2;
													}
													else {
														if ( Ay <= -0.64) {
															if ( Gy <= -0.28) {
																return 0;
															}
															else {
																if ( Gx_squared <= -0.12) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( GxXGz <= 0.01) {
														return 2;
													}
													else {
														if ( AzXGz <= 0.0) {
															if ( AyXAz <= -0.54) {
																return 2;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( GxXGy <= 0.02) {
													if ( AyXAz <= -0.45) {
														if ( Gx <= -0.23) {
															return 2;
														}
														else {
															if ( Gz_squared <= -0.13) {
																return 1;
															}
															else {
																if ( AzXGx <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Ay_squared <= 0.09) {
															if ( Gz <= -0.28) {
																if ( AxXAy <= -0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AyXAz <= -1.01) {
														return 1;
													}
													else {
														if ( AyXAz <= -0.72) {
															return 2;
														}
														else {
															if ( AyXGz <= 0.14) {
																return 2;
															}
															else {
																if ( AxXAz <= 0.18) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AyXAz <= -0.42) {
												if ( AyXGy <= 0.15) {
													if ( Ay <= -0.7) {
														return 2;
													}
													else {
														if ( Ay <= -0.62) {
															if ( AxXAz <= 0.07) {
																if ( AzXGx <= -0.01) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXGx <= -0.02) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXAz <= -0.92) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AzXGx <= -0.04) {
														if ( AyXGz <= 0.16) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Ax_squared <= -0.15) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( AzXGy <= 0.0) {
								if ( GyXGz <= -0.02) {
									if ( Gz_squared <= -0.12) {
										if ( AxXAz <= -0.15) {
											return 0;
										}
										else {
											if ( Az <= 1.59) {
												if ( Ax_squared <= 0.07) {
													if ( AyXGx <= 0.04) {
														return 0;
													}
													else {
														if ( Ay <= -0.7) {
															return 2;
														}
														else {
															if ( AxXAy <= 0.6) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXAz <= -0.13) {
													return 1;
												}
												else {
													if ( Gx <= -0.09) {
														if ( AyXAz <= -0.72) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( Gx <= -0.46) {
										return 0;
									}
									else {
										if ( AxXAz <= -0.16) {
											return 2;
										}
										else {
											if ( GyXGz <= -0.01) {
												if ( Gy_squared <= -0.15) {
													return 2;
												}
												else {
													if ( AxXGz <= 0.02) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( AxXAz <= -0.4) {
									return 0;
								}
								else {
									if ( Gx_squared <= -0.13) {
										return 0;
									}
									else {
										if ( Gz <= -0.53) {
											return 2;
										}
										else {
											if ( AyXGz <= 0.19) {
												if ( Ax <= -1.58) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( AyXGx <= -0.51) {
							if ( AyXGx <= -1.3) {
								return 0;
							}
							else {
								if ( Ay <= -0.63) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( AxXAy <= -0.44) {
								if ( GyXGz <= -0.2) {
									return 1;
								}
								else {
									if ( Gy <= 0.5) {
										if ( GxXGy <= -0.0) {
											if ( AzXGy <= -0.21) {
												return 2;
											}
											else {
												if ( AyXGy <= 0.42) {
													if ( Gz_squared <= -0.13) {
														return 0;
													}
													else {
														if ( Gz_squared <= -0.12) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AzXGz <= -0.0) {
												if ( AzXGx <= 0.04) {
													if ( AyXAz <= -0.48) {
														return 0;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXAz <= -1.22) {
														return 2;
													}
													else {
														if ( GxXGz <= -0.06) {
															return 0;
														}
														else {
															if ( Ay_squared <= -0.4) {
																return 2;
															}
															else {
																if ( Gy_squared <= -0.15) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( GyXGz <= -0.46) {
									return 2;
								}
								else {
									if ( AzXGx <= 0.03) {
										if ( GyXGz <= -0.02) {
											if ( GxXGz <= 0.01) {
												return 2;
											}
											else {
												return 0;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gz_squared <= -0.12) {
											if ( Gx_squared <= -0.13) {
												if ( Gy_squared <= -0.14) {
													if ( AxXAy <= -0.12) {
														return 0;
													}
													else {
														if ( Gx_squared <= -0.13) {
															return 0;
														}
														else {
															if ( AyXAz <= -1.06) {
																return 2;
															}
															else {
																if ( AxXAy <= -0.06) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AyXGx <= -0.05) {
														if ( AzXGx <= 0.05) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AzXGz <= -0.03) {
													if ( AxXAy <= -0.14) {
														return 0;
													}
													else {
														if ( Gy <= 0.17) {
															return 0;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( GxXGy <= 0.02) {
														if ( AyXAz <= -0.44) {
															if ( AxXGy <= 0.01) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AyXGz <= 0.55) {
												if ( AzXGx <= 0.23) {
													if ( AyXGx <= -0.18) {
														if ( AxXGz <= -0.01) {
															if ( AxXAz <= 0.12) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GxXGz <= -0.01) {
															return 2;
														}
														else {
															if ( AzXGy <= 0.06) {
																if ( AzXGz <= -0.11) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( AxXAy <= -1.03) {
						if ( Az_squared <= -0.2) {
							if ( GxXGz <= 0.01) {
								if ( Gy_squared <= -0.14) {
									return 1;
								}
								else {
									return 0;
								}
							}
							else {
								if ( AzXGx <= 0.04) {
									if ( Gy <= -0.15) {
										return 0;
									}
									else {
										if ( AxXAy <= -1.31) {
											return 1;
										}
										else {
											return 2;
										}
									}
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( AxXAy <= -1.17) {
								if ( Ay_squared <= -0.53) {
									return 0;
								}
								else {
									if ( Az <= 2.06) {
										return 0;
									}
									else {
										return 0;
									}
								}
							}
							else {
								return 0;
							}
						}
					}
					else {
						if ( Az <= 2.06) {
							if ( GxXGz <= 0.01) {
								if ( Gx <= 0.1) {
									if ( Ay <= -0.87) {
										if ( AxXGx <= 0.07) {
											return 0;
										}
										else {
											return 1;
										}
									}
									else {
										if ( AxXGy <= 0.21) {
											if ( AxXAy <= 0.94) {
												if ( Gz_squared <= -0.06) {
													if ( AxXGx <= -0.05) {
														if ( AyXAz <= -0.48) {
															if ( GyXGz <= -0.04) {
																return 0;
															}
															else {
																if ( Az <= 1.52) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Gx_squared <= -0.13) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AyXAz <= -0.45) {
															if ( GxXGz <= 0.01) {
																if ( AxXGx <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXAz <= -0.58) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAy <= 0.56) {
																if ( AxXAy <= 0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gz_squared <= -0.13) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													if ( AxXAz <= 0.32) {
														if ( GyXGz <= 0.07) {
															if ( Gz_squared <= 0.04) {
																if ( AzXGz <= 0.3) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AzXGz <= 0.44) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXGx <= -0.39) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( AzXGz <= 0.03) {
													if ( AyXAz <= -0.41) {
														if ( Gy_squared <= -0.15) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( GyXGz <= -0.02) {
										if ( AxXGx <= 0.09) {
											if ( AzXGy <= -0.06) {
												return 0;
											}
											else {
												if ( AzXGx <= 0.04) {
													return 0;
												}
												else {
													if ( AyXGx <= -0.24) {
														return 0;
													}
													else {
														if ( AzXGx <= 0.04) {
															return 2;
														}
														else {
															if ( Az <= 1.67) {
																if ( AxXGy <= 0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AxXGz <= -0.04) {
											return 0;
										}
										else {
											if ( AyXAz <= -0.7) {
												return 2;
											}
											else {
												if ( Ay <= -0.69) {
													if ( GxXGy <= -0.0) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AzXGx <= 0.06) {
														if ( AzXGx <= 0.05) {
															if ( GxXGz <= 0.01) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( AyXGx <= -0.22) {
									if ( AyXGx <= -0.63) {
										return 0;
									}
									else {
										if ( AxXGz <= 0.44) {
											if ( AxXAy <= -0.63) {
												return 0;
											}
											else {
												if ( GxXGy <= 0.06) {
													if ( AxXGy <= 0.03) {
														if ( Gy_squared <= -0.15) {
															return 2;
														}
														else {
															if ( AyXGz <= -0.01) {
																if ( GyXGz <= -0.07) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Gz <= 1.04) {
										if ( Gy_squared <= -0.14) {
											if ( Gx <= 0.13) {
												if ( AxXAz <= -0.02) {
													if ( Az <= 1.38) {
														return 2;
													}
													else {
														if ( AxXAz <= -0.16) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( AyXGy <= 0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AyXGx <= 0.14) {
														if ( Ax <= -1.18) {
															return 1;
														}
														else {
															if ( GxXGz <= 0.01) {
																if ( Az <= 1.48) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAy <= -0.26) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( AxXAy <= -0.59) {
													return 0;
												}
												else {
													if ( Az <= 1.74) {
														if ( Az <= 1.59) {
															if ( AzXGz <= 0.08) {
																if ( GxXGz <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AzXGz <= -0.01) {
												return 2;
											}
											else {
												if ( Gy <= -0.1) {
													if ( AxXGy <= -0.17) {
														return 0;
													}
													else {
														if ( Gx <= -0.39) {
															return 2;
														}
														else {
															if ( Ax_squared <= 0.05) {
																if ( GyXGz <= -0.02) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gx_squared <= -0.13) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AzXGx <= -0.04) {
														return 2;
													}
													else {
														if ( GxXGy <= -0.0) {
															return 0;
														}
														else {
															if ( AxXAz <= 0.13) {
																if ( Ay <= -0.61) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAy <= -0.49) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AzXGz <= 0.27) {
											if ( AyXGz <= -0.8) {
												return 2;
											}
											else {
												if ( AxXGz <= 0.58) {
													if ( AzXGz <= 0.16) {
														if ( AxXGx <= -0.0) {
															return 2;
														}
														else {
															if ( AzXGz <= 0.15) {
																if ( AxXGx <= 0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AxXAy <= -0.6) {
															if ( Ay_squared <= 0.01) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXGz <= 0.31) {
																if ( AxXGz <= 0.17) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GxXGy <= 0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( GxXGy <= 0.01) {
												if ( AxXAz <= -0.27) {
													return 0;
												}
												else {
													if ( Ax_squared <= -0.13) {
														if ( AyXGz <= -0.65) {
															if ( AzXGx <= 0.08) {
																if ( Gz_squared <= 0.16) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GyXGz <= -0.12) {
															if ( AyXGz <= -0.68) {
																if ( AyXGz <= -0.79) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXGy <= -0.07) {
																if ( Ax <= 0.74) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= -0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXGx <= 0.44) {
								if ( GxXGz <= -0.11) {
									if ( AxXAz <= -0.28) {
										return 2;
									}
									else {
										return 2;
									}
								}
								else {
									if ( Ax <= 0.97) {
										if ( Ax <= -1.46) {
											if ( AxXGx <= 0.04) {
												if ( Ay <= -0.57) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( GxXGy <= 0.01) {
												if ( Gx <= 0.18) {
													if ( AzXGz <= 0.6) {
														if ( AyXAz <= -1.0) {
															if ( AyXAz <= -1.14) {
																if ( Ay_squared <= -0.35) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXGx <= -0.09) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXAz <= 0.15) {
																if ( AxXAy <= 0.55) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXGz <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( GxXGy <= 0.01) {
														if ( Gy_squared <= -0.11) {
															if ( GxXGz <= 0.01) {
																return 2;
															}
															else {
																if ( AyXGx <= -0.13) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gz_squared <= -0.1) {
													if ( AxXGx <= 0.07) {
														if ( Gz <= -0.22) {
															return 2;
														}
														else {
															if ( AxXGy <= 0.02) {
																if ( AxXGy <= -0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gx <= -0.12) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( Gx <= -0.0) {
											if ( GyXGz <= -0.02) {
												if ( AyXAz <= -1.14) {
													return 2;
												}
												else {
													if ( AyXGz <= 0.04) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gz_squared <= -0.13) {
												return 0;
											}
											else {
												if ( AyXAz <= -1.14) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
							else {
								if ( Ay <= -0.57) {
									return 2;
								}
								else {
									return 1;
								}
							}
						}
					}
				}
			}
			else {
				if ( AxXAz <= 0.11) {
					if ( GxXGz <= 0.0) {
						if ( GxXGz <= -0.41) {
							return 0;
						}
						else {
							if ( Gz <= 0.66) {
								if ( AxXAz <= -0.0) {
									return 0;
								}
								else {
									return 0;
								}
							}
							else {
								return 2;
							}
						}
					}
					else {
						if ( Gz <= -3.13) {
							return 2;
						}
						else {
							if ( GxXGz <= 0.28) {
								if ( GxXGy <= -0.01) {
									if ( AzXGz <= 0.18) {
										if ( AyXGx <= -0.35) {
											return 0;
										}
										else {
											if ( AxXGx <= -0.04) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									return 0;
								}
							}
							else {
								return 0;
							}
						}
					}
				}
				else {
					if ( GyXGz <= 1.06) {
						if ( GyXGz <= -0.09) {
							if ( Gx_squared <= 0.02) {
								if ( GxXGz <= -0.15) {
									return 2;
								}
								else {
									if ( AxXGy <= -0.67) {
										return 0;
									}
									else {
										if ( Gx_squared <= -0.13) {
											return 0;
										}
										else {
											if ( Ay <= -0.64) {
												return 0;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( AzXGx <= 0.28) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( AyXGy <= 0.77) {
								if ( Ax <= 0.69) {
									if ( AxXAz <= 0.19) {
										return 0;
									}
									else {
										return 2;
									}
								}
								else {
									if ( AyXGx <= -0.78) {
										return 0;
									}
									else {
										if ( AyXGy <= -0.96) {
											return 0;
										}
										else {
											if ( GyXGz <= -0.06) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
							}
							else {
								if ( Ax <= 1.65) {
									if ( Gx_squared <= -0.07) {
										return 0;
									}
									else {
										if ( AxXAz <= 0.32) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									return 0;
								}
							}
						}
					}
					else {
						if ( Gx_squared <= 0.1) {
							return 1;
						}
						else {
							if ( AxXGy <= 2.38) {
								return 0;
							}
							else {
								return 0;
							}
						}
					}
				}
			}
		}
		else {
			if ( AxXAz <= 0.21) {
				if ( Gz_squared <= -0.12) {
					if ( AyXAz <= -0.19) {
						return 0;
					}
					else {
						if ( AyXAz <= 0.59) {
							if ( GxXGy <= 0.01) {
								if ( AxXAy <= 0.04) {
									return 0;
								}
								else {
									if ( AyXGy <= -0.03) {
										if ( Gy <= -0.26) {
											return 0;
										}
										else {
											if ( AxXAz <= 0.18) {
												if ( AzXGz <= 0.05) {
													if ( AzXGz <= 0.04) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Ax_squared <= -0.15) {
											return 1;
										}
										else {
											if ( AzXGz <= 0.01) {
												return 0;
											}
											else {
												if ( Gy_squared <= -0.13) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
							else {
								if ( Az <= 1.67) {
									if ( GxXGy <= 0.07) {
										if ( Gz_squared <= -0.13) {
											if ( Gx <= -0.16) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gz_squared <= -0.13) {
												if ( AzXGx <= 0.05) {
													if ( Gy_squared <= -0.13) {
														if ( AzXGy <= -0.05) {
															return 1;
														}
														else {
															if ( AyXGz <= 0.1) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										return 0;
									}
								}
								else {
									if ( AyXGy <= -0.01) {
										return 0;
									}
									else {
										if ( AxXGy <= 0.01) {
											return 1;
										}
										else {
											if ( Gy_squared <= -0.15) {
												return 1;
											}
											else {
												if ( Gy <= 0.01) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
						}
						else {
							return 2;
						}
					}
				}
				else {
					if ( Gx_squared <= -0.1) {
						if ( AzXGy <= -0.1) {
							if ( Az_squared <= -0.07) {
								return 2;
							}
							else {
								return 0;
							}
						}
						else {
							if ( Ay_squared <= -0.52) {
								return 0;
							}
							else {
								if ( GyXGz <= -0.05) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
					}
					else {
						if ( Gz_squared <= 2.16) {
							if ( Az_squared <= -0.25) {
								return 1;
							}
							else {
								if ( Gz_squared <= -0.1) {
									return 1;
								}
								else {
									if ( GyXGz <= -0.39) {
										return 0;
									}
									else {
										if ( Gz <= 1.06) {
											if ( AyXAz <= 0.07) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
								}
							}
						}
						else {
							return 1;
						}
					}
				}
			}
			else {
				if ( Gx_squared <= -0.13) {
					return 0;
				}
				else {
					if ( Gx_squared <= -0.13) {
						if ( Gx <= -0.14) {
							return 2;
						}
						else {
							if ( Ay_squared <= -1.28) {
								return 1;
							}
							else {
								if ( AxXGz <= 0.08) {
									if ( Ay <= 1.37) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( GxXGy <= -5.44) {
							return 1;
						}
						else {
							if ( Gz <= -1.13) {
								if ( Gx_squared <= 0.05) {
									return 0;
								}
								else {
									if ( Ay <= 2.03) {
										if ( AyXAz <= 0.33) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AyXGz <= -0.29) {
									return 1;
								}
								else {
									if ( Gz_squared <= -0.13) {
										if ( GxXGy <= -0.0) {
											return 0;
										}
										else {
											if ( AxXAy <= 1.14) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AxXGz <= 0.82) {
											if ( Gy_squared <= -0.15) {
												return 1;
											}
											else {
												if ( Gy_squared <= 0.45) {
													if ( Az <= 3.39) {
														if ( Ay <= 1.28) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.1) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
