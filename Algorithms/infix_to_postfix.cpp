/* O(1) - Checks if a character is an operator. */
bool is_operator(char c){
	return c == '+' or c == '-' or c == '*' or c == '/' or c == '^' or c == '(' or c == ')';
}

/* O(1) - Checks if a character in an expression is an unary operator. */
bool is_unary_operator(const string &infix, int i){
	if (infix[i] == '+' or infix[i] == '-'){
		return i == 0 or (is_operator(infix[i - 1]) and infix[i - 1] != ')');
	}

	return false;
}

/* O(1) - Returns the precedence value of an operator. */
int precedence(char c){
	if (c == '(' or c == ')'){
		return 0;
	}

	if (c == '+' or c == '-'){
		return 1;
	}

	if (c == '*' or c == '/'){
		return 2;
	}

	return 3;
}

/* O(N) - Converts an Infix expression to a Postfix expression.
Assumes that the given string is a correct Infix expression with no spaces.
Works with unary operators such as +a or -a but only if the unary
operator directly precedes an operand.
Examples:
	Valid: +a+b*(-c+((d))*-e) ---> {+a, b, -c, d, -e, *, +, *, +}
	Invalid: a+b*(-(c)+d*e)
	Invalid: a+b*-(c+d*e) */
vector<string> infix_to_postfix(const string &infix){
	vector<string> postfix;
	stack<string> s;

	for (int i = 0; i < (int)infix.size();){
		if (is_operator(infix[i]) and !is_unary_operator(infix, i)){
			if (infix[i] == '('){
				// Just push opening parenthesis.
				s.push("(");
			}
			else if (infix[i] == ')'){
				// Pop everything until opening parenthesis.
				while (s.top() != "("){
					postfix.push_back(s.top());
					s.pop();
				}

				s.pop();
			}
			else{
				// Pop everything that has greater or equal precedence that the current operator.
				while (!s.empty() and precedence(s.top()[0]) >= precedence(infix[i])){
					postfix.push_back(s.top());
					s.pop();
				}

				// Push current operator.
				s.push(infix.substr(i, 1));
			}

			i++;
		}
		else{
			int j;

			// Retrieving the entire operand.
			for (j = i + 1; j < (int)infix.size(); j++){
				if (is_operator(infix[j])){
					break;
				}
			}

			// Pushing operand.
			postfix.push_back(infix.substr(i, j - i));
			i = j;
		}
	}

	// Pushing the remaining operators.
	while (!s.empty()){
		postfix.push_back((string)s.top());
		s.pop();
	}

	return postfix;
}