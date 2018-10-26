//===- llvm/Transforms/Utils/OrderedInstructions.h -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an efficient way to check for dominance relation between 2
// instructions.
//
// FIXME: This is really just a convenience wrapper to check dominance between
// two arbitrary instructions in different basic blocks. We should fold it into
// DominatorTree, which is the more widely used interface.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_ORDEREDINSTRUCTIONS_H
#define LLVM_TRANSFORMS_UTILS_ORDEREDINSTRUCTIONS_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Operator.h"

namespace llvm {

class OrderedInstructions {
  /// The dominator tree of the parent function.
  DominatorTree *DT;

public:
  /// Constructor.
  OrderedInstructions(DominatorTree *DT) : DT(DT) {}

  /// Return true if first instruction dominates the second.
  bool dominates(const Instruction *, const Instruction *) const;

  /// Return true if the first instruction comes before the second in the
  /// dominator tree DFS traversal if they are in different basic blocks,
  /// or if the first instruction comes before the second in the same basic
  /// block.
  bool dfsBefore(const Instruction *, const Instruction *) const;
};

} // end namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_ORDEREDINSTRUCTIONS_H
