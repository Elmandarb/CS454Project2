#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>


// Project 2
// Eric Fleming

int delta(int start, int input, int length) {
    return (10 * start + input) % length;
}

std::string findString(int k, std::vector<int> digits) {
    //Initialize our data structures and set to their default start values
    std::queue<int> Q;
    bool visited[k];
    int parent[k];
    int label[k];
    for(int j = 0; j < k; j++ ) {
        visited[j] = false;
        parent[j] = -1;
    }
    visited[0] = true;
    int index = 0;
    int next;
    //Populate queue and arrays with children of our start node
    while(index < digits.size()) {
        if(digits[index] != 0) {
            next = delta(0,digits[index],k);
            visited[next] = true;
            Q.push(next);
            parent[next] = 0;
            label[next] = digits[index];
        }
        index++;
    }
    //While there are still children in the queue
    while(!Q.empty()) {
        int current = Q.front();
        Q.pop();
        index = 0;
        //Get a child and iterate through all options in the language
        while(index < digits.size()) {
            //get the next value on a language input
            next = delta(current, digits[index], k);
            //If the next value is zero we have found a correct string
            if(next == 0) {
                parent[next] = current;
                label[next] = digits[index];
                //traverse backwards through our label array then reverse the generated string
                std::string answer = "";
                while(parent[next] != 0) {
                    answer += std::to_string(label[next]);
                    next = parent[next];
                }
                answer += std::to_string(label[next]);
                std::reverse(answer.begin(), answer.end());
                //return the found string and exit the program
                return "Answer is : " + answer;
            }
            else if(!visited[next]) {
                //If the next value isnt zero and hasnt been evaluated mark its parent and push to Q
                visited[next] = true;
                parent[next] = current;
                label[next] = digits[index];
                Q.push(next);
            }
            index++;
        }
        
    }
    //if(next != 0) {
    //If no items are left in Q and we never hit zero inside the loop return no solution
    return "No solution for inputs";
}


int main() {
    std::string ans;
    int k = 0;
    std::cout << "Please enter a number between 1 and 99999, to exit enter -1" << std::endl;
    while(true){
        std::vector<int> digits = {};
        std::string number;
        //Get first number for k
        getline(std::cin,number);
        //handles non numeric/space
        for (int i = 0; i < number.length(); i++) {
            if(!isdigit(number[i]) && !isspace(number[i])) {
                std::cout << "Sorry this number is invalid, exiting..." << std::endl;
                exit(1);
            }
        }
        //handles null string case
        if(number.size() < 1) {
            std::cout << "Sorry this number is invalid, exiting..." << std::endl;
            exit(1);
        }
        //turns string into a number
        k = stoi(number);
        if(k < 1 || k > 999999) {
            std::cout << "Sorry this number is invalid, exiting..." << std::endl;
            exit(1);
        }
        else{
            //get numbers for digits
            std::string nums = "";
            std::cout << "Please Enter accepted values in the language and followed by spaces: " << std::endl;
            getline(std::cin,nums);
            int strIndex = 0;
            while(strIndex < nums.length()) {
                if(isdigit(nums.at(strIndex))) {
                    digits.push_back((int)(nums.at(strIndex)-'0'));
                }
                strIndex++;
            }
            //run and print our findString
            ans = findString(k, digits);
            std::cout << ans << std::endl;
            std::cout << "Please enter a number between 1 and 99999, to exit enter -1" << std::endl;
        }
    }
    
    return 0;
}