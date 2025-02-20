1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  fork lets us start a child process, so we do not have to stop running the shell to use external commands

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  if the fork fails

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  The $PATH variable is where execvp finds commands to execute. execvp searches the $PATH variable to find a match with the command input, and if it does it loaded into memory with the arguments we passed - in this case it's loaded into the fork of the shell

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  We need the child to be terminated after the parent so the child's exit code is not lost and so the child can be terminated.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  this is how we get the exit statuses of child processes so we can know if the child process was successfully completed or if it failed.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  I split the cmd string using quotes first, and then split arguments without quotes using spaces. I know the arguments without quotes because strtok will return the quoted arguments as an odd index(when indexed from 0). We need to do this since quotes in bash are protective, so we can have arguments with spaces.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  My original method was hard to follow.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  Signals are messages sent to running processes to notify them about an event or trigger a behavior.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGINT is a signal used to interrupt an running process. It is the signal sent by Ctrl+C in most shells. If the process has a signal handler for SIGINT that doesnt interrupt the process, then the signal will not interrupt the process immediately.

    SIGTERM is a signal used to terminate a process. It involves cleaning up memory after. If the process has a signal handler for SIGTERM that doesnt kill the process, then the signal will not terminate the process

    SIGKILL is used to kill a process. It terminates the process immediately with no cleanup and cannot be ignored by a process like SIGTERM.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  SIGSTOP is a signal that stops a process and cannot be handled or ignored like SIGINT. SIGSTOP also does not handle memory cleanup
