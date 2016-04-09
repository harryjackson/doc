#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h> 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harry");
MODULE_DESCRIPTION("toy kernel module");
MODULE_VERSION("0.1"); 
#define  DEVICE_NAME "toy"
#define  CLASS_NAME  "toy"

static int    param_cpu_id;
module_param(param_cpu_id    , int, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(param_cpu_id, "CPU ID that operations run on");

//static void    bar(void *arg);
//static void    foo(void *cpu);
static int     toy_open(   struct inode *inodep, struct file *fp);
static ssize_t toy_read(   struct file *fp     , char *buffer, size_t len, loff_t * offset);
static ssize_t toy_write(  struct file *fp     , const char *buffer, size_t len, loff_t *);
static int     toy_release(struct inode *inodep, struct file *fp);

static struct file_operations toy_fops = {
  .owner = THIS_MODULE,
  .open = toy_open,
  .read = toy_read,
  .write = toy_write,
  .release = toy_release,
};

static struct miscdevice toy_device = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = "toy",
  .fops = &toy_fops
};

//static int CPU_IDS[64] = {0};
static int toy_open(struct inode *inodep, struct file *filep) {
  int this_cpu = get_cpu();
  printk(KERN_INFO "open: called on CPU:%d\n", this_cpu);
  if(this_cpu == param_cpu_id) {
    printk(KERN_INFO "open: is on requested CPU: %d\n", smp_processor_id());
  }
  else {
    printk(KERN_INFO "open: not on requested CPU:%d\n", smp_processor_id());
  }
  put_cpu();
  return 0;
}
static ssize_t toy_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
  int this_cpu = get_cpu();
  printk(KERN_INFO "read: called on CPU:%d\n", this_cpu);
  if(this_cpu == param_cpu_id) {
    printk(KERN_INFO "read: is on requested CPU: %d\n", smp_processor_id());
  }
  else {
    printk(KERN_INFO "read: not on requested CPU:%d\n", smp_processor_id());
  }
  put_cpu();
  return 0;
}
static ssize_t toy_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
  int this_cpu = get_cpu();
  printk(KERN_INFO "write called on CPU:%d\n", this_cpu);
  if(this_cpu == param_cpu_id) {
    printk(KERN_INFO "write: is on requested CPU: %d\n", smp_processor_id());
  }
  else {
    printk(KERN_INFO "write: not on requested CPU:%d\n", smp_processor_id());
  }
  put_cpu();
  return 0;
}
static int toy_release(struct inode *inodep, struct file *filep){
  int this_cpu = get_cpu();
  printk(KERN_INFO "release called on CPU:%d\n", this_cpu);
  if(this_cpu == param_cpu_id) {
    printk(KERN_INFO "release: is on requested CPU: %d\n", smp_processor_id());
  }
  else {
    printk(KERN_INFO "release: not on requested CPU:%d\n", smp_processor_id());
  }
  put_cpu();
  return 0;
}

static int __init toy_init(void) {
  int cpu_id;
  if(param_cpu_id < 0 || param_cpu_id > 4) {
    printk(KERN_INFO "toy: unable to load module without cpu parameter\n");
    return -1;
  }
  printk(KERN_INFO "toy: loading to device driver, param_cpu_id: %d\n", param_cpu_id);
  //preempt_disable(); // See notes below
  cpu_id = get_cpu();
  printk(KERN_INFO "toy init called and running on CPU: %d\n", cpu_id);
  misc_register(&toy_device);
  //preempt_enable(); // See notes below
  put_cpu();
  //smp_call_function_single(1,foo,(void *)(uintptr_t) 1,1);
  return 0;
}

static void __exit toy_exit(void) {
    misc_deregister(&toy_device);
    printk(KERN_INFO "toy exit called\n");
}

module_init(toy_init);
module_exit(toy_exit);
