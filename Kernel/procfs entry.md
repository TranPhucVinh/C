# API

### proc_create()

```c
struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct proc_ops *proc_ops);
```

``umode_t``: Mode in octal base, required to be 4 number, like ``0777``

# Example

### Feature

Create a procfs folder and a file inside it (``/proc/new_proc_dir/new_proc_file``) with those 2 features:

* Send data to that procfs file
* Read responsed data from that procfs file

Send data to that procfs file: ``echo 7 > /proc/new_proc_dir/new_proc_file``
 
Read responsed data from that procfs file: ``cat /proc/new_proc_dir/new_proc_file``

### Source code

```c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#define PROC_DIR 	"new_proc_dir"
#define PROC_FILE	"new_proc_file"

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_folder;
struct proc_dir_entry *proc_file;

/**
 * @brief Response a string when user read PROC_FILE
 */
ssize_t procfs_read(struct file *File, char *buf, size_t count, loff_t *offs) {
	char responsed_string[] = "Response to user space when user read PROC_FILE\n";
	int bytes_response = copy_to_user(buf, responsed_string, sizeof(responsed_string));
	if (!bytes_response) printk("Responsed string to userpsace has been sent\n");
	else printk("%d bytes could not be send\n", bytes_response);
	return sizeof(responsed_string);
}

char data[100];
/**
 * @brief Handle write operation when user write to PROC_FILE
 */
ssize_t procfs_write(struct file *File, const char *buf, size_t len, loff_t *offs) {
	memset(data, 0, sizeof(data));
	copy_from_user(data, buf, len);
	printk("String read from userspace: %s\n", data);
	return sizeof(data);
}

 struct proc_ops fops = {
	.proc_read = procfs_read,
	.proc_write = procfs_write,
};

/**
 * @brief Create procfs folder PROC_DIR and procfs file PROC_FILE inside that folder
 * 		  It will then be /proc/new_proc_dir/new_proc_file
 */
int procfs_init(void) {
	proc_folder = proc_mkdir(PROC_DIR, NULL);
	if(proc_folder == NULL) {
		printk("Can't create /proc/%s\n", PROC_DIR);
		return -ENOMEM;
	}

	proc_file = proc_create(PROC_FILE, 0777, proc_folder, &fops);
	if(proc_file == NULL) {
		printk("Error creating /proc/%s/%s\n", PROC_DIR, PROC_FILE);
		proc_remove(proc_folder);
		return -ENOMEM;
	}

	printk("/proc/%s/%s is created successfully\n", PROC_DIR, PROC_FILE);
	return 0;
}

void procfs_exit(void) {
	printk("Removing /proc/%s/%s\n", PROC_DIR, PROC_FILE);
	proc_remove(proc_file);
	proc_remove(proc_folder);
}

module_init(procfs_init);
module_exit(procfs_exit);
```
