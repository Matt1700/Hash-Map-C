#include <stdio.h>
#include <stdlib.h>

struct node
{
    int hash;
    void * value;
    struct node * next;
};

struct table
{
    int size;
    struct node ** list;
};


void insert(struct table * table, char * name, void * value);
struct table * generate_table(int size);
int generate_hash_code(char * name);
void delete_table(struct table * table);


struct table * generate_table(int size)
{
    
    struct table * table = (struct table *) malloc(sizeof(struct table));

    table->size = size;
    table->list = (struct node **) malloc(sizeof(struct node *)* size);

    for(int i = 0; i < size; i++)
    {
        table->list[i] = NULL;
    }

    return table;

}


int generate_hash_code(char * name)
{
    char current = *name;
    int value = 0, index = 0;
    
    while(current != '\0')
    {
        index++;
        value += ((int) current)*index; 
        current = *(name++);
    }

    return value;
}


void insert(struct table * table, char * name, void * value)
{

    int hash = generate_hash_code(name);
    int position = hash % (table->size);

    struct node * list = table->list[position];
    
    struct node * new = (struct node *) malloc(sizeof(struct node));

    struct node * temp = list;

    //Check if node already exists in the list
    while(temp != NULL)
    {
        if(temp->hash==hash)
        {
            temp->value = value;
            return;
        }

        temp = temp->next;

    }

    new->hash = hash;
    new->value = value;
    new->next = list; //add node to the head of the list
    
    table->list[position] = new; //replace old list with new list

}


void * lookup(struct table * table, char * name)
{
    
    int hash = generate_hash_code(name);
    int position = hash % (table->size);

    struct node * list = table->list[position];
    struct node * current = list;

    while(current != NULL)
    {
        if(current->hash == hash) return current->value;
        
        current = current->next;

    }

    return (int *) -1;
}


void delete_table(struct table * table)
{

    for(int i = 0; i < table->size; i++) //for each list in table
    {
        struct node * list = table->list[i];

        struct node * last = NULL;
        struct node * current = list;

        while(current != NULL)
        {
            last = current;
            current = current->next;
            free(last);
        }

    }
}

//Tests
int main()
{

    struct table * table = generate_table(10);

    insert(table, (char *) "CAT",  (int *) 10);
    insert(table, (char *) "DOG",  (int *) 20);
    insert(table, (char *) "FISH", (int *) 30);

    char * str = "DOG";

    printf("%s = %d \n", str, (int *) lookup(table, str));

    delete_table(table);

}
