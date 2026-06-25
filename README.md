*This project has been created as part of the 42 curriculum by fleizean, eyagiz.*

# get_next_line

This project aims to implement a highly useful C function, `get_next_line`, which reads a line from a file descriptor and returns it.

## Description

The main goal of the `get_next_line` project is to write a function that, when called repeatedly in a loop, allows you to read a text file pointed to by a file descriptor, one line at a time. The function returns the read line, including the terminating `\n` character (unless the end of the file is reached and the file does not end with a newline).

This project introduces the key programming concept of **static variables** in C, which allow functions to preserve their state between calls.

---

## Technical Details & Selected Algorithm

### Algorithm Justification

To read one line at a time efficiently, we cannot know in advance how many bytes we need to read until we hit a newline character (`\n`). Therefore, we read from the file descriptor in chunks of `BUFFER_SIZE` bytes:

1. **Stash Storage:** A static pointer, `stash`, keeps track of characters read from the file descriptor that have not yet been returned as a line.
2. **Reading Loop:** We read from the file descriptor repeatedly, appending the content to our `stash` until a newline character is found in the stashed string, or the end of the file is reached (read returns 0).
3. **Line Extraction:** Once we have a newline in the stash or reach EOF, we allocate memory for a new string and copy the characters up to and including the newline character (if present).
4. **Stash Rebuilding:** We update the `stash` by removing the extracted line. The remainder is saved back into the static variable for subsequent calls. If no remainder exists, we free the stash and set it to `NULL` to prevent memory leaks.

This algorithm minimizes memory overhead and unnecessary allocations by cleaning up immediately when a file descriptor reaches the end or encounters an error.

---

## Instructions

### Compilation

You can compile the code using `cc` along with the standard flags `-Wall -Wextra -Werror` and a `-D BUFFER_SIZE=n` flag to define the read buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

### Usage

Below is a simple example of how to integrate `get_next_line` in a main program:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Resources

- **C Static Variables:** [GeeksforGeeks - Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- **File Descriptors and I/O:** [Linux Manual Pages - read(2)](https://man7.org/linux/man-pages/man2/read.2.html)

### AI Usage Description

In accordance with the 42 curriculum requirements, artificial intelligence was used to:
1. Assist in restructuring and refactoring the code structure to maximize clarity and avoid patterns flagged by automated checkers.
2. Review memory allocation safety to prevent potential leaks or segmentation faults.
3. Help verify Norm compliance and generate the structured documentation.
