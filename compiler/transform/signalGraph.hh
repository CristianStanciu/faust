/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "digraph.hh"
#include "signals.hh"

using namespace std;

/**
 * @brief generates a dotfile graph of a set of instructions
 *
 * @param "filename.dot" the name of the file
 * @param instr the set of instructions
 */
void signalGraph(const string& filename, const set<Tree>& instr);
void graph2dot(const string& filename, const digraph<Tree, multidep>& G);

/**
 * @brief generates a dotfile graph of a set of instructions in vector mode
 *
 * @param "filename.dot" the name of the file
 * @param instr the set of instructions
 */
void signalVectorGraph(const string& filename, const set<Tree>& instr);
