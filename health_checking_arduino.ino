#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const int chipSelect = 53;  // Chip select pin for the SD card module

#define MAX_COLS 6
#define MAX_ROWS 200  //200 for the estrus and it will take 18 round to get one data which is equalivalent to 4 hours
#define MAX_FIELD_LENGTH 50
#define MAX_SIZE 15

float field[MAX_ROWS][MAX_COLS];

unsigned int numberZero = 0;  //only reset to 0 if the data are equal to one day
unsigned int numberOne = 0;   //Store how many 1's in the data
unsigned int num = 0;
bool FirstTurn = 1;
unsigned int check_First_two_day = 0;

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
    Serial.println(node->data);
    node = node->next;
  }
  //printf("\n");
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
  int* arr;         // Array to store queue elements
  int front, rear;  // Front and rear pointers
  int capacity;     // Maximum capacity of the queue
  int size;         // Current number of elements in the queue
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
int indexFinding(struct CircularQueue* queue, int no) {
  int i = queue->front;
  int count = 0;
  while (count < queue->size) {
    if (count == no) {
      return queue->arr[i];
      break;
    }
    i = (i + 1) % queue->capacity;
    count++;
  }
}

int Health(float, float, float, float, float, float);
int CompareData(int, int, int);

struct CircularQueue* total_one_day_count = createQueue(MAX_SIZE);
struct Node* result_data = NULL;

void setup() {
  Serial.begin(9600);

  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);  // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);
}

void loop() {
  // Nothing to do in the loop for this example
  if (num == 4 && FirstTurn == 1) {  //108
    //need condition to put it into the double linked list array
    enqueue(total_one_day_count, numberOne);
    Serial.print("the total number one is");
    Serial.println(numberOne);
    numberOne = 0;
    numberZero = 0;
    num = 0;
    check_First_two_day += 1;
    Serial.print("Complete ");
    Serial.print(check_First_two_day);
    Serial.println(" Turn");

      if (check_First_two_day == 3) {
      FirstTurn = 0;
      Serial.print("The result of compared data is ");
      Serial.println(CompareData(indexFinding(total_one_day_count, 0), indexFinding(total_one_day_count, 1), indexFinding(total_one_day_count, 2)));
      insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count, 0), indexFinding(total_one_day_count, 1), indexFinding(total_one_day_count, 2)));
    }

  } else if (num == 4 && FirstTurn == 0) {  //108
    dequeue(total_one_day_count);
    //printQueue(total_one_day_count);
    enqueue(total_one_day_count, numberOne);
    //printQueue(total_one_day_count);
    Serial.print("The result of compared data is ");
    Serial.println(CompareData(indexFinding(total_one_day_count, 0), indexFinding(total_one_day_count, 1), indexFinding(total_one_day_count, 2)));

    insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count, 0), indexFinding(total_one_day_count, 1), indexFinding(total_one_day_count, 2)));
    numberOne = 0;
    numberZero = 0;
    num = 0;
    //break;
  } else {
    for (int i = 0; i < 200; i++) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      field[i][0] = a.acceleration.x;
      field[i][1] = a.acceleration.y;
      field[i][2] = a.acceleration.z;
      field[i][3] = g.gyro.x;
      field[i][4] = g.gyro.y;
      field[i][5] = g.gyro.z;
      delay(400);
    }
    for (int i = 0; i < 200; i++) {
      Serial.print(field[i][0]);
      Serial.print(" ");
      Serial.print(field[i][1]);
      Serial.print(" ");
      Serial.print(field[i][2]);
      Serial.print(" ");
      Serial.print(field[i][3]);
      Serial.print(" ");
      Serial.print(field[i][4]);
      Serial.print(" ");
      Serial.println(field[i][5]);
    }
    for (int j = 0; j < 200; j++) {
      float ax, ay, az, gx, gy, gz;
      ax = field[j][0];
      ay = field[j][1];
      az = field[j][2];
      gx = field[j][3];
      gy = field[j][4];
      gz = field[j][5];
      if (Health(ax, ay, az, gx, gy, gz)== 1 || Health(ax, ay, az, gx, gy, gz) == 2) {
        numberOne = numberOne + 1;
      } else {
        numberZero = numberZero + 1;
      }
    }
    for (int x = 0; x < 200; x++) {
      for (int i = 0; i < 6; i++) {
        field[x][i] = 0;
      }
    }
    num += 1;
    Serial.print(num);
    Serial.println("time finish for one round");
  }
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
    return 1;                                        //Warning
  } else {
    return 0;  //OK
    //But have to ask the condition first
  }
}
//RUMINATING and Sitting
int Health(float Ax, float Ay, float Az, float Gx, float Gy, float Gz) {
  float AxXGx = Ax * Gx, AyXAz = Ay * Az, AxXGy = Ax * Gy, AxXGz = Ax * Gz, AxXAy = Ax * Ay, AxXAz = Ax * Az, AyXAx = Ay * Ax, AyXGx = Ay * Gx, AyXGy = Ay * Gy, AyXGz = Ay * Gz, AzXAx = Az * Ax, AzXAy = Az * Ay, AzXGx = Az * Gx, AzxGy = Az * Gy, AzXGz = Az * Gz, Ax_squared = Ax * Ax, Ay_squared = Ay * Ay, Az_squared = Az * Az, Gx_squared = Gx * Gx, Gy_squared = Gy * Gy, Gz_squared = Gz * Gz, GxXGz = Gx * Gz, GxXGy = Gx * Gy, GyXGz = Gy * Gz, AzXGy = Az * Gy;
  if (Ay <= -0.59) {
    if (Az <= 0.32) {
      if (AyXGz <= -0.43) {
        if (Gy_squared <= -0.04) {
          if (Ay <= -0.79) {
            if (GxXGz <= -0.52) {
              if (Az <= -0.04) {
                return 1;
              } else {
                return 0;
              }
            } else {
              if (AzXGz <= -0.3) {
                if (Gz <= 1.93) {
                  if (AyXGz <= -1.1) {
                    return 0;
                  } else {
                    if (Az <= -0.22) {
                      if (AzXGy <= -0.24) {
                        return 0;
                      } else {
                        if (AzXGz <= -0.36) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 2;
                    }
                  }
                } else {
                  return 0;
                }
              } else {
                if (AxXAy <= -0.43) {
                  return 0;
                } else {
                  if (Gz <= 1.1) {
                    if (AxXAz <= -0.02) {
                      return 2;
                    } else {
                      if (AxXGz <= 0.06) {
                        if (AzXGz <= -0.25) {
                          return 0;
                        } else {
                          return 2;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 2;
                  }
                }
              }
            }
          } else {
            if (AzXGz <= -0.35) {
              if (AyXGy <= -0.16) {
                if (AxXGz <= 0.54) {
                  if (AzXGx <= 0.07) {
                    if (AzXGy <= -0.27) {
                      return 2;
                    } else {
                      return 0;
                    }
                  } else {
                    if (Gy <= 0.39) {
                      return 2;
                    } else {
                      if (Ay <= -0.67) {
                        return 2;
                      } else {
                        return 1;
                      }
                    }
                  }
                } else {
                  return 0;
                }
              } else {
                if (AzXGz <= -0.5) {
                  if (Gz_squared <= 0.36) {
                    if (AxXAy <= 0.08) {
                      if (AxXAz <= -0.34) {
                        return 0;
                      } else {
                        if (AyXGx <= 0.16) {
                          if (AyXAz <= 0.62) {
                            return 2;
                          } else {
                            if (Ay_squared <= -0.09) {
                              return 0;
                            } else {
                              if (AxXGy <= -0.06) {
                                return 0;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (Gy <= -0.4) {
                        return 0;
                      } else {
                        if (Gy_squared <= -0.15) {
                          return 0;
                        } else {
                          if (Gz_squared <= 0.16) {
                            if (Gz <= 1.14) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (Gz <= 1.41) {
                    if (GxXGz <= 0.03) {
                      if (Gy <= -0.52) {
                        return 0;
                      } else {
                        if (Gy <= -0.37) {
                          return 2;
                        } else {
                          if (AyXAz <= 0.75) {
                            if (GxXGy <= 0.07) {
                              if (GxXGy <= 0.04) {
                                if (AyXAz <= 0.55) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    } else {
                      if (AxXGy <= 0.01) {
                        if (Ay <= -0.63) {
                          if (Gz <= 1.12) {
                            return 2;
                          } else {
                            if (AxXGx <= 0.04) {
                              if (GxXGy <= -0.01) {
                                return 2;
                              } else {
                                if (AxXAy <= -0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AxXAy <= 0.38) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= -0.88) {
                      return 0;
                    } else {
                      return 2;
                    }
                  }
                }
              }
            } else {
              if (GxXGy <= 0.01) {
                if (GyXGz <= -0.08) {
                  if (GxXGy <= -0.02) {
                    if (AyXGz <= -0.63) {
                      return 2;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AxXAy <= -0.43) {
                      if (Gz_squared <= 0.07) {
                        return 2;
                      } else {
                        if (AyXAz <= 0.17) {
                          return 2;
                        } else {
                          if (AxXAy <= -0.59) {
                            return 2;
                          } else {
                            if (AxXGz <= 0.34) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    } else {
                      if (AzXGz <= -0.25) {
                        if (Ay <= -0.67) {
                          if (Gx_squared <= -0.13) {
                            return 2;
                          } else {
                            if (Gx <= 0.25) {
                              if (AyXGy <= 0.19) {
                                return 2;
                              } else {
                                if (GxXGy <= -0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (AxXGz <= 0.32) {
                          if (AzXGz <= -0.15) {
                            if (AxXGz <= 0.3) {
                              if (GxXGy <= 0.0) {
                                if (Ax_squared <= -0.13) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      }
                    }
                  }
                } else {
                  if (AxXAy <= -0.66) {
                    return 0;
                  } else {
                    if (AxXAz <= 0.18) {
                      if (Ay <= -0.64) {
                        if (Ay_squared <= 0.15) {
                          if (Gz_squared <= 0.0) {
                            if (Gy_squared <= -0.08) {
                              if (GxXGz <= -0.07) {
                                if (AxXAz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            if (Gy <= 0.11) {
                              if (GxXGy <= -0.0) {
                                return 2;
                              } else {
                                if (AxXGz <= 0.23) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Gx_squared <= -0.08) {
                                return 0;
                              } else {
                                if (AxXGz <= 0.2) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          if (Gz <= 0.9) {
                            if (AzXGx <= 0.15) {
                              return 0;
                            } else {
                              if (AxXGx <= -0.22) {
                                return 2;
                              } else {
                                if (AyXGx <= 0.59) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (Gx <= 0.07) {
                              if (Gy <= 0.45) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (GxXGz <= -0.23) {
                          return 2;
                        } else {
                          if (Az <= -0.26) {
                            return 2;
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (Gy <= 0.2) {
                  if (AxXGx <= 0.11) {
                    if (AxXAz <= -0.18) {
                      return 0;
                    } else {
                      if (AyXGy <= 0.04) {
                        if (AxXAy <= -0.18) {
                          if (AxXGz <= 0.22) {
                            if (Gx_squared <= 0.02) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (AzXGz <= -0.23) {
                            return 2;
                          } else {
                            if (AzXGz <= -0.2) {
                              return 0;
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (AxXAy <= -0.44) {
                          return 0;
                        } else {
                          if (AxXGy <= 0.04) {
                            if (AxXGx <= -0.1) {
                              if (GxXGz <= -0.29) {
                                return 2;
                              } else {
                                if (GxXGz <= -0.24) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AxXGx <= -0.05) {
                                return 0;
                              } else {
                                if (Gy_squared <= -0.14) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (AyXGz <= -0.6) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              }
            }
          }
        } else {
          if (AzXGz <= -0.15) {
            if (AxXGz <= -0.35) {
              if (Az_squared <= -0.11) {
                return 1;
              } else {
                if (Gx_squared <= 0.34) {
                  return 0;
                } else {
                  if (Gx <= -2.57) {
                    if (Gx_squared <= 1.88) {
                      return 0;
                    } else {
                      return 1;
                    }
                  } else {
                    return 1;
                  }
                }
              }
            } else {
              if (Gy_squared <= 0.31) {
                if (AxXAz <= 0.04) {
                  if (Gx_squared <= 0.32) {
                    if (GxXGy <= -0.29) {
                      return 0;
                    } else {
                      if (Ay_squared <= 0.09) {
                        if (AzXGy <= 0.19) {
                          if (Gy_squared <= 0.0) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AzXGz <= -0.23) {
                          if (AxXAz <= -0.54) {
                            return 0;
                          } else {
                            if (Az_squared <= 0.06) {
                              if (Gy_squared <= 0.18) {
                                if (AyXGx <= -0.26) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= -1.21) {
                      return 0;
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (Gz <= 0.87) {
                    return 0;
                  } else {
                    if (Gy_squared <= 0.04) {
                      return 2;
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (AzXGy <= -1.69) {
                  if (AxXAz <= -0.34) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  if (Az_squared <= -0.09) {
                    if (Gx <= -0.61) {
                      return 0;
                    } else {
                      if (AyXAz <= 0.52) {
                        if (Gx_squared <= -0.12) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (Az <= -1.24) {
                      if (GyXGz <= -11.92) {
                        return 1;
                      } else {
                        return 0;
                      }
                    } else {
                      if (AxXGy <= 0.19) {
                        if (AxXGz <= 0.3) {
                          return 1;
                        } else {
                          return 0;
                        }
                      } else {
                        if (AxXGz <= 0.4) {
                          return 0;
                        } else {
                          return 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (Gy_squared <= 0.05) {
              return 2;
            } else {
              return 0;
            }
          }
        }
      } else {
        if (Ax_squared <= -0.12) {
          if (AzXGy <= -0.12) {
            if (AzXGy <= -0.22) {
              if (Gy_squared <= 0.07) {
                if (Gz_squared <= -0.11) {
                  if (Az <= -0.33) {
                    if (Ay <= -0.8) {
                      return 0;
                    } else {
                      if (AxXAz <= 0.03) {
                        if (GxXGz <= 0.0) {
                          if (Gx_squared <= -0.12) {
                            return 2;
                          } else {
                            return 1;
                          }
                        } else {
                          if (AxXGx <= -0.01) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AyXGx <= -0.4) {
                          return 0;
                        } else {
                          if (Gz <= -0.19) {
                            if (GyXGz <= -0.05) {
                              return 1;
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXGy <= -0.01) {
                              if (AxXAy <= 0.34) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Ay_squared <= 0.07) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (GxXGz <= 0.05) {
                      if (Gz_squared <= -0.13) {
                        return 0;
                      } else {
                        if (Gz <= 0.16) {
                          if (GyXGz <= 0.01) {
                            if (Gz_squared <= -0.13) {
                              return 1;
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (AzXGz <= 0.49) {
                    if (AzXGx <= -0.06) {
                      if (Gz <= -1.31) {
                        return 1;
                      } else {
                        if (GxXGz <= -0.03) {
                          return 0;
                        } else {
                          if (GyXGz <= 0.09) {
                            return 2;
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AyXGy <= -0.63) {
                        return 0;
                      } else {
                        if (AxXGz <= -0.03) {
                          return 0;
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    return 0;
                  }
                }
              } else {
                if (AyXGx <= 0.36) {
                  if (Gz <= -2.11) {
                    return 0;
                  } else {
                    if (AyXAz <= 0.29) {
                      return 0;
                    } else {
                      if (Az_squared <= 0.27) {
                        if (Az <= -0.73) {
                          return 0;
                        } else {
                          if (Gz_squared <= -0.11) {
                            if (Az <= -0.48) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            if (AyXGy <= -1.18) {
                              return 1;
                            } else {
                              return 0;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (Gz <= 0.11) {
                    if (AxXGz <= -0.01) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    return 0;
                  }
                }
              }
            } else {
              if (GyXGz <= 0.09) {
                if (GyXGz <= -0.42) {
                  if (Gz <= -2.39) {
                    return 1;
                  } else {
                    return 2;
                  }
                } else {
                  if (AyXGx <= 0.25) {
                    if (Az_squared <= -0.04) {
                      if (AyXAz <= 0.24) {
                        if (Gy_squared <= -0.05) {
                          return 1;
                        } else {
                          return 1;
                        }
                      } else {
                        if (AzXGz <= 0.13) {
                          if (Gx <= 0.69) {
                            if (AyXGy <= -0.39) {
                              if (AxXGx <= -0.01) {
                                return 0;
                              } else {
                                if (Gy_squared <= -0.09) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (Ay_squared <= -0.04) {
                                return 0;
                              } else {
                                if (AyXAz <= 0.34) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (Ay <= -0.72) {
                              return 2;
                            } else {
                              if (AyXAz <= 0.46) {
                                return 1;
                              } else {
                                return 0;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (GyXGz <= -0.03) {
                        if (Gy <= 0.46) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        if (GxXGz <= 0.04) {
                          if (Az_squared <= 0.22) {
                            if (Ax_squared <= -0.15) {
                              if (AxXAz <= 0.11) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= 0.31) {
                      if (Gz <= 0.05) {
                        if (Ay_squared <= -0.01) {
                          return 2;
                        } else {
                          return 1;
                        }
                      } else {
                        if (AzXGx <= 0.21) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                return 2;
              }
            }
          } else {
            if (GxXGz <= -0.0) {
              if (AzXGy <= 0.17) {
                if (AzXGx <= -0.09) {
                  if (AyXAz <= 0.25) {
                    if (GxXGy <= -0.04) {
                      if (Gz_squared <= 0.0) {
                        if (Gz_squared <= -0.06) {
                          return 1;
                        } else {
                          if (AzXGx <= -0.2) {
                            if (GxXGz <= -0.27) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        return 1;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (AzXGz <= 0.43) {
                      if (AyXGz <= 0.59) {
                        if (Gz_squared <= -0.06) {
                          if (Gy <= 0.03) {
                            if (AyXGx <= -0.62) {
                              if (AyXAz <= 0.42) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gx_squared <= -0.08) {
                                if (AxXAz <= 0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            if (GxXGz <= -0.01) {
                              if (AxXGy <= 0.0) {
                                return 1;
                              } else {
                                return 0;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AyXGx <= -0.89) {
                            return 1;
                          } else {
                            if (Gy <= -0.51) {
                              return 2;
                            } else {
                              if (GxXGy <= -0.11) {
                                if (Gx_squared <= 0.13) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      } else {
                        if (AyXAz <= 0.38) {
                          if (GxXGz <= -0.31) {
                            return 1;
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (AyXGz <= -0.35) {
                    if (GxXGz <= -0.1) {
                      if (AzXGx <= 0.51) {
                        if (Ay <= -0.71) {
                          return 2;
                        } else {
                          if (Ay <= -0.64) {
                            return 2;
                          } else {
                            return 2;
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      return 1;
                    }
                  } else {
                    if (Gz <= -0.67) {
                      if (Gy_squared <= -0.15) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      if (Ay_squared <= -0.01) {
                        if (AyXGx <= 0.3) {
                          if (AxXAz <= 0.01) {
                            return 0;
                          } else {
                            if (AzXGz <= -0.08) {
                              return 1;
                            } else {
                              if (Gy_squared <= -0.14) {
                                return 1;
                              } else {
                                if (Gz_squared <= -0.12) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        } else {
                          if (Az <= -0.15) {
                            return 1;
                          } else {
                            if (GxXGz <= -0.03) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        }
                      } else {
                        if (AzXGy <= 0.07) {
                          if (AyXAz <= 0.39) {
                            if (AzXGx <= 0.15) {
                              if (AxXGx <= 0.01) {
                                if (AzXGz <= 0.12) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              if (Ay <= -0.71) {
                                return 2;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Gx_squared <= -0.03) {
                              if (AzXGz <= -0.12) {
                                return 1;
                              } else {
                                if (GyXGz <= -0.01) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (Gx_squared <= -0.11) {
                            if (Gz <= 0.04) {
                              return 0;
                            } else {
                              return 1;
                            }
                          } else {
                            if (Ax_squared <= -0.14) {
                              return 0;
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (Ay_squared <= 0.27) {
                  if (Gx_squared <= -0.12) {
                    if (GxXGz <= -0.01) {
                      return 1;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AzXGy <= 1.04) {
                      if (AxXGz <= -0.06) {
                        return 0;
                      } else {
                        if (Ax_squared <= -0.13) {
                          if (Gy <= -1.47) {
                            return 0;
                          } else {
                            if (AxXAz <= 0.15) {
                              if (AzXGy <= 0.45) {
                                if (AyXGx <= 0.6) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          return 1;
                        }
                      }
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (AyXAz <= 1.38) {
                    if (AxXGx <= -0.06) {
                      return 0;
                    } else {
                      if (Gy <= -0.95) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 1;
                  }
                }
              }
            } else {
              if (GyXGz <= 1.39) {
                if (AyXGx <= -0.1) {
                  if (AyXAz <= 0.67) {
                    if (AxXGy <= 0.01) {
                      if (Ay <= -0.65) {
                        if (Gy <= -0.59) {
                          if (AzXGx <= -0.09) {
                            return 0;
                          } else {
                            return 2;
                          }
                        } else {
                          if (GyXGz <= -0.03) {
                            if (GyXGz <= -0.04) {
                              if (Az <= -0.04) {
                                if (AxXAz <= 0.05) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXGz <= -0.15) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXAz <= 0.34) {
                                if (AyXGx <= -0.19) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Gy <= -0.36) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (GxXGz <= 0.03) {
                              if (Gy <= 0.06) {
                                if (AxXGx <= 0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXAz <= 0.27) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXGy <= -0.16) {
                                if (AyXGx <= -0.44) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Az <= 0.03) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Gy <= -0.91) {
                          return 2;
                        } else {
                          if (AxXGz <= -0.01) {
                            if (Gy_squared <= -0.15) {
                              if (AxXGz <= -0.02) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (AzXGx <= -0.09) {
                                if (Az <= -0.51) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.03) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (GxXGy <= 0.0) {
                              return 0;
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    } else {
                      if (Az_squared <= -0.09) {
                        if (AxXGx <= 0.02) {
                          if (Ay_squared <= -0.04) {
                            if (AyXAz <= 0.2) {
                              return 1;
                            } else {
                              if (Az_squared <= -0.12) {
                                if (AzXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Gy <= -0.79) {
                              return 0;
                            } else {
                              if (AzXGz <= -0.04) {
                                if (AxXAy <= 0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.03) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        } else {
                          if (AzXGy <= -0.11) {
                            return 0;
                          } else {
                            if (AzXGx <= -0.11) {
                              if (AxXGx <= 0.06) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Ay_squared <= 0.04) {
                                if (AxXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Gz <= 0.13) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Gz_squared <= -0.13) {
                          if (AxXGy <= 0.01) {
                            return 1;
                          } else {
                            if (GxXGy <= -0.0) {
                              if (Gy <= -0.5) {
                                return 1;
                              } else {
                                if (AzXGx <= -0.06) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (Gy <= 0.11) {
                            if (GxXGy <= -0.01) {
                              if (GxXGy <= -0.08) {
                                return 0;
                              } else {
                                if (Az_squared <= 0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (Gz <= 0.19) {
                                if (AzXGy <= 0.04) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGx <= -0.12) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (AzXGy <= 0.09) {
                      if (AzXGx <= -0.26) {
                        return 0;
                      } else {
                        if (AyXAz <= 0.79) {
                          if (AxXAy <= 0.04) {
                            return 0;
                          } else {
                            if (Gz <= 0.06) {
                              return 1;
                            } else {
                              if (Gz <= 0.27) {
                                return 2;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AyXGy <= 0.33) {
                        if (AzXGx <= -0.15) {
                          return 0;
                        } else {
                          if (AzXGz <= -0.03) {
                            return 2;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (Az_squared <= 0.31) {
                          if (AxXAy <= 0.04) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 1;
                        }
                      }
                    }
                  }
                } else {
                  if (GyXGz <= -0.02) {
                    if (Gx_squared <= -0.07) {
                      if (AzXGy <= 0.05) {
                        if (Az <= -0.26) {
                          if (AzXGy <= -0.03) {
                            if (Gz <= -0.59) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXGy <= 0.0) {
                              if (Gx_squared <= -0.13) {
                                if (AzXGz <= -0.08) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (AzXGz <= -0.03) {
                                if (Gy_squared <= -0.14) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (Gz <= 0.04) {
                            if (AyXAz <= 0.34) {
                              if (AxXGy <= 0.02) {
                                if (AzXGx <= 0.0) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGy <= -0.07) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (Gy <= 0.13) {
                                if (Ax_squared <= -0.15) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AzXGx <= 0.09) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (Ay <= -0.65) {
                              if (Az_squared <= -0.22) {
                                if (Ax_squared <= -0.15) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AxXGy <= -0.0) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (GxXGz <= 0.0) {
                                return 1;
                              } else {
                                if (AyXAz <= 0.31) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AyXAz <= 0.7) {
                          if (Ay <= -0.63) {
                            if (Az_squared <= -0.13) {
                              if (AzXGy <= 0.11) {
                                if (GxXGz <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              if (AzXGz <= -0.1) {
                                if (GyXGz <= -0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AxXGz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AxXAy <= 0.05) {
                              return 0;
                            } else {
                              if (AyXAz <= 0.39) {
                                return 1;
                              } else {
                                if (AzXGz <= -0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        } else {
                          if (AxXAy <= 0.25) {
                            if (GxXGz <= 0.01) {
                              return 0;
                            } else {
                              if (AyXAz <= 0.76) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    } else {
                      if (Ay <= -0.68) {
                        if (GxXGz <= 0.13) {
                          return 2;
                        } else {
                          return 0;
                        }
                      } else {
                        if (GyXGz <= -0.04) {
                          return 2;
                        } else {
                          if (AzXGx <= 0.3) {
                            if (AyXAz <= 0.31) {
                              if (Ay <= -0.62) {
                                if (AxXAy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (AzXGy <= -0.06) {
                                if (GxXGy <= -0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    }
                  } else {
                    if (GyXGz <= 0.05) {
                      if (AyXGy <= -0.09) {
                        if (Gx_squared <= -0.08) {
                          if (AzXGz <= -0.02) {
                            if (GxXGz <= 0.0) {
                              return 0;
                            } else {
                              if (Gy_squared <= -0.13) {
                                if (Gz_squared <= -0.13) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Az_squared <= -0.19) {
                              if (Ay <= -0.65) {
                                if (AzXGx <= 0.02) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              if (AyXAz <= 0.48) {
                                if (AxXGx <= -0.03) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (AzXGz <= 0.12) {
                          if (AzXGy <= 0.01) {
                            if (AzXGz <= 0.03) {
                              if (GxXGz <= 0.01) {
                                if (Az <= -0.08) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Ax <= -0.56) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (GxXGz <= 0.02) {
                                if (Ay_squared <= 0.15) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Ay_squared <= 0.04) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AyXAz <= 0.74) {
                              if (AxXAz <= 0.01) {
                                if (AyXGx <= -0.05) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXAz <= 0.49) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXGz <= -0.02) {
                                return 0;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (AyXGz <= 0.44) {
                            if (AyXAz <= 0.37) {
                              if (AzXGx <= 0.04) {
                                return 0;
                              } else {
                                return 2;
                              }
                            } else {
                              if (AxXAy <= 0.02) {
                                if (AxXGx <= -0.08) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GxXGy <= 0.02) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AzXGz <= 0.66) {
                        if (Gy <= -1.91) {
                          return 0;
                        } else {
                          if (AyXAz <= 0.62) {
                            if (AyXAz <= 0.5) {
                              if (GyXGz <= 0.22) {
                                if (AxXGx <= -0.0) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (Gz <= -3.29) {
                  if (AzXGz <= 1.05) {
                    if (AzXGy <= 0.63) {
                      return 1;
                    } else {
                      return 1;
                    }
                  } else {
                    return 1;
                  }
                } else {
                  if (GyXGz <= 1.63) {
                    if (AzXGz <= 0.69) {
                      return 1;
                    } else {
                      return 1;
                    }
                  } else {
                    if (Gy <= -2.94) {
                      return 1;
                    } else {
                      if (AzXGz <= 0.57) {
                        return 2;
                      } else {
                        if (Ay <= -0.65) {
                          return 1;
                        } else {
                          if (GxXGy <= 0.43) {
                            return 1;
                          } else {
                            if (AyXGy <= 1.77) {
                              return 2;
                            } else {
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
        } else {
          if (Ay <= -0.64) {
            if (Ax_squared <= 0.05) {
              if (Gx <= 0.52) {
                if (GyXGz <= 0.04) {
                  if (GxXGz <= 0.01) {
                    if (AyXGz <= -0.01) {
                      if (AyXGz <= -0.12) {
                        if (AzXGy <= 0.06) {
                          if (Gx_squared <= 0.0) {
                            if (AxXAz <= -0.13) {
                              if (Gy_squared <= -0.14) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              if (Gz_squared <= -0.12) {
                                return 2;
                              } else {
                                if (AxXGy <= 0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (Gz_squared <= -0.1) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (Az_squared <= 0.04) {
                          if (AxXGy <= -0.07) {
                            if (Gy <= -0.4) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            if (AzXGz <= -0.05) {
                              if (Gy_squared <= -0.14) {
                                if (AzXGz <= -0.05) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              if (AzXGy <= -0.02) {
                                if (AxXAz <= -0.14) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AzXGy <= -0.01) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AxXGy <= 0.03) {
                        if (Gz_squared <= -0.13) {
                          if (AyXGy <= 0.2) {
                            if (Gx_squared <= -0.13) {
                              if (Ay <= -0.73) {
                                return 0;
                              } else {
                                if (AyXGy <= 0.05) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (AxXGy <= -0.05) {
                                return 0;
                              } else {
                                if (GxXGy <= 0.0) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (Gy <= -0.53) {
                            return 0;
                          } else {
                            if (AxXGy <= -0.08) {
                              return 1;
                            } else {
                              if (AxXGx <= -0.02) {
                                return 1;
                              } else {
                                if (AyXGx <= 0.01) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Gy <= 0.63) {
                          if (GxXGy <= 0.0) {
                            return 1;
                          } else {
                            if (AyXGy <= 0.18) {
                              if (AyXGy <= -0.26) {
                                return 2;
                              } else {
                                if (Ax_squared <= -0.03) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (Az <= 0.14) {
                            if (AxXGy <= 0.18) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (Gy <= -0.01) {
                      if (AxXGx <= -0.04) {
                        if (AxXAz <= -0.18) {
                          return 0;
                        } else {
                          if (Gz <= -0.39) {
                            if (AxXAy <= -0.3) {
                              if (Gx <= -0.53) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            if (AzXGy <= 0.03) {
                              if (GyXGz <= -0.01) {
                                if (AzXGx <= -0.01) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Az_squared <= -0.23) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (Gx_squared <= -0.12) {
                                return 2;
                              } else {
                                if (AyXGz <= 0.1) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AzXGz <= -0.08) {
                          if (Gx <= 0.35) {
                            if (AxXGy <= -0.05) {
                              if (AxXGy <= -0.14) {
                                return 0;
                              } else {
                                return 2;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          if (AyXAz <= 0.62) {
                            if (GxXGz <= 0.01) {
                              if (AyXGz <= -0.02) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              if (AxXAz <= -0.01) {
                                if (AxXGy <= -0.08) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Gz_squared <= -0.13) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AxXGy <= -0.01) {
                        if (Az <= -0.44) {
                          return 1;
                        } else {
                          if (Ay_squared <= 0.18) {
                            if (AxXAz <= 0.18) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AyXGx <= 0.11) {
                          if (AzXGz <= -0.03) {
                            if (Gz_squared <= -0.1) {
                              if (Gz_squared <= -0.12) {
                                return 2;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (Az_squared <= -0.21) {
                              return 0;
                            } else {
                              if (GyXGz <= -0.02) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (Az_squared <= -0.19) {
                            if (AxXGy <= 0.09) {
                              return 2;
                            } else {
                              return 0;
                            }
                          } else {
                            if (Ay_squared <= 0.12) {
                              return 2;
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (GyXGz <= 1.1) {
                    if (GxXGz <= -0.05) {
                      return 0;
                    } else {
                      if (AyXAz <= 1.0) {
                        if (Gz <= -1.2) {
                          return 0;
                        } else {
                          if (GxXGz <= 0.05) {
                            if (Ax <= 0.63) {
                              if (AyXGy <= 0.67) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 1;
                  }
                }
              } else {
                if (AzXGz <= 0.03) {
                  if (AxXGx <= 0.36) {
                    if (GxXGy <= -0.33) {
                      return 1;
                    } else {
                      if (GxXGz <= 0.09) {
                        if (Ay_squared <= 0.01) {
                          return 2;
                        } else {
                          if (AyXAz <= 0.6) {
                            if (AxXGz <= -0.07) {
                              return 1;
                            } else {
                              if (GxXGy <= 0.03) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (AxXAy <= -0.22) {
                    if (Az <= -0.88) {
                      return 1;
                    } else {
                      if (AyXGy <= 1.1) {
                        if (Az <= 0.14) {
                          if (AyXGy <= -0.34) {
                            return 0;
                          } else {
                            if (Gx <= 1.17) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (AxXGy <= -0.36) {
                      return 0;
                    } else {
                      if (Gz_squared <= 1.62) {
                        if (AzXGz <= 0.36) {
                          if (Gx <= 0.94) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 1;
                      }
                    }
                  }
                }
              }
            } else {
              if (Ay_squared <= 0.01) {
                if (Gz <= -0.57) {
                  return 0;
                } else {
                  if (Gy <= -1.28) {
                    return 2;
                  } else {
                    if (Ax <= 1.2) {
                      if (GxXGy <= 0.02) {
                        if (AxXGz <= 0.04) {
                          if (AxXAz <= -0.19) {
                            return 1;
                          } else {
                            return 0;
                          }
                        } else {
                          if (Gy_squared <= -0.14) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (Gx_squared <= -0.12) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (GyXGz <= 0.0) {
                        if (Gy <= 0.44) {
                          if (AxXAz <= -0.32) {
                            return 0;
                          } else {
                            if (Gz_squared <= -0.13) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (AxXGz <= 0.77) {
                  if (AzXGx <= -0.2) {
                    if (Gy <= -5.35) {
                      return 1;
                    } else {
                      if (AzXGx <= -1.28) {
                        return 0;
                      } else {
                        if (Ay <= -0.87) {
                          return 0;
                        } else {
                          if (Az_squared <= 0.24) {
                            if (AxXAz <= -0.62) {
                              return 0;
                            } else {
                              if (AxXAy <= -0.8) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (Ay <= -0.76) {
                      if (AyXAz <= 1.28) {
                        if (AxXAz <= -0.61) {
                          return 0;
                        } else {
                          if (AzXGx <= 0.08) {
                            if (Gx_squared <= -0.13) {
                              return 0;
                            } else {
                              if (Gx_squared <= -0.13) {
                                return 0;
                              } else {
                                if (AyXGx <= -0.37) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (Ax <= 1.32) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (AzXGz <= 0.07) {
                        if (AyXGx <= -0.42) {
                          return 2;
                        } else {
                          if (Ax <= 1.03) {
                            if (Gx <= -0.08) {
                              if (AzXGz <= 0.03) {
                                if (AzXGz <= -0.04) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (AyXAz <= 0.39) {
                                if (AyXAz <= 0.24) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (AzXGx <= -0.05) {
                              return 0;
                            } else {
                              if (Gx <= 0.14) {
                                if (AxXGy <= -0.21) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      } else {
                        if (AyXAz <= 0.29) {
                          return 0;
                        } else {
                          if (AyXAz <= 0.35) {
                            return 1;
                          } else {
                            if (AzXGz <= 0.25) {
                              if (AxXGz <= -0.2) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (GyXGz <= -1.41) {
                    return 0;
                  } else {
                    if (Ay_squared <= 1.16) {
                      if (AyXGx <= -1.08) {
                        return 1;
                      } else {
                        return 1;
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              }
            }
          } else {
            if (AxXAz <= -0.15) {
              if (GyXGz <= 0.01) {
                if (Gy <= -1.23) {
                  if (AxXAy <= -1.01) {
                    return 1;
                  } else {
                    if (Gy_squared <= 0.25) {
                      if (AyXGx <= -0.41) {
                        if (AyXAz <= 0.63) {
                          if (Gy <= -1.42) {
                            return 2;
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        return 1;
                      }
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (AxXGx <= -0.24) {
                    if (GxXGz <= -0.01) {
                      return 1;
                    } else {
                      return 0;
                    }
                  } else {
                    if (GxXGz <= 0.01) {
                      if (Gx_squared <= -0.13) {
                        if (Gz_squared <= -0.13) {
                          if (AzXGx <= -0.01) {
                            if (GyXGz <= -0.02) {
                              return 1;
                            } else {
                              return 2;
                            }
                          } else {
                            if (AxXAz <= -0.22) {
                              if (AxXAy <= -0.52) {
                                if (Gz_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gy_squared <= -0.15) {
                                return 1;
                              } else {
                                if (AxXAy <= -0.44) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        } else {
                          if (Gy_squared <= -0.11) {
                            if (GyXGz <= -0.02) {
                              if (AyXGy <= -0.26) {
                                if (Az_squared <= -0.01) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AzXGz <= -0.07) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (AyXGx <= -0.05) {
                                return 1;
                              } else {
                                if (AzXGz <= 0.09) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AxXGy <= 0.0) {
                          if (Gx_squared <= -0.1) {
                            if (Gz_squared <= -0.13) {
                              if (AxXAy <= -0.68) {
                                if (Gy <= -0.25) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AxXAz <= -0.22) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (GxXGy <= -0.0) {
                                if (AzXGy <= 0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXGz <= -0.26) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (Gz_squared <= -0.09) {
                            if (AzXGy <= -0.22) {
                              if (GxXGy <= 0.06) {
                                if (AzXGx <= -0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXAz <= 0.69) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (GxXGy <= -0.01) {
                                return 0;
                              } else {
                                if (GyXGz <= -0.01) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (Gy_squared <= -0.14) {
                        if (AyXGx <= -0.14) {
                          return 1;
                        } else {
                          if (AxXGy <= 0.02) {
                            return 2;
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AzXGz <= -0.12) {
                          return 0;
                        } else {
                          if (Gy_squared <= 0.04) {
                            if (AzXGx <= -0.01) {
                              if (AxXAy <= -0.63) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (Az_squared <= 0.06) {
                  if (AxXAz <= -0.25) {
                    if (GyXGz <= 0.04) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AxXGy <= 0.29) {
                      return 0;
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (AzXGy <= -0.26) {
                    return 1;
                  } else {
                    if (GyXGz <= 0.06) {
                      return 1;
                    } else {
                      return 0;
                    }
                  }
                }
              }
            } else {
              if (GyXGz <= 0.93) {
                if (Az_squared <= 0.01) {
                  if (GyXGz <= 0.06) {
                    if (Gx <= -0.48) {
                      if (Gy <= 0.71) {
                        if (AyXGz <= 0.02) {
                          return 2;
                        } else {
                          return 2;
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (GxXGz <= 0.0) {
                        if (AzXGz <= 0.21) {
                          if (AxXGx <= -0.11) {
                            return 1;
                          } else {
                            if (Gy_squared <= -0.13) {
                              return 0;
                            } else {
                              if (AxXGx <= 0.03) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (Gz <= -0.24) {
                          if (AzXGz <= 0.06) {
                            return 2;
                          } else {
                            if (AzXGz <= 0.13) {
                              if (AzXGz <= 0.07) {
                                return 0;
                              } else {
                                return 2;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (AyXGz <= 0.07) {
                            if (Ax <= 1.03) {
                              if (Ax <= 0.18) {
                                if (GyXGz <= -0.02) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (Gx <= -0.06) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (GxXGz <= 0.01) {
                    if (Gz <= -0.49) {
                      return 0;
                    } else {
                      if (AzXGy <= -0.04) {
                        return 1;
                      } else {
                        if (AxXGz <= -0.03) {
                          return 1;
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (Gz_squared <= -0.13) {
                      return 2;
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                return 1;
              }
            }
          }
        }
      }
    } else {
      if (AxXAy <= -0.9) {
        if (Ay <= -0.68) {
          if (Gy_squared <= -0.06) {
            if (AxXAy <= -1.1) {
              if (AzXGz <= -0.11) {
                return 1;
              } else {
                if (AxXAy <= -1.83) {
                  return 0;
                } else {
                  if (AyXGz <= 0.34) {
                    if (AxXGx <= -0.54) {
                      return 0;
                    } else {
                      if (AxXGy <= -0.33) {
                        return 2;
                      } else {
                        if (AyXAz <= -0.37) {
                          return 0;
                        } else {
                          if (GxXGy <= -0.02) {
                            return 1;
                          } else {
                            if (AzXGz <= 0.02) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    return 0;
                  }
                }
              }
            } else {
              if (Gz <= 0.78) {
                if (GxXGy <= -0.01) {
                  return 0;
                } else {
                  if (AyXGz <= -0.01) {
                    if (GxXGy <= 0.01) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AxXGy <= 0.12) {
                      if (AxXGy <= -0.06) {
                        return 0;
                      } else {
                        return 2;
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                return 2;
              }
            }
          } else {
            if (Gy_squared <= 0.09) {
              if (GxXGz <= 0.01) {
                if (AxXGy <= 0.5) {
                  return 0;
                } else {
                  return 0;
                }
              } else {
                return 0;
              }
            } else {
              if (GyXGz <= -1.19) {
                return 0;
              } else {
                if (Gy_squared <= 0.13) {
                  return 1;
                } else {
                  if (AxXGz <= 2.38) {
                    if (Gx_squared <= -0.1) {
                      return 0;
                    } else {
                      if (AxXAy <= -2.12) {
                        return 0;
                      } else {
                        if (AxXGx <= 0.51) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (Ax_squared <= 3.46) {
                      return 1;
                    } else {
                      return 0;
                    }
                  }
                }
              }
            }
          }
        } else {
          if (AyXGz <= -0.47) {
            if (AzXGx <= -0.14) {
              return 2;
            } else {
              if (GxXGz <= -0.03) {
                return 0;
              } else {
                return 2;
              }
            }
          } else {
            if (GxXGz <= 0.01) {
              if (Gz_squared <= -0.12) {
                if (Gy_squared <= -0.11) {
                  if (AxXGx <= 0.16) {
                    if (Gx_squared <= -0.13) {
                      return 1;
                    } else {
                      if (AxXAz <= -0.01) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (AzXGz <= 0.03) {
                      if (Gy_squared <= -0.13) {
                        return 1;
                      } else {
                        return 0;
                      }
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (AyXGx <= 0.15) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              } else {
                if (AyXGy <= 0.15) {
                  if (GxXGz <= -0.12) {
                    return 2;
                  } else {
                    if (Gz_squared <= -0.09) {
                      if (Ax_squared <= 0.46) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (Gx_squared <= -0.12) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              }
            } else {
              if (Gy_squared <= -0.13) {
                if (AxXGx <= 0.11) {
                  if (AxXAy <= -1.22) {
                    if (Gy <= 0.03) {
                      return 1;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AyXAz <= 0.02) {
                      if (AzXGz <= 0.0) {
                        if (Ay <= -0.63) {
                          return 2;
                        } else {
                          return 1;
                        }
                      } else {
                        if (Az_squared <= -0.28) {
                          if (AzXGz <= 0.02) {
                            return 0;
                          } else {
                            return 2;
                          }
                        } else {
                          if (Gx <= -0.11) {
                            if (AxXGz <= -0.13) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            if (GyXGz <= -0.02) {
                              if (AxXAy <= -0.93) {
                                if (GxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (AxXAz <= 0.06) {
                    return 1;
                  } else {
                    return 0;
                  }
                }
              } else {
                if (AxXGy <= -0.72) {
                  return 1;
                } else {
                  if (Gz_squared <= -0.12) {
                    if (AxXAy <= -1.2) {
                      return 1;
                    } else {
                      if (Gz <= -0.18) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 0;
                  }
                }
              }
            }
          }
        }
      } else {
        if (Gy_squared <= 0.05) {
          if (AyXGz <= -0.58) {
            if (Ay_squared <= 0.45) {
              if (GxXGz <= -0.03) {
                if (GxXGy <= -0.1) {
                  return 1;
                } else {
                  if (AyXGz <= -0.74) {
                    if (Gz <= 1.65) {
                      if (Gz_squared <= 0.13) {
                        return 0;
                      } else {
                        if (Ay <= -0.74) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (Gy_squared <= -0.15) {
                      return 2;
                    } else {
                      if (AzXGz <= 0.25) {
                        if (AxXGx <= -0.02) {
                          if (Gx <= -1.33) {
                            return 2;
                          } else {
                            if (AxXAz <= 0.14) {
                              if (Gz_squared <= 0.04) {
                                return 2;
                              } else {
                                if (Gy_squared <= -0.1) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        return 2;
                      }
                    }
                  }
                }
              } else {
                if (Az <= 1.56) {
                  if (Gx_squared <= -0.08) {
                    if (AyXAz <= -0.06) {
                      if (AxXAz <= 0.08) {
                        if (GyXGz <= -0.13) {
                          if (Gz <= 1.15) {
                            return 2;
                          } else {
                            if (Gy <= -0.44) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (AyXGz <= -0.65) {
                            if (AxXGy <= -0.13) {
                              return 1;
                            } else {
                              if (Gz <= 1.27) {
                                if (AzXGy <= -0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      } else {
                        if (GyXGz <= -0.19) {
                          return 2;
                        } else {
                          if (Gy <= 0.23) {
                            if (AyXGz <= -0.84) {
                              return 2;
                            } else {
                              if (AzXGz <= 0.07) {
                                if (AzXGx <= 0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AxXAz <= 0.24) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    } else {
                      if (Gy <= 0.08) {
                        if (AzXGz <= -0.08) {
                          if (GxXGy <= 0.01) {
                            if (AzXGx <= -0.01) {
                              if (AzXGz <= -0.1) {
                                if (AxXAy <= -0.31) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              if (AyXGz <= -0.66) {
                                if (Ay_squared <= 0.18) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (AxXGz <= 0.13) {
                              return 2;
                            } else {
                              if (Gz <= 1.17) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (AxXAy <= -0.41) {
                            if (AxXAy <= -0.54) {
                              if (AxXAy <= -0.77) {
                                return 2;
                              } else {
                                if (AxXGz <= 0.39) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (GxXGy <= 0.0) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (AxXAy <= -0.33) {
                              return 2;
                            } else {
                              if (Gz_squared <= 0.11) {
                                if (Gz <= 1.07) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      } else {
                        return 2;
                      }
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (AyXAz <= -0.8) {
                    if (Gx_squared <= -0.12) {
                      if (AxXGx <= -0.02) {
                        return 0;
                      } else {
                        return 2;
                      }
                    } else {
                      return 2;
                    }
                  } else {
                    if (Ay <= -0.71) {
                      return 0;
                    } else {
                      if (Ax_squared <= -0.08) {
                        if (Ax_squared <= -0.13) {
                          if (AxXGx <= -0.01) {
                            if (AxXGz <= -0.13) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            if (Ay_squared <= -0.01) {
                              return 2;
                            } else {
                              if (AxXGx <= 0.0) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (Gz_squared <= 0.08) {
                            return 2;
                          } else {
                            if (AyXAz <= -0.72) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (Gz_squared <= 0.09) {
                          if (Gz_squared <= 0.09) {
                            return 2;
                          } else {
                            return 0;
                          }
                        } else {
                          return 2;
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (AyXGz <= -1.28) {
                if (AxXGy <= 0.02) {
                  return 1;
                } else {
                  return 0;
                }
              } else {
                if (Ay <= -0.88) {
                  if (AyXGy <= -0.12) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  return 2;
                }
              }
            }
          } else {
            if (GyXGz <= -0.3) {
              if (AyXGy <= -0.56) {
                if (Gz_squared <= 0.53) {
                  if (Gz_squared <= 0.42) {
                    return 1;
                  } else {
                    if (GxXGy <= 0.22) {
                      if (AxXAy <= -0.32) {
                        return 1;
                      } else {
                        if (Gx <= 0.44) {
                          return 2;
                        } else {
                          if (Az_squared <= -0.27) {
                            return 2;
                          } else {
                            if (AzXGx <= -0.02) {
                              if (AxXGy <= 0.02) {
                                return 2;
                              } else {
                                if (AyXGy <= -0.62) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (AxXGx <= -0.03) {
                    return 2;
                  } else {
                    if (AzXGx <= -0.0) {
                      return 1;
                    } else {
                      return 1;
                    }
                  }
                }
              } else {
                if (Ay <= -0.67) {
                  return 1;
                } else {
                  return 1;
                }
              }
            } else {
              if (AyXGx <= -0.1) {
                if (GxXGz <= -0.01) {
                  if (AyXAz <= -0.17) {
                    if (GxXGz <= -0.12) {
                      return 0;
                    } else {
                      if (AzXGz <= -0.07) {
                        if (AxXGz <= -0.1) {
                          return 0;
                        } else {
                          return 2;
                        }
                      } else {
                        if (AyXGz <= 0.39) {
                          if (GyXGz <= 0.0) {
                            if (Gz <= -0.49) {
                              return 0;
                            } else {
                              if (Ax_squared <= -0.08) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (Gx <= 0.79) {
                      if (AyXGz <= 0.24) {
                        return 0;
                      } else {
                        if (AxXAz <= 0.07) {
                          if (Ax_squared <= 0.14) {
                            if (Az_squared <= -0.27) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AzXGx <= -0.07) {
                        if (AxXAy <= -0.23) {
                          return 0;
                        } else {
                          return 1;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (AyXAz <= -0.1) {
                    if (GyXGz <= -0.02) {
                      if (AxXGy <= 0.15) {
                        if (Ay <= -0.83) {
                          return 0;
                        } else {
                          if (AxXGz <= -0.02) {
                            if (AzXGy <= -0.1) {
                              return 2;
                            } else {
                              if (AxXAz <= 0.05) {
                                return 2;
                              } else {
                                if (Az <= 1.56) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (Gz_squared <= -0.13) {
                              if (Gx_squared <= -0.13) {
                                return 0;
                              } else {
                                if (GxXGz <= 0.02) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (Gz <= 0.09) {
                                return 2;
                              } else {
                                if (Gz_squared <= -0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (AyXAz <= -0.99) {
                        return 2;
                      } else {
                        if (AzXGy <= -0.03) {
                          if (AxXGx <= 0.14) {
                            if (Gz <= -0.31) {
                              return 2;
                            } else {
                              if (AxXGz <= -0.02) {
                                if (Gx <= 0.19) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (Az_squared <= -0.18) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (GxXGy <= 0.06) {
                            if (Gx_squared <= -0.1) {
                              if (Ax_squared <= 0.05) {
                                if (Gy <= 0.0) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (Gy <= 0.02) {
                      if (AzXGx <= 0.01) {
                        if (AyXGx <= -0.58) {
                          return 0;
                        } else {
                          if (AyXGz <= -0.02) {
                            if (Gx <= 0.56) {
                              if (AyXGz <= -0.43) {
                                return 2;
                              } else {
                                if (AzXGz <= -0.02) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AyXGx <= -0.23) {
                              return 2;
                            } else {
                              if (GxXGz <= 0.01) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      } else {
                        if (Gy <= -0.55) {
                          return 0;
                        } else {
                          if (AzXGy <= 0.0) {
                            if (AxXGx <= -0.01) {
                              return 0;
                            } else {
                              if (GxXGy <= 0.0) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    } else {
                      if (AyXGx <= -0.23) {
                        if (AyXAz <= 0.02) {
                          if (Gy <= 0.63) {
                            if (GyXGz <= -0.02) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (Gz <= 0.17) {
                            if (Ax_squared <= -0.15) {
                              if (GyXGz <= -0.02) {
                                return 1;
                              } else {
                                if (Gy_squared <= -0.13) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AxXAy <= -0.09) {
                          if (Gy <= 0.71) {
                            if (Gy_squared <= -0.15) {
                              return 0;
                            } else {
                              return 2;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (AxXAy <= 0.23) {
                            if (GyXGz <= -0.02) {
                              return 1;
                            } else {
                              return 2;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (AyXGz <= 0.13) {
                  if (AyXAz <= -0.43) {
                    if (Az_squared <= -0.01) {
                      if (Ax <= -1.98) {
                        return 0;
                      } else {
                        if (Gz <= 0.77) {
                          if (GxXGy <= 0.01) {
                            if (AxXAy <= 0.52) {
                              if (AyXGy <= -0.57) {
                                return 0;
                              } else {
                                if (GxXGy <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXGy <= 0.1) {
                                if (Ay_squared <= 0.15) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (AxXGz <= 0.0) {
                              if (GxXGz <= 0.01) {
                                if (AxXAz <= 0.07) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGy <= -0.06) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AxXGy <= 0.02) {
                                if (GyXGz <= -0.08) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (AxXGx <= -0.5) {
                            return 2;
                          } else {
                            if (AzXGz <= 0.32) {
                              if (AxXGz <= -0.2) {
                                if (Gz <= 0.88) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AzXGx <= -0.12) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Ay_squared <= -0.04) {
                                if (AxXGz <= -0.16) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGz <= -0.52) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      }
                    } else {
                      if (GyXGz <= 0.08) {
                        if (Ax <= -1.41) {
                          return 0;
                        } else {
                          if (GxXGy <= 0.01) {
                            if (AyXGx <= -0.04) {
                              if (AxXAz <= 0.2) {
                                if (AzXGx <= 0.07) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              if (Az_squared <= 0.14) {
                                if (Ax <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGx <= 0.06) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AxXAy <= -0.55) {
                              return 0;
                            } else {
                              if (AxXAz <= 0.17) {
                                if (AyXGz <= 0.09) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      } else {
                        return 2;
                      }
                    }
                  } else {
                    if (GxXGy <= -0.08) {
                      if (AyXGz <= -0.33) {
                        if (Ay_squared <= 0.12) {
                          if (GxXGz <= -0.17) {
                            return 2;
                          } else {
                            if (AxXAz <= 0.07) {
                              if (AzXGx <= 0.08) {
                                return 2;
                              } else {
                                if (GxXGz <= -0.1) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (AzXGz <= 0.0) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AzXGx <= 0.04) {
                        if (AxXAy <= 0.61) {
                          if (AxXGy <= 0.14) {
                            if (AxXAy <= -0.75) {
                              if (Gz <= -0.04) {
                                if (Gy <= 0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AxXGz <= 0.32) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXGz <= -0.05) {
                                if (GyXGz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Az <= 0.58) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AxXAy <= -0.57) {
                              if (AyXGy <= -0.39) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (Gz_squared <= -0.13) {
                            if (AyXAz <= -0.25) {
                              if (Ay <= -0.68) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXAz <= -0.01) {
                              return 1;
                            } else {
                              if (AzXGx <= 0.02) {
                                if (Gy_squared <= -0.15) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGz <= 0.0) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (GxXGz <= 0.02) {
                          if (AzXGz <= -0.01) {
                            if (Gx_squared <= 0.04) {
                              if (Gy_squared <= -0.15) {
                                if (AxXAz <= 0.05) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AyXGz <= -0.38) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (AxXGz <= 0.14) {
                                return 2;
                              } else {
                                if (Gz_squared <= -0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AxXGy <= 0.15) {
                              if (Gy_squared <= -0.15) {
                                if (AxXAz <= 0.06) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (GxXGy <= 0.06) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 2;
                        }
                      }
                    }
                  }
                } else {
                  if (Gy_squared <= -0.11) {
                    if (Gz <= -0.42) {
                      if (AyXGz <= 0.52) {
                        if (AyXGy <= -0.03) {
                          if (AzXGz <= 0.01) {
                            if (AzXGx <= -0.02) {
                              if (AxXAy <= -0.03) {
                                return 0;
                              } else {
                                return 2;
                              }
                            } else {
                              if (AzXGx <= -0.01) {
                                return 0;
                              } else {
                                if (AxXGx <= -0.07) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (GxXGy <= 0.01) {
                              return 2;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (AxXGx <= -0.05) {
                            if (AzXGy <= -0.02) {
                              if (AxXAy <= -0.72) {
                                return 2;
                              } else {
                                if (AyXAz <= -0.32) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Gx <= -0.47) {
                                return 2;
                              } else {
                                if (Ay <= -0.69) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (Az <= 0.87) {
                              if (AxXGx <= -0.02) {
                                return 2;
                              } else {
                                if (Ay <= -0.67) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (Gz_squared <= -0.1) {
                                if (Ax <= -1.18) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      } else {
                        if (AzXGy <= -0.02) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AxXAy <= 0.55) {
                        if (GxXGy <= 0.02) {
                          if (Az_squared <= -0.24) {
                            if (AxXAz <= 0.1) {
                              if (AzXGy <= -0.02) {
                                if (AxXGy <= 0.06) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (GyXGz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Ax <= 0.41) {
                                if (AxXGz <= -0.05) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AyXGx <= 0.01) {
                              if (Gy <= 0.01) {
                                if (Gz <= -0.32) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GxXGz <= 0.0) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXGy <= -0.04) {
                                if (AxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GxXGy <= 0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          if (AxXGz <= -0.08) {
                            if (Az <= 1.74) {
                              if (AyXAz <= -0.24) {
                                if (Ay_squared <= 0.12) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGx <= 0.03) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AzXGz <= 0.03) {
                              if (GxXGy <= 0.04) {
                                if (GxXGz <= 0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Gx <= -0.43) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (Ay_squared <= 0.04) {
                                return 2;
                              } else {
                                if (AyXGy <= 0.21) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AxXAz <= -0.14) {
                          return 2;
                        } else {
                          if (AyXGx <= 0.12) {
                            if (Gx <= -0.01) {
                              if (Ay <= -0.69) {
                                return 2;
                              } else {
                                if (GyXGz <= -0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    }
                  } else {
                    if (Gz <= -1.14) {
                      return 0;
                    } else {
                      if (AyXGy <= 0.42) {
                        if (Gy_squared <= 0.01) {
                          if (AyXAz <= -0.62) {
                            return 2;
                          } else {
                            if (GxXGy <= 0.06) {
                              if (GyXGz <= 0.01) {
                                if (AyXGy <= -0.35) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (Ay_squared <= 0.38) {
                          if (AyXAz <= -0.29) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (Gz <= -2.09) {
            if (Gx_squared <= 0.07) {
              if (AzXGy <= -0.2) {
                return 2;
              } else {
                if (GxXGy <= 0.29) {
                  if (AyXGz <= 1.31) {
                    return 2;
                  } else {
                    return 1;
                  }
                } else {
                  if (AxXAy <= -0.13) {
                    return 1;
                  } else {
                    return 1;
                  }
                }
              }
            } else {
              if (AzXGz <= -0.09) {
                return 0;
              } else {
                return 0;
              }
            }
          } else {
            if (AxXAy <= 0.14) {
              if (Gy_squared <= 0.35) {
                if (AyXAz <= -0.21) {
                  if (GyXGz <= -0.22) {
                    return 2;
                  } else {
                    if (AzXGx <= -0.03) {
                      return 0;
                    } else {
                      if (AzXGx <= 0.17) {
                        if (Gz_squared <= -0.08) {
                          if (AyXAz <= -0.39) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (GyXGz <= 0.01) {
                    if (AzXGz <= 0.02) {
                      if (AxXGy <= -0.56) {
                        return 2;
                      } else {
                        if (AxXGy <= -0.19) {
                          return 0;
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      if (AxXGy <= -0.38) {
                        return 1;
                      } else {
                        return 2;
                      }
                    }
                  } else {
                    if (Gz <= -0.53) {
                      return 0;
                    } else {
                      if (Ay_squared <= 0.21) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (Gz <= 1.39) {
                  if (AxXGz <= -0.16) {
                    return 0;
                  } else {
                    if (GyXGz <= 0.45) {
                      if (Gz_squared <= -0.13) {
                        return 0;
                      } else {
                        if (AxXGy <= 0.45) {
                          if (Gx <= 0.84) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  return 0;
                }
              }
            } else {
              if (GyXGz <= 0.19) {
                if (AxXGz <= -0.07) {
                  if (GxXGy <= 0.27) {
                    if (AxXAz <= 0.03) {
                      return 2;
                    } else {
                      return 2;
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (AzXGz <= -0.01) {
                    return 2;
                  } else {
                    if (AzXGz <= 0.02) {
                      return 0;
                    } else {
                      if (Ay_squared <= 0.24) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (Gz_squared <= 0.04) {
                  return 0;
                } else {
                  return 0;
                }
              }
            }
          }
        }
      }
    }
  } else {
    if (Gz_squared <= -0.1) {
      if (AyXAz <= -0.76) {
        if (Ax <= -0.33) {
          if (Gy_squared <= -0.14) {
            if (AzXGz <= 0.0) {
              if (Az_squared <= 1.01) {
                if (Gx_squared <= -0.04) {
                  if (AxXGz <= -0.03) {
                    if (AxXGx <= 0.0) {
                      if (GxXGz <= 0.01) {
                        return 1;
                      } else {
                        return 2;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (Az <= -0.69) {
                      return 0;
                    } else {
                      if (AxXAy <= 0.15) {
                        if (AyXAz <= -0.89) {
                          return 2;
                        } else {
                          if (AyXAz <= -0.84) {
                            if (AxXGy <= 0.0) {
                              return 2;
                            } else {
                              if (AyXGx <= -0.03) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (Gx_squared <= -0.11) {
                              if (GxXGy <= 0.01) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (Gz <= 0.01) {
                          if (GyXGz <= -0.02) {
                            return 2;
                          } else {
                            if (AyXAz <= -0.89) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (AxXAy <= 0.21) {
                            return 2;
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  return 0;
                }
              } else {
                return 2;
              }
            } else {
              if (AyXAz <= -0.89) {
                if (Az <= -1.46) {
                  if (AxXAy <= -0.39) {
                    return 2;
                  } else {
                    if (AxXAy <= 0.07) {
                      if (AyXGy <= -0.02) {
                        return 2;
                      } else {
                        if (AzXGz <= 0.12) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      return 2;
                    }
                  }
                } else {
                  if (Az <= -0.69) {
                    return 0;
                  } else {
                    if (Ay <= 1.54) {
                      if (Ay_squared <= -0.07) {
                        if (Gz <= -0.29) {
                          return 0;
                        } else {
                          if (AzXGy <= -0.07) {
                            return 0;
                          } else {
                            if (Gx <= 0.1) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (Gx_squared <= -0.11) {
                          if (GxXGz <= 0.01) {
                            if (Az <= -0.59) {
                              return 2;
                            } else {
                              if (AzXGz <= 0.11) {
                                if (AzXGy <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      if (Gx_squared <= -0.08) {
                        if (Gy_squared <= -0.14) {
                          return 2;
                        } else {
                          return 1;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (Ay_squared <= -0.09) {
                  if (Az_squared <= 0.01) {
                    if (AyXGx <= 0.06) {
                      if (AxXAy <= 0.16) {
                        return 2;
                      } else {
                        return 2;
                      }
                    } else {
                      return 2;
                    }
                  } else {
                    return 2;
                  }
                } else {
                  if (Gx_squared <= -0.11) {
                    if (AyXGz <= -0.05) {
                      if (Ay <= 1.53) {
                        if (AyXGx <= 0.0) {
                          if (AxXGx <= -0.01) {
                            if (Ay_squared <= -0.04) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (GxXGz <= 0.0) {
                            if (Gx_squared <= -0.13) {
                              return 2;
                            } else {
                              if (AxXAz <= 0.13) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            if (Ay_squared <= -0.04) {
                              return 2;
                            } else {
                              if (AxXAz <= 0.11) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      } else {
                        return 2;
                      }
                    } else {
                      if (AxXAz <= 0.13) {
                        if (Gx <= -0.12) {
                          if (GyXGz <= -0.02) {
                            if (AyXAz <= -0.8) {
                              if (GxXGz <= 0.01) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (Gy <= 0.18) {
                            if (AzXGy <= 0.03) {
                              if (Ay <= 1.49) {
                                if (GxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AzXGz <= 0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            if (Az <= -0.37) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (Gx_squared <= -0.12) {
                          if (Gz <= -0.1) {
                            if (AzXGx <= 0.03) {
                              if (AzXGx <= -0.01) {
                                if (GyXGz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GyXGz <= -0.02) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= -0.08) {
                      return 2;
                    } else {
                      return 2;
                    }
                  }
                }
              }
            }
          } else {
            if (Gy_squared <= -0.09) {
              if (AxXAz <= 0.18) {
                if (Az <= -1.86) {
                  return 1;
                } else {
                  if (Gx_squared <= -0.06) {
                    if (Az <= -0.59) {
                      if (AxXGx <= -0.02) {
                        return 2;
                      } else {
                        if (AyXGy <= 0.13) {
                          if (Az <= -0.73) {
                            return 1;
                          } else {
                            return 2;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (Gy_squared <= -0.13) {
                        if (Ay_squared <= 0.01) {
                          if (AzXGz <= 0.01) {
                            if (AxXAy <= 0.25) {
                              if (AyXAz <= -0.88) {
                                return 0;
                              } else {
                                if (Gy <= -0.16) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            if (Ay <= 1.41) {
                              return 2;
                            } else {
                              if (AyXGz <= -0.08) {
                                return 2;
                              } else {
                                if (AyXGy <= -0.17) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          if (Az_squared <= -0.07) {
                            return 1;
                          } else {
                            if (GxXGy <= 0.02) {
                              if (AxXAz <= 0.07) {
                                return 1;
                              } else {
                                return 2;
                              }
                            } else {
                              return 1;
                            }
                          }
                        }
                      } else {
                        if (Ay <= 1.34) {
                          return 2;
                        } else {
                          if (Ay_squared <= 0.27) {
                            if (Az_squared <= -0.07) {
                              return 1;
                            } else {
                              if (AxXGx <= -0.01) {
                                if (AxXGy <= 0.0) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGz <= 0.12) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (Ay <= 1.6) {
                      if (Az <= -0.51) {
                        return 0;
                      } else {
                        return 2;
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (AyXAz <= -1.36) {
                  return 1;
                } else {
                  if (AxXAy <= -0.33) {
                    return 0;
                  } else {
                    if (GxXGz <= 0.01) {
                      return 0;
                    } else {
                      return 1;
                    }
                  }
                }
              }
            } else {
              if (Gy_squared <= 0.06) {
                if (Az <= -0.69) {
                  if (Gy <= -0.57) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  if (Ay <= 1.69) {
                    if (GyXGz <= -0.09) {
                      return 2;
                    } else {
                      if (AxXGx <= 0.01) {
                        if (AyXGz <= -0.04) {
                          return 1;
                        } else {
                          if (AzXGy <= -0.27) {
                            return 0;
                          } else {
                            if (Gy_squared <= -0.07) {
                              return 1;
                            } else {
                              return 0;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 0;
                  }
                }
              } else {
                if (Gx_squared <= 1.27) {
                  if (Gx_squared <= -0.13) {
                    return 0;
                  } else {
                    if (GyXGz <= -0.11) {
                      return 0;
                    } else {
                      if (Gy <= 1.45) {
                        if (GxXGz <= 0.0) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  return 1;
                }
              }
            }
          }
        } else {
          if (AxXAy <= 0.28) {
            if (AyXGz <= 0.13) {
              if (AxXAz <= 0.84) {
                if (GxXGy <= 0.02) {
                  if (AxXAy <= 0.27) {
                    if (Az <= 2.79) {
                      if (GyXGz <= -0.02) {
                        if (Gy_squared <= -0.12) {
                          if (AyXGy <= 0.01) {
                            if (AyXGy <= -0.07) {
                              return 2;
                            } else {
                              if (GxXGz <= 0.01) {
                                return 2;
                              } else {
                                if (AxXGz <= -0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (Gz_squared <= -0.13) {
                              return 2;
                            } else {
                              if (AzXGz <= 0.04) {
                                return 2;
                              } else {
                                if (AxXAz <= 0.3) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (GxXGz <= 0.01) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      return 2;
                    }
                  } else {
                    if (AyXGy <= -0.15) {
                      return 0;
                    } else {
                      if (AzXGx <= -0.0) {
                        return 2;
                      } else {
                        return 2;
                      }
                    }
                  }
                } else {
                  return 0;
                }
              } else {
                if (Ax_squared <= 0.99) {
                  if (AyXGz <= 0.07) {
                    if (Az_squared <= 0.57) {
                      if (Ay_squared <= -0.43) {
                        return 2;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    return 2;
                  }
                } else {
                  return 0;
                }
              }
            } else {
              if (AxXGy <= 0.03) {
                if (Gx <= -0.34) {
                  return 1;
                } else {
                  if (AxXGz <= -0.03) {
                    if (AyXGx <= -0.01) {
                      return 2;
                    } else {
                      if (AxXAz <= 0.55) {
                        return 2;
                      } else {
                        return 1;
                      }
                    }
                  } else {
                    return 1;
                  }
                }
              } else {
                if (AyXGz <= 0.16) {
                  return 0;
                } else {
                  return 2;
                }
              }
            }
          } else {
            if (Gy_squared <= -0.1) {
              if (Ay <= 1.32) {
                if (AzXGz <= 0.1) {
                  if (AxXGy <= 0.13) {
                    if (AxXAz <= -0.34) {
                      if (Gz_squared <= -0.13) {
                        return 1;
                      } else {
                        if (AyXGy <= -0.15) {
                          return 0;
                        } else {
                          if (Gz <= 0.08) {
                            if (Gx_squared <= -0.12) {
                              if (Gx_squared <= -0.13) {
                                return 1;
                              } else {
                                if (AzXGy <= -0.31) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    return 2;
                  }
                } else {
                  return 0;
                }
              } else {
                if (Ay_squared <= 0.29) {
                  if (Gx_squared <= -0.06) {
                    if (Ax <= 0.63) {
                      if (GxXGy <= 0.01) {
                        if (AxXAz <= -0.08) {
                          if (Gz_squared <= -0.13) {
                            if (Az_squared <= -0.04) {
                              return 1;
                            } else {
                              if (AyXGz <= 0.03) {
                                return 1;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            if (AxXAz <= -0.22) {
                              return 1;
                            } else {
                              if (AxXGx <= -0.05) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (AyXGy <= 0.14) {
                            if (GxXGz <= 0.02) {
                              if (AxXGz <= -0.01) {
                                return 1;
                              } else {
                                return 0;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AxXAy <= 0.32) {
                          if (AzXGz <= 0.06) {
                            return 1;
                          } else {
                            return 2;
                          }
                        } else {
                          if (GyXGz <= -0.03) {
                            if (Gx_squared <= -0.12) {
                              if (Gz_squared <= -0.13) {
                                if (Gx_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (Gz_squared <= -0.11) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (AzXGz <= -0.05) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (AyXGx <= -0.02) {
                              if (AyXGx <= -0.23) {
                                return 1;
                              } else {
                                if (AxXAz <= -0.18) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AyXGz <= 0.07) {
                                if (AyXGz <= 0.05) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (GxXGy <= 0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      }
                    } else {
                      if (Gx <= -0.04) {
                        if (Gx <= -0.17) {
                          if (AxXAz <= -0.49) {
                            return 0;
                          } else {
                            if (AzXGy <= 0.08) {
                              if (AzXGx <= 0.1) {
                                return 0;
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (GxXGy <= 0.02) {
                            return 1;
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (Ax_squared <= 0.14) {
                          if (Gy_squared <= -0.12) {
                            if (Ay <= 1.51) {
                              if (AyXGx <= 0.04) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= -0.08) {
                      return 0;
                    } else {
                      if (AxXAy <= 0.5) {
                        return 0;
                      } else {
                        if (AzXGx <= 0.42) {
                          if (Ay_squared <= 0.01) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  }
                } else {
                  if (AxXGy <= 0.03) {
                    if (GxXGy <= 0.04) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    return 0;
                  }
                }
              }
            } else {
              if (Gy_squared <= 0.01) {
                if (Ay <= 1.34) {
                  return 0;
                } else {
                  if (AyXGy <= 0.43) {
                    if (AzXGx <= 0.15) {
                      if (AyXGy <= 0.39) {
                        if (AxXAz <= 0.01) {
                          if (Gz_squared <= -0.11) {
                            if (AyXGx <= -0.13) {
                              return 1;
                            } else {
                              if (Ax_squared <= -0.03) {
                                if (AxXGy <= -0.15) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        return 1;
                      }
                    } else {
                      if (Ay <= 1.51) {
                        if (AyXGz <= 0.12) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        if (AxXAz <= -0.05) {
                          return 0;
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (AxXGx <= -0.03) {
                      return 0;
                    } else {
                      if (AxXGz <= 0.01) {
                        if (AzXGx <= -0.05) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        return 1;
                      }
                    }
                  }
                }
              } else {
                if (Gx_squared <= 0.93) {
                  if (AyXGy <= -0.62) {
                    if (Gy_squared <= 0.05) {
                      return 0;
                    } else {
                      if (AxXAy <= 0.42) {
                        return 0;
                      } else {
                        if (AxXGx <= -0.07) {
                          if (Az_squared <= -0.05) {
                            return 0;
                          } else {
                            if (AyXAz <= -1.23) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AyXGy <= 0.64) {
                      return 0;
                    } else {
                      if (Gy_squared <= 0.08) {
                        return 0;
                      } else {
                        if (Az <= -0.98) {
                          return 0;
                        } else {
                          if (AyXAz <= -0.9) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  }
                } else {
                  return 1;
                }
              }
            }
          }
        }
      } else {
        if (Ay <= 0.31) {
          if (AzXGz <= 0.03) {
            if (Az <= -0.62) {
              if (GxXGz <= 0.01) {
                if (Ax <= -1.7) {
                  if (Gx_squared <= -0.13) {
                    return 2;
                  } else {
                    return 2;
                  }
                } else {
                  if (Gy_squared <= -0.15) {
                    if (Gx_squared <= -0.13) {
                      if (Az <= -1.38) {
                        if (AyXGx <= 0.01) {
                          if (GxXGz <= 0.01) {
                            if (AzXGx <= 0.05) {
                              if (AyXGx <= 0.0) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (AxXAz <= -0.05) {
                            if (Az <= -1.6) {
                              if (Gy_squared <= -0.15) {
                                if (GxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (AzXGz <= -0.11) {
                                return 2;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Az <= -1.78) {
                              return 1;
                            } else {
                              if (Ay <= -0.45) {
                                return 2;
                              } else {
                                if (AxXGx <= -0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AxXGx <= 0.0) {
                          if (Ay_squared <= -0.27) {
                            if (Ax <= 2.34) {
                              if (Gy_squared <= -0.15) {
                                if (AxXAz <= -0.4) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGz <= -0.07) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXAz <= -0.27) {
                              if (AxXGy <= 0.02) {
                                if (Ay <= -0.55) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              if (AyXGx <= 0.05) {
                                if (AyXAz <= 0.78) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (AyXGy <= 0.03) {
                            if (AyXGy <= 0.0) {
                              if (AxXGx <= 0.02) {
                                if (AxXAy <= 0.35) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGz <= 0.03) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AzXGz <= -0.02) {
                                return 2;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AxXGx <= -0.15) {
                        return 1;
                      } else {
                        if (AzXGx <= 0.14) {
                          if (Az <= -1.28) {
                            if (Ax_squared <= -0.15) {
                              return 0;
                            } else {
                              return 1;
                            }
                          } else {
                            if (GyXGz <= -0.02) {
                              return 1;
                            } else {
                              if (GxXGy <= 0.01) {
                                if (AyXGx <= -0.13) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (AyXAz <= 0.88) {
                            if (AyXGx <= 0.13) {
                              if (AyXGy <= 0.03) {
                                if (GxXGz <= -0.0) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 2;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (Gy <= 0.04) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (AxXAz <= -0.83) {
                      if (Ax <= 3.25) {
                        if (GxXGy <= -0.04) {
                          return 0;
                        } else {
                          if (GyXGz <= -0.03) {
                            if (Az <= -0.98) {
                              return 1;
                            } else {
                              return 0;
                            }
                          } else {
                            if (Gy_squared <= -0.14) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (GxXGy <= -0.0) {
                        if (AxXAz <= -0.2) {
                          if (Gx <= -0.58) {
                            return 0;
                          } else {
                            if (AxXGy <= 0.35) {
                              if (Az_squared <= 0.34) {
                                if (AyXGy <= -0.39) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Az_squared <= 0.72) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AxXAy <= 0.15) {
                            if (AyXAz <= 0.73) {
                              return 1;
                            } else {
                              if (AzXGy <= -0.54) {
                                return 1;
                              } else {
                                if (Gy_squared <= -0.07) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (AyXGz <= -0.07) {
                              if (Gy <= 1.0) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gx <= -0.57) {
                                return 1;
                              } else {
                                if (Gy_squared <= -0.08) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Az_squared <= 0.31) {
                          if (GyXGz <= -0.02) {
                            if (AzXGx <= 0.16) {
                              if (AyXGx <= 0.01) {
                                if (AyXGy <= 0.13) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AxXGy <= 0.08) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXAy <= -0.16) {
                              if (GxXGy <= 0.01) {
                                return 1;
                              } else {
                                return 2;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AxXGz <= -0.03) {
                            if (Az <= -1.82) {
                              return 1;
                            } else {
                              if (AzXGy <= -0.18) {
                                return 1;
                              } else {
                                if (AxXAz <= 0.28) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (Gy <= -0.34) {
                              if (Gz <= 0.01) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (GyXGz <= -0.03) {
                                if (Az_squared <= 0.66) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Ay <= -0.31) {
                                  return 1;
                                } else {
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
              } else {
                if (Gz <= 0.04) {
                  if (GxXGy <= 0.02) {
                    if (Gx <= 0.86) {
                      if (GxXGy <= 0.01) {
                        if (AxXGy <= 0.18) {
                          if (AzXGz <= -0.08) {
                            return 2;
                          } else {
                            if (Az <= -1.28) {
                              if (AxXAy <= -0.21) {
                                return 1;
                              } else {
                                if (Az_squared <= 0.63) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AxXGx <= 0.02) {
                                if (Gy_squared <= -0.14) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GxXGy <= 0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (Ay <= -0.26) {
                          if (AxXGz <= -0.07) {
                            return 1;
                          } else {
                            if (AxXAz <= 0.46) {
                              if (AxXAz <= -0.6) {
                                if (AxXAy <= -0.73) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Az <= -1.93) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AxXGx <= -0.07) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (AxXAy <= -0.03) {
                            return 2;
                          } else {
                            return 2;
                          }
                        }
                      }
                    } else {
                      if (Gy_squared <= 0.2) {
                        if (Gy_squared <= 0.14) {
                          return 2;
                        } else {
                          if (AxXAy <= -0.09) {
                            if (AzXGy <= 1.0) {
                              if (GxXGy <= -0.3) {
                                if (AxXAy <= -0.28) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AxXGx <= 0.28) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (Gx_squared <= 0.0) {
                              if (AyXAz <= 0.72) {
                                return 2;
                              } else {
                                if (AxXAz <= 0.1) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        if (Gy_squared <= 0.26) {
                          if (Gy <= -1.54) {
                            return 2;
                          } else {
                            return 2;
                          }
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (AxXAz <= 0.26) {
                      if (AzXGx <= -0.2) {
                        return 1;
                      } else {
                        if (AyXGy <= -0.51) {
                          return 1;
                        } else {
                          if (Gz <= -0.05) {
                            return 1;
                          } else {
                            return 1;
                          }
                        }
                      }
                    } else {
                      return 2;
                    }
                  }
                } else {
                  if (AxXAz <= 0.89) {
                    if (Ax <= 2.28) {
                      if (GxXGy <= 0.03) {
                        if (AxXGy <= 0.28) {
                          if (Az_squared <= 0.94) {
                            if (AzXGz <= -0.08) {
                              if (AxXAy <= -0.64) {
                                if (Gy_squared <= -0.15) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGx <= -0.46) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Gx <= 0.84) {
                                if (Gy <= -0.09) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (GyXGz <= -0.08) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (GxXGz <= 0.03) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    return 0;
                  }
                }
              }
            } else {
              if (AxXAy <= -1.59) {
                if (AxXAz <= -0.49) {
                  if (AzXGz <= -0.03) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  if (AyXGz <= -0.01) {
                    if (Ax_squared <= 2.35) {
                      if (Gx_squared <= -0.13) {
                        if (AxXAz <= -0.31) {
                          return 2;
                        } else {
                          return 2;
                        }
                      } else {
                        return 2;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    return 1;
                  }
                }
              } else {
                if (AyXGz <= 0.05) {
                  if (Gy_squared <= -0.15) {
                    if (AxXGx <= 0.01) {
                      if (AzXGz <= 0.02) {
                        if (AyXAz <= 0.33) {
                          return 0;
                        } else {
                          if (AxXAy <= -0.75) {
                            if (Ax_squared <= 0.4) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 2;
                      }
                    } else {
                      if (GyXGz <= -0.02) {
                        if (Gz <= -0.0) {
                          return 1;
                        } else {
                          return 0;
                        }
                      } else {
                        if (AyXAz <= 0.5) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    }
                  } else {
                    if (Ax_squared <= 2.55) {
                      if (Ay_squared <= -0.43) {
                        if (AxXAz <= -0.88) {
                          return 0;
                        } else {
                          if (AxXAy <= -1.19) {
                            return 2;
                          } else {
                            if (GxXGz <= -0.01) {
                              return 0;
                            } else {
                              if (Gx_squared <= -0.0) {
                                if (AzXGy <= -0.04) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      } else {
                        if (AxXAz <= -0.3) {
                          if (AzXGy <= 0.45) {
                            if (AyXGx <= -0.34) {
                              return 1;
                            } else {
                              if (Gx <= -0.08) {
                                if (AyXAz <= 0.49) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AxXGz <= 0.09) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (Ax <= -0.05) {
                            if (Az <= -0.26) {
                              if (GyXGz <= -0.03) {
                                return 1;
                              } else {
                                return 0;
                              }
                            } else {
                              if (Ay_squared <= -0.27) {
                                return 0;
                              } else {
                                if (GyXGz <= -0.0) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (Gy_squared <= -0.14) {
                              if (AxXGy <= -0.04) {
                                return 2;
                              } else {
                                if (Az_squared <= -0.05) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (AzXGy <= -0.15) {
                                if (Gx_squared <= -0.08) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AxXAy <= -1.04) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        }
                      }
                    } else {
                      if (AxXAz <= -0.97) {
                        return 0;
                      } else {
                        return 1;
                      }
                    }
                  }
                } else {
                  if (AxXAz <= -0.55) {
                    return 2;
                  } else {
                    if (AyXAz <= -0.09) {
                      if (AxXGx <= 0.17) {
                        if (AxXAy <= 1.0) {
                          if (Gy_squared <= -0.06) {
                            if (Az_squared <= -0.04) {
                              if (AzXGz <= 0.01) {
                                if (GxXGz <= 0.0) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (AyXGz <= 0.05) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AzXGy <= -0.09) {
                          return 0;
                        } else {
                          if (AzXGx <= 0.05) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AxXAy <= -1.19) {
                        return 1;
                      } else {
                        if (Gy_squared <= -0.14) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (Az <= -0.44) {
              if (GxXGz <= -0.0) {
                if (Gx <= 0.54) {
                  if (AxXGz <= -0.02) {
                    if (AxXAz <= -0.83) {
                      if (Ay <= -0.36) {
                        if (AxXGy <= 0.19) {
                          if (AyXAz <= 0.61) {
                            return 2;
                          } else {
                            if (Gx <= 0.3) {
                              return 2;
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        if (Gx_squared <= -0.12) {
                          return 1;
                        } else {
                          if (Ax <= 1.43) {
                            return 1;
                          } else {
                            if (AyXGx <= -0.16) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (Gy <= -0.45) {
                        return 0;
                      } else {
                        if (AyXGy <= 0.11) {
                          if (Gy_squared <= -0.02) {
                            if (AyXGx <= -0.11) {
                              if (Ay <= -0.55) {
                                if (AxXAz <= -0.17) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AzXGy <= -0.51) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (GyXGz <= -0.08) {
                                return 1;
                              } else {
                                if (AxXGy <= 0.0) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (Gz <= -0.42) {
                              if (AyXAz <= 0.74) {
                                return 1;
                              } else {
                                if (AyXGz <= 0.2) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXAz <= -0.46) {
                                if (AxXGy <= 0.46) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Ay <= -0.4) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          if (AxXGy <= -0.06) {
                            if (Ay <= -0.51) {
                              if (Gy <= -0.22) {
                                if (Gy_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AxXGz <= -0.11) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXGy <= -0.13) {
                                if (AxXAz <= -0.75) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gy <= -0.21) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (Ay_squared <= -0.38) {
                              return 1;
                            } else {
                              if (Gy_squared <= -0.13) {
                                if (Ay <= -0.55) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (AyXGy <= -0.06) {
                      if (Ax_squared <= -0.11) {
                        if (Az <= -1.49) {
                          return 2;
                        } else {
                          if (Gy <= 0.92) {
                            return 2;
                          } else {
                            if (AyXAz <= 0.75) {
                              return 1;
                            } else {
                              if (AxXAy <= 0.41) {
                                if (AxXAy <= 0.28) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      } else {
                        if (GxXGy <= 0.06) {
                          return 2;
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      if (GxXGz <= -0.01) {
                        if (AyXAz <= 0.64) {
                          return 1;
                        } else {
                          if (Az <= -1.06) {
                            return 1;
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        return 1;
                      }
                    }
                  }
                } else {
                  if (Gy_squared <= 0.11) {
                    if (AyXGz <= 0.1) {
                      return 1;
                    } else {
                      if (GxXGz <= -0.07) {
                        return 0;
                      } else {
                        if (AzXGy <= -0.3) {
                          return 2;
                        } else {
                          if (Ay_squared <= -0.49) {
                            return 0;
                          } else {
                            if (Az <= -0.8) {
                              if (AxXAy <= -0.34) {
                                return 1;
                              } else {
                                if (GxXGy <= -0.08) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (Ay_squared <= -0.49) {
                      return 2;
                    } else {
                      if (Gy_squared <= 0.31) {
                        if (Ax_squared <= -0.1) {
                          return 1;
                        } else {
                          return 2;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (AxXAz <= 0.3) {
                  if (GxXGz <= 0.01) {
                    if (Gy <= 0.9) {
                      if (AyXGy <= -0.0) {
                        if (Az <= -1.42) {
                          if (AxXAy <= -0.08) {
                            if (AxXGy <= 0.15) {
                              if (Gy_squared <= -0.12) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (GyXGz <= -0.03) {
                              if (AyXGy <= -0.27) {
                                return 1;
                              } else {
                                if (AyXGz <= 0.17) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AyXGy <= -0.02) {
                                return 1;
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          if (Gy_squared <= -0.15) {
                            if (Gz_squared <= -0.13) {
                              if (GyXGz <= -0.02) {
                                if (Az <= -0.73) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AyXGy <= -0.23) {
                              if (AxXGy <= 0.1) {
                                if (Az_squared <= 0.41) {
                                  return 0;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Ay <= -0.55) {
                                  return 2;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (Gy_squared <= -0.14) {
                                if (AzXGy <= -0.11) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Ax <= 1.54) {
                          if (AyXGx <= -0.33) {
                            if (AyXAz <= 0.79) {
                              return 1;
                            } else {
                              return 2;
                            }
                          } else {
                            if (Gy_squared <= -0.13) {
                              if (AyXGy <= 0.09) {
                                if (Az_squared <= 0.51) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Ay_squared <= -0.43) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AzXGx <= -0.01) {
                                if (AyXGy <= 0.25) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          }
                        } else {
                          if (AzXGx <= -0.06) {
                            if (GxXGy <= 0.0) {
                              if (Ay_squared <= -0.4) {
                                return 2;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AxXGz <= -0.03) {
                        if (Ay_squared <= -0.57) {
                          return 1;
                        } else {
                          if (Ay <= -0.55) {
                            if (AxXAz <= -0.19) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            if (Gy <= 1.01) {
                              return 1;
                            } else {
                              if (Gy <= 1.14) {
                                if (AzXGy <= -0.47) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.06) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AyXAz <= 0.7) {
                          return 0;
                        } else {
                          if (Gy <= 1.18) {
                            if (Az_squared <= 0.27) {
                              return 1;
                            } else {
                              if (AxXGx <= -0.0) {
                                if (Gx <= 0.18) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (GxXGz <= 0.01) {
                      if (AxXAz <= -0.33) {
                        if (Gx <= -0.14) {
                          if (AyXGx <= 0.06) {
                            return 1;
                          } else {
                            if (AxXAz <= -0.41) {
                              if (AyXGy <= -0.08) {
                                return 0;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AzXGz <= 0.07) {
                            return 0;
                          } else {
                            if (AzXGy <= -0.24) {
                              return 0;
                            } else {
                              if (AxXAy <= -0.64) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      } else {
                        if (Ay_squared <= -0.49) {
                          if (AyXGy <= -0.18) {
                            return 2;
                          } else {
                            if (GxXGy <= 0.02) {
                              return 1;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (GxXGy <= 0.0) {
                            if (AzXGx <= 0.09) {
                              return 1;
                            } else {
                              if (AzXGy <= -0.17) {
                                if (Gy_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Gx <= -0.15) {
                              if (Ay <= -0.48) {
                                if (Gy_squared <= -0.14) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gy_squared <= -0.13) {
                                if (AxXGx <= -0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gy <= 0.69) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      }
                    } else {
                      if (AxXGx <= -0.16) {
                        if (GxXGz <= 0.02) {
                          return 0;
                        } else {
                          if (Gz_squared <= -0.12) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AyXAz <= 0.69) {
                          if (GxXGy <= 0.05) {
                            if (Ax_squared <= -0.15) {
                              return 0;
                            } else {
                              if (AyXGz <= 0.22) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (GxXGy <= 0.02) {
                            if (Ay <= -0.46) {
                              if (AyXGx <= 0.07) {
                                return 0;
                              } else {
                                if (Gz_squared <= -0.12) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              if (Ay_squared <= -0.63) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Ay <= -0.55) {
                              return 0;
                            } else {
                              if (Gz_squared <= -0.13) {
                                return 1;
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (GyXGz <= -0.02) {
                    if (Ay <= -0.43) {
                      if (AyXGy <= -0.52) {
                        return 2;
                      } else {
                        if (AxXAz <= 0.47) {
                          if (GyXGz <= -0.04) {
                            return 2;
                          } else {
                            return 1;
                          }
                        } else {
                          return 2;
                        }
                      }
                    } else {
                      if (AxXGx <= 0.02) {
                        if (AxXGx <= -0.03) {
                          return 2;
                        } else {
                          if (Az <= -1.49) {
                            return 2;
                          } else {
                            return 2;
                          }
                        }
                      } else {
                        return 2;
                      }
                    }
                  } else {
                    if (AyXGy <= 0.38) {
                      if (AyXAz <= 0.72) {
                        return 1;
                      } else {
                        if (GxXGz <= 0.0) {
                          return 1;
                        } else {
                          return 1;
                        }
                      }
                    } else {
                      return 2;
                    }
                  }
                }
              }
            } else {
              if (AxXAz <= -0.24) {
                if (Gy_squared <= -0.15) {
                  if (Az <= 0.18) {
                    if (AyXGy <= 0.01) {
                      return 1;
                    } else {
                      return 1;
                    }
                  } else {
                    return 1;
                  }
                } else {
                  if (AxXAy <= -0.79) {
                    if (Ay <= -0.34) {
                      if (AxXAz <= -0.56) {
                        if (GyXGz <= -0.02) {
                          return 1;
                        } else {
                          if (AxXAy <= -1.35) {
                            return 2;
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AxXGx <= 0.12) {
                          if (AzXGz <= 0.07) {
                            if (GxXGy <= 0.01) {
                              return 0;
                            } else {
                              return 1;
                            }
                          } else {
                            if (AyXAz <= 0.44) {
                              if (Gy_squared <= -0.12) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 2;
                            }
                          }
                        } else {
                          if (AxXGy <= -0.22) {
                            return 0;
                          } else {
                            if (AzXGy <= 0.02) {
                              if (AzXGx <= -0.07) {
                                return 0;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          }
                        }
                      }
                    } else {
                      return 2;
                    }
                  } else {
                    if (GyXGz <= -0.01) {
                      if (Ay <= -0.52) {
                        return 1;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (AyXAz <= -0.0) {
                  if (AxXGx <= 0.17) {
                    if (Ay <= -0.2) {
                      if (Gy_squared <= -0.07) {
                        if (GxXGz <= 0.01) {
                          if (AxXAz <= 0.06) {
                            return 2;
                          } else {
                            return 0;
                          }
                        } else {
                          if (Gy_squared <= -0.14) {
                            return 2;
                          } else {
                            if (AyXGy <= 0.21) {
                              if (AxXGz <= -0.1) {
                                return 2;
                              } else {
                                return 0;
                              }
                            } else {
                              return 2;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (AzXGx <= 0.08) {
                      return 0;
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (Ax <= 1.6) {
                    if (Ay_squared <= -0.24) {
                      if (AxXAz <= 0.04) {
                        if (AyXAz <= 0.28) {
                          if (AyXAz <= 0.23) {
                            if (AzXGx <= -0.07) {
                              return 0;
                            } else {
                              if (AyXAz <= 0.18) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          if (Ay <= -0.5) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (GxXGy <= 0.02) {
                          if (AzXGx <= 0.05) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (GyXGz <= -0.01) {
                        if (AyXGx <= 0.02) {
                          if (Gy_squared <= -0.07) {
                            if (AyXAz <= 0.2) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          if (AyXGy <= -0.19) {
                            return 0;
                          } else {
                            return 2;
                          }
                        }
                      } else {
                        if (AzXGz <= 0.08) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (Gx_squared <= -0.12) {
                      return 2;
                    } else {
                      return 1;
                    }
                  }
                }
              }
            }
          }
        } else {
          if (Gy_squared <= -0.05) {
            if (Az_squared <= -0.15) {
              if (AxXAy <= 0.54) {
                if (Gy <= 0.03) {
                  if (GxXGy <= 0.01) {
                    if (AzXGx <= 0.01) {
                      if (AxXGy <= -0.02) {
                        if (AyXGz <= 0.01) {
                          return 1;
                        } else {
                          if (Ay_squared <= 0.09) {
                            if (Ay <= 1.51) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (GxXGy <= 0.01) {
                          if (Az <= 0.07) {
                            if (AzXGx <= -0.02) {
                              if (AxXGy <= -0.01) {
                                return 0;
                              } else {
                                if (Gx <= 0.23) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AzXGy <= 0.07) {
                                if (AxXAz <= 0.06) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (GyXGz <= -0.06) {
                              return 2;
                            } else {
                              if (GxXGz <= 0.02) {
                                if (Ay_squared <= 0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GxXGz <= 0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        } else {
                          if (AzXGz <= 0.0) {
                            if (AxXGy <= 0.01) {
                              if (AzXGy <= -0.01) {
                                return 1;
                              } else {
                                if (AzXGz <= -0.03) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AyXAz <= -0.48) {
                                return 1;
                              } else {
                                return 2;
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    } else {
                      if (AzXGy <= -0.03) {
                        if (Ay_squared <= 0.04) {
                          if (AyXAz <= 0.11) {
                            if (AzXGz <= 0.02) {
                              return 1;
                            } else {
                              if (AyXGx <= 0.09) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        if (GyXGz <= -0.03) {
                          if (AyXGz <= 0.18) {
                            if (AyXGy <= -0.35) {
                              return 1;
                            } else {
                              if (Ay_squared <= 0.04) {
                                if (AyXAz <= -0.32) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (Gz_squared <= -0.11) {
                              if (AxXGz <= -0.0) {
                                if (Gy_squared <= -0.14) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (GyXGz <= -0.02) {
                            if (AzXGy <= -0.02) {
                              if (Gx <= 0.11) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (AxXGz <= -0.06) {
                                return 0;
                              } else {
                                if (AzXGz <= -0.0) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (Gx_squared <= -0.13) {
                              if (Ax_squared <= -0.13) {
                                if (Ay <= 1.53) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gz <= -0.21) {
                                return 1;
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (Gz <= -0.05) {
                      if (AxXGy <= -0.01) {
                        if (AyXGx <= -0.04) {
                          if (Gy <= -0.34) {
                            if (AyXAz <= -0.42) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            if (AzXGy <= 0.02) {
                              return 1;
                            } else {
                              if (AxXGy <= -0.03) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        if (AyXAz <= -0.39) {
                          if (Gx_squared <= -0.1) {
                            if (AxXGx <= 0.03) {
                              if (AyXGx <= -0.02) {
                                if (Ay_squared <= -0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gz <= -0.26) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          if (GxXGz <= 0.01) {
                            if (Ay <= 1.51) {
                              if (AzXGy <= -0.02) {
                                return 1;
                              } else {
                                if (AzXGy <= -0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXGx <= -0.01) {
                                if (AzXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXAz <= -0.34) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (GyXGz <= -0.01) {
                              if (Gy_squared <= -0.14) {
                                if (AyXAz <= -0.19) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gy_squared <= -0.12) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    } else {
                      if (Gz <= 0.23) {
                        if (Gx <= -0.91) {
                          return 0;
                        } else {
                          if (Gx_squared <= -0.13) {
                            if (Gy_squared <= -0.12) {
                              if (Gy <= -0.25) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AxXGx <= -0.01) {
                              if (AyXGx <= -0.21) {
                                if (Gz <= 0.17) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GxXGy <= 0.04) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXAz <= 0.13) {
                                if (AyXGy <= -0.42) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GxXGy <= 0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (GxXGy <= 0.03) {
                          if (AzXGz <= -0.01) {
                            if (Ay <= 1.53) {
                              if (Ax_squared <= -0.13) {
                                if (AyXGz <= 0.25) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          if (Gx_squared <= -0.08) {
                            if (AzXGx <= 0.07) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (GxXGz <= 0.01) {
                    if (Gz_squared <= -0.13) {
                      if (GxXGy <= 0.01) {
                        if (Ay_squared <= -0.01) {
                          return 1;
                        } else {
                          if (GxXGy <= 0.0) {
                            return 1;
                          } else {
                            if (Gz <= -0.07) {
                              return 1;
                            } else {
                              if (AzXGz <= 0.01) {
                                return 1;
                              } else {
                                if (Ax_squared <= -0.15) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AxXAz <= 0.1) {
                          if (AzXGx <= 0.03) {
                            if (GyXGz <= -0.03) {
                              if (Ax_squared <= -0.15) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (AyXAz <= -0.53) {
                                return 1;
                              } else {
                                if (GxXGz <= 0.01) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 1;
                        }
                      }
                    } else {
                      if (AyXAz <= -0.24) {
                        if (AxXAz <= 0.04) {
                          if (AzXGy <= -0.11) {
                            return 0;
                          } else {
                            if (AxXGy <= 0.01) {
                              return 1;
                            } else {
                              if (AzXGz <= -0.04) {
                                return 1;
                              } else {
                                if (AzXGx <= -0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        } else {
                          if (AyXGx <= -0.32) {
                            return 1;
                          } else {
                            if (AzXGz <= 0.07) {
                              if (AxXGy <= -0.01) {
                                if (AzXGy <= -0.05) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gz <= 0.22) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (Gz <= -0.42) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      } else {
                        if (Gx <= 0.11) {
                          if (AxXAz <= 0.08) {
                            return 1;
                          } else {
                            return 1;
                          }
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (Gy_squared <= -0.12) {
                      if (AyXAz <= -0.47) {
                        if (AyXGz <= 0.01) {
                          if (AzXGx <= 0.07) {
                            if (AyXGy <= 0.05) {
                              if (GxXGy <= 0.01) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          if (GyXGz <= -0.01) {
                            if (AzXGz <= -0.01) {
                              if (AzXGx <= -0.11) {
                                return 1;
                              } else {
                                if (AzXGx <= -0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXGz <= -0.01) {
                                if (GyXGz <= -0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AyXGy <= 0.17) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            if (AxXAy <= 0.25) {
                              if (GxXGz <= 0.02) {
                                if (AzXGz <= -0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              if (Ay <= 1.52) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        }
                      } else {
                        if (GxXGy <= 0.03) {
                          if (AyXGz <= 0.02) {
                            if (GxXGy <= 0.01) {
                              if (AzXGz <= 0.04) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gx <= -0.07) {
                                if (Gz <= -0.3) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (AyXAz <= -0.1) {
                              if (AzXGz <= 0.01) {
                                if (AyXGy <= 0.09) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Az <= 0.61) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AyXAz <= 0.09) {
                                if (Gz_squared <= -0.13) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (Gz <= 0.12) {
                            if (Ay <= 1.51) {
                              if (GyXGz <= -0.02) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (GxXGz <= 0.01) {
                                return 1;
                              } else {
                                if (AxXAy <= 0.16) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    } else {
                      if (AzXGz <= 0.01) {
                        if (Gy_squared <= -0.12) {
                          return 1;
                        } else {
                          if (AyXGx <= 0.38) {
                            if (Ay <= 1.58) {
                              if (AzXGy <= -0.08) {
                                if (GxXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AzXGx <= -0.04) {
                          return 1;
                        } else {
                          if (Gy_squared <= -0.09) {
                            if (Gx_squared <= -0.11) {
                              if (AzXGy <= -0.03) {
                                if (Gz_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (Gx_squared <= -0.12) {
                              return 1;
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (GxXGy <= 0.01) {
                  if (AxXGx <= -0.01) {
                    if (Gz <= -0.47) {
                      return 0;
                    } else {
                      if (AxXGx <= -0.11) {
                        if (Gz <= 0.01) {
                          return 0;
                        } else {
                          return 1;
                        }
                      } else {
                        if (AxXAy <= 0.79) {
                          if (GyXGz <= -0.02) {
                            if (GxXGy <= 0.01) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            if (GyXGz <= -0.01) {
                              if (AxXAz <= -0.04) {
                                return 1;
                              } else {
                                if (AzXGy <= -0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AxXAz <= -0.12) {
                            return 0;
                          } else {
                            return 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (Ay <= 1.39) {
                      return 0;
                    } else {
                      if (Az <= 0.21) {
                        if (AyXGz <= 0.21) {
                          if (GyXGz <= -0.03) {
                            return 0;
                          } else {
                            if (AxXAy <= 0.83) {
                              if (AyXGz <= 0.13) {
                                if (AxXAy <= 0.68) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        if (Gz <= -0.2) {
                          if (AxXAy <= 0.72) {
                            return 1;
                          } else {
                            return 0;
                          }
                        } else {
                          if (Az_squared <= -0.28) {
                            return 0;
                          } else {
                            if (Ax_squared <= 0.03) {
                              if (AzXGz <= 0.02) {
                                if (Ay <= 1.52) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AzXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (GxXGz <= 0.01) {
                    if (Ax <= 0.52) {
                      if (AxXGy <= -0.09) {
                        if (GxXGz <= 0.01) {
                          if (Ay_squared <= 0.04) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (Az_squared <= -0.22) {
                          if (AxXAz <= 0.08) {
                            if (AyXAz <= -0.21) {
                              if (AxXAy <= 0.55) {
                                return 1;
                              } else {
                                if (AzXGy <= -0.01) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (Gx_squared <= -0.13) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (Gx <= -0.2) {
                            if (AzXGz <= -0.0) {
                              return 1;
                            } else {
                              return 1;
                            }
                          } else {
                            if (Gy <= -0.03) {
                              return 0;
                            } else {
                              if (Gx_squared <= -0.06) {
                                if (AyXGy <= 0.25) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      }
                    } else {
                      if (Az_squared <= -0.25) {
                        if (AzXGz <= 0.03) {
                          if (Gy_squared <= -0.14) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (AxXAy <= 1.06) {
                            return 1;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (GxXGy <= 0.07) {
                          if (Gx_squared <= -0.13) {
                            if (AzXGy <= 0.04) {
                              if (AyXGy <= -0.17) {
                                return 1;
                              } else {
                                if (AxXGy <= -0.05) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXAy <= 0.84) {
                              return 1;
                            } else {
                              if (AxXAy <= 0.9) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (Ay_squared <= -0.04) {
                      if (Gx_squared <= -0.12) {
                        return 1;
                      } else {
                        if (Gz_squared <= -0.13) {
                          if (GyXGz <= -0.02) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (GxXGy <= 0.08) {
                        if (Gz_squared <= -0.13) {
                          if (Gx_squared <= -0.11) {
                            if (Ay_squared <= 0.07) {
                              if (Gx <= -0.12) {
                                return 1;
                              } else {
                                if (Gy <= 0.23) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AxXAz <= -0.05) {
                              return 0;
                            } else {
                              if (AyXAz <= -0.23) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (AxXGy <= 0.02) {
                            return 1;
                          } else {
                            if (AxXGy <= 0.11) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        }
                      } else {
                        return 1;
                      }
                    }
                  }
                }
              }
            } else {
              if (Ax_squared <= -0.15) {
                if (Gz <= -0.1) {
                  if (Az <= -0.15) {
                    if (AzXGy <= 0.04) {
                      if (Gy <= 0.25) {
                        if (GxXGz <= 0.01) {
                          if (AzXGz <= 0.09) {
                            if (AyXAz <= -0.74) {
                              return 2;
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (Gx_squared <= -0.09) {
                          return 2;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 1;
                    }
                  } else {
                    if (Ay_squared <= 0.09) {
                      if (AzXGx <= -0.0) {
                        return 2;
                      } else {
                        return 1;
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (Ay <= 0.41) {
                    return 0;
                  } else {
                    if (AxXAz <= -0.0) {
                      return 1;
                    } else {
                      if (Ay_squared <= -0.55) {
                        if (AxXGz <= -0.02) {
                          return 1;
                        } else {
                          return 0;
                        }
                      } else {
                        if (Ay_squared <= -0.14) {
                          if (GyXGz <= -0.02) {
                            return 1;
                          } else {
                            if (Ay <= 1.42) {
                              return 2;
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AyXAz <= -0.73) {
                            if (AyXGz <= 0.1) {
                              return 2;
                            } else {
                              if (Gx_squared <= -0.13) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            if (GxXGy <= 0.01) {
                              if (GxXGy <= 0.01) {
                                return 1;
                              } else {
                                return 0;
                              }
                            } else {
                              if (Gx <= -0.21) {
                                return 1;
                              } else {
                                if (GxXGz <= 0.02) {
                                  return 1;
                                } else {
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
              } else {
                if (Ay_squared <= -0.27) {
                  if (AyXAz <= 0.5) {
                    if (Az <= 4.28) {
                      if (Ay_squared <= -1.29) {
                        return 1;
                      } else {
                        if (AyXGx <= -0.0) {
                          if (AxXGx <= -0.07) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          if (Gy <= -0.28) {
                            return 0;
                          } else {
                            if (Gy_squared <= -0.14) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    return 2;
                  }
                } else {
                  if (AxXGy <= -0.04) {
                    if (GxXGy <= 0.01) {
                      if (GyXGz <= -0.02) {
                        if (AzXGz <= -0.04) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (Gx_squared <= -0.03) {
                        if (Gz <= 0.23) {
                          if (Gy <= -0.21) {
                            if (AzXGy <= 0.14) {
                              if (Ay <= 1.5) {
                                return 1;
                              } else {
                                if (AxXGx <= -0.07) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (GxXGz <= 0.01) {
                              return 1;
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (Gx <= -0.01) {
                      if (AxXGz <= -0.06) {
                        return 0;
                      } else {
                        if (AyXGx <= -0.3) {
                          return 0;
                        } else {
                          if (Az <= 1.78) {
                            if (Ay <= 1.44) {
                              return 1;
                            } else {
                              if (Ax_squared <= -0.1) {
                                if (GyXGz <= -0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gz_squared <= -0.12) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        }
                      }
                    } else {
                      if (AyXGy <= 0.01) {
                        if (AxXGz <= 0.04) {
                          if (AzXGx <= -0.06) {
                            return 1;
                          } else {
                            if (GyXGz <= -0.03) {
                              if (GxXGz <= 0.01) {
                                return 0;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gy <= -0.16) {
                                return 0;
                              } else {
                                if (AxXGz <= 0.01) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AxXGy <= 0.03) {
                          if (Gz <= -0.1) {
                            return 1;
                          } else {
                            if (Gz_squared <= -0.12) {
                              if (GxXGy <= 0.02) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          if (AxXAz <= -0.15) {
                            return 0;
                          } else {
                            if (AzXGz <= 0.01) {
                              if (AyXGx <= 0.22) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Ay_squared <= 0.09) {
                                return 0;
                              } else {
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
          } else {
            if (AyXGz <= 0.21) {
              if (Gy_squared <= -0.0) {
                if (AyXGy <= -0.53) {
                  if (Gx <= -0.36) {
                    if (AxXGx <= -0.24) {
                      return 1;
                    } else {
                      return 0;
                    }
                  } else {
                    return 1;
                  }
                } else {
                  if (AyXGx <= -0.01) {
                    if (AxXGy <= 0.1) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    if (AxXGx <= 0.14) {
                      if (Ay <= 1.43) {
                        return 0;
                      } else {
                        if (AyXGz <= 0.14) {
                          if (AyXGx <= 0.27) {
                            return 0;
                          } else {
                            return 1;
                          }
                        } else {
                          return 1;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (Ay_squared <= -0.27) {
                  if (Ax <= -0.9) {
                    return 0;
                  } else {
                    if (AyXAz <= -0.53) {
                      if (AyXGz <= 0.07) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (Gx_squared <= 0.24) {
                    if (AxXAz <= -0.04) {
                      if (Gx_squared <= -0.09) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      if (AyXGy <= 0.65) {
                        if (AyXGz <= 0.19) {
                          if (AzXGx <= 0.12) {
                            if (GxXGy <= 0.03) {
                              return 0;
                            } else {
                              if (AzXGx <= 0.01) {
                                return 0;
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AzXGz <= 0.03) {
                          if (AyXGx <= 0.18) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (GxXGy <= 0.17) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (AyXGz <= -0.08) {
                      return 0;
                    } else {
                      if (Gz <= -0.2) {
                        return 1;
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              }
            } else {
              if (Gy <= -0.87) {
                if (Gx_squared <= -0.09) {
                  if (AzXGx <= 0.06) {
                    return 2;
                  } else {
                    if (Gy <= -1.03) {
                      return 2;
                    } else {
                      if (AzXGz <= -0.04) {
                        return 2;
                      } else {
                        return 2;
                      }
                    }
                  }
                } else {
                  return 0;
                }
              } else {
                if (Gy <= 1.14) {
                  if (AxXGz <= -0.03) {
                    return 1;
                  } else {
                    return 0;
                  }
                } else {
                  return 0;
                }
              }
            }
          }
        }
      }
    } else {
      if (Gx_squared <= -0.11) {
        if (GyXGz <= -0.15) {
          if (AyXAz <= -0.7) {
            if (AyXGy <= -0.53) {
              if (AyXAz <= -0.98) {
                if (AzXGx <= 0.13) {
                  if (Gz_squared <= -0.03) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  return 0;
                }
              } else {
                if (AxXAz <= 0.1) {
                  if (AyXGz <= 0.53) {
                    return 0;
                  } else {
                    if (AxXGy <= -0.3) {
                      return 2;
                    } else {
                      if (AyXGz <= 0.62) {
                        return 2;
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  return 0;
                }
              }
            } else {
              if (GyXGz <= -0.2) {
                if (Gz_squared <= 0.02) {
                  if (AxXAz <= -0.07) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  if (AxXGz <= 0.03) {
                    if (Gy_squared <= -0.05) {
                      return 0;
                    } else {
                      if (AxXGy <= 0.4) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    return 0;
                  }
                }
              } else {
                if (Az <= -0.55) {
                  return 0;
                } else {
                  return 0;
                }
              }
            }
          } else {
            if (Gy <= -0.32) {
              if (Az_squared <= -0.2) {
                if (AxXAy <= 0.51) {
                  if (Gy <= -1.33) {
                    return 2;
                  } else {
                    if (AxXGz <= -0.26) {
                      return 2;
                    } else {
                      if (Az_squared <= -0.23) {
                        if (AzXGy <= -0.08) {
                          return 2;
                        } else {
                          if (AxXAz <= 0.1) {
                            if (Gz_squared <= 0.01) {
                              if (AzXGx <= 0.01) {
                                return 2;
                              } else {
                                if (AyXGz <= 0.58) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (AxXGz <= -0.07) {
                                return 2;
                              } else {
                                if (AzXGx <= 0.04) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AyXGy <= -0.82) {
                              return 0;
                            } else {
                              if (AzXGy <= 0.1) {
                                if (Gx_squared <= -0.13) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              } else {
                                if (Gz_squared <= -0.01) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (AxXGz <= -0.19) {
                          return 1;
                        } else {
                          if (AzXGx <= -0.01) {
                            return 2;
                          } else {
                            if (AxXGz <= 0.02) {
                              if (GyXGz <= -0.28) {
                                return 2;
                              } else {
                                if (AzXGy <= 0.2) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              if (Gz <= 0.97) {
                                return 2;
                              } else {
                                return 2;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (Ay_squared <= 0.07) {
                    if (AxXAz <= -0.02) {
                      return 2;
                    } else {
                      if (Gz_squared <= 0.01) {
                        return 0;
                      } else {
                        return 2;
                      }
                    }
                  } else {
                    return 2;
                  }
                }
              } else {
                if (Ay_squared <= -0.51) {
                  return 0;
                } else {
                  if (Gx_squared <= -0.13) {
                    if (AxXAy <= 0.66) {
                      if (AyXGz <= 0.56) {
                        if (Gz_squared <= 0.07) {
                          if (AxXAy <= 0.34) {
                            return 1;
                          } else {
                            return 2;
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (Gz <= 1.08) {
                          if (AxXAz <= 0.13) {
                            if (AxXGy <= -0.01) {
                              if (GyXGz <= -0.25) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 2;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 2;
                    }
                  } else {
                    if (Gy_squared <= 0.12) {
                      if (AyXGz <= -0.48) {
                        return 2;
                      } else {
                        if (AzXGx <= -0.04) {
                          return 1;
                        } else {
                          if (AxXAz <= 0.04) {
                            if (AyXGz <= 0.41) {
                              return 1;
                            } else {
                              return 2;
                            }
                          } else {
                            if (AxXAy <= 0.15) {
                              return 0;
                            } else {
                              return 2;
                            }
                          }
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              }
            } else {
              if (AyXGy <= -0.37) {
                if (AyXGz <= 0.34) {
                  return 1;
                } else {
                  if (AxXGz <= -0.05) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              } else {
                if (AzXGz <= 0.16) {
                  return 0;
                } else {
                  if (Gy_squared <= 0.04) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              }
            }
          }
        } else {
          if (AxXGz <= -0.18) {
            if (Ay <= 0.34) {
              if (AyXGz <= 0.33) {
                if (Az <= 1.09) {
                  if (AzXGx <= -0.05) {
                    if (Az_squared <= 0.51) {
                      return 1;
                    } else {
                      return 2;
                    }
                  } else {
                    if (Ax_squared <= -0.03) {
                      return 2;
                    } else {
                      if (AxXAz <= -0.46) {
                        return 1;
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  return 2;
                }
              } else {
                if (Az_squared <= 0.2) {
                  if (AyXAz <= -0.26) {
                    return 0;
                  } else {
                    if (Ax_squared <= 0.31) {
                      if (AzXGz <= 0.3) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  }
                } else {
                  return 0;
                }
              }
            } else {
              if (AzXGz <= 0.41) {
                if (Gy_squared <= -0.14) {
                  return 0;
                } else {
                  if (Ax <= -1.24) {
                    return 0;
                  } else {
                    if (Ay <= 1.43) {
                      return 0;
                    } else {
                      if (AzXGy <= 0.26) {
                        if (Gx <= 0.28) {
                          if (GxXGy <= -0.0) {
                            return 0;
                          } else {
                            if (AxXGz <= -0.2) {
                              if (Gz_squared <= -0.06) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (Ax <= 1.15) {
                  if (Gy_squared <= -0.11) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  return 0;
                }
              }
            }
          } else {
            if (AzXGz <= 0.17) {
              if (AyXAz <= 0.62) {
                if (Ay_squared <= -0.29) {
                  if (Ay <= -0.24) {
                    if (Gy_squared <= -0.12) {
                      if (Gy_squared <= -0.14) {
                        return 0;
                      } else {
                        return 2;
                      }
                    } else {
                      if (AxXGy <= -0.16) {
                        return 0;
                      } else {
                        if (Gy <= 0.66) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AzXGz <= -0.21) {
                      if (Ay <= 0.89) {
                        return 0;
                      } else {
                        if (Ay_squared <= -0.49) {
                          return 0;
                        } else {
                          if (AxXGy <= -0.04) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AxXAz <= 0.02) {
                        return 0;
                      } else {
                        return 1;
                      }
                    }
                  }
                } else {
                  if (AyXGy <= -0.17) {
                    if (GxXGy <= 0.06) {
                      if (AyXAz <= -0.3) {
                        if (AxXAz <= -0.11) {
                          if (GxXGy <= -0.01) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (AyXGy <= -0.62) {
                            return 2;
                          } else {
                            if (AyXGz <= 0.31) {
                              return 1;
                            } else {
                              if (Gx_squared <= -0.13) {
                                if (AxXAy <= 0.38) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (Gy_squared <= -0.11) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          }
                        }
                      } else {
                        if (Gz_squared <= -0.09) {
                          if (AyXAz <= -0.07) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (AzXGx <= 0.03) {
                            if (Gz_squared <= -0.04) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (Gz_squared <= -0.09) {
                        return 0;
                      } else {
                        if (Gy <= -0.64) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AyXAz <= -0.92) {
                      if (Ax <= -0.67) {
                        return 2;
                      } else {
                        if (GyXGz <= 0.02) {
                          if (AxXAy <= 0.21) {
                            return 0;
                          } else {
                            if (AyXGz <= 0.4) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AzXGz <= -0.13) {
                        if (AxXAz <= 0.12) {
                          if (AxXGy <= 0.02) {
                            if (Gy <= -0.48) {
                              return 1;
                            } else {
                              if (AyXGz <= -0.31) {
                                return 0;
                              } else {
                                if (Ax_squared <= -0.06) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            if (AxXGy <= 0.13) {
                              if (AzXGx <= 0.05) {
                                if (AyXAz <= -0.59) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (Ay_squared <= 0.04) {
                            if (AxXGy <= 0.02) {
                              if (Gz <= 0.65) {
                                return 2;
                              } else {
                                return 2;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 1;
                          }
                        }
                      } else {
                        if (AyXAz <= -0.21) {
                          if (GxXGy <= 0.0) {
                            if (GxXGz <= -0.03) {
                              return 1;
                            } else {
                              if (Gz <= 0.36) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            if (AyXGz <= 0.37) {
                              if (AzXGz <= -0.06) {
                                if (AxXAz <= -0.09) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.03) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              if (AxXGy <= 0.01) {
                                if (GxXGz <= 0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (GyXGz <= -0.04) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              }
                            }
                          }
                        } else {
                          if (Gz <= 0.74) {
                            if (AxXGx <= -0.06) {
                              return 1;
                            } else {
                              if (GxXGz <= 0.01) {
                                return 0;
                              } else {
                                if (AzXGz <= 0.01) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 2;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (AyXGy <= 0.29) {
                  if (Gz_squared <= 0.01) {
                    if (AxXAy <= -0.64) {
                      return 0;
                    } else {
                      if (GxXGy <= 0.03) {
                        if (AzXGy <= -0.14) {
                          if (Gx_squared <= -0.13) {
                            return 1;
                          } else {
                            if (Gy_squared <= -0.14) {
                              return 1;
                            } else {
                              if (Ay <= -0.52) {
                                return 1;
                              } else {
                                return 1;
                              }
                            }
                          }
                        } else {
                          if (GxXGy <= 0.02) {
                            if (AxXAz <= 0.09) {
                              if (Gx <= 0.12) {
                                return 1;
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AxXAy <= 0.26) {
                          return 1;
                        } else {
                          return 2;
                        }
                      }
                    }
                  } else {
                    if (AxXGz <= 0.24) {
                      return 2;
                    } else {
                      return 0;
                    }
                  }
                } else {
                  if (AxXAz <= 0.24) {
                    if (GxXGy <= 0.02) {
                      return 1;
                    } else {
                      if (Gy <= -0.68) {
                        return 1;
                      } else {
                        if (AxXAz <= -0.45) {
                          return 1;
                        } else {
                          if (GyXGz <= -0.11) {
                            return 1;
                          } else {
                            if (GyXGz <= -0.09) {
                              if (AyXGx <= 0.15) {
                                if (GxXGy <= 0.05) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            } else {
                              return 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    return 2;
                  }
                }
              }
            } else {
              if (Ay_squared <= 0.27) {
                if (AxXAy <= 0.35) {
                  if (AyXAz <= -0.7) {
                    if (Az <= -0.73) {
                      return 0;
                    } else {
                      if (Ay <= -0.27) {
                        return 2;
                      } else {
                        if (AxXGz <= -0.0) {
                          if (AzXGy <= 0.22) {
                            if (Az_squared <= 0.03) {
                              if (AxXGz <= -0.08) {
                                return 2;
                              } else {
                                if (Ay <= 1.47) {
                                  return 2;
                                } else {
                                  return 2;
                                }
                              }
                            } else {
                              return 2;
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 0;
                        }
                      }
                    }
                  } else {
                    if (AzXGy <= -0.34) {
                      return 1;
                    } else {
                      if (AyXAz <= 0.76) {
                        if (Az <= 1.21) {
                          if (GxXGz <= 0.06) {
                            if (AxXGy <= -0.02) {
                              return 0;
                            } else {
                              if (GxXGy <= 0.01) {
                                if (AxXAy <= 0.15) {
                                  return 0;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 2;
                        }
                      } else {
                        if (AxXGx <= 0.0) {
                          if (Ay_squared <= -0.53) {
                            return 2;
                          } else {
                            return 0;
                          }
                        } else {
                          return 2;
                        }
                      }
                    }
                  }
                } else {
                  if (AxXAz <= -0.08) {
                    return 0;
                  } else {
                    if (AzXGy <= -0.08) {
                      return 0;
                    } else {
                      if (Ay <= 1.42) {
                        return 1;
                      } else {
                        return 1;
                      }
                    }
                  }
                }
              } else {
                if (AyXGz <= -0.34) {
                  if (Gx_squared <= -0.13) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  return 0;
                }
              }
            }
          }
        }
      } else {
        if (Ay_squared <= 0.15) {
          if (Ay <= 0.15) {
            if (AxXAy <= 1.26) {
              if (Az_squared <= 0.12) {
                if (AyXGz <= -0.32) {
                  if (Gy_squared <= -0.06) {
                    if (GxXGz <= 0.09) {
                      if (Ay_squared <= -0.45) {
                        return 0;
                      } else {
                        if (AxXGz <= 0.47) {
                          if (AzXGz <= -0.43) {
                            return 0;
                          } else {
                            if (Gx <= -1.5) {
                              return 1;
                            } else {
                              if (AyXGz <= -0.38) {
                                if (Gy <= 0.38) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 2;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AyXGz <= -0.49) {
                        if (Gy_squared <= -0.12) {
                          return 0;
                        } else {
                          return 2;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (GyXGz <= -0.3) {
                      return 0;
                    } else {
                      if (AzXGy <= -0.04) {
                        if (Ay_squared <= -0.69) {
                          return 0;
                        } else {
                          if (AxXGy <= 0.14) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (AyXGz <= 0.93) {
                    if (Gy <= -0.92) {
                      if (Az <= -0.55) {
                        return 0;
                      } else {
                        if (AxXGz <= -0.72) {
                          return 0;
                        } else {
                          if (AxXGz <= 0.15) {
                            if (Az_squared <= -0.07) {
                              if (AyXGz <= 0.35) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      if (AyXAz <= -0.05) {
                        if (AyXAz <= -0.55) {
                          return 2;
                        } else {
                          if (Gx_squared <= -0.02) {
                            if (Az_squared <= -0.28) {
                              return 2;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (Gz <= -0.87) {
                          if (AyXGx <= -0.67) {
                            return 0;
                          } else {
                            if (Gy_squared <= -0.12) {
                              if (AxXGx <= 0.11) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              if (GxXGy <= 0.1) {
                                if (GxXGy <= -0.23) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          }
                        } else {
                          if (GxXGz <= -0.03) {
                            if (AyXAz <= 0.55) {
                              if (GxXGy <= -0.07) {
                                if (Az_squared <= -0.13) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (Gx <= -0.91) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 1;
                            }
                          } else {
                            if (AyXGz <= -0.28) {
                              return 1;
                            } else {
                              if (AxXAz <= 0.05) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (AyXGy <= 1.26) {
                      if (AxXAz <= -0.05) {
                        return 0;
                      } else {
                        if (AyXGy <= -0.37) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 1;
                    }
                  }
                }
              } else {
                if (Ax <= 0.63) {
                  if (AyXGz <= 0.39) {
                    if (AzXGz <= 0.46) {
                      if (GyXGz <= -0.01) {
                        if (AyXGz <= -0.34) {
                          if (Gz <= 2.02) {
                            if (Ay_squared <= -0.27) {
                              if (AyXAz <= 0.71) {
                                return 2;
                              } else {
                                return 1;
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          if (AxXAz <= 0.13) {
                            if (Gx_squared <= -0.09) {
                              return 1;
                            } else {
                              if (Gy <= -0.2) {
                                return 1;
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            if (Gx <= 0.55) {
                              return 2;
                            } else {
                              return 1;
                            }
                          }
                        }
                      } else {
                        if (AyXAz <= 0.62) {
                          return 0;
                        } else {
                          if (AxXGy <= 0.28) {
                            if (Ay <= -0.49) {
                              if (AyXGz <= -0.36) {
                                return 0;
                              } else {
                                return 1;
                              }
                            } else {
                              if (Gx_squared <= 0.68) {
                                if (GyXGz <= 0.08) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                return 1;
                              }
                            }
                          } else {
                            return 0;
                          }
                        }
                      }
                    } else {
                      return 1;
                    }
                  } else {
                    if (AzXGy <= -0.27) {
                      return 0;
                    } else {
                      if (AyXAz <= 0.52) {
                        return 2;
                      } else {
                        if (AyXGy <= 1.38) {
                          if (Gy <= -0.07) {
                            if (GyXGz <= 0.06) {
                              return 0;
                            } else {
                              if (AyXAz <= 0.79) {
                                return 0;
                              } else {
                                if (Az_squared <= 0.51) {
                                  return 1;
                                } else {
                                  return 0;
                                }
                              }
                            }
                          } else {
                            return 1;
                          }
                        } else {
                          return 1;
                        }
                      }
                    }
                  }
                } else {
                  if (Gx_squared <= -0.03) {
                    if (AxXAy <= -0.71) {
                      return 0;
                    } else {
                      if (AzXGy <= 0.13) {
                        return 0;
                      } else {
                        return 1;
                      }
                    }
                  } else {
                    if (Gz_squared <= 5.54) {
                      if (GyXGz <= 0.34) {
                        if (AzXGz <= 0.62) {
                          if (Gz_squared <= -0.03) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        if (AzXGz <= 0.88) {
                          return 0;
                        } else {
                          return 1;
                        }
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              }
            } else {
              if (AyXAz <= 0.2) {
                return 2;
              } else {
                return 0;
              }
            }
          } else {
            if (Az <= -0.59) {
              if (Ay <= 0.51) {
                return 0;
              } else {
                if (AyXGy <= -1.99) {
                  return 0;
                } else {
                  if (AyXGx <= -0.25) {
                    if (Gy <= 3.19) {
                      if (AyXGy <= -0.03) {
                        if (GxXGz <= -0.11) {
                          if (GxXGz <= -0.28) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (AxXGx <= -0.1) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AzXGx <= 1.22) {
                          if (Ay <= 1.36) {
                            return 0;
                          } else {
                            if (Ax <= -0.1) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (AxXAy <= 0.69) {
                      if (AxXGy <= 0.05) {
                        if (Az_squared <= 0.12) {
                          if (AyXAz <= -0.94) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (Az_squared <= 1.12) {
                            if (AyXGz <= 0.55) {
                              if (Gx_squared <= -0.08) {
                                return 0;
                              } else {
                                if (Gx <= 0.78) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              }
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        if (AxXGy <= 0.9) {
                          if (Gz_squared <= 0.24) {
                            if (AxXGy <= 0.15) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AyXGy <= -0.01) {
                        return 0;
                      } else {
                        if (AzXGy <= -0.19) {
                          return 0;
                        } else {
                          return 1;
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (AzXGy <= -0.3) {
                if (AyXAz <= -0.37) {
                  if (Gx_squared <= 0.11) {
                    if (GxXGz <= 0.27) {
                      if (AzXGy <= -0.36) {
                        if (Gy <= 3.04) {
                          if (GyXGz <= -0.36) {
                            if (AyXGy <= 1.26) {
                              return 0;
                            } else {
                              return 0;
                            }
                          } else {
                            if (AxXGx <= -0.01) {
                              return 0;
                            } else {
                              if (AyXGx <= 0.33) {
                                return 0;
                              } else {
                                return 0;
                              }
                            }
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  } else {
                    if (Ay <= 1.47) {
                      if (GxXGz <= 0.54) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      if (Gy <= 1.26) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (AxXAy <= 0.21) {
                    return 1;
                  } else {
                    return 0;
                  }
                }
              } else {
                if (Ay <= 1.39) {
                  if (Gx_squared <= 0.65) {
                    if (Gz_squared <= -0.05) {
                      if (Ax_squared <= -0.15) {
                        return 0;
                      } else {
                        if (AyXAz <= -0.28) {
                          return 0;
                        } else {
                          return 0;
                        }
                      }
                    } else {
                      if (AxXGy <= -0.2) {
                        return 0;
                      } else {
                        if (Gx <= -0.62) {
                          if (AxXGx <= -0.18) {
                            return 0;
                          } else {
                            if (AzXGz <= -0.4) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (AxXAy <= 0.16) {
                            return 0;
                          } else {
                            if (AyXGx <= 0.59) {
                              if (Gy <= 0.01) {
                                return 0;
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (GyXGz <= 0.31) {
                      return 0;
                    } else {
                      return 1;
                    }
                  }
                } else {
                  if (GxXGz <= -0.5) {
                    if (Gy <= 0.9) {
                      return 0;
                    } else {
                      if (GxXGz <= -0.62) {
                        return 1;
                      } else {
                        if (AzXGz <= 0.2) {
                          return 1;
                        } else {
                          return 1;
                        }
                      }
                    }
                  } else {
                    if (Gy <= 0.93) {
                      if (Gz <= -1.92) {
                        if (AzXGz <= 0.66) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        if (Ax_squared <= -0.16) {
                          if (Gx_squared <= 0.01) {
                            if (AzXGz <= -0.24) {
                              return 0;
                            } else {
                              if (Az_squared <= -0.14) {
                                if (GxXGy <= 0.05) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              } else {
                                if (AzXGx <= -0.1) {
                                  return 1;
                                } else {
                                  return 2;
                                }
                              }
                            }
                          } else {
                            if (AzXGy <= 0.1) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          if (Gy <= -0.15) {
                            if (Gx <= 0.51) {
                              if (GyXGz <= 0.1) {
                                if (AzXGz <= -0.33) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            } else {
                              if (Gx_squared <= 0.09) {
                                if (Ax_squared <= -0.09) {
                                  return 0;
                                } else {
                                  return 0;
                                }
                              } else {
                                return 0;
                              }
                            }
                          } else {
                            if (AzXGx <= 0.22) {
                              if (GyXGz <= -0.1) {
                                if (Gx <= 0.89) {
                                  return 2;
                                } else {
                                  return 0;
                                }
                              } else {
                                if (AxXGx <= 0.02) {
                                  return 1;
                                } else {
                                  return 1;
                                }
                              }
                            } else {
                              return 0;
                            }
                          }
                        }
                      }
                    } else {
                      if (AyXGx <= 0.7) {
                        if (GxXGy <= 0.12) {
                          return 0;
                        } else {
                          if (AzXGx <= -0.04) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (AyXAz <= -0.72) {
            if (Gx <= -1.61) {
              if (AxXGy <= 2.6) {
                if (AzXGy <= -1.83) {
                  return 0;
                } else {
                  if (AxXGy <= 0.12) {
                    if (GyXGz <= -0.71) {
                      return 1;
                    } else {
                      if (GxXGz <= 2.52) {
                        if (Ax_squared <= 0.18) {
                          if (AxXGx <= -0.54) {
                            return 0;
                          } else {
                            if (Gx_squared <= 0.65) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        return 0;
                      }
                    }
                  } else {
                    if (Gz <= -2.29) {
                      return 0;
                    } else {
                      if (AyXGy <= -1.49) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                return 1;
              }
            } else {
              if (AzXGz <= 0.21) {
                if (AxXGy <= 0.06) {
                  if (Gx_squared <= -0.08) {
                    return 0;
                  } else {
                    if (AyXAz <= -0.97) {
                      if (Gx <= 4.05) {
                        if (Ay_squared <= 0.57) {
                          if (Gy_squared <= -0.14) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          return 0;
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (AxXGx <= -0.08) {
                        return 0;
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (Gx_squared <= -0.07) {
                    return 0;
                  } else {
                    if (AyXAz <= -0.87) {
                      if (AyXAz <= -2.06) {
                        return 0;
                      } else {
                        return 0;
                      }
                    } else {
                      return 0;
                    }
                  }
                }
              } else {
                if (Gy <= -1.12) {
                  if (GyXGz <= 0.77) {
                    if (AzXGy <= 0.6) {
                      return 0;
                    } else {
                      return 0;
                    }
                  } else {
                    return 0;
                  }
                } else {
                  if (Gz <= -1.69) {
                    if (AxXGx <= -0.45) {
                      return 0;
                    } else {
                      if (GxXGz <= -0.64) {
                        if (Gz <= -3.08) {
                          return 0;
                        } else {
                          return 0;
                        }
                      } else {
                        if (Gy_squared <= -0.04) {
                          if (AxXGy <= -0.02) {
                            return 0;
                          } else {
                            return 0;
                          }
                        } else {
                          if (Ax_squared <= 0.0) {
                            return 0;
                          } else {
                            return 0;
                          }
                        }
                      }
                    }
                  } else {
                    if (GxXGy <= 0.06) {
                      if (GxXGy <= 0.03) {
                        if (AxXGx <= -0.19) {
                          return 0;
                        } else {
                          if (Gz <= -1.27) {
                            return 0;
                          } else {
                            if (Ay <= 1.68) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    } else {
                      if (AyXGx <= 1.69) {
                        if (Gx <= -0.76) {
                          return 0;
                        } else {
                          if (AxXGy <= -0.0) {
                            return 0;
                          } else {
                            if (AzXGz <= 0.36) {
                              return 0;
                            } else {
                              return 0;
                            }
                          }
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (Gz <= -0.79) {
              if (GyXGz <= 0.18) {
                if (AyXGz <= -1.04) {
                  if (Ax_squared <= 0.38) {
                    return 0;
                  } else {
                    return 0;
                  }
                } else {
                  if (AxXGz <= -0.56) {
                    return 1;
                  } else {
                    if (Gx <= 0.93) {
                      return 0;
                    } else {
                      if (Ay_squared <= 0.42) {
                        return 1;
                      } else {
                        return 0;
                      }
                    }
                  }
                }
              } else {
                if (GyXGz <= 0.47) {
                  return 1;
                } else {
                  return 0;
                }
              }
            } else {
              if (AxXAz <= 0.18) {
                if (AxXGy <= 0.09) {
                  if (Gx_squared <= -0.09) {
                    return 1;
                  } else {
                    if (Gx_squared <= -0.07) {
                      return 0;
                    } else {
                      if (GxXGy <= 0.76) {
                        if (GxXGy <= 0.44) {
                          if (Gx_squared <= -0.03) {
                            return 1;
                          } else {
                            if (Ay <= 1.68) {
                              return 0;
                            } else {
                              return 1;
                            }
                          }
                        } else {
                          return 1;
                        }
                      } else {
                        return 0;
                      }
                    }
                  }
                } else {
                  if (Gz_squared <= -0.06) {
                    return 0;
                  } else {
                    return 0;
                  }
                }
              } else {
                return 0;
              }
            }
          }
        }
      }
    }
  }
}
