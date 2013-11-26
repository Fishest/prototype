Game of Life Simulations
------------------------------------------------------------
The Game of a Life is a simulation of bacterial growth and death rates
that was developed in the 1970's by Mr. Conway. Primarily, the program
consists of a Grid of cells that each have a state of Dead or Alive.
Based on a set of rules, defined in part1.pdf, the cells in the next
generation may change their state. Thus a cell that is Alive in Generation
N could die off in Generation N+1 for a variety of reasons.

Over the years, there have been numerous remakes on the rules and updates
to the supported states for the game. These applications support the intital
rule set with out two possible states and basic rules for progressing to the
next generation. Future releases of these applications will contain a more
varied amount of supported Rules and states. Currently, the applications support
the ability to simulate a specified number of generations using the Life rule set.

The first application, life, supports visualizing a Grid layout in ascii art
on the terminal window. The exact characters can be controlled through the use
of the Chars section of the input file. This application also supports the ability
to export a given generations state into a configuration file. This config file
can then be imported into the programs as well. Please see the applications help
screen for more details "./life -h".

The second application, life_gui, supports visualizing the a Grid ayout through
the creation of a user interface. The interface is built around the QT framework
and thus should would on any platform. The QT version allows for customizing the
Color of the different cells as well as the size of the different cells. This
application supports many of the same feature as life and also has a help screen
in which more informaiton can be found "./life_gui -h".

Technical Breakdown
--------------------------------------------------------------------
For this project, I spent quite a bit of time looking at the design
of the application. Specifically, I didn't want this program to run into
the same limits that I ran into with the last project. Namely, I didn't want
to run into memory issues when processing extremely large, but sparsely populated
grids. I also wanted to make sure that I designed all the peices in such a
way that they could be easily extended in the future when the need arose.

The code based is broke down into several smaller components that are designed
to work with each other to implement the functionality. The clas that is responsible
for all the processing of the input files is the FileParser. The FileParser uses
a system of finite states machines and a custom tokenizer to succesifully parse the 
given files. The custom tokenizer is able to pull content from a file while ignoring
any extra white space as well as commented lines. Thus, the overall parsing of the 
function is made much simpler as the majority of the code won't ever see any whitespace
in the data that it receives. It will also never need to worry about encountering a 
commented line as input. This is all filtered at the lowest level of the Parser.

The Grid class contains all the code that keeps track of the state of particular Grid.
This class needed to be efficient in both memory and speed as a fair portion of the apps
time is spent working with the Grid. The Grid also needed to be easily extendable to 
support new states as they are needed. With these requirements in place, builiding a 
two dimensional grid of integers in memory was not going to be feasible. This layout 
would be inefficient in both memory consumption as well as performance. The terrain and
window values can change and thus the 2D grid would have to change size somewhat frequently.
My implementation of the Grid provides a 2D grid interface to the other classes throughout
the application but internally uses a default state and a map for efficiency. The Grid
will only store data on cells that have been changed from the default state. This leads to 
an efficient implementation in a couple of ways. If we revisit the concept of a extremely large
by sparcely populated Grid as an example. The Grid may be enourmous and thus having an 
entry for each of those entries would take a ton of memory. As most of those states haven't
changed from the default, my implementation would not take much memory at all by comparison.
The memory footprint of my Grid is directly proportional to the the number of cells
not in default state. The lookusp in the table are also efficient in that there are 
not as many entries that will need to be searched before finding the requested point. Internally,
it's perfecty conceivable that the map class is using a Hashmap to perform it's lookups. This
would in turn give my application near constant time lookups.

All throughout the application, I am using virtual functions and inheritance to my advantage.
For instance, each of the structs, such as Life, will inherit from a BaseStruct class. This class
will contain all the code that is consistent among all the structs. This will effectively make
the need for code duplication nonexistent within the application. It also make operations like
exporting content to a file easier since each of the more specific structs will implement the
code that is specific to them. From a high level, the application is provided a BaseStruct pointer
and all it needs to do is call export(FILE) and the file will be generated regardless of the underlying
struct type. You will also see this concept of inheritance in place with the rule sets. the iRuleSet.h
defines a entirely virtual class that is able to be extended. As part of inheriting from this class, 
a function must be implemented to is able to progress a Grid from Generation N to Generation N+1.
Setting up the application such as this make it super easy to define custom RuleSets within the 
application as well as being able up with RuleSets could be used against with Struct types.

The majority of the code is house within the common directory. This will contain all the code responsible for 
processing the input files and calculating the next generation content. There are some self-explanatory
helper classes within that directory that haven't been covered above. Another directory is the life_source directory
which contains the source code for the "./life" application. The other directory, life_gui_source, contains
the source code that handles the visualizing of the Grid in the QT framework. All of the header files with the 
source code repositories are well documented as well in the event that looking at those would provide aid in understanding
the applications.
