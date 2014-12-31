/*
 * Inode based directory notification for Linux
 *
 * Copyright (C) 2005 John McCutchan
 */
#ifndef _LINUX_INOTIFY_H
#define _LINUX_INOTIFY_H

#include <linux/sysctl.h>
#include <uapi/linux/inotify.h>
#include <linux/list.h>
#include <linux/fs.h>

extern struct ctl_table inotify_table[]; /* for sysctl */

#define ALL_INOTIFY_BITS (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | \
			  IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | \
			  IN_MOVED_TO | IN_CREATE | IN_DELETE | \
			  IN_DELETE_SELF | IN_MOVE_SELF | IN_UNMOUNT | \
			  IN_Q_OVERFLOW | IN_IGNORED | IN_ONLYDIR | \
			  IN_DONT_FOLLOW | IN_EXCL_UNLINK | IN_MASK_ADD | \
			  IN_ISDIR | IN_ONESHOT)

typedef int (*inotify_path_proc)(struct path *dst, struct path *src);

struct inotify_stackfs {
	struct list_head	list;		/* entry in inotify_fs_list */
	struct file_system_type	*fs_type;	/* registed file_system_type */	
	inotify_path_proc	func;		/* registed callback function */
};

#ifdef CONFIG_INOTIFY_STACKFS

extern int inotify_register_stackfs(struct inotify_stackfs *fs);
extern void inotify_unregister_stackfs(struct inotify_stackfs *fs);

#else

static inline int inotify_register_stackfs(struct inotify_stackfs *fs)
{
	return 0;
}

static inline void inotify_unregister_stackfs(struct inotify_stackfs *fs)
{
}

#endif	/* CONFIG_INOTIFY_STACKFS */

#endif	/* _LINUX_INOTIFY_H */
