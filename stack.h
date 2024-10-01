#ifndef stack_stack_h
#define stack_stack_h

// C Program to demonstrate how to Implement a Stack

// Define the maximim capacity of the stack
#define MAX_SIZE 100

// Define a structure for the stack
typedef struct {
    // Array to store stack elements
    int arr[MAX_SIZE];  
    // Index of the top element in the stack
    int top;        
} Stack;

// Function to initialize the stack
void initialize(Stack *stack) {
    // Set top index to -1 to indicate an empty stack
    stack->top = -1;  
}

// Function to check if the stack is empty
char isEmpty(Stack *stack) {
    // If top is -1, the stack is empty
    if (stack->top == -1){
        return 1;
    }
    return 0;  
}

// Function to check if the stack is full
char isFull(Stack *stack) {
    // If top is MAX_SIZE - 1, the stack is full
    if (stack->top == MAX_SIZE - 1){
        return 1;
    }
    return 0;  
}

// Function to push an element onto the stack
void push(Stack *stack, int value) {
    // Check for stack overflow
    if (isFull(stack)) {
        return;
    }
    // Increment top and add the value to the top of the stack
    stack->arr[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack *stack) {
    // Check for stack underflow
    if (isEmpty(stack)) {
        return -1;
    }
    // Return the top element 
    int popped = stack->arr[stack->top];
    // decrement top pointer
    stack->top--;
    // return the popped element
    return popped;
}

// Function to peek the top element of the stack
int peek(Stack *stack) {
    // Check if the stack is empty
    if (isEmpty(stack)) {
        return -1;
    }
    // Return the top element without removing it
    return stack->arr[stack->top];
}


#endif // CBMP_CBMP_H
