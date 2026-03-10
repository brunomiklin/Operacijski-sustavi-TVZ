#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jednostavan modul za OS - Labos 3");
MODULE_AUTHOR("Bruno Miklin");


int start(void){
        printk(KERN_INFO "Ucitavanje jezgrenog modula\n");
        printk(KERN_INFO "Jiffies: %lu\n", jiffies);
        printk(KERN_INFO "Proteklo vrijeme u trenutku inicjalizacije: %lu\n",jiffies/HZ); 
        return 0;  
}

void end(void){
    printk(KERN_INFO "Uklanjanje jezgrenog modula\n");
    printk(KERN_INFO "Jiffies: %lu\n", jiffies);
    printk(KERN_INFO "Proteklo vrijeme u trenutku uklanjanja modula iz jezgre: %lu\n",jiffies/HZ);   
    
}

module_init(start);
module_exit(end);