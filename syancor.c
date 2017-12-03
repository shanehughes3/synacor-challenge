#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define MAX_INT 32768

typedef struct {
	uint16_t memory[MAX_INT];
	uint16_t registers[8];
	uint16_t *mem_ptr;
	void (*instructions[22])();
} State;

State *initialize();
uint8_t read_source(State *state);
void run(State *state);

void _exit(State *state);
void _readChar(State *state);
void _noop(State *state);

int main(int argc, char *argv[])
{
	State *state = initialize();
	read_source(state);

	run(state);

	return 0;
}

State *initialize()
{
	State *state = (State *) malloc(sizeof(State));
	state->instructions[0] = _exit;
	state->instructions[1] = _noop;
	state->instructions[2] = _noop;
	state->instructions[3] = _noop;
	state->instructions[4] = _noop;
	state->instructions[5] = _noop;
	state->instructions[6] = _noop;
	state->instructions[7] = _noop;
	state->instructions[8] = _noop;
	state->instructions[9] = _noop;
	state->instructions[10] = _noop;
	state->instructions[11] = _noop;
	state->instructions[12] = _noop;
	state->instructions[13] = _noop;
	state->instructions[14] = _noop;
	state->instructions[15] = _noop;
	state->instructions[16] = _noop;
	state->instructions[17] = _noop;
	state->instructions[18] = _noop;
	state->instructions[19] = _readChar;
	state->instructions[20] = _noop;
	state->instructions[21] = _noop;
	state->mem_ptr = state->memory;

	return state;
}

uint8_t read_source(State *state) 
{
	FILE *input;
	uint16_t buff;
	
	if ((input = fopen("challenge.bin", "r")) == NULL ||
		input == NULL) {
		fprintf(stderr, "synacor: Error opening challenge.bin");
		exit(-1);
	}
	while (fread(&buff, sizeof(uint16_t), 1, input) > 0) {
		*(state->mem_ptr++) = buff;
	}
	fclose(input);
	state->mem_ptr = state->memory;
	
	return 0;
}

void run(State *state)
{
	uint16_t op;
	while (1) {
		op = *state->mem_ptr++;
		if (op > 21) {
			fprintf(stderr,
				"synacor: invalid opcode at 0x%.4lx: %d\n",
				--state->mem_ptr - state->memory, op);
			free(state);
			exit(-2);
		}
		(*state->instructions[op])(state);
	}
}

void _exit(State *state)
{
	free(state);
	exit(0);
}

void _readChar(State *state)
{
	char c = (char) *state->mem_ptr++;
	printf("%c", c);
}

void _noop(State *state)
{
	return;
}