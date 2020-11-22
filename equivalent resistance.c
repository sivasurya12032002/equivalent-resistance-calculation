#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#define max 100
char stack1[max];
int tos1 = -1;
char infix[max],postfix[max],stack[max];
int tos = -1;
float member[max];
void push1(char element){

	if (tos1 == max-1){
		printf("Stack overflow. Stack can hold a maximum of 100 characters \n");
	}
	else{
		tos1++;
		stack1[tos1] = element;
	}
}

char pop1(){
	if (tos1 == -1){
		printf("Stack underflow\n");
	}
	else{
		return stack1[tos1--];
	}
}

void pushfl(float element)
{
	if (tos == max-1){
		printf("Stack Overflow\n");
	}
	else{
		member[++tos]=element;
	}

}
float popfl(){

return(member[tos--]);


}
int prec(char element){

	if(element ==  '('){
		return 1;
	}

	if(element ==  '+' ){
		return 2;
	}

	if(element == '/'){
		return 3;
	}

}
void push(char element)
{
	if (tos == max-1){
		printf("Stack Overflow\n");
	}
	else{
		stack[++tos]=element;
	}

}
char pop(){
	if (tos == -1){
		printf("Stack Underflow\n");
	}
	else{
		return(stack[tos--]);
	}

}

int balanced(){
	int i,flag = 1;

	for (i = 0;i < strlen(infix);++i){
		if (infix[i] == '(' || infix[i] == '{' || infix[i] == '['){
			push1(infix[i]);
		}
		if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']'){
			if (infix[i] == ')'){
				if (pop1() != '('){
					flag = 0;
				}
			}
			if (infix[i] == '}'){
				if (pop1() != '{'){
					flag = 0;
				}
			}
			if (infix[i] == ']'){
				if (pop1() != '['){
					flag = 0;
				}
			}
		}


	}

		if (flag == 1 && tos1 == -1){
			return 1;
		}
		else{
			return 0;
		}
}

void evalpost(){
	int i=0,j=0;
	char sub[max];
	while(postfix[i] != '\0'){
		if (postfix[i] == '+' || postfix[i] == '/'){
			if (postfix[i] == '+'){
				pushfl(popfl()+popfl());

			}
			if (postfix[i] == '/'){
				pushfl(1/((1/popfl())+(1/popfl())));

			}
			++i;
		}
		else{
			if (postfix[i] != ' '){
				while(isalnum(postfix[i])){
					sub[j++] = postfix[i];
					i++;
				}
				pushfl((float) atof(sub));
				memset(sub,0,sizeof(sub));
				j=0;

			}
			++i;
		}

	}
}

void infix_to_postfix(){
	int i =0,j=0,k=0;
	char sub[max];
	while(infix[i] != '\0'){
		if (isalnum(infix[i])){
			while(isalnum(infix[i])){
				postfix[k++] = infix[i++];
			}
			postfix[k++] = ' ';
		}

		else if (infix[i] == '('){
			push(infix[i]);
			i++;
		}
		else if(infix[i] == ')'){
			while(stack[tos] != '('){
				postfix[k++] = pop();
			}pop();
			i++;
		}
		else{
			if (tos == -1){
				push(infix[i]);
			}
			else{
				while(prec(stack[tos]) >= prec(infix[i])){
					postfix[k++] = pop();
				}
				push(infix[i]);
			}
			i++;
		}

	}
	while(tos != -1){
		postfix[k++] = pop();
	}
	postfix[k++] ='\0';
}

main(){
	int i=0,b;
    printf("\n\n====================EQUIVALENT RESISTANCE CALCULATOR====================\n\n");
	printf("Use S for series and P for parallel\n");
	printf("For example: a 12 ohm resistor in series with a parallel combination of 24 ohm and 12 ohm resistors is entered as 12S(24P12)\n");
	printf("Enter the resistance expression:\t");
	gets(infix);

	while(infix[i] != '\0'){
		if (infix[i] == 'S' || infix[i] == 's'){
			infix[i] = '+';
		}
		if (infix[i] == 'P' || infix[i] == 'p'){
			infix[i] = '/';
		}
		i++;
	}
b = balanced();
if (b==1){
	infix_to_postfix();
evalpost();
printf("\nThe Equivalent resistance between the 2 points for the given circuit is %.2f ohms\n",member[0]);
}
else{
	printf("Enter the equation correctly\n");
}

}
