#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int grille[10][10] = { NULL };
int nbr_iteration;
int step = 0;
int startx[10] = { NULL };
int starty[10] = { NULL };
int goalx[10] = { NULL };
int goaly[10] = { NULL };
int solution[10] = { NULL };

typedef struct _Node {
	struct _Node* parent;
	struct _Node* next;
	int x;
	int y;
	int f;
	int g;
	int h;
}Node;

typedef struct _List {
	Node* first;
};

typedef struct _List* List;

void gridFileOpen(const char* filepath)
{
	//Open grid File
	FILE* f = fopen(filepath, "r");

	//Read file and assign grid
	char c = fgetc(f);
	while (c != EOF)
	{
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				//If c = 0
				if (c == 48)
					grille[x][y] = 0;
				//If c = 1
				if (c == 49)
					grille[x][y] = 1;

				//Next number
				c = fgetc(f);
				while (c != 48 && c != 49)
					c = fgetc(f);
			}
		}
	}

}

void dataFileOpen(const char* filepath)
{
	//Open data File
	FILE* f = fopen(filepath, "r");

	//Read file and assign data
	char c = fgetc(f);
	while (c != EOF)
	{
		if (nbr_iteration == NULL)
			nbr_iteration = c - 48;
		int i = 0;
		c = fgetc(f);
		while (i < nbr_iteration)
		{
			if (c != " " && c != "\n")
			{
				if (startx == NULL)
					startx[i] = c - 48;
				else if (starty == NULL)
					starty[i] = c - 48;
				else if (goalx == NULL)
					goalx[i] = c - 48;
				else if (goaly == NULL)
					goaly[i] = c - 48;
				else solution[i] = c - 48;
			}
			if (c == "\n" || c == EOF)
				i++;
			c = fgetc(f);
		}

	}

}

Node* last(List list)
{
	Node* lastNode = list->first;

	while (lastNode && lastNode->next)
	{
		lastNode = lastNode->next;
	}

	return lastNode;
}

List push(List list, int x, int y)
{
	Node* newnode = (Node*)malloc(sizeof(Node));

	//On attribue les valeurs
	newnode->x = x;
	newnode->y = y;

	newnode->g = step;
	int readx = goalx[0] - newnode->x;
	int ready = goaly[0] - newnode->y;
	if (readx < 0)
		readx = -readx;
	if (ready < 0)
		ready = ready;
	newnode->h = readx + ready;
	newnode->f = newnode->g + newnode->h;

	Node* last_n = last(list);

	if (last_n)
	{
		last_n->next = newnode;
		newnode->parent = last_n;
	}
	else
		list->first = newnode;

	return list;
}

List pop(List list, Node* deleteNode)
{
	Node* node = list->first;

	while (node != deleteNode)
	{
		node = node->next;
	}
	if (node == list->first)
		list->first = node->next;
	else
		node->parent->next = node->next;

	return list;
}

void main()
{
	List openList = calloc(1, sizeof(List));
	List closedList = calloc(1, sizeof(List));

	//Open grid File
	gridFileOpen("F:\\Ecole\\Partiel\\Prog\\Partiel_B1Game_S2_CLang\\grid.txt");

	//Open data File
	dataFileOpen("F:\\Ecole\\Partiel\\Prog\\Partiel_B1Game_S2_CLang\\data.txt");

	closedList = push(closedList, startx, starty);
}