# Sopfind - Our own implementation of the Find Command
Sopfind uses a Stack- based Directory Traversal utilizing threads, where found subdirs and files are put into a Queue for filtering and results. Supports multiple Filters and Input/Output arguments.

## How to Use & Tests
After Cloning the repo, you will have to cd into the /sopfind folder.
First, remove the current sopfind executable by using:
```
 make clean
```
Then, generate a new executable using:
```
 make 
```
### Tests
We have Tests covering Business Logic aswell as Tests specifically testing Error Cases.

To execute them, use:
```
 make test
```


## General Syntax
./sopfind [-p path] [--stdin] [filters...]

To find general Information about command arguments:
```
 ./sopfind --help
```

##  Coding Assistants
Jan G. :
AI (ChatGPT) was used for:
- MakeFile
- Discussing possible designs of the Traversal core(Recursive vs Stack/Queue based)
- Debugging of the Traversal Core
- Getting information on how to implement tests in C

Nino B.:
AI (Google Gemini) was used for:
 - Planning the worklfow and commit schedule for the filter-engine
 - Discussing and Debugging of the filter-engine

Tim G.:
AI (ChatGPT) was used for:
- Implementation of the command-line interface (CLI)
- Integration of CLI argument parsing into the main application flow
- Testing and verification of search functionality after CLI integration
