/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "digraph.hh"
#include "digraphop.hh"
#include "property.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "tree.hh"

using namespace std;

digraph<Tree, multidep> dependencyGraph(Tree sig);

std::vector<std::pair<string, string>> memoryDependencies(const std::vector<Tree>& I);
// set<Tree>     listTableDependencies(Tree sig);

ostream& dotfile2(ostream& file, const digraph<Tree, multidep>& g);
ostream& dotfile3(ostream& file, const digraph<digraph<Tree, multidep>, multidep>& g);

/**
 * A bijective function that returns a unique ID, that starts with prefix, associated to sig
 * uniqueID(prefix,sig) -> ID
 */
Tree   uniqueID(const char* prefix, Tree sig);
string uniqueStringID(const char* prefix, Tree sig);
