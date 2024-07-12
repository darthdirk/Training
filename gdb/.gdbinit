set auto-load safe-path /

# Set logging of GDB session
set logging on
set logging file gdb.logging
set logging overwrite on

# Define a custom command to print the contents of a register
define pr
    # Argument $1 is the register name
    print $arg0
end

# Document a command 
# document <command>
#     <code>
# end

# This information appears when the help feature is used
# (gdb) help <command>
# end

# When a user defined command is called, arguments can be passed in
# (gdb) <command> <arg0> <arg1> <arg2> ...

# The number of arguments, and the arguments themselfs can be
# referenced inside the command definition useing the following variables:
# $argc
# $arg0
# $arg1
# $arg2

# Source an additional configuration file
source ~/extra_gdbinit

# Break at main function
break main

# Start program execution
run

