#include "mellos/kernel/streams.h"
#include "kernel_stdio.h"
#include "autoconf.h"
#include "dynamic_mem.h"

#include "errno.h"
#include "stddef.h"
#ifdef CONFIG_GFX_VESA
#else
#include "vga_text.h"
#endif
#include "colours.h"
#include "assert.h"


extern file_t* kstdin;
extern file_t* kstdout;
extern file_t* kstderr;

//todo: the keyboard input driver that the shell polls should be passed to this
ssize_t stdin_read(file_t* f, void* buf, size_t size, uint64_t offset) {
	return kstdin->ops->read(kstdin, buf, size, offset);
}

ssize_t stdout_write(file_t* f, const void* buf, size_t size, uint64_t offset) {
	if (!buf || size <= 0) return 0;
	if (f != kstdout) {
		return -EINVAL;
	}

	char *buffer = kmalloc(size + 1);
	for (int i = 0; i < size; i++) {
		buffer[i] = ((char*)buf)[i];
	}
	buffer[size] = 0;

	kprint_col(buffer, DEFAULT_COLOUR);
	return size;
}

ssize_t stderr_write(file_t* f, const void* buf, size_t size, uint64_t offset) {
	if (!buf || size <= 0) return 0;
	if (f != kstderr) {
		return -EINVAL;
	}

	char *buffer = kmalloc(size + 1);
	for (int i = 0; i < size; i++) {
		buffer[i] = ((char*)buf)[i];
	}
	buffer[size] = 0;

	kprint_col(buffer, ERROR_COLOUR);
	return size;
}

size_t file_read(file_t* stream, char* buf, size_t size) {
	return stream->ops->read(stream, buf, size, 0);
}

size_t file_write(file_t* stream, const char* buf, size_t size) {
	return stream->ops->write(stream, buf, size, 0);
}

file_ops_t stdout_fops = {
	.read = NULL,
	.write = stdout_write,
};

file_ops_t stderr_fops = {
	.read = NULL,
	.write = stderr_write,
};

file_ops_t stdin_fops = {
	.read = stdin_read,
	.write = NULL,
};

stream_ops_t kernel_stdout_streamops = {
	.write = kstream_write,
};

stream_ops_t kernel_stderr_streamops = {
	.write = kstream_write,
};

stream_ops_t kernel_stdin_streamops = {
	.read = kstream_read,
};



void init_stdio_files() {
	kstdin = kmalloc(sizeof(file_t));
	kstdout = kmalloc(sizeof(file_t));
	kstderr = kmalloc(sizeof(file_t));
	assert_msg(kstdin, "kstdin is null");
	assert_msg(kstderr, "kstderr is null");
	assert_msg(kstdout, "kstdout is null");
}
