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

#include <set>
#include <string>

#include "exception.hh"
#include "faust/gui/JSONUI.h"
#include "instructions.hh"

using namespace std;

#ifdef WIN32
#pragma warning(disable : 4244)
#endif

/*
 FIR visitor to prepare the JSON representation.
*/

struct JSONInstVisitor : public DispatchVisitor, public JSONUI {
    map<string, string> fPathTable;       // Table : field_name, complete path
    set<string>         fControlPathSet;  // Set of already used control paths

    using DispatchVisitor::visit;

    const string& checkPath(set<string>& table, const string& path)
    {
        if (table.find(path) != table.end()) {
            throw faustexception("ERROR : path '" + path + "' is already used\n");
        } else {
            table.insert(path);
        }
        return path;
    }

    JSONInstVisitor(const std::string& name, const std::string& filename, int inputs, int outputs, int sr_index, const std::string& sha_key,
                    const std::string& dsp_code, const std::string& version, const std::string& compile_options,
                    const std::vector<std::string>& library_list, const std::vector<std::string>& include_pathnames,
                    const std::string& size, const std::map<std::string, int>& path_table)
        : JSONUI(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames,
                 size, path_table)
    {
    }

    JSONInstVisitor(int inputs, int outputs) : JSONUI(inputs, outputs) {}

    JSONInstVisitor() : JSONUI() {}

    ~JSONInstVisitor() override = default;

    void visit(AddMetaDeclareInst* inst) override { declare(nullptr, inst->fKey.c_str(), inst->fValue.c_str()); }

    void visit(OpenboxInst* inst) override
    {
        switch (inst->fOrient) {
            case 0:
                openVerticalBox(inst->fName.c_str());
                break;
            case 1:
                openHorizontalBox(inst->fName.c_str());
                break;
            case 2:
                openTabBox(inst->fName.c_str());
                break;
            default:
                faustassert(false);
                break;
        }
    }

    void visit(CloseboxInst* inst) override { closeBox(); }

    void visit(AddButtonInst* inst) override
    {
        switch (inst->fType) {
            case AddButtonInst::kDefaultButton:
                addButton(inst->fLabel.c_str(), nullptr);
                break;
            case AddButtonInst::kCheckButton:
                addCheckButton(inst->fLabel.c_str(), nullptr);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = checkPath(fControlPathSet, buildPath(inst->fLabel));
    }

    void visit(AddSliderInst* inst) override
    {
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                addHorizontalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kVertical:
                addVerticalSlider(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            case AddSliderInst::kNumEntry:
                addNumEntry(inst->fLabel.c_str(), nullptr, inst->fInit, inst->fMin, inst->fMax, inst->fStep);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = checkPath(fControlPathSet, buildPath(inst->fLabel));
    }

    void visit(AddBargraphInst* inst) override
    {
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                addHorizontalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            case AddBargraphInst::kVertical:
                addVerticalBargraph(inst->fLabel.c_str(), nullptr, inst->fMin, inst->fMax);
                break;
            default:
                faustassert(false);
                break;
        }
        faustassert(fPathTable.find(inst->fZone) == fPathTable.end());
        fPathTable[inst->fZone] = checkPath(fControlPathSet, buildPath(inst->fLabel));
    }

    void visit(AddSoundfileInst* inst) override
    {
        addSoundfile(inst->fLabel.c_str(), inst->fURL.c_str(), nullptr);
        faustassert(fPathTable.find(inst->fSFZone) == fPathTable.end());
        fPathTable[inst->fSFZone] = checkPath(fControlPathSet, buildPath(inst->fLabel));
    }

    void setInputs(int input) { fInputs = input; }
    void setOutputs(int output) { fOutputs = output; }
};
