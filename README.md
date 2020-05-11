# Assignment-1

Upon process running, create 2 thread, thread function as describe below:

Thread 1:
Accept user command from command prompt
Print out message based on user command prompt
Command supported:

‘q’ : Quit current program (whole program)

‘c’ : create a string buffer

‘s’ : insert user key in string into buffer (created by ‘c’)

‘g’ : print string buffer (user key in-in string using command ‘s’)

‘t’ : change thread 2 updating time

‘f’ : flag HIGH

'z' : flag LOW

Thread 2:

Perform the following function periodically (time control by ‘s’). Default to every seconds
Increase the first character of string buffer : e.g. a → b, or A→ B
