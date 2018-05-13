#ifndef LIST_H_
#define LIST_H_
struct Date {
    int mm, dd, yy;
};
typedef struct {
    int id;
    char stname[20];
    char name[20];
    char author[20];
    int quantity;
    float price;
    int count;
    int rackno;
    struct Date issued;
    struct Date duedate;
} Book;

#endif
