/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
* FindPath.c

Handles IO operations

	Part 1)
		File Input:
				n		(# vertices in graph)
				x y 	(end vertices of corresponding edges)
				x2 y2 	(egdges: [1,n])
				0 0		(terminating dummy line)

		File Output:
			Print adjacency list representation of graph to outfile
				s d 	(lines vertices pairs)
				s1 d1	(source destination)

	Part 2)
		File Input:
				s d 	(line vertices pairs [1,n])
				s1 d1	(source destination)
				0 0 	(terminating dummy line)

Perform Breadth First Search (BFS) from source vertex
Assigns parent vertex to every vertex in graph. Parent vertex (may be NIL)

		File Output:
				(using results of BFS)
				print out the distance for the lines source vertex to destination vertex
				use parent pointers to print out shortest path from s->d

*********************************************************************************/