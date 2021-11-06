#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

uint32_t look_up_symtab(char *sym, bool *success);

enum
{
	NOTYPE = 256,
	EQ,
	NEQ,
	MORE_EQ,
	LESS_EQ,
	AND_,
	OR_,
	DEC_NUM,
	HEX_NUM,
	REG,
	SYMB,
	NEG,
	DE_REF
	/* TODO: Add more token types */
};

static struct rule
{
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +", NOTYPE}, // white space
	{"0[xX][0-9a-fA-F]+", HEX_NUM}, // heximal number
	{"[0-9]+", DEC_NUM}, // decimal number
	{"\\+", '+'},
	{"-", '-'},
	{"\\*", '*'},
	{"/", '/'},
	{"%", '%'},
	{"\\$[a-z]{3}", REG},
	{"[a-z][a-z0-9_]*", SYMB},
	{"\\(", '('},
	{"\\)", ')'},
	{"==", EQ},
	{"!=", NEQ},
	{">=", MORE_EQ},
	{"<=", LESS_EQ},
	{">", '>'},
	{"<", '<'},
	{"!", '!'},
	{"&&", AND},
	{"\\|\\|", OR},
	{"&", '&'},
	{"\\|", '|'},
	{"\\^", '^'},
	{"~", '~'}
};


int get_priority(int type) {
    switch (type) {
        case OR_: return 0;
        case AND_: return 1;
        case EQ: case NEQ: case '<': case '>': case MORE_EQ: case LESS_EQ: return 2;
        case '%': return 3;
        case '+': case '-': return 4;
        case '*': case '/': return 5;
        case '^': return 6;
        case '|': return 7;
        case '&': return 8;
        case '!': case NEG: case DE_REF: case '~': return 100;
        default: return -1;
    }
}


#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while (e[position] != '\0')
	{
		/* Try all rules one by one. */
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				// printf("match regex[%d] at position %d with len %d: %.*s\n", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{
				case NOTYPE: break;
				case '-':
				    if (nr_token != 0 && (tokens[nr_token - 1].type == DEC_NUM || tokens[nr_token - 1].type == HEX_NUM || tokens[nr_token - 1].type == REG || tokens[nr_token - 1].type == SYMB)) {
				        tokens[nr_token++].type = '-';
				    }
				    else {
				        tokens[nr_token++].type = NEG;
				    }
				    break;
				case '*':
				    if (nr_token != 0 && (tokens[nr_token - 1].type == DEC_NUM || tokens[nr_token - 1].type == HEX_NUM || tokens[nr_token - 1].type == REG || tokens[nr_token - 1].type == SYMB)) {
				        tokens[nr_token++].type = '*';
				    }
				    else {
				        tokens[nr_token++].type = DE_REF;
				    }
				    break;
				case DEC_NUM:
				case HEX_NUM:
				case REG:
				case SYMB:
				    strncpy(tokens[nr_token].str, substr_start, substr_len);
				    tokens[nr_token].str[substr_len] = '\0';
				default:
					tokens[nr_token++].type = rules[i].token_type;
				}

				break;
			}
		}
		
		if (i == NR_REGEX)
		{
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true;
}

bool check_parentheses(int p, int q, bool* success) {
    if (tokens[p].type != '(' || tokens[q].type != ')') {
        return false;
    }
    int num = 0;
    for (int i = p + 1; i <= q - 1; i++) {
        if (tokens[i].type == '(') {
            num += 1;
        }
        else if (tokens[i].type == ')') {
            num -= 1;
        }
        if (num < 0) {
            *success = false;
            return false;
        }
    }
    if (num == 0) {
        return true;
    }
    else {
        *success = false;
        return false;
    }
}

int dominant_operator(int p, int q) {
    int split = -1;
    bool valid = true, first = true;
    for (int i = p; i <= q; i++) {
        if (tokens[i].type == '(') {
            valid = false;
            continue;
        }
        if (tokens[i].type == ')') {
            valid = true;
            continue;
        }
        if (valid && get_priority(tokens[i].type) != -1 && get_priority(tokens[i].type) != 100) {
            if (first || get_priority(tokens[i].type) <= get_priority(tokens[split].type)) {
                split = i;
                first = false;
            }
        }
    }
    return split;
}

uint32_t eval(int p, int q, bool *success) {
    if (p > q) {
        *success = false;
        return 0;
    }
    else if (p == q) {
        uint32_t result;
        switch (tokens[p].type) {
            case DEC_NUM: sscanf(tokens[p].str, "%d", &result); break;
            case HEX_NUM: sscanf(tokens[p].str, "%x", &result); break;
            case REG: 
                if (strcmp(tokens[p].str, "$eip") == 0) {
                    result = cpu.eip;
                }
                else if (strcmp(tokens[p].str, "$eax") == 0) {
                    result = cpu.eax;
                }
                else if (strcmp(tokens[p].str, "$ecx") == 0) {
                    result = cpu.ecx;
                }
                else if (strcmp(tokens[p].str, "$edx") == 0) {
                    result = cpu.edx;
                }
                else if (strcmp(tokens[p].str, "$ebx") == 0) {
                    result = cpu.ebx;
                }
                else if (strcmp(tokens[p].str, "$esp") == 0) {
                    result = cpu.esp;
                }
                else if (strcmp(tokens[p].str, "$ebp") == 0) {
                    result = cpu.ebp;
                }
                else if (strcmp(tokens[p].str, "$esi") == 0) {
                    result = cpu.esi;
                }
                else if (strcmp(tokens[p].str, "$edi") == 0) {
                    result = cpu.edi;
                }
                else {
                    result = 0;
                    *success = false;
                }
                break;
            case SYMB: result = look_up_symtab(tokens[p].str, success); break;
            default: result = 0; *success = false;
        }
        return result;
    }
    else if (check_parentheses(p, q, success)){
        return eval(p + 1, q - 1, success);
    }
    else {
        int op = dominant_operator(p, q);
        if (op != -1) {
            uint32_t val1 = eval(p, op - 1, success);
            uint32_t val2 = eval(op + 1, q, success);
            switch (tokens[op].type) {
                case OR_: return val1 || val2;
                case AND_: return val1 && val2;
                case EQ: return val1 == val2;
                case NEQ: return val1 != val2;
                case '<': return val1 < val2;
                case '>': return val1 > val2;
                case MORE_EQ: return val1 >= val2;
                case LESS_EQ: return val1 <= val2;
                case '%': return val1 % val2;
                case '+': return val1 + val2;
                case '-': return val1 - val2;
                case '*': return val1 * val2;
                case '/': 
                    if (val2 != 0) {
                        return val1 / val2;
                    }
                    else {
                        *success = false;
                        return 0;
                    }
                case '^': return val1 ^ val2;
                case '|': return val1 | val2;
                case '&': return val1 & val2;
                default: *success = false; return 0;
            }
        }
        else {
            switch (tokens[p].type) {
                case NEG: return -eval(p + 1, q, success);
                case DE_REF: return vaddr_read(eval(p + 1, q, success), 0, 4);
                case '!': return !eval(p + 1, q, success);
                case '~': return ~eval(p + 1, q, success);
                default: *success = false; return 0;
            }
        }
    }
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}
	return eval(0, nr_token - 1, success);
}
