#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>          

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sviprocesi - ispis svih procesa (Labos 3)");
MODULE_AUTHOR("Bruno Miklin");

int start(void)
{
    struct task_struct *pntrProc;

    printk(KERN_INFO "Ucitavanje modula svih procesa...\n");
    printk(KERN_INFO "Ispis svih procesa:\n");

    for_each_process(pntrProc) {
        printk(KERN_INFO "Proces: %-15s  PID: %-6d  Roditelj: %-15s  ParentPID: %-6d\n",
               pntrProc->comm,
               pntrProc->pid,
               pntrProc->parent->comm,
               pntrProc->parent->pid);
    }

    return 0;
}

void end(void)
{
    printk(KERN_INFO "Uklanjanje modula sviprocesi...\n");
}

module_init(start);
module_exit(end);
