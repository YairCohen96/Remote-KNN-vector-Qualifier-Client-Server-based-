# AP2-AS-YC3
ex3 in advanced programming course 

welcome to our machine learning K NEAREST NEIGHBORS - distance calculator !

the program is now supporting use by server and client:
for a whole use by yourself you will need to open two programs - two terminals:
as always, after cloning the project and while in its folder - put "make" order on the terminal to compile both server and client.
first program to open - server
will be open by order "server.out classified_data_file_path.csv port_will_be_listening_on" - of course only space_key press betweeen each argument
after that - the server will be open and listening, waiting for clients.

second program to open - client
will be open by order "client.out i.p_adress port_server_is_listening_on" - of course only space_key press betweeen each argument

for any incorrect data - you will get an "invalid input" message and the program will be closed (incorrect file path, i.p or port will issue a specific message accordingly).

once client is also open - put in the input to be checked by server is this order:
vector (size of vectors in classified data file) distance k
for example:
1 2 3 4 MAN 12

you can insert as many input as you like - our server will provide an answer!
if you want to close the client, choose "-1" as your input and the client will be closed.
the server - will stay open for next incoming clients



K- run on the k nearest vectors from the file and return the type of the most return type.
path to a obj_classified.csv file - path (relative or direct) to a file of classified vectors to check a vector with.
type of distance - a type of distance between 2 vectors.

notice: for any ilegal input - the program will show you a message and finish immediately!
 (including inaccurate representation of numbers. for example = ".3" will not be accetped! i don't know if your intention is indeed 0.3 or some other idea)

instructions for running the program from terminal:


a few words about our implementation:
the exercise is bulit upon previous exercises, in a object-oriented manner.
using DistanceCalc and KnnCalc object with their uniq abilities, and approaching them from client/server structure.

we execute several validation tests for the user's input before safely storing his chosen numbers in the vector, and a vector type.
these validations are made to ensure a future legal calculation for each of the calculator 5 distance types, and according to given data files.
all validations are exctued by a object build to do so.

finally, we hold a .h file holding all of functions and libraries signatures.
our code could be easily modified for adding more distance options or change k and data file while running.

