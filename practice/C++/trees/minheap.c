/*
 * =====================================================================================
 *
 *       Filename:  minheap.c
 *
 *    Description:  Implementation of minheap, insertion and deletion of a number
 *
 *        Version:  1.0
 *        Created:  Wednesday 11 March 2015 04:12:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shounak Dey (), dylandey1996@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int heap[1000];

void insert(int x)
{
	
}

int main()
{
	int size = 0;
	int choice = 0;
	while(choice != 4)
	{
		printf("1.Insert into heap \n 2.Delete from heap \n 3.Print the heap \n 4.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the number to be inserted : ");
				int x;
				scanf("%d",&x);
				insert(x);
				break;
			case 2:
				printf("Enter the number to be deleted : ");
				int x;
				scanf("%d",&x);
				delete(x);
				break;
			case 3:
				print();
				break;
		}
	}
	return 0;
}
