# Design Doc

## Append text
I am going to this recursivley. 
### If the head is NULL
I am going to create a new node and make text equal the copy of text inputed into the function. The pointer pointing to the next node is NULL because this is the only node in the linked list. I am going to return the node because this node is now the head. 
### If the next node is NULL
I am going to create a new node and copy the text into the struct. I am going to make the pointer to the next node null since this node will be the last in the linked list. I am then going to make the current node point to the new node and return the current node. 
### Return
I am going make a recursive call to the next node and return the current node because that is the head.
 
## Insert text
I am going make this function recursive. 
### If the position bigger than the list or the size of the list
I am just going to append the text at the end of the list if the position is larger than the list because to me that makes sense. 
### If the position is 0
I am going to create a new node. The new node will get the copy of the text. The new node will also point to the current node because the new node will be the new head. I will then return the new node. 
### If the position is 1
I will make a new node. The new node will get a copy of the text and it will have the next node to the current node's next. The current node's next will then point to the new node being inserted. The new node is being placed after the current node. I will then return the current node since that is the head. 
### Return
I will make a recursive call that will go to the next node, carry the text, and reduce the position by 1.
I will then return the head of the list. 

## Delete text
This function is recursive.
If the list is NULL I will return NULL. If there is only one node in the list then I will free the text, the pointer, and the node itself.
### If the position is 0
I will create a temp variable that will contain a pointer to the next node. I will free the text within the current node and then free the current node. I will then return the temp variable that contains the pointer to the new head.
### If the position is 1
I will create a temp variable that contains the pointer that the next node is pointing towards. I will then free the next node's text and the next node. The current node will then point to the node that the next node was pointing towards. I will then return the current node.
### Return
I will make a recursive call that goes to the next node and reduces the position by 1. I will the return the head of the linked list.

## Replace text
This function is recursive.
If the position is 0, I will free the current node's text. I will then copy the new string into the current node. I will then return the current node. 
After the conditional statement I will make a recursive call to the next node and reduce the position by 1. I will then return the head of the list.

## Duplicate text
This is a recursive function. If the list is null then the function is just going to return null. If the list is not null then the function will create a new node. The new node will copy the string in the current node. The new node's next pointer will be equal to a recursive call that will take in the node that is after the current node. The function will return the new node. 

## Length of Linked List
I am going to create a variable count. I am then going to iterate through the nodes until the node is null. Each iteration I am going to iterate count and make list equal the next node.
After the loop completes I am going to return the count.

## Push Duplicate
This function is guaranteed that the stack is not empty. There does not need to be a conditional that is check ofor that. This function will create a new node. The new node will use the duplicate text function to copy the linked list that is in the current top of the stack. The new node's next pointer will then point to the current top of the stack. The function will then return the new node because that is the new top of the stack. 

## Push Empty
This function is not guaranteed that the stack is empty. There will be an if statement that will check if the stack is null. If the stack is null then the function will create a new node that will have the lines equal to null and the next pointer equal to null. If the stack is not null, then the function will create a new node that will have the lines equal to null and the next pointer will point to the current top of the stack. Both cases will return the new node because that is the new top of the stack. 

## Pop Stack
If the stack is null then this function will return null. Otherwise, I will create a temporary pointer variable that will contain the current node's next pointer. I will then use a while loop that terminates when the current node's line pointer equals null. In the while loop the function will create another temp pointer that will contain the lines' next pointer. I will then free the string in the lines' node and then free the node itself. The current stack node's lines pointer will then equal the temp pointer I made at the beginning of the loop. The loop go on until the lines pointer is null. After the loop completes I will free the stack node itself. I will then return the temp pointer variable I made at the beginning of the function because that will contain the new top of the stack.  

## Changing the color of the editor (Extra Thing)
I added a function that allows the user to change the color of the interface. The function is called change_color. It takes in a color and changes the color that is printed to the terminal. It uses conditionals to compare strings and prints using the 8 ANSI colors. I edited editor.c with a new command called color that allows the user to enter the color they want from a selection. I added the function to parts of the code that I wanted to be colored.  
