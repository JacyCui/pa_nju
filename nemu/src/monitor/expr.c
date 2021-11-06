#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
	NOTYPE = 256,
	EQ,
	NEQ,
	MORE_EQ,
	LESS_EQ,
	AND,
	OR,
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
	{"[1-9][0-9]*", DEC_NUM}, // decimal number
	{"0[xX][0-9a-fA-F]+", HEX_NUM}, // heximal number
	{"\\+", '+'},
	{"-", '-'},
	{"\\*", '*'},
	{"/", '/'},
	{"%", '%'},
	{"\\$[a-z]{2,3}", REG},
	{"[a-z][a-z0-9]*", SYMB},
	{"\\(", '('},
	{"\\)", ')'},
	{"==", EQ},
	{"!=", NEQ},
	{">", '>'},
	{"<", '<'},
	{">=", MORE_EQ},
	{"<=", LESS_EQ},
	{"!", '!'},
	{"&&", AND},
	{"||", OR},
	{"\\&", '&'},
	{"|", '|'}
};

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

				printf("match regex[%d] at position %d with len %d: %.*s\n", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{
				case NOTYPE: break;
				case '-':
				    if (tokens[nr_token - 1].type == DEC_NUM || tokens[nr_token - 1].type == HEX_NUM || tokens[nr_token - 1].type == REG || tokens[nr_token - 1].type == SYMB) {
				        tokens[nr_token++].type = '-';
				    }
				    else {
				        tokens[nr_token++].type = NEG;
				    }
				    break;
				case '*':
				    if (tokens[nr_token - 1].type == DEC_NUM || tokens[nr_token - 1].type == HEX_NUM || tokens[nr_token - 1].type == REG || tokens[nr_token - 1].type == SYMB) {
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
				    // printf("debug: %s\n", tokens[nr_token].str);
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

uint32_t eval(int p, int q, bool *success) {
    return 0;
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}

	printf("\nPlease implement expr at expr.c\n");
	fflush(stdout);
	assert(0);

	return 0;
}
