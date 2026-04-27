#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/slab.h>

struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

int birthday_init(void){
    struct birthday *person;
    struct birthday *ptr, *next;
    int n=5;
    int i=0;
    int days[]={1,2,3,4,5};
    int months[]={6,7,8,9,10};
    int years[]={2000,2001,2002,2003,2004};
    printk(KERN_INFO "Birthday_Init: 2024128055 전성환\n");
    for(i=0;i<n;i++){
        person = kmalloc(sizeof(*person),GFP_KERNEL);
        if(person == NULL){
            printk(KERN_ERR "malloc fail");
            list_for_each_entry_safe(ptr,next,&birthday_list,list){
                list_del(&ptr->list);
                kfree(ptr);
            }
            return 1;
        }
        person -> day = days[i];
        person -> month = months[i];
        person -> year = years[i];
        INIT_LIST_HEAD(&person -> list);
        list_add_tail(&person -> list, &birthday_list);
    }
    list_for_each_entry(ptr,&birthday_list,list){
        printk(KERN_INFO "Birthday: %d/%d/%d\n",ptr->year,ptr->month,ptr->day);
    }
    return 0;
}

void birthday_exit(void){
    struct birthday *ptr, *next;
    printk(KERN_INFO "Rm Birthday Modules: 2024128055 전성환\n");
    list_for_each_entry_safe(ptr, next, &birthday_list,list){
        printk(KERN_INFO "RM Birthday: %d/%d/%d\n",ptr->year,ptr->month,ptr->day);
        list_del(&ptr->list);
        kfree(ptr);  
   }
    if(list_empty(&birthday_list)) printk(KERN_INFO "RM Birthday Complete\n");
    else printk(KERN_ERR "RM Failed\n");
}

module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("SHJ");
