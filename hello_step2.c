#include "hello.h"

static int n = 0;
static char *str = NULL;

static int __init my_init(void)
{
  int k = n;
  while(k) {
    printk("Hello %s\n", str);
    k--;
  }
  return 0;
}

static void __exit my_exit(void)
{
  while (n) {
    printk("Goodbye %s\n", str);
    n--;
  }
}

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("You");
module_init(my_init);
module_exit(my_exit);
module_param(n, int, S_IRUSR);
module_param(str, charp, S_IRUSR);
