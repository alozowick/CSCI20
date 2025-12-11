#include <iostream>
#include <stack>
#include <string>
#include <algorithm> 
#include <vector>


class calc {
    public:
        void set_rpn_stack(std::stack<std::string> input_stack) {
            rpn_stack = input_stack;
        }
    // Function to process the RPN expression
        int calculate(std::stack<std::string>& exp_stack) {
            // This stack holds the numbers (operands)
            std::stack<int> num_stack;

            while (!exp_stack.empty()) {
                std::string token = exp_stack.top();
                exp_stack.pop();

                // Check if it's one of the basic operations
                if (token == "+" || token == "-" || token == "*" || token == "/") {
                    
                    // This is where we infer quantity: two inputs needed for binary op.
                    if (num_stack.size() < 2) {
                        std::cerr << "Error: Not enough numbers for " << token << std::endl;
                        return 0; 
                    }

                    // Pop the two required numbers (operands)
                    int num2 = num_stack.top();
                    num_stack.pop();
                    int num1 = num_stack.top();
                    num_stack.pop();

                    int result;

                    // Do the math
                    if (token == "+") {
                        result = num1 + num2;
                    } else if (token == "-") {
                        result = num1 - num2;
                    } else if (token == "*") {
                        result = num1 * num2;
                    } else if (token == "/") {
                        if (num2 == 0) {
                            std::cerr << "Error: Divide by zero." << std::endl;
                            return 0;
                        }
                        result = num1 / num2; 
                    }

                    // Push the result back to the number stack
                    num_stack.push(result);

                } else {
                    // It's a number (operand). Infer type: natural number (int).
                    try {
                        num_stack.push(std::stoi(token));
                    } catch (const std::exception& e) {
                        std::cerr << "Error: Bad token: " << token << std::endl;
                        return 0;
                    }
                }
            }

            // Final result should be the only thing left.
            if (num_stack.size() == 1) {
                return num_stack.top();
            } else {
                std::cerr << "Error: Bad expression." << std::endl;
                return 0;
            }
        }
    private:
        std::stack<std::string> rpn_stack;
};


int main() {

    // Manually setting the expression: (3 + 4) * 5 in Prefix RPN: * + 3 4 5
    // Fill the vector so the stack is loaded correctly (reverse order).
    std::vector<std::string> expression_data = {"5", "4", "3", "+", "*"}; 

    std::stack<std::string> rpn_stack;
    
    // Reverse the inputs so the operator (*) is the first thing we pop.
    std::reverse(expression_data.begin(), expression_data.end()); 
    for (const auto& token : expression_data) {
        rpn_stack.push(token);
    }

    std::cout << "--- RPN Calculation: (* + 3 4 5) ---" << std::endl;


    calc rpn_calculator;
    rpn_calculator.set_rpn_stack(rpn_stack);

    int final_answer = rpn_calculator.calculate(rpn_stack);
    
    if (final_answer != 0) {
        std::cout << "Result: " << final_answer << std::endl;
    } else {
        std::cout << "Calculation failed." << std::endl;
    }

    return 0;
}