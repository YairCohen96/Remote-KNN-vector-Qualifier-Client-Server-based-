# KNN-vector-Qualifier
Done with in an advanced programming course at Bar-Ilan University.
By - Ahiya Schneider and Yair Cohen.

Welcome to our machine learning K NEAREST NEIGHBORS - Qualifier!

The program is now supporting use by server and multiple clients (TCP Protocol):

Instructions for running the program from terminal:

For a whole use by yourself you will need to open two programs - two terminals.
After cloning the project and while in its folder - put "make" order on the terminal to compile both server and client.
first program to open - server
will be open by order "./server.out port_will_be_listening_on" - of course make sure you put a valid number - port number to open the program successfully. the server will be open and listening, waiting for clients.

second program to open - client
will be open by order "./client.out i.p_adress port_server_is_listening_on" - of course only space_key press betweeen each argument.

for any incorrect data - you will get an "invalid input" message and the program will be closed (incorrect i.p or port will issue a specific message accordingly).

Once client is open - an instructions menu will immediatelly open. follow the options to upload and classify data and eventually - watching/dowmloading results, and exit.
Our server will treat multiple clients in parallel, so fill free to open  many more than one client simultaniously.

You can insert as many inputs as you like - our server will provide an answer!
after one client finish and exit, the server - will stay open for next incoming clients.

Terms explanation:
distance - a type of distance between 2 vectors (one will be classifieid by the other typically)
K- run on the k nearest vectors from the file and return the type of the most return type (if the k you choose is bigger than amount of vectors in file - the program will return the comparison to all of the vectors in the file).
path to a obj_classified.csv file - path (relative or direct) to a file of classified vectors to train with.
path to a obj_Unclassified.csv file - path (relative or direct) to a file of classified vectors to test.


notice: for any ilegal input - the program will show you a message and return you to try again in the main menu.
 the contents of file to train/classify, also needs to be valid - inaccurate representation of numbers will not be able to be classified.

a few words about our implementation:
added in this last version - ability to run multiple clients in parallel using threads.
a smarter code design - using design patterns and abstract classes such as: commands, listener, CLI for more modular and elegant implementations.

the exercise is bulit upon previous exercises, in a object-oriented manner.
using DistanceCalc and KnnCalc object with their uniq abilities, and approaching them from client/server structure.

We execute several validation tests for any user's input before safely storing the data, using a validator object we built.
these validations are made to ensure a future legal calculation for each of the calculator 5 distance types, and according to given data files.

finally, we hold a .h file holding all of functions and libraries signatures.
our code could be easily modified for adding more distance options or change k and data file while running - as you will see using our server menu.

enjoy!

