struct tree{
	node *root;
};


struct node
{
	char *value;
	int level;
	node *parent;
	node *next;
	node *child;
};

node *root = 0;

void destroy_tree(node *leaf){
	if(leaf->next != 0){
		destroy_tree(leaf->next);
		destroy_tree(leaf->child);
		free(leaf);
	}
}

insert(char *key, int level, node **leaf){
	if(*leaf == 0){
		*leaf = (node*) malloc(sizeof(node));
		(*leaf)->key = key;
		(*leaf)->level = level;
		(*leaf)->parent = 0;
		(*leaf)->child = 0;
		(*leaf)->next = 0;
	}
	else if(level > (*leaf)->level){
		insert(key, level, &(*leaf)->child);
	}
	else if(level < (*leaf)->level){
		insert(key, level, &(*leaf)->parent);
	}
	else if(level == (*leaf)->level){
		insert(key, level, &(*leaf)->next);
	}
}
