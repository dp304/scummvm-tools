/* DeScumm - Scumm Script Disassembler
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2002-2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef DESCUMM_H
#define DESCUMM_H

#include "util.h"


typedef unsigned int uint;

/**
 * Extremly simple fixed size stack class.
 */
template <class T, int MAX_SIZE = 10>
class FixedStack {
protected:
	T	_stack[MAX_SIZE];
	int	_size;
public:
	FixedStack<T, MAX_SIZE>() : _size(0) {}

	bool empty() const {
		return _size <= 0;
	}
	void clear() {
		_size = 0;
	}
	void push(const T& x) {
		assert(_size < MAX_SIZE);
		_stack[_size++] = x;
	}
	const T& top() const {
		assert(_size > 0);
		return _stack[_size - 1];
	}
	T& top() {
		assert(_size > 0);
		return _stack[_size - 1];
	}
	T pop() {
		T tmp = top();
		--_size;
		return tmp;
	}
	int size() const {
		return _size;
	}
	T& operator [](int i) {
		assert(0 <= i && i < MAX_SIZE);
		return _stack[i];
	}
	const T& operator [](int i) const {
		assert(0 <= i && i < MAX_SIZE);
		return _stack[i];
	}
};

//
// The block stack records jump instructions
//
struct Block {
	uint from;	// From which offset...
	uint to;		// ...to which offset
	bool isWhile;			// Set to true if we think this jump is part of a while loop
};

typedef FixedStack<Block, 256> BlockStack;

extern BlockStack g_blockStack;


//
// Jump decoding auxillaries (used by the code which tries to translate jumps
// back into if / else / while / etc. constructs).
//
extern bool pendingElse, haveElse;
extern int pendingElseTo;
extern int pendingElseOffs;
extern int pendingElseOpcode;
extern int pendingElseIndent;

//
// The opcode of an unconditional jump instruction.
//
extern int g_jump_opcode;

//
// Command line options
//
extern bool alwaysShowOffs;
extern bool dontOutputIfs;
extern bool dontOutputElse;
extern bool dontOutputElseif;
extern bool dontOutputWhile;
extern bool dontOutputBreaks;
extern bool dontShowOpcode;
extern bool dontShowOffsets;
extern bool haltOnError;

extern bool HumongousFlag;
extern bool ZakFlag;
extern bool IndyFlag;
extern bool GF_UNBLOCKED;

//
// The SCUMM version used for the script we are descumming.
//
extern byte scriptVersion;
extern byte heVersion;

//
// Various positions / offsets
//
extern byte *cur_pos, *org_pos;
extern int offs_of_line;

//
// Total size of the currently loaded script
//
extern uint size_of_code;

//
// Common
//

extern void outputLine(const char *buf, int curoffs, int opcode, int indent);

extern char *strecpy(char *buf, const char *src);
extern int get_curoffs();
extern int get_byte();
extern int get_word();
extern int get_dword();

extern bool maybeAddIf(uint cur, uint to);
extern bool maybeAddElse(uint cur, uint to);
extern bool maybeAddElseIf(uint cur, uint elseto, uint to);
extern bool maybeAddBreak(uint cur, uint to);
extern void writePendingElse();

//
// Entry points for the descumming
//
extern void next_line_V0(char *buf);	// For V0
extern void next_line_V12(char *buf);	// For V1 and V2
extern void next_line_V345(char *buf);	// For V3, V4, V5
extern void next_line_V67(char *buf);
extern void next_line_V8(char *buf);
extern void next_line_HE_V72(char *buf);



#endif
