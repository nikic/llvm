//===-- OrderedInstructions.cpp - Instruction dominance function ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines utility to check dominance relation of 2 instructions.
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/OrderedInstructions.h"
using namespace llvm;

/// Given 2 instructions, check for dominance relation if the instructions are
/// in the same basic block. Otherwise, use dominator tree.
bool OrderedInstructions::dominates(const Instruction *InstA,
                                    const Instruction *InstB) const {
  if (InstA->getParent() == InstB->getParent())
    return InstA->comesBefore(InstB);
  return DT->dominates(InstA->getParent(), InstB->getParent());
}

bool OrderedInstructions::dfsBefore(const Instruction *InstA,
                                    const Instruction *InstB) const {
  if (InstA->getParent() == InstB->getParent())
    return InstA->comesBefore(InstB);

  DomTreeNode *DA = DT->getNode(InstA->getParent());
  DomTreeNode *DB = DT->getNode(InstB->getParent());
  return DA->getDFSNumIn() < DB->getDFSNumIn();
}
