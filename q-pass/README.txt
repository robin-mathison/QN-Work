To run:
"make" will make all needed *.o and *.h files.
"./qpass -*" will execute the "qpass" executable.
"-u" is undirected (meaning paths are two way)
"-d" is directed (meaning paths are one way)
"-m" will print the matrix diagram
e.g.: "./qpass -u -m" will run the executable as an indirected Matrix with a printed output.

After execution, different paths can be made by entering pairs that simulate node to node
connections where "z" is the destination.
Each pair should be followed by the "enter" key.
End of paths can be designated with the "control + d" keys.
e.g.:
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
Finally, q_reserve() will parse through the queue and reserve the path with least hops.
(Still in progression)

