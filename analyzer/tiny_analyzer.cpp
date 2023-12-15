#include <iostream>
#include "utils.cpp"

// Define the parse tree node structure functions prototypes
TreeNode* program(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* stmtseq(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* stmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* ifstmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* repeatstmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* assignstmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* readstmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* writestmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* expr(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* mathexpr(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* term(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* factor(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* newexpr(CompilerInfo* pci, ParseInfo* ppi);


// Define the parse tree node structure functions implementations

// match the program non-terminal node
TreeNode* program(CompilerInfo* pci, ParseInfo* ppi) {
    return stmtseq(pci, ppi);
}

// match the stmtseq non-terminal node
TreeNode* stmtseq(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = stmt(pci, ppi);
    while (ppi->next_token.type == SEMI_COLON) {
        GetNextToken(pci, &ppi->next_token);
        TreeNode* nextStmt = stmt(pci, ppi);
        if (node) {
            TreeNode* temp = node;
            while (temp->sibling) {
                temp = temp->sibling;
            }
            temp->sibling = nextStmt;
        } else {
            node = nextStmt;
        }
    }
    return node;
}

// match the stmt non-terminal node
TreeNode* stmt(CompilerInfo* pci, ParseInfo* ppi) {
    switch (ppi->next_token.type) {
        case IF:
            return ifstmt(pci, ppi);
        case REPEAT:
            return repeatstmt(pci, ppi);
        case ID:
            return assignstmt(pci, ppi);
        case READ:
            return readstmt(pci, ppi);
        case WRITE:
            return writestmt(pci, ppi);
        default:
            throw runtime_error("Syntax error in stmt");
    }
}

// match the ifstmt non-terminal node
TreeNode* ifstmt(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = new TreeNode();
    node->node_kind = IF_NODE;
    GetNextToken(pci, &ppi->next_token);
    if (ppi->next_token.type == ID || ppi->next_token.type == NUM || ppi->next_token.type == LEFT_PAREN) {
        node->child[0] = expr(pci, ppi);
    } else {
        throw runtime_error("Syntax error in ifstmt");
    }

    if (ppi->next_token.type == THEN) {
        GetNextToken(pci, &ppi->next_token);
        node->child[1] = stmtseq(pci, ppi);

        if (ppi->next_token.type == ELSE) {
            GetNextToken(pci, &ppi->next_token);
            node->child[2] = stmtseq(pci, ppi);
        }

        if (ppi->next_token.type == END) {
            GetNextToken(pci, &ppi->next_token);
        } else {
            throw runtime_error("Syntax error in ifstmt");
        }
    } else {
        throw runtime_error("Syntax error in ifstmt");
    }

    return node;
}

// match the repeatstmt non-terminal node
TreeNode* repeatstmt(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = new TreeNode();
    node->node_kind = REPEAT_NODE;

    GetNextToken(pci, &ppi->next_token);
    node->child[0] = stmtseq(pci, ppi);

    if (ppi->next_token.type == UNTIL) {
        GetNextToken(pci, &ppi->next_token);
        if (ppi->next_token.type == ID || ppi->next_token.type == NUM) {
            node->child[1] = expr(pci, ppi);
        } else {
            throw runtime_error("Syntax error in repeatstmt");
        }
    } else {
        throw runtime_error("Syntax error in repeatstmt");
    }

    return node;
}

// match the assignstmt non-terminal node
TreeNode* assignstmt(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = new TreeNode();
    node->node_kind = ASSIGN_NODE;

    if (ppi->next_token.type == ID) {
        node->id = new char[MAX_TOKEN_LEN + 1];
        Copy(node->id, ppi->next_token.str);
        GetNextToken(pci, &ppi->next_token);
    } else {
        throw runtime_error("Syntax error in assignstmt");
    }

    if (ppi->next_token.type == ASSIGN) {
        GetNextToken(pci, &ppi->next_token);
        if (ppi->next_token.type == LEFT_PAREN || ppi->next_token.type == ID || ppi->next_token.type == NUM) {
            node->child[0] = expr(pci, ppi);
        } else {
            cout << ppi->next_token.str << endl;
            throw runtime_error("Syntax error in assignstmt");
        }
    } else {
        throw runtime_error("Syntax error in assignstmt");
    }

    return node;
}

// match the readstmt non-terminal node
TreeNode* readstmt(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = new TreeNode();
    node->node_kind = READ_NODE;

    GetNextToken(pci, &ppi->next_token);
    if (ppi->next_token.type == ID) {
        node->id = new char[MAX_TOKEN_LEN + 1];
        Copy(node->id, ppi->next_token.str);
        GetNextToken(pci, &ppi->next_token);
    } else {
        throw runtime_error("Syntax error in readstmt");
    }

    return node;
}

// match the writestmt non-terminal node
TreeNode* writestmt(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = new TreeNode();
    node->node_kind = WRITE_NODE;

    GetNextToken(pci, &ppi->next_token);
    node->child[0] = expr(pci, ppi);

    return node;
}

// match the expr non-terminal node
TreeNode* expr(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = mathexpr(pci, ppi);

    if (ppi->next_token.type == LESS_THAN || ppi->next_token.type == EQUAL) {
        TreeNode* opNode = new TreeNode();
        opNode->node_kind = OPER_NODE;
        opNode->oper = ppi->next_token.type;

        GetNextToken(pci, &ppi->next_token);

        opNode->child[0] = node;
        opNode->child[1] = mathexpr(pci, ppi);

        node = opNode;
    }

    return node;
}

// match the mathexpr non-terminal node
TreeNode* mathexpr(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = term(pci, ppi);

    while (ppi->next_token.type == PLUS || ppi->next_token.type == MINUS) {
        TreeNode* opNode = new TreeNode();
        opNode->node_kind = OPER_NODE;
        opNode->oper = ppi->next_token.type;

        GetNextToken(pci, &ppi->next_token);

        opNode->child[0] = node;
        opNode->child[1] = term(pci, ppi);

        node = opNode;
    }

    return node;
}

// match the term non-terminal node
TreeNode* term(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = factor(pci, ppi);

    while (ppi->next_token.type == TIMES || ppi->next_token.type == DIVIDE) {
        TreeNode* opNode = new TreeNode();
        opNode->node_kind = OPER_NODE;
        opNode->oper = ppi->next_token.type;

        GetNextToken(pci, &ppi->next_token);

        opNode->child[0] = node;
        opNode->child[1] = factor(pci, ppi);

        node = opNode;
    }

    return node;
}

// match the factor non-terminal node
TreeNode* factor(CompilerInfo* pci, ParseInfo* ppi) {
    TreeNode* node = newexpr(pci, ppi);

    while (ppi->next_token.type == POWER) {
        TreeNode* opNode = new TreeNode();
        opNode->node_kind = OPER_NODE;
        opNode->oper = ppi->next_token.type;

        GetNextToken(pci, &ppi->next_token);

        opNode->child[0] = node;
        opNode->child[1] = factor(pci, ppi);

        node = opNode;
    }

    return node;
}

// match the newexpr non-terminal|terminal node
TreeNode* newexpr(CompilerInfo* pci, ParseInfo* ppi) {
    if (ppi->next_token.type == LEFT_PAREN) {
        GetNextToken(pci, &ppi->next_token);
        TreeNode* node = mathexpr(pci, ppi);

        if (ppi->next_token.type == RIGHT_PAREN) {
            GetNextToken(pci, &ppi->next_token);
            return node;
        } else {
            throw runtime_error("Syntax error in newexpr");
        }
    } else if (ppi->next_token.type == NUM) {
        TreeNode* node = new TreeNode();
        node->node_kind = NUM_NODE;
        node->num = stoi(ppi->next_token.str);

        GetNextToken(pci, &ppi->next_token);
        return node;
    } else if (ppi->next_token.type == ID) {
        TreeNode* node = new TreeNode();
        node->node_kind = ID_NODE;
        node->id = new char[MAX_TOKEN_LEN + 1];
        Copy(node->id, ppi->next_token.str);

        GetNextToken(pci, &ppi->next_token);
        return node;
    } else {
        throw runtime_error("Syntax error in newexpr");
    }
}

void writeLogFIle(CompilerInfo* pci, const char* msg) {
    fprintf(pci->debug_file.file, "%s\n", msg);
}


int main(int argc, char **argv) {
    // create the compiler info and parse info objects
    char *input_file_name = argv[1];
    if (!input_file_name)
    {
        printf("error: no input file\n");
        return 1;
    }
    FILE *input_file = fopen(input_file_name, "r");
    if (!input_file)
    {
        printf("error: file %s does not exist\n", input_file_name);
        return 1;
    }
    fclose(input_file);
    CompilerInfo compilerInfo(input_file_name, "output.txt", "debug.txt");
    ParseInfo parseInfo;

    try {
        GetNextToken(&compilerInfo, &parseInfo.next_token);
        TreeNode* root = program(&compilerInfo, &parseInfo); // parse first token to start the parsing
        PrintTree(root); // print the parse tree
        writeTree(&compilerInfo, root); // write the parse tree to the output file
        delete root; // free the memory allocated for the parse tree
    } catch (const exception& e) {
        // print the error message and exit
        cerr << "Error: " << e.what() << endl;
        writeLogFIle(&compilerInfo, e.what()); // write the error message to the log file
        return 1;
    }

    return 0;
}

