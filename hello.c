#include "hello.h"

static int is_open = 0;
static char *output = NULL;

static int my_dev_open(struct inode *inode, struct file *file)
{
  if (is_open == 0) {
    printk("Device is open.\n");
    is_open = 1;
  } else
    printk("Device already opened\n");
  return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
  printk("Device is closed\n");
  is_open = 0;
  return 0;
}

static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off)
{
  return len;
}

static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
  int i = 0;
  output = kmalloc(sizeof(char) * (len + 1), GFP_KERNEL);
  for (i = 0; i < len && buf[i]; i++) {
    output[i] = buf[i];
  }
  printk("Output is [%s]\n", output);
  //kfree(output);
  return len;
}

static struct file_operations fops = {
  .read = my_dev_read,
  .write = my_dev_write,
  .open = my_dev_open,
  .release = my_dev_close
};

static int __init my_init(void)
{
  int kd = register_chrdev(0, "etib", &fops);
  printk("kernel driver: %d\n", kd);
  return 0;
}

static void __exit my_exit(void)
{
  printk("Goodbye !\n");
}

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("julithein");
module_init(my_init);
module_exit(my_exit);
