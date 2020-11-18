The executable, Q-PASS, simulates the quantum routing protocol described in 4.2 of 
'Modeling and Designing Routing Protocols in Quantum Networks' 
(https://arxiv.org/pdf/1909.09329.pdf). This implementation is in C. 

The program works by inputting s-d pairs that are recursively pushed onto a stack to find paths. 
These paths are then placed into a priority queue and ordered least to most hops. 

To run:
"make" will make all needed *.o and *.h files.
"./qpass -*" will execute the "qpass" executable.
"-u" is undirected (meaning paths are two way)
"-d" is directed (meaning paths are one way) ** this is recommended
"-m" will print the matrix diagram for visualization
e.g.: "./qpass -d -m" will run the executable as a directed Matrix with a printed output.

After execution, different paths can be made by entering pairs that simulate node to node
connections where "a" is the start and "z" is the destination.
Pairs should progress further into indices of the alphabet. See below:
Acceptable format: (in the form value (index))
a(0)b(1)
b(1)c(2)
c(2)z(25)
**This will result in a->b->c->z

Unacceptable format:
a(0)y(24)
y(24)e(4) **this line is incorrect
y(24)z(25)
**This will result in a->y->z

Thus, it is acceptable to skip letters, so long as the first index is lesser than the second.

Each pair should be followed by the "enter" key.
End of paths can be designated with the "control + d" keys.
input example:
ab
bc
cd
dz
de
er
es
sz

This input would yield two paths:
a->b->c->d->z
a->b->c->d->e->s->z

The shortest path distance would also be recorded.
Afterwards, the paths will be put into a priority queue from least to greatest hops.
Finally, q_reserve() will parse through the queue and reserve the path with least hops and create a queue of unsatisfiable paths.
(Still in progression)

