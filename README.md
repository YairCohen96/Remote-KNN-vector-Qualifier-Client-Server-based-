# AP1-AS-YC3
ex4 in advanced programming course 

welcome to our machine learning K NEAREST NEIGHBORS - distance calculator !

the program is now supporting use by server and multiple clients:

instructions for running the program from terminal:

for a whole use by yourself you will need to open two programs - two terminals.
as always, after cloning the project and while in its folder - put "make" order on the terminal to compile both server and client.
first program to open - server
will be open by order "./server.out port_will_be_listening_on" - of course make sure you put a valid number - port number to open the program successfully. the server will be open and listening, waiting for clients.

second program to open - client
will be open by order "./client.out i.p_adress port_server_is_listening_on" - of course only space_key press betweeen each argument.

for any incorrect data - you will get an "invalid input" message and the program will be closed (incorrect i.p or port will issue a specific message accordingly).

once client is also open - an instructions menu will immediatelly open. follow the options to upload and classify data and eventually - watching/dowmloading results, and exit.
our server will treat multiple clients in parallel, so you can open more than one client program safly!

you can insert as many inputs as you like - our server will provide an answer!
after one client finish and exit, the server - will stay open for next incoming clients.

terms explanation:
distance - a type of distance between 2 vectors (one will be classifieid by the other typically)
K- run on the k nearest vectors from the file and return the type of the most return type (if the k you choose is bigger than amount of vectors in file - the program will return the comparison to all of the vectors in the file).
path to a obj_classified.csv file - path (relative or direct) to a file of classified vectors to train with.
path to a obj_Unclassified.csv file - path (relative or direct) to a file of classified vectors to test.


notice: for any ilegal input - the program will show you a message and return you to try again in the main menu.
 the contents of file to train/classify, also needs to be valid - inaccurate representation of numbers will not be able to be classified.
 for example = ".3" will not be accetped! we don't know if your intention is indeed 0.3 or some other idea



a few words about our implementation:
added in this last ex. - ability to run multiple clients in parallel using threads.
a smarter code design - using design patterns and abstract classes such as: commands, listener, CLI for more modular implementations.

the exercise is bulit upon previous exercises, in a object-oriented manner.
using DistanceCalc and KnnCalc object with their uniq abilities, and approaching them from client/server structure.

we execute several validation tests for any user's input before safely storing the data.
these validations are made to ensure a future legal calculation for each of the calculator 5 distance types, and according to given data files.
all validations are exctued by a object build to do so.

finally, we hold a .h file holding all of functions and libraries signatures.
our code could be easily modified for adding more distance options or change k and data file while running - as you will see using our server menu.

enjoy!

