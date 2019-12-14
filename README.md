# Blast-Algorithm

Both part one and part two are written in the main.cpp

For the first part, the construction of k-mers a file "fastadb.txt" needs to be provided. The resulting k-mers will be 
stored in a file "db.txt". The variable k is initialized to '5' but it may be changed in the code according to the needs.

For the second part, a file "query.txt" needs to be provided. This file will contain the list of query sequences. 
The results will be written to a file called "results.txt".


Working of part 2:
The query sequence is taken and k-mers generated and stored in a linked list.
The k-mers in the linked list are then compared with the already stored k-mers in the database file.
All the matched k-mers are stored in another linked list
Their start and end points are noted and stored
The whole list is parsed any k-mers that can be merged, are merged e.g one k-mer starts at 1 to 6 and another is 4 to 9 they are both merged to form 1 to 10 sequence k-mer, provided they belong to the same sequence in the database.
The results are this merging along will all other k-mers is stored in a file "matches.txt".
The results are then compared with the original sequences db sequence and the corresponding required values are stored in the results file in a tabular form.
