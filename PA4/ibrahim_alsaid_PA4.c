#include <stdio.h>
#include <string.h>

void filling_array (char input2[100][250]){

	int x=0,y=0; 
	FILE *input; 

	input = fopen ("input2.txt","r");

	while (!feof(input)){

		input2[x][y]=fgetc(input);

		if (input2[x][y]=='\n'){
			x++;
			y=-1;
		}

		y++;
	}

	input2[x][y]='\0'; 

	fclose (input);

}

void comparing_array (char input2[100][250],char word[10]){

	int x=0, y=0,length=0;
	FILE *words,*output;

	words = fopen ("input1.txt","r"); 
	output = fopen ("output.txt","w"); 

	int count_the_diff=0;
	int z=0;
	while (!feof(words)){

		fscanf (words,"%s",word); 

		while (word[z]!='\0' && input2[x][y]!='\0'){ 

			if (input2[x][y]=='\n'){ // to reset after finding and printing the first world 

				y=0;
				x++;

			}

			else if(word[z]==input2[x][y]){ // if the first letter is the same in both 

				if(word[z+1]==input2[x][y+1]){ //horizontally

					length= strlen (word); 
					for (int k=0;k<length;k++){ 
						if(word[k]!=input2[x][y+k]){

							count_the_diff++;

						}

					}

					if (count_the_diff==0){ // means there are no diffrences 
						fprintf(output, "%s (%d,%d) Horizontal\n",word,x+1,y+1 ); 
						x=0;
						y=0;
						z=length;									
					}
					count_the_diff=0;

				}

				else if(word[z+1]==input2[x+1][y]){ //vertically

					length= strlen (word); 
					for (int k=0;k<length;k++){ 

						if(word[k]!=input2[x+k][y]){

							count_the_diff++;
						}
					}

					if (count_the_diff==0){ // means there are no diffrences 
						fprintf(output, "%s (%d,%d) Vertical\n",word,x+1,y+1 );
						x=0;
						y=0;
						z=length;
					}	
					count_the_diff=0;

				}else if(word[z+1]==input2[x+1][y+1]){ // diagonal

					length= strlen (word); 
					for (int k=0;k<length;k++){ 

						if(word[k]!=input2[x+k][y+k]){

							count_the_diff++;
						}
					}

					if (count_the_diff==0){ // means there are no diffrences 
						fprintf(output, "%s (%d,%d) Diagonal\n",word,x+1,y+1 );
						x=0;
						y=0;
						z=length;
					}	
					count_the_diff=0;




				}
			}
		y++;
					
			
		}
		y=0;
		z=0;
		count_the_diff=0;		
		for (int i=0;i<10;i++){

			word[i]='\0';
		}
		x=0;		
	}
	fclose (words);
	fclose (output);
}


int main(){

	char input2[100][250], //to take the file.2 content
	word[10]; //to take the world from the 1. file

	filling_array (input2);
	comparing_array (input2,word);
	
}




