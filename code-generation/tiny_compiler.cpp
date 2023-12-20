#include <iostream>
#include <cmath>
#include "utils.cpp"

using namespace std;

void getSymbolTable(TreeNode* syntax_tree,SymbolTable &symbol_table){
    //  insert the id nodes in the symbol table
    if(syntax_tree->node_kind==READ_NODE || syntax_tree->node_kind==ASSIGN_NODE || syntax_tree->node_kind==ID_NODE){
        symbol_table.Insert(syntax_tree->id, syntax_tree->line_num);
    }
    //  traverse the tree in preorder to get the symbol table
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        if(syntax_tree->child[i]){
            getSymbolTable(syntax_tree->child[i],symbol_table);
        }
    }
    if(syntax_tree->sibling){
        getSymbolTable(syntax_tree->sibling,symbol_table);
    }
}


void replaceNonVoid(TreeNode* syntax_tree,bool &ok){

    //  replace the non-void nodes
    if(syntax_tree->node_kind == NUM_NODE || syntax_tree->node_kind==ID_NODE){
        syntax_tree->expr_data_type=INTEGER;
    }else if(syntax_tree->node_kind == OPER_NODE && (syntax_tree->oper==EQUAL || syntax_tree->oper==LESS_THAN)){
        syntax_tree->expr_data_type=BOOLEAN;
    }else if(syntax_tree->node_kind == OPER_NODE) {
        syntax_tree->expr_data_type = INTEGER;
    }

    //  recursively traverse the tree to replace the non-void nodes and validate nodes
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        if(syntax_tree->child[i]){
            replaceNonVoid(syntax_tree->child[i],ok);
        }
    }
    // after traversing children and validating nodes we traverse the sibling
    if(syntax_tree->sibling){
        replaceNonVoid(syntax_tree->sibling,ok);
    }


    //  match IF_NODE have Boolean type after it
    if(syntax_tree->node_kind == IF_NODE && syntax_tree->child[0]->expr_data_type!=BOOLEAN){
        printf("error: if should be followed by a Boolean on line %d\n",syntax_tree->line_num);
        ok = false;
    }
        //  match REPEAT_NODE have Boolean type after it
    else if(syntax_tree->node_kind == REPEAT_NODE && syntax_tree->child[1]->expr_data_type!=BOOLEAN) {
        printf("error: repeat should be followed by a Boolean on line %d\n" ,syntax_tree->line_num);
        ok = false;
    }
        //  match OPER_NODE have Integer type after and before it
    else if(syntax_tree->node_kind == OPER_NODE){
        if(syntax_tree->child[0]->expr_data_type!=INTEGER || syntax_tree->child[1]->expr_data_type!=INTEGER) {
            printf("error: operand should be followed and preceded by Integer on line %d\n" ,syntax_tree->line_num);
            ok = false;
        }
    }
        // match ASSIGN_NODE have Integer type after it
    else if(syntax_tree->node_kind == ASSIGN_NODE && syntax_tree->child[0]->expr_data_type!=INTEGER){
        printf("error: assign should be followed by an Integer on line %d\n" ,syntax_tree->line_num);
        ok = false;
    }
        // match WRITE_NODE have Integer type after it
    else if(syntax_tree->node_kind == WRITE_NODE && syntax_tree->child[0]->expr_data_type!=INTEGER){
        printf("error: write should be followed by an Integer on line %d\n" ,syntax_tree->line_num);
        ok = false;
    }

}

int getVariableValue(char *name,SymbolTable* symbol_table,int* variables){
    return variables[symbol_table->Find(name)->memloc];
}

int getValue(TreeNode* syntax_tree,SymbolTable* symbol_table,int* variables){
    if(syntax_tree->node_kind==NUM_NODE){
        return syntax_tree->num;
    }else if(syntax_tree->node_kind==ID_NODE){
        return getVariableValue(syntax_tree->id, symbol_table, variables);
    }

    int num1 = getValue(syntax_tree->child[0], symbol_table, variables);
    int num2 = getValue(syntax_tree->child[1], symbol_table, variables);
    TokenType oper = syntax_tree->oper;

    switch (oper) {
        case PLUS:
            return num1+num2;
        case MINUS:
            return num1-num2;
        case TIMES:
            return num1*num2;
        case DIVIDE:
            return num1/num2;
        case POWER:
            return (int)pow(num1,num2);
        case EQUAL:
            return num1==num2;
        case LESS_THAN:
            return num1<num2;
        default:
            return -1;
    }
}

void RunProgram(TreeNode* syntax_tree,SymbolTable* symbol_table,int* variables){

    // code generation for the if statement
    if (syntax_tree->node_kind == IF_NODE){
        int cond = getValue(syntax_tree->child[0], symbol_table, variables);
        if(cond) {
            RunProgram(syntax_tree->child[1], symbol_table, variables);
        }else{
            if(syntax_tree->child[2]){
                RunProgram(syntax_tree->child[2], symbol_table, variables);
            }
        }

    // code generation for the repeat statement
    }else if(syntax_tree->node_kind == REPEAT_NODE){
        do{
            RunProgram(syntax_tree->child[0], symbol_table, variables);
        } while (!getValue(syntax_tree->child[1], symbol_table, variables));

    // code generation for the assign, read and write statements
    }else if(syntax_tree->node_kind == ASSIGN_NODE){
        int val = getValue(syntax_tree->child[0], symbol_table, variables);
        variables[symbol_table->Find(syntax_tree->id)->memloc] = val;

    //        code generation for the read statement
    }else if(syntax_tree->node_kind == READ_NODE){
        cout<<"Enter "<<syntax_tree->id<<": ";
        cin>>variables[symbol_table->Find(syntax_tree->id)->memloc];

    //        code generation for the write statement
    }else if(syntax_tree->node_kind == WRITE_NODE){
        cout<<"Val: "<<getValue(syntax_tree->child[0], symbol_table, variables)<<endl;
    }

    //  traverse the tree in preorder to generate the code
    if(syntax_tree->sibling){
        RunProgram(syntax_tree->sibling, symbol_table, variables);
    }
}

int main(int argc, char **argv)
{
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
    CompilerInfo compiler_info(input_file_name, "output.txt", "debug.txt");

    TreeNode* syntax_tree = Parse(&compiler_info);
    SymbolTable symbol_table;
    getSymbolTable(syntax_tree,symbol_table);
    bool ok = true;
    replaceNonVoid(syntax_tree,ok);

    // arr to store the values of the variables in the symbol table
    int* variables=new int[symbol_table.num_vars];
    memset(variables, 0, sizeof(int)*symbol_table.num_vars);

    if(ok){
        printf("Symbol Table:\n");
        symbol_table.Print();
        printf("\n--------------------------------------------------\n\n");
        printf("Syntax Tree:\n");
        PrintTree(syntax_tree);
        writeTree(&compiler_info, syntax_tree);
        printf("\n--------------------------------------------------\n");
        RunProgram(syntax_tree, &symbol_table, variables);
    }
    return 0;
}