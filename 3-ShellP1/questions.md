1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  `fgets()` can also read files

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  the size of the input from the user is not known in advance. A fixed-size array would limit the input length, potentially leading to buffer overflows or wasted memory. malloc() allows the program to allocate memory as needed, ensuring flexibility and memory efficiency. This is especially important in interactive applications like a shell, where the user could input an arbitrary number of characters.


3. In `dshlib.c`, the function `build_cmd_list()` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  because by trimming leading and trailing whitespaces we can ensure that we do not accidentally read extra whitespace as extra commands, since we use the whitespace to divide commands and arguments

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  Redirection in Linux allows controlling where input and output go, and in our custom shell, we should implement output redirection (`>`) to write command output to a file (overwriting it), append output redirection (`>>`) to append command output to a file, and input redirection (`<`) to take input from a file. 
    
    Challenges in implementing these include managing file permissions, ensuring files are opened correctly (for writing or appending), handling errors if files don’t exist or are inaccessible, and managing edge cases like empty files or invalid syntax. Additionally, proper file handling, error checking, and managing input/output buffering are key to implementing robust redirection.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**: Redirection involves changing the destination of input or output. For example, command > file.txt redirects the output of command to a file. Similarly, input redirection like command < file.txt directs the input of command from a file. Redirection changes where data goes, whether to or from files, instead of the default STDOUT and STDIN streams.

    > Pipes, on the other hand, allow the output of one command to be passed as input to another command. For example, command1 | command2 sends the output of command1 directly to command2. This allows multiple commands to be chained together without the need to store intermediate results in files.



- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  Separating STDERR from STDOUT is crucial because it allows the user or program to distinguish between normal output and error messages. If both streams are combined, it becomes difficult to parse the output correctly and handle errors effectively. Keeping them separate makes it easier to debug, log errors, or redirect them to different destinations (e.g., logging errors to a file while displaying normal output on the terminal).

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  Our custom shell should handle errors by keeping STDERR separate from STDOUT unless explicitly merged by the user. Merging the two streams can be useful for certain debugging scenarios, but by default, we should allow the user to handle both streams independently. If merging is needed, we can use redirection like command > output.txt 2>&1, which merges both streams into one. Alternatively, we can implement flags in the shell to enable or disable merging for specific commands or globally.