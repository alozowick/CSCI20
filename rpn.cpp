#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>


// Checks if a given string token is an arithmetic operator.
bool is_operator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int main() {
    // Manually define the expression tokens (RPN: 10 2 - 5 * equals 40)
    std::vector<std::string> rpn_tokens = {"10", "2", "-", "5", "*"};

    // The stack holds numbers (operands) and intermediate results.
    std::stack<long long> calculation_stack;

    std::cout << "// RPN Expression: (10 - 2) * 5" << std::endl;
    
    // Process the expression token by token.
    for (const std::string& token : rpn_tokens) {
        
        // **Type Inference:** Check if the token is an operator or a number.
        if (!is_operator(token)) {
            // Found a number. Push it onto the stack.
            try {
                long long number = std::stoll(token);
                calculation_stack.push(number);
                std::cout << "// Pushed number: " << number << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "// Error: Invalid number format." << std::endl;
                return 1;
            }
        } else {
            // **Quantity Inference:** An operator (binary) requires two operands.
            if (calculation_stack.size() < 2) {
                std::cerr << "// Error: Stack has too few operands." << std::endl;
                return 1;
            }

            // Pop operands in correct order (op1 then op2 for op1 <op> op2).
            long long op2 = calculation_stack.top(); calculation_stack.pop();
            long long op1 = calculation_stack.top(); calculation_stack.pop();
            long long result = 0;

            std::cout << "// Operator '" << token << "' found. Calculating: " << op1 << token << op2 << std::endl;

            // Perform the operation.
            if (token == "+") {
                result = op1 + op2;
            } else if (token == "-") {
                result = op1 - op2;
            } else if (token == "*") {
                result = op1 * op2;
            } else if (token == "/") {
                if (op2 == 0) {
                    std::cerr << "// Error: Division by zero." << std::endl;
                    return 1;
                }
                result = op1 / op2;
            }
            
            // Push the calculated result back for the next operation.
            calculation_stack.push(result);
        }
    }

    // The final result remains as the last item on the stack.
    if (calculation_stack.size() == 1) {
        std::cout << "\n// Final Result: " << calculation_stack.top() << std::endl;
    } else {
        std::cerr << "\n// Error: Bad RPN expression." << std::endl;
    }

    return 0;
}