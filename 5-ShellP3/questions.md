1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation uses waitpid() to wait for child processes to end before accepting input. If i did not do this, the new process would make the parent lose its childs pid, making it unable to terminate

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

If we don't close the unused pipe ends in the  both parent and child processes may hang indefinitely.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

This is because when changing the working directory, we want this to affect the main supervisor process and not a child subprocess. If cd were an external command,  it would run in a child process, and any directory changes it made would not affect the parent shell.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would store commamds in a dynamically resized array using realloc(), while pipes are allocated with malloc(), creating 2 * (num_commands - 1) file descriptors. Each child process, created via fork(), sets up dup2() to redirect input/output appropriately, then closes all unused pipes to prevent descriptor leaks. The parent closes pipes after spawning children and waits for all processes to finish. Finally, allocated memory is freed to avoid leaks. This approach increases flexibility but introduces trade-offs like higher memory usage, potential performance overhead from dynamic allocation, and complexity in managing system file descriptor limits.