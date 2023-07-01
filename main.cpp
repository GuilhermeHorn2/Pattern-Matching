#include <stdio.h>
#include <iostream>
#include <vector>


bool pattern_match(std::string &pattern,std::string &value);

bool test_pattern(std::string &pattern,std::string &value,std::string &a,int num_a,int num_b);

int main()
{
	 /* ?\n;||(or) e &&(and)*/


	std::string pattern = "aabab";
	std::string value1 = "catcatgocatgo";

	std::cout << pattern_match(pattern,value1);

	//std::cout << test_pattern_a(pattern,value1,a,3,2);

	return 0;
}

bool test_pattern(std::string &pattern,std::string &value,std::string& a,int num_a,int num_b,char strt){

	//suppose i now what a is,now test if there is a viable configuration of b
	//can be b on front too,does not matter but is simpler if i assume this to build the core algorithm

	int len_a = a.size();
	int len_b = (value.size() - num_a*(len_a))/num_b;
	//std::cout << len_b << '\n';
	int k = 0;
	int i = 0;
	bool has_b = false;
	int curr = 0;
	bool block_curr = false;
	int c = 0;
	//
	bool has_error = false;
	//std::string b = "";
	std::string non_strt = "";
	while(true){
		if(k >= pattern.size() || i+1 >= value.size()){
			break;
		}
		if(pattern[k] == strt){
			//i += len_a;
			if(!block_curr){
				curr = i;
				block_curr = true;
			}
			if(i < curr+len_a){
				if(a[c] != value[i]){
					has_error = true;
				}
				c++;
				if(i+1 == curr+len_a){
					c = 0;
					block_curr = false;
					k++;
				}
			}
		}
		else{
			if(!block_curr){
				curr = i;
				block_curr = true;
			}
			else if(!has_b){
				if(i < curr+len_b){
					non_strt += value[i];
					if(i+1 == curr+len_b){
						has_b = true;
						block_curr = false;
						k++;
					}
				}

			}
			else if(has_b){
				if(i < curr+len_b){
					if(non_strt[c] != value[i]){
						has_error = true;
					}
					c++;
					if(i+1 == curr+len_b){
						block_curr = false;
						c = 0;
						k++;
					}
				}
			}

		}
		i++;

	}
	return !has_error;
}

bool pattern_match(std::string &pattern,std::string &value){


	//find number of a´s and b´s in the value
	int num_a = 0;
	int num_b = 0;
	for(int i = 0;i < pattern.size();i++){
		if(pattern[i] == 'a'){
			num_a++;
		}
		if(pattern[i] == 'b'){
			num_b++;
		}
	}


	//im calling a,but can be b too because the test_pattern function can handle both cases
	std::string a = "";
	for(int i = 0;i < value.size();i++){
		a += value[i];
		if(test_pattern(pattern,value,a,num_a,num_b,pattern[0])){
			return true;
		}

	}
	return false;


}
