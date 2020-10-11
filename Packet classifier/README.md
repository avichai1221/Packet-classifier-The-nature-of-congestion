Explain how to run:

# prefix_table

First we will make sure that the input file we want to run is in the correct format (the program will not work properly once the command format is not correct) then we will enter the name of the input file in main as input to the function "read".
Finally you can execute "make prefix_table" command and the program will compile and create a run file named "prefix_table" and than you need to execute the "./prefix_table" command The executable file will be executed and all the commands in the input file will be executed and we will see the program output.



# prefix_table_opt

First we will make sure that the input file we want to run is in the correct format (the program will not work properly once the command format is not correct) then we will enter the name of the input file in main as input to the function "read".
Finally you can execute "make prefix_table_opt" command and the program will compile and create a run file named "prefix_table_opt" and than you need to execute the "./prefix_table_opt" command The executable file will be executed and all the commands in the input file will be executed and we will see the program output.



***Using the "make" or "make all" command you can compile and generate the executable files simultaneously for the above two files.

*** Using the "make clean" command you can automatically delete all executable files and .o files that Created.

***Attaches a file named "sample_input" with a sample run commands and also output files for prefix_table_opt and for prefix_table.

***The depth of the tree is calculated as the number of vertices from the root to the farthest leaf not including the root itself. (In the FIND function the depth of the vertex we found is calculated).

***The program supports only 3 actions and assumes that no additional actions will be entered.
ADD- This function adds a prefix to the tree.
REMOVE- This function deletes a given prefix.
FIND- This function searches for a given prefix.



Examples of proper format for the operation-ADD
ADD 110.255.255.255/5 A
The output will be-
Added 110.255.255.255/5 A at the depth 5,total nodes 6
You cannot insert a different format.

Examples of proper format for the operation-FIND
FIND 110.255.255.255
The output will be-
Found 110.255.255.255 A at the depth 5
You cannot insert a different format.

Examples of proper format for the operation-REMOVE
REMOVE 101.255.255.255/5 A
The output will be-
Removed 101.255.255.255/5 A at the depth 0,total nodes 1
You cannot insert a different format.


In addition, please note that it is not possible to delete or search the tree for the prefix that we did not add before.
if we delete a prefix that does not exist, the normal format will be printed (without changing the number of vertices and the depth of the tree because nothing has been deleted).



